// PagesParametres.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <io.h>
#include <RegistrationKey.h>
#include <Dib.h>
#include <DibSurface.h>
#include <DibPal.h>

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"
#include "EcoGravitation.h"
#include "PagesParametres.h"
#include "SharewareMessageWnd.h"

#include "options.h"

#pragma warning( disable : 4711 )

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
	{
	UINT	IdValue ;
	int		Special ;
	}
	T_INT_SPECIAL ;

#define	ID_NB_MIN				0
#define	ID_NB_MAX				1
#define ID_NB_INIT				2
#define ID_3D					3
#define	ID_G					4
#define	ID_IMAGES_SECONDE		5
#define ID_DENSITE_ETOILES		6
#define ID_AFFICHE_REPERE		7
#define ID_EFFACE_TRAJECTOIRES	8
#define ID_CHANGE_RESOLUTION	9
#define ID_VITESSE_LIBERATION	10
#define ID_COEFF_TEMPS			11
#define ID_COEFF_DISTANCE		12
#define ID_COEFF_RAYON			13
#define ID_VITESSE_COLISION		14
#define ID_TRAVELING			15
#define ID_ZOOM					16
#define ID_CREATION				17
#define ID_FICHIER				18
#define ID_MASSE_0				19
#define ID_MASSE_1				20
#define ID_MASSE_2				21
#define ID_MASSE_3				22
#define ID_MASSE_4				23
#define ID_MASSE_5				24
#define ID_MASSE_6				25
#define ID_MASSE_7				26
#define ID_VENT_SOLAIRE			27
#define ID_MAX_POUSSIERE		28
#define ID_TAILLE_POUSSIERE		29
#define ID_DISPERSION_POUSSIERE	30
#define ID_CREATION_COMETE		31
#define ID_SECTION_NUMBERS		32
#define ID_SECTION_CREATION		33
#define ID_SECTION_PHYSIQUE		34
#define ID_SECTION_MASSES		35
#define ID_SECTION_COMETES		36
#define	ID_SECTION_AFFICHAGE	37
#define ID_TITRE				38
#define	ID_DUST_LIFE_LENGTH		39
#define	ID_SECTION_CAMERA		40
#define ID_AFFICHE_INFOS		41
#define ID_PLUSDETOILE			42
#define ID_USE_SKIN_FILE		43
#define ID_SKIN_FILE			44

HTREEITEM	hGItem = 0 ;
UINT		GIdLabel ;
int			GIntMin ;
int			GIntMax ;

COption *	pGOption ;
CPagesParametres::CALL_BACK_FLOTTANT GFlottantCallBack ;

/////////////////////////////////////////////////////////////////////////////
// CPagesParametres property page

IMPLEMENT_DYNCREATE(CPagesParametres, CPropertyPage)

void	fctG( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;

	if ( Val == 0.0 )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_G ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}


void	fctTemps( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;

	if ( Val == 0.0 )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_TEMPS ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}


