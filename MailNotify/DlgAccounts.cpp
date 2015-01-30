// DlgAccounts.cpp : implementation file
//

#include "stdafx.h"
//#include "afxtempl.h"

#include "DlgAccounts.h"
#include "DlgAddAccount.h"

#include "CompteMail.h"

extern	CArray<CCompteMail *,CCompteMail *>	Comptes ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAccounts dialog


CDlgAccounts::CDlgAccounts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAccounts::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAccounts)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAccounts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccounts)
	DDX_Control(pDX, IDC_LIST_ACCOUNTS, m_ListeComptes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAccounts, CDialog)
	//{{AFX_MSG_MAP(CDlgAccounts)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAccounts message handlers

void CDlgAccounts::OnAdd() 
{
	CDlgAddAccount	Dlg ;

	if ( Dlg.DoModal() == IDOK )
		{
		CString Nom	=	Dlg.m_Nom ;
		CString Server=	Dlg.m_Server ;
		int		Port=	Dlg.m_Port ;
		CString Username= Dlg.m_UserName ;
		CString Password= Dlg.m_Password ;

		CCompteMail*	pCompte	=	new CCompteMail( Nom, Server, Port, Username, Password ) ;

		Comptes.Add( pCompte ) ;
		RemplitListeComptes() ;
		}
}

BOOL CDlgAccounts::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	RemplitListeComptes() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void	CDlgAccounts::RemplitListeComptes()
	{
	m_ListeComptes.DeleteColumn( 3 ) ;
	m_ListeComptes.DeleteColumn( 2 ) ;
	m_ListeComptes.DeleteColumn( 1 ) ;
	m_ListeComptes.DeleteColumn( 0 ) ;
	
	m_ListeComptes.InsertColumn( 0, "Name", LVCFMT_LEFT, 100 ) ;
	m_ListeComptes.InsertColumn( 1, "Server", LVCFMT_LEFT, 70 ) ;
	m_ListeComptes.InsertColumn( 2, "Port", LVCFMT_RIGHT, 50 ) ;
	m_ListeComptes.InsertColumn( 3, "Username", LVCFMT_LEFT, 70 ) ;

	for ( int i = 0; i < Comptes.GetSize(); i++)
		{
		CString	Port ;
		Port.Format( "%d", Comptes[i]->Port()) ;
		m_ListeComptes.InsertItem( i, Comptes[i]->Nom() ) ;
		m_ListeComptes.SetItem( i, 1, LVIF_TEXT, Comptes[i]->Serveur(), 0, 0, 0, 0 ) ;
		m_ListeComptes.SetItem( i, 2, LVIF_TEXT, Port, 0, 0, 0, 0 ) ;
		m_ListeComptes.SetItem( i, 3, LVIF_TEXT, Comptes[i]->UserName(), 0, 0, 0, 0 ) ;
		}
	}

void CDlgAccounts::OnEdit() 
{
	const int	Selected	=	m_ListeComptes.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selected == -1 )
		return ;

	CCompteMail* pCompte	=	Comptes[Selected] ;
	if ( ! pCompte  )
		return ;

	CDlgAddAccount	Dlg ;

	Dlg.m_Nom	=	pCompte->Nom() ;
	Dlg.m_Server=	pCompte->Serveur() ;
	Dlg.m_UserName=	pCompte->UserName() ;
	Dlg.m_Password = pCompte->Password() ;

	if ( Dlg.DoModal() == IDOK )
		{
		pCompte->Nom( Dlg.m_Nom ) ;
		pCompte->Serveur( Dlg.m_Server ) ;
		pCompte->Port( Dlg.m_Port ) ;
		pCompte->UserName( Dlg.m_UserName ) ;
		pCompte->Password( Dlg.m_Password ) ;

		CString	Port ;
		Port.Format( "%d", pCompte->Port()) ;

		m_ListeComptes.SetItem( Selected, 0, LVIF_TEXT, pCompte->Nom(), 0, 0, 0, 0 ) ;
		m_ListeComptes.SetItem( Selected, 1, LVIF_TEXT, pCompte->Serveur(), 0, 0, 0, 0 ) ;
		m_ListeComptes.SetItem( Selected, 2, LVIF_TEXT, Port, 0, 0, 0, 0 ) ;
		m_ListeComptes.SetItem( Selected, 3, LVIF_TEXT, pCompte->UserName(), 0, 0, 0, 0 ) ;
		}
}
