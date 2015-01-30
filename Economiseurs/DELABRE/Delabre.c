/*  STARSAVE Economiseur d'ecran intergalactique
 */

#include <windows.h>
#include <scrnsave.h>
#include <commctrl.h>
#include <time.h>
#include <stdlib.h>
#include "..\specif.h"
#include "resource.h"

#define LARGEUR	GetSystemMetrics(SM_CXSCREEN)
#define HAUTEUR	GetSystemMetrics(SM_CYSCREEN)
#define MAX_DELAI		200
#define MIN_DELAI		50
#define NB_MAX_GOUTTES	15
#define NB_MAX_BITMAP 	20

// ======================================================= Types
typedef struct
		{
		POINT		PosDepart ;
		SIZE		TailleDepart ;
		POINT		Pos ;
		SIZE		Taille ;
		SIZE		TailleMax ;
		int		Masque ;
		DWORD		RasterOp ;
		HBITMAP	hBitmapDepart ;
		}
		GOUTTE ;
		
// ========================================== Variables globales
HBITMAP	hBitmaps[ NB_MAX_BITMAP ] ;
int		NbBitmaps ;
GOUTTE	Goutte[NB_MAX_GOUTTES] ;

// Valeurs de parametrage
int		Grosseur, Rapidite, Densite ;
HBITMAP	hBitmapEcran ;

const	char	*	SPECIF_NomEconomiseur	=	"Delabre" ;
const	char	*	SPECIF_ValeurEnregistre	=	"LPI_DEl.0"  ;

void CouleurEnHaut( HDC hDC )
{
	HBRUSH hOldBrush ;
	HBRUSH hBrush ;
	static int CompteTours = 0 ;
	
	if ( CompteTours ++  )	
		{
		if ( CompteTours > HAUTEUR )
			CompteTours = 0 ;
			
		return ;
		}
		
	hBrush = CreateSolidBrush( RGB(Alea( 0, 255 ), Alea( 0, 255 ), Alea( 0, 255 )) ) ;
	
	hOldBrush = SelectObject( hDC, hBrush ) ;
	PatBlt(hDC, 0, 2, LARGEUR, 8, PATCOPY )	;
	SelectObject( hDC, hOldBrush ) ;
	DeleteObject( hBrush ) ;
}

void AfficheGoutte( HDC hDC, GOUTTE * pGoutte )
{
	HDC		hMasqueDC ;
	HBITMAP	hOldMasque ;
	BITMAP	Masque ;
	HDC		hTailleMasqueDC ;
	HBITMAP	hTailleMasqueBM ;
	HBITMAP	hOldTailleMasque ;
	HDC		hEcranDC ;
	HBITMAP	hEcranBM ;
	HBITMAP	hOldEcran ;
	HDC		hTempoDC ;
	HBITMAP	hTempoBM ;
	HBITMAP	hOldTempo ;
	
	// Retailler le masque
	hMasqueDC = CreateCompatibleDC( hDC ) ;
	hOldMasque= SelectObject( hMasqueDC, hBitmaps[pGoutte->Masque] ) ;
	GetObject( hBitmaps[pGoutte->Masque], sizeof( Masque ), &Masque ) ;

	hTailleMasqueDC = CreateCompatibleDC( hDC ) ;
	hTailleMasqueBM = CreateCompatibleBitmap( hDC, pGoutte->Taille.cx, pGoutte->Taille.cy ) ;
	hOldTailleMasque= SelectObject( hTailleMasqueDC, hTailleMasqueBM ) ;
	
	StretchBlt( hTailleMasqueDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy,
				hMasqueDC, 0, 0, Masque.bmWidth, Masque.bmHeight, NOTSRCCOPY ) ;
				
	SelectObject( hMasqueDC, hOldMasque ) ;
	DeleteDC( hMasqueDC ) ;
	
	// Etirer l'image de l'ecran
	{
	HDC hMemDC ;
	HBITMAP hOldBitmap ;
	
	hMemDC		= CreateCompatibleDC( hDC ) ;
	hOldBitmap	= SelectObject( hMemDC, pGoutte->hBitmapDepart  ) ;
	
	hEcranDC = CreateCompatibleDC( hDC ) ;
	hEcranBM = CreateCompatibleBitmap( hDC, pGoutte->Taille.cx, pGoutte->Taille.cy ) ;
	hOldEcran= SelectObject( hEcranDC, hEcranBM ) ;
	
	StretchBlt( hEcranDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy,
					hMemDC, 0,0,
					pGoutte->TailleDepart.cx, pGoutte->TailleDepart.cy, SRCCOPY ) ;
	
	SelectObject( hMemDC, hOldBitmap );
	DeleteDC( hMemDC ) ;
	}
				
	// Effacer les parties hors de la goutte
	BitBlt( hEcranDC, 0, 0,  pGoutte->Taille.cx, pGoutte->Taille.cy,
			hTailleMasqueDC, 0, 0, SRCAND ) ;
			
	PatBlt( hTailleMasqueDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy, DSTINVERT ) ;

	// Dc temporaire pour eviter les scintillements
	hTempoDC = CreateCompatibleDC( hDC ) ;
	hTempoBM = CreateCompatibleBitmap( hDC, pGoutte->Taille.cx, pGoutte->Taille.cy ) ;
	hOldTempo= SelectObject( hTempoDC, hTempoBM ) ;
	                      
    BitBlt( hTempoDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy,
			hDC, pGoutte->Pos.x, pGoutte->Pos.y, SRCCOPY) ;
			
    BitBlt( hTempoDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy,
			hTailleMasqueDC, 0, 0, SRCAND ) ;
			
	BitBlt( hTempoDC, 0, 0, pGoutte->Taille.cx, pGoutte->Taille.cy,
			hEcranDC, 0, 0, SRCPAINT ) ;

	// Afficher (enfin !)
	BitBlt( hDC, pGoutte->Pos.x, pGoutte->Pos.y,
			pGoutte->Taille.cx, pGoutte->Taille.cy,
			hTempoDC, 0, 0, pGoutte->RasterOp ) ;
    
	// Detruire les objets crees	
	SelectObject( hTempoDC, hOldTempo ) ;
	DeleteDC( hTempoDC ) ;
	DeleteObject( hTempoBM ) ;
	
	SelectObject( hEcranDC, hOldEcran ) ;
	DeleteDC( hEcranDC ) ;
	DeleteObject( hEcranBM ) ;
	
	SelectObject( hTailleMasqueDC, hOldTailleMasque ) ;
	DeleteDC( hTailleMasqueDC ) ;
	DeleteObject( hTailleMasqueBM ) ;
}

