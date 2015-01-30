//
//	Tapisserie
//
#include "stdafx.h"
#include "resource.h"
#include <winreg.h>
#include "tapisserie.h"
#include "TapisserieSheet.h"


CTapisserie::CTapisserie( const char * Nom, BOOL Mosaique, int NbMinutes, BOOL Change, COLORREF Couleur )
{
	_Nom		= Nom ;
	_Mosaique	= Mosaique ;
	_NbMinutes	= NbMinutes ;
	_ChangeCouleur	=	Change ;
	_Couleur	=	Couleur ;
	_hBitmap	=	NULL ;
}


CTapisserie::~CTapisserie()
	{
	if ( _hBitmap )
		DeleteObject( _hBitmap ) ;
	}

void	CTapisserie::Mosaique( BOOL Mosaique )
{
	_Mosaique	=	Mosaique ;
}

		
void	CTapisserie::Active()
{
	CWaitCursor	Wait ;
	
	NOTIFYICONDATA tnd;
	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= AfxGetMainWnd()->m_hWnd ;
	tnd.uID			= 1;
	tnd.uFlags		= NIF_ICON;
	tnd.uCallbackMessage	= CTapisserieSheet::_wTaskBarNotify ;
	tnd.hIcon		= AfxGetApp()->LoadIcon( IDI_ICON1 ) ;
	Shell_NotifyIcon(NIM_MODIFY, &tnd);
	

	BOOL	ScrActif ;
	int		ScrTimeOut ;

	::SystemParametersInfo( SPI_GETSCREENSAVEACTIVE, 0, (void far *)&ScrActif, 0 ) ;
	::SystemParametersInfo( SPI_GETSCREENSAVETIMEOUT, 0, (void far *)&ScrTimeOut, 0 ) ;

	const char	* strTile	;
	if ( _Mosaique )
		strTile	=	"1" ;
	else
		strTile	=	"0" ;
	
	if ( _ChangeCouleur )
		{
		INT	Indice		=	COLOR_DESKTOP ;
		
		SetSysColors( 1, &Indice, &_Couleur ) ;
		}

	::WriteProfileString( "Desktop", "TileWallPaper", _Mosaique ? "1" : "0" ) ;

    // And in registry
    HKEY  hKey;
    LONG lRet = RegOpenKeyEx ( HKEY_CURRENT_USER, "Control Panel\\Desktop", 0, KEY_SET_VALUE, &hKey);

    if ( lRet == ERROR_SUCCESS )
		{
		// Write this new value in registry
		lRet = RegSetValueEx( hKey, "TileWallPaper",
							NULL, REG_SZ, (LPBYTE)(const char *)strTile, 
							strlen(strTile) + 1 );
		}

	::SystemParametersInfo( SPI_SETDESKWALLPAPER, 0, (void far *)(LPCSTR)_Nom, SPIF_UPDATEINIFILE ) ;

	::SystemParametersInfo( SPI_SETSCREENSAVEACTIVE, ScrActif, 0, 0 ) ;
	::SystemParametersInfo( SPI_SETSCREENSAVETIMEOUT, ScrTimeOut, 0, 0 ) ;


	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= AfxGetMainWnd()->m_hWnd ;
	tnd.uID			= 1;
	tnd.uFlags		= NIF_ICON;
	tnd.uCallbackMessage	= CTapisserieSheet::_wTaskBarNotify ;
	tnd.hIcon		= AfxGetApp()->LoadIcon( IDI_TASKBAR ) ;
	Shell_NotifyIcon(NIM_MODIFY, &tnd);
	
}


HBITMAP	CTapisserie::GetBitmap()
	{
	if( ! _hBitmap )
		_hBitmap =	(HBITMAP)LoadImage( AfxGetInstanceHandle(),
										   Nom(),
										   IMAGE_BITMAP,
										   32, 32,
										   LR_LOADFROMFILE ) ;
	return _hBitmap ;
	}

