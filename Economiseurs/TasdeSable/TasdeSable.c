///////////////////////////////////////////////////////////////////////////////
// TASDESABLE.C
// Simule l'ecoulement d'un tas de sable dont les grains sont representes par
// les pixels de l'ecran
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <commctrl.h>
#include <math.h>
#include "resource.h"
#include "..\specif.h"

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
#define DBL_EPSILON	2.2204460492503131e-013

const	char *	SPECIF_NomEconomiseur	=	"Tas de sable" ;
const	char *	SPECIF_ValeurEnregistre =	"1573--3°0" ;

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



///////////////////////////////////////////////////////////////////////////////
// ToutEnBas
//	Verifie que toutes les valeurs stockees correspondents ( a peu pres )
//	au bas de l'ecran
///////////////////////////////////////////////////////////////////////////////
BOOL ToutEnBas()
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
BOOL ToutEnHaut()
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
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_InitEconomiseur( HWND hWnd )
{
	int	i ;

	if ( hDCMemo )
		return ;

	NoircirEcran=	FALSE ;
	hDCMemo		=	FastCreateDC() ;
	hOldMemo	=	SelectObject( hDCMemo, MemoEcran( Largeur, Hauteur )) ;
	NbColonnes	=	Largeur  ;

	// calloc initialise a 0
	pHauteurs	=	calloc( NbColonnes , sizeof( *pHauteurs )) ;
	for ( i = 0; i < NbColonnes; i++)
		pHauteurs[i] = 0 ;

	// Choix de la premiere colonne qui descent
	iDescente	=	Alea( 0, NbColonnes - 1 ) ;

	Descente	=	TRUE ;

}

///////////////////////////////////////////////////////////////////////////////
// Affiche une colonne
// ENTREES :	Device Context
//				No de la colonne
//				Hauteur de la colonne
///////////////////////////////////////////////////////////////////////////////
void	__inline Affiche( HDC hDC, int x, int y )
{
	FastStretchBlt( hDC, x * 1, y, 1, Hauteur-y, hDCMemo, x * 1 , 0, 1 , Hauteur ) ;
	PatBlt( hDC, x * 1 , 0, 1, y, BLACKNESS ) ;
}

void	DescentAGauche( HDC hDC, int Indice, double Val )
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

void	DescentADroite( HDC hDC, int Indice, double Val )
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
void	Descend( HDC hDC, int Indice, double	Val )
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
void	__inline MonteADroite( HDC hDC, int Indice, double Val )
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

