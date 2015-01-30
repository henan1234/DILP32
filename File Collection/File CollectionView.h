// File CollectionView.h : interface of the CFileCollectionView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOLLECTIONVIEW_H__26DA739D_8966_48AD_8234_0C641633886D__INCLUDED_)
#define AFX_FILECOLLECTIONVIEW_H__26DA739D_8966_48AD_8234_0C641633886D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileCollectionView : public CFormView
{
protected: // create from serialization only
	CFileCollectionView();
	DECLARE_DYNCREATE(CFileCollectionView)

public:
	//{{AFX_DATA(CFileCollectionView)
	enum{ IDD = IDD_FILECOLLECTION_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CFileCollectionDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileCollectionView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileCollectionView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileCollectionView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in File CollectionView.cpp
inline CFileCollectionDoc* CFileCollectionView::GetDocument()
   { return (CFileCollectionDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECOLLECTIONVIEW_H__26DA739D_8966_48AD_8234_0C641633886D__INCLUDED_)
