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
	int		m_Depart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageGenese)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageGenese)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
