// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Jibe96.h"
#include "Jibe96Doc.h"
#include "Jibe96View.h"

#include "MainFrm.h"
#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define AUTOHIDETIMERINTERVAL 400
#define SGN(x)		( (x) > 0 ? 1 : (x) < 0 ? -1 : 0 )

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
UINT CMainFrame::_AppBarCallBackMessage	=	RegisterWindowMessage( "LULU/Jibe/MainFrame/AppBarCallBackMessage" ) ;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_INITMENU()
	ON_REGISTERED_MESSAGE( _AppBarCallBackMessage, OnAppBarCallBack )
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	_AutoHide	=	TRUE ;
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style	=	WS_POPUP | WS_BORDER | WS_SYSMENU ;
	cs.dwExStyle|=	WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE ;

	if ( cs.hMenu )
		::DestroyMenu( cs.hMenu ) ;

	cs.hMenu	=	0 ;
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);
	SetTimer( 1, 900, 0 ) ;

	ShowWindow( SW_HIDE ) ;
	m_bAutoMenuEnable	=	FALSE ;
	return 0;
}

// AppBarCallback - processes notification messages sent by the system. 
// hwndAccessBar - handle of the appbar 
// uNotifyMsg - identifier of the notification message 
// lParam - message parameter 
LRESULT CMainFrame::OnAppBarCallBack( WPARAM wParam, LPARAM lParam )
{
	HWND	hwndAccessBar	=	m_hWnd ;
    UINT	uNotifyMsg		=	wParam ;
	APPBARDATA abd; 
    UINT uState	; 
 
    abd.cbSize = sizeof(abd); 
    abd.hWnd = hwndAccessBar; 

    uState = ::SHAppBarMessage(ABM_GETSTATE, &abd); 
 
    switch (uNotifyMsg)
		{ 
        case ABN_STATECHANGE: 
		    // Check to see if the taskbar's always-on-top state has 
            // changed and, if it has, change the appbar's state 
            // accordingly. 
            ::SetWindowPos(hwndAccessBar, 
                (ABS_ALWAYSONTOP & uState) ? HWND_TOPMOST : HWND_BOTTOM, 
                0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); 
            break; 
 
        case ABN_FULLSCREENAPP: 
 
            // A full screen application has started, or the last full 
            // screen application has closed. Set the appbar's 
            // Z order appropriately. 
            if (lParam)
				{
				::SetWindowPos(hwndAccessBar, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE); 
    			}
			else
				{ 
                if (uState & ABS_ALWAYSONTOP) 
                    ::SetWindowPos(hwndAccessBar, HWND_TOPMOST, 
                        0, 0, 0, 0, 
                        SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				} 
 
        case ABN_POSCHANGED: 
            // The taskbar or another appbar has changed its 
            // size or position. 
            AppBarPosChanged(&abd); 
            break; 
    } 

	return 0 ;
} 
 
  
// AppBarPosChanged - adjusts the appbar's size and position. 
// pabd - address of an APPBARDATA structure that contains information 
//     used to adjust the size and position 
void PASCAL CMainFrame::AppBarPosChanged(PAPPBARDATA pabd) 
{ 
    RECT rc; 
    RECT rcWindow; 
    int iHeight; 
    int iWidth; 
 
    rc.top = 0; 
    rc.left = 0; 
    rc.right = GetSystemMetrics(SM_CXSCREEN) + 2 * GetSystemMetrics( SM_CXDLGFRAME ) ; 
    rc.bottom = GetSystemMetrics(SM_CYSCREEN)+ 2 * GetSystemMetrics( SM_CYDLGFRAME ) ; 
 
    ::GetWindowRect(pabd->hWnd, &rcWindow); 
    iHeight = rcWindow.bottom - rcWindow.top; 
    iWidth = rcWindow.right - rcWindow.left; 
 
    switch (GetSide())
		{ 
        case ABE_TOP: 
            rc.bottom = rc.top + iHeight; 
            break; 
 
        case ABE_BOTTOM: 
            rc.top = rc.bottom - iHeight; 
            break; 
 
        case ABE_LEFT: 
            rc.right = rc.left + iWidth; 
            break; 
 
        case ABE_RIGHT: 
            rc.left = rc.right - iWidth; 
            break; 
        } 

        AppBarQuerySetPos(GetSide(), &rc, pabd); 
} 

// AppBarQuerySetPos - sets the size and position of an appbar. 
// uEdge - screen edge to which the appbar is to be anchored 
// lprc - current bounding rectangle of the appbar 
// pabd - address of APPBARDATA structure with the hWnd and 
//     cbSize members filled 
void PASCAL CMainFrame::AppBarQuerySetPos(UINT uEdge, LPRECT lprc, PAPPBARDATA pabd) 
{ 
	const CSize	Taille =	GetSize() ;

	// La fenetre est cachee a moitie quand il n'est pas active
	int iHeight = Taille.cx/2 ; 
    int iWidth	= Taille.cy/2 ; 
 
    pabd->uEdge = uEdge; 
 
    // Copy the screen coordinates of the appbar's bounding 
    // rectangle into the APPBARDATA structure. 
    switch (uEdge)
		{ 
        case ABE_LEFT: 
			pabd->rc.left	=	0 ;
			pabd->rc.top	=	0 ;
			pabd->rc.right	=	iWidth ;
			pabd->rc.bottom	=	GetSystemMetrics( SM_CYSCREEN ) ;
            break; 
 
        case ABE_RIGHT: 
            pabd->rc.left	=	GetSystemMetrics( SM_CXSCREEN ) - iHeight ;
			pabd->rc.right	=	GetSystemMetrics( SM_CXSCREEN ) ; ;
			pabd->rc.top	=	0 ;
			pabd->rc.bottom	=	GetSystemMetrics( SM_CYSCREEN ) ;
            break; 
 
        case ABE_TOP: 
            pabd->rc.left	=	0 ;
			pabd->rc.top	=	0 ;
			pabd->rc.right	=	GetSystemMetrics( SM_CXSCREEN ) ; ;
			pabd->rc.bottom	=	iHeight ;
            break; 
 
        case ABE_BOTTOM: 
            pabd->rc.left	=	0 ;
			pabd->rc.right	=	GetSystemMetrics( SM_CXSCREEN ) ; 
            pabd->rc.top	=	GetSystemMetrics( SM_CYSCREEN ) - iHeight ;
			pabd->rc.bottom	=	GetSystemMetrics( SM_CYSCREEN ) ;
			break; 
    } 
 
    // Query the system for an approved size and position. 
    ::SHAppBarMessage(ABM_QUERYPOS, pabd); 
 
    // Adjust the rectangle, depending on the edge to which the 
    // appbar is anchored. 
    switch (uEdge) { 
        case ABE_LEFT: 
            pabd->rc.right = pabd->rc.left + iWidth; 
            break; 
 
        case ABE_RIGHT: 
            pabd->rc.left = pabd->rc.right - iWidth; 
            break; 
 
        case ABE_TOP: 
            pabd->rc.bottom = pabd->rc.top + iHeight; 
            break; 
 
        case ABE_BOTTOM: 
            pabd->rc.top = pabd->rc.bottom - iHeight; 
            break; 
    } 
 
    // Pass the final bounding rectangle to the system. 
    ::SHAppBarMessage(ABM_SETPOS, pabd); 
 
    // Move and size the appbar so that it conforms to the 
    // bounding rectangle passed to the system. 
	switch (uEdge) { 
        case ABE_RIGHT: 
            pabd->rc.right = pabd->rc.left + Taille.cx; 
            break; 
 
        case ABE_LEFT: 
            pabd->rc.left = pabd->rc.right - Taille.cx; 
            break; 
 
        case ABE_BOTTOM: 
            pabd->rc.bottom = pabd->rc.top + Taille.cy ; 
            break; 
 
        case ABE_TOP: 
            pabd->rc.top = pabd->rc.bottom - Taille.cy ; 
            break; 
    } 

    ::MoveWindow(pabd->hWnd, pabd->rc.left, pabd->rc.top, 
        pabd->rc.right - pabd->rc.left, 
        pabd->rc.bottom - pabd->rc.top, TRUE);
} 
 
void	CMainFrame::InitToolbar( void )
{
		
	// Enregistrer la fenetre en tant que TOOLBAR du systeme
	APPBARDATA	AppBarData ;
	AppBarData.cbSize				=	sizeof( AppBarData ) ;
	AppBarData.hWnd					=	m_hWnd ;
	AppBarData.uCallbackMessage		=	_AppBarCallBackMessage ;
	AppBarData.uEdge				=	GetSide() ;


	::SHAppBarMessage( ABM_NEW, &AppBarData ) ;

	AppBarData.lParam				=	(LPARAM)_AutoHide ;

	::SHAppBarMessage( ABM_SETAUTOHIDEBAR, &AppBarData ) ;

	// Regler la taille et la position de la fenetre
	CRect	R( GetSystemMetrics( SM_CXSCREEN ) - 50,
			   0,
			   GetSystemMetrics( SM_CXSCREEN ),
			   GetSystemMetrics( SM_CYSCREEN )) ;

	AppBarQuerySetPos(GetSide(), R, &AppBarData ) ;
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	switch( nIDEvent )
		{
		case 1 :
			InitToolbar() ;
			KillTimer( 1 ) ;
			ShowWindow( SW_SHOW ) ;
			break ;

		}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	// Enregistrer la fenetre en tant que TOOLBAR du systeme
}

void	CMainFrame::OnWindowPosChanged( WINDOWPOS *	pwndpos )
	{
	CFrameWnd::OnWindowPosChanged( pwndpos ) ;
	APPBARDATA	AppBarData ;
	AppBarData.cbSize				=	sizeof( AppBarData ) ;
	AppBarData.hWnd					=	m_hWnd ;
	AppBarData.uCallbackMessage		=	_AppBarCallBackMessage ;
	AppBarData.uEdge				=	GetSide() ;

	::SHAppBarMessage( ABM_ACTIVATE, &AppBarData ) ;
	}
  
void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	APPBARDATA	AppBarData ;
	AppBarData.cbSize				=	sizeof( AppBarData ) ;
	AppBarData.hWnd					=	m_hWnd ;
	AppBarData.uCallbackMessage		=	_AppBarCallBackMessage ;
	AppBarData.uEdge				=	GetSide() ;

	::SHAppBarMessage( ABM_ACTIVATE, &AppBarData ) ;

	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
}

