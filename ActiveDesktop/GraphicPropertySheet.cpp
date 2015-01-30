// GraphicPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "activedesktop.h"
#include "GraphicPropertySheet.h"
#include "FenetreTransparente.h"
#include "Preferences.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL	Attente			=	FALSE ;

#define PLAGE_IMAGES 10000

CGraphicPropertySheet * CGraphicPropertySheet::_pZeOnlyOuane = 0 ;
/////////////////////////////////////////////////////////////////////////////
// CGraphicPropertySheet

IMPLEMENT_DYNAMIC(CGraphicPropertySheet, CPropertySheet)
UINT	CGraphicPropertySheet::_wTaskBarNotify	=	RegisterWindowMessage( "Message from Taskbar to ActiveDesktop, Lucien PILLONI") ;


DWORD	WINAPI	AttenteEdition( LPVOID	lp )
	{
	CGraphicPropertySheet*	pDlg	=	(CGraphicPropertySheet*)lp ;
	WaitForSingleObject( pDlg->_hProcessEdition, INFINITE ) ;
	pDlg->FinEdition() ;
	return 0 ;
	}


CGraphicPropertySheet::CGraphicPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	ASSERT( _pZeOnlyOuane == 0 ) ;
	_pZeOnlyOuane	=	this ;
	_bPermissionMenu=	TRUE ;
}

CGraphicPropertySheet::CGraphicPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CGraphicPropertySheet::~CGraphicPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CGraphicPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGraphicPropertySheet)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(_wTaskBarNotify, OnTaskBarNotify )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicPropertySheet message handlers

int CGraphicPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Ajouter une icone dans la barre de tache
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	tnd.hIcon		= LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME )) ;
	
	LoadString( AfxGetResourceHandle(), IDS_TIP, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon( NIM_ADD, &tnd);

	_pFenetreTransparente	=	new CFenetreTransparente() ;

	_pFenetreTransparente->CreateEx( 0,
									 AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW, LoadCursor( NULL, IDC_ARROW), (HBRUSH)GetStockObject( NULL_BRUSH ) ),
									 "Whole Active desktop",
									 WS_POPUP | WS_VISIBLE,
									 0, 0, 100,100,
									 NULL,
									 NULL,
									 NULL
									 ) ;

	_pFenetreTransparente->SetBitmap(CPreferences::ImageCourante()) ;
	_pFenetreTransparente->SetWindowPos( &wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE ) ;

	// On va cacher la fenetre
	SetTimer( 2, 50, NULL ) ;
	
	return 0;
}


void CGraphicPropertySheet::OnDestroy() 
{
	CPropertySheet::OnDestroy();
	
	// Ajouter une icone dans la barre de tache
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	
	Shell_NotifyIcon( NIM_DELETE, &tnd);
}


LONG CGraphicPropertySheet::OnTaskBarNotify(UINT wParam, LONG lParam)
{
	switch( lParam )
		{
		case WM_LBUTTONDOWN :
			EditBackGroundImage() ;
			break ;

		case WM_RBUTTONDOWN :
			if ( _bPermissionMenu )
				{
				// Afficher le menu 
				CMenu Menu ;
				Menu.LoadMenu( IDR_MENU ) ;

				CMenu * pSousMenu	=	Menu.GetSubMenu(0 ) ;

				if ( pSousMenu )
					{
					CompleteSousMenu( pSousMenu ) ;

					CPoint	Pt ;
					GetCursorPos( &Pt );

					pSousMenu->TrackPopupMenu( TPM_RIGHTALIGN | TPM_RIGHTBUTTON,
														  Pt.x, Pt.y,
														  this
														) ;
					}
				}
				break ;
		}

	return 0 ;
}


void CGraphicPropertySheet::EditBackGroundImage()
{
	ShowWindow( SW_HIDE ) ;

	CString	LigneCommande( CPreferences::GetImageEditor() ) ;
	LigneCommande += " \"" ;
	LigneCommande += CPreferences::ImageCourante() ;
	LigneCommande += "\"" ;

	STARTUPINFO Startup ;
	memset( &Startup, 0, sizeof( Startup )) ;
	Startup.cb	=	sizeof( Startup ) ;

	PROCESS_INFORMATION Process ;

	CFileStatus	Status ;
	CFile::GetStatus( CPreferences::ImageCourante(), Status ) ;
	_DateAvantEdition	=	Status.m_mtime ;

	if ( !CreateProcess(	NULL,
					(char*)(const char *)LigneCommande, 
					NULL, NULL,
					TRUE,
					CREATE_DEFAULT_ERROR_MODE,
					NULL,
					NULL,
					&Startup, &Process ))
		{
		MessageBox( "Impossible de lancer" );
		}
	else
		{
		// Lancement reussi, mise en attente du programme
		NOTIFYICONDATA tnd;

		tnd.cbSize		= sizeof(NOTIFYICONDATA);
		tnd.hWnd		= m_hWnd;
		tnd.uID			= 1;

		tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
		tnd.uCallbackMessage	= _wTaskBarNotify ;
		tnd.hIcon		= LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_WAITING )) ;
		
		LoadString( AfxGetResourceHandle(), IDS_WAITING, tnd.szTip, sizeof(tnd.szTip));
		
		Shell_NotifyIcon( NIM_MODIFY, &tnd);

		Attente	=	TRUE ;
		_hProcessEdition	=	Process.hProcess ;
		DWORD Id ;

		PermetMenu( FALSE ) ;
		CreateThread( NULL, 0, AttenteEdition, (LPDWORD)this, 0, &Id ) ;
		}
}


