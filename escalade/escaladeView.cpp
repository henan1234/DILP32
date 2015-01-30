// escaladeView.cpp : implementation of the CEscaladeView class
//

#include "stdafx.h"
#include "escalade.h"
#include "math.h"

#include "escaladeDoc.h"
#include "escaladeView.h"
#include "Droite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LONGUEUR_CUISSE	50
#define LONGUEUR_JAMBE	50
#define LONGUEUR_AVANT_BRAS	50
#define LONGUEUR_BRAS		50
#define DISTANCE_EPAULES	-35
#define DISTANCE_HANCHES	20
#define DISTANCE_TETE		20

#define LARGEUR_EPAULE	30
#define LARGEUR_HANCHE	20

#define COULEUR_PEAU	RGB(199,179,141) 
#define COULEUR_MAILLOT RGB(  0,128,255)
#define COULEUR_SHORT	RGB(0,0,0)

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView

IMPLEMENT_DYNCREATE(CEscaladeView, CView)

BEGIN_MESSAGE_MAP(CEscaladeView, CView)
	//{{AFX_MSG_MAP(CEscaladeView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView construction/destruction

CEscaladeView::CEscaladeView()
{

	_ButtonDown		=	FALSE ;
}

CEscaladeView::~CEscaladeView()
{
}

BOOL CEscaladeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView drawing

