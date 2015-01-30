// Partie specifique de l'economiseur
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <math.h>
#include <stdlib.h>
#include "resource.h"

#include "..\specif.h"

const char	*	SPECIF_NomEconomiseur	=	"Baladeurs" ;
const char	*	SPECIF_ValeurEnregistre	=	"BALA-65-UR" ;
#define NB_MAX_POINTS	50

static POINT Pt[ NB_MAX_POINTS ] ;
COLORREF	Couleur[ NB_MAX_POINTS ] ;

int			NbPoints = 5 ;
// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
static __inline int Alea( int Min, int Max )
{
	return Min + rand() % ( Max - Min + 1 ) ;
}

void SPECIF_InitEconomiseur( HWND hWnd )
{
	int i ;
	
	SetTimer( hWnd, 1, 100, NULL ) ;
	
	for ( i = 0; i < NbPoints; i++ )
		{
		Pt[i].x		= GetSystemMetrics( SM_CXSCREEN ) / 2 ;	
		Pt[i].y		= GetSystemMetrics( SM_CYSCREEN ) / 2 ;	
		Couleur[i]	=	RGB( Alea( 0, 255 ), Alea( 0, 255 ), Alea( 0, 255 ) ) ;
		}
}

static __inline void	Bouge( POINT * pPt, LPRECT pR)
{
	pPt->x = Alea( pPt->x - 10, pPt->x + 10 ) ;
	pPt->y = Alea( pPt->y -10, pPt->y + 10 ) ;
		
	if ( pPt->x < pR->left )
		pPt->x = pR->right ;
	if ( pPt->x > pR->right )
		pPt->x = pR->left ;
			
	if ( pPt->y < pR->top )
		pPt->y = pR->bottom ;
			
	if ( pPt->y > pR->bottom )
		pPt->y = pR->top ;
}

DWORD _stdcall SPECIF_Animation( LPVOID lp )
{
	HBRUSH	hBrush, hOldBrush ;
	int		i ;
	HDC		hDC ;
	RECT	R ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	SetRect( &R, 0, 0, Largeur, Hauteur ) ;
	hDC		=	GetDC( hWndPrincipale ) ;

	SetEvent( hEventInitFini ) ;

   while ( ! Fini )
	for ( i = 0; i < NbPoints; i++ )
		{
		POINT	Points[5] ;
		int	NbPoints = Alea( 3, 5 ) ;
		int	j ;
			
		hBrush		=CreateSolidBrush( GetNearestColor(hDC, Couleur[i] )) ;
		hOldBrush	= SelectObject( hDC, hBrush ) ;
			
		for ( j = 0; j < NbPoints; j++ )
			{
			Points[j].x = Alea( Pt[i].x -20, Pt[i].x + 20 ) ;
			Points[j].y = Alea( Pt[i].y -20, Pt[i].y + 20 ) ;
			}
		//PatBlt( hDC, Pt[i].x, Pt[i].y, 1,1,PATCOPY ) ;
		Polygon( hDC, Points, NbPoints ) ;
			
		Couleur[i]	= RGB(	Alea(GetRValue( Couleur[i] ) - 1, GetRValue( Couleur[i] ) + 1),
									Alea(GetGValue( Couleur[i] ) - 1, GetGValue( Couleur[i] ) + 1),
									Alea(GetBValue( Couleur[i] ) - 1, GetBValue( Couleur[i] ) + 1)
									) ;
		Bouge( &Pt[i], &R ) ;
		SelectObject( hDC, hOldBrush ) ;
		DeleteObject( hBrush ) ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;
	return 0 ;
}

// ============================================================================
// SPECIF_Fin
// Fin de l'economiseur
// ============================================================================
void SPECIF_Fin( HWND hWnd )
{
}

			
// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	LitEntier( "NoircirEcran",  TRUE ) ;
	NbPoints		=	LitEntier( "Points", NbPoints ) ;
	
	if ( NbPoints < 1 || NbPoints >= NB_MAX_POINTS )
		NbPoints = 2 ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
	EcritEntier( "NoircirEcran", NoircirEcran ) ;
	EcritEntier( "Points", NbPoints) ;
}

// ============================================================================
// SPECIF_ValideParametres
// Valide les parametres saisis dans la boite de dialogue
// ============================================================================
BOOL	SPECIF_ValideParametres(  HWND hWnd )
{
	if ( NbPoints < 1 || NbPoints >= NB_MAX_POINTS )
		{
		char	Message[500] ;
		wsprintf( Message, "Veuillez saisir un nombre de points entre 1 et %d.", (int)NB_MAX_POINTS ) ;
		MessageBox( hWnd, Message, "Points de couleur", MB_OK | MB_ICONHAND ) ;
		return FALSE ;
		}
		
	return TRUE ;
}


// ============================================================================
// SPECIF_ConfInitDialog
// Initialiser la boite de configuration
// ============================================================================
BOOL SPECIF_PreprocessMessageConfig( HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam  )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			SPECIF_LirePreferences() ;
			CheckDlgButton( hDlg, IDC_NOIRCIR, NoircirEcran ) ;
			SetDlgItemInt( hDlg, IDC_NB_POINTS, NbPoints, FALSE ) ;
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS, UDM_SETBUDDY, (WPARAM)GetDlgItem( hDlg,IDC_NB_POINTS ), 0) ;
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS, UDM_SETRANGE, 0, MAKELPARAM( NB_MAX_POINTS, 1)) ;
			break ;

		case WM_COMMAND :
		switch( wParam )
			{
			case IDOK :
				{
				BOOL	Translated ;

				NoircirEcran	= IsDlgButtonChecked( hDlg, IDC_NOIRCIR ) ;
				NbPoints		= GetDlgItemInt( hDlg, IDC_NB_POINTS, &Translated, FALSE ) ;
			
				if ( SPECIF_ValideParametres(hDlg))
					{
					SPECIF_EcrirePreferences() ;
					EndDialog( hDlg, TRUE ) ;
					}
				}
				return TRUE ;
			
			default :
				return FALSE ;
			}
			break ;

		default :
			return FALSE ;
		}
	return TRUE ;

}

void SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
}
