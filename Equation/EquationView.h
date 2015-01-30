// EquationView.h : interface of the CEquationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUATIONVIEW_H__11F7A58B_126E_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_EQUATIONVIEW_H__11F7A58B_126E_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEquationView : public CView
{
protected: // create from serialization only
	CEquationView();
	DECLARE_DYNCREATE(CEquationView)

// Attributes
public:
	CEquationDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquationView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEquationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEquationView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static void MarquePointSurDroite( CDC * pDC, double a, double b, double x );
	static void TrouvePerpendiculaire( double a, double b, double x, double * pa, double * pb );
	void TraceDroite( CDC * pDC, double a, double b, COLORREF Couleur );
};

#ifndef _DEBUG  // debug version in EquationView.cpp
inline CEquationDoc* CEquationView::GetDocument()
   { return (CEquationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_EQUATIONVIEW_H__11F7A58B_126E_11D1_AEF5_444553540000__INCLUDED_)
