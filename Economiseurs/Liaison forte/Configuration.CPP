// Configuration.cpp : implementation file
//

#include "..\economiseur generique\stdafx.h"
#include "resource.h"
#include "liaisonforte.h"
#include "Configuration.h"
#include <RegistrationKey.h>

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
// CConfiguration property page

IMPLEMENT_DYNCREATE(CConfiguration, CPropertyPage)

CConfiguration::CConfiguration() : CPropertyPage(CConfiguration::IDD)
{
	//{{AFX_DATA_INIT(CConfiguration)
	m_Agitation = 0.0;
	m_Amortissement = 0.0;
	m_Atomes = 0;
	m_Distance = 0;
	m_Intensite = 0.0;
	m_Creation = 0.0;
	m_Max = 0.0;
	m_NbMaxLiens = 0;
	m_Repulsion = 0.0;
	//}}AFX_DATA_INIT
}

CConfiguration::~CConfiguration()
{
}

void CConfiguration::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfiguration)
	DDX_Control(pDX, IDC_SPIN2, m_SpinLiens);
	DDX_Control(pDX, IDC_NB_IMAGES, m_ImagesSecondes);
	DDX_Control(pDX, IDC_SPIN1, m_SpinAtomes);
	DDX_Text(pDX, IDC_AGITATION, Agitation);
	DDX_Text(pDX, IDC_AMORTISSEMENT, Amortissement);
	DDX_Text(pDX, IDC_ATOMES, NbAtomes);
	DDX_Text(pDX, IDC_DISTANCE, LongueurVoulue);
	DDX_Text(pDX, IDC_INTENSITE, Intensite);
	DDX_Text(pDX, IDC_CREATION, LongueurMin);
	DDX_Text(pDX, IDC_MAX, LongueurMax);
	DDX_Text(pDX, IDC_LIENS, NbMaxLiensParAtome );
	DDX_Text(pDX, IDC_REPULSION, Repulsion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfiguration, CPropertyPage)
	//{{AFX_MSG_MAP(CConfiguration)
	ON_BN_CLICKED(IDC_COULEUR, OnCouleur)
	ON_BN_CLICKED(IDC_COULEUR_LIENS, OnCouleurLiens)
	ON_BN_CLICKED(IDC_COULEUR_LIBRE, OnCouleurLibre)
	ON_BN_CLICKED(IDC_COULEUR_SATURE, OnCouleurSature)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfiguration message handlers

BOOL CConfiguration::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_SpinAtomes.SetRange( 1, NB_MAX_ATOMES ) ;
	m_SpinAtomes.SetPos( NbAtomes ) ;
	

	m_SpinLiens.SetRange( 2, NB_MAX_LIENS_PAR_ATOME ) ;
	m_SpinLiens.SetPos( NbMaxLiensParAtome ) ;

	m_ImagesSecondes.SetRange( 1, 25 ) ;
	m_ImagesSecondes.SetPos( ImagesSecondes ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfiguration::OnCouleur() 
{
	CColorDialog	Dlg( CouleurFond, CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CouleurFond = Dlg.GetColor() ;
		}
}

void CConfiguration::OnCouleurLiens() 
{
	CColorDialog	Dlg( CouleurLien, CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CouleurLien = Dlg.GetColor() ;
		}
}

void CConfiguration::OnCouleurLibre() 
{
	CColorDialog	Dlg( AtomeLibre, CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		AtomeLibre = Dlg.GetColor() ;
		}
}

void CConfiguration::OnCouleurSature() 
{
	CColorDialog	Dlg( AtomeSature, CC_ANYCOLOR | CC_FULLOPEN | CC_RGBINIT, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		AtomeSature = Dlg.GetColor() ;
		}
}

HBRUSH CConfiguration::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr =	CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if ( nCtlColor	== CTLCOLOR_BTN )
		{
		if ( pWnd->m_hWnd	=	::GetDlgItem( m_hWnd, IDC_COULEUR ))
			{
			DeleteObject( hbr ) ;
			hbr	=	CreateSolidBrush( CouleurFond ) ;
			pDC->SetTextColor( CouleurFond ) ;
			}
		else
		if ( pWnd->m_hWnd	=	::GetDlgItem( m_hWnd, IDC_COULEUR_LIENS ))
			{
			DeleteObject( hbr ) ;
			hbr	=	CreateSolidBrush( CouleurLien ) ;
			pDC->SetBkColor( CouleurLien ) ;
			}
		else
		if ( pWnd->m_hWnd	=	::GetDlgItem( m_hWnd, IDC_COULEUR_LIBRE ))
			{
			DeleteObject( hbr ) ;
			hbr	=	CreateSolidBrush( AtomeLibre ) ;
			pDC->SetBkColor( AtomeLibre ) ;
			}
		else
		if ( pWnd->m_hWnd	=	::GetDlgItem( m_hWnd, IDC_COULEUR_SATURE ))
			{
			DeleteObject( hbr ) ;
			hbr	=	CreateSolidBrush( AtomeSature ) ;
			pDC->SetBkColor( AtomeSature ) ;
			}
		}
		
	
	return hbr;
}

void CConfiguration::OnOK() 
{
	CPropertyPage::OnOK();

	ImagesSecondes	=	m_ImagesSecondes.GetPos() ;
}

BOOL CConfiguration::OnSetActive() 
{
	CRegistrationKey	*	pKey	=	CRegistrationKey::GetKey() ;	

	if ( pKey->IsLocked())
		{
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_AMORTISSEMENT ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_INTENSITE ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_AGITATION ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_REPULSION ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NB_IMAGES ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_LIENS ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_LIBRE ), FALSE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_SATURE ), FALSE ) ;
		}
	else
		{
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_AMORTISSEMENT ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_INTENSITE ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_AGITATION ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_REPULSION ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_NB_IMAGES ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_LIENS ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_LIBRE ), TRUE ) ;
		::EnableWindow( ::GetDlgItem( m_hWnd, IDC_COULEUR_SATURE ), TRUE ) ;
		}
	
	return CPropertyPage::OnSetActive();
}

