/*

			Craters  --  The Screen Saver
			
		by John Walker  --  kelvint@netcom.com
		
*/ 

#include "craters.h"

#ifdef _DEBUG
#define Timing		1
#define Statistics	1
#define Elevation	1
#endif

static HGLOBAL haux;						// Elevation array handle
static unsigned short __huge *aux;          // Elevation array pointer
static HGLOBAL hDIbits;						// DI bitmap handle

#define Auxadr(x, y)  ((unsigned short __huge *) (aux + ((((long) (y)) * (long) (scrX + 1)) + ((long) (x)))))

#ifdef _DEBUG
#define D(x) {char s[132]; wsprintf(s, "Craters: %s\r\n", x); OutputDebugString(s); }
#else
#define D(x)
#endif

// Definitions for obtaining random numbers.

#define Cast(low, high) ((low) + ((high) - (low)) * (random() / arand))

//  Display parameters

#define ImageGamma 0.4						// Image gamma
#define rollmin 0.9                         // Roll-off factor
#define MAXSTAMPER  40 	   					// Largest stamper size

//  Local variables

static int scrX, scrY;              		// Screen size
static int maxcrater = 200;					// Largest crater size
static double arand = (double) (LONG_MAX);	// Random number range
static double dgamma = 1.0;					// Display gamma
static double CdepthPower = 1.5;			// Crater depth power factor
static double DepthBias = 0.707107;			// Depth bias
static HGLOBAL stampers[MAXSTAMPER];		// Handles of stampers
static BOOL initslope = TRUE;				// Initialise slope to grey tables ?
static int slopemin = -52, slopemax = 52;	// Slope minimum and max (canned)
static unsigned char slopemap[128];         // Map from slope to intensity
static HPALETTE imagePal = NULL;			// Custom colour palette
static DWORD lastReset;						// Time of last reset
#ifdef Timing
static long nCraters = 0;					// Craters generated
static time_t startTime;					// Start time
#endif
#ifdef Statistics
static long tinyCraters = 0,				// Number of tiny (Moore) craters
			stampedCraters = 0,             // Number of craters stamped
			calculatedCraters = 0;          // Number of craters calculated
#endif

static struct {								// Logical palette
	WORD	palVersion;
	WORD	palNumEntries;
	PALETTEENTRY palPalEntry[256];
} logpal;

static struct {								// DI bitmap used to paint craters
	BITMAPINFOHEADER bmi;
	unsigned short palidx[256];
} pBits;

//  INITSEED  --  Generate initial random seed, if needed.

static void initseed(void)
{
	srandom(GetTickCount());
}

//  DISPINIT  --  Initialise colour palette.
		  
static void dispinit(void)
{
	int i;

	// Generate shades to represent elevation albedo
	
	logpal.palVersion = 0x300;
	logpal.palNumEntries = 256;
	for (i = 0; i <= 255; i++) {
		logpal.palPalEntry[i].peRed =
		logpal.palPalEntry[i].peGreen =
		logpal.palPalEntry[i].peBlue = (BYTE) i;
		logpal.palPalEntry[i].peFlags = PC_NOCOLLAPSE;
	}
	imagePal = CreatePalette((LPLOGPALETTE) &logpal);
}

/*  GSTAMP  --	Get stamper for crater of a given size.  If no stamper
				is available return NULL.  */