void CMainFrame::OnDestroy() 
{
	// Supprimer la TOOLBAR
	APPBARDATA	AppBarData ;
	AppBarData.cbSize				=	sizeof( AppBarData ) ;
	AppBarData.hWnd					=	m_hWnd ;
	AppBarData.uCallbackMessage		=	_AppBarCallBackMessage ;
	AppBarData.uEdge				=	ABE_RIGHT ;

	::SHAppBarMessage( ABM_REMOVE, &AppBarData ) ;
	
	CFrameWnd::OnDestroy();

	::PostQuitMessage( 0 ) ;
}


UINT CMainFrame::GetSide( void )
{
	CJibe96View	*	pView	=	(CJibe96View*) GetActiveView() ;
	if ( ! pView )
		return ABE_RIGHT ;

	ASSERT_VALID( pView ) ;
	CJibe96Doc*		pDoc	=	pView->GetDocument() ;

	if ( ! pDoc )
		return ABE_RIGHT ;

	ASSERT( pDoc ) ;

	return pDoc->GetSide() ;
}

void CMainFrame::SetSide( UINT Pos )
{
	CJibe96View	*	pView	=	(CJibe96View*) GetActiveView() ;
	ASSERT( pView ) ;
	CJibe96Doc*		pDoc	=	pView->GetDocument() ;
	ASSERT( pDoc ) ;

	pDoc->SetSide(Pos) ;
}

