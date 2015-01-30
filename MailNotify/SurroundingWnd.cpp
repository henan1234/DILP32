// SurroundingWnd.cpp : implementation file
//

#include "stdafx.h"
#include "SurroundingWnd.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurroundingWnd

CSurroundingWnd::CSurroundingWnd( )
{
}

CSurroundingWnd::~CSurroundingWnd()
{
}


BEGIN_MESSAGE_MAP(CSurroundingWnd, CGraphicWnd)
	//{{AFX_MSG_MAP(CSurroundingWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSurroundingWnd message handlers

BOOL CSurroundingWnd::Create(HWND hSurroundedWindow)
{
	if ( ! hSurroundedWindow )
		return FALSE ;

	if ( ! IsWindow( hSurroundedWindow ))
		return FALSE ;

	// Get the window rects
	CRect InnerRect, OuterRect ;
	::GetWindowRect( hSurroundedWindow, InnerRect ) ;

	OuterRect	=	InnerRect ;
	OuterRect.InflateRect(	2*::GetSystemMetrics( SM_CXBORDER ), 
							2*::GetSystemMetrics( SM_CYBORDER )) ;

	// Register the window class
	WNDCLASS WndClass ;
	WndClass.style			=	CS_VREDRAW | CS_HREDRAW ;
	WndClass.lpfnWndProc	=	AfxWndProc ;
	WndClass.cbClsExtra		=	0 ;
	WndClass.cbWndExtra		=	0 ;
	WndClass.hInstance		=	AfxGetInstanceHandle() ;
	WndClass.hIcon			=	0 ;
	WndClass.hCursor		=	NULL ;
	WndClass.hbrBackground	=	0 ;
	WndClass.lpszMenuName	=	0 ;
	WndClass.lpszClassName	=	szSurroundingWindowClassName ;
	if ( ! AfxRegisterClass( &WndClass ))
		return FALSE ;

	// Create the window
	if (!CreateEx(	WS_EX_TOOLWINDOW | WS_EX_TOPMOST, szSurroundingWindowClassName,
						"HP Brio Center Warning Icon", WS_POPUP,
						OuterRect, NULL, NULL, NULL ))
		return FALSE ;

	// Create a rectangular region with a rectangular hole in the center
	HRGN	hInnerRegion	=	CreateRectRgn(	InnerRect.left,
												InnerRect.top,
												InnerRect.right,
												InnerRect.bottom ) ;

	HRGN	hOuterRegion	=	CreateRectRgn(	OuterRect.left,
												OuterRect.top,
												OuterRect.right,
												OuterRect.bottom ) ;

	HRGN	hWndRegion		=	CreateRectRgn( 0,0,0,0 ) ;
	CombineRgn( hWndRegion, hOuterRegion, hInnerRegion, RGN_DIFF ) ;
	DeleteObject( hOuterRegion ) ;
	DeleteObject( hInnerRegion ) ;

	// Set the window region
	OffsetRgn( hWndRegion, -OuterRect.left, -OuterRect.top ) ;
	SetWindowRgn( hWndRegion, TRUE ) ;

	return TRUE ;
}

