// AnimationView.h : interface of the CAnimationView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATIONVIEW_H__2759DB6D_4F85_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_ANIMATIONVIEW_H__2759DB6D_4F85_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAnimationView : public CFormView
{
protected: // create from serialization only
	CAnimationView();
	DECLARE_DYNCREATE(CAnimationView)

public:
	//{{AFX_DATA(CAnimationView)
	enum { IDD = IDD_ANIMATION_FORM };
	CListCtrl	m_Liste;
	//}}AFX_DATA

// Attributes
public:
	CAnimationDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimationView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditionMonterlimage();
	afx_msg void OnEditionDescendrelimage();
	afx_msg void OnEditCopy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int _IndiceImageCourante;
	CStringArray	_NomsDeFichiers;
	CObArray		_Bitmaps ;
	CImageList		_ListeImages;
};

#ifndef _DEBUG  // debug version in AnimationView.cpp
inline CAnimationDoc* CAnimationView::GetDocument()
   { return (CAnimationDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_ANIMATIONVIEW_H__2759DB6D_4F85_11D1_AEF5_444553540000__INCLUDED_)