void NouvelleGoutte( HDC hDC, GOUTTE * pGoutte )
{
	int		Aleat ;
	
	pGoutte->PosDepart.x	= Alea( 0, LARGEUR ) ;
	pGoutte->PosDepart.y	= Alea( 0, HAUTEUR ) ;
	
	pGoutte->TailleDepart.cx= Alea( Grosseur, Grosseur*2 ) ;
	pGoutte->TailleDepart.cy= Alea( 3, 20 ) ;
	
	pGoutte->Taille.cx		= pGoutte->TailleDepart.cx-Alea(2,10) ;
	pGoutte->Taille.cy		= pGoutte->TailleDepart.cy+1 ;
	
	pGoutte->Pos.x				= pGoutte->PosDepart.x + 1 ;
	pGoutte->Pos.y				= pGoutte->PosDepart.y + 1 ;
	
	pGoutte->TailleMax.cx	= pGoutte->TailleDepart.cx ;		
	pGoutte->TailleMax.cy	= pGoutte->TailleDepart.cy * Alea( 5, 30) ;		
		
	pGoutte->Masque			= Alea( 0, NbBitmaps-1 ) ;
	
	if ( GetDeviceCaps(hDC, NUMCOLORS ) > 16 )
		Aleat = 3 ;
	else
		Aleat = 8 ;
	
	switch( Alea( 0, 8 ))
		{
		case 0 :
			pGoutte->RasterOp =SRCPAINT ;
			break ;
		case 1 :
			pGoutte->RasterOp =SRCAND ;
			break ;
		default :
			pGoutte->RasterOp = SRCCOPY ;
			break ;
		}
	
	if ( pGoutte->hBitmapDepart )
		{
		DeleteObject( pGoutte->hBitmapDepart ) ;
		pGoutte->hBitmapDepart = 0 ;
		}
	
	// Creer la bitmap qui memorise l'image a degouliner	
	{
	HDC		hMemDC ;
	HBITMAP  hOldBitmap ;
	
	hMemDC				= CreateCompatibleDC( hDC ) ;
	pGoutte->hBitmapDepart	= CreateCompatibleBitmap( hDC, pGoutte->TailleDepart.cx, pGoutte->TailleDepart.cy ) ;
	hOldBitmap			= SelectObject( hMemDC, pGoutte->hBitmapDepart ) ;
	BitBlt( hMemDC, 0, 0, pGoutte->TailleDepart.cx, pGoutte->TailleDepart.cy,
			  hDC, pGoutte->PosDepart.x, pGoutte->PosDepart.y, SRCCOPY ) ;
			  
	SelectObject( hMemDC, hOldBitmap ) ;
	DeleteDC( hMemDC ) ;
	}
}

