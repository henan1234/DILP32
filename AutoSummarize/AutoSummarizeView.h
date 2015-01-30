// AutoSummarizeView.h : interface of the CAutoSummarizeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOSUMMARIZEVIEW_H__927C4AF7_3BF8_4837_9312_DDDB8095B9B6__INCLUDED_)
#define AFX_AUTOSUMMARIZEVIEW_H__927C4AF7_3BF8_4837_9312_DDDB8095B9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoSummarizeView : public CView
{
protected: // create from serialization only
	CAutoSummarizeView();
	DECLARE_DYNCREATE(CAutoSummarizeView)

// Attributes
public:
	CAutoSummarizeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoSummarizeView)
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
	virtual ~CAutoSummarizeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoSummarizeView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoSummarizeView.cpp
inline CAutoSummarizeDoc* CAutoSummarizeView::GetDocument()
   { return (CAutoSummarizeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSUMMARIZEVIEW_H__927C4AF7_3BF8_4837_9312_DDDB8095B9B6__INCLUDED_)
