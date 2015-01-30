///////////////////////////////////////////////////////////////////////////////
//
//	MailNotify.CPP
//
//	This program displays a Window in the task bar notification tray.
//	It is written in C++ without the MFC in order to take the less possible
//	memory space
//
//	Author: Lucien PILLONI
//
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "afxtempl.h"
#include "resource.h"
#include "common.h"
#include "SetupDlg.h"
#include "DlgAccounts.h"
#include "CompteMail.h"
#include "MyApp.h"
#include "WarningWnd.h"
#include "mail.h"
#include "restriction.h"
#include "dlgNewMessages.h"
#include "deroulemailswnd.h"

CMyApp	zeApp ;
CArray<CCompteMail *,CCompteMail *>	Comptes ;
const TCHAR	NOTIFICATION[]	=	TEXT("Notification") ;
static const char TRANSPARENCY[]	=	"Transparency" ;
static const char BLEND[]			=	"Blend" ;

UINT	wPrivateMessage	=	RegisterWindowMessage( "LPI|MailNotify" ) ;

HWND		hwndMain ;
HINSTANCE	hInstance ;
int			noFlashIcon	=	0 ;
HANDLE		hThreadNotification = NULL ;
UINT	wIconNotificationMessage	=	::RegisterWindowMessage( "LPI:Mail notification:Tray bar notify message" ) ;
CString Texte ;
HBITMAP	hGauche, hDroite, hCentre ;
int			Decalage	=	0 ;
int noTimer ;
int LargeurGauche, LargeurDroite, LargeurCentre ;

#define TIMER_CHECK		2
#define TIMER_DEFILE	3

UINT	TableauIcones[]=
	{
	IDR_ICON_FLASHED, IDR_ICON_FLASHED_3, IDR_ICON_FLASHED_4,
	IDR_ICON_FLASHED_5, IDR_ICON_FLASHED_6,  IDR_ICON_FLASHED_7,
	IDR_ICON_FLASHED_8, IDR_MAINFRAME
	};


void DessineFenetre( HDC hDc)
{
	RECT R ;
	GetClientRect( hwndMain, &R ) ;

	HDC hMemDC = CreateCompatibleDC( hDc ) ;

	HBITMAP hOldBitmap	=	(HBITMAP)SelectObject( hMemDC, hGauche ) ;
	BitBlt( hDc, 0, 0, LargeurGauche, R.bottom-R.top, hMemDC, 0, 0, SRCCOPY ) ;

	int x	=	LargeurGauche ;

	SelectObject( hMemDC, hCentre ) ;

	for ( int i = LargeurGauche; i < R.right - R.left - LargeurDroite; i+= LargeurCentre )
		{
		BitBlt( hDc, x, 0, LargeurCentre, R.bottom-R.top, hMemDC, 0, 0, SRCCOPY ) ;
		x += LargeurCentre ;
		}

	SelectObject( hMemDC, hDroite ) ;
	BitBlt( hDc, R.right - R.left-LargeurDroite, 0, LargeurDroite, R.bottom-R.top, hMemDC, 0, 0, SRCCOPY ) ;

	SelectObject( hMemDC, hOldBitmap ) ;
	DeleteDC( hMemDC ) ;

	SelectObject( hDc, GetStockObject(ANSI_VAR_FONT )) ;
	SetTextColor( hDc, RGB(0,0,0) ) ;
	SetBkMode( hDc, TRANSPARENT ) ;
	
	R.left +=	LargeurGauche ;
	R.right -= LargeurDroite ;
	R.top += 2 ;
	R.bottom -= 2 ;

	HRGN	hRegion	=	::CreateRectRgn( R.left, R.top, R.right, R.bottom ) ;

	SelectClipRgn( hDc, hRegion ) ;

	DWORD dw =	GetTabbedTextExtent( hDc, (const char*)Texte,
												   Texte.GetLength(),
												   0, NULL ) ;

	int	Largeur = LOWORD( dw ) ;

	while  ( Decalage < -Largeur)
			Decalage += Largeur ;

	x	=	Decalage ;
	while ( x < R.right - LargeurDroite )
		{
		TextOut( hDc, x, 2, (const char*)Texte, Texte.GetLength() ) ;
		x += Largeur ;
		}

	SelectClipRgn( hDc, NULL ) ;
	DeleteObject( hRegion ) ;
}


