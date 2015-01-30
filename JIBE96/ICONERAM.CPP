///////////////////////////////////////////////////////////////////////////////
// CIconeRAM
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "iconeRAM.h"

IMPLEMENT_SERIAL( CIconeRAM,CIconeJauge, 0 ) ;

CIconeRAM::CIconeRAM()
	{
	}

CIconeRAM::~CIconeRAM()
	{
	}


UINT	CIconeRAM::GetPourcentage( void )
	{
	MEMORYSTATUS	Status ;

	GlobalMemoryStatus(  &Status ) ;

	return	ChangeIntervalle( Status.dwAvailPhys, 0, Status.dwTotalPhys, 0, 100 ) ;
	}

UINT	CIconeRAM::GetIDBitmap( void ) const
	{
	return Colors64K() ? IDB_RAM : IDB_RAM16 ;
	}

COLORREF	CIconeRAM::GetCouleurBarre( BOOL	Alarme ) const
	{
	if ( Alarme )
		return RGB( 255, 255, 0 ) ;
	else
		return RGB( 250,255,250) ;
	}


	
UINT		CIconeRAM::GetMenuID( void ) const
	{
	return IDR_MENU_DISQUE ;
	}




CString CIconeRAM::GetTip( void )
{
	MEMORYSTATUS	Status ;
	GlobalMemoryStatus(  &Status ) ;
	
	DWORD	Ko			=	(DWORD)( Status.dwTotalPhys / 1024.0 ) ;
	DWORD	KoLibres	=	(DWORD)( Status.dwAvailPhys / 1024.0 ) ;

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
	Texte.Format( IDS_RAM_LIBRE, (LPCSTR)Libre, (LPCSTR)UniteLibre, (LPCSTR)Total, (LPCSTR)UniteTotal ) ;
	return Texte ;
}

CString CIconeRAM::GetText( UINT Pourcentage )
	{
	return "" ;
	}
	
/////////////////////////////////////////////////////////////////////////////
// CDlgRAM dialog


CDlgRAM::CDlgRAM(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRAM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRAM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRAM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRAM)
	DDX_Control(pDX, IDC_SLIDER1, m_Alarme);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRAM, CDialog)
	//{{AFX_MSG_MAP(CDlgRAM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRAM message handlers

BOOL CIconeRAM::ExecuteCommand( UINT Command )
{
	switch( Command )
	{
	case ID_PROPRIETES :
		return ExecuteCommand() ;

	default :
		return FALSE ;
	}
}

BOOL CIconeRAM::ExecuteCommand( void )
{
	CDlgRAM	Dlg ;
	Dlg.m_PctAlarme	=	GetPourcentageAlarme() ;

	if ( Dlg.DoModal() != IDOK )
		return FALSE ;

	SetPourcentageAlarme( Dlg.m_PctAlarme ) ;
	return TRUE ;
}


BOOL CDlgRAM::OnInitDialog() 
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

void CDlgRAM::OnOK() 
{
	m_PctAlarme	=	m_Alarme.GetPos() ;
	
	CDialog::OnOK();
}

