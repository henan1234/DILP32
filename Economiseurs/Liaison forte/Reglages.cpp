// Reglages.cpp : implementation file
//

#include "stdafx.h"
#include "liaisonForte.h"
#include "Reglages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int	NbLiens	;
extern int	NbAtomes;
extern double	LongueurVoulue	;
extern double	LongueurMax		;
extern double	LongueurMin		;
extern double	Amortissement	 ;
extern double	Agitation		 ;
extern double	Intensite		 ;
extern int		NbMaxLiensParAtome ;
extern double	Repulsion ;
extern COLORREF	CouleurFond ;
extern COLORREF	CouleurLien ;
extern COLORREF	AtomeLibre ;
extern COLORREF	AtomeSature ;
extern DWORD	ImagesSecondes ;


/////////////////////////////////////////////////////////////////////////////
// CReglages property page

IMPLEMENT_DYNCREATE(CReglages, CPropertyPage)

CReglages::CReglages() : CPropertyPage(CReglages::IDD)
{
	//{{AFX_DATA_INIT(CReglages)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CReglages::~CReglages()
{
}

void CReglages::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReglages)
	DDX_Control(pDX, IDC_NB_ATOMES, m_NbAtomes);
	DDX_Control(pDX, IDC_MIN, m_Min);
	DDX_Control(pDX, IDC_MAX, m_Max);
	DDX_Control(pDX, IDC_LIENS, m_Liens);
	DDX_Control(pDX, IDC_EQUILIBRE, m_Equilibre);
	DDX_Control(pDX, IDC_AFFICHAGE, m_Affichage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReglages, CPropertyPage)
	//{{AFX_MSG_MAP(CReglages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReglages message handlers

BOOL CReglages::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Nombre d'atomes
	m_NbAtomes.SetRange( 2, NB_MAX_ATOMES ) ;
	m_NbAtomes.SetPos( NbAtomes ) ;

	// Nb max de liens par atomes
	m_Liens.SetRange( 2, NB_MAX_LIENS_PAR_ATOME ) ;
	m_Liens.SetPos( NbMaxLiensParAtome ) ;
	
	// Distances
	m_Min.SetRange( (int)DIAMETRE_MAX_ATOME, (int)DISTANCE_MAX ) ;
	m_Max.SetRange( (int)DIAMETRE_MAX_ATOME, (int)DISTANCE_MAX ) ;
	m_Equilibre.SetRange( (int)DIAMETRE_MAX_ATOME, (int)DISTANCE_MAX ) ;
	PositionsSliders() ;

	// Nb images par seconde
	m_Affichage.SetRange( 15, 30 ) ;
	m_Affichage.SetPos( ImagesSecondes ) ;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReglages::PositionsSliders()
{
	// Positions des selections
	m_Min.SetSelection( (int)DIAMETRE_MAX_ATOME, (int)LongueurMax ) ;
	m_Max.SetSelection( (int)LongueurVoulue, (int)DISTANCE_MAX ) ;
	m_Equilibre.SetSelection( (int)DIAMETRE_MAX_ATOME, (int)LongueurMax ) ;

	m_Min.SetPos( (int)LongueurMin ) ;
	m_Max.SetPos( (int)LongueurMax ) ;
	m_Equilibre.SetPos( (int)LongueurVoulue ) ;

}
