#if !defined(AFX_PROPPAGEREGISTERING_H__04039F03_2507_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_PROPPAGEREGISTERING_H__04039F03_2507_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPageRegistering.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPageRegistering dialog

class CPropPageRegistering : public CPropertyPage
{
// Construction
public:
	CPropPageRegistering(UINT Id, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropPageRegistering)
//	enum { IDD = IDD_PROPPAGE_REGISTERING };
	CString	m_KeyCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropPageRegistering)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropPageRegistering)
	virtual BOOL OnInitDialog();
	afx_msg void OnEntercode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg long	OnUserParameters( UINT, LONG ) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGEREGISTERING_H__04039F03_2507_11D1_AEF5_444553540000__INCLUDED_)
