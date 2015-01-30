// FilesCollectionView.h : interface of the CFilesCollectionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESCOLLECTIONVIEW_H__2197A08B_2081_42AC_8642_A61397704A16__INCLUDED_)
#define AFX_FILESCOLLECTIONVIEW_H__2197A08B_2081_42AC_8642_A61397704A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFilesCollectionView : public CListView
{
protected: // create from serialization only
	CFilesCollectionView();
	DECLARE_DYNCREATE(CFilesCollectionView)

// Attributes
public:
	CFilesCollectionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesCollectionView)
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
	virtual ~CFilesCollectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilesCollectionView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FilesCollectionView.cpp
inline CFilesCollectionDoc* CFilesCollectionView::GetDocument()
   { return (CFilesCollectionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESCOLLECTIONVIEW_H__2197A08B_2081_42AC_8642_A61397704A16__INCLUDED_)
