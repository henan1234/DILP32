// tapisseriedlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "tapisserie.h"
#include "tapisseriedlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const	UINT	CTapisserieDlg::_wTaskBarNotify =	RegisterWindowMessage( "LPI:CTapisserieDlg:Taskbar notification" ) ;
CTapisserieDlg*	CTapisserieDlg::_pDlg	=	0 ;

/////////////////////////////////////////////////////////////////////////////
// CTapisserieDlg
void CTapisserieDlg::ChangeTray( UINT Message, HICON hIcone )
{
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	tnd.hIcon		= hIcone ;
	
	LoadString( AfxGetResourceHandle(), CMonAppli::Enregistree ? IDS_TIP_ENREGISTREE:IDS_TIP, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon(Message, &tnd);
}


IMPLEMENT_DYNAMIC(CTapisserieDlg, CPropertySheet)

CTapisserieDlg::CTapisserieDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	ASSERT( ! _pDlg ) ;
	_pDlg	=	this ;

	// Dans la version enregistree, on met la page about a la fin, c'est moins chiant
	if ( ! CMonAppli::Enregistree() )
		AddPage( &_APropos ) ;

	AddPage( &_Backgrounds ) ;
	AddPage( &_Savers ) ;

	if ( CMonAppli::Enregistree() )
		AddPage( &_APropos ) ;
}

CTapisserieDlg::~CTapisserieDlg()
{
	_pDlg	=	0 ;
}


BEGIN_MESSAGE_MAP(CTapisserieDlg, CPropertySheet)
	ON_REGISTERED_MESSAGE(_wTaskBarNotify, OnTaskBarNotify )

	//{{AFX_MSG_MAP(CTapisserieDlg)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTapisserieDlg message handlers
void CTapisserieDlg::OnTimer(UINT nIDEvent) 
{
	switch( nIDEvent )
		{
		case 1 :
			// Timer toutes les minutes pour gestion des backgrounds et economiseurs
			CPropBackground::OnTimer() ;
			CPropEconomiseurs::OnTimer() ;
			break ;

		case 2 :
			ShowWindow( SW_HIDE ) ;
			KillTimer( 2 ) ;
			break ;
		}
}

int CTapisserieDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Cacher les boutons inutiles
	GetDlgItem( IDCANCEL )->ShowWindow( SW_HIDE ) ;
	GetDlgItem( ID_APPLY_NOW )->ShowWindow( SW_HIDE ) ;
	GetDlgItem( ID_HELP )->ShowWindow( SW_HIDE );

	// Cacher la fenetre
	SetWindowPos( &CWnd::wndTop, ::GetSystemMetrics( SM_CXSCREEN), ::GetSystemMetrics( SM_CYSCREEN ),
				 	0, 0, SWP_NOSIZE | SWP_NOZORDER ) ;	

	ShowWindow( SW_HIDE );
	// Ajouter l'icone dans la barre de notification
	HICON	hIcone	=	AfxGetApp()->LoadIcon( IDI_TASKBAR ) ;
	ChangeTray( NIM_ADD, hIcone ) ;
	DestroyIcon( hIcone ) ;
	

	const LONG	Style	=	::GetWindowLong( m_hWnd, GWL_EXSTYLE ) ;
	::SetWindowLong( m_hWnd, GWL_EXSTYLE, Style | WS_EX_TOOLWINDOW	) ;

	int res = SetTimer( 1, 60000, NULL ) ;

	// On va cacher la fenetre
	res =	SetTimer( 2, 200, NULL ) ;

	return 0;
}

void CTapisserieDlg::OnDestroy() 
{
	ChangeTray( NIM_DELETE, NULL );
	CPropertySheet::OnDestroy();
}

LRESULT CTapisserieDlg::OnTaskBarNotify( WPARAM wParam, LPARAM lParam )
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
		CPropBackground::ChangeMaintenant() ;
		break ;
	}

	return 0 ;
}

BOOL CTapisserieDlg::OnCommand( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
		{
		case ID_F_CONFIGURATION :
			{
			// Montrer la fenetre
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
			CPropBackground::ChangeMaintenant() ;
			break ;

		case ID_F_FERMER :
			EndDialog(TRUE) ;
			break ;

		case IDOK :
			ShowWindow( SW_HIDE ) ;
			break ;

		case IDCANCEL :
		default :
			return CPropertySheet::OnCommand( wParam, lParam ) ;
		}

	return TRUE ;
}


void	CTapisserieDlg::Icone( UINT IdIcone )
{
	HICON	hIcone	=	AfxGetApp()->LoadIcon( IdIcone ) ;
	ASSERT( hIcone ) ;
	ASSERT( _pDlg ) ;

 	_pDlg->ChangeTray( NIM_MODIFY, hIcone ) ;

	DestroyIcon( hIcone ) ;	
}
