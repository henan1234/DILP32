// DlgIcone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIcone dialog

class CDlgIcone : public CDialog
{
// Construction
public:
	int _IndiceIcone;
	CDlgIcone(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIcone)
	enum { IDD = IDD_CHANGE_ICONE };
	CListBox	m_Liste;
	CString	m_NomFichier;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIcone)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIcone)
	afx_msg void OnParcourir();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RemplitIcones( void );
};
