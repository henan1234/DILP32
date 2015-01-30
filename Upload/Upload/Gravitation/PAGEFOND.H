// PageFond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageFond dialog

class CPageFond : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageFond)

// Construction
public:
	CPageFond();
	~CPageFond();

// Dialog Data
	//{{AFX_DATA(CPageFond)
	enum { IDD = IDD_PAGE_FOND };
	CButton	m_CtlParcourir;
	CEdit	m_CtlFichier;
	CEdit	m_CtlEtoiles;
	int		m_Etoiles;
	CString	m_Fichier;
	int		m_Noir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageFond)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageFond)
	afx_msg void OnNoir();
	afx_msg void OnImage();
	afx_msg void OnParcourir();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateControle( void );
};
