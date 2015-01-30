// Universe Creation KitView.h : interface of the CUniverseCreationKitView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIVERSECREATIONKITVIEW_H__069CCDAF_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
#define AFX_UNIVERSECREATIONKITVIEW_H__069CCDAF_5F35_11D1_98A4_080009F8FCDD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUniverseCreationKitView : public CView
{
protected: // create from serialization only
	CUniverseCreationKitView();
	DECLARE_DYNCREATE(CUniverseCreationKitView)

// Attributes
public:
	CUniverseCreationKitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniverseCreationKitView)
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
	virtual ~CUniverseCreationKitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUniverseCreationKitView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Universe Creation KitView.cpp
inline CUniverseCreationKitDoc* CUniverseCreationKitView::GetDocument()
   { return (CUniverseCreationKitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIVERSECREATIONKITVIEW_H__069CCDAF_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
