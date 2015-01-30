// PageMasses.cpp : implementation file
//


#include "stdafx.h"
#include "resource.h"

#include <RegistrationKey.h>
#include <Dib.h>
#include <DibSurface.h>
#include <DibPal.h>

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"
#include "PageMasses.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageMasses property page

IMPLEMENT_DYNCREATE(CPageMasses, CPropertyPage)

CPageMasses::CPageMasses() : CPropertyPage(CPageMasses::IDD)
{
	//{{AFX_DATA_INIT(CPageMasses)
	m_Masse0 = 0.0;
	m_Masse1 = 0.0;
	m_Masse2 = 0.0;
	m_Masse3 = 0.0;
	m_Masse4 = 0.0;
	m_Masse5 = 0.0;
	m_Masse6 = 0.0;
	m_Masse7 = 0.0;
	//}}AFX_DATA_INIT

	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_MASSES ) ;
}

CPageMasses::~CPageMasses()
{
}

void CPageMasses::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMasses)
	DDX_Text(pDX, IDC_M0, m_Masse0);
	DDX_Text(pDX, IDC_M1, m_Masse1);
	DDX_Text(pDX, IDC_M2, m_Masse2);
	DDX_Text(pDX, IDC_M3, m_Masse3);
	DDX_Text(pDX, IDC_M4, m_Masse4);
	DDX_Text(pDX, IDC_M5, m_Masse5);
	DDX_Text(pDX, IDC_M6, m_Masse6);
	DDX_Text(pDX, IDC_M7, m_Masse7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageMasses, CPropertyPage)
	//{{AFX_MSG_MAP(CPageMasses)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_USER_PARAMETERS, OnUserParameters )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageMasses message handlers

void CPageMasses::OnOK() 
{
	CPropertyPage::OnOK();

	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	pEco->_Bitmap[0].MasseMax = m_Masse0	;
	pEco->_Bitmap[1].MasseMax = m_Masse1	;
	pEco->_Bitmap[2].MasseMax = m_Masse2	;
	pEco->_Bitmap[3].MasseMax = m_Masse3	;
	pEco->_Bitmap[4].MasseMax = m_Masse4	;
	pEco->_Bitmap[5].MasseMax = m_Masse5	;
	pEco->_Bitmap[6].MasseMax = m_Masse6	;
	pEco->_Bitmap[7].MasseMax = m_Masse7	;
}

BOOL CPageMasses::OnInitDialog() 
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Masse0	=	pEco->_Bitmap[0].MasseMax ;
	m_Masse1	=	pEco->_Bitmap[1].MasseMax ;
	m_Masse2	=	pEco->_Bitmap[2].MasseMax ;
	m_Masse3	=	pEco->_Bitmap[3].MasseMax ;
	m_Masse4	=	pEco->_Bitmap[4].MasseMax ;
	m_Masse5	=	pEco->_Bitmap[5].MasseMax ;
	m_Masse6	=	pEco->_Bitmap[6].MasseMax ;
	m_Masse7	=	pEco->_Bitmap[7].MasseMax ;

	CPropertyPage::OnInitDialog();
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPageMasses::OnSetActive() 
{
	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	if ( pKey->IsLocked() )
		{
		GetDlgItem( IDC_M6 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M5 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M4 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M3 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M2 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M1 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_M0 )->EnableWindow( FALSE ) ;
		}
	else
		{
		GetDlgItem( IDC_M6 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M5 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M4 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M3 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M2 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M1 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_M0 )->EnableWindow( TRUE ) ;
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
LONG	CPageMasses::OnUserParameters( UINT wParam, LONG lParam )
{
	if ( wParam )
		{
		UpdateData( TRUE ) ;

		// Lire les parametres dans les controles
		// Les valeurs sont modifiees en temps reel, donc pas besoin de rien faire
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

		pEco->_Bitmap[0].MasseMax = m_Masse0	;
		pEco->_Bitmap[1].MasseMax = m_Masse1	;
		pEco->_Bitmap[2].MasseMax = m_Masse2	;
		pEco->_Bitmap[3].MasseMax = m_Masse3	;
		pEco->_Bitmap[4].MasseMax = m_Masse4	;
		pEco->_Bitmap[5].MasseMax = m_Masse5	;
		pEco->_Bitmap[6].MasseMax = m_Masse6	;
		pEco->_Bitmap[7].MasseMax = m_Masse7	;
		}
	else
		{
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

		m_Masse0	=	pEco->_Bitmap[0].MasseMax ;
		m_Masse1	=	pEco->_Bitmap[1].MasseMax ;
		m_Masse2	=	pEco->_Bitmap[2].MasseMax ;
		m_Masse3	=	pEco->_Bitmap[3].MasseMax ;
		m_Masse4	=	pEco->_Bitmap[4].MasseMax ;
		m_Masse5	=	pEco->_Bitmap[5].MasseMax ;
		m_Masse6	=	pEco->_Bitmap[6].MasseMax ;
		m_Masse7	=	pEco->_Bitmap[7].MasseMax ;

		UpdateData( FALSE ) ;
		}

	return 0 ;
}
