// MailNotifDlg.h : header file
//

#if !defined(AFX_MAILNOTIFDLG_H__E86251E6_504B_4948_819F_0FDEA366DC2E__INCLUDED_)
#define AFX_MAILNOTIFDLG_H__E86251E6_504B_4948_819F_0FDEA366DC2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMailNotifDlg dialog

class CMailNotifDlg : public CDialog
{
// Construction
public:
	CMailNotifDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMailNotifDlg)
	enum { IDD = IDD_MAILNOTIF_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailNotifDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMailNotifDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPlus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL _Ferme;
	void FermeFenetre();
	void OuvreFenetre();
	CRect _RFerme;
	CRect _ROuvert;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILNOTIFDLG_H__E86251E6_504B_4948_819F_0FDEA366DC2E__INCLUDED_)