void	__inline MonteAGauche( HDC hDC, int Indice, double  Val )
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
void	Monte( HDC hDC, int Indice, double Val )
{
	if ( pHauteurs[Indice] <= 0.0)
		return ;
	
	pHauteurs[Indice] -= Val ;
	Affiche( hDC, Indice, (int)pHauteurs[Indice] ) ;

	MonteAGauche( hDC, Indice - 1, Val * CoeffMontee ) ;
	MonteADroite( hDC, Indice + 1, Val * CoeffMontee ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Animation
// Cette fonction fonctionne comme un thread.
// Ne pas oublier de dresser l'event hEventFini des que l'initialisation est
// faite
///////////////////////////////////////////////////////////////////////////////
DWORD	_stdcall SPECIF_Animation( LPVOID p  )
{
	HDC		hDC ;
	RECT	R ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;

	hDC	=	GetDC( hWndPrincipale ) ;
	if ( hPalette )
		{
		SelectPalette( hDC, hPalette, FALSE ) ;
		RealizePalette( hDC ) ;
		}

	GetClientRect( hWndPrincipale, &R ) ;
	SPECIF_PeintFenetre( hDC, &R ) ;

	SetStretchBltMode( hDC, STRETCH_HALFTONE ) ;
	SetBrushOrgEx( hDC, 0, 0, NULL ) ;

	SetEvent( hEventInitFini ) ;

	while (! Fini )
		{
		if ( Descente )
			{
			if ( pHauteurs[iDescente] >= Hauteur || UnSur( (Hauteur / (int)ValDescente) / 4 ) )
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

			Descend( hDC, iDescente, ValDescente ) ;
			}
		else
			{
			if ( pHauteurs[iDescente] <= 0 || UnSur( (Hauteur / (int)ValDescente) / 4 ))
				{
				// Tout est en haut ?
				if ( ToutEnHaut() )
					Descente = TRUE ;
				else
					iDescente	=	Alea( 0, NbColonnes - 1 ) ;
				}

			Monte( hDC, iDescente, ValDescente ) ;
			}
		}

		ReleaseDC( hWndPrincipale, hDC ) ;
		SPECIF_Fin(hWndPrincipale) ;

		return FALSE ;
}

///////////////////////////////////////////////////////////////////////////////
//	Fin de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_Fin( HWND hWnd )
{
	if (! hDCMemo )
		return ;

	free( pHauteurs ) ;
		
	DeleteObject( SelectObject( hDCMemo, hOldMemo )) ;
	DeleteDC( hDCMemo ) ;		
	hDCMemo	=	0 ;
}
 
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	int i ;

	for ( i = 0; i < NbColonnes; i++)
		Affiche( hDC, i, (int)pHauteurs[i] ) ;
}

void	SPECIF_LirePreferences(void)
{
	NoircirEcran	=	FALSE ;
	CoeffMontee		=	LitDouble( "CoeffMontee", CoeffMontee ) ;
	CoeffDescente	=	LitDouble( "CoeffDescente", CoeffDescente ) ;
	ValDescente		=	LitDouble( "Vitesse", ValDescente ) ;
}

void	SPECIF_EcrirePreferences(void)
{
	EcritDouble( "CoeffDescente", CoeffDescente ) ;
	EcritDouble( "CoeffMontee",	CoeffMontee ) ;
	EcritDouble( "Vitesse",	ValDescente) ;
}

BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam , LPARAM lParam )
{ 
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			SPECIF_LirePreferences() ;
			SendDlgItemMessage( hDlg, IDC_MONTEE, TBM_SETRANGE, TRUE, MAKELPARAM( 400, 990 )) ;
			SendDlgItemMessage( hDlg, IDC_MONTEE, TBM_SETPOS, TRUE, (LPARAM)(int)(CoeffMontee * 1000 ) ) ;
			
			SendDlgItemMessage( hDlg, IDC_DESCENTE, TBM_SETRANGE, TRUE, MAKELPARAM( 400, 990 )) ;
			SendDlgItemMessage( hDlg, IDC_DESCENTE, TBM_SETPOS, TRUE, (LPARAM)(int)(CoeffDescente * 1000) ) ;

			SendDlgItemMessage( hDlg, IDC_VITESSE, TBM_SETRANGE, TRUE, MAKELPARAM( 10, 100 )) ;
			SendDlgItemMessage( hDlg, IDC_VITESSE, TBM_SETPOS, TRUE, (LPARAM)(int)(ValDescente * 10) ) ;
			return FALSE ; 	// Pour centrer la fenetre
			}
			break ;
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					CoeffMontee	=	(double)SendDlgItemMessage( hDlg, IDC_MONTEE, TBM_GETPOS, 0, 0 ) / 1000.0 ;
					CoeffDescente=	(double)SendDlgItemMessage( hDlg, IDC_DESCENTE, TBM_GETPOS, 0, 0 ) / 1000.0 ;
					ValDescente =	(double)SendDlgItemMessage( hDlg, IDC_VITESSE, TBM_GETPOS, 0, 0 ) / 10.0 ;

					SPECIF_EcrirePreferences() ;
					EndDialog( hDlg, IDOK ) ;
					break ;

				default :
					return FALSE ;
				}
			break ;

		default :
			return FALSE ;
		}
	return TRUE ;
}
