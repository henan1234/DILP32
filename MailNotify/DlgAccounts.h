#if !defined(AFX_DLGACCOUNTS_H__8A90C0C1_9696_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_DLGACCOUNTS_H__8A90C0C1_9696_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAccounts.h : header file
//
#include <afxtempl.h>
#include "resource.h"
#include "restriction.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgAccounts dialog

class CDlgAccounts : public CDialog
{
// Construction
public:
	CDlgAccounts(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAccounts)
	enum { IDD = IDD_ACCOUNTS };
	CListCtrl	m_ListeComptes;
	//}}AFX_DATA

	CArray<CRestriction*, CRestriction*> _Restrictions ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAccounts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAccounts)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void	RemplitListeComptes() ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGACCOUNTS_H__8A90C0C1_9696_11D3_A61A_00A04B04180E__INCLUDED_)
