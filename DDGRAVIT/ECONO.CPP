/*  Economiseur generique
 */
#include "stdafx.h"
#include <scrnsave.h>
#include "economiseur.h"

const char *	MessageCopyright	=	"Version ShareWare non enregistrée, (c) Lucien PILLONI 1995" ;
//const char *	MessageCopyright	=	"Copyright (c) Lucien PILLONI 1995. Ceci est une version de démonstration non destinée à la distribution" ;

DWORD	dwSeed ;

COLORREF	CouleurMessage ;
int			Sens ;
CWinApp		TheApp ;
BOOL		VersionEnregistree	=	FALSE ;

///////////////////////////////////////////////////////////////////////////////
// Verifie que c'est une version enregistree ou que c'est la machine a lulu
///////////////////////////////////////////////////////////////////////////////
BOOL VerifVersion()
{
	char	Buffer[100] ;
	DWORD	Taille	;
	time_t	tim ;
	struct	tm *	ptm ;

	if ( fChildPreview )
		return TRUE ;

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

	//CString	Valeur ;
	//CEconomiseur::GetEconomiseur()->LiPreference( "Enregistrement", Valeur) ;

	// Verification de la date
	time( &tim ) ;
	ptm	=	localtime( &tim ) ;

	if ( ptm->tm_year >= 97 && ptm->tm_mon >= 1 && ptm->tm_mday >= 3 )
		{
		if ( ! fChildPreview )
			{
			MessageBeep( MB_ICONSTOP ) ;
			MessageBox( 0, "Ceci est un ShareWare, il est temps de vous enregistrer ( voyez la boîte de configuration ).",
						"ShareWare", MB_OK | MB_ICONSTOP ) ;

			exit(0) ;
			}
		}
	return FALSE ;//return lstrcmp( Buffer, SPECIF_ValeurEnregistre ) == 0 ;
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
	static		CEconomiseur *	pEconomiseur ;
	static		BOOL InitSave	=	FALSE ;
	    			
	switch (msg)
   	{
      case WM_CREATE:
    		{
			AfxWinInit((HINSTANCE)hMainInstance, 0, "", SW_SHOW ) ;

			hMainWindow	=	hWnd ;

			AfxSetResourceHandle( (HINSTANCE)hMainInstance ) ;
#ifdef _DEBUG
			SetWindowPos( hWnd, 0, 0, 0, GetSystemMetrics( SM_CXSCREEN ) / 3,
						  GetSystemMetrics( SM_CYSCREEN )/2, SWP_NOMOVE ) ;
			SetWindowLong( hWnd, GWL_STYLE,
							GetWindowLong( hWnd, GWL_STYLE ) | WS_THICKFRAME ) ;
#endif
			dwSeed = GetCurrentTime() ;

			pEconomiseur	=	CEconomiseur::GetEconomiseur() ;

			InitSave	=	FALSE ;
			pEconomiseur->CEstParti( hWnd ) ;
    
			const BOOL	Res = pEconomiseur->RealizePalette() ;
			InitSave	=	TRUE ;
	    	break;
        	}

	case WM_PAINT :
		{
		pEconomiseur	=	CEconomiseur::GetEconomiseur() ;
		CRect R ;
		BeginPaint( hWnd, &Ps ) ;
		GetClientRect( hWnd, R ) ;
			
		CDC	Dc ;
		Dc.Attach( Ps.hdc ) ;
 		pEconomiseur->UpdateFenetre( Dc, R ) ;
		Dc.Detach() ;

		EndPaint( hWnd, &Ps ) ;
		}
		break ;
			
  case WM_ERASEBKGND:
     	if ( pEconomiseur->NoircirEcran )
      		return DefWindowProc( hWnd, msg, wParam, lParam ) ;
      	else
      		return TRUE ;

  case WM_PALETTECHANGED :
		  if ( (HWND)wParam == hWnd )
			  break ;
  case WM_QUERYNEWPALETTE :
		  {
		  pEconomiseur	=	CEconomiseur::GetEconomiseur() ;
		  const BOOL	Res = pEconomiseur->RealizePalette() ;
		  return Res  ;
		  }


	case WM_DISPLAYCHANGE :
	case WM_WINDOWPOSCHANGING :
	case WM_WINDOWPOSCHANGED :
	case WM_MOVE :
	case WM_SIZE :
		return 0 ;

	case WM_DESTROY:     
		pEconomiseur->Fini() ;
		// Pas de break !

	default :
		return DefScreenSaverProc(hWnd, msg, wParam, lParam);
	}


	return 0 ;
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
	switch( msg )
		{
		case WM_INITDIALOG :
			{
			AfxWinInit((HINSTANCE)hMainInstance, 0, "", SW_SHOW ) ;
			CEconomiseur * pEco	=	CEconomiseur::GetEconomiseur() ;
			CPropertySheet	Prop ;

			pEco->LitPreferences() ;
			pEco->Configuration( &Prop ) ;

			if ( Prop.DoModal() == IDOK )
				{
				pEco->EcritPreferences() ;
				}

			EndDialog( hDlg, IDOK ) ;
			}
			return 0 ;
		default :
			return 0 ;
		}
}