/////////////////////////////////////////////////////////////////////////////
// Modifies the icon in the notification tray
/////////////////////////////////////////////////////////////////////////////
void ModifyNotificationIcon(UINT IdIcon)
{
	NOTIFYICONDATA tnd;
	memset( &tnd, 0, sizeof( tnd )) ;


	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= hwndMain ;
	tnd.uID			= 1;
	tnd.uFlags		= NIF_ICON ;
	tnd.hIcon		= LoadIcon( hInstance, MAKEINTRESOURCE( IdIcon )) ;
		
	Shell_NotifyIcon( NIM_MODIFY, &tnd);
}



/////////////////////////////////////////////////////////////////////////////
// SetTooltip
/////////////////////////////////////////////////////////////////////////////
void SetTooltip(LPCSTR Tooltip)
{
	NOTIFYICONDATA tnd;
	memset( &tnd, 0, sizeof( tnd )) ;


	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= hwndMain ;
	tnd.uID			= 1;
	tnd.uFlags		= NIF_TIP ;
	strncpy( tnd.szTip,  Tooltip, sizeof( tnd.szTip) ) ;
	tnd.szTip[sizeof( tnd.szTip)-1] = 0 ;
		
	Shell_NotifyIcon( NIM_MODIFY, &tnd);
}

/////////////////////////////////////////////////////////////////////////////
// GetEtatTouche
/////////////////////////////////////////////////////////////////////////////
BOOL	GetEtatTouche( UINT Touche )
	{
	BYTE	keyStates[256] ;
	GetKeyboardState( keyStates ) ;

	BYTE state	=	keyStates[Touche] ;

	return (state & 1 ) != 0 ;
	}

/////////////////////////////////////////////////////////////////////////////
// SetEtatTouche
/////////////////////////////////////////////////////////////////////////////
void	SetEtatTouche( UINT Touche, BOOL State )
	{
	BYTE	keyStates[256] ;
	GetKeyboardState( keyStates ) ;

	if ( State )
		keyStates[Touche]	|= 1 ;
	else
		keyStates[Touche]	&= 0xFE ;

	SetKeyboardState( keyStates ) ;
	}


/////////////////////////////////////////////////////////////////////////////
// Change the look of the icon
/////////////////////////////////////////////////////////////////////////////
void DoFlashKeyboardLed()
{


	keybd_event( VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY, 0 ) ;
    keybd_event( VK_SCROLL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0 ) ;
}


/////////////////////////////////////////////////////////////////////////////
// Change the look of the icon
/////////////////////////////////////////////////////////////////////////////
void DoFlashIcon()
{
	ModifyNotificationIcon( TableauIcones[noFlashIcon]) ;
	noFlashIcon ++ ;

	if ( noFlashIcon >= sizeof(TableauIcones)/sizeof(TableauIcones[0]))
		noFlashIcon	=	0 ;
}


