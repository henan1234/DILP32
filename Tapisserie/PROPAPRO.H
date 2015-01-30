// propapro.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropAPropos dialog

class CPropAPropos : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropAPropos)

// Construction
public:
	CPropAPropos();
	~CPropAPropos();

// Dialog Data
	//{{AFX_DATA(CPropAPropos)
	enum { IDD = IDD_DIALOG3, IDD_ENR	=	IDD_DIALOG3_ENREG };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropAPropos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropAPropos)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
