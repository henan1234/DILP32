// MosaiqueView.h : interface of the CMosaiqueView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOSAIQUEVIEW_H__8987664E_40B7_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_MOSAIQUEVIEW_H__8987664E_40B7_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyDragList.h"

class CBitmapWnd ;

class CMosaiqueView : public CFormView
{
protected: // create from serialization only
	CMosaiqueView();
	DECLARE_DYNCREATE(CMosaiqueView)

public:
	//{{AFX_DATA(CMosaiqueView)
	enum { IDD = IDD_MOSAIQUE_FORM };
	CListBox	m_Liste;
	BOOL	m_Bordure;
	int		m_NbLignes;
	int		m_NbColonnes;
	BOOL	m_NomDeFichier;
	CString	m_Memo;
	//}}AFX_DATA

// Attributes
public:
	CMosaiqueDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMosaiqueView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDropFiles( HDROP ) ;
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	afx_msg void OnBeginDrag( NMHDR * pNotifyStruct, LRESULT * result ) ;

// Implementation
public:
	int _IndiceMemo;
	virtual ~CMosaiqueView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void CalculDebutFin(int NoPage, int * pDebut, int * pFin) ;
	int CalculNbPages() ;


	CBitmapWnd * _pBitmapWnd ;

// Generated message map functions
protected:
	//{{AFX_MSG(CMosaiqueView)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkListe();
	afx_msg void OnChangeNbcolonnes();
	afx_msg void OnChangeNblignes();
	afx_msg void OnPlushaut();
	afx_msg void OnPlusbas();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton3();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MosaiqueView.cpp
inline CMosaiqueDoc* CMosaiqueView::GetDocument()
   { return (CMosaiqueDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_MOSAIQUEVIEW_H__8987664E_40B7_11D1_AEF5_444553540000__INCLUDED_)
