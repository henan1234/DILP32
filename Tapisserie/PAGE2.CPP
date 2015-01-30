// Page2.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include <winreg.h>
#include "tapisserie.h"
#include "Tapisserie V2.h"
#include "Page2.h"
#include "..\classes\registrykey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
	//{{AFX_DATA_INIT(CPage2)
	m_Minutes = 5;
	m_Mosaique = -1;
	m_Economiseur = FALSE;
	//}}AFX_DATA_INIT

	// Chargement de la liste d'images
	CRegistryKey	Key( HKEY_CURRENT_USER, "Software\\Lucien PILLONI\\Tapisserie V2\\Images" ) ;
	Key.GetValue( "Courant", _Courant ) ;
	Key.GetValue( "Economiseur", m_Economiseur ) ;

	int	Indice	=	0 ;
	while ( TRUE )
		{
		CString	Nom ;
		Nom.Format( "Image%d", Indice ) ;

		CRegistryKey	SubKey( Key, Nom ) ;
		if ( ! SubKey.Exist())
			break ;

		BOOL	Mosaique ;
		int		NbMinutes ;
		if ( ! SubKey.GetValue( "Nom", Nom ))
			break ;

		if ( ! SubKey.GetValue( "Mosaique", Mosaique ))
			break ;


		if ( ! SubKey.GetValue( "NbMinutes", NbMinutes ))
			break ;

		CTapisserie*	pTapisserie	=	new CTapisserie( Nom, Mosaique, NbMinutes ) ;
		_ListeTapisseries.SetAtGrow( _ListeTapisseries.GetSize(), pTapisserie ) ;

		Indice ++ ;
		}
}

CPage2::~CPage2()
{
	CRegistryKey	Key( HKEY_CURRENT_USER, "Software\\Lucien PILLONI\\Tapisserie V2\\Images" ) ;
	// Vide la clef de registry
	Key.Delete() ;

	Key.SetValue( "Courant", _Courant ) ;
	Key.SetValue( "Economiseur", m_Economiseur ) ;
	
	for ( int i = 0; i < _ListeTapisseries.GetSize(); i++)
		{
		CTapisserie*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[i] ;

		CString	Nom ;
		Nom.Format( "Image%d", i ) ;

		CRegistryKey	SubKey( Key, Nom ) ;
		
		SubKey.SetValue( "Nom", pTapisserie->Nom()) ;
		SubKey.SetValue( "Mosaique", pTapisserie->Mosaique()) ;
		SubKey.SetValue( "NbMinutes", pTapisserie->NbMinutes()) ;
		}
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
	DDX_Control(pDX, IDC_SPIN1, m_SpinnerMinutes);
	DDX_Control(pDX, IDC_MINUTES, m_EditMinutes);
	DDX_Control(pDX, IDC_SUPPRIMER, m_Supprimer);
	DDX_Control(pDX, IDC_LISTE, m_Liste);
	DDX_Text(pDX, IDC_MINUTES, m_Minutes);
	DDV_MinMaxInt(pDX, m_Minutes, 1, 100);
	DDX_Radio(pDX, IDC_Mosaique, m_Mosaique);
	DDX_Check(pDX, IDC_ECONOMISEUR, m_Economiseur);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPage2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AJOUTER, OnAjouter)
	ON_BN_CLICKED(IDC_CENTRE, OnCentre)
	ON_BN_CLICKED(IDC_Mosaique, OnMosaique)
	ON_EN_CHANGE(IDC_MINUTES, OnChangeMinutes)
	ON_BN_CLICKED(IDC_TESTER, OnTester)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTE, OnItemchangedListe)
	ON_BN_CLICKED(IDC_SUPPRIMER, OnSupprimer)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTE, OnDblclkListe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers

///////////////////////////////////////////////////////////////////////////////
// Changement immediat d'image
///////////////////////////////////////////////////////////////////////////////
void CPage2::ChangeMaintenant( void )
{
	if ( _ListeTapisseries.GetSize() == 0 )
		return ;

	if ( _Courant >= _ListeTapisseries.GetSize())
		_Courant	=	0 ;

	CTapisserie*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[_Courant] ;

	_DepuisChangement = 0 ;
	pTapisserie->Active() ;
	_Courant ++ ;
}

