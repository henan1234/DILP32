// TapisserieSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTapisserieSheet

class CTapisserieSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CTapisserieSheet)

// Construction
public:
	CTapisserieSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CTapisserieSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	afx_msg LRESULT OnTaskBarNotify( WPARAM wParam, LPARAM lParam ) ;
	afx_msg	BOOL OnCommand( WPARAM wParam, LPARAM lParam ) ;
	static const	UINT	_wTaskBarNotify ;
	
private :
	static CTapisserieSheet*	_pDlg ;

/////////////////////////////////////////////////////////////////////////////
// CTapisserieSheet
void CTapisserieSheet::ChangeTray( UINT Message, HICON hIcone ) ;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapisserieSheet)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTapisserieSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTapisserieSheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
