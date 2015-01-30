// DumpView.cpp : implementation of the CDumpView class
//

#include "stdafx.h"
#include "Dump.h"

#include "DumpDoc.h"
#include "DumpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumpView

IMPLEMENT_DYNCREATE(CDumpView, CScrollView)

BEGIN_MESSAGE_MAP(CDumpView, CScrollView)
	//{{AFX_MSG_MAP(CDumpView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpView construction/destruction

CDumpView::CDumpView()
{
	// TODO: add construction code here

}

CDumpView::~CDumpView()
{
}

BOOL CDumpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDumpView drawing

void CDumpView::OnDraw(CDC* pDC)
{
	PrepareDC( *pDC) ;
	CDumpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect	R ;
	GetClientRect( R ) ;

	CPoint	ScrollPos	=	GetScrollPosition() ;
	int		y			=	0 ;

	CSize	TailleCaracteres	=	TailleCaractere() ;

	int	NbLignes		=	pDoc->NbLignes() ;

	for ( int NoLigne	= 0;  NoLigne < NbLignes; NoLigne ++ )
		{
		if ( y >= ScrollPos.y )
			{
			CString	Ligne	=	pDoc->GetLigne( NoLigne ) ;

			pDC->TextOut( 0, y, Ligne ) ;
			}

		y += TailleCaracteres.cy ;
		NoLigne ++ ;
		}
}


void CDumpView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;

	CDumpDoc* pDoc = GetDocument();
	const int	NbLignes	=	pDoc->NbLignes() ;
	const CSize	TailleCaracteres=	TailleCaractere() ;
	const int	LongueurLigne=	pDoc->LongueurLigne() ;


	sizeTotal.cx	=	NbLignes*TailleCaracteres.cy ;
	sizeTotal.cy	=	LongueurLigne*TailleCaracteres.cy ;
	SetScrollSizes(MM_TEXT, sizeTotal, sizeDefault, TailleCaracteres );
}

/////////////////////////////////////////////////////////////////////////////
// CDumpView printing

BOOL CDumpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDumpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDumpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDumpView diagnostics

#ifdef _DEBUG
void CDumpView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDumpView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDumpDoc* CDumpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDumpDoc)));
	return (CDumpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumpView message handlers


// Retourne la taille d'un caractere
CSize CDumpView::TailleCaractere()
{
	CClientDC		Dc( this ) ;

	PrepareDC( Dc ) ;

	TEXTMETRIC Tm ;
	Dc.GetTextMetrics( &Tm ) ;

	return CSize( Tm.tmMaxCharWidth, Tm.tmHeight + Tm.tmExternalLeading ) ;
}

void CDumpView::PrepareDC(CDC & Dc)
{
	Dc.SelectStockObject( ANSI_FIXED_FONT ) ;
	Dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT )) ;
	Dc.SetBkColor( GetSysColor( COLOR_WINDOW )) ;
}


void CDumpView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	
	CDumpDoc*	pDoc	=	GetDocument() ;	
	if ( ! pDoc )
		return ;

	const int	NbLignes	=	pDoc->NbLignes() ;
	const CSize	TailleCaracteres=	TailleCaractere() ;
	const int	LongueurLigne=	pDoc->LongueurLigne() ;
	CSize	sizeTotal ;

	sizeTotal.cx	=	NbLignes*TailleCaracteres.cy ;
	sizeTotal.cy	=	LongueurLigne*TailleCaracteres.cy ;
	SetScrollSizes(MM_TEXT, sizeTotal, sizeDefault, TailleCaracteres );
}
