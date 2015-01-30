// CollectionFichiersView.h : interface of the CCollectionFichiersView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLECTIONFICHIERSVIEW_H__A6815025_5053_4630_AF51_C3C32059ED2A__INCLUDED_)
#define AFX_COLLECTIONFICHIERSVIEW_H__A6815025_5053_4630_AF51_C3C32059ED2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MyTree.h"

class CCollectionFichiersView : public CFormView
{

private:
	CString GetNomAttributTri();
	void NotificationHeader( NMHEADER * pNotif );
	void SetHeaderCtrl();
	CImageList _ImageList;
	int			m_IndiceElementSelectionne;
	int			m_IndiceElement;
	int			m_IndiceRootSelectionne;
	int			m_IndiceRoot;
	CHeaderCtrl	_HeaderCtrl ;

protected: // create from serialization only
	CCollectionFichiersView();
	DECLARE_DYNCREATE(CCollectionFichiersView)

public:
	//{{AFX_DATA(CCollectionFichiersView)
	CMyTree	m_Liste;
	//}}AFX_DATA

// Attributes
public:
	CCollectionFichiersDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionFichiersView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollectionFichiersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollectionFichiersView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFichiersAjouter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CollectionFichiersView.cpp
inline CCollectionFichiersDoc* CCollectionFichiersView::GetDocument()
   { return (CCollectionFichiersDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTIONFICHIERSVIEW_H__A6815025_5053_4630_AF51_C3C32059ED2A__INCLUDED_)
