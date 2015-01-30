// propback.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "propback.h"
#include "tapisserie.h"
#include "tapisseriedlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


static const	char	*	SousClef	=	"Fonds d'écran" ;

/////////////////////////////////////////////////////////////////////////////
// CPropBackground property page
const	UINT	CPropBackground::_wDragListNotify=	RegisterWindowMessage( DRAGLISTMSGSTRING ) ;
int				CPropBackground::_NbMinutes		 	=	0 ;
int				CPropBackground::_Courant		 	=	0 ;
int				CPropBackground::_DepuisChangement	 =	0 ;



IMPLEMENT_DYNCREATE(CPropBackground, CPropertyPage)

CPropBackground::CPropBackground() : CPropertyPage(CPropBackground::IDD)
{
	//{{AFX_DATA_INIT(CPropBackground)
	//m_MinutesTexte = _T("");
	//}}AFX_DATA_INIT
}


CPropBackground::~CPropBackground()
{
}

void CPropBackground::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange( pDX ) ;
	//{{AFX_DATA_MAP(CPropBackground)
	DDX_Control(pDX, IDC_TEXTE_MINUTES, m_MinutesTexte);
	DDX_Control(pDX, IDC_MINUTES, m_Minutes);
	DDX_Control(pDX, IDC_IMAGES, m_Liste);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropBackground, CPropertyPage)
	ON_WM_DROPFILES()
	ON_REGISTERED_MESSAGE(_wDragListNotify, OnDragListNotify )
	
	//{{AFX_MSG_MAP(CPropBackground)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_AJOUTER, OnAjouter)
	ON_BN_CLICKED(IDC_SUPPRIMER, OnSupprimer)
	ON_BN_CLICKED(IDC_TESTER, OnTester)
	ON_LBN_DBLCLK(IDC_IMAGES, OnDblclkImages)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropBackground message handlers

