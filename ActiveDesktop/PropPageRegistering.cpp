// PropPageRegistering.cpp : implementation file
//

#include "stdafx.h"
#include "activedesktop.h"
#include "PropPageRegistering.h"
#include "registrationKey.h"
#include "DeblocageDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPageRegistering dialog

	
CPropPageRegistering::CPropPageRegistering(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CPropPageRegistering::IDD ) //, pParent)
{
	//{{AFX_DATA_INIT(CPropPageRegistering)
	m_KeyCode = _T("");
	//}}AFX_DATA_INIT
}


void CPropPageRegistering::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPageRegistering)
	DDX_Text(pDX, IDC_KEY_CODE, m_KeyCode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPageRegistering, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPageRegistering)
	ON_BN_CLICKED(IDC_ENTERCODE, OnEntercode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPageRegistering message handlers

BOOL CPropPageRegistering::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

	m_KeyCode	=	pApp->_pRegistration->GetDisplayableLockKey() ;

	UpdateData( FALSE ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropPageRegistering::OnEntercode() 
{
	CDeblocageDlg	Dlg ;

	Dlg.DoModal() ;
}