/////////////////////////////////////////////////////////////////////////////
// Defile le message
/////////////////////////////////////////////////////////////////////////////
void DefileMessage()
	{
	// Place la fenetre de notification au dessus de la caption de la fenetre active
//	HWND	hWnd	=	GetForegroundWindow() ;
/*	RECT R ;
//	if ( IsWindow( hWnd ) && hWnd!=hwndMain )
//		{
//		GetWindowRect( hWnd, & R ) ;
//		}
//	else
		{
		R.left	=	0 ;
		R.top = 0 ;
		R.right	=	GetSystemMetrics( SM_CXSCREEN ) ;
		R.bottom = GetSystemMetrics( SM_CYSCREEN ) ;
		}
*/
	RECT RWindow ;
	GetClientRect( hwndMain, &RWindow ) ;
/*
	SetWindowPos( hwndMain, HWND_TOP,
					R.right - 16 - (RWindow.right-RWindow.top),
					R.top + 1, 0, 0,
					SWP_NOSIZE|SWP_NOACTIVATE ) ;
				   
*/
	// Dessine le message deroulant
	HDC	hDC	=	GetDC( hwndMain ) ;
	HDC hMemDC	=	CreateCompatibleDC( hDC ) ;
	HBITMAP hBitmap	=	CreateCompatibleBitmap( hDC, RWindow.right-RWindow.left, RWindow.bottom-RWindow.top ) ;
	HBITMAP hOld	=	(HBITMAP)SelectObject( hMemDC, hBitmap ) ;

	DessineFenetre( hMemDC ) ;
	BitBlt( hDC, 0, 0, RWindow.right-RWindow.left, RWindow.bottom-RWindow.top, hMemDC, 0, 0, SRCCOPY ) ;

	SelectObject( hMemDC, hOld ) ;
	DeleteObject( hBitmap ) ;
	DeleteDC( hMemDC ) ;

	ReleaseDC( hwndMain, hDC ) ;
	Decalage -- ;
	}


/////////////////////////////////////////////////////////////////////////////
//	DisplayMessageWindow
/////////////////////////////////////////////////////////////////////////////
void	DisplayMessageWindow( HWND hWnd /*LPCSTR Message */)
{
	DefileMessage() ;
}


/////////////////////////////////////////////////////////////////////////////
// threadNotification
//	Thread de notification, boucle tant que hThreadNotification != null
/////////////////////////////////////////////////////////////////////////////
DWORD WINAPI threadNotification(  LPVOID  )
	{
	// Animation de l'icone dans la tray bar
	if ( GetConfigurationInt( NOTIFICATION, "Animate Icon", TRUE ))
		noFlashIcon	=	0 ;

	while ( hThreadNotification )
		{
		// Change LED
		if ( GetConfigurationInt( NOTIFICATION, "Flash Scroll Lock", TRUE ))
			DoFlashKeyboardLed() ;

		// Flashing icon
		if ( GetConfigurationInt( NOTIFICATION, "Animate Icon", TRUE ))
			DoFlashIcon() ;

		// Sleep
		Sleep( GetTimerDelay( DELAY_FLASH )) ;

		// Change LED
		if ( GetConfigurationInt( NOTIFICATION, "Flash Scroll Lock", TRUE ))
			DoFlashKeyboardLed() ;
	
		// Flashing icon
		if ( GetConfigurationInt( NOTIFICATION, "Animate Icon", TRUE ))
			DoFlashIcon() ;

		//DefileMessage() ;

		Sleep( GetTimerDelay( DELAY_FLASH )) ;
		}

	ModifyNotificationIcon( IDR_MAINFRAME ) ;

	return 0 ;
	}

