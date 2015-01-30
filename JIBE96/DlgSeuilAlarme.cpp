// DlgSeuilAlarme.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "IconeJauge.h"
#include "DlgSeuilAlarme.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSeuilAlarme dialog


CDlgSeuilAlarme::CDlgSeuilAlarme(CIcone * pIcone, CWnd* pParent /*=NULL*/)
:CWndIcone( pIcone )
{
	//{{AFX_DATA_INIT(CDlgSeuilAlarme)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSeuilAlarme::DoDataExchange(CDataExchange* pDX)
{
//	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSeuilAlarme)
	DDX_Control(pDX, IDC_PCT, m_Pct);
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSeuilAlarme, CWndIcone)
	//{{AFX_MSG_MAP(CDlgSeuilAlarme)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSeuilAlarme message handlers

BOOL CDlgSeuilAlarme::OnInitDialog() 
{
	CWndIcone::OnInitDialog();
	m_Slider.SetRange( 0, 100 ) ;
	m_Slider.SetLineSize( 1 ) ;
	m_Slider.SetPageSize( 10 ) ;
	m_Slider.SetTicFreq( 10 ) ;

//	ASSERT_VALID( _pIconeAssociee ) ;
	CIconeJauge*	pIcone	=	STATIC_DOWNCAST( CIconeJauge, _pIconeAssociee );

	m_Slider.SetPos( pIcone->GetPourcentageAlarme( )) ;	
	ChangePct() ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSeuilAlarme::OnDestroy() 
{
	ASSERT_VALID( _pIconeAssociee ) ;
	CIconeJauge*	pIcone	=	STATIC_DOWNCAST( CIconeJauge, _pIconeAssociee );

	pIcone->SetPourcentageAlarme( m_Slider.GetPos()) ;	
	CWndIcone::OnDestroy();
	
}

void CDlgSeuilAlarme::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	ChangePct() ;
	
	CWndIcone::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgSeuilAlarme::ChangePct( void )
{
	CString S ;
	S.Format( "%d%%", (int)m_Slider.GetPos()) ;
	m_Pct.SetWindowText( S ) ;
}