void CMainFrame::SetPos( UINT Side )
{
	SetSide( Side ) ;
	APPBARDATA	AppBarData ;
	AppBarData.cbSize				=	sizeof( AppBarData ) ;
	AppBarData.hWnd					=	m_hWnd ;
	AppBarData.uCallbackMessage		=	_AppBarCallBackMessage ;
	AppBarData.uEdge				=	Side ;
	
	CRect	R	;
	GetWindowRect( R ) ;
	AppBarQuerySetPos(Side, R, &AppBarData ) ;

	CJibe96View*	pVue	=	(CJibe96View*)GetActiveView() ;
	ASSERT_VALID( pVue ) ;
	pVue->SetSide( Side ) ;
}



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	CJibe96View::PreTranslateToolTipMsg( pMsg ) ;
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

///////////////////////////////////////////////////////////////////////////////
// Retourne la taille desiree pour la barre
// ( cx = largeur de la barre horizontale )
// ( cy = hauteur de la barre verticale )
///////////////////////////////////////////////////////////////////////////////
CSize CMainFrame::GetSize( void )
{
	return CSize(::GetSystemMetrics( SM_CYICON )*2 + 2 * GetSystemMetrics( SM_CXDLGFRAME ),
				 ::GetSystemMetrics( SM_CXICON )*2 + 2 * GetSystemMetrics( SM_CYDLGFRAME ) ) ;
}

