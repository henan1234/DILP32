// PageGenese.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "PageGenese.h"
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\DibPal.h"
#include <RegistrationKey.h>

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
	m_2D = -1;
	m_Fichier = _T("");
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
	DDX_Control(pDX, IDC_PARCOURIR, m_CtrlParcourir);
	DDX_Control(pDX, IDC_FICHIER, m_CtrlFichier);
	DDX_Radio(pDX, IDC_RADIO1, m_Depart);
	DDX_Radio(pDX, IDC_RADIO_2D, m_2D);
	DDX_Text(pDX, IDC_FICHIER, m_Fichier);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageGenese, CPropertyPage)
	//{{AFX_MSG_MAP(CPageGenese)
	ON_BN_CLICKED(IDC_PARCOURIR, OnParcourir)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_USER_PARAMETERS, OnUserParameters )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageGenese message handlers

BOOL CPageGenese::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Depart	=	pEco->_Depart ;

	if ( m_Depart == 5 )
		{
		m_CtrlFichier.EnableWindow( TRUE ) ;
		m_CtrlParcourir.EnableWindow( TRUE ) ;
		}
	else
		{
		m_CtrlFichier.EnableWindow( FALSE ) ;
		m_CtrlParcourir.EnableWindow( FALSE ) ;
		}

	m_2D		=	pEco->_3D ? 1 : 0 ;
	m_Fichier	=	pEco->_FichierInit ;

	UpdateData( FALSE ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageGenese::OnOK() 
{
	UpdateData( TRUE ) ;
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;


	pEco->_Depart = m_Depart ;
	pEco->_3D	  = m_2D == 0 ? 0 : 1 ;
	pEco->_FichierInit	=	m_Fichier ;
	
	CPropertyPage::OnOK();
}

///////////////////////////////////////////////////////////////////////////////
// OnUserParameter
// Message prive WM_USER_PARAMETER envoie par la premiere page sur action sur
// un des boutons de lecture/ecriture de fichiers
// ENTREES :
//		wParam : TRUE : lire les parametres saisis et les stocker dans l'economiseur
//				 FALSE : lire les parametres dans l'economiseur et les mettre dans les controles
///////////////////////////////////////////////////////////////////////////////
LONG	CPageGenese::OnUserParameters( UINT wParam, LONG lParam )
{
	if ( wParam )
		{
		// Lire les parametres dans les controles
		// Les valeurs sont modifiees en temps reel, donc pas besoin de rien faire
		UpdateData( TRUE ) ;
		
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
		pEco->_Depart = m_Depart ;
		pEco->_3D	  = m_2D == 0 ? 0 : 1 ;
		pEco->_FichierInit	=	m_Fichier ;
		}
	else
		{
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
		m_Depart	=	pEco->_Depart ;
		m_2D		=	pEco->_3D ? 1 : 0 ;
		m_Fichier	=	pEco->_FichierInit ;

		UpdateData( FALSE ) ;
		}

	return 0 ;
}

void CPageGenese::OnParcourir() 
{
	CString	Filter ;
	Filter.LoadString( IDS_FILTRE_FICHIER_UNIVERS ) ;

	CFileDialog Dlg( TRUE, ".Universe", m_Fichier,
					 OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
					 Filter, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		// Enregistrer les parametres
		CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
		
		pEco->_FichierInit	=	Dlg.GetPathName() ;
		pEco->LoadFile( pEco->_FichierInit ) ;
		pEco->_Depart	=	5 ;

		// Charger tous les parametres dans toutes les pages
		AvertitPages(  ) ;
		}
}

void CPageGenese::OnRadio1() 
{
	m_CtrlFichier.EnableWindow( FALSE ) ;
	m_CtrlParcourir.EnableWindow( FALSE ) ;
}

void CPageGenese::OnRadio2() 
{
	m_CtrlFichier.EnableWindow( FALSE ) ;
	m_CtrlParcourir.EnableWindow( FALSE ) ;
}

void CPageGenese::OnRadio3() 
{
	m_CtrlFichier.EnableWindow( FALSE ) ;
	m_CtrlParcourir.EnableWindow( FALSE ) ;
}

void CPageGenese::OnRadio4() 
{
	m_CtrlFichier.EnableWindow( FALSE ) ;
	m_CtrlParcourir.EnableWindow( FALSE ) ;
}

void CPageGenese::OnRadio5() 
{
	m_CtrlFichier.EnableWindow( FALSE ) ;
	m_CtrlParcourir.EnableWindow( FALSE ) ;
}

void CPageGenese::OnRadio6() 
{
	m_CtrlFichier.EnableWindow( TRUE ) ;
	m_CtrlParcourir.EnableWindow( TRUE ) ;
}

void CPageGenese::AvertitPages()
{
	CPropertySheet	*	pParent	=	(CPropertySheet*)GetParent() ;

	const int NbPages	=	pParent->GetPageCount() ;

	for ( int i = 0; i < NbPages; i++)
		{
		CPropertyPage * pPage = pParent->GetPage(i) ;

		// Demander a la page de lire ses parametres et les stocker dans l'econimiseur
		// Attention ! Elle n'a peut etre pas encore ete creee
		if ( IsWindow( pPage->m_hWnd ))
			pPage->SendMessage( WM_USER_PARAMETERS, FALSE, 0 ) ;
		}
}

BOOL CPageGenese::OnSetActive() 
{
	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	if ( pKey->IsLocked() )
		{
		if ( m_Depart > 4 )
			{
			m_Depart	=	4 ;
			UpdateData( FALSE ) ;
			}

		GetDlgItem( IDC_RADIO6 )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_FICHIER )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_PARCOURIR )->EnableWindow( FALSE ) ;
		}
	else
		{
		GetDlgItem( IDC_RADIO6 )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_FICHIER )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_PARCOURIR )->EnableWindow( TRUE ) ;
		}
	
	return CPropertyPage::OnSetActive();
}
