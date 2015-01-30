#if !defined(AFX_SCANNINGDLG1_H__3BF5399E_6177_468A_ACE5_76B55DC8D624__INCLUDED_)
#define AFX_SCANNINGDLG1_H__3BF5399E_6177_468A_ACE5_76B55DC8D624__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanningDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanningDlg dialog

class CScanningDlg : public CDialog
{
// Construction
public:
	CScanningDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL Abort();

// Dialog Data
	//{{AFX_DATA(CScanningDlg)
	enum { IDD = IDD_SCANNING };
	CAnimateCtrl	m_Animate;
	CProgressCtrl	m_CheckSum;
	CProgressCtrl	m_Progress;
	CStatic	m_Fichier;
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
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL	m_Abort ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNINGDLG1_H__3BF5399E_6177_468A_ACE5_76B55DC8D624__INCLUDED_)
