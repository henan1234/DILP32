#if !defined(AFX_DLGPROCESS_H__FA0FA301_1903_11D3_A59E_00A04B04180E__INCLUDED_)
#define AFX_DLGPROCESS_H__FA0FA301_1903_11D3_A59E_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProcess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProcess dialog

class CDlgProcess : public CDialog
{
// Construction
public:
	CDlgProcess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProcess)
	enum { IDD = IDD_PROGRESS };
	CProgressCtrl	m_Progress;
	CEdit	m_Message;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProcess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProcess)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROCESS_H__FA0FA301_1903_11D3_A59E_00A04B04180E__INCLUDED_)
