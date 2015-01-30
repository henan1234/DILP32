// FichiersDoublesView.cpp : implementation of the CFichiersDoublesView class
//

#include "stdafx.h"
#include "FichiersDoubles.h"

#include "FichiersDoublesDoc.h"
#include "FichiersDoublesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView

IMPLEMENT_DYNCREATE(CFichiersDoublesView, CListView)

BEGIN_MESSAGE_MAP(CFichiersDoublesView, CListView)
	//{{AFX_MSG_MAP(CFichiersDoublesView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView construction/destruction

CFichiersDoublesView::CFichiersDoublesView()
{
	// TODO: add construction code here

}

CFichiersDoublesView::~CFichiersDoublesView()
{
}

BOOL CFichiersDoublesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView drawing

void CFichiersDoublesView::OnDraw(CDC* pDC)
{
	CFichiersDoublesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void CFichiersDoublesView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	CListCtrl & Liste	=	GetListCtrl() ;

	Liste.ModifyStyle( LVS_ICON|LVS_SMALLICON|LVS_LIST, LVS_REPORT , 0 ) ;

	static BOOL  ColonneInseree	=	FALSE ;
	if ( ! ColonneInseree)
		{
		Liste.InsertColumn( 0, "Identiques", LVCFMT_LEFT, 200, 0 ) ;
		ColonneInseree	=	TRUE ;
		}
}

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView printing

BOOL CFichiersDoublesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFichiersDoublesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFichiersDoublesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView diagnostics

#ifdef _DEBUG
void CFichiersDoublesView::AssertValid() const
{
	CListView::AssertValid();
}

void CFichiersDoublesView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFichiersDoublesDoc* CFichiersDoublesView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFichiersDoublesDoc)));
	return (CFichiersDoublesDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesView message handlers
void CFichiersDoublesView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CFichiersDoublesView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	switch(lHint )
		{
		case HINT_VIDE:
			GetListCtrl().DeleteAllItems() ;
			break ;

		default:
			{
			CFichiersDoublesDoc* pDoc	= GetDocument();
			CListCtrl& Liste			= GetListCtrl() ;
			Liste.DeleteAllItems() ;

			CElement*	pElement		= pDoc->GetSelectionne() ;
			if ( pElement )
				pElement->RemplitListe( Liste ) ;
			}
		}
}

