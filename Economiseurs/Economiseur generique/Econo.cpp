/*  Economiseur generique
 */
#include "stdafx.h"
#include <scrnsave.h>
#include "economiseur.h"
#include "..\..\Classes\RegistrationKey.h"

const char *	MessageCopyright	=	"Version ShareWare non enregistrée, (c) Lucien PILLONI 1995" ;
//const char *	MessageCopyright	=	"Copyright (c) Lucien PILLONI 1995. Ceci est une version de démonstration non destinée à la distribution" ;

DWORD	dwSeed ;

COLORREF	CouleurMessage ;
int			Sens ;
BOOL		VersionEnregistree	=	FALSE ;

CWinApp	ZeApp ;

CRegistrationKey		Key() ;

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
			SetWindowPos( hWnd, 0, 0, 0, GetSystemMetrics( SM_CXSCREEN ) / 2,
						  GetSystemMetrics( SM_CYSCREEN ), SWP_NOMOVE ) ;
			SetWindowLong( hWnd, GWL_STYLE,
							GetWindowLong( hWnd, GWL_STYLE ) | WS_THICKFRAME ) ;
#endif

			dwSeed = GetCurrentTime() ;

			pEconomiseur	=	CEconomiseur::GetEconomiseur() ;

			InitSave	=	FALSE ;
			pEconomiseur->CEstParti( hWnd ) ;
    
			  {
			  HDC	hDC	=	GetDC( hWnd ) ;
			  CDC	Dc ;
			  Dc.Attach( hDC ) ;
			  const BOOL	Res = pEconomiseur->RealizePalette(Dc) ;
			  Dc.Detach() ;
			  ReleaseDC( hWnd, hDC ) ;
			  
			  }
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

	case WM_TIMER :
		{
		pEconomiseur->OnTimer( (UINT)wParam ) ;
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
		  HDC	hDC	=	GetDC( hWnd ) ;
		  CDC	Dc ;
		  Dc.Attach( hDC ) ;
		  const BOOL	Res = pEconomiseur->RealizePalette(Dc) ;
		  Dc.Detach() ;
		  ReleaseDC( hWnd, hDC ) ;
		  return Res  ;
		  }

		return DefScreenSaverProc(hWnd, msg, wParam, lParam);

	case WM_DISPLAYCHANGE :
		return 0 ;

	case WM_DESTROY:     
		pEconomiseur->Fini() ;
		// Pas de break !

	default :
		return DefScreenSaverProc(hWnd, msg, wParam, lParam);
	}


	return 0 ;
}


///////////////////////////////////////////////////////////////////////////////
// ScreenSaverConfigureDialog
// WndProc de la boite de configuration de l'economiseur
// On la remplace par une propertysheet
///////////////////////////////////////////////////////////////////////////////
BOOL WINAPI ScreenSaverConfigureDialog (HWND hDlg, UINT msg, WPARAM , LPARAM )
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
		CEconomiseur* pEco	=	CEconomiseur::GetEconomiseur() ;
		AfxWinInit((HINSTANCE)hMainInstance, 0, "", SW_SHOW ) ;
		AfxSetResourceHandle( (HINSTANCE)hMainInstance ) ;
		
		pEco->Configure() ;

		EndDialog( hDlg, TRUE ) ;
		}
		return TRUE;

	default:
		return FALSE;
    }
}




