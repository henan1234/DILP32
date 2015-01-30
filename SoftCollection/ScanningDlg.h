#if !defined(AFX_SCANNINGDLG_H__0FBDC2C2_4BF9_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_SCANNINGDLG_H__0FBDC2C2_4BF9_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ScanningDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanningDlg dialog

class CScanningDlg : public CDialog
{
// Construction
public:
	BOOL Abort();
	CScanningDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScanningDlg)
	enum { IDD = IDD_SCANNING };
	CStatic	m_Processed;
	CStatic	m_File;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanningDlg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_Abort;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNINGDLG_H__0FBDC2C2_4BF9_11D2_B79A_0000E8D9BF74__INCLUDED_)
