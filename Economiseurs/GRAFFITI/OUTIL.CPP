///////////////////////////////////////////////////////////////////////////////
// Classe generique Outil
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <math.h>
#include <scrnsave.h>
#include "outil.h"

CRect	DernierRect ;

int	__inline ChangeIntervalle( int Valeur, int SrcMin, int SrcMax, int DstMin, int DstMax )
	{
	if ( Valeur <= SrcMin )
		return DstMin ;

	if ( Valeur >= SrcMax )
		return DstMax ;

	Valeur -= SrcMin ;
	Valeur	=	MulDiv( Valeur, (DstMax-DstMin), (SrcMax-SrcMin)) ;
	Valeur +=	DstMin ;
	return Valeur ;
	}

inline int COutil::Alea( int Min, int Max )
{
	return (rand() % (Max-Min+1)) + Min ;
}

inline COLORREF COutil::InterpoleCouleur( int Val, int Min, int Max, COLORREF Base, COLORREF Nouvelle )
{
return Nouvelle	=	RGB( ChangeIntervalle( Val, Min, Max, GetRValue( Base ), GetRValue( Nouvelle )),
						 ChangeIntervalle( Val, Min, Max, GetGValue( Base ), GetGValue( Nouvelle )),
						 ChangeIntervalle( Val, Min, Max, GetBValue( Base ), GetBValue( Nouvelle ))) ;
}

///////////////////////////////////////////////////////////////////////////////
// CouleurHasard
// Retourne une couleur au hasard
///////////////////////////////////////////////////////////////////////////////
inline COLORREF COutil::CouleurHasard( void )
	{
	return RGB( Alea( 0, 255),
				Alea( 0, 255),
				Alea( 0, 255) ) ;
	}


BOOL	COutil::Poids( void )
	{
	_Poids ++ ;

	if ( _Poids < _UnSur )
		return FALSE ;

	_Poids = 0 ;
	return TRUE ;
	}

COutil::COutil()
	{
	_Poids	=	0 ;
	_UnSur	=	0 ;
	}

///////////////////////////////////////////////////////////////////////////////
// Trace : par defaut on traite tous les points un par un sur le segment
///////////////////////////////////////////////////////////////////////////////
void	COutil::Trace( CDC & Dc, int x1, int y1, int x2, int y2 )
	{
	_pDCLigneDroite	=	&Dc ;
	LineDDA( x1, y1, x2, y2, LineDDAProc, (LPARAM)this ) ;
	}