void	fctRayon( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;

	if ( Val == 0.0 || Val > 2.0 )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_RAYON ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void fctColision( CPagesParametres *  )
	{
	}

void fctTraveling( CPagesParametres *  )
	{
	}
void fctZoom( CPagesParametres *  )
	{
	}

void fctDistance( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;

	if ( Val == 0.0 )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_DISTANCE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse0( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val >= COptions::MasseMax(1))
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}


void	fctMasse1( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax(0 ) || Val >= COptions::MasseMax(2) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse2( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax( 1 ) || Val >= COptions::MasseMax(3) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse3( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax( 2 ) || Val >= COptions::MasseMax(4) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse4( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax( 3) || Val >= COptions::MasseMax(5) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse5( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax( 4 ) || Val >= COptions::MasseMax(6) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
		
	}

void	fctMasse6( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax( 5 ) || Val >= COptions::MasseMax(7) )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}

void	fctMasse7( CPagesParametres * pPage )
	{
	CString	Text	;
	pPage->m_FlottantEdit.GetWindowText(Text) ;

	FLOTTANT Val	=	atof( Text ) ;
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	if ( Val <= COptions::MasseMax(6)  )
		{
		CString Text ;
		Text.LoadString( IDS_ERREUR_MASSE ) ;
		MessageBeep( MB_ICONSTOP ) ;
		pPage->MessageBox( Text, NULL, MB_ICONSTOP | MB_OK ) ;
		pPage->m_FlottantEdit.SetFocus() ;
		pPage->m_Tree.Select( hGItem, TVGN_CARET ) ;
		}
	}


CPagesParametres::CPagesParametres() : CPropertyPage(CPagesParametres::IDD)
{
	//{{AFX_DATA_INIT(CPagesParametres)
	//}}AFX_DATA_INIT
	m_psp.dwFlags |= PSP_USEICONID ;
	m_psp.pszIcon	=	MAKEINTRESOURCE( IDI_PARAMETRES ) ;

	pGOption		=	0 ;
}

CPagesParametres::~CPagesParametres()
{
}

void CPagesParametres::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPagesParametres)
	DDX_Control(pDX, IDC_FICHIER_BROWSE, m_FichierBrowse);
	DDX_Control(pDX, IDC_FICHIER_EDIT, m_FichierEdit);
	DDX_Control(pDX, IDC_CHOIX, m_Choix);
	DDX_Control(pDX, IDC_FLOTTANT_EDIT, m_FlottantEdit);
	DDX_Control(pDX, IDC_FLOTTANT_UNITE, m_FlottantUnite);
	DDX_Control(pDX, IDC_BOOLCHECK, m_BoolCheck);
	DDX_Control(pDX, IDC_INT_CURRENT_VALUE, m_IntCurrentValue);
	DDX_Control(pDX, IDC_INT_NUMBER, m_IntNumber);
	DDX_Control(pDX, IDC_TIP, m_Tip);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagesParametres, CPropertyPage)
	//{{AFX_MSG_MAP(CPagesParametres)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BOOLCHECK, OnBoolcheck)
	ON_EN_KILLFOCUS(IDC_FLOTTANT_EDIT, OnKillfocusFlottantEdit)
	ON_EN_CHANGE(IDC_FLOTTANT_EDIT, OnChangeFlottantEdit)
	ON_CBN_SELCHANGE(IDC_CHOIX, OnSelchangeChoix)
	ON_BN_CLICKED(IDC_FICHIER_BROWSE, OnFichierBrowse)
	//}}AFX_MSG_MAP
	ON_MESSAGE( WM_USER_PARAMETERS, OnUserParameters )

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagesParametres message handlers

HBRUSH CPagesParametres::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr ;
	if ( nCtlColor == CTLCOLOR_STATIC  )
		{
		if ( GetWindowLong( *pWnd, GWL_ID ) == IDC_TIP )
			{
			pDC->SetTextColor(RGB(0,0,0)) ;

			
			static HBRUSH hBrush	= NULL ;
			static COLORREF	Couleur = 0 ;
			if ( hBrush == NULL )
				{
				HDC	hDC	=	CreateDC( "display", 0, 0, 0 ) ;

				if ( (GetDeviceCaps( hDC, BITSPIXEL ) * GetDeviceCaps( hDC, PLANES )) > 8 )
					{
					hBrush			= CreateSolidBrush( RGB( 255, 255, 192 )) ;
					Couleur			= RGB( 255, 255, 192 ) ;
					}
				else
					{
					hBrush			= CreateSolidBrush( RGB( 255, 255, 0 )) ;
					Couleur			= RGB(255,255,0) ; 	
					}

				DeleteDC( hDC) ;
				}

			pDC->SetBkColor( Couleur ) ;
			hbr	=	hBrush ;
			}
		else
			hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
		}
	else
			hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);


	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// RemplitNombres
// Remplit la categorie Nombre de l'arbre:
//	Nb min de corps
//	Nb max de corps
//	Nb initial de corps
///////////////////////////////////////////////////////////////////////////////
void	CPagesParametres::RemplitNombres()
	{
	CString	Label ;
	Label.LoadString( IDS_NUMBERS ) ;

	const int	Icon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_NOMBRES ))) ;
	HTREEITEM	hRoot	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
											   Label, Icon, Icon, 0, 0, ID_SECTION_NUMBERS, TVI_ROOT, TVI_LAST ) ;

	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;

	AddItem( hRoot, ID_NB_INIT, IDS_INIT_NUMBER, COptions::NbInitCorps(), IDI_INIT ) ;
	AddItem( hRoot, ID_NB_MAX, IDS_MAX_NUMBER, COptions::NbMaxCorps(), IDI_MAX ) ;
	AddItem( hRoot, ID_NB_MIN, IDS_MIN_NUMBER, COptions::NbMinCorps(), IDI_MIN ) ;
	AddBoolItem( hRoot, ID_PLUSDETOILE, IDS_PLUSDETOILE, COptions::ReInitSiPlusDEtoile(), IDI_ETOILE ) ;

	const int	IconCreation	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_CREATION ))) ;
	Label.LoadString( IDS_CREATION_METHOD ) ;
	HTREEITEM	hRootCreation	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
											   Label, IconCreation, IconCreation, 0, 0, ID_SECTION_CREATION, TVI_ROOT, TVI_LAST ) ;
	AddItemChoix( hRootCreation, ID_CREATION, IDS_CREATION, IDS_CREATION_CHOIX, COptions::Depart(), IDI_CREATION ) ;
	AddItemFichier( hRootCreation, ID_FICHIER, IDS_FICHIER, COptions::FichierInit(), IDI_FICHIER ) ;

	m_Tree.Expand( hRootCreation, TVE_EXPAND ) ;
	m_Tree.Expand( hRoot, TVE_EXPAND ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// RemplitPhysique
// Remplit la categorie Physique de l'arbre
///////////////////////////////////////////////////////////////////////////////
void	CPagesParametres::RemplitPhysique()
	{
	CString	Label ;
	Label.LoadString( IDS_PHYS ) ;

	const int	Icon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_PHYSIQUE ))) ;

	HTREEITEM	hRoot	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
											   Label, Icon, Icon, 0, 0, ID_SECTION_PHYSIQUE, TVI_ROOT, TVI_LAST ) ;
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;

	AddBoolItem( hRoot, ID_3D, IDS_3D2D, COptions::Modele3D(), IDI_3D ) ;
	AddFlottantItem( hRoot, ID_G, IDS_G_CST, COptions::G(), IDI_G ) ;
	AddFlottantItem( hRoot, ID_COEFF_TEMPS, IDS_COEFF_TEMPS, COptions::TimeMult(), IDI_TEMPS ) ;
	AddFlottantItem( hRoot, ID_COEFF_DISTANCE, IDS_COEF_DISTANCE, COptions::DistMult(), IDI_DISTANCE ) ;
	AddFlottantItem( hRoot, ID_COEFF_RAYON, IDS_COEF_RAYON, COptions::CoeffRayon(), IDI_RAYON ) ;
	AddFlottantItem( hRoot, ID_VITESSE_COLISION, IDS_VITESSE_COLISION, COptions::DeltaVMax(), IDI_DELTAVMAX ) ;
	AddItem( hRoot, ID_VITESSE_LIBERATION, IDS_VITESSE_LIBERATION, COptions::CoeffLiberation(), IDI_LIBERATION ) ;
	
	RemplitMasses( hRoot ) ;
	RemplitCometes( hRoot ) ;

	m_Tree.Expand( hRoot, TVE_EXPAND ) ;
}


