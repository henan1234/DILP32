// Configuration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfiguration dialog

class CConfiguration : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfiguration)

// Construction
public:
	CConfiguration();
	~CConfiguration();

// Dialog Data
	//{{AFX_DATA(CConfiguration)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
	CSpinButtonCtrl	m_SpinLiens;
	CSliderCtrl	m_ImagesSecondes;
	CSpinButtonCtrl	m_SpinAtomes;
	double	m_Agitation;
	double	m_Amortissement;
	int		m_Atomes;
	int		m_Distance;
	double	m_Intensite;
	double	m_Creation;
	double	m_Max;
	int		m_NbMaxLiens;
	double	m_Repulsion;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfiguration)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfiguration)
	virtual BOOL OnInitDialog();
	afx_msg void OnCouleur();
	afx_msg void OnCouleurLiens();
	afx_msg void OnCouleurLibre();
	afx_msg void OnCouleurSature();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
