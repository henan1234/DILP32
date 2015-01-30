// TasDeSable.cpp: implementation of the CTasDeSable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <RegistrationKey.h>
#include "resource.h"

#include "TasDeSable.h"
#include "Configuration.h"

#define FastCreateDC()		CreateCompatibleDC( NULL )
#define FastStretchBlt( h, x, y, l, z, i, j, k, m, n )	StretchBlt( h, x, y, l, z, i, j ,k, m, n, SRCCOPY )


///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
#define DBL_EPSILON	2.2204460492503131e-013

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistrationKey	Key( TDS_PATH, TDS_HIDDEN ) ;
CTasDeSable			LEconomiseur ;

///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC			hDCMemo			=	0 ;
HBITMAP		hOldMemo ;

int			NbColonnes	;
double		*	pHauteurs ;
int			iDescente ;
BOOL		Descente ;
double		CoeffMontee		=	0.96;
double		CoeffDescente	=	0.96 ;
double		ValDescente		=	3.0 ;


// ==================================================================================================
// Retourne une bitmap qui contient l'image de l'ecran, eventuellement retaillee
// ==================================================================================================
HBITMAP MemoEcran( int Larg, int Haut )
{
	HDC	hDC ;
	HDC	hDCEcran ;
	HBITMAP	hBmpEcran ;
	HBITMAP	hOldEcran ;

	hDC			=	CreateDC( "display", 0, 0, 0 ) ;
	hDCEcran	=	FastCreateDC() ;

	hBmpEcran	=	CreateCompatibleBitmap( hDC, Larg, Haut  ) ;
    hOldEcran	=	(HBITMAP)SelectObject(	hDCEcran,	hBmpEcran ) ;

	FastStretchBlt(	hDCEcran, 0,0, Larg, Haut, 
					hDC, 0,0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) ) ;

	DeleteDC( hDC ) ;
	SelectObject( hDCEcran, hOldEcran ) ;
	DeleteDC( hDCEcran ) ;

	return hBmpEcran ;
}

