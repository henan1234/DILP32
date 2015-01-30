// FilesCollectionView.cpp : implementation of the CFilesCollectionView class
//

#include "stdafx.h"
#include "FilesCollection.h"

#include "FilesCollectionDoc.h"
#include "FilesCollectionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView

IMPLEMENT_DYNCREATE(CFilesCollectionView, CListView)

BEGIN_MESSAGE_MAP(CFilesCollectionView, CListView)
	//{{AFX_MSG_MAP(CFilesCollectionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView construction/destruction

CFilesCollectionView::CFilesCollectionView()
{
	// TODO: add construction code here

}

CFilesCollectionView::~CFilesCollectionView()
{
}

BOOL CFilesCollectionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView drawing

void CFilesCollectionView::OnDraw(CDC* pDC)
{
	CFilesCollectionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFilesCollectionView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView printing

BOOL CFilesCollectionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFilesCollectionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFilesCollectionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView diagnostics

#ifdef _DEBUG
void CFilesCollectionView::AssertValid() const
{
	CListView::AssertValid();
}

void CFilesCollectionView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFilesCollectionDoc* CFilesCollectionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFilesCollectionDoc)));
	return (CFilesCollectionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionView message handlers
