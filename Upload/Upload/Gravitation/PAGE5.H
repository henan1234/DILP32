// Page5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage5

class CPage5 : public CPropertySheet
{
	DECLARE_DYNAMIC(CPage5)

// Construction
public:
	CPage5(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPage5(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPage5)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPage5();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPage5)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
