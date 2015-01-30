// ScanningDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "ScanningDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScanningDlg dialog


CScanningDlg::CScanningDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScanningDlg::IDD, pParent)
{
	m_Abort	= FALSE ;
	//{{AFX_DATA_INIT(CScanningDlg)
	//}}AFX_DATA_INIT
}


void CScanningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanningDlg)
	DDX_Control(pDX, IDC_ANIMATE1, m_Animate);
	DDX_Control(pDX, IDC_CHECKSUM, m_CheckSum);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_FICHIER, m_Fichier);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanningDlg, CDialog)
	//{{AFX_MSG_MAP(CScanningDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanningDlg message handlers

void CScanningDlg::OnCancel() 
{
	m_Abort	=	TRUE ;
}

BOOL CScanningDlg::Abort()
{
	MSG	msg ;

	while ( ::PeekMessage( &msg, NULL, NULL, NULL, PM_NOREMOVE ))
		AfxGetThread()->PumpMessage() ;

	return m_Abort ;
}

BOOL CScanningDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Animate.Open( IDD_SCANNING ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
