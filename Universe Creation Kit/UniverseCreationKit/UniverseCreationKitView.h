// UniverseCreationKitView.h : interface of the CUniverseCreationKitView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIVERSECREATIONKITVIEW_H__634F8E50_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_UNIVERSECREATIONKITVIEW_H__634F8E50_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CUniverseCreationKitView : public CFormView
{
protected: // create from serialization only
	CUniverseCreationKitView();
	DECLARE_DYNCREATE(CUniverseCreationKitView)

public:
	//{{AFX_DATA(CUniverseCreationKitView)
	enum { IDD = IDD_UNIVERSECREATIONKIT_FORM };
	CButton	m_Display;
	CTreeCtrl	m_Tree;
	//}}AFX_DATA

// Attributes
public:
	CUniverseCreationKitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniverseCreationKitView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	void RemplitListe();
	HTREEITEM	_hUniverseParameters ;
	HTREEITEM	_hPlanets ;
};

#ifndef _DEBUG  // debug version in UniverseCreationKitView.cpp
inline CUniverseCreationKitDoc* CUniverseCreationKitView::GetDocument()
   { return (CUniverseCreationKitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIVERSECREATIONKITVIEW_H__634F8E50_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_)
