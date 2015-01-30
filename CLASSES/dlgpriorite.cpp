// dlgpriorite.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <economiseur.h>
#include "dlgpriorite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPriorite property page

IMPLEMENT_DYNCREATE(CDlgPriorite, CPropertyPage)

CDlgPriorite::CDlgPriorite() : CPropertyPage(CDlgPriorite::IDD)
{
	//{{AFX_DATA_INIT(CDlgPriorite)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_PRIORITE ) ;
}

CDlgPriorite::~CDlgPriorite()
{
}

void CDlgPriorite::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPriorite)
	DDX_Control(pDX, IDC_PRIORITE, m_Priorite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPriorite, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgPriorite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPriorite message handlers

BOOL CDlgPriorite::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEconomiseur*	pEco	=	CEconomiseur::GetEconomiseur() ;
	m_Priorite.SetRange( 0, NB_PRIORITE-1 ) ;
	m_Priorite.SetPos( pEco->_PrioriteThread ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPriorite::OnOK() 
{
	CEconomiseur*	pEco	=	CEconomiseur::GetEconomiseur() ;
	pEco->_PrioriteThread	=	m_Priorite.GetPos() ;

	CPropertyPage::OnOK();
}
