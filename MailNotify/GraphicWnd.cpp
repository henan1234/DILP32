// GraphicWnd.cpp : implementation file
//

#include "stdafx.h"
#include "GraphicWnd.h"
#include "common.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int	CGraphicWnd::_Origin	=	0 ;
CObList	CGraphicWnd::_WindowList ;

/////////////////////////////////////////////////////////////////////////////
// CGraphicWnd

CGraphicWnd::CGraphicWnd()
{
	_WindowList.AddTail( this ) ;
}

CGraphicWnd::~CGraphicWnd()
{
	POSITION Position	=	_WindowList.Find( this ) ;

	if ( Position )
		_WindowList.RemoveAt( Position ) ;
}


BEGIN_MESSAGE_MAP(CGraphicWnd, CWnd)
	//{{AFX_MSG_MAP(CGraphicWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGraphicWnd message handlers

void CGraphicWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( IDB_PATTERN ) ;
	CBrush Brosse( &Bitmap ) ;
	
	CRect	R ;
	GetClientRect( R ) ;

	CPoint	Point( _Origin, 0 ) ;
	ClientToScreen( &Point ) ;

	Brosse.UnrealizeObject() ;
	dc.SetBrushOrg( Point ) ;

	dc.FillRect( R, &Brosse ) ;

	Brosse.DeleteObject() ;
}



void CALLBACK EXPORT TimerProc(HWND, UINT, UINT, DWORD ) 
{
	CGraphicWnd::_Origin ++ ;

	POSITION Pos	=	CGraphicWnd::_WindowList.GetHeadPosition() ;

	while ( Pos )
		{
		CGraphicWnd*	pWnd	=	(CGraphicWnd*)CGraphicWnd::_WindowList.GetNext( Pos ) ;

		ASSERT_VALID( pWnd ) ;

		if ( pWnd )
			if ( IsWindow( pWnd->m_hWnd ))
				{
				pWnd->Invalidate( FALSE ) ;
				pWnd->UpdateWindow() ;
				}
		}
}

int CGraphicWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer( 1, GetTimerDelay( DELAY_ANIMATION ), TimerProc ) ;
	return 0;
}

BOOL CGraphicWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle	|=	WS_EX_TOOLWINDOW | WS_EX_TOPMOST ;
	return CWnd::PreCreateWindow(cs);
}


