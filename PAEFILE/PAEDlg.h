// PAEDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPAEDlg dialog

class CPAEDlg : public CDialog
{
// Construction
public:
	CPAEDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPAEDlg)
	enum { IDD = IDD_PAE_DIALOG };
	CListBox	m_Liste;
	int		m_Duree;
	CString	m_Image;
	CString	m_PAE;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPAEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPAEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnParcourirImages();
	afx_msg void OnParcourirPae();
	virtual void OnOK();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDescendre();
	afx_msg void OnMonter();
	afx_msg void OnSupprimer();
	afx_msg void OnVider();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
