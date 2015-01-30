// Partie specifique de l'economiseur
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "resource.h"
#include "..\specif.h"

// ================================================================= Constantes
#define NB_NUANCES		16
#define NB_NUANCES_SPOT	256
#define CENTRE				Largeur/2, Hauteur/2
#define NB_MAX_SPOTS	200
#define DEG_RAD(x)		((x) * 3.14 * 2.0  / 360.0)
#define INCREMENT		1

// ====================================================================== Types
typedef	struct
			{
			double	Position ;
			double	Rayon ;
			int		Nuance ;
			int		Taille ;
			}
			SPOT ;             
			
const	char	*	SPECIF_NomEconomiseur	=	"Radar" ;
const	char	*	SPECIF_ValeurEnregistre	=	"37-2" ;

			
int	Rayon ;
int	NbSpots ;
int	Position ;
SPOT	Spot[ NB_MAX_SPOTS ] ;
int	CompR, CompG, CompB ;

// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
static __inline int Alea( int Min, int Max )
{
	return Min + rand() % ( Max - Min + 1 ) ;
}

// ==================================================================================================
// UnSur
// Retourne une VRAI un coup sur...
// ==================================================================================================
static __inline BOOL UnSur( int x )
{
	return (rand() % x) == 0 ;
}


// ==================================================================================================
COLORREF	Couleur( int Nuance )
// ==================================================================================================
{
	int	Valeur = 128 * Nuance / NB_NUANCES ;
	return RGB( CompR * Valeur, CompG * Valeur, CompB * Valeur ) ;
}

// ==================================================================================================
int	CoordX( int Position )
// ==================================================================================================
{
	return Largeur/2 + (int)((double)Rayon * sin( DEG_RAD( Position ))) ;
}

// ==================================================================================================
int	CoordY( int Position )
// ==================================================================================================
{
	return Hauteur/2 + (int)((double)Rayon * cos( DEG_RAD( Position ))) ;
}



// ==================================================================================================
void AfficheRayon( HDC hDC, int Position, int Nuance )
// Affiche une des nuances du radar
// ==================================================================================================
{
	HPEN hBrush, hOldBrsh;
	POINT	Pt[3] ;
	
	hBrush = CreateSolidBrush( Couleur( Nuance )) ;
	hOldBrsh = SelectBrush( hDC, hBrush) ;
	
	Pt[0].x =	Largeur / 2 ;
	Pt[0].y =	Hauteur / 2 ;
	Pt[1].x =	CoordX( Position ) ;
	Pt[1].y =	CoordY( Position ) ;
	Pt[2].x =	CoordX( Position + INCREMENT ) ;
	Pt[2].y =	CoordY( Position + INCREMENT ) ;
	
	Polygon( hDC, Pt, sizeof( Pt ) / sizeof( Pt[0] )) ;
	
	SelectBrush( hDC, hOldBrsh ) ;
	DeletePen( hBrush ) ;
}

// ==================================================================================================
void NouveauSpot( void )
// ==================================================================================================
{
	Spot[NbSpots].Position 	= Position ;
	Spot[NbSpots].Rayon	  	= Alea( 10, Rayon-10 ) ;
	Spot[NbSpots].Nuance	= Alea( NB_NUANCES_SPOT/2, NB_NUANCES_SPOT ) ;
	Spot[NbSpots].Taille	= Alea( 1, 8 ) ;
	
	NbSpots ++ ;
}

// ==================================================================================================
COLORREF	CouleurSpot( int Nuance )
// ==================================================================================================
{
	int	Valeur = 256 * Nuance / NB_NUANCES_SPOT ;
	return RGB( CompR * Valeur, CompG * Valeur, CompB * Valeur ) ;
}

