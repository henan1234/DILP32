// PageFond.cpp : implementation file
//

#include "..\stdafx.h"
#include "resource.h"
#include "PageFond.h"
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\DibPal.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageFond property page

IMPLEMENT_DYNCREATE(CPageFond, CPropertyPage)

CPageFond::CPageFond() : CPropertyPage(CPageFond::IDD)
{
	//{{AFX_DATA_INIT(CPageFond)
	m_Etoiles = 0;
	m_Fichier = _T("");
	m_Noir = -1;
	//}}AFX_DATA_INIT
}

CPageFond::~CPageFond()
{
}

void CPageFond::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFond)
	DDX_Control(pDX, IDC_PARCOURIR, m_CtlParcourir);
	DDX_Control(pDX, IDC_FICHIER, m_CtlFichier);
	DDX_Control(pDX, IDC_ETOILES, m_CtlEtoiles);
	DDX_Text(pDX, IDC_ETOILES, m_Etoiles);
	DDV_MinMaxInt(pDX, m_Etoiles, 0, 10000);
	DDX_Text(pDX, IDC_FICHIER, m_Fichier);
	DDX_Radio(pDX, IDC_NOIR, m_Noir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageFond, CPropertyPage)
	//{{AFX_MSG_MAP(CPageFond)
	ON_BN_CLICKED(IDC_NOIR, OnNoir)
	ON_BN_CLICKED(IDC_IMAGE, OnImage)
	ON_BN_CLICKED(IDC_PARCOURIR, OnParcourir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageFond message handlers

void CPageFond::OnNoir() 
{
	m_Noir	=	0 ;

	UpdateControle() ;
}

void CPageFond::OnImage() 
{
	m_Noir	=	1 ;

	UpdateControle() ;
}

void CPageFond::OnParcourir() 
{
	CFileDialog	Dlg( TRUE, "*.BMP", m_Fichier,
					 OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_EXPLORER | OFN_FILEMUSTEXIST,
					 "Fichiers images|*.BMP; *.DIB", this ) ;

	if ( Dlg.DoModal())
		{
		m_Fichier	=	Dlg.GetPathName() ;
		UpdateData( FALSE ) ;
		}
}

BOOL CPageFond::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	m_Noir		=	pEco->_Noir ? 0 : 1 ;
	m_Fichier	=	pEco->_Fichier ;
	m_Etoiles	=	pEco->_DensiteEtoiles ;

	UpdateControle() ;

	UpdateData( FALSE ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageFond::UpdateControle( void )
{
	m_CtlEtoiles.EnableWindow( m_Noir == 0 ) ;
	m_CtlFichier.EnableWindow( m_Noir == 1) ;
	m_CtlParcourir.EnableWindow( m_Noir == 1 ) ;
}

void CPageFond::OnOK() 
{
	CPropertyPage::OnOK();
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	pEco->_Noir		=	m_Noir	== 0 ? TRUE : FALSE ;
	pEco->_Fichier	=	m_Fichier ;
	pEco->_DensiteEtoiles	=	m_Etoiles ;
}
