///////////////////////////////////////////////////////////////////////////////
// CIconeMem
///////////////////////////////////////////////////////////////////////////////
#ifndef _ICONEMEM_H_
#define _ICONEMEM_H_

#include "iconeJauge.h"

class	CIconeMem : public CIconeJauge
	{
	DECLARE_SERIAL( CIconeMem ) ;

public:
	virtual BOOL ExecuteCommand( void );
	virtual BOOL ExecuteCommand( UINT Command );
	virtual CString GetTip( void );
	~CIconeMem();
	CIconeMem();

	virtual UINT		GetMenuID( void ) const ;

protected:
	virtual CString GetText( UINT Pourcentage );
	virtual	UINT		GetPourcentage( void ) ;
	virtual	UINT		GetIDBitmap( void ) const  ;
	virtual	COLORREF	GetCouleurBarre( BOOL	Alarme = FALSE ) const ;	
	} ;

/////////////////////////////////////////////////////////////////////////////
// CDlgRAM dialog

class CDlgMem : public CDialog
{
// Construction
public:
	UINT m_PctAlarme;
	CDlgMem(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRAM)
	enum { IDD = IDD_MEM };
	CSliderCtrl	m_Alarme;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRAM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRAM)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
