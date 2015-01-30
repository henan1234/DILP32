// ============================================================================
// PAYSAGE.C
// Dessine le paysage en arriere plan de la foret
// ============================================================================
#include <windows.h>
#include <windowsx.h>
#include <math.h>

extern int	Alea( int, int ) ;
#define DEG_RAD(x)		(((x)+180) * 3.14 * 2.0  / 360.0)
#define SIN(x)				sin( DEG_RAD(x))
#define COS(x)				cos( DEG_RAD(x))

// ----------------------------------------------------------------------------
// Degarde
// Fait un degrade horizontal
// ----------------------------------------------------------------------------
static void Degrade( HDC   hDC,
			     int   x,
			     int   y,
			     int   l,
			     int   h,
			     int   n,
			     DWORD CouleurDepart,
			     DWORD CouleurArrivee )
{
	int 			Rouge, Vert, Bleu ;
	int 			i ;
	HBRUSH			hBrush ;
	HBRUSH			hOBrush ;
	int 			HauteurBande ;
	HPEN			hOPen ;

	hOPen = SelectPen( hDC, GetStockObject( NULL_PEN )) ;
   HauteurBande = (h / n) ;


    for (i = 0; i < n; i++)
		{
		/* =============================== Creation de la brosse correspondante */
		Rouge	=	GetRValue( CouleurDepart ) +
					i * (GetRValue(CouleurArrivee)
						 - GetRValue(CouleurDepart)) / n ;
		
		Vert	=	GetGValue( CouleurDepart ) +
					i * (GetGValue(CouleurArrivee)
					 - GetGValue(CouleurDepart)) / n ;
		
		Bleu	= GetBValue( CouleurDepart ) +
					i * (GetBValue(CouleurArrivee)
					 - GetBValue(CouleurDepart)) / n ;
		hBrush = CreateSolidBrush( RGB( Rouge, Vert, Bleu ) ) ;
		
		hOBrush = SelectObject( hDC, hBrush ) ;
		
		/* ================================================ Tracer le rectangle */
		PatBlt( hDC,
			x,
			y + HauteurBande * i,
			l,
			HauteurBande,
			PATCOPY ) ;
			
		SelectObject(hDC, hOBrush ) ;
		DeleteObject( hBrush ) ;
		}

    hBrush  = CreateSolidBrush( CouleurArrivee) ;
    hOBrush = SelectObject( hDC, hBrush ) ;

    PatBlt( hDC,
	    x,
	    y + h - (h - HauteurBande * n),
	    l, h - HauteurBande * n,
	    PATCOPY ) ;
    SelectObject( hDC, hOBrush ) ;
    DeleteObject( hBrush ) ;

	SelectObject( hDC, hOPen ) ;

}


// ----------------------------------------------------------------------------
// Affiche un nuage aleatoire
// ----------------------------------------------------------------------------
void __inline	AfficheNuage( HDC hDC, int x, int y )
{
	HPEN	hOldPen ;
	HBRUSH hOldBrush ;
	int	i ;
	int	RayonMax ;
	int	Rayon ;
	
	hOldPen = SelectPen( hDC, GetStockObject( NULL_PEN )) ;
	hOldBrush= SelectBrush( hDC, GetStockObject( WHITE_BRUSH)) ;
	
	RayonMax = 20 ;
	
	for ( i = 0; i < Alea( 5, 30 ); i++)
		{
		Rayon = Alea( 10, RayonMax ) ;
		RayonMax += 3 ;
		Ellipse( hDC, x-Rayon, y-Rayon*2, x+Rayon, y) ;
		x += Rayon  ;
		}
	
	SelectPen( hDC, hOldPen ) ;
	SelectBrush( hDC, hOldBrush ) ;
}

