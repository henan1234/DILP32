///////////////////////////////////////////////////////////////////////////////
// CEcoOrbite
///////////////////////////////////////////////////////////////////////////////
#include "..\Economiseur Generique\stdafx.h"
#include <math.h>
#include "..\Economiseur Generique\animate.h"
#include "..\Economiseur Generique\RectAffichage.h"
#include "Orbites.h"
#include "resource.h"

#define PI	3.14159

CEcoOrbite	CeciEstMonEconomiseur ;

CEcoOrbite::CEcoOrbite()
:CEconomiseur( "Orbites", "qmsrogh" )
	{
	_NbPoints	=	5 ;
	_pIntermediaire	=	0 ;
	_pDIB		=	0 ;
	_pPalette	=	0 ;
	_Step		=	1.2 ;
	_RapportVitesse		=	1.5 ;
	_RapportLongueur	=	0.5 ;
	}


CEcoOrbite::~CEcoOrbite()
	{
	delete _pIntermediaire ;
	delete _pDIB ;
	delete _pPalette ;
	}

void CEcoOrbite::InitSave( HWND	hWnd )
	{
	CEconomiseur::InitSave( hWnd );

	for ( int i =0; i < _NbPoints; i++)
		_Angles[i]	=	0 ;

	_Affichage.Espace( CRect(1,1,Largeur-2, Hauteur-2)) ;

	_pDIB	=	new	CDIB ;
	_pDIB->Load( IDR_DIB1 ) ;

	_pPalette	=	new	CDIBPal ;
	_pPalette->Create( _pDIB ) ;
	hPalette	=	(HPALETTE)_pPalette->m_hObject ;

	_pIntermediaire		=	new	CDIBSurface ;
	_pIntermediaire->Create( Largeur, Hauteur, _pPalette ) ;
	_pIntermediaire->GetDC()->PatBlt( 0, 0, Largeur, Hauteur, BLACKNESS ) ;

	::SetTimer( hWnd, 1, 50, NULL ) ;
}
		
void CEcoOrbite::InitConfig( HWND hWnd )
	{
	}


CPoint	CEcoOrbite::CalculePos( CPoint Reference, double Angle, int Rayon ) const
	{
	const double	x	=	(double)Reference.x	+ sin( Angle * PI / 360 ) * Rayon ;
	const double	y	=	(double)Reference.y + cos( Angle * PI / 360 ) * Rayon ;
	
	return CPoint( (int)x, (int)y ) ;
	}

void	CEcoOrbite::Affiche( CPoint Pt1, CPoint Pt2 )
	{
	HDC	hDC		=	_pIntermediaire->GetHDC() ;

	CRect	R( (Pt1.x*2)-Pt2.x, (Pt1.y*2)-Pt2.x, Pt2.x, Pt2.y ) ;
	
	_pIntermediaire->GetDC()->Ellipse( R ) ;

	R.NormalizeRect() ;
	R.InflateRect( 1, 1 ) ;
	_Affichage.LimiteRect( R ) ;
	_Affichage.Ajoute( R ) ;
	}

void	CEcoOrbite::Affiche( CPoint Pt )
	{
	const int	LargeurBoule	=	_pDIB->GetWidth() ;
	const int	HauteurBoule	=	_pDIB->GetHeight() ;

	CRect	R;
	
	R.left	=	Pt.x - LargeurBoule	/ 2 ;
	R.top	=	Pt.y - HauteurBoule / 2 ;
	R.right	=	R.left + LargeurBoule ;
	R.bottom=	R.top  + HauteurBoule ;

	int	DecX, DecY ;
	_Affichage.LimiteRect( R, &DecX, &DecY ) ;

	if ( ! R.IsRectEmpty())
		{
		_pDIB->CopyBits( _pIntermediaire, R.left, R.top, R.Width(), R.Height(),
					     DecX, DecY,
						 PALETTEINDEX(100)) ;
		_Affichage.Ajoute( R ) ;
		}
	}

void CEcoOrbite::Animation( CDC&	Dc, BOOL	PremiereFois )
	{
	_Affichage.PatBlt( _pIntermediaire->GetHDC(), BLACKNESS ) ;
	CRectAffichage	Intermediaire( _Affichage ) ;
	_Affichage.Vide() ;
	
	int		LargeurDisponible	=	min( Largeur, Hauteur) / 3 ;
	CPoint	Reference( Largeur/2, Hauteur/2 ) ;
	double	Step	=	_Step ;

	_pIntermediaire->GetDC()->SelectStockObject( WHITE_PEN ) ;
	_pIntermediaire->GetDC()->SelectStockObject( NULL_BRUSH ) ;
	
	for ( int i = 0; i < _NbPoints; i++)
		{
		const CPoint pt =	CalculePos( Reference, _Angles[i], LargeurDisponible ) ;
		Affiche( Reference, pt ) ;
		Affiche( pt ) ;
		_Angles[i] +=	Step ;
		Reference	=	pt ;
		LargeurDisponible	=	(int)((double)LargeurDisponible*_RapportLongueur) ;
		Step	*=	_RapportVitesse ;
		}

	Intermediaire	+=	_Affichage ;
	Intermediaire.BitBlt( Dc, *(_pIntermediaire->GetDC()) ) ;
	}


BOOL CEcoOrbite::PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
	{
	return FALSE ;
	}

void CEcoOrbite::Preferences()
	{
	Preference( "Nb Points", _NbPoints ) ;
	_NbPoints =	min( NB_MAX_POINTS, max( 2, _NbPoints )) ;
	Preference( "Step", _Step ) ;
	Preference( "Rapport vitesse", _RapportVitesse ) ;
	Preference( "Rapport longueur", _RapportLongueur ) ;
	}

