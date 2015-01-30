// PageGenese.cpp : implementation file
//

#include "..\stdafx.h"
#include "resource.h"
#include "PageGenese.h"
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\DibPal.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageGenese property page

IMPLEMENT_DYNCREATE(CPageGenese, CPropertyPage)

CPageGenese::CPageGenese() : CPropertyPage(CPageGenese::IDD)
{
	//{{AFX_DATA_INIT(CPageGenese)
	m_Depart = -1;
	//}}AFX_DATA_INIT

		m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_CREATION ) ;
}

CPageGenese::~CPageGenese()
{
}

void CPageGenese::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageGenese)
	DDX_Radio(pDX, IDC_RADIO1, m_Depart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageGenese, CPropertyPage)
	//{{AFX_MSG_MAP(CPageGenese)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageGenese message handlers

BOOL CPageGenese::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	m_Depart	=	pEco->_Depart ;

	UpdateData( FALSE ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageGenese::OnOK() 
{
	UpdateData( TRUE ) ;
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	pEco->_Depart = m_Depart ;
	
	CPropertyPage::OnOK();
}
