/*  Economiseur generique
 */
#define STRICT
#include <windows.h> 
#include <mmsystem.h>
#include <scrnsave.h>
#include <commctrl.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "specif.h"

#ifndef WIN32
#error	Ce programme doit etre compile uniquement en 32 bits
#endif


const char *	MessageCopyright	=	"Version ShareWare non enregistrée, (c) Lucien PILLONI 1995" ;
//const char *	MessageCopyright	=	"Copyright (c) Lucien PILLONI 1995. Ceci est une version de démonstration non destinée à la distribution" ;

BOOL	NoircirEcran = TRUE ;
BOOL	HautePriorite = TRUE ;
BOOL	Configure = FALSE ;
DWORD	dwSeed ;

COLORREF	CouleurMessage ;
int			Sens ;
int			Largeur ;
int			Hauteur ;
BOOL		VersionEnregistree	=	FALSE ;
HPALETTE	hPalette = 0 ;
HANDLE		hWinGLib ;
typedef BOOL (WINGAPI WinGRecommendDIBFormat)( BITMAPINFO FAR *pFormat );
typedef HBITMAP (WINGAPI WinGCreateBitmap)( HDC WinGDC, BITMAPINFO const FAR *pHeader,void FAR *FAR *ppBits );



struct header
	{
	  BITMAPINFOHEADER  Header;
	  RGBQUAD           aColors[256];
	} header;

HANDLE	hThread ;

// Fonctions de substitutions si on trouve pas WInG
HDC WINGAPI LOCAL_CreateDC(void)
	{
	return	CreateCompatibleDC( NULL ) ;
	}

BOOL WINGAPI LOCAL_BitBlt(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc,int nYOriginSrc )
	{
	return BitBlt(	hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,
					hdcSrc,	nXOriginSrc,nYOriginSrc,SRCCOPY ) ;
	}

BOOL WINGAPI LOCAL_StretchBlt(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc, int nYOriginSrc,int nWidthSrc,int nHeightSrc )
	{
	return StretchBlt( hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest,hdcSrc, nXOriginSrc, nYOriginSrc,nWidthSrc,nHeightSrc, SRCCOPY ) ;
	}

/*
 *  Clear the System Palette so that we can ensure an identity palette 
 *  mapping for fast performance.
 */

void ClearSystemPalette(void)
{
  //*** A dummy palette setup
  struct
  {
    WORD Version;
    WORD NumberOfEntries;
    PALETTEENTRY aEntries[256];
  } Palette =
  {
    0x300,
    256
  };

  HPALETTE ScreenPalette = 0;
  HDC ScreenDC;
  int Counter;
  UINT nMapped = 0;
  BOOL bOK = FALSE;
  int  nOK = 0;
  
  //*** Reset everything in the system palette to black
  for(Counter = 0; Counter < 256; Counter++)
  {
    Palette.aEntries[Counter].peRed = 0;
    Palette.aEntries[Counter].peGreen = 0;
    Palette.aEntries[Counter].peBlue = 0;
    Palette.aEntries[Counter].peFlags = PC_NOCOLLAPSE;
  }

  //*** Create, select, realize, deselect, and delete the palette
  ScreenDC = GetDC(NULL);
  ScreenPalette = CreatePalette((LOGPALETTE *)&Palette);

  if (ScreenPalette)
  {
    ScreenPalette = SelectPalette(ScreenDC,ScreenPalette,FALSE);
    nMapped = RealizePalette(ScreenDC);
    ScreenPalette = SelectPalette(ScreenDC,ScreenPalette,FALSE);
    bOK = DeleteObject(ScreenPalette);
  }

  nOK = ReleaseDC(NULL, ScreenDC);

  return;
}



///////////////////////////////////////////////////////////////////////////////
// InitFonctions
//	Tente de charger WinG pour des transferts de bits plus rapides
///////////////////////////////////////////////////////////////////////////////
void	InitFonctions()
{
    hWinGLib = LoadLibrary("WING32");
    if (hWinGLib)
		{
		
        FastCreateDC	= (WinGCreateDCProc*) GetProcAddress((HMODULE) hWinGLib,"WinGCreateDC");
        FastBitBlt	= (WinGBitBltProc*) GetProcAddress((HMODULE) hWinGLib,"WinGBitBlt");
        FastStretchBlt= (WinGStretchBltProc*)GetProcAddress((HMODULE) hWinGLib, "WinGStretchBlt");

		ClearSystemPalette() ;
		}
	else
		{
		FastCreateDC	=	LOCAL_CreateDC ;
		FastBitBlt	=	LOCAL_BitBlt ;
		FastStretchBlt=	LOCAL_StretchBlt ;
		}
}

