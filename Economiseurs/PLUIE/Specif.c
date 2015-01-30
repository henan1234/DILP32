// Partie specifique de l'economiseur
#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <commctrl.h>
#include "resource.h"
#include "..\specif.h"

// ================================================================= Constantes
#define NB_MAX_POINTS	3000
#define NB_MAX_COULEURS	16
#define NB_MAX_ROND		8
#define NB_ECLAIR			9				// Doit etre impair
#define COULEUR_ECLAIR	RGB( 255,255,0)

// ====================================================================== Types
typedef struct	
	{
	int	x ;
	int	y ;
	int	Niveau ;
	}
	GOUTTE ;
	
typedef struct
	{
	int	x ;
	int	y ;
	int	Niveau ;
	int	Rayon ;
	}
	ROND ;

const	char	*	SPECIF_NomEconomiseur	=	"Pluie" ;
const	char	*	SPECIF_ValeurEnregistre	=	"Diluvienne" ;

// ================================================================= Variables
static int		NbPoints	= NB_MAX_POINTS ;
static int		NbNiveaux	= NB_MAX_COULEURS ;
static int		NbRond		= 0 ;
static GOUTTE	Gouttes[NB_MAX_POINTS] ;
static ROND		Rond[ NB_MAX_ROND ] ;
static POINT	Eclair[NB_ECLAIR] ;
static BOOL		YaEclair = FALSE ;

static		COLORREF	Couleurs[NB_MAX_COULEURS] =
				{
				RGB(255,255,255),
				RGB(  0,255,255),
				RGB(192,192,192),
				RGB(  0,192,192),
				RGB(160,160,160),
				RGB(  0,160,160),
				RGB(128,128,128),
				RGB(  0,128,128),
				RGB(112,112,112),
				RGB(  0,112,112),
				RGB( 96, 96, 96),
				RGB(  0, 96, 96),
				RGB( 64, 64, 64),
				RGB(  0, 64, 64),
				RGB( 32, 32, 32),
				RGB(  0, 32, 32)
				}  ;
				
HBRUSH		hBrush[ NB_MAX_COULEURS ] ;
HBRUSH		hBrushEclair ;

// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
static __inline int Alea( int Min, int Max )
{
	return Min + rand() % ( Max - Min + 1 ) ;
}

static __inline HBRUSH Couleur( int Niveau )
{
	return hBrush[NbNiveaux - Niveau-1] ;
}

void SPECIF_InitEconomiseur( HWND hWnd )
{
	int i ;
	
	SPECIF_LirePreferences() ;

	for ( i = 0; i < NbPoints; i++ )
		{
		Gouttes[i].x	=	Alea( 0, Largeur) ;
		Gouttes[i].y	=	Alea( 0, Hauteur) ;
		Gouttes[i].Niveau = Alea( 0, NbNiveaux-1 ) ;
		}	
		
	NbRond = 0 ;
		
	NoircirEcran = TRUE ;

	for ( i = 0; i < NB_MAX_COULEURS; i++)
		hBrush[i] = CreateSolidBrush( Couleurs[i]) ;
		
	hBrushEclair = CreateSolidBrush( COULEUR_ECLAIR ) ;
}  


static void CalculEclair( void )
{
	int 	i, j ;
	int	IntervalleY	=	Hauteur / ( NB_ECLAIR / 2 ) ;
	
	for ( i = 0; i < (NB_ECLAIR/2)+1; i++)
		{
		Eclair[i].x = Alea( 0, Largeur) ;
		Eclair[i].y = i * Alea( IntervalleY * 3 / 4, IntervalleY ) ;
		}
		
	for ( i = (NB_ECLAIR/2) + 1; i < NB_ECLAIR; i++ )
		{
		j = ( NB_ECLAIR - i - 1 ) ;
		Eclair[i].x = Eclair[j].x + Alea( i * 10, i * 20 ) ;
		Eclair[i].y = Eclair[j].y ; 
		}
}

static void GenereRond( GOUTTE * pGoutte )
{
	if ( NbRond < NB_MAX_ROND -1 )
		{
		Rond[NbRond].x			= pGoutte->x ;
		Rond[NbRond].y			= pGoutte->y - pGoutte->Niveau + 1 ;
		Rond[NbRond].Rayon	= 0 ;
		Rond[NbRond].Niveau  = pGoutte->Niveau ;
		
		NbRond ++ ;
		}
}

static __inline void	Bouge( GOUTTE * pGoutte )
{
	pGoutte->y += pGoutte->Niveau + 1 ;
	
	if ( pGoutte->y > Hauteur - ( (NbNiveaux - pGoutte->Niveau) * 14 ))
		{
		GenereRond( pGoutte ) ;
		pGoutte->x	=	Alea( 0, Largeur) ;
		pGoutte->y	=	0 ;
		pGoutte->Niveau = Alea( 0, NbNiveaux-1 ) ;
		}
}


