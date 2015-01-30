///////////////////////////////////////////////////////////////////////////////
// CIconeSwap
///////////////////////////////////////////////////////////////////////////////
#ifndef _ICONESWAP_H_
#define _ICONESWAP_H_

#include "iconeJauge.h"

class	CIconeSwap : public CIconeJauge
	{
	DECLARE_SERIAL( CIconeSwap ) ;

public:
	virtual BOOL ExecuteCommand( void );
	virtual BOOL ExecuteCommand( UINT Command );
	virtual CString GetTip( void );
	~CIconeSwap();
	CIconeSwap();

	virtual UINT		GetMenuID( void ) const ;

protected:
	virtual CString		GetText( UINT Pourcentage );
	virtual	UINT		GetPourcentage( void ) ;
	virtual	UINT		GetIDBitmap( void ) const  ;
	virtual	COLORREF	GetCouleurBarre( BOOL	Alarme = FALSE ) const ;	
	} ;

#endif
/////////////////////////////////////////////////////////////////////////////
// CDlgSwap dialog

class CDlgSwap : public CDialog
{
// Construction
public:
	UINT m_PctAlarme;
	CDlgSwap(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSwap)
	enum { IDD = IDD_SWAP };
	CSliderCtrl	m_Alarme;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSwap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSwap)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
