// escaladeView.h : interface of the CEscaladeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ESCALADEVIEW_H__D65FDB9E_2CAF_48A8_90FF_0CEB2DECAADB__INCLUDED_)
#define AFX_ESCALADEVIEW_H__D65FDB9E_2CAF_48A8_90FF_0CEB2DECAADB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "droite.h"

class CEscaladeView : public CView
{
protected: // create from serialization only
	CEscaladeView();
	DECLARE_DYNCREATE(CEscaladeView)

// Attributes
public:
	CEscaladeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEscaladeView)
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
	virtual ~CEscaladeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	Point	_MainGauche, _MainDroite, _CoudeGauche, _CoudeDroit, _EpauleGauche, _EpauleDroite ;
	Point	_PiedGauche, _PiedDroit, _GenouGauche, _GenouDroit, _HancheGauche, _HancheDroite ;
	Point	_Tete ;
// Generated message map functions
protected:
	//{{AFX_MSG(CEscaladeView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DessinePoint( CDC * pDC, CPoint pt, CString Chaine );
	void DessineDroite( CDC * pDC, Droite & dr );
	void CalculeEquationDroite( Point P1, Point P2, double * a, double * b );
	void CalculeCorps();
	void DessineCorps( CDC * pDC, Point EpauleGauche, Point EpauleDroite, Point HancheGauche, Point HancheDroite );
	void DessineJambe( CDC* pDC, Point Pied, Point Genou, Point Hanche );
	void DessineBras( CDC * pDC, Point Main, Point Coude, Point Epaule );
	void CalculeArticulations();
	void CalculePositionIntermediaire( Point & P1, Point & P2, double Coeff, Point * Pt );
	void CalculeHancheDroite();
	void CalculeHancheGauche();
	void CalculeEpauleDroite();
	void CalculeEpauleGauche();
	Point * _Deplace;
	BOOL _ButtonDown;
	static BOOL CalculeIntersectionDeuxCercles( Point X1, Point X2, int R1, int R2, CoupleDePoints * Couple );
	void CalculeGenouGauche();
	void CalculeGenouDroit();
	void CalculeCoudeGauche();
	void CalculeCoudeDroit();
};

#ifndef _DEBUG  // debug version in escaladeView.cpp
inline CEscaladeDoc* CEscaladeView::GetDocument()
   { return (CEscaladeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESCALADEVIEW_H__D65FDB9E_2CAF_48A8_90FF_0CEB2DECAADB__INCLUDED_)