// ==================================================================================================
// FastCreateBitmap
// Creer une bitmap le mieux adaptee possible a l'affichage actuel (eventuellement WinG)
// ENTREES :	Largeur, Hauteur
// SORTIES :	rien
// RETOUR :		HBITMAP
// ==================================================================================================
HBITMAP	FastCreateBitmap( HDC hDC, int Largeur, int Hauteur ) 
{
	HBITMAP	hResult ;

	HDC	hIC	= CreateIC("display", 0, 0, 0 ) ;
	hResult	=	CreateCompatibleBitmap( hIC, Largeur, Hauteur ) ;
	DeleteDC( hIC ) ;
	
	return hResult ;
}
///////////////////////////////////////////////////////////////////////////////
// Verifie que c'est une version enregistree ou que c'est la machine a lulu
///////////////////////////////////////////////////////////////////////////////
BOOL VerifVersion()
{
	char	Buffer[100] ;
	DWORD	Taille	;
	time_t	tim ;
	struct	tm *	ptm ;
/*
	// Si c'est moi, je vais quand meme pas payer...
	Taille	=	sizeof( Buffer ) ;
	GetUserName( Buffer, &Taille) ;

	CharUpper( Buffer ) ;

	if ( lstrcmp( Buffer, "PILLONI" ) == 0)
		return TRUE ;


	if ( lstrcmp( Buffer, "LUCIEN" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LULU" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LP" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LPI" ) == 0)
		return TRUE ;

	LitChaine( "Enregistrement", Buffer, sizeof( Buffer )) ;
*/

	// Verification de la date
	time( &tim ) ;
	ptm	=	localtime( &tim ) ;

	if ( ptm->tm_year >= 98 && ptm->tm_mon >= 3 && ptm->tm_mday >= 3 )
		{
		exit(0) ;
		}

	return lstrcmp( Buffer, SPECIF_ValeurEnregistre ) == 0 ;
}

static void PrepareDC( HDC hDC, RECT R )
{
	SetMapMode( hDC, MM_ANISOTROPIC ) ;
					
	SetWindowExtEx(  hDC, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), NULL ) ;
	SetWindowOrgEx(  hDC, 0, 0, NULL) ;
	
	SetViewportExtEx( hDC, R.right - R.left, R.bottom - R.top, NULL ) ;
	SetViewportOrgEx( hDC, R.left,R.top, NULL ) ;

	if ( hPalette )
		{
		SelectPalette( hDC, hPalette, FALSE ) ;
		RealizePalette( hDC ) ;
		}
}

/* ScreenSaverProc - Main entry point for screen saver messages.
 *  This function is required for all screen savers.
 *
 * Params:  Standard window message handler parameters.
 *
 * Return:  The return value depends on the message.
 *
 *  Note that all messages go to the DefScreenSaverProc(), except
 *  for ones we process.
 */