void Transparence( HWND hWnd )
{
	static const int Blend	=	GetConfigurationInt( TRANSPARENCY, BLEND, 70 ) ;
	if ( Blend == 100 )
		return ;

	typedef BOOL (WINAPI * FCT_SetLayeredWindowAttributes)(	HWND hwnd,           // handle to the layered window
													COLORREF crKey,      // specifies the color key
													BYTE bAlpha,         // value for the blend function
													DWORD dwFlags        // action
				);
	
	HINSTANCE	hLib	=	LoadLibrary( "user32" ) ;
	if ( ! hLib )
		return ;

	FCT_SetLayeredWindowAttributes fct	=	(FCT_SetLayeredWindowAttributes)GetProcAddress( hLib, "SetLayeredWindowAttributes" ) ;
	if ( ! fct )
		{
		FreeLibrary( hLib ) ;
		return ;
		}	

#ifndef WS_EX_LAYERED
#define WS_EX_LAYERED			0x00080000
#endif
#ifndef LWA_ALPHA
#define LWA_COLORKEY            0x00000001
#define LWA_ALPHA               0x00000002
#endif

	SetWindowLong(	hWnd, GWL_EXSTYLE,
					GetWindowLong( hWnd, GWL_EXSTYLE ) | WS_EX_LAYERED ) ;
	fct( hWnd, RGB( 255, 255, 192 ), (255*Blend)/100, LWA_COLORKEY|LWA_ALPHA ) ;

	FreeLibrary( hLib ) ;
}
/////////////////////////////////////////////////////////////////////////////
// StartNotification
//	Demarre les gadgets qui avertissent que des mails ont ete recus
/////////////////////////////////////////////////////////////////////////////
void	StartNotification()
	{
/*	if ( GetConfigurationInt( NOTIFICATION, "", TRUE ))
		{

		}
*/		
	DWORD	ThreadId ;
	hThreadNotification	=	CreateThread( NULL, 0, threadNotification, 0, 0, &ThreadId ) ;


	// Montre la fenetre des mails
	SetWindowPos( hwndMain, HWND_TOPMOST,
				  0, 0, 350, 16,
				  SWP_NOACTIVATE | SWP_SHOWWINDOW ) ;
	Transparence( hwndMain ) ;
	noTimer = SetTimer( hwndMain, TIMER_DEFILE, 750, NULL ) ;
	}

/////////////////////////////////////////////////////////////////////////////
// StopNotification
/////////////////////////////////////////////////////////////////////////////
void StopNotification()
	{
	if ( hThreadNotification )
		{
		hThreadNotification = NULL ;
		}

	KillTimer( hwndMain, noTimer ) ;
	ShowWindow( hwndMain, SW_HIDE ) ;
	}

/////////////////////////////////////////////////////////////////////////////
//	DisplayMessageWindow
/////////////////////////////////////////////////////////////////////////////
void	CheckMailAccounts(  )
{
	static BOOL	CheckEnCours	=	FALSE ;

	if ( CheckEnCours )
		return ;
	
	CheckEnCours	=	TRUE ;

	StopNotification() ;
	ModifyNotificationIcon( IDR_CHECK ) ;

	int NbMails	=	0 ;
	CString	Mails ;

	Texte.Empty() ;
	for ( int i = 0; i < Comptes.GetSize(); i++)
		{
		CCompteMail * pCompte = Comptes[i] ;
		pCompte->SupprimeMails() ;

		CString Tip	=	"Checking " + pCompte->Nom() ;
		SetTooltip( Tip ) ;

		const int Nb = pCompte->Check() ;
		NbMails	+= Nb ;
		}

	if ( NbMails == 0 )
		{
		ModifyNotificationIcon( IDR_MAINFRAME ) ;
		CTime	Time( CTime::GetCurrentTime()) ;
		SetTooltip( Time.Format( "No new mail, last check %H:%M:%S" ) ) ;
		}
	else
		{
		CString	Message ;
		Message.Format( NbMails > 1 ? "%d mails" : "%d mail", NbMails ) ;
		SetTooltip( Message ) ;

		for ( int i = 0; i <Comptes.GetSize(); i++)
			{
			CCompteMail * pCompte = Comptes[i] ;

			const int Nb	=	pCompte->GetNbMails() ;
			if ( Nb > 0 )
				{
				CString Compte ;
				//Compte.Format( " '%s' account: %d mails,", (const char*)pCompte->Nom(), Nb ) ;

				for ( int i = 0; i < Nb; i++)
					{
					const CMail * pMail	=	pCompte->GetMail( i ) ;
					CString Mail ;
					Mail.Format( "from:%s, %s,", (const char*)pMail->From(), (const char*)pMail->Subject()) ;
					Compte += Mail ;
					}

				Texte += Compte ;
				}
			}

		Texte += "...       " ;
		DisplayMessageWindow( hwndMain ) ; //, Mails ) ;
		StartNotification() ;
		}

	CheckEnCours	=	FALSE ;
}


