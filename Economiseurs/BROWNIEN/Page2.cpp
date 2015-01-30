// Page2.cpp : implementation file
//

#include "..\stdafx.h"
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\Dibpal.h"
#include "..\Economiseur Generique\RectAffichage.h"

#include "brownien.h"
#include "resource.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
	//{{AFX_DATA_INIT(CPage2)
	m_Charges = 0;
	m_Particules = 0;
	m_Vitesse = 0.0;
	//}}AFX_DATA_INIT
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
	DDX_Text(pDX, IDC_NB_CHARGES, m_Charges);
	DDX_Text(pDX, IDC_NB_PARTICULES, m_Particules);
	DDX_Text(pDX, IDC_VITESSE, m_Vitesse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers

BOOL CPage2::OnInitDialog() 
{
	CEcoBrownien*	pEco	=	(CEcoBrownien*)CEconomiseur::GetEconomiseur() ;

	m_Charges		=	pEco->NombreCouleurs ;
	m_Particules	=	pEco->NbCorps ;
	m_Vitesse		=	pEco->CoeffAttraction ;
	
	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage2::OnOK() 
{
	CPropertyPage::OnOK();
	CEcoBrownien*	pEco	=	(CEcoBrownien*)CEconomiseur::GetEconomiseur() ;

	pEco->NombreCouleurs=	m_Charges ;
	pEco->NbCorps		=	m_Particules ;
	pEco->CoeffAttraction	=	m_Vitesse ;
}