void CEscaladeView::OnDraw(CDC* pDC)
{
/*	CEscaladeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

*/

	DessineBras( pDC, _MainGauche, _CoudeGauche, _EpauleGauche ) ;
	DessineBras( pDC, _MainDroite, _CoudeDroit, _EpauleDroite ) ;
	DessineJambe( pDC, _PiedGauche, _GenouGauche, _HancheGauche ) ;
	DessineJambe( pDC, _PiedDroit, _GenouDroit, _HancheDroite ) ;
	
	DessineCorps( pDC, _EpauleGauche, _EpauleDroite, _HancheGauche, _HancheDroite ) ;



/*
	Point Pt1( 100, 100 ) ;
	Point Pt2( 250, 384 ) ;

	pDC->PatBlt( Pt1.x-1, Pt1.y-1, 2, 2, BLACKNESS ) ;
	pDC->PatBlt( Pt2.x-1, Pt2.y-1, 2, 2, BLACKNESS ) ;

	Droite dr( Pt1, Pt2 ) ;

	DessineDroite( pDC, dr ) ;

	Point PtC( (Pt1.x+Pt2.x)/2, (Pt1.y+Pt2.y)/2) ;
	pDC->PatBlt( PtC.x-2, PtC.y-2, 4, 4, BLACKNESS ) ;

	Point PtT	=	dr.PointADistance( PtC, COEFF_EPAULE ) ;
	Droite LigneEpaules	=	dr.Perpendiculaire( PtT ) ;
	DessineDroite( pDC, LigneEpaules ) ;

	Point EpauleDroite	=	LigneEpaules.PointADistance( PtT, 50 ) ;
	Point EpauleGauche	=	LigneEpaules.PointADistance( PtT, -50 ) ;

	PtT			=	dr.PointADistance( PtC, COEFF_HANCHE ) ;
	Droite LigneHanches	=	dr.Perpendiculaire( PtT ) ;
	DessineDroite( pDC, LigneHanches ) ;

	Point	HancheDroite=	LigneHanches.PointADistance( PtT, 40 ) ;
	Point	HancheGauche=	LigneHanches.PointADistance( PtT, -40 ) ;

	pDC->MoveTo( EpauleDroite ) ;
	pDC->LineTo( EpauleGauche ) ;
	pDC->LineTo( HancheGauche ) ;
	pDC->LineTo( HancheDroite ) ;
	pDC->LineTo( EpauleDroite ) ;
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView printing

BOOL CEscaladeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEscaladeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEscaladeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView diagnostics

#ifdef _DEBUG
void CEscaladeView::AssertValid() const
{
	CView::AssertValid();
}

void CEscaladeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEscaladeDoc* CEscaladeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEscaladeDoc)));
	return (CEscaladeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEscaladeView message handlers

void CEscaladeView::CalculeGenouGauche()
{
	CoupleDePoints	Couple ;
	if ( ! CalculeIntersectionDeuxCercles(_HancheGauche, _PiedGauche, LONGUEUR_CUISSE, LONGUEUR_JAMBE, &Couple ))
		return ;


	Point P1, P2 ;
	Couple.GetPoints( &P1, &P2 ) ;

	// Choisir le plus a gauche ou le plus haut
	if ( P1.x < P2.x )
		_GenouGauche	=	P1 ;
	else
		if ( P1.x > P2.x )
			_GenouGauche	=	P2 ;
		else
			if ( P1.y < P2.y )
				_GenouGauche	=	P1 ;
			else
				_GenouGauche	=	P2 ;
}

void CEscaladeView::CalculeGenouDroit()
{
	CoupleDePoints	Couple ;
	if ( ! CalculeIntersectionDeuxCercles(_HancheDroite, _PiedDroit, LONGUEUR_CUISSE, LONGUEUR_JAMBE, &Couple ))
		return ;

	Point P1, P2 ;
	Couple.GetPoints( &P1, &P2 ) ;

	// Choisir le plus haut ou le plus a droite
	if ( P1.y < P2.y )
		_GenouDroit	=	P1 ;
	else
	if ( P1.y > P2.y )
		_GenouDroit = P2 ;
	else
	if ( P1.x < P2.x )
		_GenouDroit	=	P2 ;
	else
		_GenouDroit	=	P1 ;
		
}

void CEscaladeView::CalculeCoudeGauche()
{
	CoupleDePoints	Couple ;
	if ( ! CalculeIntersectionDeuxCercles(_MainGauche, _EpauleGauche, LONGUEUR_AVANT_BRAS, LONGUEUR_BRAS, &Couple ))
		return ;

	Point P1, P2 ;
	Couple.GetPoints( &P1, &P2 ) ;

	// Choisir le plus a gauche ou le plus bas
	if ( P1.x < P2.x )
		_CoudeGauche	=	P1 ;
	else
		if ( P1.x > P2.x )
			_CoudeGauche	=	P2 ;
	else
		if ( P1.y > P2.y )
				_CoudeGauche	=	P1 ;
	else
				_CoudeGauche	=	P2 ;

}

void CEscaladeView::CalculeCoudeDroit()
{
	CoupleDePoints	Couple ;
	if ( ! CalculeIntersectionDeuxCercles(_MainDroite, _EpauleDroite, LONGUEUR_AVANT_BRAS, LONGUEUR_BRAS, &Couple ))
		return ;

	Point P1, P2 ;
	Couple.GetPoints( &P1, &P2 ) ;
	
	// Choisir le plus a droite ou le plus bas
	if ( P1.x < P2.x )
		_CoudeDroit	=	P2 ;
	else
		if ( P1.x > P2.x )
			_CoudeDroit	=	P1 ;
		else
			if ( P1.y > P2.y )
				_CoudeDroit	=	P1 ;
			else
				_CoudeDroit	=	P2 ;


}

double doubleabs( double d )
{
	if ( d >= 0.0 )
		return d ;
	else
		return -d ;
}
///////////////////////////////////////////////////////////////////////////////
// Calcule l'intersection deux deux cercles
///////////////////////////////////////////////////////////////////////////////
BOOL CEscaladeView::CalculeIntersectionDeuxCercles(Point C0, Point C1, int R0, int R1, CoupleDePoints * pCouple)
{
#define CARRE(x)	(x)*(x)

	const double d	=	sqrt( CARRE(C0.x-C1.x) + CARRE(C0.y-C1.y)) ;
	if ( d > R0+R1 )
		// Pas de solution
		return FALSE ;

	const double a	=	(double)((R0*R0)-double(R1*R1)+d*d) / ( d + d ) ;
	const double h	=	sqrt( (double)(R0*R0) - (a*a)) ;

	Point Pt ;	// Le point central
	Pt.x			=	(long)((double)C0.x + a * (C1.x - C0.x) / d ) ;
	Pt.y			=	(long)((double)C0.y + a * (C1.y - C0.y) / d ) ;


	Point P1, P2 ;
	P1.x			=	(long)( Pt.x + h * ( C1.y - C0.y)/d) ;
	P1.y			=	(long)( Pt.y - h * ( C1.x - C0.x)/d) ;

	P2.x			=	(long)( Pt.x - h * ( C1.y - C0.y)/d) ;
	P2.y			=	(long)( Pt.y + h * ( C1.x - C0.x)/d) ;

	pCouple->SetPoints( P1, P2 ) ;
	return TRUE ;
}

#define Carre(x)	(x)*(x)
#define Distance(p1,p2)	sqrt( Carre((p1).x-(p2).x) + Carre((p1).y-(p2).y))
void CEscaladeView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture() ;
	_ButtonDown	=	TRUE ;
	
	_Deplace	=	&_MainDroite ;

	if ( Distance( point, *_Deplace ) > Distance( point, _MainGauche ))
		_Deplace	=	&_MainGauche ;

	if ( Distance( point, *_Deplace ) > Distance( point, _PiedDroit ))
		_Deplace	=	&_PiedDroit ;

	if ( Distance( point, *_Deplace ) > Distance( point, _PiedGauche ))
		_Deplace	=	&_PiedGauche ;

	CView::OnLButtonDown(nFlags, point);
}

void CEscaladeView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( _ButtonDown )
		ReleaseCapture() ;
	
	_ButtonDown	=	FALSE ;
	CalculeArticulations() ;
	Invalidate(TRUE) ;

	CView::OnLButtonUp(nFlags, point);
}

void CEscaladeView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( _ButtonDown)
	{
	_Deplace->x	=	point.x ;
	_Deplace->y	=	point.y ;
	CalculeArticulations()  ;
	Invalidate(TRUE ) ;
	}

	CView::OnMouseMove(nFlags, point);
}



void CEscaladeView::CalculeArticulations()
{
	CalculeCorps() ;
//	CalculeEpauleGauche() ;
//	CalculeEpauleDroite() ;
//	CalculeHancheGauche() ;
//	CalculeHancheDroite() ;

	CalculeCoudeGauche() ;
	CalculeCoudeDroit() ;
	CalculeGenouGauche() ;
	CalculeGenouDroit() ;
}

void CEscaladeView::DessineBras( CDC * pDC, Point Main, Point Coude, Point Epaule)
{
	CPen	penPeau ;
	penPeau.CreatePen( PS_SOLID, 7, COULEUR_PEAU ) ;
	CPen *pOld	=	pDC->SelectObject( &penPeau ) ;
	pDC->MoveTo( Main ) ;
	pDC->LineTo( Coude ) ;

	CPen penManche ;
	penManche.CreatePen( PS_SOLID, 7, COULEUR_MAILLOT ) ;
	pDC->SelectObject( &penManche ) ;

	pDC->LineTo( Epaule ) ;

	pDC->SelectObject( pOld ) ;
	penPeau.DeleteObject() ;
	penManche.DeleteObject() ;
}

void CEscaladeView::DessineJambe(CDC *pDC, Point Pied, Point Genou, Point Hanche)
{
	CPen	penPeau ;
	penPeau.CreatePen( PS_SOLID, 11, COULEUR_PEAU ) ;
	CPen *pOld	=	pDC->SelectObject( &penPeau ) ;
	pDC->MoveTo( Pied ) ;
	pDC->LineTo( Genou ) ;

	CPen penManche ;
	penManche.CreatePen( PS_SOLID, 13, COULEUR_SHORT ) ;
	pDC->SelectObject( &penManche ) ;

	pDC->LineTo( Hanche ) ;

	pDC->SelectObject( pOld ) ;
	penPeau.DeleteObject() ;
	penManche.DeleteObject() ;

}

void CEscaladeView::DessineCorps(CDC *pDC, Point EpauleGauche, Point EpauleDroite, Point HancheGauche, Point HancheDroite)
{
	CPoint Pts[4]	=	{ EpauleGauche, EpauleDroite, HancheDroite, HancheGauche } ;
	CBrush	br( COULEUR_MAILLOT ) ;
	CBrush* pOld	=	pDC->SelectObject( &br ) ;

	pDC->Polygon( Pts, 4 ) ;
	pDC->SelectObject( pOld ) ;
	br.DeleteObject() ;

	pDC->SelectStockObject( BLACK_BRUSH ) ;
	pDC->SelectStockObject( BLACK_PEN ) ;
	pDC->Ellipse( (int)_Tete.x-20, (int)_Tete.y-20, (int)_Tete.x+20, (int)_Tete.y+20 ) ;
}

void CEscaladeView::CalculeCorps()
{
	// Trouve le milieu du segment passant par les deux mains
	Point	MilieuMains	;
	MilieuMains.x	=	(_MainDroite.x + _MainGauche.x)/2 ;
	MilieuMains.y	=	(_MainDroite.y + _MainGauche.y)/2 ;

	// Trouve le milieu du segment passant par les deux pieds
	Point	MilieuPieds	;
	MilieuPieds.x	=	(_PiedDroit.x + _PiedGauche.x)/2 ;
	MilieuPieds.y	=	(_PiedDroit.y + _PiedGauche.y)/2 ;

	// Centre de gravite ( milieu des 4 extremites )
	Point CG ;
	CG.x			=	(MilieuMains.x + MilieuPieds.x)/2 ;
	CG.y			=	(MilieuMains.y + MilieuPieds.y)/2 ;

	// La colonne vertebrale est sur la ligne qui passe par les points 
	// MilieuMains et MilieuPieds
	Droite colonne( MilieuMains, MilieuPieds ) ;

	// Calcule les epaules
	CoupleDePoints ColonneVertebrale	=	colonne.PointADistance( CG, DISTANCE_EPAULES ) ;
	Point CentreEpaules				=	ColonneVertebrale.LePlusHaut() ;
	Point CentreHanches				=	ColonneVertebrale.LePlusBas() ;
	
	Droite LigneEpaules					=	colonne.Perpendiculaire( CentreEpaules ) ;
	CoupleDePoints	Epaules				=	LigneEpaules.PointADistance( CentreEpaules, LARGEUR_EPAULE ) ;
	_EpauleDroite						=	Epaules.LePlusADroite() ;
	_EpauleGauche						=	Epaules.LePlusAGauche() ;

	// Calcule les hanches
	Droite LigneHanches					=	colonne.Perpendiculaire( CentreHanches ) ;
	CoupleDePoints	Hanches				=	LigneHanches.PointADistance( CentreHanches, LARGEUR_HANCHE ) ;
	_HancheDroite						=	Hanches.LePlusADroite() ;
	_HancheGauche						=	Hanches.LePlusAGauche() ;

	// Calcule la tete
	CoupleDePoints	Tetes				=	colonne.PointADistance( CentreEpaules, DISTANCE_TETE ) ;
	_Tete								=	Tetes.LePlusHaut() ;
}

/*
void CEscaladeView::CalculeEquationDroite(Point P1, Point P2, double *a, double *b)
{
	// Trouver l'equation de la droite y = ax + b qui relie les deux points
	if ( P1.x == P2.x )
		P2.x ++ ;

	if ( P1.y == P2.y )
		P2.y ++ ;

	*a	=	(double)(P1.y-P2.y) / (double)(P1.x-P2.x) ;
	*b	=	(double)P1.y - (*a * P1.x) ;
}
*/

void CEscaladeView::DessineDroite(CDC *pDC, Droite &dr)
{
	for ( int x = 0; x < 1000; x += 2 )
	{
		double y	=	dr.CalculeY( x ) ;
		pDC->SetPixelV( x, (int)y, RGB( 255, 0, 0 )) ;
	}

}

int CEscaladeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: add construction code here

	_MainGauche.x	=	100 ;
	_MainGauche.y	=	100 ;

	_MainDroite.x	=	200 ;
	_MainDroite.y	=	100 ;


	_PiedGauche.x	=	90 ;
	_PiedGauche.y   =	300 ;
	
	_PiedDroit.x	=	250 ;
	_PiedDroit.y	=	250 ;

	CalculeArticulations() ;
	
	return 0;
}

void CEscaladeView::DessinePoint(CDC *pDC, CPoint pt, CString Chaine)
{
	pDC->PatBlt( pt.x-1, pt.y-1, 3, 3, BLACKNESS ) ;
	pDC->TextOut( pt.x+3, pt.y, Chaine ) ;
}
