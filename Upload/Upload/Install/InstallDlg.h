// InstallDlg.h : header file
//

#if !defined(AFX_INSTALLDLG_H__FA8AA785_1EC0_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_INSTALLDLG_H__FA8AA785_1EC0_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

class CInstallDlg : public CDialog
{
// Construction
public:
	CInstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInstallDlg)
	enum { IDD = IDD_INSTALL_DIALOG };
	CButton	m_Configuration;
	CButton	m_Choix;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInstall();
	afx_msg void OnReadme();
	afx_msg void OnConfiguration();
	afx_msg void OnChoix();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_INSTALLDLG_H__FA8AA785_1EC0_11D1_AEF5_444553540000__INCLUDED_)
