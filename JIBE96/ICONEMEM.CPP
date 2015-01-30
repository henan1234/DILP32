///////////////////////////////////////////////////////////////////////////////
// CIconeMem
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "iconeMem.h"

IMPLEMENT_SERIAL( CIconeMem,CIconeJauge, 0 ) ;

CIconeMem::CIconeMem()
	{
	}

CIconeMem::~CIconeMem()
	{
	}


UINT	CIconeMem::GetPourcentage( void )
	{
	MEMORYSTATUS	Status ;

	GlobalMemoryStatus(  &Status ) ;

	return	100-(UINT)Status.dwMemoryLoad ;
	}

UINT	CIconeMem::GetIDBitmap( void ) const
	{
	return Colors64K() ? IDB_MEM : IDB_MEM16 ;
	}

COLORREF	CIconeMem::GetCouleurBarre( BOOL	Alarme ) const
	{
	if ( Alarme )
		return RGB( 255, 255, 0 ) ;
	else
		return RGB( 250,255,250) ;
	}


	
UINT		CIconeMem::GetMenuID( void ) const
	{
	return IDR_MENU_DISQUE ;
	}




CString CIconeMem::GetTip( void )
{
	MEMORYSTATUS	Status ;
	GlobalMemoryStatus(  &Status ) ;
	
	const CString	Total ( FormatNumber( 100 - Status.dwMemoryLoad )) ;
	
	
	CString	Texte ;
	Texte.Format( IDS_FORMAT_VIRTUELLE_LIBRE, (LPCSTR)Total ) ;
	return Texte ;
}

CString CIconeMem::GetText( UINT Pourcentage )
	{
	return "" ;
	}
	
/////////////////////////////////////////////////////////////////////////////
// CDlgMem dialog


CDlgMem::CDlgMem(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMem)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMem)
	DDX_Control(pDX, IDC_SLIDER1, m_Alarme);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMem, CDialog)
	//{{AFX_MSG_MAP(CDlgMem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMem message handlers

BOOL CIconeMem::ExecuteCommand( UINT Command )
{
	switch( Command )
	{
	case ID_PROPRIETES :
		return ExecuteCommand() ;

	default :
		return FALSE ;
	}
}

BOOL CIconeMem::ExecuteCommand( void )
{
	CDlgMem	Dlg ;
	Dlg.m_PctAlarme	=	GetPourcentageAlarme() ;

	if ( Dlg.DoModal() != IDOK )
		return FALSE ;

	SetPourcentageAlarme( Dlg.m_PctAlarme ) ;
	return TRUE ;
}

BOOL CDlgMem::OnInitDialog() 
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

void CDlgMem::OnOK() 
{
	m_PctAlarme	=	m_Alarme.GetPos() ;
	
	CDialog::OnOK();
}
