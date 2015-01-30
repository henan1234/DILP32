// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__F4A5578B_2BB2_4E5B_BEEB_BF477F119760__INCLUDED_)
#define AFX_LEFTVIEW_H__F4A5578B_2BB2_4E5B_BEEB_BF477F119760__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFichiersDoublesDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFichiersDoublesDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnNonDupliques();
	afx_msg void OnUpdateNonDupliques(CCmdUI* pCmdUI);
	afx_msg void OnProprietes();
	afx_msg void OnUpdateProprietes(CCmdUI* pCmdUI);
	afx_msg void OnEditionOuvre();
	afx_msg void OnUpdateEditionOuvre(CCmdUI* pCmdUI);
	afx_msg void OnEditionSupprimeduppliqus();
	afx_msg void OnUpdateEditionSupprimeduppliqus(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	BOOL _AfficherNonDuppliques;
	void AfficheElementTree(CTreeCtrl &Tree, CDC &dc, HTREEITEM hItem) ;

};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFichiersDoublesDoc* CLeftView::GetDocument()
   { return (CFichiersDoublesDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__F4A5578B_2BB2_4E5B_BEEB_BF477F119760__INCLUDED_)
