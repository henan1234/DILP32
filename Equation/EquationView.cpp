// EquationView.cpp : implementation of the CEquationView class
//

#include "stdafx.h"
#include "Equation.h"

#include "EquationDoc.h"
#include "EquationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEquationView

IMPLEMENT_DYNCREATE(CEquationView, CView)

BEGIN_MESSAGE_MAP(CEquationView, CView)
	//{{AFX_MSG_MAP(CEquationView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquationView construction/destruction

CEquationView::CEquationView()
{
	// TODO: add construction code here

}

CEquationView::~CEquationView()
{
}

BOOL CEquationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEquationView drawing

void CEquationView::OnDraw(CDC* pDC)
{
	CEquationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect	R ;
	GetClientRect( R ) ;

	pDC->SetMapMode( MM_ISOTROPIC ) ;
	pDC->SetWindowExt( 2000, -2000 ) ;
	pDC->SetWindowOrg( 1000, -1000 ) ;

	pDC->SetViewportExt( R.Width(), R.Height()) ;
	pDC->SetViewportOrg( R.Width(), R.Height() ) ;

	pDC->MoveTo( -1000, 0 ) ;
	pDC->LineTo( 1000, 0 )  ;
	pDC->MoveTo( 990, 10 ) ;
	pDC->LineTo( 1000, 0 ) ;
	pDC->MoveTo( 990, -10 ) ;

	pDC->MoveTo( 0, -1000 ) ;
	pDC->LineTo( 0, 1000 ) ;

	pDC->MoveTo( 10, 990 ) ;
	pDC->LineTo( 0, 1000 ) ;
	pDC->LineTo( -10, 990 ) ;

	const double	a	=	12;
	const double	b	=	10 ;

	TraceDroite( pDC, a, b, RGB( 255, 0, 0 ) ) ;
	MarquePointSurDroite( pDC, a, b, 75 ) ;

	double aP, bP ;
	TrouvePerpendiculaire( a, b, 75, &aP, &bP ) ;

	TraceDroite( pDC, aP, bP, RGB( 0, 255, 0 )) ;
}

/////////////////////////////////////////////////////////////////////////////
// CEquationView printing

BOOL CEquationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEquationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEquationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEquationView diagnostics

#ifdef _DEBUG
void CEquationView::AssertValid() const
{
	CView::AssertValid();
}

void CEquationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEquationDoc* CEquationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEquationDoc)));
	return (CEquationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEquationView message handlers

void CEquationView::TraceDroite(CDC * pDC, double a, double b, COLORREF Couleur)
{
//b	=	0 ;
	CPen	Pen( PS_SOLID, 1, Couleur ) ;

	CPen* pOld	=	pDC->SelectObject( &Pen ) ;

	if ( a !=  2147483,647 )
		{
		pDC->MoveTo( -1000, (int)((a*-1000.0 )+b)) ;
		pDC->LineTo( 1000, (int)((a*1000.0)+b) ) ;	
		}
	else
		{
		pDC->MoveTo( b, -1000 ) ;
		pDC->LineTo( b, 1000 ) ;
		}

	pDC->SelectObject( pOld ) ;
	Pen.DeleteObject() ;
}

void CEquationView::TrouvePerpendiculaire(double a, double b, double x, double * pa, double * pb)
{
	const double	y	=	a*x + b ;

	if ( a != 0.0 )
		{
		*pa	=	-1/a ;
		*pb	=	y - (*pa)*x  ;
		}
	else
		{
		*pa =	2147483647 ;
		*pb	=	x ;
		}
}

void CEquationView::MarquePointSurDroite(CDC * pDC, double a, double b, double x)
{
	const double	y	=	 a*x + b ;

	pDC->Rectangle( (int)x-20, (int)y-20, (int)x+20, (int)y+20 ) ;
}
