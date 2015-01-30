// PageComete.cpp : implementation file
//

#include "..\stdafx.h"
#include "resource.h"


#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"
#include "PageComete.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageComete property page

IMPLEMENT_DYNCREATE(CPageComete, CPropertyPage)

CPageComete::CPageComete() : CPropertyPage(CPageComete::IDD)
{
	//{{AFX_DATA_INIT(CPageComete)
	m_CreationComete = 0;
	m_Dispersion = 0;
	m_MaxPoussieres = 0;
	m_TailleMax = 0;
	m_ViePoussieres = 0;
	m_VentSolaire = 0.0;
	//}}AFX_DATA_INIT
}

CPageComete::~CPageComete()
{
}

void CPageComete::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageComete)
	DDX_Control(pDX, IDC_SPIN_MAX, m_SpinMax);
	DDX_Control(pDX, IDC_SPIN_DISPERSION, m_SpinDispersion);
	DDX_Text(pDX, IDC_CREE_COMETES, m_CreationComete);
	DDV_MinMaxInt(pDX, m_CreationComete, 1, 1000000);
	DDX_Text(pDX, IDC_DISPERSION, m_Dispersion);
	DDV_MinMaxInt(pDX, m_Dispersion, 0, 100);
	DDX_Text(pDX, IDC_MAX_POUSSIERES, m_MaxPoussieres);
	DDV_MinMaxInt(pDX, m_MaxPoussieres, 0, 2000);
	DDX_Text(pDX, IDC_TAILLE_MAX, m_TailleMax);
	DDV_MinMaxInt(pDX, m_TailleMax, 1, 10);
	DDX_Text(pDX, IDC_VIE_POUSSIERES, m_ViePoussieres);
	DDV_MinMaxInt(pDX, m_ViePoussieres, 0, 60);
	DDX_Text(pDX, IDC_VENT, m_VentSolaire);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageComete, CPropertyPage)
	//{{AFX_MSG_MAP(CPageComete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageComete message handlers

BOOL CPageComete::OnInitDialog() 
{
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_CreationComete	=	pEco->_CreationComete	;
	m_Dispersion		=	pEco->_BruitPoussieres	;
	m_MaxPoussieres		=	pEco->_NbMaxPoussieres	;
	m_TailleMax			=	pEco->_TaillePoussieres	;
	m_VentSolaire		=	pEco->_VentSolaire ;
	m_ViePoussieres		=	pEco->_ViePoussieres ;

	CPropertyPage::OnInitDialog();

	m_SpinMax.SetRange( 0, NB_MAX_POUSSIERES ) ;
	m_SpinMax.SetPos( m_MaxPoussieres ) ;

	m_SpinDispersion.SetRange( 0, 100 ) ;
	m_SpinDispersion.SetPos( m_Dispersion ) ;

	if ( pEco->ShareWare() )
		{
		GetDlgItem( IDC_VENT )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_MAX_POUSSIERES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_TAILLE_MAX )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_VIE_POUSSIERES )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_DISPERSION )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_CREE_COMETES )->EnableWindow( FALSE ) ;
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageComete::OnOK() 
{
	UpdateData( TRUE ) ;
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	pEco->_CreationComete	= m_CreationComete		;
	pEco->_BruitPoussieres	= m_Dispersion			;
	pEco->_NbMaxPoussieres	= m_MaxPoussieres		;
	pEco->_TaillePoussieres	= m_TailleMax			;
	pEco->_VentSolaire		= m_VentSolaire			;
	pEco->_ViePoussieres	= m_ViePoussieres		;

	
	CPropertyPage::OnOK();
}