static HGLOBAL gstamp(int gy)
{
	int x, y;
	double g = gy;
	float FAR *sbuf;

	if (gy >= MAXSTAMPER) {		// If too big for a stamper
		return NULL;			// make caller do it the hard way
	}

	if (stampers[gy] != NULL) {	// If stamper of this size already exists
	   return stampers[gy];    	// just return the pre-allocated stamper.
	}

	// Create a stamper for craters of this size.

	stampers[gy] = GlobalAlloc(GHND, sizeof(float) * 2 * (gy + 1) * (gy + 1));
	if (stampers[gy] == NULL) {
		return NULL;
	}
	sbuf = (float FAR *) GlobalLock(stampers[gy]);
	if (sbuf == NULL) {
		GlobalFree(stampers[gy]);
		stampers[gy] = NULL;	
		return NULL;
	}

	for (y = 0; y <= gy; y++) {
		float FAR *ax = sbuf + (y * 2 * (gy + 1));
		double dy = y / (double) gy,
			   dysq = dy * dy;

		for (x = 0; x <= gy; x++) {
			double dx = x / ((double) gy),
				   cd = (dx * dx) + dysq,
				   cd2 = cd * 2.25,
				   tcz = DepthBias - sqrt(fabs(1 - cd2)),
				   cz = max((cd2 > 1) ? 0.0 : -10, tcz),
				   roll;

			*ax++ = (float) (cz * pow(g, CdepthPower));

			roll = (((1 / (1 - min(rollmin, cd))) /
					(1 / (1 - rollmin))) - (1 - rollmin)) / rollmin;
			*ax++ = (float) roll;
		}
	}
	GlobalUnlock(stampers[gy]);
	return stampers[gy];	   		// Return newly-built stamper
}

//  RELSTAMP  --  Release all stampers. 

void relstamp(void)
{
	int i;

	for (i = 0; i < MAXSTAMPER; i++) {
		if (stampers[i] != NULL) {
			GlobalFree(stampers[i]);
			stampers[i] = NULL;
		}
	}
}

//  RESET_ELEVATION  --  Reset elevation to flat terrain.

static void reset_elevation(void)
{
	int i, j;
	
	for (i = 0; i < scrY; i++) {
	   unsigned short __huge *zax = aux + (((long) scrX + 1) * i);
	   for (j = 0; j < scrX + 1; j++)
	      *zax++ = 32767;
	}
}

//  CLEARSCREEN  --  Clear the screen to flat terrain.

static void clearScreen(HWND hWnd, HDC hDC)
{
	RECT wi;
	HBRUSH bbr;
	
	GetClientRect(hWnd, &wi);
	bbr = CreateSolidBrush(RGB(127, 127, 127));
	FillRect(hDC, &wi, bbr);
	DeleteObject(bbr);
}

//  GENCRATERS	--  Generate cratered terrain.

