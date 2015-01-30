// PageAffichage.cpp : implementation file
//

#include "..\stdafx.h"
#include "resource.h"
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\DibPal.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"

#include "PageAffichage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageAffichage property page

IMPLEMENT_DYNCREATE(CPageAffichage, CPropertyPage)

CPageAffichage::CPageAffichage() : CPropertyPage(CPageAffichage::IDD)
{
	//{{AFX_DATA_INIT(CPageAffichage)
	m_Images = 0;
	m_Traveling = 0.0;
	m_Effacer = FALSE;
	m_Zoom = 0.0;
	m_Repere = FALSE;
	m_Etoiles = 0;
	m_Resolution = FALSE;
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_AFFICHAGE ) ;
}

CPageAffichage::~CPageAffichage()
{
}

void CPageAffichage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAffichage)
	DDX_Control(pDX, IDC_SPIN_IMAGES, m_SpinImages);
	DDX_Control(pDX, IDC_SPIN1, m_SpinZoom);
	DDX_Text(pDX, IDC_IMAGES, m_Images);
	DDV_MinMaxInt(pDX, m_Images, 1, 30);
	DDX_Text(pDX, IDC_TRAVELLING, m_Traveling);
	DDX_Check(pDX, IDC_EFFACER, m_Effacer);
	DDX_Text(pDX, IDC_ZOOM, m_Zoom);
	DDV_MinMaxDouble(pDX, m_Zoom, 1., 100.);
	DDX_Check(pDX, IDC_REPERE, m_Repere);
	DDX_Text(pDX, IDC_ETOILES, m_Etoiles);
	DDX_Check(pDX, IDC_RESOLUTION, m_Resolution);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAffichage, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAffichage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAffichage message handlers

void CPageAffichage::OnOK() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	UpdateData( TRUE ) ;

	pEco->_NbImagesSecondes		=	m_Images	 ;
	pEco->_CoeffTraveling		=	m_Traveling  ;
	pEco->_Effacer				=	m_Effacer ;
	pEco->_ZoomMax				=	m_Zoom ;
	pEco->_AfficherRepere		=	m_Repere ;
	pEco->_DensiteEtoiles		=	m_Etoiles ;
	pEco->_ChangeResolution		=	m_Resolution ;
	CPropertyPage::OnOK();
}

BOOL CPageAffichage::OnInitDialog() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Images = pEco->_NbImagesSecondes ;
	m_Etoiles = pEco->_DensiteEtoiles ;
	m_Traveling = pEco->_CoeffTraveling ;
	m_Effacer	=	pEco->_Effacer ;
	m_Zoom		=	pEco->_ZoomMax ;
	m_Repere	=	pEco->_AfficherRepere ;
	m_Resolution=	pEco->_ChangeResolution ;
	CPropertyPage::OnInitDialog();
	
	m_SpinZoom.SetRange( 1, 100 ) ;
	m_SpinZoom.SetPos( (int)m_Zoom ) ;

	m_SpinImages.SetRange( 1, 30 ) ;
	m_SpinImages.SetPos( m_Images ) ;

	if ( pEco->ShareWare())
		{
		GetDlgItem( IDC_IMAGES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_REPERE )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_TRAVELLING )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_ZOOM )->EnableWindow( FALSE ) ;
		}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
