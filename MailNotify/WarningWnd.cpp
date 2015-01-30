// WarningWnd.cpp : implementation file
//

#include "stdafx.h"
#include "WarningWnd.h"
#include "LinkWindow.h"
#include "SurroundingWnd.h"
#include "common.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


	
/////////////////////////////////////////////////////////////////////////////
// CWarningWnd

CWarningWnd::CWarningWnd()
{
	_pSurroundingWnd	=	0 ;
	_pLinkWnd			=	0 ;
	_pBitmap			=	0 ;
}

CWarningWnd::~CWarningWnd()
{

}


BEGIN_MESSAGE_MAP(CWarningWnd, CWnd)
	//{{AFX_MSG_MAP(CWarningWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWarningWnd message handlers

int CWarningWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}



/////////////////////////////////////////////////////////////////////////////
// OnTimer
//	Receives notification from the timer
/////////////////////////////////////////////////////////////////////////////
void CWarningWnd::OnTimer(UINT nIDEvent) 
{
	HideMessageWindow() ;

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// DisplayMessageWindow
// This method will display the message window next to the icon notification
// tray bar
/////////////////////////////////////////////////////////////////////////////
void CWarningWnd::DisplayMessageWindow()
{
	// First, check if the window is already displayed
	if ( IsWindowVisible() )
		// Nothing to do yet, the window is already open
		return ;

	// Get the final window position and size
	CRect CurrentWindowRect, FinalWindowRect	;
	GetInitialAndFinalWindowRect( CurrentWindowRect, FinalWindowRect ) ;

	ASSERT( ! _pSurroundingWnd ) ;
	_pSurroundingWnd	=	new CSurroundingWnd() ;
	_pSurroundingWnd->Create(GetIconTrayWnd() ) ;
	_pSurroundingWnd->ShowWindow( SW_SHOWNOACTIVATE ) ;

	ASSERT( ! _pLinkWnd ) ;
	_pLinkWnd		=	new CLinkWindow() ;
	_pLinkWnd->Create() ;
	_pLinkWnd->ShowWindow( SW_SHOWNOACTIVATE ) ;

	// Set the timer to hide the window after a delay
	SetTimer( 1, GetTimerDelay( DELAY_BEFORE_HIDE ),0) ;

	// Progressively move the window to its final position
	CRect	SurroundingRect ;
	const	int	Edge	=	GetTaskBarPosition( ::FindWindow( "Shell_TrayWnd", NULL ));

	_pSurroundingWnd->GetWindowRect( SurroundingRect ) ;

	do
		{
		SetWindowPos(	&wndTopMost,
						CurrentWindowRect.left, CurrentWindowRect.top,
						CurrentWindowRect.Width(), CurrentWindowRect.Height(),
						SWP_NOACTIVATE | SWP_SHOWWINDOW ) ;

		UpdateWindow() ;

		CRect	R =	GetLinkRect( SurroundingRect, CurrentWindowRect, Edge ) ;

		_pLinkWnd->MoveWindow( R, TRUE ) ;

		MoveRect( CurrentWindowRect, FinalWindowRect ) ;
		
		MSG	msg ;
		if ( PeekMessage(  &msg, 0, 0, 0, PM_REMOVE ))
			{
			TranslateMessage( &msg ) ;
			DispatchMessage( &msg ) ;
			}
		}
	while ( CurrentWindowRect != FinalWindowRect ) ;
}

/////////////////////////////////////////////////////////////////////////////
// GetFinalWindowRect
//	Get the initial and final window rect after the animation
//	This is the hardest part of the program because we need to get the tray
//	bar position and to know the position of the task bar on the desktop
//	( left, right, top, bottom )
/////////////////////////////////////////////////////////////////////////////
void CWarningWnd::GetInitialAndFinalWindowRect( CRect & Initial, CRect & Final )
{
	//////////////////////////////////////////////////////// Get the task bar
	HWND hTaskBar	=	::FindWindow( "Shell_TrayWnd", NULL ) ;
	if ( ! hTaskBar )
		return ;

	CRect	TaskBarRect ;
	::GetWindowRect( hTaskBar, TaskBarRect ) ;
	// Get the task position
	const UINT Edge	=	GetTaskBarPosition( hTaskBar ) ;

	/////////////////////////////////////////////// Now find its child window
	HWND hIconTray	=	::FindWindowEx( hTaskBar, NULL, "TrayNotifyWnd", NULL ) ;
	if ( ! hIconTray )
		return ;

	// Get the window position
	CRect	IconTrayRect ;
	::GetWindowRect( hIconTray, IconTrayRect ) ;

	CString Message	;
	GetWindowText( Message ) ;
	CClientDC Dc(this) ;
	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	CRect RText ;
	Dc.DrawText( Message, RText, DT_LEFT | DT_TOP | DT_EXPANDTABS | DT_CALCRECT | DT_NOCLIP ) ;

	const int Width	=	RText.Width() + 16 ;
	const int Height=	RText.Height() + 16 ;


	switch ( Edge )
		{
		case ABE_BOTTOM :
			Initial.top		=	TaskBarRect.top ;
			Initial.bottom	=	Initial.top + Height ;
			Initial.right	=	IconTrayRect.right -IconTrayRect.Width()/4;
			Initial.left	=	IconTrayRect.right - Width ;
	
			Final.top		=	TaskBarRect.top - Height * 3 / 2 ;
			Final.bottom	=	Final.top + Height ;
			Final.left		=	Initial.left ;
			Final.right		=	Final.left + Width ;
			break ;

		case ABE_LEFT :
			Initial.left	=	TaskBarRect.right ;
			Initial.right	=	Initial.left + Width ;
			Initial.top		=	IconTrayRect.top - IconTrayRect.Height() /4 ;
			Initial.bottom	=	Initial.top + Height ;

			Final.left		=	TaskBarRect.right + Width / 2 ;
			Final.right		=	Final.left + Width ;
			Final.top		=	Initial.top ;
			Final.bottom	=	Initial.top + Height ;
			break ;

		case ABE_RIGHT :
			Initial.right	=	TaskBarRect.left;
			Initial.left	=	Initial.right - Width ;
			Initial.top		=	IconTrayRect.top + IconTrayRect.Height() /4 ;
			Initial.bottom	=	Initial.top + Height ;

			Final.right		=	TaskBarRect.right - Width / 2 ;
			Final.left		=	Final.right - Width ;
			Final.top		=	Initial.top ;
			Final.bottom	=	Initial.top + Height ;
			break ;
		
		case ABE_TOP :
			Initial.top		=	TaskBarRect.bottom ;
			Initial.bottom	=	Initial.top + Height ;
			Initial.right	=	IconTrayRect.right -IconTrayRect.Width()/4;
			Initial.left	=	IconTrayRect.right - Width ;

			Final.bottom	=	TaskBarRect.bottom + Height * 3 / 2 ;
			Final.top		=	Final.bottom - Height ;
			Final.left		=	Initial.left ;
			Final.right		=	Final.left + Width ;
			break ;
		}
}

/////////////////////////////////////////////////////////////////////////////
//  Repaint the window
//	This is done from :
//		- A background window
//		- A 'tip' text
//		- An icon
/////////////////////////////////////////////////////////////////////////////
void CWarningWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	HWND hTaskBar	=	::FindWindow( "Shell_TrayWnd", NULL ) ;
	if ( ! hTaskBar )
		return ;

	// Get the task position
	const UINT Edge	=	GetTaskBarPosition( hTaskBar ) ;

	
	CString	Message	;
	GetWindowText(Message) ;
	dc.SelectStockObject( ANSI_VAR_FONT ) ;
	dc.SetBkMode( TRANSPARENT ) ;

	CRect RText ;
	GetClientRect( RText ) ;
	RText.DeflateRect( 8, 8 ) ;

	// Draw the text
	dc.DrawText( Message, RText, DT_LEFT | DT_TOP | DT_EXPANDTABS | DT_NOCLIP ) ;
}

