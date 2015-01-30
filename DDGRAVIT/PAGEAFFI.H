// PageAffichage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageAffichage dialog

class CPageAffichage : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAffichage)

// Construction
public:
	CPageAffichage();
	~CPageAffichage();

// Dialog Data
	//{{AFX_DATA(CPageAffichage)
	enum { IDD = IDD_PAGE_AFFICHAGE };
	CSpinButtonCtrl	m_SpinImages;
	CSpinButtonCtrl	m_SpinZoom;
	int		m_Densite;
	int		m_Images;
	double	m_Traveling;
	BOOL	m_Effacer;
	double	m_Zoom;
	BOOL	m_Repere;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAffichage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAffichage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
