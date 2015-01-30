// SharewareMessageWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SharewareMessageWnd.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSharewareMessageWnd

CSharewareMessageWnd::CSharewareMessageWnd()
{
}

CSharewareMessageWnd::~CSharewareMessageWnd()
{
}


BEGIN_MESSAGE_MAP(CSharewareMessageWnd, CWnd)
	//{{AFX_MSG_MAP(CSharewareMessageWnd)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSharewareMessageWnd message handlers

void CSharewareMessageWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CString	Message ;
	Message.LoadString( IDS_SHAREWARE_WND ) ;


	dc.SetTextColor( RGB( 255, 0,0 )) ;
	dc.SetBkMode( TRANSPARENT ) ;
	dc.SelectStockObject( ANSI_VAR_FONT ) ;

	CRect	R ;
	GetClientRect(R) ;

	dc.DrawText( Message, R, DT_CENTER | DT_TOP | DT_WORDBREAK ) ;

	SetTimer(1,100, 0) ;
}

void CSharewareMessageWnd::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CWnd::OnShowWindow(bShow, nStatus);
	
	if ( bShow )
		SetTimer(1,100, 0) ;
	else
		KillTimer(1) ;
}


void CSharewareMessageWnd::OnTimer(UINT nIDEvent) 
{
	BringWindowToTop() ;
	SetWindowPos(  &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE ) ;
	Invalidate( TRUE ) ;

	CWnd::OnTimer(nIDEvent);
}

void CSharewareMessageWnd::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CWnd::OnWindowPosChanged(lpwndpos);
	
	if ( IsWindowVisible())
		SetTimer(1,100, 0) ;
	else
		KillTimer(1) ;
}
