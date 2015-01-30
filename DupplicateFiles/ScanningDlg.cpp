// ScanningDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DupplicateFiles.h"
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
	//{{AFX_DATA_INIT(CScanningDlg)
	//}}AFX_DATA_INIT
	m_Abort	=	FALSE ;
}


void CScanningDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanningDlg)
	DDX_Control(pDX, IDC_PROCESSED, m_Processed);
	DDX_Control(pDX, IDC_FOUND, m_Found);
	DDX_Control(pDX, IDC_FILE, m_File);
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
