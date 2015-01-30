// MyTree.cpp: implementation of the CMyTree class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "MyTree.h"
#include "element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP( CMyTree, CTreeCtrl)
	//{{AFX_MSG_MAP(CInpiTree)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMyTree::CMyTree()
{
	_pHeader	=	NULL ;
}

CMyTree::~CMyTree()
{

}

void CMyTree::OnPaint()
{
	CPaintDC dc(this);
	
	// Create a memory DC compatible with the paint DC
	CDC memDC;
	memDC.CreateCompatibleDC( &dc );
	
	CRect rcClip, rcClient;
	dc.GetClipBox( &rcClip );
	rcClip.InflateRect( 0, 2 ) ;

	rcClip.NormalizeRect() ;
	GetClientRect(&rcClient);
	
	// Select a compatible bitmap into the memory DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap( &dc, rcClient.Width(), rcClient.Height() );
	CGdiObject*	pOldBitmap	=	 memDC.SelectObject( &bitmap );
	
	// Set clip region to be same as that in paint DC
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcClip );
	memDC.SelectClipRgn(&rgn);
	rgn.DeleteObject();
	

	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
	
	HTREEITEM hItem = GetFirstVisibleItem();
	
	int n = GetVisibleCount()+1;
	memDC.SelectStockObject( ANSI_VAR_FONT ) ;
	
	while( hItem && n--)
		{
		CRect rect;
		GetItemRect( hItem, rect, FALSE ) ;
		rect.NormalizeRect() ;

		CRect Intersection ;
		if ( Intersection.IntersectRect( rcClip, rect ))
			AfficheElement( memDC, hItem ) ;

		
		hItem = GetNextVisibleItem( hItem );
		}


	// Affiche tous les attributs de l'item dans les cases donnees par le header
	memDC.SelectStockObject( LTGRAY_BRUSH ) ;
	const int NB	=	_pHeader->GetItemCount() ;
	for ( int i = 0; i < NB; i++)
		{
		CRect RItem ;
		_pHeader->GetItemRect( i, RItem ) ;

		memDC.FillSolidRect( RItem.right-1, rcClip.top, 1, rcClip.Height(), RGB( 128, 128, 128 ) ) ;
		}

	// Transfert l'image memoire vers l'ecran
	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, 
				rcClip.left, rcClip.top, SRCCOPY );

	dc.SelectObject( pOldBitmap ) ;
	bitmap.DeleteObject() ;
}

void CMyTree::AfficheElement(CDC &DC, HTREEITEM hItem)
{
	if ( !_pHeader )
		return ;

	CRect RClient ;
	GetClientRect( RClient ) ;

	CRect R ;
	GetItemRect( hItem, R, TRUE ) ;
	R.right=	RClient.right ;

	// Retrouve l'adresse de l'item
	TV_ITEM Item ;
	Item.mask	=	TVIF_PARAM | TVIF_STATE;
	Item.hItem	=	hItem;
	Item.lParam	=	0 ;
	GetItem( &Item ) ;

	CElement * pElement	=	(CElement*)Item.lParam ;
	if (! pElement )
		return ;


	if ( Item.state & TVIS_SELECTED )
		{
		DC.FillSolidRect( R, GetSysColor( COLOR_HIGHLIGHT )) ;
		DC.SetBkColor( GetSysColor( COLOR_HIGHLIGHT )) ;
		DC.SetTextColor( GetSysColor( COLOR_HIGHLIGHTTEXT )) ;
		}
	else
		{
		DC.FillSolidRect( R, GetSysColor( COLOR_WINDOW )) ;
		DC.SetBkColor( GetSysColor( COLOR_WINDOW )) ;
		DC.SetTextColor( GetSysColor( COLOR_WINDOWTEXT )) ;
		}

	R.DeflateRect( 1, 0 ) ;

	// Affiche tous les attributs de l'item dans les cases donnees par le header
	const int NB	=	_pHeader->GetItemCount() ;
	for ( int i = 0; i < NB; i++)
		{
		CRect RItem ;
		_pHeader->GetItemRect( i, RItem ) ;
		RItem.top			=	R.top ;
		RItem.bottom		=	R.bottom ;
		RItem.left			=	max( RItem.left, R.left ) ;

		char Buffer[1024] ;
		HDITEM	item ;
		item.mask		=	HDI_TEXT ;
		item.pszText	=	Buffer ;
		item.cchTextMax	=	sizeof( Buffer ) ;
		_pHeader->GetItem( i, &item ) ;		

		CString Texte	=	pElement->GetAttribut( Buffer ) ;
		RItem.DeflateRect( 4, 0 ) ;
		DC.DrawText( Texte, RItem, DT_LEFT | DT_SINGLELINE | DT_PATH_ELLIPSIS | DT_NOPREFIX | DT_VCENTER ) ;
		}
}
