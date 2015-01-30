// DlgAddAccount.cpp : implementation file
//

#include "stdafx.h"
#include "DlgAddAccount.h"
#include "DlgRestriction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddAccount dialog


CDlgAddAccount::CDlgAddAccount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddAccount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddAccount)
	m_Password = _T("");
	m_Port = 110;
	m_Server = _T("mailhost");
	m_UserName = _T("");
	m_Nom = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAddAccount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddAccount)
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Text(pDX, IDC_SERVER, m_Server);
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_NAME, m_Nom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddAccount, CDialog)
	//{{AFX_MSG_MAP(CDlgAddAccount)
	ON_BN_CLICKED(IDC_RULES, OnRules)
	ON_BN_CLICKED(IDC_ADD_RESTRICTION, OnAddRestriction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddAccount message handlers

void CDlgAddAccount::OnRules() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgAddAccount::OnAddRestriction() 
{
/*	CDlgRestriction	Dlg ;
	if ( Dlg.DoModal() == IDOK )
		{
		}*/
}