///////////////////////////////////////////////////////////////////////////////
// Fonction appelee par la fenetre principale toutes les minutes
// Si le decompte est superieur au temps de retention de l'image courante,
// on passe a la suivante
///////////////////////////////////////////////////////////////////////////////
void CPage2::OnTimer(UINT nIDEvent) 
{
	if ( _ListeTapisseries.GetSize() == 0 )
		return ;

	if ( ! m_Economiseur )
		{
		if ( ::FindWindow("WindowsScreenSaverClass", NULL ))
			return ;
		}

	if ( _Courant >= _ListeTapisseries.GetSize())
		_Courant	=	0 ;

	CTapisserie*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[_Courant] ;

	_DepuisChangement ++ ;

	if ( _DepuisChangement >=	pTapisserie->NbMinutes())
		{
		_DepuisChangement = 0 ;
		pTapisserie->Active() ;
		_Courant ++ ;
		}

	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CPage2::OnInitDialog() 
{	
	CWaitCursor C ;
	CPropertyPage::OnInitDialog();


	_ImageListe.Create( 16, 16, TRUE, 3, 1) ;
	_ImageListe.Add( AfxGetApp()->LoadIcon( IDI_ICON3 )) ;
	_ImageListe.Add( AfxGetApp()->LoadIcon( IDI_ICON4 )) ;
	_ImageListe.Add( AfxGetApp()->LoadIcon( IDI_ICON5 )) ;


	m_Liste.SetImageList( &_ImageListe, LVSIL_SMALL ) ;

	// Remplissage de la liste
	CString	Titre ;
	Titre.LoadString( IDS_TITRE1 ) ;
	m_Liste.InsertColumn( 0, Titre, LVCFMT_LEFT, 345, 0 )  ;

	Titre.LoadString( IDS_TITRE3 ) ;
	m_Liste.InsertColumn( 2, Titre, LVCFMT_RIGHT, 50, 1 )  ;

	m_SpinnerMinutes.SetRange( 1, 100 ) ;

	for ( int i = 0; i < _ListeTapisseries.GetSize(); i++ )
		{
		CTapisserie*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[i] ;

		CString Min ;
		Min.Format ( "%d min", pTapisserie->NbMinutes() ) ;

		const	int	NoItem =	m_Liste.GetItemCount() ;

		m_Liste.InsertItem( NoItem, pTapisserie->Nom(), NoIcone( pTapisserie ) ) ;
		m_Liste.SetItem( NoItem, 1, LVIF_TEXT, Min, 0,0,0,0) ;
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

///////////////////////////////////////////////////////////////////////////////
// Ajout d'une image dans la liste
///////////////////////////////////////////////////////////////////////////////
void CPage2::AjouteImage( const char * Image, BOOL Mosaique, int NbMinutes )
{
	CString Min ;
	Min.Format ( "%d min", NbMinutes ) ;

	const	int	NoItem =	m_Liste.GetItemCount() ;
	m_Liste.InsertItem( NoItem, Image ) ;
	m_Liste.SetItem( NoItem, 1, LVIF_TEXT, Min, 0,0,0,0) ;
	
	CTapisserie *	pTapisserie	=	new CTapisserie( Image, Mosaique,NbMinutes ) ;

	_ListeTapisseries.SetAtGrow( _ListeTapisseries.GetSize(), pTapisserie ) ;
}

void CPage2::OnAjouter() 
{
	char	BufferFiles[ _MAX_PATH * 100 ] ;


	CFileDialog		Dlg(	TRUE, "BMP", NULL,
							OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_EXPLORER | OFN_LONGNAMES,
							"Images Windows (*.BMP)|*.BMP;*.DIB|",
							this ) ;

	Dlg.m_ofn.lpstrFile	=	BufferFiles ;
	Dlg.m_ofn.nMaxFile	=	sizeof( BufferFiles ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CWaitCursor C ;
		UpdateData( TRUE ) ;

		POSITION	Pos	=	Dlg.GetStartPosition() ;
		while ( Pos )
			{
			CString Nom	=	Dlg.GetNextPathName(Pos) ;
			AjouteImage( Nom, m_Mosaique == 0, m_Minutes ) ;
			}
		}

}

void CPage2::OnCentre() 
{
	const int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;
	pTapisserie->Mosaique( FALSE ) ;

	m_Liste.SetItem( Selectionne, 0, LVIF_IMAGE, 0, NoIcone( pTapisserie ), 0, 0, 0 ) ;
}

void CPage2::OnMosaique() 
{
	const int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;
	pTapisserie->Mosaique( TRUE ) ;

	m_Liste.SetItem( Selectionne, 0, LVIF_IMAGE, 0, NoIcone( pTapisserie ), 0, 0, 0 ) ;
}


void CPage2::OnChangeMinutes() 
{
	const int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CString	NbMinutes ;
	m_EditMinutes.GetWindowText( NbMinutes ) ;
	const	int	Nb	=	atoi( NbMinutes ) ;

	CString	Chaine ;
	Chaine.Format( "%d min", Nb ) ;

	m_Liste.SetItem( Selectionne, 1,LVIF_TEXT|LVIF_STATE, Chaine, 0,0,0,0 ) ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;
	pTapisserie->NbMinutes( Nb ) ;

}

void CPage2::OnTester() 
{
	const int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;
	pTapisserie->Active() ;

}

void CPage2::OnItemchangedListe(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	const int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;

	m_Minutes	=	pTapisserie->NbMinutes() ;
	m_Mosaique	=	(pTapisserie->Mosaique() ? 0 : 1) ;

	UpdateData( FALSE ) ;
}

void CPage2::OnSupprimer() 
{
	int	Selectionne	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( Selectionne == -1 )
		return ;

	CTapisserie	*	pTapisserie	=	(CTapisserie*)_ListeTapisseries[Selectionne] ;
	_ListeTapisseries.RemoveAt( Selectionne ) ;
	delete pTapisserie ;

	m_Liste.DeleteItem( Selectionne ) ;

	if ( m_Liste.GetItemCount() <= Selectionne )
		Selectionne	=	m_Liste.GetItemCount() ;

	m_Liste.SetItem( Selectionne, 0, LVIF_STATE, NULL, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED, 0 ) ;
	m_Liste.EnsureVisible( Selectionne, FALSE ) ;
}

void CPage2::OnDblclkListe(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnTester() ;
	
	*pResult = 0;
}

int CPage2::NoIcone( const CTapisserie * pTapisserie )
{
	const int ErrorMode = SetErrorMode( SEM_NOOPENFILEERRORBOX ) ;
	int	  NoIcone ;

	if ( _access( pTapisserie->Nom(), 0 ) == -1 )
		NoIcone = 2 ;
	else
		if ( pTapisserie->Mosaique() )
			NoIcone	=	1 ;
		else
			NoIcone	=	0 ;

	SetErrorMode( ErrorMode ) ;

	return NoIcone ;
}

