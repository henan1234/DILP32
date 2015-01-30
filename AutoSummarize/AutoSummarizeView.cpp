// AutoSummarizeView.cpp : implementation of the CAutoSummarizeView class
//

#include "stdafx.h"
#include "AutoSummarize.h"

#include "AutoSummarizeDoc.h"
#include "AutoSummarizeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView

IMPLEMENT_DYNCREATE(CAutoSummarizeView, CView)

BEGIN_MESSAGE_MAP(CAutoSummarizeView, CView)
	//{{AFX_MSG_MAP(CAutoSummarizeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView construction/destruction

CAutoSummarizeView::CAutoSummarizeView()
{
	// TODO: add construction code here

}

CAutoSummarizeView::~CAutoSummarizeView()
{
}

BOOL CAutoSummarizeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView drawing

void CAutoSummarizeView::OnDraw(CDC* pDC)
{
	CAutoSummarizeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SelectStockObject( ANSI_VAR_FONT ) ;
	pDC->SetTextColor( GetSysColor( COLOR_WINDOWTEXT )) ;
	pDC->SetBkColor( GetSysColor( COLOR_WINDOW )) ;

	TEXTMETRIC	me ;
	pDC->GetTextMetrics( &me ) ;
	
	CString Phrase ;
	
	CRect R ;
	GetClientRect( R ) ;

	for ( int i = 0; i < pDoc->_Mots.GetSize(); i++)
		{
		Phrase += pDoc->_Mots[i] + " " ;
		}

	pDC->DrawText( Phrase, R, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView printing

BOOL CAutoSummarizeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAutoSummarizeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAutoSummarizeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView diagnostics

#ifdef _DEBUG
void CAutoSummarizeView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoSummarizeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoSummarizeDoc* CAutoSummarizeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoSummarizeDoc)));
	return (CAutoSummarizeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeView message handlers
