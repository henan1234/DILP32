// PageAffichage.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <RegistrationKey.h>
#include <Dib.h>
#include <DibSurface.h>
#include <DibPal.h>

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
	m_Repere = FALSE;
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
	DDX_Control(pDX, IDC_SLIDER_ZOOM, m_SliderZoom);
	DDX_Control(pDX, IDC_SLIDER_TRAVELLING, m_SliderTraveling);
	DDX_Control(pDX, IDC_SLIDER_IMAGES, m_SliderImages);
	DDX_Control(pDX, IDC_SLIDER_ETOILES, m_SliderEtoiles);
	DDX_Check(pDX, IDC_REPERE, m_Repere);
	DDX_Check(pDX, IDC_RESOLUTION, m_Resolution);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CPageAffichage, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAffichage)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_USER_PARAMETERS, OnUserParameters )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAffichage message handlers

void CPageAffichage::OnOK() 
{
	GetControls() ;

	CPropertyPage::OnOK();
}

BOOL CPageAffichage::OnInitDialog() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	CPropertyPage::OnInitDialog();

	///////////////////////////////////////////////////////////////////////////
	// Slider image / secondes
	///////////////////////////////////////////////////////////////////////////
	SetControls() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageAffichage::OnSetActive() 
{
	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	if ( pKey->IsLocked() )
		{
		GetDlgItem( IDC_SLIDER_IMAGES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_REPERE )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_SLIDER_TRAVELLING )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_SLIDER_ZOOM )->EnableWindow( FALSE ) ;
		}
	else
		{
		GetDlgItem( IDC_SLIDER_IMAGES )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_REPERE )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_SLIDER_TRAVELLING )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_SLIDER_ZOOM )->EnableWindow( TRUE ) ;
		}

	return CPropertyPage::OnSetActive();
}


///////////////////////////////////////////////////////////////////////////////
// OnUserParameter
// Message prive WM_USER_PARAMETER envoie par la premiere page sur action sur
// un des boutons de lecture/ecriture de fichiers
// ENTREES :
//		wParam : TRUE : lire les parametres saisis et les stocker dans l'economiseur
//				 FALSE : lire les parametres dans l'economiseur et les mettre dans les controles
///////////////////////////////////////////////////////////////////////////////
LONG	CPageAffichage::OnUserParameters( UINT wParam, LONG lParam )
{
	if ( wParam )
		{
		// Lire les parametres dans les controles
		// Les valeurs sont modifiees en temps reel, donc pas besoin de rien faire
		GetControls() ;
		}
	else
		{
		SetControls() ;
		}

	return 0 ;
}

void CPageAffichage::SetControls()
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_SliderImages.SetRange( 20, 30 ) ;
	m_SliderImages.SetPos( pEco->_NbImagesSecondes ) ;

	///////////////////////////////////////////////////////////////////////////
	// Slider travelling 0.005, 0.01, 0.05, 0.1, 0.5, 1
	///////////////////////////////////////////////////////////////////////////
	m_SliderTraveling.SetRange( 0, 5 ) ;
	if ( pEco->_CoeffTraveling <= 0.005 )
		m_SliderTraveling.SetPos( 0 ) ;
	else
	if ( pEco->_CoeffTraveling <= 0.01 )
		m_SliderTraveling.SetPos( 1 ) ;
	else
	if ( pEco->_CoeffTraveling <= 0.05 )
		m_SliderTraveling.SetPos( 2 ) ;
	else
	if ( pEco->_CoeffTraveling <= 0.1 )
		m_SliderTraveling.SetPos( 3 ) ;
	else
	if ( pEco->_CoeffTraveling <= 0.5 )
		m_SliderTraveling.SetPos( 4 ) ;
	else
		m_SliderTraveling.SetPos( 5 ) ;

	
	///////////////////////////////////////////////////////////////////////////
	// Facteur zoom de 1 a 50
	///////////////////////////////////////////////////////////////////////////
	m_SliderZoom.SetRange( 1, 50 ) ;
	m_SliderZoom.SetPos( (int)pEco->_ZoomMax ) ;

	///////////////////////////////////////////////////////////////////////////
	// Densite d'etoiles,  de 0 a 1000
	///////////////////////////////////////////////////////////////////////////
	m_SliderEtoiles.SetRange( 0, 100 ) ;
	m_SliderEtoiles.SetPos( pEco->_DensiteEtoiles / 10 ) ;

	///////////////////////////////////////////////////////////////////////////
	// Check boxes
	///////////////////////////////////////////////////////////////////////////
	m_Repere	=	pEco->_AfficherRepere ;
	m_Resolution=	pEco->_ChangeResolution ;

	UpdateData( FALSE ) ;
}

void CPageAffichage::GetControls()
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	UpdateData( TRUE ) ;

	///////////////////////////////////////////////////////////////////////////
	// Slider image / secondes
	///////////////////////////////////////////////////////////////////////////
	pEco->_NbImagesSecondes		=	m_SliderImages.GetPos() ;

	///////////////////////////////////////////////////////////////////////////
	// Slider travelling 0.005, 0.01, 0.05, 0.1, 0.5, 1
	///////////////////////////////////////////////////////////////////////////
	switch( m_SliderTraveling.GetPos())
		{
		case 0 :
			pEco->_CoeffTraveling	=	0.005 ;
			break ;

		case 1 :
			pEco->_CoeffTraveling	=	0.01 ;
			break ;
		case 2 :
			pEco->_CoeffTraveling	=	0.05 ;
			break ;
		case 3 :
			pEco->_CoeffTraveling	=	0.1 ;
			break ;
		case 4 :
			pEco->_CoeffTraveling	=	0.5 ;
			break ;
		default :
			pEco->_CoeffTraveling	=	0.5 ;
			break ;
		}

	///////////////////////////////////////////////////////////////////////////
	// Facteur zoom de 1 a 50
	///////////////////////////////////////////////////////////////////////////
	pEco->_ZoomMax				=	m_SliderZoom.GetPos() ;

	///////////////////////////////////////////////////////////////////////////
	// Densite d'etoiles,  de 0 a 1000 ( 0 = pas d'etoiles )
	///////////////////////////////////////////////////////////////////////////
	pEco->_DensiteEtoiles		=	m_SliderEtoiles.GetPos() * 10 ;
	
	pEco->_AfficherRepere		=	m_Repere ;
	pEco->_ChangeResolution		=	m_Resolution ;
}