///////////////////////////////////////////////////////////////////////////////
// RemplitAffichage
//	Remplit la branche des options d'affichage
///////////////////////////////////////////////////////////////////////////////
void	CPagesParametres::RemplitAffichage()
	{
	CString	Label ;
	Label.LoadString( IDS_AFFICHAGE ) ;

	const int	Icon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_AFFICHAGE ))) ;

	HTREEITEM	hRoot	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
											   Label, Icon, Icon, 0, 0, ID_SECTION_AFFICHAGE, TVI_ROOT, TVI_LAST ) ;
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;

	AddBoolItem( hRoot, ID_USE_SKIN_FILE, IDS_USE_SKIN_FILE, COptions::UseSkinFile(), IDI_SKINFILE ) ;
	AddItemFichier( hRoot, ID_SKIN_FILE, IDS_SKIN_FILE, COptions::SkinFile(), IDI_SKINFILE ) ;

	AddItem( hRoot, ID_DENSITE_ETOILES, IDS_DENSITEETOILES, COptions::DensiteEtoiles(), IDI_ETOILES ) ;
	AddBoolItem( hRoot, ID_AFFICHE_REPERE, IDS_AFFICHE_REPERE, COptions::AfficherRepere(), IDI_REPERE ) ;
	AddBoolItem( hRoot, ID_CHANGE_RESOLUTION, IDS_CHANGER_RESOLUTION, COptions::ChangerResolution(), IDI_AFFICHAGE ) ;
	AddBoolItem( hRoot, ID_AFFICHE_INFOS, IDS_AFFICHE_INFOS, COptions::AfficherInfos(), IDI_AFFICHAGE ) ;

	
	Label.LoadString( IDS_CAMERA ) ;
	const int	IconeCamera	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_CAMERA ))) ;
	HTREEITEM hItemCamera	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
													Label, IconeCamera, IconeCamera, 0, 0, ID_SECTION_CAMERA, hRoot, TVI_LAST ) ;

	RemplitCamera( hItemCamera ) ;
	m_Tree.Expand( hRoot, TVE_EXPAND ) ;
	}



BOOL CPagesParametres::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	_Shareware.SubclassDlgItem( IDC_SHAREWARE, this ) ;

	RemplitArbre() ;

	return TRUE;
}


void	CPagesParametres::AddItem( HTREEITEM hParent, UINT ParamNumber, UINT IdLabel, int Valeur, UINT Icon ) 
	{
	CString	Label ;
	Label.Format( IdLabel, Valeur ) ;
	const int	NoIcon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( Icon ))) ;

	TV_INSERTSTRUCT Item ;
	Item.hParent	=	hParent ;
	Item.hInsertAfter	=	TVI_LAST ;
	Item.item.mask	=	TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ; 
	Item.item.hItem	=	hParent ;
    Item.item.state	=	0 ;
	Item.item.stateMask= 0 ;
	Item.item.pszText=	Label.GetBuffer(1) ;
    Item.item.cchTextMax = Label.GetLength() + 1 ;
	Item.item.iImage = NoIcon ;
	Item.item.iSelectedImage = NoIcon ;
	Item.item.lParam = ParamNumber ;
	m_Tree.InsertItem(	&Item ); ;
	}

///////////////////////////////////////////////////////////////////////////////
// AddFlottantItem
//	Ajoute un ITEM flottant a l'arbre
///////////////////////////////////////////////////////////////////////////////
void	CPagesParametres::AddFlottantItem( HTREEITEM hParent, UINT ParamNumber, UINT IdLabel, FLOTTANT Valeur, UINT Icon ) 
	{
	CString	Label ;
	Label.Format( IdLabel, Valeur ) ;

	const int	NoIcon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( Icon ))) ;

	TV_INSERTSTRUCT Item ;
	Item.hParent	=	hParent ;
	Item.hInsertAfter	=	TVI_LAST ;
	Item.item.mask	=	TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ; 
	Item.item.hItem	=	hParent ;
    Item.item.state	=	0 ;
	Item.item.stateMask= 0 ;
	Item.item.pszText=	Label.GetBuffer(1) ;
    Item.item.cchTextMax = Label.GetLength() + 1 ;
	Item.item.iImage = NoIcon ;
	Item.item.iSelectedImage = NoIcon ;
	Item.item.lParam = ParamNumber ;
	m_Tree.InsertItem(	&Item ); ;
	}

void	CPagesParametres::AddItemFichier( HTREEITEM hParent, UINT ParamNumber, UINT IdLabel, const CString & Valeur, UINT Icon ) 
	{
	CString	Label ;
	Label.Format( IdLabel, (const char *)Valeur ) ;

	const int	NoIcon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( Icon ))) ;

	TV_INSERTSTRUCT Item ;
	Item.hParent	=	hParent ;
	Item.hInsertAfter	=	TVI_LAST ;
	Item.item.mask	=	TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ; 
	Item.item.hItem	=	hParent ;
    Item.item.state	=	0 ;
	Item.item.stateMask= 0 ;
	Item.item.pszText=	Label.GetBuffer(1) ;
    Item.item.cchTextMax = Label.GetLength() + 1 ;
	Item.item.iImage = NoIcon ;
	Item.item.iSelectedImage = NoIcon ;
	Item.item.lParam = ParamNumber ;
	m_Tree.InsertItem(	&Item ); ;
	}

