// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "FichiersDoubles.h"

#include "FichiersDoublesDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_PAINT()
	ON_COMMAND(IDM_NON_DUPLIQUES, OnNonDupliques)
	ON_UPDATE_COMMAND_UI(IDM_NON_DUPLIQUES, OnUpdateNonDupliques)
	ON_COMMAND(IDM_PROPRIETES, OnProprietes)
	ON_UPDATE_COMMAND_UI(IDM_PROPRIETES, OnUpdateProprietes)
	ON_COMMAND(ID_EDITION_OUVRE, OnEditionOuvre)
	ON_UPDATE_COMMAND_UI(ID_EDITION_OUVRE, OnUpdateEditionOuvre)
	ON_COMMAND(ID_EDITION_SUPPRIMEDUPPLIQUS, OnEditionSupprimeduppliqus)
	ON_UPDATE_COMMAND_UI(ID_EDITION_SUPPRIMEDUPPLIQUS, OnUpdateEditionSupprimeduppliqus)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	_AfficherNonDuppliques	=	TRUE ;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CFichiersDoublesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl & Tree			=	GetTreeCtrl() ;

	Tree.ModifyStyle( 0, TVS_DISABLEDRAGDROP|TVS_SHOWSELALWAYS|TVS_TRACKSELECT|TVS_INFOTIP|TVS_FULLROWSELECT, SWP_NOSIZE|SWP_NOZORDER|SWP_NOMOVE ) ;
	CFichiersDoublesDoc* pDoc = GetDocument();
	Tree.SetImageList( &(pDoc->GetImageList()), TVSIL_NORMAL ) ;

	Tree.DeleteAllItems() ;
	Tree.ModifyStyle( 0, TVS_HASBUTTONS|TVS_HASLINES|TVS_LINESATROOT|TVS_DISABLEDRAGDROP|TVS_SHOWSELALWAYS );

	pDoc->RemplitArbre( Tree, _AfficherNonDuppliques ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFichiersDoublesDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFichiersDoublesDoc)));
	return (CFichiersDoublesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CTreeCtrl	&	TreeCtrl	= GetTreeCtrl() ;

	HTREEITEM	hSelectionne	=	TreeCtrl.GetSelectedItem() ;

	CElement*	pElement		=	NULL ;

	if ( hSelectionne )
		{
		pElement =	(CElement*)TreeCtrl.GetItemData( hSelectionne ) ;
		}

	CFichiersDoublesDoc* pDoc = GetDocument();

	pDoc->Selectionne( pElement ) ;
		
	*pResult = 0;
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CTreeCtrl	&	TreeCtrl	= GetTreeCtrl() ;

	switch( lHint )
		{
		case HINT_VIDE:
			TreeCtrl.DeleteAllItems() ;
			break ;
		}
}

void CLeftView::OnPaint() 
{
	CPaintDC dc(this);
	CTreeCtrl&	tree	=	GetTreeCtrl() ;
	CFont*		font	=	tree.GetFont() ;
	
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
	
	memDC.SelectObject( font ) ;

	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );
	
	HTREEITEM hItem = tree.GetFirstVisibleItem();
	
	int n = tree.GetVisibleCount()+1;

	while( hItem && n--)
		{
		CRect rect;
		tree.GetItemRect( hItem, rect, FALSE ) ;
		rect.NormalizeRect() ;

		CRect Intersection ;
		if ( Intersection.IntersectRect( rcClip, rect ))
			AfficheElementTree( tree, memDC, hItem )  ;
		
		hItem = tree.GetNextVisibleItem( hItem );
		}

	// Transfert l'image memoire vers l'ecran
	dc.BitBlt( rcClip.left, rcClip.top, rcClip.Width(), rcClip.Height(), &memDC, 
				rcClip.left, rcClip.top, SRCCOPY );

	dc.SelectObject( pOldBitmap ) ;
	bitmap.DeleteObject() ;
}