// ----------------------------------------------------------------------------
// AfficheOiseau
// ----------------------------------------------------------------------------
static void AfficheOiseau( HDC hDC, int x, int y )
{
	POINT	Pt[8] ;
	HBRUSH hOldBrush ;
	HPEN	 hOldPen ;
	
	Pt[2].x	=	x ;
	Pt[2].y	=	y ;
	
	Pt[6].x	=	x ;
	Pt[6].y	=	y + 4 ;
	
	Pt[1].x	=	x - 10 - Alea( 0, 2 ) ;
	Pt[1].y	=	y - 10 - Alea( 0, 2 ) ;
	
	Pt[7].x	=	Pt[1].x ;
	Pt[7].y	=	Pt[1].y - 3 ;
	
	Pt[0].x	=	Pt[1].x - Alea( 5, 7 );
	Pt[0].y	=	Pt[1].y + Alea( 5, 7 );
	
	Pt[3].x	=	x + 10 + Alea( 0, 2 ) ;
	Pt[3].y	=	y - 10 - Alea( 0, 2 ) ;
	
	Pt[5].x	=	Pt[3].x ;
	Pt[5].y	=	Pt[3].y - 3 ;
	
	Pt[4].x	=	Pt[3].x + Alea( 5, 7 );
	Pt[4].y	=	Pt[3].y + Alea( 5, 7 );
	
	hOldBrush	=	SelectBrush( hDC, GetStockObject( BLACK_BRUSH )) ;
	hOldPen		=	SelectPen( hDC, GetStockObject( BLACK_PEN )) ;
	Polygon( hDC, Pt, 8 ) ;
	SelectBrush( hDC, hOldBrush ) ;
	SelectPen( hDC, hOldPen ) ;
}

void	AfficheSoleil( HDC hDC, int x, int y, int Rayon )
{
	HPEN	hPen, hOldPen ;
	HBRUSH	hBrush, hOldBrush ;
	int	i ;
   int   LongueurRayon ;
   
	hBrush = CreateSolidBrush( RGB( 255, 255, 128 ) ) ;
	hOldPen = SelectPen( hDC, GetStockObject( NULL_PEN )) ;
	hOldBrush = SelectBrush( hDC, hBrush ) ;
	
	Ellipse( hDC,  x- Rayon,
						y- Rayon,
						x+ Rayon,
						y+ Rayon ) ;
	
	SelectBrush( hDC, hOldBrush ) ;
	DeleteObject( hBrush ) ;
	
	hPen =	CreatePen( PS_SOLID, 5, RGB( 255, 255, 0 ) ) ;
	SelectPen( hDC , hPen ) ;
	for ( i = 0; i < 360; i+= 20 )
		{
		LongueurRayon = Alea( Rayon, Rayon*2 ) ;
		MoveToEx( hDC, x + (int)(Rayon*SIN(i)), y + (int)(Rayon*COS(i)), NULL);
		LineTo( hDC, x + (int)(LongueurRayon*SIN(i)), y + (int)(LongueurRayon*COS(i)));
		}

	SelectPen( hDC, hOldPen ) ;
	DeletePen( hPen ) ;
}

void PeintPaysage( HDC hDC, LPRECT lpR )
{
	UINT	HauteurSol ;
	int	XSol, YSol ;
	int	Rayon ;
	int	i ;
	HauteurSol = lpR->top + ( lpR->bottom-lpR->top) / 2 ;
	
	// Afficher le ciel
	Degrade( hDC, lpR->left, lpR->top, lpR->right-lpR->left,
			     lpR->bottom-lpR->top- HauteurSol ,
			     32,
			     RGB( 0, 128, 128 ),
			     RGB( 128, 255, 255 ) ) ;
	// Afficher le soleil
	XSol = Alea( lpR->left,lpR->right ) ;
	YSol = Alea( lpR->top, lpR->bottom-HauteurSol ) ;
	Rayon = (lpR->right-lpR->left)/20 ;
	AfficheSoleil( hDC, XSol, YSol, Rayon ) ;	
	// Nuages
	Rayon = Alea( 2, 16 ) ;
	for ( i = 0; i < Rayon; i++)
		AfficheNuage( hDC, Alea( lpR->left, lpR->right ), Alea( lpR->top, lpR->bottom-HauteurSol )) ;

	// Oiseaux
	Rayon = Alea( 3, 20 ) ;
	for ( i = 0; i < Rayon; i++)
		AfficheOiseau( hDC, Alea( lpR->left, lpR->right ), Alea( lpR->top, lpR->bottom-HauteurSol )) ;

	// Afficher le sol
	Degrade( hDC, lpR->left, lpR->bottom-HauteurSol, lpR->right-lpR->left, HauteurSol , 32, RGB( 128, 255, 128 ), RGB( 0, 128, 0 ) ) ;
}
