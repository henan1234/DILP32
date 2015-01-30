// TapisserieSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Resource.h"
#include "tapisserie v2.h"
#include "TapisserieSheet.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTapisserieSheet
const	UINT	CTapisserieSheet::_wTaskBarNotify =	RegisterWindowMessage( "LPI:CTapisserieSheet:Taskbar notification" ) ;
CTapisserieSheet*	CTapisserieSheet::_pDlg	=	0 ;

/////////////////////////////////////////////////////////////////////////////
// CTapisserieSheet
void CTapisserieSheet::ChangeTray( UINT Message, HICON hIcone )
{
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	tnd.hIcon		= hIcone ;
	
	LoadString( AfxGetResourceHandle(), /*CMonAppli::Enregistree ? IDS_TIP_ENREGISTREE:*/IDS_TIP, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon(Message, &tnd);
}


IMPLEMENT_DYNAMIC(CTapisserieSheet, CPropertySheet)

CTapisserieSheet::CTapisserieSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CTapisserieSheet::CTapisserieSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CTapisserieSheet::~CTapisserieSheet()
{
}


BEGIN_MESSAGE_MAP(CTapisserieSheet, CPropertySheet)
	ON_REGISTERED_MESSAGE(_wTaskBarNotify, OnTaskBarNotify )
	//{{AFX_MSG_MAP(CTapisserieSheet)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTapisserieSheet message handlers

int CTapisserieSheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	AfxGetApp()->m_pMainWnd	=	this ;
	
	// Cacher la fenetre
	SetWindowPos( &CWnd::wndTop,
					::GetSystemMetrics( SM_CXSCREEN),
					::GetSystemMetrics( SM_CYSCREEN ),
					0, 0, SWP_NOSIZE | SWP_NOZORDER ) ;	

	ShowWindow( SW_HIDE );
	// Ajouter l'icone dans la barre de notification
	HICON	hIcone	=	AfxGetApp()->LoadIcon( IDI_TASKBAR ) ;
	ChangeTray( NIM_ADD, hIcone ) ;
	DestroyIcon( hIcone ) ;
	

	ModifyStyle( WS_SYSMENU, 0 ) ;
	
	const LONG	Style	=	::GetWindowLong( m_hWnd, GWL_EXSTYLE ) ;
	::SetWindowLong( m_hWnd, GWL_EXSTYLE, Style | WS_EX_TOOLWINDOW	) ;

	int res = SetTimer( 1, 60000, NULL ) ;

	// On va cacher la fenetre
	res =	SetTimer( 2, 200, NULL ) ;

	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CTapisserieSheet::OnDestroy() 
{
	CPropertySheet::OnDestroy();
	
	ChangeTray( NIM_DELETE, NULL );
}


LRESULT CTapisserieSheet::OnTaskBarNotify( WPARAM wParam, LPARAM lParam )
{
	switch (lParam)
	{
	case WM_RBUTTONDOWN :
		{
		// Afficher le menu 
		CMenu Menu ;
		Menu.LoadMenu( IDR_MENU ) ;

		CPoint	Pt ;
		GetCursorPos( &Pt );

		Menu.GetSubMenu(0)->TrackPopupMenu( TPM_RIGHTALIGN | TPM_RIGHTBUTTON,
										  Pt.x, Pt.y,
										  this
										) ;
		}
		break ;

	case WM_LBUTTONDBLCLK :
		{
		CPage2*	pPage	=	(CPage2*)GetPage(1) ;
		ASSERT_VALID( pPage ) ;
		pPage->ChangeMaintenant() ;
		break ;
		}
	}

	return 0 ;
}

BOOL CTapisserieSheet::OnCommand( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
		{
		case ID_F_CONFIGURATION :
			{
			// Montrer la fenetre
			KillTimer(0) ;
			ShowWindow( SW_SHOW ) ;
			CRect	R ;
			GetClientRect( R ) ;
			SetWindowPos( &wndTop, (GetSystemMetrics( SM_CXSCREEN ) - R.Width())/2,
								   (GetSystemMetrics( SM_CYSCREEN ) - R.Height())/2,
								   0,0,
						 SWP_NOSIZE ) ;
			}
			break ;

		case ID_F_CHANGERMAINTENANT :
			{
			CPage2*	pPage	=	(CPage2*)GetPage(1) ;
			ASSERT_VALID( pPage ) ;
			pPage->ChangeMaintenant() ;
			}
			break ;

		case ID_F_FERMER :
			EndDialog(TRUE) ;
			break ;

		case IDOK :
			ShowWindow( SW_HIDE ) ;
			SetTimer( 1, 60000, NULL ) ;
			break ;

		case IDCANCEL :
		default :
			return CPropertySheet::OnCommand( wParam, lParam ) ;
		}

	return TRUE ;
}


void CTapisserieSheet::OnTimer(UINT nIDEvent) 
{
	CPropertySheet::OnTimer(nIDEvent);

	switch( nIDEvent )
	{
	case	2 :
		{
		CWnd	*	pChild	=	GetDlgItem( IDCANCEL ) ;
		if ( pChild )
			pChild->ShowWindow( SW_HIDE ) ;

		pChild	=	GetDlgItem( IDHELP ) ;
		if ( pChild )
			pChild->ShowWindow( SW_HIDE ) ;


		pChild	=	GetDlgItem( 0x3021 ) ;
		if ( pChild )
			pChild->ShowWindow( SW_HIDE ) ;

		ShowWindow( SW_HIDE ) ;
		KillTimer( 2 ) ;
		}
		break ;

	case	1 :
		{
		CPage2*	pPage	=	(CPage2*)GetPage(1) ;
		ASSERT_VALID( pPage ) ;
		pPage->OnTimer(1) ;
		break ;
		}
	}
}

BOOL CTapisserieSheet::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style	=	cs.style & ( ~ WS_VISIBLE ) ;
	cs.x		=	GetSystemMetrics( SM_CXSCREEN ) ;
	
	return CPropertySheet::PreCreateWindow(cs);
}
