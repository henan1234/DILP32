// tapisseriedlg.h : header file
//

#include "propback.h"
#include "propecon.h"
#include "propapro.h"

/////////////////////////////////////////////////////////////////////////////
// CTapisserieDlg

class CTapisserieDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CTapisserieDlg)

// Construction
public:
	CTapisserieDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
//	CTapisserieDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	void ChangeTray( UINT Message, HICON hIcone ) ;
	static	void	Icone( UINT ) ;

private :
	static const	UINT	_wTaskBarNotify ;
	CPropAPropos		_APropos ;
	CPropBackground	 	_Backgrounds ;
	CPropEconomiseurs	_Savers ;
	static	CTapisserieDlg*	_pDlg ;


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTapisserieDlg)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTapisserieDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTapisserieDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT	OnTaskBarNotify( WPARAM, LPARAM ) ;
	virtual	BOOL	OnCommand( WPARAM, LPARAM ) ;

};

/////////////////////////////////////////////////////////////////////////////