/////////////////////////////////////////////////////////////////////////////
// OpenMenu
// Open the menu when the user clic on the icon
/////////////////////////////////////////////////////////////////////////////
void OpenMenu( HWND hWnd )
{
	static HMENU	hMenu = 0 ;

	if ( hMenu == 0 )
		{
		hMenu	=	LoadMenu( hInstance, MAKEINTRESOURCE( IDR_MENU )) ;

		if ( ! hMenu )
			return ;
		}

	HMENU hSubMenu	=	GetSubMenu( hMenu, 0 ) ;
	if ( ! hSubMenu )
		return ;

	POINT Point ;
	GetCursorPos( &Point ) ;
	TrackPopupMenu( hSubMenu, 
					TPM_RIGHTALIGN|TPM_BOTTOMALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
					Point.x, Point.y, 0, hWnd, NULL ) ;
}

/////////////////////////////////////////////////////////////////////////////
// OnIconNotificationMessage
// This funciton receives the icon notification message
/////////////////////////////////////////////////////////////////////////////
LONG OnIconNotificationMessage( HWND hwnd, WPARAM wParam, LPARAM lParam )
{
		switch( lParam )
		{
		case WM_RBUTTONDOWN :
			OpenMenu( hwnd ) ;
			break ;

		case WM_LBUTTONDBLCLK :
			CheckMailAccounts() ;
			break ;
		}

	return 0 ;
}


/////////////////////////////////////////////////////////////////////////////
// AddIcon
//	Add an icon in the icon notification tray
/////////////////////////////////////////////////////////////////////////////
void AddIcon( HWND hWnd, UINT IdIcon, UINT NotificationMessage)
{
	NOTIFYICONDATA tnd;
	memset( &tnd, 0, sizeof( tnd )) ;

	tnd.cbSize			= sizeof(NOTIFYICONDATA);
	tnd.hWnd			= hWnd;
	tnd.uID				= 1;
	strcpy( tnd.szTip, "Mail notification" ) ;

	tnd.uFlags			= NIF_MESSAGE | NIF_ICON | NIF_TIP ;
	tnd.uCallbackMessage= NotificationMessage ;
	tnd.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE( IdIcon )) ;
		
	Shell_NotifyIcon( NIM_ADD, &tnd);
}

/////////////////////////////////////////////////////////////////////////////
// OnTimer
//	Receives notification from the timer
/////////////////////////////////////////////////////////////////////////////
void OnTimer(HWND hWnd, UINT nIDEvent) 
{
	switch ( nIDEvent )
		{
		case TIMER_CHECK :
			// Time to check the mail
			CheckMailAccounts() ;
			break ;

		case TIMER_DEFILE :
			DefileMessage() ;
			break ;
		}
}



/////////////////////////////////////////////////////////////////////////////
// HandleCommand
/////////////////////////////////////////////////////////////////////////////
void HandleCommand( HWND hWnd, WPARAM wParam )
{
	switch( wParam )
		{
		case ID_CHECKMAILNOW :
			CheckMailAccounts() ;
			break ;

		case ID_SHOWMESSAGES :
			//DisplayMessageWindow( hwndMain ) ;
			ShowWindow( hwndMain, SW_HIDE ) ;
			break ;

		case IDM_ACCOUNTS:
			{
			CDlgAccounts dlg ;
			dlg.DoModal() ;
			}
			break ;

		case IDM_SETUP :
			{
			CSetupDlg	Dlg ;
			Dlg.DoModal() ;
			SetTimer( hwndMain, TIMER_CHECK, GetTimerDelay(DELAY_CHECK), NULL ) ;
			}
			break ;

		case IDM_QUIT:
			DestroyWindow( hWnd ) ;
			break ;
		}
}