///////////////////////////////////////////////////////////////////////////////
// MoveRect
//	Gradually change a rectangle so it will be the same as the target rectangle
///////////////////////////////////////////////////////////////////////////////
void CWarningWnd::MoveRect(CRect & Moving, const CRect & Target)
{
	MoveIntTo( Moving.left, Target.left ) ;
	MoveIntTo( Moving.right, Target.right ) ;
	MoveIntTo( Moving.top, Target.top ) ;
	MoveIntTo( Moving.bottom, Target.bottom ) ;
}

void CWarningWnd::MoveIntTo(LONG & Moving, LONG Target)
{
	if ( Moving < Target )
		{
		const int Delta	=	( Target-Moving) / 2 ;
		if ( Delta )
			Moving += Delta ;
		else
			Moving ++ ;
		}
	else
		if ( Moving > Target )
			{
			const int Delta	= (Moving-Target)/2 ;
			if ( Delta )
				Moving -= Delta ;
			else
				Moving -- ;
			}
}

///////////////////////////////////////////////////////////////////////////////
// Get the docking side of a taskbar : ABE_TOP, ABE_BOTTOM, ABE_LEFT, ABE_RIGHT
///////////////////////////////////////////////////////////////////////////////
UINT CWarningWnd::GetTaskBarPosition(HWND hTaskBar)
{
/*	APPBARDATA abd; 
	memset( &abd, 0, sizeof( abd )) ;

    abd.cbSize	= sizeof(APPBARDATA);  
    abd.hWnd	= hTaskBar ;

	SHAppBarMessage(ABM_GETSTATE, &abd);

	return abd.uEdge ;*/

	// Determine which screen the taskbar is closer
	const LONG	Left	=	0 ;
	const LONG	Right	=	GetSystemMetrics( SM_CXFULLSCREEN ) ;
	const LONG	Top		=	0 ;
	const LONG	Bottom	=	GetSystemMetrics( SM_CYFULLSCREEN ) ;
	
	CRect	R ;
	::GetWindowRect( hTaskBar, R ) ;

	CPoint	MiddleOfTaskBar	=	R.CenterPoint() ;

	const LONG DistanceLeft	=	labs( MiddleOfTaskBar.x- Left ) ;
	const LONG DistanceRight=	labs( MiddleOfTaskBar.x- Right ) ;
	const LONG DistanceTop	=	labs( MiddleOfTaskBar.y- Top ) ;
	const LONG DistanceBottom=	labs( MiddleOfTaskBar.y- Bottom ) ;

	// Determine which distance is smaller
	int	DistanceMin		=	min( DistanceLeft, DistanceRight ) ;
	DistanceMin			=	min( DistanceMin, DistanceTop ) ;
	DistanceMin			=	min( DistanceMin, DistanceBottom ) ;

	if ( DistanceMin	==	DistanceBottom )
		return ABE_BOTTOM ;

	if ( DistanceMin	==	DistanceTop )
		return ABE_TOP ;

	if ( DistanceMin	==	DistanceRight )
		return ABE_RIGHT ;

	return ABE_LEFT ;
}


