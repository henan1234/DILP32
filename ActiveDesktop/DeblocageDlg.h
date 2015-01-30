#if !defined(AFX_DEBLOCAGEDLG_H__EBECB3E1_2F81_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_DEBLOCAGEDLG_H__EBECB3E1_2F81_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DeblocageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeblocageDlg dialog

class CDeblocageDlg : public CDialog
{
// Construction
public:
	CDeblocageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeblocageDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_Deblocage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeblocageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDeblocageDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEBLOCAGEDLG_H__EBECB3E1_2F81_11D1_AEF5_444553540000__INCLUDED_)