void CLeftView::AfficheElementTree(CTreeCtrl &Tree, CDC &dc, HTREEITEM hItem)
{
	CRect rect ;
	Tree.GetItemRect( hItem, rect, TRUE ) ;

	DWORD	Data	=	Tree.GetItemData( hItem ) ;
	if ( Data == 0 )
		return ;

	CElement * pElement	=	(CElement*)Data ;
	if ( ! pElement->IsKindOf( RUNTIME_CLASS( CElement )))
		return ;

	pElement->SetAttributs( dc ) ;

	UINT	ItemFlags	=	Tree.GetItemState( hItem, TVIS_BOLD | TVIS_DROPHILITED | TVIS_SELECTED ) ;
	rect.DeflateRect( 2, 2 ) ;

	if ( ItemFlags & ( /*TVIS_DROPHILITED |*/ TVIS_SELECTED ))	
		{
		if ( CWnd::GetFocus() == this )
			{
			dc.FillSolidRect( rect, GetSysColor(COLOR_HIGHLIGHT)) ;
			}
		else
			{
			dc.FillSolidRect( rect, GetSysColor(COLOR_INACTIVECAPTION) ) ;
			}

		// Dessiner un rectangle 'focus' si l'item est selectionne
		if ( ItemFlags & ( TVIS_SELECTED ))
			{
			CRect RFocus( rect ) ;
			RFocus.InflateRect( 2, 2 ) ;
			dc.DrawFocusRect( RFocus ) ;
			}
		}
		else
			{
			dc.FillSolidRect( rect, GetSysColor( COLOR_WINDOW )) ;
			}

		CString	sItem = Tree.GetItemText( hItem ) ;
		Tree.GetItemRect( hItem, &rect, TRUE );

		dc.DrawText( sItem, rect, DT_SINGLELINE | DT_VCENTER | DT_CENTER ) ;

}

void CLeftView::OnNonDupliques() 
{
	_AfficherNonDuppliques	=	! _AfficherNonDuppliques ;

	CTreeCtrl& tree	=	GetTreeCtrl() ;
	tree.DeleteAllItems() ;

	CFichiersDoublesDoc* pDoc = GetDocument();
	pDoc->RemplitArbre( tree, _AfficherNonDuppliques ) ;
}

void CLeftView::OnUpdateNonDupliques(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck( ! _AfficherNonDuppliques ) ;
}

void CLeftView::OnProprietes() 
{
	CTreeCtrl& Tree		=	GetTreeCtrl() ;
	HTREEITEM	hItem	=	Tree.GetSelectedItem() ;
	if ( hItem	== NULL )
		return ;

	DWORD		Data	=	Tree.GetItemData( hItem ) ;
	if ( Data == 0 )
		return ;

	CElement*	pElement=	(CElement*)Data ;

	pElement->AfficheProprietes( this ) ;
}

void CLeftView::OnUpdateProprietes(CCmdUI* pCmdUI) 
{
	HTREEITEM	hItem	=	GetTreeCtrl().GetSelectedItem() ;

	pCmdUI->Enable( hItem != NULL ) ;
}



void CLeftView::OnEditionOuvre() 
{
	CTreeCtrl& Tree		=	GetTreeCtrl() ;
	HTREEITEM	hItem	=	Tree.GetSelectedItem() ;
	if ( hItem	== NULL )
		return ;

	DWORD		Data	=	Tree.GetItemData( hItem ) ;
	if ( Data == 0 )
		return ;

	CElement*	pElement=	(CElement*)Data ;

	pElement->Ouvre( this ) ;
}

void CLeftView::OnUpdateEditionOuvre(CCmdUI* pCmdUI) 
{
	HTREEITEM	hItem	=	GetTreeCtrl().GetSelectedItem() ;

	pCmdUI->Enable( hItem != NULL ) ;
}

void CLeftView::OnEditionSupprimeduppliqus() 
{
	CTreeCtrl& Tree		=	GetTreeCtrl() ;
	HTREEITEM	hItem	=	Tree.GetSelectedItem() ;
	if ( hItem	== NULL )
		return ;

	DWORD		Data	=	Tree.GetItemData( hItem ) ;
	if ( Data == 0 )
		return ;

	CElement*	pElement=	(CElement*)Data ;

	if ( ! pElement->IsKindOf( RUNTIME_CLASS( CFichier )))
		return ;
	CFichier* pFichier	=	(CFichier*)pElement ;

	CFichiersDoublesDoc* pDoc = GetDocument();
	pDoc->SupprimeDuppliques( pFichier ) ;


	Tree.DeleteAllItems() ;
	pDoc->RemplitArbre( Tree, _AfficherNonDuppliques ) ;
}

void CLeftView::OnUpdateEditionSupprimeduppliqus(CCmdUI* pCmdUI) 
{
	HTREEITEM	hItem	=	GetTreeCtrl().GetSelectedItem() ;
	if ( hItem	== NULL )
		{
		pCmdUI->Enable( FALSE ) ;
		return ;
		}

	DWORD		Data	=	GetTreeCtrl().GetItemData( hItem ) ;
	if ( Data == 0 )
		{
		pCmdUI->Enable( FALSE ) ;
		return ;
		}

	CElement*	pElement=	(CElement*)Data ;
	pCmdUI->Enable( pElement->ADesDuppliques()) ;
}