void CGraphicPropertySheet::FinEdition()
{
	PermetMenu() ;

	// Noter la fin de l'attente
	Attente	=	FALSE ;
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	tnd.hIcon		= LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME )) ;
	
	LoadString( AfxGetResourceHandle(), IDS_TIP, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon( NIM_MODIFY, &tnd);

	if ( ImageModifiee())
		ChangeImageDeFond() ;
}


void CGraphicPropertySheet::OnTimer(UINT nIDEvent) 
{
	ShowWindow( SW_HIDE ) ;
	KillTimer( 2 ) ;
				
	CPropertySheet::OnTimer(nIDEvent);
}

BOOL CGraphicPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch( wParam )
		{
		case ID_CONFIGURE :
			ShowWindow( SW_SHOW ) ;
			break ;

		case ID_EDITERLIM :
			EditBackGroundImage() ;
			break ;

		case IDOK :
			ShowWindow( SW_HIDE ) ;
			break ;

		case IDCANCEL :
		case ID_APPLY_NOW :
			break ;

		case ID_EXIT :
			EndDialog( TRUE ) ;
			break ;

		default :
			if ( (int)wParam >= PLAGE_IMAGES  && (int)wParam < PLAGE_IMAGES +CPreferences::NbPages())
				{
				CPreferences::SetImageCourante( (int)wParam-PLAGE_IMAGES ) ;
				_pFenetreTransparente->SetBitmap(CPreferences::ImageCourante()) ;
				}
			return CPropertySheet::OnCommand(wParam, lParam);
		}

	return TRUE ;
}

void CGraphicPropertySheet::ChangeImageDeFond()
{
	ASSERT( _pFenetreTransparente ) ;
	_pFenetreTransparente->SetBitmap(CPreferences::ImageCourante()) ;
}


BOOL CGraphicPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	::DestroyWindow	( ::GetDlgItem( m_hWnd, IDCANCEL )) ;
	::DestroyWindow	( ::GetDlgItem( m_hWnd, ID_APPLY_NOW )) ;
	
	CString	Button ;
	Button.LoadString( IDS_BUTTON ) ;

	::SetWindowText( ::GetDlgItem( m_hWnd, IDOK ), Button ) ;
	return bResult;
}

BOOL CGraphicPropertySheet::ImageModifiee()
{
	CFileStatus	Status ;
	CFile::GetStatus( CPreferences::ImageCourante(), Status ) ;

	if (  Status.m_mtime == _DateAvantEdition )
		{
		CString Message ;
		CString Titre ;

		Message.LoadString( IDS_IMAGE_NON_MODIFIEE ) ;
		Titre.LoadString( IDS_TITRE ) ;

		MessageBeep( MB_ICONQUESTION ) ;
		if ( MessageBox( Message, Titre, MB_ICONQUESTION | MB_YESNO ) == IDNO )
			return FALSE ;
		}

	return TRUE ;
}

void CGraphicPropertySheet::CompleteSousMenu(CMenu * pMenu)
{
	CMenu * pSousMenu	= pMenu->GetSubMenu( 0 ) ;

	if ( ! pSousMenu )
		return ;

	pSousMenu->DeleteMenu( ID_F_DISPLAY_XXX, MF_BYCOMMAND ) ;

	const int NbImages	= CPreferences::NbPages() ;

	for ( int i = 0; i < NbImages; i++)
		pSousMenu->AppendMenu( MF_STRING, PLAGE_IMAGES+i, CPreferences::NomImage(i) ) ;
}

void CGraphicPropertySheet::PermetMenu(BOOL bPermission)
{
	ASSERT( _pZeOnlyOuane ) ;
	
	_pZeOnlyOuane->_bPermissionMenu 	=	bPermission ;
}
