#include <windows.h>
#include <commctrl.h>
#include "..\specif.h"
#include "glouglou.h"

///////////////////////////////////////////////////////////////////////////////
//	VARIABLES GLOBALES
///////////////////////////////////////////////////////////////////////////////
const char *	SPECIF_ValeurEnregistre	=	"Gloug/15/15" ;
const char *	SPECIF_NomEconomiseur	=	"Economiseur mouillé" ;


BOOL		Montee ;
int			Niveau ;
BOOL		NoircirEcran ;
BOOL		HautePriorite ;
int			NoBitmap ;

HDC			hDCEcran ;
HBITMAP		hBmpEcran ;
HBITMAP		hOldEcran ;

COLORREF	CouleurLiquide ;
int			FrequenceTimer = 0 ;

void	AfficheBitmapTransparent( HDC	hDC, int xD, int yD, int l, int h, HBITMAP hBitmap, int xS, int yS )
	{
	HDC	hDCBitmap ;
	HBITMAP	hOldBm ;

	// La partie noire de la bitmap : transparente
	// La partie blanche de la bitmap : change la teinte de la destination
	SetBkColor( hDC, CouleurLiquide ) ;
	SetTextColor( hDC, RGB(255,255,255)) ;

	hDCBitmap	=	FastCreateDC(  ) ;
	hOldBm		=	SelectObject( hDCBitmap, hBitmap ) ;

	BitBlt( hDC, xD, yD, l, h,hDCBitmap, xS, yS, SRCAND ) ;

	SelectObject( hDCBitmap, hOldBm ) ;
	DeleteDC( hDCBitmap ) ;
	}

void	SPECIF_LirePreferences()
{
	NbMaxBulles	=	LitEntier( "NbMaxBulles", 10 ) ;
	NbMaxGouttes =	LitEntier( "NbMaxGouttes", 10) ;
	FrequenceTimer	=	LitEntier( "FrequenceTimer", 10 ) ;

	if ( NbMaxBulles < 0 )
		NbMaxBulles	=	0 ;

	if ( NbMaxBulles >= NB_MAX_BULLES )
		NbMaxBulles	=	NB_MAX_BULLES ;
}

void	SPECIF_EcrirePreferences()
{
	EcritEntier( "NbMaxBulles", NbMaxBulles ) ;
	EcritEntier( "NbMaxGouttes", NbMaxGouttes ) ;
	EcritEntier( "FrequenceTimer", FrequenceTimer );
}

///////////////////////////////////////////////////////////////////////////////
// NouveauLiquide
//	Choix d'un nouveau liquide colore
///////////////////////////////////////////////////////////////////////////////
static void NouveauLiquide( void )
{
	COLORREF	Couleur	=	RGB( 	Alea( 32, 255 ),
									Alea( 32, 255 ),
									Alea( 32, 255 )) ;

	HDC	hDC	=	CreateDC( "display", 0, 0, 0 ) ;
	CouleurLiquide	=	GetNearestColor( hDC, Couleur ) ;
	DeleteDC( hDC ) ;
}

///////////////////////////////////////////////////////////////////////////////
// DessineVaguesMontantes
//	Dessine les vagues alors que le niveau monte
///////////////////////////////////////////////////////////////////////////////
static	void	DessineVaguesMontantes( HDC hDC )
{
	HBITMAP	hBitmap ;
	HDC		hDCIntermediaire ;
	BITMAP	sBitmap ;
	HBITMAP	hBitmapIntermediaire ;
	HBITMAP	hOldInterm ;
	int		i	 ;

	// On passage par un DC intermediaire pour ameliorer l'affichage
	hBitmap	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE(NoBitmap )) ;
	GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;
	
	// Creation de la bitmap intermediaire
	hDCIntermediaire	=	FastCreateDC( ) ;
	hBitmapIntermediaire=	CreateCompatibleBitmap( hDC, Largeur, sBitmap.bmHeight ) ;
	hOldInterm			=	SelectObject( hDCIntermediaire, hBitmapIntermediaire ) ;	


	// Mettre l'image de l'ecran dans la bitmap intermediaire
	FastBitBlt( hDCIntermediaire, 0,0, Largeur, sBitmap.bmHeight,
				  hDCEcran, 0, Niveau ) ;
	
	// Faire l'affichage dans la bitmap intermediaire
	{
	HDC	hDCVague ;
	HBITMAP	hOldBm ;

	SetBkColor( hDCIntermediaire, CouleurLiquide ) ;
	SetTextColor( hDCIntermediaire, RGB(255,255,255)) ;

	hDCVague	=	FastCreateDC( ) ;
	hOldBm		=	SelectObject( hDCVague, hBitmap ) ;

	for ( i = 0; i < Largeur; i += sBitmap.bmWidth )
		BitBlt( hDCIntermediaire, i,0, sBitmap.bmWidth, sBitmap.bmHeight,
				hDCVague, 0, 0, SRCAND ) ;


	SelectObject( hDCVague, hOldBm ) ;
	DeleteDC( hDCVague ) ;
	}	
	
	// Transferer sur l'ecran
	FastBitBlt(	hDC, 0, Niveau, Largeur, sBitmap.bmHeight,
					hDCIntermediaire, 0,0 ) ; 

	SelectObject( hDCIntermediaire, hOldInterm ) ;
	DeleteDC( hDCIntermediaire ) ;

	DeleteObject( hBitmapIntermediaire) ;
	DeleteObject( hBitmap ) ;
}


