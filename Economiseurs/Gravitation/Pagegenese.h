// PageGenese.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageGenese dialog

class CPageGenese : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageGenese)

// Construction
public:
	CPageGenese();
	~CPageGenese();

// Dialog Data
	//{{AFX_DATA(CPageGenese)
	enum { IDD = IDD_PAGE5 };
	CButton	m_CtrlParcourir;
	CEdit	m_CtrlFichier;
	int		m_Depart;
	int		m_2D;
	CString	m_Fichier;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageGenese)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageGenese)
	virtual BOOL OnInitDialog();
	afx_msg void OnParcourir();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg long	OnUserParameters( UINT, LONG ) ;

private:
	void AvertitPages();
};
