// PageMasses.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageMasses dialog

class CPageMasses : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageMasses)

// Construction
public:
	CPageMasses();
	~CPageMasses();

// Dialog Data
	//{{AFX_DATA(CPageMasses)
	enum { IDD = IDD_PAGE_MASSES };
	double	m_Masse0;
	double	m_Masse1;
	double	m_Masse2;
	double	m_Masse3;
	double	m_Masse4;
	double	m_Masse5;
	double	m_Masse6;
	double	m_Masse7;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMasses)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMasses)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