// ==================================================================================================
void  AfficheSpot( HDC hDC, SPOT Spot )
// ==================================================================================================
{
	HBRUSH hBrush, hOldBrush ;
	int	x, y ;
	
	x = Largeur / 2 + (int)((double)Spot.Rayon * sin( DEG_RAD( Spot.Position ))) ;
	y = Hauteur / 2 + (int)((double)Spot.Rayon * cos( DEG_RAD( Spot.Position ))) ;
	
	hBrush		=	CreateSolidBrush( CouleurSpot( Spot.Nuance )) ;
	hOldBrush	=	SelectBrush( hDC, hBrush ) ;
		
	Ellipse( hDC, x-Spot.Taille, y-Spot.Taille, x+Spot.Taille, y+Spot.Taille ) ;
		
	SelectObject( hDC, hOldBrush ) ;
	DeleteObject( hBrush ) ;
}

// ==================================================================================================
void ChangeComposantes( void )
// ==================================================================================================
{
	CompR = Alea( 0,1 ) ;
	CompG = Alea( 0,1 ) ;
	CompB = Alea( 0,1 ) ;
	
	if ( !CompR && !CompG && !CompB )
		CompG = 1 ;
}

// ==================================================================================================
// ==================================================================================================
void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	// Pour l'animation
	NoircirEcran = TRUE ;

	Rayon	= min( Largeur, Hauteur )/2 ;
	
	NbSpots = 0 ;
	Position = 0 ;
	
	CompR = 0 ;
	CompG = 1 ;
	CompB	= 0 ;
}  

// ============================================================================
// ============================================================================
DWORD __stdcall SPECIF_Animation( LPVOID  lp )
//void SPECIF_Animation( HDC hDC, UINT NoTimer, LPRECT lpR )
// ============================================================================
// ============================================================================
{
	int i ;
	static	BOOL	CouleurChangee = FALSE ;
	
	HDC	hDC ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	SetEvent( hEventInitFini ) ;

	hDC	=	GetDC( hWndPrincipale ) ;
	while ( ! Fini )
		{
		if ( UnSur( 500 ))
			{
			if ( ! CouleurChangee )
				{
				ChangeComposantes() ;
				CouleurChangee = TRUE ;
				}
			}
		else
			CouleurChangee = FALSE ;
			
		SelectObject( hDC, GetStockObject( NULL_PEN )) ;
		
		// Balayage
		for ( i = 0; i < NB_NUANCES; i++)
			AfficheRayon( hDC, Position + (i*INCREMENT), i ) ;
			
		// Spots
		if ( NbSpots < NB_MAX_SPOTS )
			if ( UnSur( 10 ))
				NouveauSpot() ;
				
		Position += INCREMENT  ;
		if ( Position > 360)
			Position = 0 ;
			
		for ( i = 0; i < NbSpots; i++)
			{                   
			AfficheSpot( hDC, Spot[i] ) ;
			Spot[i].Nuance -- ;
			}
			
		i = 0 ;
		
		while ( i < NbSpots )
			if ( Spot[i].Nuance > -1)
				i ++ ;
			else
				{
				memmove( &Spot[i], &Spot[i+1], sizeof( SPOT )* ( NbSpots-i)) ;
				NbSpots -- ;
				}
		}
	
	SPECIF_Fin( hWndPrincipale ) ;
	ReleaseDC( hWndPrincipale, hDC) ;

	SetEvent( hEventFini ) ;
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
	NoircirEcran	=	TRUE ;
//	HautePriorite	=	LitEntier( "Haute Priorite", HautePriorite ) ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
//	EcritEntier( "Haute Priorite", HautePriorite ) ;
}

// ============================================================================
// SPECIF_ConfInitDialog
// Initialiser la boite de configuration
// ============================================================================
BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, UINT	Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			SPECIF_LirePreferences() ;
//			CheckDlgButton( hDlg, IDC_PRIORITE, HautePriorite ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
//					HautePriorite	= IsDlgButtonChecked( hDlg, IDC_PRIORITE ) ;
			
					SPECIF_EcrirePreferences() ;
					EndDialog( hDlg, TRUE ) ;
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

// ============================================================================
void	SPECIF_PeintFenetre( HDC hDC , LPRECT lpR )
{
}
