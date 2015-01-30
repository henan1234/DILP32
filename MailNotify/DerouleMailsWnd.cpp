// DerouleMailsWnd.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
//#include "mailnotify.h"
#include "DerouleMailsWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDerouleMailsWnd

CDerouleMailsWnd::CDerouleMailsWnd()
{
}

CDerouleMailsWnd::~CDerouleMailsWnd()
{
}


BEGIN_MESSAGE_MAP(CDerouleMailsWnd, CWnd)
	//{{AFX_MSG_MAP(CDerouleMailsWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDerouleMailsWnd message handlers

BOOL CDerouleMailsWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.cx	=	200 ;
	cs.cy	=	18 ;
	return CWnd::PreCreateWindow(cs);
}

int CDerouleMailsWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	_Centre.LoadBitmap( IDB_CENTRE ) ;
	_Droite.LoadBitmap( IDB_DROITE ) ;
	_Gauche.LoadBitmap( IDB_GAUCHE ) ;

	SetTimer( 1, 100, NULL ) ;
	
	return 0;
}

void CDerouleMailsWnd::OnTimer(UINT nIDEvent) 
{
	_Decalage -- ;
	
	CClientDC Dc( this ) ;
	CRect R ;
	GetClientRect( R ) ;

	CDC	MemDC ;
	MemDC.CreateCompatibleDC( &Dc ) ;
	CBitmap Bitmap ;
	Bitmap.CreateCompatibleBitmap( &Dc, R.Width(), R.Height()) ;

	CBitmap * pOld	=	MemDC.SelectObject( & Bitmap ) ;

	Dessine( MemDC ) ;

	Dc.BitBlt( R.left, R.top, R.Width(), R.Height(), &MemDC, 0, 0, SRCCOPY ) ;

	MemDC.SelectObject( pOld ) ;
	Bitmap.DeleteObject() ;
	MemDC.DeleteDC() ;

	CWnd::OnTimer(nIDEvent);
}

void CDerouleMailsWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	Dessine( dc ) ;
}


void CDerouleMailsWnd::Dessine(CDC &Dc)
{
	CRect R ;
	GetClientRect( R ) ;

	CDC	MemDC ;
	MemDC.CreateCompatibleDC( &Dc ) ;

	CBitmap* pBitmap	=	MemDC.SelectObject( &_Gauche ) ;

	BITMAP Bitmap ;
	_Gauche.GetBitmap( &Bitmap ) ;
	const int LargeurGauche	=	Bitmap.bmWidth ;
	Dc.BitBlt( 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, &MemDC, 0, 0, SRCCOPY ) ;

	_Droite.GetBitmap( &Bitmap ) ;
	const int LargeurDroite	=	Bitmap.bmWidth ;

	_Centre.GetBitmap( &Bitmap ) ;
	const int LargeurCentre	=	Bitmap.bmWidth ;

	int x	=	LargeurGauche ;


	MemDC.SelectObject( _Centre ) ;

	for ( int i = LargeurGauche; i < R.Width() - LargeurDroite; i+= LargeurCentre )
		{
		Dc.BitBlt( x, 0, LargeurCentre, Bitmap.bmHeight, &MemDC, 0, 0, SRCCOPY ) ;
		x += LargeurCentre ;
		}

	MemDC.SelectObject( _Droite ) ;
	Dc.BitBlt( R.Width()-LargeurDroite, 0, LargeurDroite, Bitmap.bmHeight, &MemDC, 0, 0, SRCCOPY ) ;

	MemDC.SelectObject( pBitmap ) ;
	MemDC.DeleteDC() ;

	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetTextColor( RGB(0,0,0) ) ;
	Dc.SetBkMode( TRANSPARENT ) ;
	
	R.left +=	LargeurGauche ;
	R.right -= LargeurDroite ;
	R.top += 2 ;
	R.bottom -= 2 ;

	HRGN	hRegion	=	::CreateRectRgn( R.left, R.top, R.right, R.bottom ) ;

	SelectClipRgn( Dc, hRegion ) ;

	CSize	size	=	Dc.GetTextExtent( _Texte ) ;
	while  ( _Decalage < -size.cx )
			_Decalage += size.cx ;

	x	=	_Decalage ;
	while ( x < R.Width() - LargeurDroite )
		{
		Dc.TextOut( x, 2, _Texte ) ;
		x += size.cx ;
		}

	SelectClipRgn( Dc, NULL ) ;
	DeleteObject( hRegion ) ;
}
