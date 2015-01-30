// CouleursWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Vasarely.h"
#include "CouleursWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCouleursWnd

CCouleursWnd::CCouleursWnd()
{
}

CCouleursWnd::~CCouleursWnd()
{
}


BEGIN_MESSAGE_MAP(CCouleursWnd, CWnd)
	//{{AFX_MSG_MAP(CCouleursWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCouleursWnd message handlers

void CCouleursWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	for ( int x = 0; x < 256; x+=2 )
		for ( int y = 0; y < 256; y+=2 )
			{
			CBrush	Brosse( RGB( x, y, 0 ) ) ;
			CBrush*	pOld	=	dc.SelectObject( &Brosse ) ;

	
			dc.PatBlt( x, y, 2, 2, PATCOPY ) ;

			dc.SelectObject( pOld ) ;
			Brosse.DeleteObject() ;
			}
}
