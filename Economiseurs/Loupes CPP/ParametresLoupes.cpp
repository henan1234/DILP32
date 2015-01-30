// ParametresLoupes.cpp : implementation file
//

#include "stdafx.h"
#include <registrationkey.h>
#include "resource.h"
#include "loupes.h"
#include "ParametresLoupes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParametresLoupes property page

IMPLEMENT_DYNCREATE(CParametresLoupes, CPropertyPage)

CParametresLoupes::CParametresLoupes() : CPropertyPage(CParametresLoupes::IDD)
{
	//{{AFX_DATA_INIT(CParametresLoupes)
	m_Noir = FALSE;
	m_Texte = _T("");
	//}}AFX_DATA_INIT
}

CParametresLoupes::~CParametresLoupes()
{
}

void CParametresLoupes::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParametresLoupes)
	DDX_Control(pDX, IDC_SLIDER1, m_Slider);
	DDX_Check(pDX, IDC_NOIR, m_Noir);
	DDX_Text(pDX, IDC_TEXT, m_Texte);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParametresLoupes, CPropertyPage)
	//{{AFX_MSG_MAP(CParametresLoupes)
	ON_BN_CLICKED(IDC_COULEUR, OnCouleur)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParametresLoupes message handlers

BOOL CParametresLoupes::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CLoupes*	pEco	=	(CLoupes*)CEconomiseur::GetEconomiseur() ;
	m_Noir	=	pEco->NoircirEcran ;

	m_Slider.SetRange( 1, NB_MAX_SPRITES ) ;
	m_Slider.SetPos( pEco->NbMaxSprites ) ;
	
	m_Texte	=	pEco->_Texte ;

	UpdateData( FALSE ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CParametresLoupes::OnOK() 
{
	UpdateData( TRUE ) ;	

	CLoupes*	pEco	=	(CLoupes*)CEconomiseur::GetEconomiseur() ;

	pEco->NoircirEcran	=	m_Noir ;
	pEco->NbMaxSprites	=	m_Slider.GetPos() ;
	pEco->_Texte			=	m_Texte ;
	
	CPropertyPage::OnOK();
}

BOOL CParametresLoupes::OnSetActive() 
{
	CRegistrationKey	*	pKey	=	CRegistrationKey::GetKey() ;

	if ( pKey->IsLocked())
		{
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_TEXT ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR ), FALSE ) ;
		}
	else
		{
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_TEXT ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR ), TRUE ) ;
		}

	return CPropertyPage::OnSetActive();
}

void CParametresLoupes::OnCouleur() 
{
	CLoupes*	pEco	=	(CLoupes*)CEconomiseur::GetEconomiseur() ;
	CColorDialog	Dlg( pEco->_CouleurTexte, CC_SOLIDCOLOR | CC_FULLOPEN ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		pEco->_CouleurTexte	=	Dlg.GetColor() ;
		}
}
