// SetupDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SetupDlg.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg dialog


CSetupDlg::CSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDlg)
	m_Delay = GetTimerDelay( DELAY_CHECK)/(1000*60) ;
	m_ScrollLock = FALSE;
	m_Animate = FALSE;
	m_MailClient = _T("");
	//}}AFX_DATA_INIT

	m_ScrollLock	= GetConfigurationInt( "Notification", "Flash Scroll Lock", TRUE ) ;
	m_Animate		= GetConfigurationInt( "Notification", "Animate Icon", TRUE ) ;

}


void CSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDlg)
	DDX_Text(pDX, IDC_DELAY, m_Delay);
	DDV_MinMaxUInt(pDX, m_Delay, 1, 100000);
	DDX_Check(pDX, IDC_SCROLLLOCK, m_ScrollLock);
	DDX_Check(pDX, IDC_ANIMATE, m_Animate);
	DDX_Text(pDX, IDC_CLIENT, m_MailClient);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDlg, CDialog)
	//{{AFX_MSG_MAP(CSetupDlg)
	ON_BN_CLICKED(IDC_BROWSEMAILCLIENT, OnBrowsemailclient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDlg message handlers

BOOL CSetupDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Delay	=	GetTimerDelay( DELAY_CHECK ) / (60*1000)  ;
	m_ScrollLock	=	GetConfigurationInt( "Notification", "Flash Scroll Lock", TRUE ) ;
	m_Animate		=	GetConfigurationInt( "Notification", "Animate Icon", TRUE ) ;
	m_MailClient	=	GetConfigurationString( "Mail", "Client", "" ) ;

	UpdateData( FALSE ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetupDlg::OnOK() 
{
	UpdateData( TRUE ) ;
	SetTimerDelay( DELAY_CHECK, m_Delay * 60 * 1000 ) ;
	WriteConfigurationInt( "Notification", "Flash Scroll Lock", m_ScrollLock ) ;
	WriteConfigurationInt( "Notification", "Animate Icon", m_Animate ) ;
	WriteConfigurationString( "Mail", "Client", m_MailClient ) ;
	CDialog::OnOK();
}

void CSetupDlg::OnBrowsemailclient() 
{
	UpdateData() ;
	CFileDialog Dlg( TRUE, ".exe", m_MailClient, 
					 OFN_ENABLESIZING | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
					 "Mail clients|*.exe|All files|*.*||",
					 this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		m_MailClient	=	Dlg.GetPathName() ;
		UpdateData( FALSE ) ;
		}

}