static void gencraters(HWND hWnd, HDC hDC, int budget)
{
	int i, llenb;
  	HPALETTE opal;
  	static BOOL needClear = TRUE;
  	unsigned char __huge *bits, __huge *pits, __huge *lbits; // DIB pointer
	double g;
	int cx, cy, gx, gy, x, y, top, bot, left, right;
	long amptot, axelev;
	int npatch;

	if (initslope) {
	
		/* If it's been requested, update the mapping from slopes
		   to screen intensities. */

		for (i = slopemin; i <= slopemax; i++) {
		
	        /* Confused?  OK, we're using the left-to-right slope to
		       calculate a shade based on the sine of the angle with
		       respect to the vertical (light incident from the left).
		       Then, with one exponentiation, we account for both the
		       inherent gamma of the image (ad-hoc), and the
		       user-specified display gamma, using the identity:
	
						(x^y)^z = (x^(y*z))		     */
	
			slopemap[i - slopemin] = (unsigned char ) (i > 0 ?
				(128 + 127.0 *
					pow(sin((PI / 2) * i / slopemax),
			       dgamma * ImageGamma)) :
				(128 - 127.0 *
					pow(sin((PI / 2) * i / slopemin),
			       dgamma * ImageGamma)));
		}
		initslope = FALSE;
	}
	
    pits = (unsigned char __huge *) GlobalLock(hDIbits);
    if (pits == NULL) {
    	return;
    }
  	if (imagePal != NULL) {
		opal = SelectPalette(hDC, imagePal, FALSE);
		RealizePalette(hDC);
	}

	while (budget-- > 0) {
		amptot = 0;
		npatch = 0;
		cx = (int) Cast(0.0, ((double) scrX - 1));
	    cy = (int) Cast(0.0, ((double) scrY - 1));
		
		/* Phase 1.	Compute the mean elevation of the impact
		   area.  We assume the impact area is a
		   fraction of the total crater size.
			
		   Thanks, Rudy, for this equation that maps the uniformly
		   distributed numbers from Cast into an area-law distribution
		   as observed on cratered bodies. */
		   
		g = sqrt(1 / (PI * (1 - Cast(0, 0.9999))));

//		Define Twiggle to draw craters of increasing size for debugging.
//#define Twiggle
#ifdef Twiggle
		{	static int gee = 1;
			
{ char s[132]; wsprintf(s, "Cratersize = %d\r\n", gee); OutputDebugString(s); }
			g = gee++;
			cx = scrX / 2;
			cy = scrY / 2;
			budget = 0;
		}
#endif

		g = min(g, (maxcrater - 1) / 2);		// Limit crater size

		// If the crater is tiny, handle it specially
	
		if (g < 3) {
#ifdef Statistics
			tinyCraters++;
#endif

			// Set pixel to the average of its Moore neighbourhood.
			
			for (y = max(0, cy - 1); y <= min(scrY - 1, cy + 1); y++) {
				int sx = max(0, cx - 1);
				unsigned short __huge *a = Auxadr(sx, y);
	
				for (x = sx; x <= min(scrX - 1, cx + 1); x++) {
					amptot += *a++;
					npatch++;
				}
			}
			axelev = amptot / npatch;
			*Auxadr(cx, cy) = (unsigned short) axelev;
	
			// Jam repaint sizes to correct patch.
			gx = 0;
			gy = 0;
	
		} else {
	
			/* Regular crater.  Generate an impact feature of the
			   correct size and shape. */
	        
	        HGLOBAL shandle;
			float FAR *stamp;
	
			// Determine mean elevation around the impact area.
	
			gx = gy = (int) max(2, g / 4);

			for (y = max(0, cy - gy); y <= min(scrY - 1, cy + gy); y++) {
				int sx = max(0, cx - gx);
				unsigned short __huge *a = Auxadr(sx, y);
	
				for (x = sx; x <= min(scrX - 1, cx + gx); x++) {
					amptot += *a++;
					npatch++;
				}
			}
			axelev = amptot / npatch;
	
			g = gx = gy = (int) max(2, g);
			
			shandle = NULL;
			stamp = NULL;
	
			shandle = gstamp(gy);			// Look for stamper of this size
			if (shandle != NULL) {
				stamp = (float FAR *) GlobalLock(shandle);
			}

			if (stamp != NULL) {
#ifdef Statistics
				stampedCraters++;
#endif
			
				for (y = max(0, cy - gy); y <= min(scrY - 1, cy + gy); y++) {
					int sx = max(0, cx - gx), ex = min(scrX - 1, cx + gx);
					unsigned short __huge *ax = Auxadr(sx, y);
					float FAR *sp1 = stamp + 2 * (abs(y - cy) * (gx + 1));
					int x;
	
					for (x = sx; x <= ex; x++) {
						double roll, cz;
						unsigned short av;
						float FAR *sp = sp1 + (2 * abs(x - cx));
							
						cz = *sp++;
						roll = *sp;
							
						av = (unsigned short) ((axelev + cz) * (1 - roll) +
									(*ax + cz) * roll);
						*ax++ = (unsigned short) max(1000, min(64000, av));
					}
				}
				GlobalUnlock(shandle);
	
			} else {
	
				/* Can't generate the crater with a stamper.  Do it
				   the hard way, from the fundamental definition. */
#ifdef Statistics
				calculatedCraters++;
#endif

				for (y = 0; y <= gy; y++) {
					double dy = y / ((double) gy),
						   dysq = dy * dy;

					for (x = 0; x <= gx; x++) {
						double dx = x / ((double) gx),
							   cd = (dx * dx) + dysq,
							   cd2 = cd * 2.25,
							   tcz = DepthBias - sqrt(fabs(1 - cd2)),
							   cz = max((cd2 > 1) ? 0.0 : -10, tcz),
							   roll, iroll;
						unsigned short av;
						unsigned short __huge *ax;
								
						cz *= pow(g, CdepthPower);
						if (dy == 0 && dx == 0 && ((int) cz) == 0) {
							cz = cz < 0 ? -1 : 1;
						}
	
						roll = (((1 / (1 - min(rollmin, cd))) /
								(1 / (1 - rollmin))) - (1 - rollmin)) / rollmin;
						iroll = 1 - roll;
	                    
	                    /*	Exploit symmetry to set all pixels to which this
	                    	floating point calculation applies.  */

#define doPix(tx, ty)	if ((tx) >= 0 && (tx) < scrX && (ty) >= 0 && (ty) < scrY) { \
	                    	ax = Auxadr((tx), (ty)); \
							av = (unsigned short) ((axelev + cz) * iroll + (*ax + cz) * roll); \
							*ax = (unsigned short) max(1000, min(64000, av)); }
						doPix(cx + x, cy + y);
						if (x > 0) {
							doPix(cx - x, cy + y);
						}
						if (y > 0) {
							doPix(cx + x, cy - y);
							if (x > 0) {
								doPix(cx - x, cy - y);
							}
						}
#undef doPix
					}
				}		
			}
		}
		
		// If first time or time to reset, clear the screen
	
		if (needClear) {
			needClear = FALSE;
			clearScreen(hWnd, hDC);
		}
		
		/* Repaint the area of the screen affected by the most
		   recent impact. */
	
		llenb = (maxcrater + (sizeof(LONG) - 1)) & ~(sizeof(LONG) - 1);
			
		top = max(0, cy - gy);
		bot = min(scrY - 1, cy + gy);
		left = max(0, cx - gx);
		right = min(scrX - 1, cx + gx);
		bits = pits + llenb * ((long) (bot - top));
		for (y = top; y <= bot; y++) {
			unsigned short __huge *ax = Auxadr(left, y);
			
            lbits = bits;
            bits -= llenb;  
			for (x = left; x <= right; x++) {
				int arg = ax[1] - ax[0];
				arg = min(max(arg, slopemin), slopemax);
				arg = slopemap[arg - slopemin];
				*lbits++ = (unsigned char) arg;
#ifdef Twiggle
				*ax = 32767;
#endif				
				ax++;
			}
		}
		SetDIBitsToDevice(hDC, left, top, (right - left) + 1, (bot - top) + 1,
        		0, 0, 0, (bot - top) + 1,
	        		pits, (LPBITMAPINFO) &pBits, DIB_PAL_COLORS);

#ifdef Timing
		nCraters++;
#endif	        		
	}
	GlobalUnlock(hDIbits);			
	if (imagePal != NULL) {
		SelectPalette(hDC, opal, FALSE);
	}
}