void CALLBACK	COutil::LineDDAProc( int x , int y, LPARAM lp )
	{
	COutil *	pOutil	=	(COutil*)lp ;
	ASSERT_VALID( pOutil ) ;

	if ( pOutil->Poids())
		pOutil->PointDeLigneDroite( *(pOutil->_pDCLigneDroite), x, y ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Classe Stylo
///////////////////////////////////////////////////////////////////////////////
CStylo::CStylo()
	{
	_Pen.CreatePen( PS_SOLID, Alea( 1, 4 ), CouleurHasard() ) ;
	}

CStylo::~CStylo()
	{
	_Pen.DeleteObject() ;
	}

void	CStylo::Trace( CDC & Dc, int x1, int y1, int x2, int y2 )
	{
	CPen*	pOld	=	Dc.SelectObject( &_Pen ) ;
	Dc.MoveTo( x1, y1 ) ;
	Dc.LineTo( x2, y2 ) ;
	Dc.SelectObject( pOld ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Classe Plume ( trait incline )
///////////////////////////////////////////////////////////////////////////////
CPlume::CPlume()
	{
	_Pen.CreatePen( PS_SOLID, 2, CouleurHasard() ) ;

	_dx		=	 Alea( -10, 10 ) ;
	_dy		=	 Alea( -10, 10 ) ;
	}

CPlume::~CPlume()
	{
	_Pen.DeleteObject() ;
	}


void	CPlume::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	CPen*	pOld	=	Dc.SelectObject( &_Pen ) ;
	Dc.MoveTo( x, y ) ;
	Dc.LineTo( x+_dx, y+_dy ) ;
	Dc.SelectObject( pOld ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Classe Craie ( points eparpilles )
///////////////////////////////////////////////////////////////////////////////
CCraie::CCraie()
	{
	_Couleur	=	CouleurHasard()  ;
	_Largeur	=	Alea( 2, 20 ) ;
	}

void	CCraie::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	const int	Surface	=	_Largeur * _Largeur ;
	const int	Minx	=	x - _Largeur/2 ;
	const int	Maxx	=	x + _Largeur/2 ;
	const int	Miny	=	y - _Largeur/2 ;
	const int	Maxy	=	y + _Largeur/2 ;

	for ( int i = 0; i < Surface / 8; i++)
		Dc.SetPixelV( Alea( Minx, Maxx ), Alea( Miny, Maxy ), _Couleur ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Classe CraieGrasse ( points eparpilles et estompes )
///////////////////////////////////////////////////////////////////////////////
CCraieGrasse::CCraieGrasse()
	{
	_Couleur	=	CouleurHasard() ;
	_Largeur	=	Alea( 2, 20 ) ;
	}

void	CCraieGrasse::PointDeLigneDroite( CDC & Dc, int X, int Y )
	{
	const int	Surface	=	_Largeur * _Largeur ;
	const int	Minx	=	X - _Largeur/2 ;
	const int	Maxx	=	X + _Largeur/2 ;
	const int	Miny	=	Y - _Largeur/2 ;
	const int	Maxy	=	Y + _Largeur/2 ;

	for ( int i = 0; i < Surface / 8; i++)
		{
		const	int	x	=	Alea( Minx, Maxx ) ;
		const	int	y	=	Alea( Miny, Maxy ) ;
		const COLORREF	Couleur	=	Dc.GetPixel( x, y ) ;
		const	int	NiveauEstompe	=	Alea( 16, 240 ) ;

		const COLORREF Nouvelle	=	InterpoleCouleur( NiveauEstompe, 0, 256, _Couleur, Couleur ) ;
		Dc.SetPixelV( x, y, Nouvelle ) ;
		}
	}


///////////////////////////////////////////////////////////////////////////////
// Classe Aerographe
///////////////////////////////////////////////////////////////////////////////
CAerographe::CAerographe()
	{
	_Couleur	=	CouleurHasard()  ;
	_Largeur	=	Alea( 8, 50 ) ;
	ASSERT( _Largeur/2 > 2 ) ;
	InitPoids( Alea( 2, _Largeur/2 )) ;
	}

void	CAerographe::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	const int	DemiLargeur		=	_Largeur/2 ;

	for ( int i = x - DemiLargeur; i < x + DemiLargeur; i++)
		for ( int j	=	y - DemiLargeur; j < y + DemiLargeur; j ++ )
			{
			int	Distance=(int)sqrt( (x-i)*(x-i) + (y-j)*(y-j)) ;
			if ( Distance < DemiLargeur )
				{
				COLORREF Couleur	=	Dc.GetPixel( i, j ) ;
				COLORREF Nouvelle	=	InterpoleCouleur( Distance, 0, DemiLargeur, _Couleur , Couleur ) ;
				Dc.SetPixelV( i, j, Nouvelle ) ;
				}
			}
	}

///////////////////////////////////////////////////////////////////////////////
// Classe Estompe
///////////////////////////////////////////////////////////////////////////////
CEstompe::CEstompe()
	{
	DernierRect.SetRectEmpty() ;
	_Largeur	=	Alea( 8, 20 ) ;

	CDC	Dc ;
	Dc.CreateDC( "display", 0,0,0 ) ;
	_MemDC.CreateCompatibleDC( &Dc ) ;

	CBitmap	*	pBit	=	new CBitmap() ;
	pBit->CreateCompatibleBitmap( &Dc, _Largeur, _Largeur ) ;

	_pOld	=	_MemDC.SelectObject( pBit ) ;
	}


CEstompe::~CEstompe()
	{
	CBitmap*	pBit	=	_MemDC.SelectObject( _pOld ) ;
	pBit->DeleteObject() ;
	delete pBit ;
	}

void	CEstompe::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	_MemDC.BitBlt( 0, 0, _Largeur, _Largeur, &Dc, x, y, SRCCOPY ) ;

	for ( int i = 0; i < _Largeur; i++)
		for ( int j	=	0; j < _Largeur; j++)
		if (	! DernierRect.PtInRect( CPoint (x+i, y+j))) 
			_MemDC.SetPixelV( i, j, CouleurMoyenne( Dc, x + i, y + j )) ;
		
	Dc.BitBlt( x, y, _Largeur, _Largeur, &_MemDC, 0, 0, SRCCOPY ) ;

	DernierRect.SetRect( x, y, x+_Largeur, y + _Largeur ) ;
	}

COLORREF	CEstompe::CouleurMoyenne( CDC & Dc, int x, int y )
	{
	COLORREF	Couleur0	=	Dc.GetPixel( x,		y	) ;
	COLORREF	Couleur1	=	Dc.GetPixel( x,		y+1 ) ;
	COLORREF	Couleur2	=	Dc.GetPixel( x,		y-1 ) ;
	COLORREF	Couleur3	=	Dc.GetPixel( x+1,	y	) ;
	COLORREF	Couleur4	=	Dc.GetPixel( x+1,	y+1 ) ;
	COLORREF	Couleur5	=	Dc.GetPixel( x+1,	y-1 ) ;
	COLORREF	Couleur6	=	Dc.GetPixel( x-1,	y	) ;
	COLORREF	Couleur7	=	Dc.GetPixel( x-1,	y+1 ) ;
	COLORREF	Couleur8	=	Dc.GetPixel( x-1,	y-1 ) ;

	const int	R	=	GetRValue( Couleur0 ) * 9 +
						GetRValue( Couleur1 ) +
						GetRValue( Couleur2 ) +
						GetRValue( Couleur3 ) +
						GetRValue( Couleur4 ) +
						GetRValue( Couleur5 ) +
						GetRValue( Couleur6 ) +
						GetRValue( Couleur7 ) +
						GetRValue( Couleur8 ) ;

	const int	G	=	GetGValue( Couleur0 ) * 9 +
						GetGValue( Couleur1 ) +
						GetGValue( Couleur2 ) +
						GetGValue( Couleur3 ) +
						GetGValue( Couleur4 ) +
						GetGValue( Couleur5 ) +
						GetGValue( Couleur6 ) +
						GetGValue( Couleur7 ) +
						GetGValue( Couleur8 ) ;

	const int	B	=	GetBValue( Couleur0 ) * 9 +
						GetBValue( Couleur1 ) +
						GetBValue( Couleur2 ) +
						GetBValue( Couleur3 ) +
						GetBValue( Couleur4 ) +
						GetBValue( Couleur5 ) +
						GetBValue( Couleur6 ) +
						GetBValue( Couleur7 ) +
						GetBValue( Couleur8 ) ;

	return RGB( R/17, G/17, B/17 ) ;
	}


CDoigt::CDoigt()
	{
	_Largeur	=	Alea( 4, 30 )  ;
	_Poids		=	Alea( 16, 240 ) ;
	}

void	CDoigt::PointDeLigneDroite( CDC & Dc, int x , int y )
	{
	for ( int	i = x + _Largeur - 1; i > x; i--)
		for ( int j = y; j < y + _Largeur; j++)
		{
		const COLORREF Couleur	=	Dc.GetPixel( i, j ) ;
		const COLORREF CouleurBase	=	Dc.GetPixel( i-1, j ) ;
		const COLORREF Nouvelle	=	InterpoleCouleur( _Poids, 0, 256, Couleur , CouleurBase ) ;
		Dc.SetPixelV( i, j, Nouvelle ) ;
		}

	}


CSurligneur::CSurligneur()
	{
	_Couleur	=	CouleurHasard()  ;
	_Largeur	=	Alea( 4, 20 ) ;
	_Force		=	Alea( 16, 64 ) ;
	}

void	CSurligneur::PointDeLigneDroite( CDC & Dc, int x , int y )
	{
	for ( int	i = x + _Largeur - 1; i > x; i--)
		for ( int j = y; j < y + _Largeur; j++)
		if ( ! _DernierRectangle.PtInRect( CPoint( i, j )))
		{
		const COLORREF Couleur	=	Dc.GetPixel( i, j ) ;
		const COLORREF Nouvelle	=	InterpoleCouleur( _Force, 0, 256, _Couleur, Couleur ) ;
		Dc.SetPixelV( i, j, Nouvelle ) ;
		}

	_DernierRectangle.SetRect( x, y, x+_Largeur, y+_Largeur ) ;
	}



CPinceau::CPinceau()
	{
	_Couleur	=	RGB( Alea( 16, 239 ), Alea( 16, 239), Alea( 16, 239)) ;
	_Largeur	=	Alea( 5, 20 ) ;
	_Hauteur	=	Alea( 5, 20 ) ;
	InitPoids( Alea( 2, min( _Largeur, _Hauteur )/2)) ;
	}

void CPinceau::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	CBrush	Brosse( RGB(	GetRValue( _Couleur ) + (BYTE)Alea( -8, 8),
							GetGValue( _Couleur ) + (BYTE)Alea( -8, 8 ),
							GetBValue( _Couleur ) + (BYTE)Alea( -8, 8 ),
						)) ;

	Dc.SelectStockObject( NULL_PEN );
	CBrush	*	pOld	=	Dc.SelectObject( &Brosse ) ;
	Dc.Ellipse( x, y, x+_Largeur, y+_Hauteur ) ;
	Dc.SelectObject( pOld ) ;
	Brosse.DeleteObject() ;
	}

// Gros pinceau qui degouline
CGrosPinceau::CGrosPinceau()
	{
	_Couleur	=	CouleurHasard() ;
	_Hauteur	=	Alea( 5, 30 ) ;
	}

void	CGrosPinceau::PointDeLigneDroite( CDC & Dc, int x, int y )
	{
	_Hauteur	+=	Alea( -2, 2 ) ;
	if ( _Hauteur <= 1 )
		_Hauteur	=	1 ;

	for ( int i = 0; i < _Hauteur; i++)
		{
		const COLORREF Couleur	=	Dc.GetPixel( x, y + i ) ;
		const COLORREF Nouvelle	=	InterpoleCouleur( i, 0, _Hauteur, _Couleur , Couleur ) ;
		Dc.SetPixel( x, y + i, Nouvelle ) ;
		}

	const COLORREF Couleur	=	Dc.GetPixel( x, y + i ) ;
	const COLORREF Nouvelle	=	InterpoleCouleur( i, 0, _Hauteur, _Couleur, Couleur ) ;
	Dc.SetPixel( x, y + i, Nouvelle ) ;
	}


CHachures::CHachures()
	{
	_Couleur	=	CouleurHasard() ;
	_NbPoints	=	0 ;
	_pPts		=	0 ;
	}

CHachures::~CHachures()
	{
	HRGN	hRegion	=	CreatePolygonRgn( _pPts, _NbPoints, WINDING ) ;
	TraceDansRegion( hRegion ) ;
	DeleteObject( hRegion ) ;
	free( _pPts ) ;
	}

void	CHachures::Trace( CDC &, int x , int y, int, int )
	{
	// Ajouter le point
	if ( _pPts )
		_pPts	=	(POINT*)realloc( _pPts, sizeof (POINT ) * (_NbPoints + 4) ) ;
	else
		_pPts	=	(POINT*)malloc( sizeof( POINT ) * 4) ;

	_pPts[_NbPoints].x	=	x ;
	_pPts[_NbPoints].y	=	y ;
	_NbPoints ++ ;
	_pPts[_NbPoints].x	=	x ;
	_pPts[_NbPoints].y	=	y + 10;
	_NbPoints ++ ;
	_pPts[_NbPoints].x	=	x + 10 ;
	_pPts[_NbPoints].y	=	y + 10 ;
	_NbPoints ++ ;
	_pPts[_NbPoints].x	=	x + 10 ;
	_pPts[_NbPoints].y	=	y ;
	_NbPoints ++ ;
	}

void	CHachures::TraceDansRegion( HRGN hRegion)
	{
	if ( ! IsWindow( hMainWindow ))
		return ;

	CClientDC Dc( CWnd::FromHandle( hMainWindow )) ;

	CRect	R ;
	GetRgnBox( hRegion, R ) ;
	const int	EcartX	=	Alea( -10, 10 ) ;
	const int	Vide	=	Alea( 2, 4 ) ;
	CPen	Pen( PS_SOLID, 0, _Couleur ) ;
	CPen*	pOld	=	Dc.SelectObject( &Pen ) ;

	SelectClipRgn( Dc, hRegion ) ;

	for ( int i = R.left-EcartX; i < R.right+EcartX; i += Vide )
		{
		Dc.MoveTo( i, R.top ) ;
		Dc.LineTo( i + EcartX + Alea( -4, 4), R.bottom ) ;
		}

	for ( i = R.top - EcartX; i < R.bottom+EcartX; i += Vide )
		{
		Dc.MoveTo( R.left,	i ) ;
		Dc.LineTo( R.right,	i + EcartX + Alea( -4, 4) ) ;
		}

	Dc.SelectObject( pOld ) ;
	Pen.DeleteObject() ;
	SelectClipRgn( Dc, NULL ) ;
	}


CCrayonGris::CCrayonGris()
	{
	const int	Couleur	=	Alea( 0, 200) ;
	_Couleur	=	RGB( Couleur, Couleur, Couleur ) ;
	}