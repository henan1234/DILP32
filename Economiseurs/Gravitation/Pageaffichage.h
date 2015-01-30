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
	CSliderCtrl	m_SliderZoom;
	CSliderCtrl	m_SliderTraveling;
	CSliderCtrl	m_SliderImages;
	CSliderCtrl	m_SliderEtoiles;
	BOOL	m_Repere;
	BOOL	m_Resolution;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAffichage)
	public:
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	afx_msg long	OnUserParameters( UINT, LONG ) ;


// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAffichage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void GetControls();
	void SetControls( void );
};
