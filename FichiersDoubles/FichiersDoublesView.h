// FichiersDoublesView.h : interface of the CFichiersDoublesView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHIERSDOUBLESVIEW_H__03BEE670_61D9_4764_AB64_42C92A76C25C__INCLUDED_)
#define AFX_FICHIERSDOUBLESVIEW_H__03BEE670_61D9_4764_AB64_42C92A76C25C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFichiersDoublesView : public CListView
{
protected: // create from serialization only
	CFichiersDoublesView();
	DECLARE_DYNCREATE(CFichiersDoublesView)

// Attributes
public:
	CFichiersDoublesDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFichiersDoublesView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFichiersDoublesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFichiersDoublesView)
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FichiersDoublesView.cpp
inline CFichiersDoublesDoc* CFichiersDoublesView::GetDocument()
   { return (CFichiersDoublesDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FICHIERSDOUBLESVIEW_H__03BEE670_61D9_4764_AB64_42C92A76C25C__INCLUDED_)
