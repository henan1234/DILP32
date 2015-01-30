#include "..\economiseur generique\stdafx.h"
#include <math.h>
#include <signal.h>
#include "resource.h"
#include "..\economiseur generique\RectAffichage.h"
#include "LiaisonForte.h"
#include "utilitaires.h"

extern COLORREF	CouleurFond ;
extern COLORREF	AtomeSature ;
extern COLORREF	AtomeLibre ;
extern COLORREF	CouleurLien ;
extern int		Diviseur ;
extern int		NbLiens ;
extern int		NbMaxLiensParAtome ;
extern int		NbAtomes ;
extern CRectAffichage	NouveauxRectangles ;
extern CRectAffichage	DerniersRectangles ;

extern double	X1, X2, X3, X4, X5, X6, X7, X8 ;
extern double	Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8 ;
double	DeltaX5, DeltaX6, DeltaX7, DeltaX8 ;
double	DeltaY5, DeltaY6, DeltaY7, DeltaY8 ;
double pX5 ; double pY5 ;
double pX6 ; double pY6 ;
double pX7 ; double pY7 ;
double pX8 ; double pY8 ;

#pragma inline_recursion( off )
#pragma inline_depth( 0 )

void CalculeDeltas( double NbSegments )
	{
	DeltaX5	=	(X1 - X5) / NbSegments ;
	DeltaY5	=	(Y1 - Y5) / NbSegments ;
	DeltaX6	=	(X2 - X6) / NbSegments ;
	DeltaY6	=	(Y2 - Y6) / NbSegments ;
	DeltaX7	=	(X3 - X7) / NbSegments ;
	DeltaY7	=	(Y3 - Y7) / NbSegments ;
	DeltaX8	=	(X4 - X8) / NbSegments ;
	DeltaY8	=	(Y4 - Y8) / NbSegments ;

	}
void	Trace( CDC & Dc, double & X, double & Y, double DeltaX, double DeltaY )
{
	Dc.MoveTo( (int)X, (int)Y ) ;
	Dc.LineTo( (int)(X+DeltaX), (int)(Y+DeltaY)) ;

	X += DeltaX ;
	Y += DeltaY ;
}


void	SelectionneClippingRegion( CDC & Dc)
	{
	const int	NbRectangles	=	DerniersRectangles.NbRectangles() ;
	const CRect *	pRect	=	DerniersRectangles.Rectangles() ;

	RGNDATA * pRgnData	=	(RGNDATA *)malloc( sizeof( RGNDATA ) + NbRectangles * sizeof( RECT )) ;

	pRgnData->rdh.dwSize	=	sizeof( pRgnData->rdh ) ;
	pRgnData->rdh.iType		=	RDH_RECTANGLES ;
	pRgnData->rdh.nCount	=	NbRectangles ;
	pRgnData->rdh.nRgnSize	=	NbRectangles * sizeof( RECT ) ;
	pRgnData->rdh.rcBound	=	CRect( 0, 0, CLiaisons::Largeur, CLiaisons.Hauteur ) ;

	memcpy( &pRgnData->Buffer[0], pRect, NbRectangles * sizeof( RECT ) ) ;

	HRGN hRgn	=	ExtCreateRegion( NULL, sizeof( RGNDATA ) + NbRectangles * sizeof( RECT ),
								 pRgnData ) ;

	SelectClipRgn( Dc.m_hDC, hRgn ) ;

	DeleteObject( hRgn ) ;
	free( pRgnData ) ;
	}


void TraceCadreDuFond( CDC & Dc )
	{
	// Dessine le rectangle du fond
	BYTE	Rouge	=	255 ;
	BYTE	Vert	=	255 ;
	BYTE	Bleu	=	255 ;


	
	EloigneCouleur( DISTANCE_MAX, Rouge, Vert, Bleu ) ;
	const int	Largeur	=	CalculDiametre( DISTANCE_MAX, DIAMETRE_MAX_LIEN/2 ) ; 

	CPen	Pinceau( PS_SOLID|PS_COSMETIC|PS_ENDCAP_ROUND, Largeur, RGB( Rouge, Vert, Bleu )) ;
	CPen * pOld = Dc.SelectObject( &Pinceau ) ;
	Dc.MoveTo( (int)X5, (int)Y5 ) ;
	Dc.LineTo( (int)X6, (int)Y6 ) ;
	Dc.LineTo( (int)X7, (int)Y8 ) ;
	Dc.LineTo( (int)X8, (int)Y8 ) ;
	Dc.LineTo( (int)X5, (int)Y5) ;
	Dc.SelectObject( pOld ) ;
	Pinceau.DeleteObject() ;
	}


void TraceSegmentsLateraux( CDC & Dc )
	{
	const int NbSegments	=	64 / Diviseur + 1 ;

	pX5 = X5 ; pY5 = Y5 ;
	pX6 = X6 ; pY6 = Y6 ;
	pX7 = X7 ; pY7 = Y7 ;
	pX8 = X8 ; pY8 = Y8 ;

	CalculeDeltas(NbSegments) ;

	CPen Pinceau ;

	// Dessine les bords qui s'eloignent
	for ( double i = DISTANCE_MAX; i > 0; i-=DISTANCE_MAX/NbSegments )
		{
		const int Largeur	=	CalculDiametre( i, DIAMETRE_MAX_LIEN/2 ) ; 

		BYTE Rouge	=	255 ;
		BYTE Vert	=	255 ;
		BYTE Bleu	=	255 ;
		EloigneCouleur( i, Rouge, Vert, Bleu ) ;

		Pinceau.CreatePen( PS_SOLID|PS_COSMETIC|PS_ENDCAP_ROUND, Largeur, RGB( Rouge, Vert, Bleu )) ;
		CPen* pOld	=	Dc.SelectObject( &Pinceau ) ;

		Trace( Dc, pX5, pY5, DeltaX5, DeltaY5 ) ;
		Trace( Dc, pX6, pY6, DeltaX6, DeltaY6 ) ;
		Trace( Dc, pX7, pY7, DeltaX7, DeltaY7 ) ;
		Trace( Dc, pX8, pY8, DeltaX8, DeltaY8 ) ;

		Dc.SelectObject( pOld ) ;
		Pinceau.DeleteObject() ;
		}
	}

void	DessineCage( CDC & Dc )
	{
	const int	NbRectangles=DerniersRectangles.NbRectangles() ;

	if ( NbRectangles )
		SelectionneClippingRegion(Dc) ;
	
	TraceCadreDuFond(Dc) ;
	
	TraceSegmentsLateraux( Dc ) ;

	if ( NbRectangles )
		SelectClipRgn( Dc.m_hDC, NULL ) ;
}
	
