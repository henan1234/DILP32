// PagePhysique.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PagePhysique.h"
#include <RegistrationKey.h>
#include <Dib.h>
#include <DibSurface.h>
#include <DibPal.h>

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPagePhysique property page

IMPLEMENT_DYNCREATE(CPagePhysique, CPropertyPage)

CPagePhysique::CPagePhysique() : CPropertyPage(CPagePhysique::IDD)
{
	//{{AFX_DATA_INIT(CPagePhysique)
	m_Collision = 0.0;
	m_CoeffDistance = 0.0;
	m_G = 0.0;
	m_Liberation = 0.0;
	m_CoeffTemps = 0.0;
	m_Rayon = 0.0;
	//}}AFX_DATA_INIT

	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_PHYSIQUE ) ;
}

CPagePhysique::~CPagePhysique()
{
}

void CPagePhysique::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagePhysique)
	DDX_Control(pDX, IDC_SPIN_LIBERATION, m_SpinLiberation);
	DDX_Text(pDX, IDC_COLLISION, m_Collision);
	DDX_Text(pDX, IDC_DISTANCE, m_CoeffDistance);
	DDX_Text(pDX, IDC_G, m_G);
	DDX_Text(pDX, IDC_LIBERATION, m_Liberation);
	DDV_MinMaxDouble(pDX, m_Liberation, 0., 100.);
	DDX_Text(pDX, IDC_TEMPS, m_CoeffTemps);
	DDX_Text(pDX, IDC_RAYON, m_Rayon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagePhysique, CPropertyPage)
	//{{AFX_MSG_MAP(CPagePhysique)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_USER_PARAMETERS, OnUserParameters )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagePhysique message handlers

void CPagePhysique::OnOK() 
{
	UpdateData( TRUE ) ;

	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	pEco->_DeltaVMax			= m_Collision ;
	pEco->CoeffDistance		= m_CoeffDistance ;
	pEco->_G				= m_G ;
	pEco->_CoeffLiberation	= m_Liberation ;
	pEco->_IntervalleTemps	= m_CoeffTemps ;
	pEco->CoeffRayon		= m_Rayon				 ;
	
	CPropertyPage::OnOK();
}

BOOL CPagePhysique::OnInitDialog() 
{
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Collision		= pEco->_DeltaVMax		;
	m_CoeffDistance = pEco->CoeffDistance	;
	m_G				= pEco->_G				;
	m_Liberation	= pEco->_CoeffLiberation;
	m_CoeffTemps	= pEco->_IntervalleTemps ;
	m_Rayon			= pEco->CoeffRayon ;

	CPropertyPage::OnInitDialog();

	m_SpinLiberation.SetRange( 0, 100 ) ;
	m_SpinLiberation.SetPos( (int)m_Liberation ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////////////
// OnUserParameter
// Message prive WM_USER_PARAMETER envoie par la premiere page sur action sur
// un des boutons de lecture/ecriture de fichiers
// ENTREES :
//		wParam : TRUE : lire les parametres saisis et les stocker dans l'economiseur
//				 FALSE : lire les parametres dans l'economiseur et les mettre dans les controles
///////////////////////////////////////////////////////////////////////////////
LONG	CPagePhysique::OnUserParameters( UINT wParam, LONG lParam )
{
	if ( wParam )
		{
		// Lire les parametres dans les controles
		// Les valeurs sont modifiees en temps reel, donc pas besoin de rien faire
		UpdateData( TRUE ) ;

		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

		pEco->_DeltaVMax			= m_Collision ;
		pEco->CoeffDistance		= m_CoeffDistance ;
		pEco->_G				= m_G ;
		pEco->_CoeffLiberation	= m_Liberation ;
		pEco->_IntervalleTemps	= m_CoeffTemps ;
		pEco->CoeffRayon		= m_Rayon				 ;
		}
	else
		{
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

		m_Collision		= pEco->_DeltaVMax		;
		m_CoeffDistance = pEco->CoeffDistance	;
		m_G				= pEco->_G				;
		m_Liberation	= pEco->_CoeffLiberation;
		m_CoeffTemps	= pEco->_IntervalleTemps ;
		m_Rayon			= pEco->CoeffRayon ;

		m_SpinLiberation.SetRange( 0, 100 ) ;
		m_SpinLiberation.SetPos( (int)m_Liberation ) ;

		UpdateData( FALSE ) ;
		}

	return 0 ;
}

BOOL CPagePhysique::OnSetActive() 
{
	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	if ( pKey->IsLocked())
		{
		GetDlgItem( IDC_TEMPS )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_DISTANCE )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_LIBERATION )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_COLLISION )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_RAYON )->EnableWindow( FALSE ) ;
		}	
	else
		{
		GetDlgItem( IDC_TEMPS )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_DISTANCE )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_LIBERATION )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_COLLISION )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_RAYON )->EnableWindow( TRUE ) ;
		}
	return CPropertyPage::OnSetActive();
}