//  CRATERINIT  --  Initialise crater generation.

BOOL craterInit(void)
{
	int i;
	RECT rc;
	DWORD bmsi;

#ifdef Timing 
	startTime = time((time_t *) NULL);
#endif
	lastReset = GetTickCount();		// Get tick count at start
	DepthBias = sqrt(0.5);			// Get exact value for depth bias

	initseed();
	dispinit();
	
	/* Acquire the elevation array and initialise it to mean
	   surface elevation. */
    
    GetWindowRect(GetDesktopWindow(), &rc);
    scrX = rc.right;
    scrY = rc.bottom;
	haux = GlobalAlloc(GHND, ((DWORD) scrX + 1) * scrY * sizeof(short));
	if (haux == NULL) {
		return FALSE;
	}
	hDIbits = GlobalAlloc(GHND, bmsi = ((DWORD) ((maxcrater + (sizeof(LONG) - 1)) &
											~(sizeof(LONG) - 1))) * maxcrater);
	if (hDIbits == NULL) {
		GlobalFree(haux);
		return FALSE;
	}
//return FALSE;					// Test out of mem during init

	// Initialise elevation buffer to mean initial elevation.
	
	aux = (unsigned short __huge *) GlobalLock(haux);
	if (aux == NULL) {
		GlobalFree(haux);
		GlobalFree(hDIbits);
	   return FALSE;
	}
    reset_elevation();
	GlobalUnlock(haux);
	
	// Initialise device-independent bitmap header.
	
	pBits.bmi.biSize = sizeof(BITMAPINFOHEADER);
	pBits.bmi.biWidth = maxcrater;
	pBits.bmi.biHeight = maxcrater;
	pBits.bmi.biPlanes = 1;
	pBits.bmi.biBitCount = 8;
	pBits.bmi.biCompression = BI_RGB;
	pBits.bmi.biSizeImage = bmsi;
	pBits.bmi.biXPelsPerMeter = pBits.bmi.biYPelsPerMeter = 1000;
	pBits.bmi.biClrUsed = 256;
	pBits.bmi.biClrImportant = 256;
	for (i = 0; i < 256; i++) {
		pBits.palidx[i] = (unsigned short) i;	// Initialise logical palette indices
	}
	
	// Initialise stamper handle table
	
	for (i = 0; i < MAXSTAMPER; i++) {
		stampers[i] = NULL;
	}
	return TRUE;
}