/////////////////////////////////////////////////////////////////////////////
// OnPrivateMessage
//	Traitement du message prive qui permet la communication entre fenetres
//	a l'interieur de ce programme
//	
/////////////////////////////////////////////////////////////////////////////
LONG	OnPrivateMessage( HWND hwnd, UINT wParam, LONG lParam )
{
	switch( wParam )
		{
		case LAUNCHED_MAIL_CLIENT :
			StopNotification() ;
			break ;

		case CLOSED_MAILS_WINDOW :
			CheckMailAccounts() ;
			break ;
		}
	return 0 ;
}



/////////////////////////////////////////////////////////////////////////////
// This is the Wndproc where all message to our main window arrive
/////////////////////////////////////////////////////////////////////////////
LONG APIENTRY WndProc (HWND hwnd, UINT msg, UINT wParam, LONG lParam)
{
	switch( msg )
		{
		case WM_CREATE :
			// Add the icon in the notification tray
			AddIcon( hwnd, IDR_MAINFRAME, wIconNotificationMessage ) ;

			// Set the timer
			SetTimer( hwnd, TIMER_CHECK, GetTimerDelay(DELAY_CHECK), NULL ) ;
			break ;

		case WM_TIMER :
			OnTimer( hwnd, wParam ) ;
			break ;

		case WM_COMMAND:
			HandleCommand( hwnd, wParam ) ;
			break ;


		case WM_PAINT :
			{
			PAINTSTRUCT Ps ;
			HDC	hdc =	BeginPaint( hwnd, &Ps ) ;

			DessineFenetre( hdc ) ;

			EndPaint( hwnd, &Ps ) ;
			}
			break ;

		case WM_DESTROY :
			{
			NOTIFYICONDATA tnd;
			memset( &tnd, 0, sizeof( tnd )) ;

			tnd.cbSize		= sizeof(NOTIFYICONDATA);
			tnd.hWnd		= hwnd;
			tnd.uID			= 1;
			
			Shell_NotifyIcon( NIM_DELETE, &tnd);
			PostQuitMessage(0) ;
			}
			break ;

		case WM_NCHITTEST:
			{
			int xPos = LOWORD(lParam); 
			int yPos = HIWORD(lParam); 
		
			return HTCAPTION ;	
			//return DefWindowProc( hwnd, msg, wParam, lParam ) ;
			}
			break ;

		default :
			if ( msg == wIconNotificationMessage )
				return OnIconNotificationMessage(hwnd, wParam, lParam) ;
			else
				if ( msg	==	wPrivateMessage )
					return OnPrivateMessage( hwnd, wParam, lParam ) ;
			else
				return DefWindowProc( hwnd, msg, wParam, lParam ) ;
		}
	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
//	Ecriture des comptes mail dans le fichier de configuration//
///////////////////////////////////////////////////////////////////////////////
void	EcritComptesMails()
	{
	for ( int i = 0; i < Comptes.GetSize(); i++)
		{
		CCompteMail*	pCompte =	Comptes[i] ;
		if ( pCompte )
			{	
			CString	SectionName	;
			SectionName.Format( "MailAccount#%d", i ) ;
			WriteConfigurationString( SectionName, "Name", pCompte->Nom()) ;
			WriteConfigurationString( SectionName, "Server", pCompte->Serveur()) ;
			WriteConfigurationInt( SectionName, "Port", pCompte->Port()) ;
			WriteConfigurationString( SectionName, "UserName", pCompte->UserName()) ;
			WriteConfigurationString( SectionName, "Password", pCompte->Password()) ;
			WriteConfigurationInt( SectionName, "Nb Restrictions", pCompte->GetNbRestrictions()) ;

			SectionName.Format( "Restrictions#%d.%s", i, (LPCSTR)pCompte->Nom() ) ;

			for ( int j = 0; j < pCompte->GetNbRestrictions(); j++ )
				{
				CRestriction*	pRestriction	=	pCompte->GetRestriction( j ) ;
				WriteConfigurationInt( SectionName, "Rule", (int)pRestriction->GetRule()) ;
				WriteConfigurationString( SectionName, "Text", pRestriction->GetText()) ;
				}
			}
		}

	WriteConfigurationInt( "MailAccounts", "Number", Comptes.GetSize()) ;
	}

///////////////////////////////////////////////////////////////////////////////
//	Lecture des comptes mail dans le fichier de configuration//
///////////////////////////////////////////////////////////////////////////////
void	LitComptesMails()
	{
	const int Nb	=	GetConfigurationInt( "MailAccounts", "Number", 0 ) ;

	for ( int i = 0; i < Nb; i++)
		{
		CString	SectionName	;
		SectionName.Format( "MailAccount#%d", i ) ;

		CString	Name	=	GetConfigurationString( SectionName, "Name", "" ) ;
		CString Server	=	GetConfigurationString( SectionName, "Server", "" ) ;
		int		Port	=	GetConfigurationInt( SectionName, "Port", 110 ) ;
		CString UserName=	GetConfigurationString( SectionName, "UserName", "" ) ;
		CString Password=	GetConfigurationString( SectionName, "Password", "") ;

		CCompteMail*	pCompte	=	new CCompteMail( Name, Server, Port, UserName, Password ) ;
		
		int NbRestrictions	=	GetConfigurationInt( SectionName, "Nb Restrictions", 0) ;

		SectionName.Format( "Restrictions#%d.%s", i, (LPCSTR)pCompte->Nom() ) ;

		for ( int j = 0; j < NbRestrictions; j++ )
			{
			int	Rule	=	GetConfigurationInt( SectionName, "Rule", 0) ;
			CString	Text=	GetConfigurationString( SectionName, "Text", "" ) ;

			CRestriction*	pRestriction	=	new CRestriction( (CRestriction::T_RULE)Rule, Text ) ;
			pCompte->AddRestriction( pRestriction ) ;
			}
			
		Comptes.Add( pCompte ) ;
		}

	}


///////////////////////////////////////////////////////////////////////////////
// This is the programm entry point, standard windows parameters.
///////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	if ( MultipleInstances())
		{
		ExitInstance() ;
		return 0 ;
		}

	LitComptesMails() ;

    MSG         msg;
    WNDCLASS    wndclass;

	hInstance	=	hInst ;
    
    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = (WNDPROC)WndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = hInst;
    wndclass.hIcon         = LoadIcon (hInst, szAppName);
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = szClassName ;

	hDroite	=	LoadBitmap( hInst, MAKEINTRESOURCE( IDB_DROITE )) ;
	hGauche =	LoadBitmap( hInst, MAKEINTRESOURCE( IDB_GAUCHE )) ;
	hCentre	=	LoadBitmap( hInst, MAKEINTRESOURCE( IDB_CENTRE )) ;
	BITMAP Bitmap ;
	GetObject( hGauche, sizeof( Bitmap ), &Bitmap ) ;
	LargeurGauche	=	Bitmap.bmWidth ;

	GetObject( hDroite, sizeof( Bitmap ), &Bitmap ) ;
	LargeurDroite	=	Bitmap.bmWidth ;

	GetObject( hCentre, sizeof( Bitmap ), &Bitmap ) ;
	LargeurCentre	=	Bitmap.bmWidth ;


	if (!RegisterClass (&wndclass))
		return FALSE;
			
	hwndMain = CreateWindowEx ( WS_EX_TOOLWINDOW,
								szClassName,
								szAppName,
								WS_POPUP | WS_CLIPCHILDREN,
								0, 0,
								250,16,
								NULL, NULL, hInst, NULL);

	AfxWinInit( (HINSTANCE)hInst, 0, "", SW_SHOW ) ;
	AfxSetResourceHandle( (HINSTANCE)hInst ) ;

	zeApp.InitInstance() ;
	
    if (!hwndMain)
		return FALSE;
    	
    while (GetMessage (&msg, NULL, 0, 0))
		{
		TranslateMessage (&msg);
        DispatchMessage (&msg);
		}

	ExitInstance() ;
	
	EcritComptesMails() ;

	StopNotification() ;

	return msg.wParam;

    lpCmdLine; // Just to resolve reference
}