static	void	DessineVaguesDescendantes( HDC hDC )
{
	HBITMAP	hBitmap ;
	HDC		hDCIntermediaire ;
	BITMAP	sBitmap ;
	HBITMAP	hBitmapIntermediaire ;
	HBITMAP	hOldInterm ;
	int		i	 ;
	const	int	DecalageDescente	=	2 ;

	// On passe par un DC intermediaire pour ameliorer l'affichage
	hBitmap	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( NoBitmap )) ;
	GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;
	
	// Creation de la bitmap intermediaire
	hDCIntermediaire	=	FastCreateDC(  ) ;
	hBitmapIntermediaire=	CreateCompatibleBitmap( hDC, Largeur, sBitmap.bmHeight + DecalageDescente ) ;
	hOldInterm			=	SelectObject( hDCIntermediaire, hBitmapIntermediaire ) ;	


	// Mettre l'image de l'ecran dans la bitmap intermediaire
	FastBitBlt(	hDCIntermediaire, 0,0, Largeur, sBitmap.bmHeight+DecalageDescente,
					hDCEcran, 0, Niveau-DecalageDescente ) ;
	
	// Faire l'affichage dans la bitmap intermediaire
	{
	HDC	hDCVague ;
	HBITMAP	hOldBm ;

	SetBkColor( hDCIntermediaire, CouleurLiquide ) ;
	SetTextColor( hDCIntermediaire, RGB(255,255,255)) ;

	hDCVague	=	FastCreateDC(  ) ;
	hOldBm		=	SelectObject( hDCVague, hBitmap ) ;

	for ( i = 0; i < Largeur; i += sBitmap.bmWidth )
		BitBlt( hDCIntermediaire, i,DecalageDescente, sBitmap.bmWidth, sBitmap.bmHeight,
				hDCVague, 0, 0, SRCAND ) ;

	SelectObject( hDCVague, hOldBm ) ;
	DeleteDC( hDCVague ) ;
	}	
	
	// Transferer sur l'ecran
	FastBitBlt(	hDC, 0, Niveau-DecalageDescente, Largeur, sBitmap.bmHeight+DecalageDescente,
					hDCIntermediaire, 0,0 ) ; 

	SelectObject( hDCIntermediaire, hOldInterm ) ;
	DeleteDC( hDCIntermediaire ) ;

	DeleteObject( hBitmapIntermediaire) ;
	DeleteObject( hBitmap ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_InitEconomiseur( HWND hWnd )
{
	HDC		hDC ;

	SPECIF_LirePreferences() ;

	Montee				=	TRUE ;
	Niveau				=	Hauteur ;
	NouveauLiquide() ;
	NoircirEcran		=	FALSE ;
	HautePriorite		=	FALSE ;	
	NoBitmap			=	IDB_VAGUE ;	
	NbBulles			=	0 ;

	
	hDC	=	CreateIC( "display", 0, 0, 0 ) ;
	hDCEcran=	FastCreateDC() ;

	hBmpEcran	=	CreateCompatibleBitmap( hDC, Largeur, Hauteur ) ;
    hOldEcran	=	SelectObject(	hDCEcran,	hBmpEcran ) ;

	FastStretchBlt(	hDCEcran, 0,0, Largeur, Hauteur, 
						hDC, 0,0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) ) ;

	DeleteDC( hDC ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
DWORD __stdcall SPECIF_Animation( LPVOID lpVoid )
{
	HDC		hDC ;
	RECT	R ;
	SPECIF_InitEconomiseur( hWndPrincipale ) ;

	SetRect( &R, 0, 0, Largeur, Hauteur ) ;
	SetEvent( hEventInitFini ) ;

	hDC	=	GetDC( hWndPrincipale ) ;

	while ( ! Fini )
		{
		if ( Montee )
			{
			DessineVaguesMontantes( hDC ) ;
			Niveau -- ;
			
			// On est arrive en bas ?
			if (Niveau < R.top - 5 )
				{
				Montee	=	FALSE ;
				NbGouttes	=	0 ;
				}
			else
				GestionGouttes( hDC, CouleurLiquide, Niveau ) ;
			}
		else
			{
			DessineVaguesDescendantes( hDC ) ;

			Niveau ++ ;
			
			if ( Niveau > R.bottom )
				{
				Montee	=	TRUE ;
				NouveauLiquide() ;
				NbBulles	=	0 ;
				}
			else
				MonteeDesBulles( hDC ) ;
			}


		// Passage a la vague suivante	
		switch( NoBitmap )
			{
			case IDB_VAGUE :
				NoBitmap	=	IDB_VAGUE2 ;
				break ;
			case IDB_VAGUE2 :
				NoBitmap	=	IDB_VAGUE3 ;
				break ;
			case IDB_VAGUE3 :
				NoBitmap	=	IDB_VAGUE4 ;
				break ;
			default :
				NoBitmap	=	IDB_VAGUE ;
			}

		Sleep( FrequenceTimer ) ;
		}		

	ReleaseDC( hWndPrincipale, hDC ) ;
	SetEvent( hEventFini ) ;
	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
// FinEconomiseur
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_Fin( HWND hWnd )
{
    SelectObject(hDCEcran,hOldEcran ) ;
	DeleteDC( hDCEcran ) ;
	DeleteObject( hBmpEcran ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Repeindre le fond de la fenetre
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC	hDC, LPRECT lpR )
{
	FastBitBlt( hDC,	lpR->left, lpR->top, lpR->right - lpR->left, lpR->bottom-lpR->top,
				  hDCEcran,	0, 0 ) ;

	SetBkColor( hDC, CouleurLiquide ) ;
	SetTextColor( hDC, RGB(255,255,255)) ;
	
	BitBlt( hDC, lpR->left, lpR->top + Niveau,
				 lpR->right - lpR->left,
				 lpR->bottom-lpR->top-Niveau,
			hDCEcran, 0, Niveau, SRCAND ) ;
}


static	void	ConfSlider( HWND hWnd, UINT Id, int	Valeur, int Min, int Max )
{
	SendDlgItemMessage( hWnd, Id, TBM_SETRANGE, TRUE, MAKELPARAM( Min, Max )) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETPAGESIZE, TRUE, 10 ) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETLINESIZE, TRUE, 1 ) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETPOS, TRUE, (LPARAM)Valeur ) ;
}


/* ScreenSaverConfigureDialog -- Dialog box function for configuration
 * dialog.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL SPECIF_PreprocessMessageConfig(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
		SPECIF_LirePreferences() ;
		ConfSlider( hDlg, IDC_BULLES, NbMaxBulles, 0, NB_MAX_BULLES ) ;
		ConfSlider( hDlg, IDC_GOUTTES, NbMaxGouttes, 0, 20 ) ;
		ConfSlider( hDlg, IDC_VITESSE, FrequenceTimer, 0, 1000 ) ;
		}
		return FALSE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			NbMaxBulles		=	SendDlgItemMessage( hDlg, IDC_BULLES, TBM_GETPOS , 0, 0 ) ;
			NbMaxGouttes	=	SendDlgItemMessage( hDlg, IDC_GOUTTES, TBM_GETPOS , 0, 0 ) ;
			FrequenceTimer	=	SendDlgItemMessage( hDlg, IDC_VITESSE, TBM_GETPOS , 0, 0 ) ;

			SPECIF_EcrirePreferences() ;
			EndDialog( hDlg, TRUE ) ;
			return TRUE ;

		case IDCANCEL:
			EndDialog( hDlg, wParam ) ;
			return TRUE ;

		default :
			return FALSE ;
		}
		
	default:
		return FALSE;
    }
}


