#if !defined(AFX_PROGRESSDLG_H__362F0EEC_9F3F_40AD_BA56_7374385B118E__INCLUDED_)
#define AFX_PROGRESSDLG_H__362F0EEC_9F3F_40AD_BA56_7374385B118E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
// Construction
public:
	BOOL Aborted();
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS };
	CStatic	m_TempsMoyen;
	CAnimateCtrl	m_Animate;
	CStatic	m_FichierEnCours;
	CStatic	m_UnSur;
	CStatic	m_DuppliquesTrouves;
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL _Aborted ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDLG_H__362F0EEC_9F3F_40AD_BA56_7374385B118E__INCLUDED_)