//  CRATERMAKE  --  Create another budgeted set of craters.

BOOL craterMake(HWND hWnd, HDC hDC, int budget)
{
//if ((random() & 0xFFL) == 131) return FALSE;	// Test out of mem during make
	aux = (unsigned short __huge *) GlobalLock(haux);
	if (aux == NULL) {
	   return FALSE;
	}
	if ((resetInterval > 0) && (GetTickCount() > (lastReset + resetInterval))) {
		reset_elevation();
		clearScreen(hWnd, hDC);
		lastReset = GetTickCount();
	}
	gencraters(hWnd, hDC, budget);
	GlobalUnlock(haux);
	return TRUE;
}               

/*  CRATERTERM  --  Terminate crater generation and release all resources.
					Note that craterTerm can be called more than once in
					the case of an out of memory condition, and must clean
					up after itself so it doesn't do anything silly in
					such an eventuality.  */

void craterTerm(void)
{
#ifdef _DEBUG
	if (haux != NULL) {
#ifdef Elevation
		aux = (unsigned short __huge *) GlobalLock(haux);
        if (aux != NULL) {
        	unsigned short emin = USHRT_MAX, emax = 0;
        	int x, y;
        	char s[132];
        	
        	for (y = 0; y < scrY; y++) {
        		unsigned short __huge *a = Auxadr(0, y);
        		for (x = 0; x < scrX; x++) {
        			unsigned short e = *a++;
        			emin = min(e, emin);
        			emax = max(e, emax);
        		}
        	}
        	GlobalUnlock(haux);
			wsprintf(s, "Elevation: min = %u, max = %u, average = %ld.\r\n", emin, emax,
				(((long) emin) + emax)/ 2);
			OutputDebugString(s); 	
        }
#endif _Elevation        
#ifdef Timing
		{	time_t elapsedTime = time((time_t *) NULL) - startTime;
			char s[132];
			
			wsprintf(s, "%ld craters in %ld seconds.  %ld craters/second.\r\n", nCraters,
				elapsedTime, nCraters / elapsedTime);
			OutputDebugString(s); 	
		}
#endif // Timing
#ifdef Statistics
		{	char s[132];
			
			wsprintf(s, "Craters: %ld tiny, %ld normal (%ld stamped, %ld calculated).\r\n",
				tinyCraters, stampedCraters + calculatedCraters,
				stampedCraters, calculatedCraters);
			OutputDebugString(s);
		} 	
#endif // Statistics
	}
#endif // _DEBUG
	if (haux != NULL) {
		GlobalFree(haux);
		haux = NULL;
	}
	if (hDIbits != NULL) {
		GlobalFree(hDIbits);
		hDIbits = NULL;
	}
	relstamp();
	if (imagePal != NULL) {
		DeleteObject(imagePal);
		imagePal = NULL;
	}
}
