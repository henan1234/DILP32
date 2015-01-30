// CollectionView.h : interface of the CCollectionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLECTIONVIEW_H__94F7C75A_FE52_4924_B333_42F53A58C431__INCLUDED_)
#define AFX_COLLECTIONVIEW_H__94F7C75A_FE52_4924_B333_42F53A58C431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCollectionView : public CListView
{
protected: // create from serialization only
	CCollectionView();
	DECLARE_DYNCREATE(CCollectionView)

// Attributes
public:
	CCollectionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionView)
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
	virtual ~CCollectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollectionView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CollectionView.cpp
inline CCollectionDoc* CCollectionView::GetDocument()
   { return (CCollectionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTIONVIEW_H__94F7C75A_FE52_4924_B333_42F53A58C431__INCLUDED_)
