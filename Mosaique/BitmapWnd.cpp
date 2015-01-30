// BitmapWnd.cpp : implementation file
//

#include "stdafx.h"
#include "mosaique.h"
#include "BitmapWnd.h"
#include "image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd

CBitmapWnd::CBitmapWnd()
{
}

CBitmapWnd::~CBitmapWnd()
{
}


BEGIN_MESSAGE_MAP(CBitmapWnd, CWnd)
	//{{AFX_MSG_MAP(CBitmapWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd message handlers

void CBitmapWnd::SetImage(CImage * pImage)
{
	_pImage	=	pImage ;
	SetWindowText( pImage->Nom()) ;

	Invalidate( TRUE ) ;
}

void CBitmapWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if ( ! _pImage )
		return ;

	_pImage->Dessine( dc, 0, 0, 1.0 );
}
