// SaverWndClass.cpp : implementation file
//

#include "stdafx.h"
#include "SaverMFC.h"
#include "SaverWndClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaverWndClassClass

CSaverWndClassClass::CSaverWndClassClass()
{
}

CSaverWndClassClass::~CSaverWndClassClass()
{
}


BEGIN_MESSAGE_MAP(CSaverWndClassClass, CWnd)
	//{{AFX_MSG_MAP(CSaverWndClassClass)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_SETCURSOR()
	ON_WM_NCACTIVATE()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



int CSaverWndClassClass::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
#ifdef _DEBUG
	SetWindowPos( hWnd, 0, 0, 0, GetSystemMetrics( SM_CXSCREEN ) / 2,
				  GetSystemMetrics( SM_CYSCREEN ), SWP_NOMOVE ) ;
	SetWindowLong( hWnd, GWL_STYLE,
					GetWindowLong( hWnd, GWL_STYLE ) | WS_THICKFRAME ) ;
#endif
	CEconomiseur * pEconomiseur	=	CEconomiseur::GetEconomiseur() ;

	InitSave	=	FALSE ;
	pEconomiseur->CEstParti( hWnd ) ;

	  
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


void CSaverWndClass::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if ((nID == SC_SCREENSAVE) || (nID == SC_CLOSE))
		return;
	CDrawWnd::OnSysCommand(nID, lParam);
}

void CSaverWndClass::OnDestroy() 
{
	PostQuitMessage(0);
	CDrawWnd::OnDestroy();
}

BOOL CSaverWndClass::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(NULL);
	return TRUE;
}

BOOL CSaverWndClass::OnNcActivate(BOOL bActive) 
{
	if (!bActive)
		return FALSE;
	return CDrawWnd::OnNcActivate(bActive);
}

void CSaverWndClass::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if (nState == WA_INACTIVE)
		PostMessage(WM_CLOSE);
	CDrawWnd::OnActivate(nState, pWndOther, bMinimized);
}

void CSaverWndClass::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	if (!bActive)
		PostMessage(WM_CLOSE);
	CDrawWnd::OnActivateApp(bActive, hTask);
}

void CSaverWndClass::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_ptLast == CPoint(-1,-1))
		m_ptLast = point;
	else if (m_ptLast != point)
		PostMessage(WM_CLOSE);
	CDrawWnd::OnMouseMove(nFlags, point);
}

void CSaverWndClass::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CWnd::OnLButtonDown(nFlags, point);
}

void CSaverWndClass::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CWnd::OnLButtonDown(nFlags, point);
}

void CSaverWndClass::OnRButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_CLOSE);
	CWnd::OnRButtonDown(nFlags, point);
}

void CSaverWndClass::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	PostMessage(WM_CLOSE);
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSaverWndClass::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	PostMessage(WM_CLOSE);
	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
