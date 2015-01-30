// LinkWindow.cpp : implementation file
//

#include "stdafx.h"
#include "LinkWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinkWindow

CLinkWindow::CLinkWindow()
{
}

CLinkWindow::~CLinkWindow()
{
}


BEGIN_MESSAGE_MAP(CLinkWindow, CGraphicWnd)
	//{{AFX_MSG_MAP(CLinkWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLinkWindow message handlers

void CLinkWindow::Create()
{
	WNDCLASS	WndClass ;
	WndClass.style			=	CS_VREDRAW | CS_HREDRAW ;
	WndClass.lpfnWndProc	=	AfxWndProc ;
	WndClass.cbClsExtra		=	0 ;
	WndClass.cbWndExtra		=	0 ;
	WndClass.hInstance		=	AfxGetInstanceHandle() ;
	WndClass.hIcon			=	0 ;
	WndClass.hCursor		=	NULL ;
	WndClass.hbrBackground	=	0 ;
	WndClass.lpszMenuName	=	0 ;
	WndClass.lpszClassName	=	"HPBrioCenter:LinkWindow" ;
	AfxRegisterClass( &WndClass ) ;

	if (!CreateEx(	WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
						"HPBrioCenter:LinkWindow",
						"HP Brio Center Warning Icon",
						WS_POPUP,
						0,0,10,10, NULL, NULL, NULL ))
		return ;
}
