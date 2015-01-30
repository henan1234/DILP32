#if !defined(AFX_SETUPPROPERTYSHEET_H__16AA2FC2_968B_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_SETUPPROPERTYSHEET_H__16AA2FC2_968B_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupPropertySheet.h : header file
//
#include "SetupPropertyPage.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertySheet

class CSetupPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSetupPropertySheet)

// Construction
public:
	CSetupPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSetupPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSetupPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSetupPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CSetupPropertyPage	m_Page1 ;	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPPROPERTYSHEET_H__16AA2FC2_968B_11D3_A61A_00A04B04180E__INCLUDED_)
