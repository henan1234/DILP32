// WorkingDlg.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
#include "Transparentdesktop.h"
#include "WorkingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NB_TIPS	11
/////////////////////////////////////////////////////////////////////////////
// CWorkingDlg dialog


CWorkingDlg::CWorkingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWorkingDlg::IDD, pParent)
{
	srand( GetTickCount()) ;
	_NoTip	=	rand() % NB_TIPS ;

	//{{AFX_DATA_INIT(CWorkingDlg)
	m_Tip = _T("");
	//}}AFX_DATA_INIT
}


void CWorkingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWorkingDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Text(pDX, IDC_TIP, m_Tip);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWorkingDlg, CDialog)
	//{{AFX_MSG_MAP(CWorkingDlg)
	ON_BN_CLICKED(IDC_OTHER_TIP, OnOtherTip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkingDlg message handlers


/////////////////////////////////////////////////////////////////////////////
// Clic sur le bouton "Autre conseil"
// On affiche un autre conseil
/////////////////////////////////////////////////////////////////////////////
void CWorkingDlg::OnOtherTip() 
{
	m_Tip.LoadString( IDS_TIP1 + _NoTip ++) ;
	if ( _NoTip >= NB_TIPS )
		_NoTip = 0 ;

	UpdateData( FALSE ) ;
}

BOOL CWorkingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnOtherTip() ;	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

