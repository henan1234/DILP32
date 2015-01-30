// Page1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Page1.h"
#include <registrationKey.h>
#include <Dib.h>
#include <DibSurface.h>
#include <DibPal.h>
#include <RectAffichage.h>

#include "ecogravitation.h"
#pragma warning( disable : 4711 )

#pragma optimize ( "sg", on )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define	NB_IMAGES	50


/////////////////////////////////////////////////////////////////////////////
// CPage1 property page

IMPLEMENT_DYNCREATE(CPage1, CPropertyPage)

CPage1::CPage1() : CPropertyPage(CPage1::IDD)
{
	//{{AFX_DATA_INIT(CPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_IMPORTANT ) ;

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CPage1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_SAUVER, OnSauver)
	ON_BN_CLICKED(IDC_DEFAUT, OnDefaut)
	ON_BN_CLICKED(IDC_CHARGER, OnCharger)
	ON_BN_CLICKED(IDC_INTERNET, OnInternet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage1 message handlers
#pragma optimize ( "sg", off )



void CPage1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDIB	Image ;
	CRect R ;
	GetClientRect( R ) ;
	Image.Load( IDR_ESPACE_FOND ) ;
	CDIBPal	Palette ;
	Palette.Create( &Image ) ;

	dc.SelectPalette( &Palette, FALSE ) ;
	dc.RealizePalette() ;

	dc.PatBlt( R.left, R.top, R.Width(), R.Height(), BLACKNESS ) ;
	Image.Draw( &dc, R.right - Image.GetWidth(), 0 ) ;

	R.DeflateRect( 16, 16 ) ;

	dc.SetTextColor( RGB( 255, 0, 0 )) ;
	dc.SetBkMode( TRANSPARENT ) ;
	CFont Font ;
	Font.CreateFont( 48, 0, 
				0, 0, FW_BOLD, 
				FALSE, FALSE, FALSE, 
				ANSI_CHARSET,
				OUT_TT_PRECIS, 
				CLIP_TT_ALWAYS,
				PROOF_QUALITY, 
				VARIABLE_PITCH | FF_DONTCARE,
				"Arial" );
	CFont* pOld	=	dc.SelectObject( &Font ) ;
	dc.DrawText( "Gravitation 5.0", R, DT_LEFT | DT_TOP ) ;
	dc.SelectObject( pOld ) ;
	Font.DeleteObject() ;

	dc.SelectStockObject( ANSI_VAR_FONT ) ;
	dc.SetTextColor( RGB( 255, 255, 0 )) ;
	R.top += 50 ;
	R.right -= 100 ;

	CRegistrationKey*	pKey = CRegistrationKey::GetKey() ;

	CString Shareware ;

	if ( pKey->IsLocked())
	Shareware = "This is a shareware program.\r\nYou can freely test it and distribute it.\r\n"
					"If you decide to keep it, you must get the registered version.\r\n"
					"The registered version will let you tune all the parameters.\r\n" ;
	
	CString Message =
			"Copyright (c) Lucien PILLONI\r\n\r\n"
			"This program simulates the universal gravity among random star systems.\r\n"
			"It uses the real newtonnian equations to compute planets motion.\r\n"
			"You can fine tune all physical and display parameters and create your own universe\r\n"
			+ Shareware
			+ "\r\nYour screen must display at least 256 colors\r\n"
			+ "\r\nVisit the Gravitation web site for more informations and help about Gravitation.\r\n";
		
	dc.DrawText( Message, R, DT_LEFT | DT_TOP | DT_WORDBREAK ) ;
}




void CPage1::OnSauver() 
{
	CString	Filter ;
	Filter.LoadString( IDS_FILTRE_FICHIER ) ;

	CFileDialog Dlg( FALSE, ".Gravitation", "*.Gravitation",
					 OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
					 Filter, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		// Charger tous les parametres dans toutes les pages
		AvertitPages( TRUE ) ;
		
		// Enregistrer les parametres
		CEcoGravitation * pEconomiseur =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
		pEconomiseur->SaveFile( Dlg.GetPathName()) ;
		}
}

void CPage1::OnDefaut() 
{
	// Enregistrer les parametres
	CEcoGravitation * pEconomiseur =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	pEconomiseur->DefaultParameters() ;

	// Charger tous les parametres dans toutes les pages
	AvertitPages( FALSE ) ;
}

void CPage1::OnCharger() 
{
	CString	Filter ;
	Filter.LoadString( IDS_FILTRE_FICHIER ) ;

	CFileDialog Dlg( TRUE, ".Gravitation", "*.Gravitation",
					 OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
					 Filter, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		// Enregistrer les parametres
		CEcoGravitation * pEconomiseur =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
		pEconomiseur->LoadFile( Dlg.GetPathName()) ;

		// Charger tous les parametres dans toutes les pages
		AvertitPages( FALSE ) ;
		}
}

void CPage1::AvertitPages(BOOL Ecriture)
{
	CPropertySheet	*	pParent	=	(CPropertySheet*)GetParent() ;

	const int NbPages	=	pParent->GetPageCount() ;

	for ( int i = 0; i < NbPages; i++)
		{
		CPropertyPage * pPage = pParent->GetPage(i) ;

		// Demander a la page de lire ses parametres et les stocker dans l'econimiseur
		// Attention ! Elle n'a peut etre pas encore ete creee
		if ( IsWindow( pPage->m_hWnd ))
			pPage->SendMessage( WM_USER_PARAMETERS, Ecriture, 0 ) ;
		}
}

BOOL CPage1::OnSetActive() 
{
	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	if ( pKey->IsLocked() )
		{
		GetDlgItem( IDC_SAUVER )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_CHARGER )->EnableWindow( FALSE ) ;
		GetDlgItem( IDC_DEFAUT )->EnableWindow( FALSE ) ;
		}
	else
		{
		GetDlgItem( IDC_SAUVER )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_CHARGER )->EnableWindow( TRUE ) ;
		GetDlgItem( IDC_DEFAUT )->EnableWindow( TRUE ) ;
		}
	return CPropertyPage::OnSetActive();
}

BOOL CPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString Message ;
	Message.Format( "%d/%d/%d", (int)ANNEE_VERSION, (int)MOIS_VERSION, (int)JOUR_VERSION ) ;

	SetDlgItemText( IDC_COMPILATION_DATE, Message ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPage1::OnInternet() 
{
	char Directory[_MAX_PATH] ;

	GetCurrentDirectory( sizeof( Directory ), Directory ) ;
	ShellExecute( NULL, "open", "http://members.tripod.com/~gravitation_saver",
				  NULL, Directory, SW_SHOW ) ;
}



