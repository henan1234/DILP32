// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
// The ABE_UNKNOWN and ABE_FLOAT macros are defined here as follows:
#define ABE_UNKNOWN           ((UINT) -1)
#define ABE_FLOAT             ((UINT) -2)

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	afx_msg void OnInitMenu(CMenu* pMenu);
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	void FermeFenetre( void );
	void OuvreFenetre( void );
	static CSize GetSize( void );
	void SetPos( UINT Side );
	void InitToolbar( void );
	UINT GetSide( void );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT	OnAppBarCallBack( WPARAM, LPARAM ) ;

private:
	void MoveWindowTo( CPoint );
	void GereAutoHide();
	CRect GetRect();
	BOOL _AutoHide;
	void PASCAL AppBarPosChanged(PAPPBARDATA pabd) ;
	void PASCAL AppBarQuerySetPos(UINT uEdge, LPRECT lprc, PAPPBARDATA pabd) ;
	void OnWindowPosChanged( WINDOWPOS *	pwndpos );
	void SetSide( UINT Pos ) ;

	static UINT _AppBarCallBackMessage;

} ;

/////////////////////////////////////////////////////////////////////////////