void AvanceGoutte( GOUTTE * pGoutte )
{
	(pGoutte->Taille.cy) ++ ;
}

void DelabreEcran( HDC hDC, GOUTTE * pGoutte )
{	
	// Controles
	if ( (pGoutte->Taille.cx > pGoutte->TailleMax.cx) || (pGoutte->Taille.cy > pGoutte->TailleMax.cy) )
		// Nouvelle goutte
		NouvelleGoutte( hDC, pGoutte ) ;

	AfficheGoutte( hDC, pGoutte ) ;
	
	// Avance la goutte
	AvanceGoutte( pGoutte ) ;

}             

void ChargeBitmaps()
{
	NbBitmaps = 0 ;
	
	while ( NbBitmaps < NB_MAX_BITMAP )
		{
		hBitmaps[NbBitmaps] = LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_BITMAP1 + NbBitmaps )) ;
		if ( ! hBitmaps[NbBitmaps] )
			return ;
		
		NbBitmaps ++ ;
		}
}

void DetruitBitmaps()
{
	int i ;
	
	for ( i = 0; i < NbBitmaps; i++)
		DeleteObject( hBitmaps[i] ) ;
}

void SPECIF_LirePreferences()
{
//    	HautePriorite = LitEntier( "Priorite",  TRUE ) ;
		Rapidite	= LitEntier( "Rapidite", 60 ) ;
		Grosseur	= LitEntier( "Grosseur", 50 ) ;
		Densite		= LitEntier( "Densite", NB_MAX_GOUTTES/2) ;
		
		if ( Densite >= NB_MAX_GOUTTES)
			Densite = NB_MAX_GOUTTES - 1 ;
}

void	SPECIF_EcrirePreferences()
{
//	EcritEntier( "Priorite", HautePriorite ) ;
    EcritEntier( "Rapidite", Rapidite ) ;
	EcritEntier( "Grosseur", Grosseur ) ;
	EcritEntier( "Densite", Densite ) ;
}

void	SPECIF_InitEconomiseur( HWND hWnd )
{				
	HDC	hDC ;
	int i ;

	hBitmapEcran	=	MemoEcran( Largeur, Hauteur ) ;

	ChargeBitmaps() ;
	        
	hDC = GetDC( hWnd ) ;
	for ( i = 0; i < Densite; i++)
		NouvelleGoutte( hDC, &Goutte[i] ) ;

	ReleaseDC( hWnd, hDC ) ;
	        
	SetTimer( hWnd, 1, (MAX_DELAI+MIN_DELAI)-Rapidite, (TIMERPROC)NULL ) ;
	NoircirEcran	=	FALSE ;
//	HautePriorite	=	TRUE ;
}


DWORD _stdcall SPECIF_Animation( LPVOID lp )
{
	int  i ;
	int	Fois=0 ;
	HDC	hDC ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	hDC	=	GetDC( hWndPrincipale ) ;


	SetEvent( hEventInitFini ) ;

	while ( ! Fini )
		{
		Fois++ ;

		if ( Fois == 1000 )
			{
			CouleurEnHaut(hDC) ;
			Fois	=	0 ;
			}
				
		for ( i = 0; i < Densite; i++)
			DelabreEcran( hDC, &Goutte[i] ) ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;
	return 0 ;
}

void	SPECIF_Fin( HWND hWnd )
{
	int i ;

	ShowCursor( TRUE ) ;
	DetruitBitmaps() ;
	for ( i = 0; i < Densite; i++)
		if ( Goutte[i].hBitmapDepart )
			DeleteObject( Goutte[i].hBitmapDepart ) ;
}


void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	HDC	hMemDC ;
	HBITMAP	hOBitmap ;

	hMemDC	=	CreateCompatibleDC( hDC ) ;
	hOBitmap		=	SelectObject( hMemDC, hBitmapEcran ) ;
	StretchBlt( hDC, lpR->left, lpR->top, lpR->right-lpR->left, lpR->bottom-lpR->top,
				hMemDC, 0, 0, LARGEUR, HAUTEUR, SRCCOPY ) ;
	SelectObject( hMemDC, hOBitmap ) ;
	DeleteDC( hMemDC) ;
}


void CentreFenetre( HWND hFenetre )
{
	RECT R ;
	int	LargeurEcran = GetSystemMetrics( SM_CXSCREEN ) ;
	int	HauteurEcran = GetSystemMetrics( SM_CYSCREEN ) ;
	int	LargeurFenetre, HauteurFenetre ;
	
	GetWindowRect( hFenetre, &R ) ;
	
	LargeurFenetre = R.right - R.left ;
	HauteurFenetre = R.bottom - R.top ;
	
	R.left = (LargeurEcran - LargeurFenetre) / 2 ;
	R.top = (HauteurEcran - HauteurFenetre) / 2 ;
	
	SetWindowPos( hFenetre, HWND_TOP, R.left, R.top, LargeurFenetre, HauteurFenetre,
				  SWP_NOSIZE ) ;
}