///////////////////////////////////////////////////////////////////////////////
// Clic on the window
// If the user clicked on the icon, launch the HP Brio Center
///////////////////////////////////////////////////////////////////////////////
void CWarningWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HideMessageWindow() ;
	CWnd::OnLButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// HideMessageWindow
//	Guess what ?
///////////////////////////////////////////////////////////////////////////////
void CWarningWnd::HideMessageWindow()
{
	KillTimer( 3 ) ;

	delete _pSurroundingWnd ;
	_pSurroundingWnd	=	0 ;

	delete _pLinkWnd ;
	_pLinkWnd	=	0 ;

	DestroyWindow() ; 
}

///////////////////////////////////////////////////////////////////////////////
// GetIconTrayWnd
//	Get the handle of the icon notification tray wnd.
///////////////////////////////////////////////////////////////////////////////
HWND CWarningWnd::GetIconTrayWnd()
{
	HWND hTaskBar	=	::FindWindow( "Shell_TrayWnd", NULL ) ;
	if ( ! hTaskBar )
		return 0 ;

	return ::FindWindowEx( hTaskBar, NULL, "TrayNotifyWnd", NULL ) ;
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
void CWarningWnd::OnDestroy() 
{
	if ( _pBitmap )
		{
		_pBitmap->DeleteObject() ;
		delete _pBitmap ;
		}	

	if ( _pSurroundingWnd )
		_pSurroundingWnd->DestroyWindow() ;

	if ( _pLinkWnd )
		_pLinkWnd->DestroyWindow() ;

	CWnd::OnDestroy();
}

///////////////////////////////////////////////////////////////////////////////
// GetLinkRect
//	Get the rectangular shape of the link window between the message window and
//	the window surrounding the icon tray
///////////////////////////////////////////////////////////////////////////////
CRect CWarningWnd::GetLinkRect(const CRect & Tray, const CRect & Message, int Edge)
{
	CRect R ;
	switch ( Edge )
		{
		case ABE_BOTTOM :
			R.top	=	Message.bottom ;
			R.bottom=	Tray.top ;

			R.left	=	Tray.left + (Message.right-Tray.left)/2 - 1*::GetSystemMetrics( SM_CXBORDER );
			R.right	=	R.left + 2 *::GetSystemMetrics( SM_CXBORDER );
			break ;

		case ABE_TOP :
			R.top	=	Tray.bottom ;
			R.bottom=	Message.top ;
			R.left	=	Tray.left + (Message.right-Tray.left)/2 - 1*::GetSystemMetrics( SM_CXBORDER );
			R.right	=	R.left + 2 *::GetSystemMetrics( SM_CXBORDER ) ;
			break ;

		case ABE_RIGHT:
			R.left	=	Message.right ;
			R.right	=	Tray.left ;
			R.top	=	Tray.top + ( Message.bottom-Tray.top)/2 - 1*::GetSystemMetrics( SM_CXBORDER );
			R.bottom=	R.top + 2 *::GetSystemMetrics( SM_CXBORDER ) ;
			break ;

		case ABE_LEFT:
			R.left	=	Tray.right ;
			R.right	=	Message.left ;
			R.top	=	Tray.top + ( Message.bottom-Tray.top)/2 - 1*::GetSystemMetrics( SM_CXBORDER );
			R.bottom=	R.top + 2 *::GetSystemMetrics( SM_CXBORDER ) ;
			break ;

		default :
			break ;
		}

	return R ;
}




BOOL CWarningWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor( AfxGetApp()->LoadCursor( IDC_HAND )) ;
	
	return TRUE ;
}



BOOL CWarningWnd::OnEraseBkgnd(CDC* pDC) 
{
	CRect	R ;
	GetClientRect( R ) ;

	pDC->FillSolidRect( R, RGB( 255, 255, 128 )) ;

	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( IDB_PATTERN ) ;
	CBrush Brosse( &Bitmap ) ;
	CRect RF( R ) ;

	RF.bottom=	RF.top + 4 ;
	pDC->FillRect( RF, &Brosse ) ;

	RF.bottom=	R.bottom ;
	RF.top   =	R.bottom - 4 ;
	pDC->FillRect( RF, &Brosse ) ;

	RF.top   =	R.top + 4 ;
	RF.bottom=	R.bottom - 4 ;
	RF.right =	R.left + 4 ;
	RF.left	 =	R.left ;
	pDC->FillRect( RF, &Brosse ) ;

	RF.right =	R.right ;
	RF.left	 =	R.right - 4 ;
	pDC->FillRect( RF, &Brosse ) ;

	Brosse.DeleteObject() ;
	return CWnd::OnEraseBkgnd(pDC);
}