CString	ExtraitMorceau( const CString & Chaine, int Morceau )
	{
	CString	Ch( Chaine ) ;
	int No	=	0 ;
	int	IndiceDebut	=	0 ;

	while ( No	< Morceau && IndiceDebut < Ch.GetLength() )
		{
		if ( Ch[IndiceDebut] == '|' )
			No ++ ;
		IndiceDebut ++ ;
		}

	Ch	=	Ch.Mid( IndiceDebut ++ ) ;
	int	IndiceFin	=	Ch.Find( "|" ) ;
	return Ch.Left( IndiceFin ) ;
	}

void	CPagesParametres::AddItemChoix( HTREEITEM hParent, UINT ParamNumber, UINT IdLabel, UINT IdChoix, int Valeur, UINT Icon ) 
	{
	CString	Labels ;
	Labels.LoadString( IdChoix ) ;
	CString Morceau	=	ExtraitMorceau( Labels, Valeur ) ;

	CString Label ;
	Label.Format( IdLabel, (const char *)Morceau ) ;

	const int	NoIcon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( Icon ))) ;

	TV_INSERTSTRUCT Item ;
	Item.hParent	=	hParent ;
	Item.hInsertAfter	=	TVI_LAST ;
	Item.item.mask	=	TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ; 
	Item.item.hItem	=	hParent ;
    Item.item.state	=	0 ;
	Item.item.stateMask= 0 ;
	Item.item.pszText=	Label.GetBuffer(1) ;
    Item.item.cchTextMax = Label.GetLength() + 1 ;
	Item.item.iImage = NoIcon ;
	Item.item.iSelectedImage = NoIcon ;
	Item.item.lParam = ParamNumber ;
	m_Tree.InsertItem(	&Item ); ;
	}

void	CPagesParametres::AddBoolItem( HTREEITEM hParent, UINT ParamNumber, UINT IdLabel, BOOL Valeur, UINT Icon ) 
	{
	CString IdOui, IdNon ;
	IdOui.LoadString( IDS_OUI ) ;
	IdNon.LoadString( IDS_NON ) ;
	CString	Label ;
	Label.Format( IdLabel, Valeur ? (const char *) IdOui : (const char *)IdNon ) ;

	const int	NoIcon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( Icon ))) ;

	TV_INSERTSTRUCT Item ;
	Item.hParent	=	hParent ;
	Item.hInsertAfter	=	TVI_LAST ;
	Item.item.mask	=	TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE ; 
	Item.item.hItem	=	hParent ;
    Item.item.state	=	0 ;
	Item.item.stateMask= 0 ;
	Item.item.pszText=	Label.GetBuffer(1) ;
    Item.item.cchTextMax = Label.GetLength() + 1 ;
	Item.item.iImage = NoIcon ;
	Item.item.iSelectedImage = NoIcon ;
	Item.item.lParam = ParamNumber ;
	m_Tree.InsertItem(	&Item ); ;
	}

