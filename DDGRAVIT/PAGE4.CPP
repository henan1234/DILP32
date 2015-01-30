// Page4.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Page4.h"

#include "RectAffichage.h"
#include "EcoGravitation.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage4 property page

IMPLEMENT_DYNCREATE(CPage4, CPropertyPage)

CPage4::CPage4() : CPropertyPage(CPage4::IDD)
{
	//{{AFX_DATA_INIT(CPage4)
	m_CreationComete = 0;
	m_Etoiles = 0;
	m_MaxPoussieres = 0;
	m_Poussieres = 0.0;
	m_Repere = 0;
	m_Traveling = 0.0;
	m_TaillePoussieres = 0;
	//}}AFX_DATA_INIT
}

CPage4::~CPage4()
{
}

void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage4)
	DDX_Text(pDX, IDC_CREE_COMETES, m_CreationComete);
	DDX_Text(pDX, IDC_ETOILES, m_Etoiles);
	DDX_Text(pDX, IDC_MAX_POUSSIERES, m_MaxPoussieres);
	DDV_MinMaxInt(pDX, m_MaxPoussieres, 0, 2000);
	DDX_Text(pDX, IDC_POUSSIERES, m_Poussieres);
	DDV_MinMaxDouble(pDX, m_Poussieres, 0., 100.);
	DDX_Text(pDX, IDC_REPERE, m_Repere);
	DDX_Text(pDX, IDC_TRAVELLING, m_Traveling);
	DDX_Text(pDX, IDC_TAILLE_POUSSIERES, m_TaillePoussieres);
	DDV_MinMaxInt(pDX, m_TaillePoussieres, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CPage4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage4 message handlers

BOOL CPage4::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	
	m_CreationComete = pEco->_CreationComete ;
	m_Etoiles = pEco->_DensiteEtoiles ;
	m_MaxPoussieres = pEco->_NbMaxPoussieres ;
	m_Poussieres = pEco->_BruitPoussieres ;
	m_Repere = pEco->_Repere ;
	m_Traveling = pEco->_CoeffTraveling ;
	m_TaillePoussieres= pEco->_TaillePoussieres ;

	UpdateData( FALSE ) ;

	if ( pEco->ShareWare())
		{
		GetDlgItem( IDC_POUSSIERES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_TRAVELLING )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_CREE_COMETES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_ETOILES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_MAX_POUSSIERES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_REPERE )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_TAILLE_POUSSIERES )->EnableWindow( FALSE ) ;
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage4::OnOK() 
{
	UpdateData( TRUE ) ;

	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	
	pEco->_CreationComete 	= m_CreationComete	;
	pEco->_DensiteEtoiles 	= m_Etoiles			;
	pEco->_NbMaxPoussieres	= m_MaxPoussieres	;
	pEco->_BruitPoussieres	= m_Poussieres		;
	pEco->_Repere			= m_Repere		;
	pEco->_CoeffTraveling 	= m_Traveling		;
	pEco->_TaillePoussieres	= m_TaillePoussieres ;

	CPropertyPage::OnOK();
}