BOOL CALLBACK DlgAbout( HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	RECT		R ;
	PAINTSTRUCT	Ps ;
	HDC			hMemDC ;
	HBITMAP		hBitmap ;
	HBITMAP		hOldBitmap ;
	BITMAP		sBitmap ;
	
	switch( Message )
		{
		case WM_INITDIALOG :
			CentreFenetre( hDlg ) ;
			return TRUE ;
			
		case WM_COMMAND :
			switch( wParam)
				{
				case IDOK :
					EndDialog( hDlg, TRUE ) ;
					break ;
				default :
					return FALSE ;
				}
			break ;
		case WM_PAINT :
			BeginPaint( hDlg, &Ps ) ;
			GetClientRect( hDlg, &R ) ;
			hBitmap		= LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_APROPOS )) ;
			hMemDC		= CreateCompatibleDC( Ps.hdc ) ;
			hOldBitmap	= SelectObject( hMemDC, hBitmap ) ;
			GetObject( hBitmap, sizeof( sBitmap ), (LPSTR)&sBitmap ) ;
			
			BitBlt(Ps.hdc, (R.right-R.left-sBitmap.bmWidth) / 2, (R.bottom-R.top-sBitmap.bmHeight)/2,
				   sBitmap.bmWidth, sBitmap.bmHeight,
				   hMemDC, 0, 0, SRCCOPY ) ;
				   
			SelectObject( hMemDC, hOldBitmap ) ;
			DeleteDC( hMemDC ) ;
			DeleteObject( hBitmap ) ;
			EndPaint( hDlg, &Ps ) ;
			break ;
			
		default :
			return FALSE ;
		}
		
	return TRUE ;
}

void BoiteAPropos( HWND hDlg )
{
	//FARPROC	lProc = MakeProcInstance( DlgAbout, hMainInstance ) ;
	
	DialogBox( hMainInstance, MAKEINTRESOURCE( IDD_APROPOS ), hDlg, DlgAbout ) ;
	//FreeProcInstance( lProc ) ;
}

/* ScreenSaverConfigureDialog -- Dialog box function for configuration
 * dialog.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL SPECIF_PreprocessMessageConfig ( HWND hDlg, UINT Message,
                                          WPARAM wParam, LPARAM lParam)
{
    switch( Message )
        {
        case WM_INITDIALOG :
        	CentreFenetre( hDlg ) ;

            SPECIF_LirePreferences() ;
			
			SendDlgItemMessage( hDlg, IDC_RAPIDITE, TBM_SETRANGE, TRUE, MAKELPARAM( MIN_DELAI, MAX_DELAI )) ;
			SendDlgItemMessage( hDlg, IDC_RAPIDITE, TBM_SETPOS, TRUE, Rapidite ) ;

			SendDlgItemMessage( hDlg, IDC_GROSSEUR, TBM_SETRANGE, TRUE, MAKELPARAM( 0, 100 ));
			SendDlgItemMessage( hDlg, IDC_GROSSEUR, TBM_SETPOS, TRUE, Grosseur ) ;
			
			SendDlgItemMessage( hDlg, IDC_DENSITE, TBM_SETRANGE, TRUE, MAKELPARAM( 1, NB_MAX_GOUTTES-1 )) ;
			SendDlgItemMessage( hDlg, IDC_DENSITE, TBM_SETPOS, TRUE, Densite ) ;

//			CheckDlgButton( hDlg, IDC_PRIORITE, HautePriorite ) ;
			break ;


		case WM_COMMAND :
			switch( wParam )
					{
					case IDC_APROPOS :
						BoiteAPropos( hDlg ) ;
						break ;

					case IDCANCEL :
					EndDialog( hDlg, FALSE ) ;
					break ;

					case IDOK :
						Rapidite	= SendDlgItemMessage( hDlg, IDC_RAPIDITE, TBM_GETPOS, 0, 0 ) ;
						Grosseur	= SendDlgItemMessage( hDlg, IDC_GROSSEUR, TBM_GETPOS, 0, 0 ) ;
						Densite		= SendDlgItemMessage( hDlg, IDC_DENSITE, TBM_GETPOS, 0, 0 ) ;

//						HautePriorite	=	IsDlgButtonChecked( hDlg, IDC_PRIORITE ) ;

						SPECIF_EcrirePreferences() ;

						EndDialog( hDlg, TRUE ) ;
                    break ;
                }
                break;

        default :
            return FALSE ;
        }

    return TRUE ;
}