void CPagesParametres::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	pGOption	=	0 ;

	HTREEITEM	hItem	=	m_Tree.GetNextItem(m_Tree.GetRootItem(), TVGN_CARET ) ;
	CString	Tip ;
	DWORD	Data = Data	=	m_Tree.GetItemData( hItem ) ;

	// affiche le tip correspondant
	Tip.LoadString( 5000 + Data ) ;
	m_Tip.SetWindowText( Tip ) ;

	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;

	switch( Data )
		{
		case ID_NB_MIN:
			SaisieIntIntervalle( hItem, IDS_MIN_NUMBER, &COptions::NbMinCorps(), 2, COptions::NbInitCorps() - 1 ) ;
			break ;

		case ID_NB_MAX:
			SaisieIntIntervalle( hItem, IDS_MAX_NUMBER,
								 &COptions::NbMaxCorps(), COptions::NbInitCorps()+1, NB_MAX_CORPS ) ;
			break ;

		case ID_NB_INIT :
			SaisieIntIntervalle( hItem, IDS_INIT_NUMBER,
								 &COptions::NbInitCorps(), COptions::NbMinCorps() + 1, COptions::NbMaxCorps() ) ;
			break ;

		case ID_PLUSDETOILE :
			SaisieBool( hItem, IDS_PLUSDETOILE, IDS_CHECK_PLUSDETOILE,
						&COptions::ReInitSiPlusDEtoile()) ;
			break ;

		case ID_IMAGES_SECONDE:
			SaisieIntIntervalle( hItem, IDS_IMAGE_SECONDE,
								 &COptions::NbImagesSeconde(), 15, 30 ) ;
			break ;

		case ID_DENSITE_ETOILES :
			SaisieIntIntervalle( hItem, IDS_DENSITE_ETOILES,
								 &COptions::DensiteEtoiles(), 0, 5000 ) ;
			break ;

		case ID_AFFICHE_REPERE :
			SaisieBool( hItem, IDS_AFFICHE_REPERE, IDS_CHECK_DISPLAY_CROSSHAIR, &COptions::AfficherRepere() ) ;
			break ;

		case ID_CHANGE_RESOLUTION :
			SaisieBool( hItem, IDS_CHANGER_RESOLUTION, IDS_CHECK_CHANGE_RESOLUTION, &COptions::ChangerResolution() ) ;
			break ;

		case ID_VITESSE_LIBERATION:
			SaisieIntIntervalle( hItem, IDS_VITESSE_LIBERATION,
								 &COptions::CoeffLiberation(), 1, 99 ) ;
			break ;

		case ID_3D :
			SaisieBool( hItem, IDS_3D2D, IDS_CHECK_3D2D, &COptions::Modele3D() ) ;
			break ;

		case ID_G :
			SaisieFlottant( hItem, IDS_G_CST, &COptions::G(), fctG ) ;
			break ;

		case ID_COEFF_TEMPS :
			SaisieFlottant( hItem, IDS_COEFF_TEMPS, &COptions::TimeMult(), fctTemps ) ;
			break ;

		case ID_COEFF_DISTANCE :
			SaisieFlottant( hItem, IDS_COEF_DISTANCE, &COptions::DistMult(), fctDistance ) ;
			break ;

		case ID_COEFF_RAYON :
			SaisieFlottant( hItem, IDS_COEF_RAYON, &COptions::CoeffRayon(), fctRayon ) ;
			break ;

		case ID_VITESSE_COLISION :
			SaisieFlottant( hItem, IDS_VITESSE_COLISION, &COptions::DeltaVMax(), fctColision ) ;
			break ;

		case ID_TRAVELING :
			SaisieFlottant( hItem, IDS_TRAVELING, &COptions::CoeffTraveling(), fctTraveling ) ;
			break ;

		case ID_ZOOM :
			SaisieFlottant( hItem, IDS_ZOOM, &COptions::ZoomMax(), fctZoom ) ;
			break ;

		case ID_CREATION :
			SaisieChoix( hItem, IDS_CREATION, IDS_CREATION_CHOIX, &COptions::Depart() ) ;
			break ;

		case ID_FICHIER :
			SaisieFichier( hItem, IDS_FICHIER, &COptions::FichierInit() ) ;
			break ;

		case ID_MASSE_0 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(0), fctMasse0 ) ;
			break ;

		case ID_MASSE_1 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(1), fctMasse1 ) ;
			break ;
		case ID_MASSE_2 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(2), fctMasse2 ) ;
			break ;
		case ID_MASSE_3 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(3), fctMasse3 ) ;
			break ;
		case ID_MASSE_4 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(4), fctMasse4 ) ;
			break ;
		case ID_MASSE_5 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(5), fctMasse5 ) ;
			break ;
		case ID_MASSE_6 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(6), fctMasse6 ) ;
			break ;
		case ID_MASSE_7 :
			SaisieFlottant( hItem, IDS_MASSE_ITEM, &COptions::MasseMax(7), fctMasse7 ) ;
			break ;

		case ID_VENT_SOLAIRE	:
			SaisieFlottant( hItem, IDS_VENTSOLAIRE, &COptions::VentSolaire(), 0 ) ;
			break ;
		case ID_MAX_POUSSIERE	:
			SaisieIntIntervalle( hItem, IDS_MAX_POUSSIERE, &COptions::NbMaxPoussieres(), 0, NB_MAX_POUSSIERES ) ;
			break ;

		case  ID_TAILLE_POUSSIERE:
			SaisieIntIntervalle( hItem, IDS_TAILLE_POUSSIERE, &COptions::TaillePoussieres(), 1,6 ) ;
			break ;

		case ID_CREATION_COMETE:
			SaisieIntIntervalle( hItem, IDS_CREATIONCOMETE, &COptions::CreationComete(), 2,5000 ) ;
			break ;

		case ID_DISPERSION_POUSSIERE:
			SaisieIntIntervalle( hItem, IDS_DISPERSION_POUSSIERE, &COptions::BruitPoussieres(), 1, 99 ) ;
			break ;

		case ID_DUST_LIFE_LENGTH :
			SaisieIntIntervalle( hItem, IDS_DUST_LIFE, &COptions::ViePoussieres(), 0, 20 ) ;
			break ;


		case ID_AFFICHE_INFOS :
			SaisieBool( hItem, IDS_AFFICHE_INFOS, IDS_CHECK_AFFICHE_INFOS, &COptions::AfficherInfos() ) ;
			break ;

		case ID_USE_SKIN_FILE :
			SaisieBool( hItem, IDS_USE_SKIN_FILE, IDS_CHECK_USE_SKIN_FILE, &COptions::UseSkinFile()) ;
			break ;

		case ID_SKIN_FILE :
			SaisieFichier( hItem, IDS_SKIN_FILE, &COptions::SkinFile()) ;
			break ;

		default :
			CacheControles() ;
			break ;
		}

	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	BOOL Cacher	= FALSE ;
		
	if ( pKey->IsLocked())
		{
		if ( pGOption )
			if ( ! pGOption->ModifiableShareware())
				Cacher = TRUE ;
		}

	if ( Cacher )
		{
		m_IntNumber.EnableWindow( FALSE ) ;
		m_IntCurrentValue.EnableWindow( FALSE ) ;
		m_BoolCheck.EnableWindow( FALSE ) ;
		m_FlottantEdit.EnableWindow( FALSE ) ;
		m_FlottantUnite.EnableWindow( FALSE ) ;
		m_Choix.EnableWindow( FALSE ) ;
		m_FichierEdit.EnableWindow( FALSE ) ;
		m_FichierBrowse.EnableWindow( FALSE ) ;
		_Shareware.ModifyStyle( WS_EX_TRANSPARENT, WS_EX_TOPMOST, SWP_NOSIZE | SWP_NOACTIVATE ) ;
		_Shareware.ShowWindow(SW_SHOW) ;
		_Shareware.BringWindowToTop() ;
		}
	else
		{
		_Shareware.ShowWindow( SW_HIDE ) ;

		m_IntNumber.EnableWindow( TRUE ) ;
		m_IntCurrentValue.EnableWindow( TRUE ) ;
		m_BoolCheck.EnableWindow( TRUE ) ;
		m_FlottantEdit.EnableWindow( TRUE ) ;
		m_FlottantUnite.EnableWindow( TRUE ) ;
		m_Choix.EnableWindow( TRUE ) ;
		m_FichierEdit.EnableWindow( TRUE ) ;
		m_FichierBrowse.EnableWindow( TRUE ) ;
		}


}

