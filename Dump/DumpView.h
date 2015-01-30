// DumpView.h : interface of the CDumpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUMPVIEW_H__3B6AAF8D_1231_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_DUMPVIEW_H__3B6AAF8D_1231_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDumpView : public CScrollView
{
protected: // create from serialization only
	CDumpView();
	DECLARE_DYNCREATE(CDumpView)

// Attributes
public:
	CDumpDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDumpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDumpView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void PrepareDC( CDC & Dc );
	CSize TailleCaractere( void );
};

#ifndef _DEBUG  // debug version in DumpView.cpp
inline CDumpDoc* CDumpView::GetDocument()
   { return (CDumpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_DUMPVIEW_H__3B6AAF8D_1231_11D1_AEF5_444553540000__INCLUDED_)
