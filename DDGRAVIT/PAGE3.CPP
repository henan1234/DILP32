// Page3.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Page3.h"

#include "RectAffichage.h"
#include "EcoGravitation.h"

/////////////////////////////////////////////////////////////////////////////
// CPage3 property page

IMPLEMENT_DYNCREATE(CPage3, CPropertyPage)

CPage3::CPage3() : CPropertyPage(CPage3::IDD)
{
	//{{AFX_DATA_INIT(CPage3)
	m_Collision = 0.0;
	m_Distance = 0.0;
	m_G = 0.0;
	m_Images = 0;
	m_Masses = 0.0;
	m_Rayon = 0.0;
	m_Temps = 0.0;
	//}}AFX_DATA_INIT
}

CPage3::~CPage3()
{
}

void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage3)
	DDX_Text(pDX, IDC_COLLISION, m_Collision);
	DDX_Text(pDX, IDC_DISTANCE, m_Distance);
	DDX_Text(pDX, IDC_G, m_G);
	DDX_Text(pDX, IDC_IMAGES, m_Images);
	DDX_Text(pDX, IDC_MASSE, m_Masses);
	DDX_Text(pDX, IDC_RAYON, m_Rayon);
	DDX_Text(pDX, IDC_TEMPS, m_Temps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CPage3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage3 message handlers

BOOL CPage3::OnInitDialog() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Collision		=	pEco->_DeltaVMax ;
	m_Distance		=	pEco->CoeffDistance ;
	m_G				=	pEco->_G ;
	m_Images		=	pEco->_NbImagesSecondes ;
	m_Masses		=	pEco->CoeffMasses ;
	m_Rayon			=	pEco->CoeffRayon ;
	m_Temps			=	pEco->_IntervalleTemps ;

	CPropertyPage::OnInitDialog();

	if ( pEco->ShareWare())
		{
		GetDlgItem( IDC_COLLISION )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_DISTANCE )->EnableWindow( FALSE ) ;
		//GetDlgItem( IDC_G )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_IMAGES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_MASSE )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_RAYON )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_VENT )->EnableWindow( FALSE ) ;	
		GetDlgItem( IDC_TEMPS )->EnableWindow( FALSE ) ;
		}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage3::OnOK() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	pEco->_DeltaVMax		=	m_Collision		;
	pEco->CoeffDistance		=	m_Distance		;
	pEco->_G				=	m_G				;
	pEco->_NbImagesSecondes =	m_Images		;
	pEco->CoeffMasses		=	m_Masses		;
	pEco->CoeffRayon		=	m_Rayon			;
	pEco->_IntervalleTemps	=	m_Temps			;
	
	CPropertyPage::OnOK();
}