BOOL CPagesParametres::OnSetActive() 
{

	return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////////////////
// SaisieIntIntervalle
//	Saisie d'un entier dans un intervalle
///////////////////////////////////////////////////////////////////////////////
void CPagesParametres::SaisieIntIntervalle(HTREEITEM hIntItem, UINT IdLabel, COptionEntier * pValue, int Min, int Max )
{
	hGItem		=	hIntItem ;
	GIdLabel	=	IdLabel ;
	GIntMin		=	Min ;
	GIntMax		=	Max ;
	pGOption	=	pValue ;

	m_IntNumber.SetRange( Min, Max ) ;
	m_IntNumber.SetPos( *pValue ) ;

	CString		Text ;
	Text.Format("%d", (int)*pValue ) ;

	m_IntCurrentValue.SetWindowText( Text ) ;

	CacheControles() ;
	m_IntNumber.ShowWindow( SW_SHOW ) ;
	m_IntCurrentValue.ShowWindow( SW_SHOW ) ;
	_Shareware.BringWindowToTop() ;
}


///////////////////////////////////////////////////////////////////////////////
// SaisieIntIntervalle
//	Saisie d'un entier dans un intervalle
///////////////////////////////////////////////////////////////////////////////
void CPagesParametres::SaisieBool(HTREEITEM hIntItem, UINT IdLabel, UINT IdBtnLabel, COptionEntier * pValue )
{
	hGItem		=	hIntItem ;
	GIdLabel	=	IdLabel ;
	pGOption	=	pValue ;

	m_BoolCheck.SetCheck( (int)*pValue ) ;

	CString	Label ;
	Label.LoadString( IdBtnLabel );
	m_BoolCheck.SetWindowText( Label ) ;

	CacheControles() ;
	m_BoolCheck.ShowWindow( SW_SHOW ) ;
	_Shareware.BringWindowToTop() ;
}

///////////////////////////////////////////////////////////////////////////////
// SaisieFlottant
//	Saisie d'un flottant
///////////////////////////////////////////////////////////////////////////////
void CPagesParametres::SaisieFlottant(HTREEITEM hIntItem, UINT IdLabel, COptionFlottant * pValue, CALL_BACK_FLOTTANT CallBack )
{
	hGItem				=	hIntItem ;
	GIdLabel			=	IdLabel ;
	GFlottantCallBack	=	CallBack ;
	pGOption			=	pValue ;

	CString	Val ;
	Val.Format( "%g", (double)*pValue ) ;
	m_FlottantEdit.SetWindowText( Val ) ;

	CacheControles() ;
	m_FlottantEdit.ShowWindow( SW_SHOW ) ;
	m_FlottantUnite.ShowWindow( SW_SHOW ) ;

	_Shareware.BringWindowToTop() ;
}

///////////////////////////////////////////////////////////////////////////////
// SaisieChoix
//	Saisie d'un entier dans un intervalle
///////////////////////////////////////////////////////////////////////////////
void CPagesParametres::SaisieChoix(HTREEITEM hIntItem, UINT IdLabel, UINT IdChoix, COptionEntier * pValue )
{
	hGItem		=	hIntItem ;
	GIdLabel	=	IdLabel ;
	pGOption	=	pValue ;

	CString	Morceaux	;
	Morceaux.LoadString( IdChoix ) ;

	m_Choix.ResetContent() ;
	int	NoMorceau	=	0 ;
	while ( TRUE )
		{
		CString Morceau	=	ExtraitMorceau( Morceaux, NoMorceau) ;
		if ( Morceau.IsEmpty())
			break ;
		else
			{
			NoMorceau ++ ;
			m_Choix.AddString( Morceau ) ;
			}
		}
	
	m_Choix.SetCurSel( *pValue ) ;

	CacheControles() ;
	m_Choix.ShowWindow( SW_SHOW ) ;
	_Shareware.BringWindowToTop() ;
}

void CPagesParametres::SaisieFichier(HTREEITEM hIntItem, UINT IdLabel, COptionChaine * pValue  )
{
	hGItem		=	hIntItem ;
	GIdLabel	=	IdLabel ;
	pGOption	=	pValue ;

	m_FichierEdit.SetWindowText( *(COptionChaine*)pValue ) ;

	CacheControles() ;
	m_FichierEdit.ShowWindow( SW_SHOW ) ;
	m_FichierBrowse.ShowWindow( SW_SHOW ) ;
}

void CPagesParametres::CacheControles()
{
	m_IntNumber.ShowWindow( SW_HIDE ) ;
	m_IntCurrentValue.ShowWindow( SW_HIDE ) ;

	m_BoolCheck.ShowWindow( SW_HIDE ) ;

	m_FlottantEdit.ShowWindow( SW_HIDE ) ;
	m_FlottantUnite.ShowWindow( SW_HIDE ) ;

	m_Choix.ShowWindow( SW_HIDE ) ;
	
	m_FichierEdit.ShowWindow( SW_HIDE ) ;
	m_FichierBrowse.ShowWindow( SW_HIDE ) ;
}

void CPagesParametres::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if ( pGOption )
		{
		COptionEntier	*	pIntOption = (COptionEntier*)pGOption ;
		CEcoGravitation*	pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;

		if ( 	m_IntCurrentValue.IsWindowVisible())
			{
			pIntOption->Set( m_IntNumber.GetPos()) ;
			
			CString		Text ;
			Text.Format("%d", (int)*pIntOption ) ;

			m_IntCurrentValue.SetWindowText( Text ) ;

			Text.Format( GIdLabel, (int)*(pIntOption) ) ;
			m_Tree.SetItem( hGItem, TVIF_TEXT, Text, 0,0,0,0,0) ;
			}
		}

	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPagesParametres::OnBoolcheck() 
{
	if ( pGOption )
		{
		((COptionEntier*)pGOption)->Set( m_BoolCheck.GetCheck()) ;

		CString IdOui, IdNon ;

		IdOui.LoadString( IDS_OUI ) ;
		IdNon.LoadString( IDS_NON ) ;
		CString	Label ;
		Label.Format( GIdLabel, *((COptionEntier*)pGOption) ? (const char *) IdOui : (const char *)IdNon ) ;
		m_Tree.SetItem( hGItem, TVIF_TEXT, Label, 0,0,0,0,0) ;
		}
}

void CPagesParametres::OnKillfocusFlottantEdit() 
{
	if ( GFlottantCallBack )
		GFlottantCallBack( this ) ;
}

void CPagesParametres::OnChangeFlottantEdit() 
{
	if ( pGOption )
		{
		CString Text ;
		m_FlottantEdit.GetWindowText(Text) ;

		COptionFlottant * pOption	=	(COptionFlottant*)pGOption ;
		double	Valeur	= atof( Text ) ;
		pOption->Set(  Valeur ) ;

		Text.Format( GIdLabel, (double)*pOption ) ;
		m_Tree.SetItem( hGItem, TVIF_TEXT, Text, 0,0,0,0,0) ;			
		}
}

void CPagesParametres::OnSelchangeChoix() 
{
	if ( ! pGOption )
		return ;

	const int	CurSel	=	m_Choix.GetCurSel() ;

	if ( CurSel != CB_ERR )
		{
		COptionEntier * pOption = (COptionEntier*)pGOption ;

		pOption->Set( CurSel ) ;

		CString	Text ;
		m_Choix.GetLBText( CurSel, Text )  ;

		CString Label ;
		Label.Format( GIdLabel, Text ) ;
		m_Tree.SetItem( hGItem, TVIF_TEXT, Label, 0,0,0,0,0) ;
		}

}

void CPagesParametres::OnFichierBrowse() 
{
	if ( ! pGOption )
		return ;

	COptionChaine*	pOption	=	(COptionChaine*)pGOption ;

	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;
	
	CFileDialog Dlg( TRUE, pOption->Extension(), *pOption,
					 OFN_EXPLORER | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
					 pOption->Filtre(), this ) ;

	char	Directory[_MAX_PATH] ;
	GetDirectory( pOption, Directory ) ;
	SetCurrentDirectory( Directory ) ;
	Dlg.m_ofn.lpstrInitialDir	=	Directory ;

	if ( Dlg.DoModal() == IDOK )
		{
		// Enregistrer les parametres
		pOption->Set( Dlg.GetPathName()) ;

		CString Text ;
		Text.Format( GIdLabel, (const char *)COptions::FichierInit() ) ;
		m_Tree.SetItem( hGItem, TVIF_TEXT, Text, 0,0,0,0,0) ;

		m_FichierEdit.SetWindowText( COptions::FichierInit() ) ;
		GetCurrentDirectory( sizeof( Directory ), Directory ) ;
		SetDirectory( pOption, Directory ) ;
		}	
}

void CPagesParametres::RemplitMasses(HTREEITEM hRoot)
{
	const int	IconMasses	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_MASSES ))) ;
	CString Label ;
	Label.LoadString( IDS_SECTION_MASSES ) ;
	HTREEITEM	hRootItem	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
													Label, IconMasses, IconMasses, 0, 0, ID_SECTION_MASSES, hRoot, TVI_LAST ) ;	
	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	AddFlottantItem( hRootItem, ID_MASSE_0, IDS_MASSE_ITEM, COptions::MasseMax(0), IDI_MASSE_0 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_1, IDS_MASSE_ITEM, COptions::MasseMax(1), IDI_MASSE_1 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_2, IDS_MASSE_ITEM, COptions::MasseMax(2), IDI_MASSE_2 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_3, IDS_MASSE_ITEM, COptions::MasseMax(3), IDI_MASSE_3 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_4, IDS_MASSE_ITEM, COptions::MasseMax(4), IDI_MASSE_4 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_5, IDS_MASSE_ITEM, COptions::MasseMax(5), IDI_MASSE_5 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_6, IDS_MASSE_ITEM, COptions::MasseMax(6), IDI_MASSE_6 ) ;
	AddFlottantItem( hRootItem, ID_MASSE_7, IDS_MASSE_ITEM, COptions::MasseMax(7), IDI_MASSE_7 ) ;

	m_Tree.Expand( hRootItem, TVE_EXPAND ) ;
}

