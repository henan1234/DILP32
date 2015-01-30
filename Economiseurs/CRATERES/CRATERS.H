/*

			Craters  --  The Screen Saver
			
		by John Walker  --  kelvint@netcom.com
		
            		Definitions
		
*/ 

#include <windows.h>

#include <scrnsave.h>
#include <string.h>
#include <time.h>
#include "resource.h"
#ifndef RC_INVOKED
#include <math.h>
#include <limits.h>
#endif

#ifdef WIN32
#define _huge
#define __huge
#define _fmemcpy memcpy
#define _fstrlen strlen
#define _fstrstr strstr
typedef RGBQUAD *LPRGBQUAD;
#define STRETCH_DELETESCANS COLORONCOLOR
#define MoveTo(h, x, y)	MoveToEx((h), (x), (y), NULL)
#endif

//      String codes in resource file

#define IDS_APPNAME				103		// Application name/title

#define PI 3.14159265358979323846		/* Assume not near black hole nor in
                                      	   Tennessee */

//  Handy mathematical functions

#ifdef abs
#undef abs
#endif

#define abs(x) ((x) < 0 ? (-(x)) : (x))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

//  Assertion checking for Windows

#ifndef NDEBUG
#define assert(x) { if (!(x)) { char erm[128]; wsprintf((LPSTR) erm, \
        (LPSTR) "Assertion %s failed at line %d of file %s.", (LPCSTR) #x, __LINE__,(LPSTR) __FILE__); \
        FatalAppExit(0, (LPCSTR) erm); }}
#else
#define assert(x)
#endif

//	Make sure no debug output remains in production builds: use Honk(x) for debug MessageBeep(x)

#ifdef NDEBUG
#define OutputDebugString(x) &&&&&&&&&}}}}}}}}}}}}}}
#define Honk(x) &&&&&&&&&}}}}}}}}}}}}}}
#define MessageBeep(x) &&&&&&&&&}}}}}}}}}}}}}}
#else
#define Honk(x)	MessageBeep(x)
#endif

extern char szString[128];		// Variable to load resource strings
#define hInst	hMainInstance
#define hWndMain hMainWindow
//extern HINSTANCE hInst;			// Class instance pointer
extern HWND hWndMain;			// Main window pointer

extern DWORD resetInterval;		// Screen reset interval

//	Window message processing procedure

#define WindowProc(x) LONG FAR PASCAL x(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)

//	Dialogue message processing function

#define DialogueProc(name) BOOL FAR PASCAL name(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)

//	From CRATERS.C
extern BOOL craterInit(void), craterMake(HWND hWnd, HDC hDC, int budget);
extern void craterTerm(void), relstamp(void);

//  From RANDOM.C
extern void srandom(unsigned long seed);
extern long random(void);
