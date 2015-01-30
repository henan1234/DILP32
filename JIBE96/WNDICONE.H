// WndIcone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWndIcone window
#ifndef _WNDICONE_H_
#define _WNDICONE_H_

class	CIcone ;

class CWndIcone : public CDialog
{
// Construction
public:
	CWndIcone( CIcone * );
	CRect AjusteRectangle( const CRect&, int Largeur, int Hauteur, DWORD Style, DWORD StyleEx );
	void  AjusteRectangle( const CRect& ) ;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndIcone)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndIcone();

	// Generated message map functions
protected:
	virtual BOOL ConfirmeFermetureAuto( void );
	void FautRester( BOOL = TRUE );
	//{{AFX_MSG(CWndIcone)
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CIcone * _pIconeAssociee;
private:
	BOOL _FautRester;
};

#endif
