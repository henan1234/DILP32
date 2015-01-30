#if !defined(AFX_DLGRESTRICTION_H__01497661_A719_11D3_A623_00A04B04180E__INCLUDED_)
#define AFX_DLGRESTRICTION_H__01497661_A719_11D3_A623_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRestriction.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRestriction dialog

class CDlgRestriction : public CDialog
{
// Construction
public:
	CDlgRestriction(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRestriction)
	enum { IDD = IDD_RESTRICTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRestriction)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRestriction)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RemplitRules();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRESTRICTION_H__01497661_A719_11D3_A623_00A04B04180E__INCLUDED_)
