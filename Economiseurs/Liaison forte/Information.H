// Information.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInformation dialog

class CInformation : public CPropertyPage
{
	DECLARE_DYNCREATE(CInformation)

// Construction
public:
	CInformation();
	~CInformation();

// Dialog Data
	//{{AFX_DATA(CInformation)
	enum { IDD = IDD_PROPPAGE_SMALL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInformation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
