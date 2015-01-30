/*  Economiseur generique
 */
#include "stdafx.h"
#include <scrnsave.h>
#include "economiseur.h"


DWORD	dwSeed ;

COLORREF	CouleurMessage ;
int			Sens ;
BOOL		VersionEnregistree	=	FALSE ;

CWinApp	ZeApp ;

///////////////////////////////////////////////////////////////////////////////
// Verifie que c'est une version enregistree ou que c'est la machine a lulu
///////////////////////////////////////////////////////////////////////////////
BOOL VerifVersion()
{
//	char	Buffer[100] ;
//	DWORD	Taille	;
	time_t	tim ;
	struct	tm *	ptm ;

	if ( fChildPreview )
		return TRUE ;

/*	// Si c'est moi, je vais quand meme pas payer...
	Taille	=	sizeof( Buffer ) ;
	GetUserName( Buffer, &Taille) ;

	CharUpper( Buffer ) ;

	for ( UINT i = 0; i < strlen( Buffer ); i++ )
		Buffer[i] ++ ;

	if ( lstrcmp( Buffer, "QJMMPOJ" ) == 0)
		return TRUE ;


	if ( lstrcmp( Buffer, "MVDJFO" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "MVMV" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "MQ" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "MQJ" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "CPIHBSE" ) == 0 )
		return TRUE ;
*/
	// Verification de la date
	time( &tim ) ;
	ptm	=	localtime( &tim ) ;

	if ( ptm->tm_year >= 98 && ptm->tm_mon >= 1 && ptm->tm_mday >= 3 )
		{
		if ( ! fChildPreview )
			{
			MessageBeep( MB_ICONSTOP ) ;
			MessageBox( 0, "This shareware program is for test only. You had time enough to test it. It is now time for you to obtain the registered version. Please check the configuration box.",
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
BOOL WINAPI ScreenSaverConfigureDialog (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		{
		CEconomiseur* pEco	=	CEconomiseur::GetEconomiseur() ;
		AfxWinInit((HINSTANCE)hMainInstance, 0, "", SW_SHOW ) ;
		AfxSetResourceHandle( (HINSTANCE)hMainInstance ) ;
		
		CPropertySheet	Prop ;

		pEco->LitPreferences() ;
		pEco->Configuration(  &Prop ) ;

		if ( Prop.DoModal() == IDOK )
			pEco->EcritPreferences() ;

		EndDialog( hDlg, TRUE ) ;
		}
		return TRUE;

	default:
		return FALSE;
    }
}




