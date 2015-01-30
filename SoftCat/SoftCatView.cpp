// SoftCatView.cpp : implementation of the CSoftCatView class
//

#include "stdafx.h"
#include "SoftCat.h"

#include "SoftCatSet.h"
#include "SoftCatDoc.h"
#include "SoftCatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftCatView

IMPLEMENT_DYNCREATE(CSoftCatView, CRecordView)

BEGIN_MESSAGE_MAP(CSoftCatView, CRecordView)
	//{{AFX_MSG_MAP(CSoftCatView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoftCatView construction/destruction

CSoftCatView::CSoftCatView()
	: CRecordView(CSoftCatView::IDD)
{
	//{{AFX_DATA_INIT(CSoftCatView)
	m_pSet = NULL;
	m_Nom = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSoftCatView::~CSoftCatView()
{
}

void CSoftCatView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoftCatView)
	DDX_Text(pDX, IDC_NOM, m_Nom);
	//}}AFX_DATA_MAP
}

BOOL CSoftCatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CSoftCatView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_softCatSet;
	CRecordView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSoftCatView printing

BOOL CSoftCatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSoftCatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSoftCatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSoftCatView diagnostics

#ifdef _DEBUG
void CSoftCatView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CSoftCatView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CSoftCatDoc* CSoftCatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSoftCatDoc)));
	return (CSoftCatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoftCatView database support
CRecordset* CSoftCatView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CSoftCatView message handlers
