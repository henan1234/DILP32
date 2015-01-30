// PageComete.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageComete dialog

class CPageComete : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageComete)

// Construction
public:
	CPageComete();
	~CPageComete();

// Dialog Data
	//{{AFX_DATA(CPageComete)
	enum { IDD = IDD_PAGE_COMETE };
	CSpinButtonCtrl	m_SpinMax;
	CSpinButtonCtrl	m_SpinDispersion;
	int		m_CreationComete;
	int		m_Dispersion;
	int		m_MaxPoussieres;
	int		m_TailleMax;
	int		m_ViePoussieres;
	double	m_VentSolaire;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageComete)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageComete)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