void CMainFrame::OnInitMenu(CMenu* pMenu)
{
   CFrameWnd::OnInitMenu(pMenu);
  
	// CG: This block added by 'Tip of the Day' component.
	{
		// TODO: This code adds the "Tip of the Day" menu item
		// on the fly.  It may be removed after adding the menu
		// item to all applicable menu items using the resource
		// editor.

		// Add Tip of the Day menu item on the fly!
		static CMenu* pSubMenu = NULL;

		CString strHelp; strHelp.LoadString(CG_IDS_TIPOFTHEDAYHELP);
		CString strMenu;
		int nMenuCount = pMenu->GetMenuItemCount();
		BOOL bFound = FALSE;
		for (int i=0; i < nMenuCount; i++) 
		{
			pMenu->GetMenuString(i, strMenu, MF_BYPOSITION);
			if (strMenu == strHelp)
			{ 
				pSubMenu = pMenu->GetSubMenu(i);
				bFound = TRUE;
				ASSERT(pSubMenu != NULL);
			}
		}

		CString strTipMenu;
		strTipMenu.LoadString(CG_IDS_TIPOFTHEDAYMENU);
		if (!bFound)
		{
			// Help menu is not available. Please add it!
			if (pSubMenu == NULL) 
			{
				// The same pop-up menu is shared between mainfrm and frame 
				// with the doc.
				static CMenu popUpMenu;
				pSubMenu = &popUpMenu;
				pSubMenu->CreatePopupMenu();
				pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION, 
					CG_IDS_TIPOFTHEDAY, strTipMenu);
			} 
			pMenu->AppendMenu(MF_STRING|MF_BYPOSITION|MF_ENABLED|MF_POPUP, 
				(UINT)pSubMenu->m_hMenu, strHelp);
			DrawMenuBar();
		} 
		else
		{      
			// Check to see if the Tip of the Day menu has already been added.
			pSubMenu->GetMenuString(0, strMenu, MF_BYPOSITION);

			if (strMenu != strTipMenu) 
			{
				// Tip of the Day submenu has not been added to the 
				// first position, so add it.
				pSubMenu->InsertMenu(0, MF_BYPOSITION);  // Separator
				pSubMenu->InsertMenu(0, MF_STRING|MF_BYPOSITION, 
					CG_IDS_TIPOFTHEDAY, strTipMenu);
			}
		}
	}

}