BOOL CPropBackground::OnInitDialog()
{
	CPropertyPage::OnInitDialog() ;

	LitConfiguration() ;

	m_Minutes.SetRange( 1, 100 ) ;
	m_Minutes.SetPos( _NbMinutes ) ;
	m_Minutes.SetPageSize( 5 ) ;

	MakeDragList( m_Liste.m_hWnd ) ;

	m_Liste.SetCurSel( 0 ) ;

	ChangeTexteMinutes( _NbMinutes ) ;

	DragAcceptFiles( TRUE ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CPropBackground::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	ChangeTexteMinutes( m_Minutes.GetPos());
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}
	

void	CPropBackground::ChangeTexteMinutes( int Nb )
{
	char	Buffer[50] ;

	if ( Nb == 1)
		lstrcpy( Buffer, "Chaque minute" ) ;
	else
		wsprintf( Buffer, "Toutes les %d minutes", Nb ) ;

	m_MinutesTexte.SetWindowText( Buffer ) ;

}

///////////////////////////////////////////////////////////////////////////////
// Ajout d'une image dans la liste apres dialogue
///////////////////////////////////////////////////////////////////////////////
void CPropBackground::OnAjouter() 
{
	CFileDialog		Dlg(	TRUE, "BMP", NULL,
							OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_NONETWORKBUTTON | OFN_EXPLORER | OFN_LONGNAMES,
							"Bitmaps|*.BMP|", this ) ;
	if ( Dlg.DoModal())
		{
		m_Liste.AddString( Dlg.GetPathName()) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
//
// Lire toute la configuration :
//		- Liste des images
//		- Delai entre chaque changement
//		- Image courante
//
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::LitConfiguration()
{
	_NbMinutes			=	CMonAppli::LitEntier( SousClef, "Delai", 5 ) ;
	_Courant			=	CMonAppli::LitEntier( SousClef, "Courant", 0 ) ;

	const	DWORD	Nb	=	CMonAppli::LitEntier( SousClef, "Nb Images", 0 ) ;

	m_Liste.ResetContent() ;

	for ( DWORD	i	=	0; i < Nb; i++)
		{
		CString	Rubrique ;
		Rubrique.Format( "Image%d", i ) ;
		char	Fichier[255] ;

		CMonAppli::LitChaine( SousClef, Rubrique, Fichier, sizeof( Fichier ) ) ;

		m_Liste.AddString( Fichier ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
//
// Ecrire toute la configuration :
//		- Liste des images
//		- Delai entre chaque changement
//		- Image courante
//
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::EcritConfiguration()
{
	_NbMinutes	=	m_Minutes.GetPos() ;

	CMonAppli::EcritEntier( SousClef, "Delai", _NbMinutes ) ;
	CMonAppli::EcritEntier( SousClef, "Courant", _Courant ) ;
	CMonAppli::EcritEntier( SousClef, "Nb images", m_Liste.GetCount()) ;
	
	for ( int i = 0; i < m_Liste.GetCount(); i++)
		{
		CString	Fichier	;
		m_Liste.GetText( i, Fichier ) ;

		CString	Rubrique ;
		Rubrique.Format( "Image%d", i ) ;
		CMonAppli::EcritChaine( SousClef, Rubrique, Fichier ) ;
		}
}



///////////////////////////////////////////////////////////////////////////////
// Suppression d'une image de la liste
///////////////////////////////////////////////////////////////////////////////
void CPropBackground::OnSupprimer() 
{
	const	int	Indice	=	m_Liste.GetCurSel() ;
	
	m_Liste.DeleteString	( Indice ) ;
}



///////////////////////////////////////////////////////////////////////////////
// Tester l'image selectionnee dans la liste
///////////////////////////////////////////////////////////////////////////////
void CPropBackground::OnTester() 
{
	const	int	Sel	=	m_Liste.GetCurSel() ;

	if ( Sel == LB_ERR )
		return ;

	CString	Texte	;
	m_Liste.GetText( Sel, Texte ) ;


	ChangeTapisserie( Texte ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Changer l'image de fond de Windows
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::ChangeTapisserie( const char * NomFichier )
{
	HCURSOR	hCurseur	=	SetCursor( LoadCursor( AfxGetResourceHandle(), "CHANGEMENT" )) ;
	CTapisserieDlg::Icone( IDI_TASKBAR_CHANGE ) ;

	// Memoriser les info concernant le screen saver, a cause d'un bug
	BOOL	ScrActif ;
	int		ScrTimeOut ;

	::SystemParametersInfo( SPI_GETSCREENSAVEACTIVE, 0, (void far *)&ScrActif, 0 ) ;
	::SystemParametersInfo( SPI_GETSCREENSAVETIMEOUT, 0, (void far *)&ScrTimeOut, 0 ) ;


	::SystemParametersInfo( SPI_SETDESKWALLPAPER, 0, 
						(void far *)(LPCSTR)NomFichier,
	                    SPIF_UPDATEINIFILE ) ;

	::SystemParametersInfo( SPI_SETSCREENSAVEACTIVE, ScrActif, 0, 0 ) ;
	::SystemParametersInfo( SPI_SETSCREENSAVETIMEOUT, ScrTimeOut, 0, 0 ) ;

	CTapisserieDlg::Icone(  IDI_TASKBAR ) ;
	SetCursor( hCurseur ) ;
}

///////////////////////////////////////////////////////////////////////////////
// reception de fichiers dans la liste
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::OnDropFiles( HDROP hDropInfo )
{
	const	UINT NbFichiers	=	::DragQueryFile( hDropInfo, (UINT)-1,0,0 ) ;

	for ( UINT i = 0; i < NbFichiers; i++)
		{
		CString	Fichier ;
		const	int	Longueur	=	::DragQueryFile( hDropInfo, i, 0, 0 ) +1 ;
		::DragQueryFile( hDropInfo, i, Fichier.GetBuffer( Longueur ), Longueur ) ;
		Fichier.ReleaseBuffer( ) ;

		m_Liste.AddString( Fichier ) ;
		}

	::DragFinish( hDropInfo ) ;
}


///////////////////////////////////////////////////////////////////////////////
// OnDblclkImages
//	Double clic sur une image dans la liste -> test de l'image
///////////////////////////////////////////////////////////////////////////////
void CPropBackground::OnDblclkImages() 
{
	OnTester() ;	
}

///////////////////////////////////////////////////////////////////////////////
// OnDragListNotify
//	Gestion des messages de notification de la drag list box
///////////////////////////////////////////////////////////////////////////////
LRESULT	CPropBackground::OnDragListNotify( WPARAM wParam, LPARAM	lParam )
{
 	if ( wParam == IDC_IMAGES )
		{
		DRAGLISTINFO	*	lpDragListInfo	=	(DRAGLISTINFO*)lParam ;
		const int	Indice	=	LBItemFromPt( m_Liste.m_hWnd, lpDragListInfo->ptCursor, TRUE ) ;
								
		switch( lpDragListInfo->uNotification )
			{
			case DL_BEGINDRAG :
				DrawInsert( m_hWnd, m_Liste.m_hWnd, Indice) ;
				return TRUE ;

			case DL_CANCELDRAG :
				break ;

			case DL_DRAGGING :
				{
				DrawInsert( m_hWnd, m_Liste.m_hWnd, Indice) ;
		
				if ( Indice	== -1 )
					return DL_STOPCURSOR ;
				else
					return DL_MOVECURSOR ;
				}
					
			case DL_DROPPED :
				{
				const int	Indice	=	LBItemFromPt( m_Liste.m_hWnd, lpDragListInfo->ptCursor, TRUE ) ;
				
				if ( Indice != -1 )
					{
					const int	Selected	=	m_Liste.GetCurSel() ;
					m_Liste.SetRedraw( FALSE ) ;

					CString	Chaine ;
					m_Liste.GetText( Selected, Chaine ) ;

					m_Liste.DeleteString( Selected ) ;
					m_Liste.InsertString( Indice>Selected ? Indice -1 : Indice, Chaine ) ;

					m_Liste.SetCurSel( Indice ) ;

					m_Liste.SetRedraw() ;
					m_Liste.InvalidateRect( NULL, TRUE ) ;
					}
				}
				break ;
			}
		}
	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
// OnTimer, STATIQUE
//	Appelee toutes les minutes par la fenetre principale
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::OnTimer()
{
	_DepuisChangement	++ ;

	const int Delai	=		CMonAppli::LitEntier( SousClef, "Delai", 5 ) ;

	if ( _DepuisChangement >= Delai )
		ChangeMaintenant() ;
}

///////////////////////////////////////////////////////////////////////////////
// ChangeMaintenant, STATIQUE
//	Force le changement immediat de la tapisserie
///////////////////////////////////////////////////////////////////////////////
void	CPropBackground::ChangeMaintenant()
{
	HCURSOR	hCurseur	=	SetCursor( LoadCursor( AfxGetResourceHandle(), "CHANGEMENT" )) ;
	UINT	Courant	=	CMonAppli::LitEntier( SousClef, "Courant", 0 ) ;

	CString	Rubrique ;
	Rubrique.Format( "Image%d", Courant ) ;
	char	Fichier[255] ;

	CMonAppli::LitChaine( SousClef, Rubrique, Fichier, sizeof( Fichier ) ) ;
	
	Courant ++ ;

	const	UINT	Nb	=	CMonAppli::LitEntier( SousClef, "Nb Images", 0 ) ;
	if ( Courant >= Nb )
		Courant	=	0 ;

	CMonAppli::EcritEntier( SousClef, "Courant", Courant ) ;

	ChangeTapisserie( Fichier ) ;

	_DepuisChangement	=	0 ;
}

void	CPropBackground::OnOK()
{
	// Validation de la page
	EcritConfiguration() ;
}
