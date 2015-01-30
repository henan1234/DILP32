// SoftCatView.h : interface of the CSoftCatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFTCATVIEW_H__EDF20DA4_CEDC_4A5B_8510_6B0D99141342__INCLUDED_)
#define AFX_SOFTCATVIEW_H__EDF20DA4_CEDC_4A5B_8510_6B0D99141342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSoftCatSet;

class CSoftCatView : public CRecordView
{
protected: // create from serialization only
	CSoftCatView();
	DECLARE_DYNCREATE(CSoftCatView)

public:
	//{{AFX_DATA(CSoftCatView)
	enum { IDD = IDD_SOFTCAT_FORM };
	CSoftCatSet* m_pSet;
	CString	m_Nom;
	//}}AFX_DATA

// Attributes
public:
	CSoftCatDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCatView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoftCatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoftCatView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SoftCatView.cpp
inline CSoftCatDoc* CSoftCatView::GetDocument()
   { return (CSoftCatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTCATVIEW_H__EDF20DA4_CEDC_4A5B_8510_6B0D99141342__INCLUDED_)
