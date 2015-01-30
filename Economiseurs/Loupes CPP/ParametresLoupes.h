#if !defined(AFX_PARAMETRESLOUPES_H__303B2581_4A40_11D1_AB40_0020AF71E433__INCLUDED_)
#define AFX_PARAMETRESLOUPES_H__303B2581_4A40_11D1_AB40_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ParametresLoupes.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CParametresLoupes dialog

class CParametresLoupes : public CPropertyPage
{
	DECLARE_DYNCREATE(CParametresLoupes)

// Construction
public:
	CParametresLoupes();
	~CParametresLoupes();

// Dialog Data
	//{{AFX_DATA(CParametresLoupes)
	enum { IDD = IDD_PARAMETRES };
	CSliderCtrl	m_Slider;
	BOOL	m_Noir;
	CString	m_Texte;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParametresLoupes)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CParametresLoupes)
	virtual BOOL OnInitDialog();
	afx_msg void OnCouleur();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMETRESLOUPES_H__303B2581_4A40_11D1_AB40_0020AF71E433__INCLUDED_)
