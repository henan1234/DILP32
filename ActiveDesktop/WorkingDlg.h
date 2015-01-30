// WorkingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkingDlg dialog

class CWorkingDlg : public CDialog
{
// Construction
public:
	void SetMessage( UINT );
	CWorkingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkingDlg)
	enum { IDD = IDD_WORKING };
	CProgressCtrl	m_Progress;
	CString	m_Tip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkingDlg)
	afx_msg void OnOtherTip();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
