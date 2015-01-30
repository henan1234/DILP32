// Configuration.cpp : implementation file
//

#include "stdafx.h"
#include "tasdesable.h"
#include "Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern double ValDescente ;

/////////////////////////////////////////////////////////////////////////////
// CConfiguration dialog


CConfiguration::CConfiguration()
	: CPropertyPage(CConfiguration::IDD)
{
	//{{AFX_DATA_INIT(CConfiguration)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfiguration::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfiguration)
	DDX_Control(pDX, IDC_SLIDER1, m_Vitesse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfiguration, CPropertyPage)
	//{{AFX_MSG_MAP(CConfiguration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfiguration message handlers

BOOL CConfiguration::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	//CTasDeSable	*	pEco	=	(CTasDeSable*)CEconomiseur::GetEconomiseur() ;
	
	m_Vitesse.SetRange( 10, 50 ) ;
	m_Vitesse.SetPos( (int)(ValDescente*10.0) ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfiguration::OnOK() 
{
	ValDescente	=	(double)m_Vitesse.GetPos() / 10.0 ;
	
	CPropertyPage::OnOK();
}
