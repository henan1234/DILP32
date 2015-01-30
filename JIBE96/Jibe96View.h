// Jibe96View.h : interface of the CJibe96View class
//
/////////////////////////////////////////////////////////////////////////////

class CJibe96CntrItem;
class CJibe96Doc ;
class	CSideButton ;

class CJibe96View : public CView
{
protected: // create from serialization only
	LRESULT OnSideButtonNotify( WPARAM wParam, LPARAM lParam );
	CJibe96View();
	DECLARE_DYNCREATE(CJibe96View)

// Attributes
public:
	static CSize GetSize( void );
	static void PreTranslateToolTipMsg( MSG * pMsg );
	static void UpdateIcon( CIcone *, BOOL = FALSE );
	void SetSide( UINT Side );
	CJibe96Doc* GetDocument();
	// m_pSelection holds the selection to the current CJibe96CntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CJibe96CntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
//	CJibe96CntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJibe96View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
//	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void	OnTTNeedText(NMHDR* pNMHDR, LRESULT* pResult) ;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJibe96View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJibe96View)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCancelEditCntr();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFgNouvelleicneNote();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSupprimer();
	afx_msg void OnPlusbas();
	afx_msg void OnUpdatePlusbas(CCmdUI* pCmdUI);
	afx_msg void OnPlushaut();
	afx_msg void OnUpdatePlushaut(CCmdUI* pCmdUI);
	afx_msg void OnHeure();
	afx_msg void OnDate();
	afx_msg void OnPlacedisque();
	afx_msg void OnFgNouvelleicnePlaceram();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFgNouvelleicnePlacemmoire();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnFgFichierdchange();
	afx_msg void OnSeparateur();
	afx_msg void OnFgPrfrences();
	afx_msg void OnGroupe();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSurveilleRep();
	afx_msg void OnCommande();
	afx_msg void OnBouton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HWND _hApplicationActive;
	CIcone* _pIconeFenetre;
	void Selectionne( CIcone * );
	CIcone* IconePlusProche( CPoint );
	CPoint _BrushOrg;
	void DessineFantome( CDC &, HRGN );
	HRGN _hOldRegion;
	CSize _Decalage;
	CPoint GetPosIcon( CIcone * );
	static BOOL CurseurTropLoing( const CPoint &, const CPoint & );
	CPoint _PointDepart;
	int _ChoixAppui;
	CIcone* _pSelectionnee;
	void CacheFenetreIcone( void );
	CRect GetIconeRect( CIcone * pIcone );
	CWnd* _pFenetreIcone;
	void SetWindowPosFromPoint( void );
	void SetTipsOnIcons( void );
	CPoint GetPosIcon( int Indice );
	static CJibe96View * _thisView;
	CToolTipCtrl _ToolTip;
	CPoint PosDepart( void );
	void ShiftPos( CPoint & Pt, CIcone * ) ;
	CIcone* GetIconeFromPoint( CPoint Pt ) ;
	void AjouteIcone( CIcone * );
};

#ifndef _DEBUG  // debug version in Jibe96View.cpp
inline CJibe96Doc* CJibe96View::GetDocument()
   { return (CJibe96Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