void CPagesParametres::RemplitCometes(HTREEITEM hRoot)
{
	const int	IconCometes	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_COMETE ))) ;
	CString Label ;
	Label.LoadString( IDS_SECTION_COMETES ) ;
	HTREEITEM	hRootItem	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
													Label, IconCometes, IconCometes, 0, 0, ID_SECTION_COMETES, hRoot, TVI_LAST ) ;

	CEcoGravitation * pEco =	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	AddItem			( hRootItem, ID_CREATION_COMETE, IDS_CREATIONCOMETE, COptions::CreationComete(), IDI_COMETE ) ;
	AddFlottantItem	( hRootItem, ID_VENT_SOLAIRE, IDS_VENTSOLAIRE, COptions::VentSolaire(), IDI_COMETE ) ;
	AddItem			( hRootItem, ID_MAX_POUSSIERE, IDS_MAX_POUSSIERE, COptions::NbMaxPoussieres(), IDI_COMETE ) ;
	AddItem			( hRootItem, ID_TAILLE_POUSSIERE, IDS_TAILLE_POUSSIERE, COptions::TaillePoussieres(), IDI_COMETE ) ;
	AddItem			( hRootItem, ID_DISPERSION_POUSSIERE, IDS_DISPERSION_POUSSIERE, COptions::BruitPoussieres(), IDI_COMETE ) ;
	AddItem			( hRootItem, ID_DUST_LIFE_LENGTH, IDS_DUST_LIFE, COptions::ViePoussieres(), IDI_COMETE ) ;
	
	m_Tree.Expand( hRootItem, TVE_EXPAND ) ;
}


