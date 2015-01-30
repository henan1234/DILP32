// AlunissageView.cpp : implementation of the CAlunissageView class
//

#include "stdafx.h"
#include "Alunissage.h"

#include "AlunissageDoc.h"
#include "AlunissageView.h"
#include "..\Economiseurs\Economiseur Generique\RectAffichage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NB_MAX_POINTS_PAR_COULEUR	1000
#define NB_MAX_COULEURS				16

POINT	PolyPoints[ NB_MAX_COULEURS][NB_MAX_POINTS_PAR_COULEUR] ;
int		NbPolyPoints[NB_MAX_COULEURS] ;

DWORD	NbPoints[NB_MAX_COULEURS][NB_MAX_POINTS_PAR_COULEUR/2] ;
int		NbNbPoints[ NB_MAX_COULEURS ] ;

COLORREF	Couleurs[ NB_MAX_COULEURS ] ;
int		NbCouleurs	=	0 ;
COLORREF Couleur ;
BOOL Bouton ;

POINT	PointDepart ;

/////////////////////////////////////////////////////////////////////////////
// CAlunissageView

IMPLEMENT_DYNCREATE(CAlunissageView, CView)

BEGIN_MESSAGE_MAP(CAlunissageView, CView)
	//{{AFX_MSG_MAP(CAlunissageView)
	ON_COMMAND(ID_COULEUR_BLEU, OnCouleurBleu)
	ON_COMMAND(ID_COULEUR_CYAN, OnCouleurCyan)
	ON_COMMAND(ID_COULEUR_JAUNE, OnCouleurJaune)
	ON_COMMAND(ID_COULEUR_MAGENTA, OnCouleurMagenta)
	ON_COMMAND(ID_COULEUR_NOIR, OnCouleurNoir)
	ON_COMMAND(ID_COULEUR_ROUGE, OnCouleurRouge)
	ON_COMMAND(ID_COULEUR_VERT, OnCouleurVert)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlunissageView construction/destruction

CAlunissageView::CAlunissageView()
{
	NbCouleurs	=	0 ;
}

CAlunissageView::~CAlunissageView()
{
}

BOOL CAlunissageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAlunissageView drawing

void CAlunissageView::OnDraw(CDC* pDC)
{
	CAlunissageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	PrepareDC( *pDC ) ;

	RendScene( *pDC, NULL ) ;
}

/////////////////////////////////////////////////////////////////////////////
// CAlunissageView diagnostics

#ifdef _DEBUG
void CAlunissageView::AssertValid() const
{
	CView::AssertValid();
}

void CAlunissageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAlunissageDoc* CAlunissageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAlunissageDoc)));
	return (CAlunissageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlunissageView message handlers

void CAlunissageView::RendScene(CDC & Dc, CRectAffichage * pRects )
{
	// Dessin de tous les segments dans le DC Intermediaire
	for ( int i = 0; i < NbCouleurs; i++)
		if ( NbNbPoints[i] )
			{
			CPen	Pinceau( PS_SOLID, 0, Couleurs[i] ) ;
			CPen *pOld = Dc.SelectObject( & Pinceau ) ;
			Dc.PolyPolyline( PolyPoints[i], NbPoints[i], NbNbPoints[i] ) ;
			Dc.SelectObject( pOld ) ;
			Pinceau.DeleteObject() ;
			}

	if ( pRects )
		{
		}
}

void CAlunissageView::AjouteSegment(COLORREF Couleur, POINT Point1, POINT Point2)
{
	// Chercher un indice de couleur pour ce point
	const int Indice	=	ChercheCouleurLibre( Couleur ) ;

	if ( Indice != -1 )
		{
		// Ajoute le segment dans la liste de la couleur
		PolyPoints[ Indice ][NbPolyPoints[Indice]]	=	Point1 ;
		PolyPoints[ Indice ][NbPolyPoints[Indice]+1]=	Point2 ;

		// Compte des segments dans ce "polypoint"
		NbPolyPoints[Indice] += 2 ;

		// Ajoute un compteur de segment
		NbPoints[Indice][NbNbPoints[Indice]++] = 2 ;
		}
}

int CAlunissageView::ChercheCouleurLibre(COLORREF Couleur)
{
	// Cherche dans la liste des couleurs existantes
	//
	for ( int i = 0; i < NbCouleurs; i++ )
		{
		if ( Couleurs[i] == Couleur )
			{
			// La couleur correspond, reste-t-il de la place ?
			if ( NbPolyPoints[i] >= NB_MAX_POINTS_PAR_COULEUR )
				continue ;

			if ( NbNbPoints[i] >= NB_MAX_POINTS_PAR_COULEUR/2 )
				continue ;

			return i ;
			}
		}

	// Essaie d'ajouter une couleur
	if ( NbCouleurs < NB_MAX_COULEURS )
		{
		NbNbPoints[NbCouleurs] = 0 ;
		NbPolyPoints[NbCouleurs] = 0 ;
		
		Couleurs[ NbCouleurs ] = Couleur ;
		NbCouleurs ++ ;
		}

	// Plus de place
	return -1 ;
}

void CAlunissageView::OnCouleurBleu() 
{
	Couleur	=	RGB( 0, 0, 255 ) ;	
}

void CAlunissageView::OnCouleurCyan() 
{
	Couleur	=	RGB( 0, 255, 255 ) ;	
}

void CAlunissageView::OnCouleurJaune() 
{
	Couleur	=	RGB( 255, 255, 0) ;	
	
}

void CAlunissageView::OnCouleurMagenta() 
{
		Couleur	=	RGB( 255, 0, 255 ) ;	
	
}

void CAlunissageView::OnCouleurNoir() 
{
	Couleur = 0 ;
	
}

void CAlunissageView::OnCouleurRouge() 
{
	Couleur = RGB( 255, 0, 0 ) ;
	
}

void CAlunissageView::OnCouleurVert() 
{
	Couleur = RGB( 0, 255, 0 ) ;
}

void CAlunissageView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC Dc( this ) ;
	PrepareDC( Dc ) ;
	
	Dc.DPtoLP( &point ) ;

	PointDepart	=	point ;

	Bouton = TRUE ;
	SetCapture() ;
	CView::OnLButtonDown(nFlags, point);
}

void CAlunissageView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC Dc( this ) ;
	PrepareDC( Dc ) ;
	
	Dc.DPtoLP( &point ) ;

	AjouteSegment( Couleur, PointDepart, point ) ;
	ReleaseCapture() ;
	Invalidate() ;

	Bouton = FALSE ;
	CView::OnLButtonUp(nFlags, point);
}

void CAlunissageView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( Bouton )
		{
		CClientDC Dc( this ) ;
		PrepareDC( Dc ) ;
		
		Dc.DPtoLP( &point ) ;

		AjouteSegment( Couleur, PointDepart, point ) ;
		PointDepart	=	point  ;
		}

	CView::OnMouseMove(nFlags, point);
}

void CAlunissageView::PrepareDC(CDC & Dc)
{
	CRect R ;
	GetClientRect( R ) ;

	Dc.SetMapMode( MM_ISOTROPIC ) ;

	Dc.SetViewportExt( R.Size() ) ;
	Dc.SetWindowExt( 1000, 1000 ) ;
}

BOOL CAlunissageView::OnEraseBkgnd(CDC* pDC) 
{
	CRect R ;
	GetClientRect( R ) ;

	pDC->PatBlt( 0, 0, R.Width(), R.Height(), BLACKNESS ) ;
	
	return TRUE ;
}