LRESULT WINAPI ScreenSaverProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT	Ps ;
	RECT 		R ;
	    			
	switch (msg)
   	{
      case WM_CREATE:
    		{
			DWORD	Id ;
			InitFonctions() ;

			hPalette	=	0 ;
#ifdef _DEBUG
			SetWindowPos( hWnd, 0, 0, 0, GetSystemMetrics( SM_CXSCREEN ) / 2,
						  GetSystemMetrics( SM_CYSCREEN ), SWP_NOMOVE ) ;
			SetWindowLong( hWnd, GWL_STYLE,
							GetWindowLong( hWnd, GWL_STYLE ) | WS_THICKFRAME ) ;
#endif
			dwSeed = GetCurrentTime() ;

			GetClientRect( hWnd, &R) ;
			Largeur	=	R.right - R.left ;
			Hauteur	=	R.bottom - R.top ;

			hWndPrincipale	=	hWnd ;
			hEventInitFini	=	CreateEvent( NULL, FALSE, FALSE, SPECIF_NomEconomiseur ) ;

			CouleurMessage	=	RGB(0,255, 0) ;
			Sens			=	-16 ;
			VersionEnregistree	=	VerifVersion() ;

			hThread	=	CreateThread( NULL, 0, SPECIF_Animation, 0, CREATE_SUSPENDED, &Id ) ;
			SetThreadPriority( hThread, THREAD_PRIORITY_NORMAL ) ;
			ResumeThread( hThread ) ;
			
			if( WaitForSingleObject( hEventInitFini, 20000 ) == WAIT_TIMEOUT )
				// Time out pour verifier que j'ai pas oublie de faire SetEvent !
				MessageBox( hWnd, "Event oublié pour cet economiseur !", 0, MB_OK ) ;

			CloseHandle( hEventInitFini ) ;
			break;
        	}

	case WM_DESTROY:
		hEventFini	=	CreateEvent( NULL, FALSE, FALSE, SPECIF_NomEconomiseur ) ;
		Fini	=	TRUE ;
		WaitForSingleObject( hEventFini, 20000 ) ;
		CloseHandle( hEventFini ) ;

		if ( hWinGLib )
			FreeLibrary( hWinGLib ) ;
		break;

	case WM_PAINT :
		SuspendThread( hThread ) ;
		BeginPaint( hWnd, &Ps ) ;
		GetClientRect( hWnd, &R ) ;
			
		if ( Configure )
			PrepareDC( Ps.hdc, R ) ;
				
		R.right = R.left + GetSystemMetrics( SM_CXSCREEN ) ;
		R.bottom= R.top+ GetSystemMetrics( SM_CYSCREEN ) ;
			
		SPECIF_PeintFenetre( Ps.hdc, &R ) ;
		EndPaint( hWnd, &Ps ) ;
		ResumeThread( hThread ) ;
		break ;
			
      case WM_ERASEBKGND:
      	if ( NoircirEcran )
      		return DefWindowProc( hWnd, msg, wParam, lParam ) ;
      	else
      		return TRUE ;

	  case WM_PALETTECHANGED :
		  if ( hPalette )
			  {
			  if ( (HWND)wParam == hWnd )
					break ;
			  }
	  case WM_QUERYNEWPALETTE :
		  {
		  if ( hPalette )
			  {
			  HDC	hDC	=	GetDC( hWnd ) ;
			  SelectPalette( hDC, hPalette, FALSE ) ;
			  RealizePalette( hDC ) ;
			  ReleaseDC( hWnd, hDC ) ;
			  }
		  return (hPalette != 0 ) ;
		  }

	case WM_LBUTTONDOWN :
	case WM_MBUTTONDOWN :
	case WM_RBUTTONDOWN :
	case WM_KEYDOWN :
	case WM_KEYUP :
	case WM_MOUSEMOVE:
		{
		LRESULT	Res ;
		int		Priority =	GetThreadPriority( hThread ) ;
		SetThreadPriority( hThread, THREAD_PRIORITY_LOWEST ) ;
		Res	=	DefScreenSaverProc( hWnd, msg, wParam, lParam ) ;
		SetThreadPriority( hThread, Priority ) ;
		return Res ;
		}
		break ;

		default:
			break;
	}

	return DefScreenSaverProc(hWnd, msg, wParam, lParam);
}