///////////////////////////////////////////////////////////////////////////////
// GetRect
// Calcule le rectangle que doit occuper la task bar sur l'ecran
///////////////////////////////////////////////////////////////////////////////
CRect CMainFrame::GetRect()
{
	CSize	Taille	=	GetSize() ;

	const	int	LargeurEcran	=	GetSystemMetrics( SM_CXSCREEN ) ;
	const	int HauteurEcran	=	GetSystemMetrics( SM_CYSCREEN ) ;

	switch ( GetSide())
		{
		case ABE_LEFT :
			return CRect( 0, 0, Taille.cx/2, HauteurEcran) ;

		case ABE_TOP :
			return CRect( 0, 0, LargeurEcran, Taille.cy/2 ) ;

		case ABE_RIGHT :
			return CRect( LargeurEcran-Taille.cx/2, 0, Taille.cx/2, HauteurEcran ) ;

		case ABE_BOTTOM :
			return CRect( 0, HauteurEcran-Taille.cy/2, LargeurEcran, Taille.cy/2 ) ;
		}

	return CRect(0,0,0,0) ;
}




void CMainFrame::OuvreFenetre( void )
{
	CSize	Taille	=	GetSize() ;

	const	int	LargeurEcran	=	GetSystemMetrics( SM_CXSCREEN ) ;
	const	int HauteurEcran	=	GetSystemMetrics( SM_CYSCREEN ) ;

	CPoint	Point ;
	switch ( GetSide())
		{
		case ABE_LEFT :
			Point.x	=	0 ;
			Point.y	=	0 ;
			break ;

		case ABE_TOP :
			Point.x	=	0 ;
			Point.y	=	0 ;
			break ;

		case ABE_RIGHT :
			Point.x	=	LargeurEcran-Taille.cx ;
			Point.y	=	0 ;
			break ;

		case ABE_BOTTOM :
			Point.x	=	0 ;
			Point.y	=	HauteurEcran-Taille.cy ;
			break ;

		}

	MoveWindowTo( Point ) ;
}

void CMainFrame::FermeFenetre( void )
{
	CSize	Taille	=	GetSize() ;

	const	int	LargeurEcran	=	GetSystemMetrics( SM_CXSCREEN ) ;
	const	int HauteurEcran	=	GetSystemMetrics( SM_CYSCREEN ) ;

	CPoint	Point ;

	switch ( GetSide())
		{
		case ABE_LEFT :
			Point.x	=	-Taille.cx/2 ;
			Point.y	=	0 ;
			break ;

		case ABE_TOP :
			Point.x	=	0 ;
			Point.y	=	-Taille.cy/2 ;
			break ;

		case ABE_RIGHT :
			Point.x	=	LargeurEcran-Taille.cx/2 ;
			Point.y	=	0 ;
			break ;

		case ABE_BOTTOM :
		default :
			Point.x	=	0 ;
			Point.y	=	HauteurEcran-Taille.cy/2 ;
			break ;
		}

	MoveWindowTo( Point ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Deplacer progressivement la fenetre vers un autre point
///////////////////////////////////////////////////////////////////////////////
void CMainFrame::MoveWindowTo( CPoint Pt )
{
	CRect R ;
	GetWindowRect( R ) ;
	CPoint	PtActuel( R.TopLeft());

	while ( PtActuel !=	Pt )
		{
		int DecalageX	=	0 ;
		int DecalageY	=	0 ;
		if ( Pt.x > PtActuel.x )
			DecalageX	=	( Pt.x - PtActuel.x )/2 + 1 ;
		else
		if ( Pt.x < PtActuel.x)
			DecalageX	=	( Pt.x - PtActuel.x )/2 - 1 ;

		if ( Pt.y > PtActuel.y )
			DecalageY	=	( Pt.y - PtActuel.y )/2 + 1 ;
		else
		if ( Pt.y < PtActuel.y )
			DecalageY	=	( Pt.y - PtActuel.y )/2 - 1 ;

		PtActuel.x	+= DecalageX ;
		PtActuel.y	+= DecalageY ;
		SetWindowPos( &wndTopMost, PtActuel.x, PtActuel.y, 0, 0,
					  SWP_NOSIZE | SWP_NOACTIVATE ) ;
		}
}
