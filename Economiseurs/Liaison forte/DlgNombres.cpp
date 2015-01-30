// DlgNombres.cpp : implementation file
//

#include "stdafx.h"
#include "liaisonForte.h"
#include "DlgNombres.h"

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
// CDlgNombres property page

IMPLEMENT_DYNCREATE(CDlgNombres, CPropertyPage)

CDlgNombres::CDlgNombres() : CPropertyPage(CDlgNombres::IDD)
{
	//{{AFX_DATA_INIT(CDlgNombres)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgNombres::~CDlgNombres()
{
}

void CDlgNombres::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNombres)
	DDX_Control(pDX, IDC_NB_ATOMES, m_NbAtomes);
	DDX_Control(pDX, IDC_MIN, m_Min);
	DDX_Control(pDX, IDC_MAX, m_Max);
	DDX_Control(pDX, IDC_LIENS, m_Liens);
	DDX_Control(pDX, IDC_EQUILIBRE, m_Equilibre);
	DDX_Control(pDX, IDC_AFFICHAGE, m_Affichage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNombres, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgNombres)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNombres message handlers

BOOL CDlgNombres::OnInitDialog() 
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

void CDlgNombres::PositionsSliders()
{
	// Positions des selections
	m_Min.SetSelection( (int)DIAMETRE_MAX_ATOME, (int)LongueurMax ) ;

	m_Max.SetSelection( (int)LongueurVoulue, (int)DISTANCE_MAX ) ;

	m_Equilibre.SetSelection( (int)DIAMETRE_MAX_ATOME, (int)LongueurMax ) ;

	m_Min.SetPos( (int)LongueurMin ) ;
	m_Max.SetPos( (int)LongueurMax ) ;
	m_Equilibre.SetPos( (int)LongueurVoulue ) ;

	m_Min.Invalidate(FALSE) ;
	m_Max.Invalidate(FALSE) ;
	m_Equilibre.Invalidate(FALSE) ;
}

void CDlgNombres::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl	*		pSlider	=	(CSliderCtrl*) pScrollBar ;

	switch( nSBCode )
		{
		case TB_BOTTOM :
		case TB_ENDTRACK :
		case TB_LINEDOWN :
		case TB_LINEUP :
		case TB_PAGEDOWN :
		case TB_PAGEUP :
		case TB_THUMBPOSITION :
		case TB_TOP :
			LongueurMin			=	m_Min.GetPos() ;
			LongueurMax			=	m_Max.GetPos() ;
			LongueurVoulue		=	m_Equilibre.GetPos() ;
			break ;

		case TB_THUMBTRACK :
			{
			double	Valeur	=	pSlider->GetPos() ;
			
			// Modifier la valeur en temps reel
			switch( GetWindowWord( (HWND)pScrollBar->m_hWnd, GWL_ID ))
				{
				case IDC_EQUILIBRE :
					if( Valeur > LongueurMax )
						Valeur = LongueurMax ;
					if (Valeur < DIAMETRE_MAX_ATOME )
						Valeur = DIAMETRE_MAX_ATOME ;

					LongueurVoulue	=	Valeur ;
					break ;
				case IDC_MIN :
					if ( Valeur > LongueurMax )
						Valeur	=	LongueurMax ;
					//if (Valeur > LongueurVoulue )
					//	Valeur = LongueurVoulue ;
					if ( Valeur < DIAMETRE_MAX_ATOME )
						Valeur = DIAMETRE_MAX_ATOME ;

					LongueurMin	=	Valeur ;
					break ;

				case IDC_MAX :
					if ( Valeur < LongueurVoulue )
						Valeur	=	LongueurVoulue ;

					if ( Valeur < LongueurMin )
						Valeur	=	LongueurMin ;

					if ( Valeur > DISTANCE_MAX )
						Valeur = DISTANCE_MAX ;

					LongueurMax	=	Valeur ;
					break ;

				default :
					return ;
				}

			pSlider->SetPos( (int)Valeur) ;
			}
		}

	PositionsSliders() ;
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgNombres::OnOK()
	{
	LongueurMin	=	m_Min.GetPos() ;
	LongueurMax	=	m_Max.GetPos() ;
	LongueurVoulue	=	m_Equilibre.GetPos() ;

	NbAtomes			=	m_NbAtomes.GetPos() ;
	NbMaxLiensParAtome	=	m_Liens.GetPos() ;
	ImagesSecondes		=	m_Affichage.GetPos() ;

	CPropertyPage::OnOK() ;
	}