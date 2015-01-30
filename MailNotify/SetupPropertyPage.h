#if !defined(AFX_SETUPPROPERTYPAGE_H__16AA2FC1_968B_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_SETUPPROPERTYPAGE_H__16AA2FC1_968B_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupPropertyPage.h : header file
//
#include "afxdlgs.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertyPage dialog

class CSetupPropertyPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPropertyPage)

// Construction
public:
	CSetupPropertyPage();
	~CSetupPropertyPage();

// Dialog Data
	//{{AFX_DATA(CSetupPropertyPage)
	enum { IDD = IDD_PROPPAGE_LARGE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPropertyPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupPropertyPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPPROPERTYPAGE_H__16AA2FC1_968B_11D3_A61A_00A04B04180E__INCLUDED_)
