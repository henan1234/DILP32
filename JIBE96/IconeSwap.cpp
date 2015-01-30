///////////////////////////////////////////////////////////////////////////////
// CIconeSwap
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "iconeSwap.h"

IMPLEMENT_SERIAL( CIconeSwap,CIconeJauge, 0 ) ;

CIconeSwap::CIconeSwap()
	{
	}

CIconeSwap::~CIconeSwap()
	{
	}


UINT	CIconeSwap::GetPourcentage( void )
	{
	MEMORYSTATUS	Status ;

	GlobalMemoryStatus(  &Status ) ;

	return	ChangeIntervalle( Status.dwAvailPageFile/1024, 0, Status.dwTotalPageFile/1024, 0, 100 ) ;
	}

UINT	CIconeSwap::GetIDBitmap( void ) const
	{
	return Colors64K() ? IDB_SWAP : IDB_SWAP16 ;
	}

COLORREF	CIconeSwap::GetCouleurBarre( BOOL	Alarme ) const
	{
	if ( Alarme )
		return RGB( 255, 255, 0 ) ;
	else
		return RGB( 250,255,250) ;
	}


	
UINT		CIconeSwap::GetMenuID( void ) const
	{
	return IDR_MENU_DISQUE ;
	}




CString CIconeSwap::GetTip( void )
{
	MEMORYSTATUS	Status ;
	GlobalMemoryStatus(  &Status ) ;
	
	DWORD	Ko			=	(DWORD)( Status.dwTotalPageFile / 1024.0 ) ;
	DWORD	KoLibres	=	(DWORD)( Status.dwAvailPageFile / 1024.0 ) ;

	CString Libre ;
	CString	Total ;
	CString	UniteLibre ;
	CString	UniteTotal ;

	if ( Ko > 1024L )
		{
		// en Mo
		Total = FormatNumber( Ko / 1000.0  ) ;
		UniteTotal.LoadString( IDS_UNITE_MO ) ;
		}
	else
		{
		Total  = FormatNumber( Ko )  ;
		UniteTotal.LoadString( IDS_UNITE_KO ) ;
		}

	if ( KoLibres > 1024L )
		{
		// en Mo
		Libre = FormatNumber( KoLibres / 1000.0  ) ;
		UniteLibre.LoadString( IDS_UNITE_MO ) ;
		}
	else
		{
		Libre = FormatNumber( KoLibres ) ;
		UniteLibre.LoadString( IDS_UNITE_KO ) ;
		}

	CString	Texte ;
	Texte.Format( IDS_SWAP_LIBRE, (LPCSTR)Libre, (LPCSTR)UniteLibre, (LPCSTR)Total, (LPCSTR)UniteTotal ) ;
	return Texte ;
}

CString CIconeSwap::GetText( UINT Pourcentage )
	{
	return "" ;
	}
	
/////////////////////////////////////////////////////////////////////////////
// CDlgSwap dialog


CDlgSwap::CDlgSwap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSwap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSwap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSwap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSwap)
	DDX_Control(pDX, IDC_SLIDER1, m_Alarme);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSwap, CDialog)
	//{{AFX_MSG_MAP(CDlgSwap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSwap message handlers

BOOL CIconeSwap::ExecuteCommand( UINT Command )
{
	switch( Command )
	{
	case ID_PROPRIETES :
		return ExecuteCommand() ;

	default :
		return FALSE ;
	}
}

BOOL CIconeSwap::ExecuteCommand( void )
{
	CDlgSwap	Dlg ;
	Dlg.m_PctAlarme	=	GetPourcentageAlarme() ;

	if ( Dlg.DoModal() != IDOK )
		return FALSE ;

	SetPourcentageAlarme( Dlg.m_PctAlarme ) ;
	return TRUE ;
}

BOOL CDlgSwap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Alarme.SetRange( 0, 100 ) ;
	m_Alarme.SetTicFreq( 10 );
	m_Alarme.SetPageSize( 10 ) ;
	m_Alarme.SetLineSize( 1 ) ;
	m_Alarme.SetPos( m_PctAlarme ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSwap::OnOK() 
{
	m_PctAlarme	=	m_Alarme.GetPos() ;
	
	CDialog::OnOK();
}