///////////////////////////////////////////////////////////////////////////////
// ToutEnBas
//	Verifie que toutes les valeurs stockees correspondents ( a peu pres )
//	au bas de l'ecran
///////////////////////////////////////////////////////////////////////////////
BOOL CTasDeSable::ToutEnBas()
{
	int i ;

	for ( i = 0; i < Largeur; i++)
		if ( pHauteurs[i] < Hauteur )
			return FALSE ;

	for ( i = 0; i < Largeur; i++)
		pHauteurs[i]	=	Hauteur ;

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// ToutEnHaut
//	Verifie que toutes les valeurs stockees correspondents ( a peu pres )
//	au haut de l'ecran
///////////////////////////////////////////////////////////////////////////////
BOOL CTasDeSable::ToutEnHaut()
{
	int i ;

	for ( i = 0; i < Largeur; i++)
		if ( pHauteurs[i] >= 0 )
			return FALSE ;

	for ( i = 0; i < Largeur; i++)
		pHauteurs[i]	=	0 ;

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// Affiche une colonne
// ENTREES :	Device Context
//				No de la colonne
//				Hauteur de la colonne
///////////////////////////////////////////////////////////////////////////////
void	__inline CTasDeSable::Affiche( HDC hDC, int x, int y )
{
	FastStretchBlt( hDC, x * 1, y, 1, Hauteur-y, hDCMemo, x * 1 , 0, 1 , Hauteur ) ;
	PatBlt( hDC, x * 1 , 0, 1, y, BLACKNESS ) ;
}

void	CTasDeSable::DescentAGauche( HDC hDC, int Indice, double Val )
{
	int	 OldY, NewY ;
	if ( Indice < 0 )
		return ;


	if ( Val < DBL_EPSILON )
		return ; 

	OldY	=	(int)pHauteurs[Indice] ;
	pHauteurs[Indice] += Val ;
	NewY	=	(int)pHauteurs[Indice] ;
	if ( OldY != NewY)	
		Affiche( hDC, Indice, NewY ) ;

	if ( Indice > 0 )
		if( pHauteurs[Indice] > pHauteurs[Indice-1] )
			DescentAGauche( hDC, Indice - 1, Val * CoeffDescente ) ;
}

void	CTasDeSable::DescentADroite( HDC hDC, int Indice, double Val )
{
	int	 OldY, NewY ;
	if ( Indice >= NbColonnes )
		return ;

	if ( Val < DBL_EPSILON )
		return ; 

	OldY	=	(int)pHauteurs[Indice] ;
	pHauteurs[Indice] += Val ;
	NewY	=	(int)pHauteurs[Indice] ;
	if ( OldY != NewY)	
		Affiche( hDC, Indice, NewY ) ;

	if ( Indice < NbColonnes-1 )
		if( pHauteurs[Indice] > pHauteurs[Indice+1] )
			DescentADroite( hDC, Indice + 1, Val * CoeffDescente ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Descend
//	Descendre une colonne et le voisines si elles sont plus hautes
///////////////////////////////////////////////////////////////////////////////
void	CTasDeSable::Descend( HDC hDC, int Indice, double	Val )
{
	if ( pHauteurs[Indice] >= Hauteur )
		return ;

	if ( Val < DBL_EPSILON )
		return ; 

	pHauteurs[Indice] += Val ;
	Affiche( hDC, Indice, (int)pHauteurs[Indice] ) ;

	DescentADroite( hDC, Indice + 1, Val * CoeffDescente ) ;
	DescentAGauche( hDC, Indice - 1, Val * CoeffDescente ) ;
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
void	__inline CTasDeSable::MonteADroite( HDC hDC, int Indice, double Val )
{
	int	 OldY, NewY ;

	if ( Indice >= NbColonnes )
		return ;

	if ( Val < DBL_EPSILON )
		return ; 

	if ( pHauteurs[Indice] <= 0.0)
		return ;

	OldY	=	(int)pHauteurs[Indice] ;
	pHauteurs[Indice] -= Val ;
	NewY	=	(int)pHauteurs[Indice] ;
	if ( OldY != NewY)	
		Affiche( hDC, Indice, NewY ) ;
	
	if ( Indice < NbColonnes-1 )
		if( pHauteurs[Indice] < pHauteurs[Indice+1] )
		MonteADroite( hDC, Indice + 1, Val * CoeffMontee ) ;
}

void	__inline CTasDeSable::MonteAGauche( HDC hDC, int Indice, double  Val )
{
	int	 OldY, NewY ;
	if ( Indice < 0 )
		return ;

	if ( Val < DBL_EPSILON )
		return ; 

	if ( pHauteurs[Indice] <= 0.0)
		return ;

	OldY	=	(int)pHauteurs[Indice] ;
	pHauteurs[Indice] -= Val ;
	NewY	=	(int)pHauteurs[Indice] ;
	if ( OldY != NewY)	
		Affiche( hDC, Indice, NewY ) ;

	if ( Indice > 0 )
		if( pHauteurs[Indice] < pHauteurs[Indice-1] )
			MonteAGauche( hDC, Indice - 1, Val * CoeffMontee ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Montee
//	Remonte une colonne et le voisines si elles sont plus basses
///////////////////////////////////////////////////////////////////////////////
void	CTasDeSable::Monte( HDC hDC, int Indice, double Val )
{
	if ( pHauteurs[Indice] < 0.0)
		return ;
	
	pHauteurs[Indice] -= Val ;
	Affiche( hDC, Indice, (int)pHauteurs[Indice] ) ;

	MonteAGauche( hDC, Indice - 1, Val * CoeffMontee ) ;
	MonteADroite( hDC, Indice + 1, Val * CoeffMontee ) ;
}


CTasDeSable::CTasDeSable()
:CEconomiseur( "SandBox" )
{

}

CTasDeSable::~CTasDeSable()
{

}


void CTasDeSable::InitSave( HWND	hWnd )
	{
	CEconomiseur::InitSave( hWnd ) ;
	int	i ;

	if ( hDCMemo )
		return ;

	NoircirEcran=	FALSE ;
	hDCMemo		=	FastCreateDC() ;
	hOldMemo	=	(HBITMAP)SelectObject( hDCMemo, (HBITMAP)MemoEcran( Largeur, Hauteur )) ;
	NbColonnes	=	Largeur  ;

	// calloc initialise a 0
	pHauteurs	=	(double*)calloc( NbColonnes , sizeof( *pHauteurs )) ;
	for ( i = 0; i < NbColonnes; i++)
		pHauteurs[i] = 0 ;

	// Choix de la premiere colonne qui descent
	iDescente	=	Alea( 0, NbColonnes - 1 ) ;

	Descente	=	TRUE ;
	}


void CTasDeSable::Configuration( CPropertySheet * pPs )
	{
	pPs->AddPage( new CConfiguration ) ;

	CEconomiseur::Configuration( pPs ) ;

	CString Message ;
	Message.LoadString( IDS_TITRE_SETTINGS ) ;

	pPs->SetTitle( Message ) ;
	}

		// Animation
void CTasDeSable::Animation( CDC&	Dc ) 
	{
	Dc.SetStretchBltMode( COLORONCOLOR ) ;
	SetBrushOrgEx( Dc, 0, 0, NULL ) ;

		if ( Descente )
			{
			if ( pHauteurs[iDescente] >= Hauteur || UnSur( (Hauteur / (int)ValDescente) / 2 ) )
				{
				// Tout est en bas  ?
				if ( ToutEnBas() )
					{
					if ( UnSur(2))
						FastStretchBlt( hDCMemo, 0, 0, Largeur, Hauteur, hDCMemo, Largeur, 0, -Largeur, Hauteur ) ;
					else
						FastStretchBlt( hDCMemo, 0, 0, Largeur, Hauteur, hDCMemo, 0, Hauteur, Largeur, -Hauteur ) ;
					
					Descente = FALSE ;
					}
				else
					iDescente	=	Alea( 0, NbColonnes - 1 ) ;
				}

			Descend( Dc.m_hDC, iDescente, ValDescente ) ;
			}
		else
			{
			if ( pHauteurs[iDescente] <= 0 || UnSur( (Hauteur / (int)ValDescente) / 2 ))
				{
				// Tout est en haut ?
				if ( ToutEnHaut() )
					Descente = TRUE ;
				else
					iDescente	=	Alea( 0, NbColonnes - 1 ) ;
				}

			Monte( Dc.m_hDC, iDescente, ValDescente ) ;
			}
	}

void CTasDeSable::InitDC( CDC & )
	{
	}

void CTasDeSable::FinDC( CDC & )
	{
	if (! hDCMemo )
		return ;

	free( pHauteurs ) ;
		
	DeleteObject( SelectObject( hDCMemo, hOldMemo )) ;
	DeleteDC( hDCMemo ) ;		
	hDCMemo	=	0 ;
	}

void CTasDeSable::Preferences()
	{
	if ( ! Key.IsLocked() )
		{
		Preference( "Vitesse", ValDescente ) ;
		}
	}