// ============================================================================
DWORD _stdcall SPECIF_Animation( LPVOID lp )
// ============================================================================
{
	int		i, j ;
	HBRUSH	hOldBrush ;
	HPEN	hPen, hOldPen ;
	int		FrequenceEclair ;
	HDC		hDC ;

   SPECIF_InitEconomiseur( hWndPrincipale ) ;
   hDC	=	GetDC( hWndPrincipale ) ;

   SetEvent( hEventInitFini ) ;

   while ( ! Fini )
	   {   
   		FrequenceEclair = 300 ;

		if ( Alea(0,FrequenceEclair ) == 0 )
   			{
   			CalculEclair() ;
   			
   			hOldBrush	= SelectBrush( hDC, hBrushEclair ) ;
   			Polygon( hDC, Eclair, NB_ECLAIR ) ;
   			SelectBrush ( hDC,hOldBrush) ;
	   			
   			YaEclair = TRUE ;
	   			
   			if ( Alea( 1, 5 ) == 1 )
   				{
   				PatBlt( hDC, 0, 0, Largeur, Hauteur, DSTINVERT ) ;
   				PatBlt( hDC, 0, 0, Largeur, Hauteur, DSTINVERT ) ;
   				}
   			}
   
	   for ( j = 0; j < NbNiveaux; j++ )
			{
			hOldBrush	=	SelectBrush( hDC, Couleur( j ) ) ;
			
			for ( i = 0; i < NbPoints; i++ )
				if ( j == Gouttes[i].Niveau )
					{
					PatBlt( hDC, Gouttes[i].x, Gouttes[i].y, 2,Gouttes[i].Niveau + 1,  BLACKNESS ) ;
					Bouge( & Gouttes[i] ) ;
					PatBlt( hDC, Gouttes[i].x, Gouttes[i].y, 2,Gouttes[i].Niveau + 1,  PATCOPY ) ;
					}
				
			SelectBrush( hDC, hOldBrush ) ;
			}
		SelectBrush( hDC, GetStockObject( NULL_BRUSH )) ;
			
		for ( i = 0; i < NbRond; i++ )
			{
			hOldPen = SelectPen( hDC, GetStockObject( BLACK_PEN )) ;
			Ellipse( hDC, Rond[i].x - Rond[i].Rayon * 3, Rond[i].y - Rond[i].Rayon,
					 Rond[i].x + Rond[i].Rayon * 3, Rond[i].y + Rond[i].Rayon )  ;
				
			if ( Rond[i].Rayon > Rond[i].Niveau * 2 )
				{
				memmove( &Rond[i], &Rond[i+1], sizeof( ROND ) * ( NbRond - i )) ;
				NbRond -- ;
				i++ ;
				}
			else
				{	
				Rond[i].Rayon ++  ;
					
				hPen	=	CreatePen( PS_SOLID, 0, Couleurs[ NbNiveaux-Rond[i].Niveau ]) ;
				SelectPen( hDC, hPen ) ;
				Ellipse( hDC, Rond[i].x - Rond[i].Rayon * 3, Rond[i].y - Rond[i].Rayon,
								 Rond[i].x + Rond[i].Rayon * 3, Rond[i].y + Rond[i].Rayon )  ;
					
				SelectPen( hDC, hOldPen ) ;
				DeletePen( hPen ) ;
				}
			}
   
		if ( YaEclair )
			{
			SelectObject( hDC, GetStockObject( BLACK_BRUSH )) ;
			Polygon( hDC, Eclair, NB_ECLAIR ) ;
			YaEclair = FALSE ;
			}
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
   int i ;
   
   for ( i = 0; i < NB_MAX_COULEURS; i++)
   	DeleteObject( hBrush[i] ) ;
   	
   DeleteObject( hBrushEclair ) ;
}

			
// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	TRUE ;
	NbPoints		=	LitEntier( "Nombre de points", 800 ) ;
	
	if ( NbPoints < 1 || NbPoints >= NB_MAX_POINTS )
		NbPoints = 2 ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
	EcritEntier( "Nombre de points", NbPoints ) ;
}

// ============================================================================
// SPECIF_ValideParametres
// Valide les parametres saisis dans la boite de dialogue
// ============================================================================
BOOL	SPECIF_ValideParametres(  HWND hWnd )
{
	if ( NbPoints < 1 || NbPoints > NB_MAX_POINTS )
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
BOOL SPECIF_PreprocessMessageConfig( HWND hDlg, UINT	Message, WPARAM 	wParam, LPARAM lParam )
{
	BOOL Translated ;
	switch( Message )
		{
		case WM_INITDIALOG :
			SPECIF_LirePreferences() ;
			CheckDlgButton( hDlg, IDC_NOIR, NoircirEcran ) ;
			SetDlgItemInt( hDlg, IDC_NB_POINTS, NbPoints, FALSE ) ;
	
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS, UDM_SETBUDDY, (WPARAM)GetDlgItem( hDlg,IDC_NB_POINTS ), 0) ;
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS, UDM_SETRANGE, 0, MAKELPARAM( NB_MAX_POINTS, 1)) ;
			break ;
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					NoircirEcran	= IsDlgButtonChecked( hDlg, IDC_NOIR ) ;
					NbPoints			= GetDlgItemInt( hDlg, IDC_NB_POINTS, &Translated, FALSE ) ;
					
					if ( SPECIF_ValideParametres(hDlg))
						{
						SPECIF_EcrirePreferences() ;
						EndDialog( hDlg, TRUE ) ;
						}
					return TRUE ;
			
				default :
					return FALSE ;
				}
			
		default :
			return FALSE ;
		}

	return TRUE ;
}

void SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
}
