// InstalleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstalleDlg dialog

class CInstalleDlg : public CDialog
{
// Construction
public:
	CInstalleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInstalleDlg)
	enum { IDD = IDD_INSTALLE_DIALOG };
	CStatic	m_EnCours;
	CButton	m_Cancel;
	CButton	m_OK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstalleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInstalleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