void CPagesParametres::RemplitArbre()
{
	_ImageListe.Create( 16, 16, ILC_COLOR16 | ILC_MASK, 0, 1 ) ;
	m_Tree.SetImageList( &_ImageListe, TVSIL_NORMAL ) ;
	m_Tree.DeleteAllItems() ;



	RemplitNombres() ;
	RemplitPhysique() ;
	RemplitAffichage() ;


	CString	Label ;
	Label.LoadString( IDS_TITRE_ARBRE ) ;
	const int	Icon	=	_ImageListe.Add( LoadIcon( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDI_IMPORTANT ))) ;
	HTREEITEM	hRoot	=	m_Tree.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
											   Label, Icon, Icon, 0, 0, ID_TITRE, TVI_ROOT, TVI_FIRST ) ;

	m_Tree.SelectItem( m_Tree.GetNextItem( TVI_ROOT, TVGN_ROOT)) ;
}


// OnUserParameter
// Message prive WM_USER_PARAMETER envoie par la premiere page sur action sur
// un des boutons de lecture/ecriture de fichiers
// ENTREES :
//		wParam : TRUE : lire les parametres saisis et les stocker dans l'economiseur
//				 FALSE : lire les parametres dans l'economiseur et les mettre dans les controles
///////////////////////////////////////////////////////////////////////////////
LONG	CPagesParametres::OnUserParameters( UINT wParam, LONG  )
{
	if ( wParam )
		{
		UpdateData( TRUE ) ;
		}
	else
		{
		RemplitArbre() ;
		}

	return 0 ;
}

void CPagesParametres::RemplitCamera(HTREEITEM hRoot)
{
	AddItem( hRoot, ID_IMAGES_SECONDE, IDS_IMAGE_SECONDE, COptions::NbImagesSeconde(), IDI_CINEMA ) ;
	AddFlottantItem( hRoot, ID_TRAVELING, IDS_TRAVELING, COptions::CoeffTraveling(), IDI_TRAVELING ) ;
	AddFlottantItem( hRoot, ID_ZOOM, IDS_ZOOM, COptions::ZoomMax(), IDI_ZOOM ) ;

	m_Tree.Expand( hRoot, TVE_EXPAND ) ;
}

void CPagesParametres::OnOK() 
{
/*	CRegistrationKey*	pKey = CRegistrationKey::GetKey() ;
	CEconomiseur * pEco	=	CEconomiseur::GetEconomiseur() ;

	CString RegistryKey = "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" 
							+ pEco->NomEconomiseur() ;

	Options.EcritRegistry( RegistryKey, pKey->IsLocked() ) ;
*/
	CEcoGravitation * pEco	=	(CEcoGravitation*)CEcoGravitation::GetEconomiseur() ;
	pEco->GetOptions()->EcritFichier( "Last configuration", "C:\\Gravitation.log", FALSE ) ;

	CPropertyPage::OnOK();
}

///////////////////////////////////////////////////////////////////////////////
// Recupere le repertoire memorise dans la registry pour une option
///////////////////////////////////////////////////////////////////////////////
void CPagesParametres::GetDirectory(COptionChaine *pOption, char *pDir)
{
	CEconomiseur*	pEco	=	CEconomiseur::GetEconomiseur() ;
	CString	Chemin	=	"Software\\Lucien Pilloni\\Economiseurs d'écrans\\Gravitation\\Chemins\\" ;

	HKEY	hKey ;
	if ( RegOpenKeyEx( HKEY_CURRENT_USER,
				  Chemin, 0, KEY_ALL_ACCESS, &hKey ) != ERROR_SUCCESS )
	{
			pDir[0] = 0;
			return ;
	}
						
	char	Valeur [ 1024 ] ;
	DWORD	Taille	=	sizeof( Valeur ) ;
	DWORD Type	=	REG_SZ ;

	if ( RegQueryValueEx( hKey, pOption->Nom(), 0, &Type, (LPBYTE)Valeur, &Taille) == ERROR_SUCCESS )
		strcpy( pDir, Valeur ) ;

	RegCloseKey( hKey ) ;
}

void CPagesParametres::SetDirectory(COptionChaine *pOption, char *pDir)
{
	CEconomiseur*	pEco	=	CEconomiseur::GetEconomiseur() ;
	CString	Chemin	=	"Software\\Lucien Pilloni\\Economiseurs d'écrans\\Gravitation\\Chemins\\" ;

	HKEY	hKey ;
	DWORD	disp ;
	if ( RegCreateKeyEx( HKEY_CURRENT_USER, Chemin, 0, "Path", 
						 REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
						 NULL, &hKey, &disp ) != ERROR_SUCCESS )
		return ;

	RegSetValueEx( hKey, pOption->Nom(), 0, REG_SZ, (BYTE*)pDir, strlen( pDir ) + 1 ) ;
	RegCloseKey( hKey ) ; 
}
