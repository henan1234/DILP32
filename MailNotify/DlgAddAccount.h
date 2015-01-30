#if !defined(AFX_DLGADDACCOUNT_H__8A90C0C7_9696_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_DLGADDACCOUNT_H__8A90C0C7_9696_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddAccount.h : header file
//
//#include <afxtempl.h>
#include "resource.h"
//#include "restriction.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgAddAccount dialog

class CDlgAddAccount : public CDialog
{
// Construction
public:
	CDlgAddAccount(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddAccount)
	enum { IDD = IDD_ADD_ACCOUNT };
	CString	m_Password;
	int		m_Port;
	CString	m_Server;
	CString	m_UserName;
	CString	m_Nom;
	//}}AFX_DATA

//	CArray<CRestriction*, CRestriction*> _Restrictions ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddAccount)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddAccount)
	afx_msg void OnRules();
	afx_msg void OnAddRestriction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDACCOUNT_H__8A90C0C7_9696_11D3_A61A_00A04B04180E__INCLUDED_)