/* RegisterDialogClasses -- Entry point for registering window
 * classes required by configuration dialog box.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL WINAPI RegisterDialogClasses( HINSTANCE hInst)
{
#ifdef LPICTRL
	LPICTRL_EnregistreControles( hInst ) ;
#endif
	InitCommonControls() ;
	return TRUE;
}



/* ScreenSaverConfigureDialog -- Dialog box function for configuration
 * dialog.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL WINAPI ScreenSaverConfigureDialog (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if ( msg	== WM_CREATE )
		InitFonctions() ;
	else
		if ( msg	== WM_DESTROY )
		{
		if ( hWinGLib )
			FreeLibrary( hWinGLib ) ;
		}

	if ( SPECIF_PreprocessMessageConfig( hDlg, msg, wParam, lParam ))
		return TRUE ;

	switch (msg)
	{
	case WM_INITDIALOG:
		{
		// Ajouter les property pages

		// Centrer la boite sur l'ecran
		RECT	R ;
		GetWindowRect( hDlg, &R ) ;

		SetWindowPos( hDlg, 0,	(GetSystemMetrics( SM_CXSCREEN ) - (R.right-R.left))/2,
								(GetSystemMetrics( SM_CYSCREEN ) - (R.bottom-R.top))/2,
								0,0,
					  SWP_NOZORDER	| SWP_NOSIZE ) ;

		}
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
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


// ==================================================================================================
// Retoune un entier aleatoire
// ==================================================================================================
int arand( int x )
{
	dwSeed = dwSeed * 0x343fd + 0x269ec3;
	return( (int)(((dwSeed >> 16) & 0x7fff) * x >> 15) );
}


// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
int Alea( int Min, int Max )
{
	return Min + arand( Max - Min + 1 ) ;
}

// ==================================================================================================
// UnSur
// Retourne une VRAI un coup sur...
// ==================================================================================================
BOOL UnSur( int x )
{
	return !(arand(x)) ;
}


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
    hOldEcran	=	SelectObject(	hDCEcran,	hBmpEcran ) ;

	FastStretchBlt(	hDCEcran, 0,0, Larg, Haut, 
					hDC, 0,0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) ) ;

	DeleteDC( hDC ) ;
	SelectObject( hDCEcran, hOldEcran ) ;
	DeleteDC( hDCEcran ) ;

	return hBmpEcran ;
}

// ==================================================================================================
// EcritEntier
//	Ecrit un entier dans la registry sous la branche donnee pour l'economiseur
//	par SPECIF_NomEconomiseur
// ==================================================================================================
void	EcritEntier( char * RubriqueName, DWORD Valeur )
{
	char	Clef[255] ;
	DWORD	Dispo ;
	HKEY	hKey ;

	lstrcpy( Clef, "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" ) ;
	lstrcat( Clef, SPECIF_NomEconomiseur ) ;
	
	if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
		return ;

	RegSetValueEx( hKey, RubriqueName, 0, REG_DWORD, (LPBYTE)&Valeur, sizeof( Valeur )) ;
}

void	EcritChaine( char * RubriqueName, char * Valeur )
{
	char	Clef[255] ;
	DWORD	Dispo ;
	HKEY	hKey ;

	lstrcpy( Clef, "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" ) ;
	lstrcat( Clef, SPECIF_NomEconomiseur ) ;
	
	if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
		return ;

	RegSetValueEx( hKey, RubriqueName, 0, REG_SZ, (LPBYTE)Valeur, lstrlen( Valeur )+1) ;
}

int		LitEntier( char * RubriqueName, DWORD Defaut )
{
	DWORD Retour	=	Defaut ;
	char	Clef[255] ;
	HKEY	hKey ;
	DWORD	Taille ;
 	DWORD	Type ;

	lstrcpy( Clef, "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" ) ;
	lstrcat( Clef, SPECIF_NomEconomiseur ) ;
	
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		return Retour ;

 	Taille	=	sizeof( Retour ) ;
	Type	=	REG_DWORD ;
	if ( RegQueryValueEx( hKey, RubriqueName, 0, &Type, (LPBYTE)&Retour, &Taille) != ERROR_SUCCESS )
		Retour	=	Defaut ;

	return Retour ;
}

void LitChaine( char * RubriqueName, char * Buffer, int T )
{
	char	Clef[255] ;
	char	*	pValeur ;
	HKEY	hKey ;
	DWORD	Taille ;
 	DWORD	Type ;

	lstrcpy( Clef, "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" ) ;
	lstrcat( Clef, SPECIF_NomEconomiseur ) ;
	
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		return ;


	pValeur	=	malloc( T ) ;
 	Taille	=	T ;
	Type	=	REG_SZ ;

	if ( RegQueryValueEx( hKey, RubriqueName, 0, &Type, (LPBYTE)pValeur, &Taille) == ERROR_SUCCESS )
		{
		lstrcpy( Buffer, pValeur ) ;
		}

	free( pValeur ) ;
}


double LitDouble( char * RubriqueName, double Defaut )
{
	char	Buffer[50] ;

	gcvt( Defaut, 45, Buffer ) ;

	LitChaine( RubriqueName, Buffer, sizeof( Buffer ) ) ;

	return atof( Buffer ) ;
}

void EcritDouble( char * RubriqueName, double Valeur )
{
	char	Buffer[50] ;

	gcvt( Valeur, 45, Buffer ) ;

	EcritChaine( RubriqueName, Buffer ) ;
}

// ==================================================================================================
// IncluRect
//	Determine si le deuxieme rectangle est entierement inclu dans le premier
// ENTREES :	Deux rectangles
// RETOUR :		Vrai si le deuxieme est inclu dans le premier
// ==================================================================================================
BOOL IncluRect( const RECT *	pR1, const RECT * pR2 )
{
	if ( pR2->left > pR1->right || pR2->left < pR1->left )
		return FALSE ;

	if ( pR2->top > pR1->bottom || pR2->top < pR1->top )
		return FALSE ;

	if ( pR2->right < pR1->left || pR2->right > pR1->right )
		return FALSE ;

	if ( pR2->bottom < pR1->top || pR2->bottom > pR1->bottom )
		return FALSE ;

	return TRUE ;
}


///////////////////////////////////////////////////////////////////////
// UnionValable
//	Decide si ca vaut le coup de combiner les deux rectangles pour
//	optimiser l'affichage
///////////////////////////////////////////////////////////////////////
BOOL	_inline UnionValable( const RECT * pR1, const RECT * pR2 )
	{
	RECT	Union ;
	int		SurfaceUnion, Surfaces ;

	if ( ! IntersectRect(&Union, pR1, pR2 ))
		return FALSE ;

	UnionRect( &Union, pR1, pR2 ) ;

	SurfaceUnion	=	(Union.right-Union.left) * (Union.bottom-Union.top) ;
	Surfaces		=	((pR1->right-pR1->left) * (pR1->bottom-pR1->top))
					  + ((pR2->right-pR2->left) * (pR2->bottom-pR2->top)) ;

	// On retourne VRAI meme si les surfaces sont identique car un 
	// bitblt vaut mieux que 2
	return	SurfaceUnion <= Surfaces ;
	}


// ==================================================================================================
// AjouteRect
// Ajoute un rectangle a la liste de rectangles a afficher, ne la prend pas en compte si elle sort de
// l'ecran ou si le rectangle est inclu dans un rectangle deja affiche
// ENTREES :	Tableau de rectangles
//				Taille du tableau
//				Nombre actuel de rectangles
//				Rectangle a ajouter
// SORTIES :	Nb de rectangles eventuellement incremente
// RETOUR :		rien
// ==================================================================================================
void AjouteRect( RECT*	TabRects, int NbMaxRects, int * pNbRects, const RECT * pR )
{
	int	i	;

	if ( pR->left > Largeur )
		return ;
	if ( pR->right < 0 )
		return ;

	if ( pR->top > Hauteur )
		return ;
	if ( pR->bottom < 0 )
		return ;

	// Essayer de trouver un rectangle qui coupe celui-ci pour n'en faire qu'un
	for ( i = 0; i < (* pNbRects); i++)
		if ( UnionValable( &TabRects[i], pR ))
			{
			UnionRect( &TabRects[i], &TabRects[i], pR ) ;
			//TabRects[i].left	=	min( TabRects[i].left, pR->left ) ;
			//TabRects[i].right	=	max( TabRects[i].right, pR->right ) ;
			//TabRects[i].top		=	min( TabRects[i].top, pR->top ) ;
			//TabRects[i].bottom	=	max( TabRects[i].bottom, pR->bottom ) ;
			return ;
			}

	// Pas de rectangle trouve, on en cree un autre
	if ( (* pNbRects)  < NbMaxRects )
		{
		TabRects[(* pNbRects)] = *pR ;
		(* pNbRects)	++ ;
		}
	else
		{
		// Deja tous utilises, on prend le premier venu
		RECT R ;
		UnionRect( &R, &TabRects[0], pR ) ;
		TabRects[0]=R;
		}
}

// ==================================================================================================
// AfficheRectangle
// Affiche les rectangles de la liste
// ENTREES :	Tableau de rectangles
//				Nombre de rectangles
//				Dc source et dest
// SORTIES :	rien
// RETOUR :		rien
// ==================================================================================================
void	AfficheRectangles( RECT *	TabRect, const int NbRects, HDC hDCDest, HDC hDCSrc )
{
	int i ;

	for (i = 0; i < NbRects; i++)
		FastBitBlt( hDCDest,
					TabRect[i].left,
					TabRect[i].top,
					TabRect[i].right - TabRect[i].left,
					TabRect[i].bottom - TabRect[i].top,
					hDCSrc,
					TabRect[i].left,
					TabRect[i].top ) ;
}

// ==================================================================================================
// NbCouleurs
// Retourne le nombre de couleurs du mode graphique
// ENTREES :	rien
// SORTIES :	rien
// RETOUR :		vraisemblablement 16, 256 ou 65536
// ==================================================================================================
int	NbCouleurs(void)
{
	HDC	hDC	;
	int	Nb ;

	hDC	=	CreateIC( "display", 0, 0, 0 ) ;
	Nb	=	GetDeviceCaps( hDC, PLANES ) * (int)pow( 2, GetDeviceCaps( hDC, BITSPIXEL )) ;
	DeleteDC( hDC ) ;

	return Nb ;
}
