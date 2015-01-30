// Universe Creation KitView.cpp : implementation of the CUniverseCreationKitView class
//

#include "stdafx.h"
#include "Universe Creation Kit.h"

#include "Universe Creation KitDoc.h"
#include "Universe Creation KitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView

IMPLEMENT_DYNCREATE(CUniverseCreationKitView, CView)

BEGIN_MESSAGE_MAP(CUniverseCreationKitView, CView)
	//{{AFX_MSG_MAP(CUniverseCreationKitView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView construction/destruction

CUniverseCreationKitView::CUniverseCreationKitView()
{
	// TODO: add construction code here

}

CUniverseCreationKitView::~CUniverseCreationKitView()
{
}

BOOL CUniverseCreationKitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView drawing

void CUniverseCreationKitView::OnDraw(CDC* pDC)
{
	CUniverseCreationKitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView printing

BOOL CUniverseCreationKitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUniverseCreationKitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUniverseCreationKitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView diagnostics

#ifdef _DEBUG
void CUniverseCreationKitView::AssertValid() const
{
	CView::AssertValid();
}

void CUniverseCreationKitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUniverseCreationKitDoc* CUniverseCreationKitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUniverseCreationKitDoc)));
	return (CUniverseCreationKitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView message handlers

BOOL CUniverseCreationKitView::OnEraseBkgnd(CDC* pDC) 
{
	CRect R ;
	GetClientRect( R ) ;

	FillRect(pDC->m_hDC, R, (HBRUSH)GetStockObject( BLACK_BRUSH )) ;

	return TRUE ;
}
