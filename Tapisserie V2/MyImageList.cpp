// MyImageList.cpp : implementation file
//

#include "stdafx.h"
#include "tapisserie v2.h"
#include "MyImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyImageList

CMyImageList::CMyImageList()
{
}

CMyImageList::~CMyImageList()
{
}


BEGIN_MESSAGE_MAP(CMyImageList, CListCtrl)
	//{{AFX_MSG_MAP(CMyImageList)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyImageList message handlers

void CMyImageList::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// Create a memory DC compatible with the paint DC
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );
	
	CRect rClient;
	
	GetClientRect(&rClient);
	
	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rClient.Width(), rClient.Height() );
	CGdiObject*	pOldBitmap	=	 memDC.SelectObject( &bitmap );
	
	
	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
	
	

	// Transfert l'image memoire vers l'ecran
	dc.BitBlt( rClient.left, rClient.top, rClient.Width(), rClient.Height(), &memDC, 
				rClient.left, rClient.top, SRCCOPY );

	dc.SelectObject( pOldBitmap ) ;
	bitmap.DeleteObject() ;

	
}
