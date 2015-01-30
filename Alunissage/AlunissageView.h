// AlunissageView.h : interface of the CAlunissageView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALUNISSAGEVIEW_H__94D7A78B_0E62_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_ALUNISSAGEVIEW_H__94D7A78B_0E62_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRectAffichage ;

class CAlunissageView : public CView
{
protected: // create from serialization only
	CAlunissageView();
	DECLARE_DYNCREATE(CAlunissageView)

// Attributes
public:
	CAlunissageDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlunissageView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAlunissageView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAlunissageView)
	afx_msg void OnCouleurBleu();
	afx_msg void OnCouleurCyan();
	afx_msg void OnCouleurJaune();
	afx_msg void OnCouleurMagenta();
	afx_msg void OnCouleurNoir();
	afx_msg void OnCouleurRouge();
	afx_msg void OnCouleurVert();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrepareDC(  CDC & Dc );
	static int ChercheCouleurLibre( COLORREF Couleur );
	void AjouteSegment( COLORREF Couleur, POINT Point1, POINT Point2 );
	void RendScene( CDC & Dc, CRectAffichage * );
};

#ifndef _DEBUG  // debug version in AlunissageView.cpp
inline CAlunissageDoc* CAlunissageView::GetDocument()
   { return (CAlunissageDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_ALUNISSAGEVIEW_H__94D7A78B_0E62_11D1_AEF5_444553540000__INCLUDED_)
