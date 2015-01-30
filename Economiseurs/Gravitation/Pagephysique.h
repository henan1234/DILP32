// PagePhysique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPagePhysique dialog

class CPagePhysique : public CPropertyPage
{
	DECLARE_DYNCREATE(CPagePhysique)

// Construction
public:
	CPagePhysique();
	~CPagePhysique();

// Dialog Data
	//{{AFX_DATA(CPagePhysique)
	enum { IDD = IDD_PAGE_PHYSIQUE };
	CSpinButtonCtrl	m_SpinLiberation;
	double	m_Collision;
	double	m_CoeffDistance;
	double	m_G;
	double	m_Liberation;
	double	m_CoeffTemps;
	double	m_Rayon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPagePhysique)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPagePhysique)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg long	OnUserParameters( UINT, LONG ) ;

};
