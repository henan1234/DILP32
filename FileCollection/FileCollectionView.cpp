// FileCollectionView.cpp : implementation of the CFileCollectionView class
//

#include "stdafx.h"
#include "FileCollection.h"

#include "FileCollectionDoc.h"
#include "FileCollectionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView

IMPLEMENT_DYNCREATE(CFileCollectionView, CListView)

BEGIN_MESSAGE_MAP(CFileCollectionView, CListView)
	//{{AFX_MSG_MAP(CFileCollectionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView construction/destruction

CFileCollectionView::CFileCollectionView()
{
	// TODO: add construction code here

}

CFileCollectionView::~CFileCollectionView()
{
}

BOOL CFileCollectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView drawing

void CFileCollectionView::OnDraw(CDC* pDC)
{
	CFileCollectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFileCollectionView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView printing

BOOL CFileCollectionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFileCollectionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFileCollectionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView diagnostics

#ifdef _DEBUG
void CFileCollectionView::AssertValid() const
{
	CListView::AssertValid();
}

void CFileCollectionView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFileCollectionDoc* CFileCollectionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileCollectionDoc)));
	return (CFileCollectionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionView message handlers
