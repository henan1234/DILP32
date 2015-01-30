// Dir2HTMLDlg.h : header file
//

#if !defined(AFX_DIR2HTMLDLG_H__33399865_F389_4B95_8D5F_ACF270B464E4__INCLUDED_)
#define AFX_DIR2HTMLDLG_H__33399865_F389_4B95_8D5F_ACF270B464E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDir2HTMLDlg dialog

class CDir2HTMLDlg : public CDialog
{
// Construction
public:
	CDir2HTMLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDir2HTMLDlg)
	enum { IDD = IDD_DIR2HTML_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDir2HTMLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDir2HTMLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChooseDir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIR2HTMLDLG_H__33399865_F389_4B95_8D5F_ACF270B464E4__INCLUDED_)
