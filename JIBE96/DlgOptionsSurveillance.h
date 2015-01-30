// DlgOptionsSurveillance.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsSurveillance dialog

class CDlgOptionsSurveillance : public CDialog
{
// Construction
public:
	CDlgOptionsSurveillance(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptionsSurveillance)
	enum { IDD = IDD_OPTIONS_SURVEILLE };
	BOOL	m_Attributs;
	BOOL	m_DateModif;
	BOOL	m_Fichiers;
	BOOL	m_Repertoires;
	BOOL	m_SousRep;
	BOOL	m_Taille;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptionsSurveillance)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptionsSurveillance)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
