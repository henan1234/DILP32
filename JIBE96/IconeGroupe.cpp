///////////////////////////////////////////////////////////////////////////////
// CIconeGroupeGroupe : classe icone contenant un groupe de documents
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winreg.h>
#include "resource.h"
#include "icone.h"
#include "iconeGroupe.h"
#include "raccourci.h"
IMPLEMENT_SERIAL( CIconeGroupe, CIcone, 0 ) ;
#define	NB_PTS_ICONE_GROUPE	5


int	CIconeGroupe::_NbGroupes	=	0 ;
  
COLORREF	Couleurs[]	 =			
						{
						RGB( 0, 255, 128 ),
						RGB( 255, 255, 128 ),
						RGB( 128, 255, 255 ),
						RGB( 192, 192, 192 ),
						RGB( 0, 128, 192 ),
						RGB( 128, 128, 0 )
						} ;

CIconeGroupe::CIconeGroupe()
{
	_Couleur	=	Couleurs[ _NbGroupes % (sizeof( Couleurs )/sizeof( Couleurs[0]))] ;

	_Nom.Format( IDS_NOM_GROUPE_DEFAUT, _NbGroupes ) ;

	_NbGroupes ++ ;
}


CIconeGroupe::~CIconeGroupe()
{
	for ( int i = 0; i <= _Raccourcis.GetUpperBound(); i++)
		delete (CRaccourci*)_Raccourcis[i] ;

	_NbGroupes -- ;
}


///////////////////////////////////////////////////////////////////////////////
// GetMenuID
//	Retourne l'ID du menu associe aux icones dans les ressources
//	0 pour indiquer pas de menu
///////////////////////////////////////////////////////////////////////////////
UINT		CIconeGroupe::GetMenuID( void ) const
	{
	return IDR_MENU_GROUPE ;
	}

///////////////////////////////////////////////////////////////////////////////
// ExecuteCommande
//	Execute une commande sur l'icone
//	ENTREES	:	No de l'action dans le menu contextuel
///////////////////////////////////////////////////////////////////////////////
BOOL CIconeGroupe::ExecuteCommand( UINT NoCommande )
	{
	switch( NoCommande )
		{
		case ID_DISQUE_COULEUR :
			{
			CColorDialog Dlg( _Couleur, CC_FULLOPEN | CC_RGBINIT ) ;
			if ( Dlg.DoModal()==IDOK)
				{
				Modifiee( TRUE ) ;
				_Couleur	=	Dlg.GetColor() ;
				Update() ;
				}
			}
			break ;

		case ID_PROPRIETES :
			{
			CPropsGroupe Dlg ;

			Dlg.m_Nom	=	_Nom ;
			if ( Dlg.DoModal() == IDOK)
				{
				_Nom	=	Dlg.m_Nom ;
				Modifiee( TRUE ) ;
				Update() ;
				}
			}
			break ;

		default :
			return ExecuteCommand() ;
		}

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// ExecuteCommande
//	Execute la commande par defaut sur l'icone
///////////////////////////////////////////////////////////////////////////////
BOOL CIconeGroupe::ExecuteCommand( void )
	{
	return FALSE ;
	}

#ifdef _DEBUG
void	CIconeGroupe::AssertValid() const 
	{
	CIcone::AssertValid() ;

	}

void	CIconeGroupe::Dump( CDumpContext & dc ) const
	{
	CIcone::Dump( dc ) ;
	}

#endif


///////////////////////////////////////////////////////////////////////////////
// Affiche :
//	Afficher l'icone groupe
///////////////////////////////////////////////////////////////////////////////
void	CIconeGroupe::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	HRGN	hRegion		=	Region( Pt ) ;

	HBRUSH	hBrosse		=	CreateSolidBrush( _Couleur ) ;

	FillRgn( Dc.m_hDC, hRegion, hBrosse ) ;
	FrameRgn( Dc.m_hDC, hRegion, (HBRUSH)GetStockObject( BLACK_BRUSH ),
			  GetSystemMetrics( SM_CXBORDER ),
			  GetSystemMetrics( SM_CYBORDER ) ) ;

	CRect		R ;
	GetRgnBox( hRegion, R ) ;

	DeleteObject( hRegion ) ;
	DeleteObject( hBrosse ) ;

	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetBkMode( TRANSPARENT ) ;

	if ( Selectionnee )
		Dc.SetTextColor( GetSysColor( COLOR_HIGHLIGHTTEXT )) ;
	else
		Dc.SetTextColor( GetSysColor( COLOR_BTNTEXT )) ;

	Dc.DrawText( _Nom, -1, R, DT_VCENTER | DT_CENTER | DT_SINGLELINE ) ;
	}



void	CIconeGroupe::Serialize( CArchive & ar )
	{
	CIcone::Serialize( ar ) ;

	if ( ar.IsStoring())
		{
		ar << _Couleur ;
		ar << _Nom ;
		}
	else
		{
		ar >> _Couleur ;
		ar >> _Nom ;
		}

	_Raccourcis.Serialize( ar ) ;
	}


CString CIconeGroupe::GetTip( void )
{
	CString	Texte ;
	Texte.LoadString( IDS_TIP_GROUPE ) ;
	return Texte ;
}



CWnd* CIconeGroupe::OuvreFenetre( CRect & RectFenetre, CWnd* pParent )
{
	CWndGroupe	*	pWnd =	new	CWndGroupe(this) ;
	ASSERT( pWnd ) ;

	const	int	LargeurVoulue	=	GetSystemMetrics( SM_CXICONSPACING ) * 4 ;
	const	int HauteurVoulue	=	GetSystemMetrics( SM_CYICONSPACING ) * 4 ;
	const	DWORD	StyleEx		=	WS_EX_TOOLWINDOW ;
	const	DWORD	Style		=	WS_POPUP | WS_VISIBLE | WS_BORDER | WS_THICKFRAME ;

	pParent->ClientToScreen( RectFenetre ) ;
	CRect	R( pWnd->AjusteRectangle( RectFenetre, LargeurVoulue, HauteurVoulue, Style, StyleEx )) ;
	

	LPCTSTR	pClass	=	
	AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW,
						 LoadCursor( AfxGetResourceHandle(), MAKEINTRESOURCE( IDC_CURSOR )),
						 (HBRUSH)(COLOR_BTNFACE + 1 ),
						 0 ) ;

	pWnd->CreateEx( StyleEx,
					pClass, "", Style,
					R.left, R.top, R.Width(), R.Height(),
					pParent->m_hWnd, 0 ) ;
			
	return pWnd ;
}


///////////////////////////////////////////////////////////////////////////////
// Region
//	Obtient la region occupee par l'icone
///////////////////////////////////////////////////////////////////////////////
HRGN	CIconeGroupe::Region( CPoint	Pt ) const
	{
	POINT	Pts[ NB_PTS_ICONE_GROUPE ] ;
	GetPolygon( Pts ) ;
	HRGN	hRegion	=	CreatePolygonRgn( Pts, NB_PTS_ICONE_GROUPE, WINDING ) ;
	OffsetRgn( hRegion, Pt.x, Pt.y ) ;
	return hRegion ;
	}

///////////////////////////////////////////////////////////////////////////////
// Obtient le polygone occupe par l'icone
///////////////////////////////////////////////////////////////////////////////
void CIconeGroupe::GetPolygon( POINT * Pts ) const
{
	ASSERT( AfxIsValidAddress( Pts, sizeof( POINT ) * NB_PTS_ICONE_GROUPE, TRUE )) ;
	const CSize	Size( GetMainSize()) ;
	const int	Biseau	=	GetSystemMetrics( SM_CXSMICON ) / 3;
	const int	Largeur	=	GetSystemMetrics( SM_CXICON ) * 2 / 3 ;


	switch( GetSide())
		{
		case ABE_LEFT :
			Pts[0].x	=	Size.cx ;
			Pts[0].y	=	0 ;
			Pts[1].x	=	Biseau ;
			Pts[1].y	=	0 ;
			Pts[2].x	=	0 ;
			Pts[2].y	=	0 + Biseau ;
			Pts[3].x	=	0 ;
			Pts[3].y	=	Largeur ;
			Pts[4].x	=	Size.cx ;
			Pts[4].y	=	Largeur ;
			break ;
		case ABE_RIGHT :
			Pts[0].x	=	0 ;
			Pts[0].y	=	0 ;
			Pts[1].x	=	Size.cx -  Biseau ;
			Pts[1].y	=	0 ;
			Pts[2].x	=	Size.cx ;
			Pts[2].y	=	0 + Biseau ;
			Pts[3].x	=	Size.cx ;
			Pts[3].y	=	Largeur	;
			Pts[4].x	=	0 ;
			Pts[4].y	=	Largeur ;
			break ;

		case ABE_TOP :
			break ;
		case ABE_BOTTOM :
			break ;
		}
}
/////////////////////////////////////////////////////////////////////////////
// CWndGroupe

CWndGroupe::CWndGroupe( CIcone * pIcone )
:CWndIcone( pIcone )
{
}

CWndGroupe::~CWndGroupe()
{
}


BEGIN_MESSAGE_MAP(CWndGroupe, CWndIcone)
	//{{AFX_MSG_MAP(CWndGroupe)
	ON_WM_CREATE()
	ON_NOTIFY( LVN_BEGINLABELEDIT, 1, OnBeginLabelEdit )
	ON_NOTIFY( LVN_ENDLABELEDIT,   1,	  OnEndLabelEdit )
	ON_NOTIFY( LVN_KEYDOWN, 1, OnKeydown )
	ON_NOTIFY(NM_DBLCLK, 1, OnDblclk)
	ON_NOTIFY(NM_RCLICK, 1, OnRclick)
	ON_COMMAND( ID_PROPRIETES, OnProprietes )
	ON_COMMAND( ID_SUPPRIMER, OnSupprimer )
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndGroupe message handlers


int CWndGroupe::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWndIcone::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	CRect	R ;
	GetClientRect( R ) ;

	_Liste.Create( WS_CHILD | WS_VISIBLE |
				   LVS_AUTOARRANGE | LVS_ICON | LVS_EDITLABELS | LVS_NOCOLUMNHEADER | LVS_SINGLESEL, 
				   R, this, 1 ) ;

	_ListeIcones.Create( GetSystemMetrics( SM_CXICON ), GetSystemMetrics( SM_CYICON ),
						 TRUE, 10, 10 ) ;

	
	// Remplir la liste des icones
	ASSERT_VALID( _pIconeAssociee ) ;
	ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;
	CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;
	const		int		NbRacc	=	pIcone->NbRaccourcis() ;

	_Liste.SetImageList( &_ListeIcones, LVSIL_NORMAL ) ;
	_Liste.SetBkColor( pIcone->GetCouleur()) ;

	for ( int i = 0; i < NbRacc; i++)
		{
		CRaccourci*	pRac	=	pIcone->GetRaccourcis( i ) ;

		// Ajouter l'icone
		HICON	hIcone	=	pRac->GetIcone() ;
		CString	Texte	=	pRac->GetText() ;

		const int	IndiceImage	=	_ListeIcones.Add( hIcone ) ;

		_Liste.InsertItem( i, Texte, IndiceImage ) ;
		}

	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Retourne le nombre de raccourcis que gere ce groupe
///////////////////////////////////////////////////////////////////////////////
int CIconeGroupe::NbRaccourcis( void ) const
{
	return _Raccourcis.GetSize() ;
}


CRaccourci* CIconeGroupe::GetRaccourcis( int Indice )
{
	return (CRaccourci*)_Raccourcis[Indice] ;
}

void CIconeGroupe::SupprimeRaccourci( int Indice )
{
	ASSERT( Indice >= 0 ) ;
	ASSERT( Indice <= _Raccourcis.GetUpperBound()) ;

	delete	(CRaccourci*)_Raccourcis[Indice] ;
	_Raccourcis.RemoveAt( Indice ) ;
	Modifiee( TRUE ) ;
}

//////////////////////////////////////////////////////////////////////////////
// AccepteFichiers
//	Ajoute un raccourci par fichier lache sur le groupe
//	Si un raccourci est un nom de repertoire, on demande a l'utilisateur s'il
//	veut ajouter le contenu du repertoire
//////////////////////////////////////////////////////////////////////////////
void CIconeGroupe::AccepteFichiers( HDROP hDropInfo )
{
	CWaitCursor	C ;

	const int	NbFichiers	=	DragQueryFile( hDropInfo, 0xFFFFFFFF, 0,0 ) ;
	
	for ( int i = 0; i < NbFichiers; i++)
		{
		char	Nom[_MAX_PATH] ;
		DragQueryFile( hDropInfo, i, Nom, sizeof( Nom )) ;

		CString	Resolu( Nom ) ;
		CRaccourci::ResoudShortCut( Resolu ) ;

		// Est-ce un fichier ou un repertoire ?
		if ( CRaccourci::IsFolder( Resolu ) )
			{
			CString	Confirme ;
			Confirme.Format( IDS_CONFIRME_GROUPE_REPERTOIRE, Nom ) ;
			if ( AfxMessageBox( Confirme, MB_ICONQUESTION | MB_YESNO ) == IDYES )
				{
				AjouteRep( Resolu ) ;
				continue ;
				}
			}
		
		// Ajout du fichier
		CRaccourci	*	pRaccourci =	new	CRaccourci ;

		pRaccourci->SetCommande( Resolu ) ;
		pRaccourci->SetIcone( Nom, 0 ) ;

		char	Texte[_MAX_FNAME] ;
		_splitpath( Nom, 0,0, Texte, 0 ) ;
		pRaccourci->SetText( Texte ) ;

		_Raccourcis.Add( pRaccourci ) ;
		Modifiee(TRUE) ;
		}
}


void CWndGroupe::OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = FALSE ;
}

void CWndGroupe::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	if ( pDispInfo->item.pszText )
		{
		CString		NouveauTexte( pDispInfo->item.pszText ) ;
		const		int	No	= _Liste.GetNextItem( -1, LVNI_SELECTED ) ;

		ASSERT( No != -1 ) ;
		ASSERT_VALID( _pIconeAssociee ) ;
		ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;
		CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;
		
		CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( No ) ;
		pRaccourci->SetText( NouveauTexte ) ;
		pIcone->Modifiee(TRUE) ;
		_Liste.SetItem( No, 0, LVIF_TEXT, NouveauTexte, 0, 0, 0, 0 ) ;
		}

	*pResult = 0;
}

void CWndGroupe::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	
	if ( NoSel != -1 )
		{
		switch	( pLVKeyDow->wVKey )
			{
			case VK_F2 :
				_Liste.EditLabel( NoSel ) ;
				break ;

			case VK_DELETE :
				SupprimeRaccourci( NoSel ) ;
				break ;
			}
		}

	*pResult = 0;
}

void CWndGroupe::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	
	if ( NoSel != -1 )
		{
		ASSERT_VALID( _pIconeAssociee ) ;
		ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;
		CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;
		
		CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( NoSel ) ;
		ASSERT_VALID( pRaccourci ) ;
		pRaccourci->Active() ;
		}

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////
// OnRClick
//	Clic avec le deuxieme bouton de la souris, on affiche un menu contextuel
//	sur l'objet clique
//	On demande a l'objet d'ajouter eventuellement des options de menu
//////////////////////////////////////////////////////////////////////////////
void CWndGroupe::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	
	if ( NoSel != -1 )
		{
		ASSERT_VALID( _pIconeAssociee ) ;
		ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;

		CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;
		
		CMenu	Menu;
		Menu.LoadMenu( IDR_RACCOURCI ) ;
		CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( NoSel ) ;
		
		pRaccourci->ModifMenu( Menu.GetSubMenu(0), IDM_COMMANDES ) ;

		CPoint	Pt ;
		GetCursorPos( &Pt ) ;

		Menu.GetSubMenu(0)->TrackPopupMenu( TPM_RIGHTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
											Pt.x, Pt.y, this ) ;
		
		Menu.DestroyMenu() ;
		}
	*pResult = 0;
}

void CWndGroupe::SupprimeRaccourci( int NoSel )
	{
	FautRester() ;
	ASSERT_VALID( _pIconeAssociee ) ;
	ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;

	CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;

	CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( NoSel ) ;
	ASSERT_VALID( pRaccourci ) ;
	CString	Message ;
	Message.Format( IDS_SUPPRIMER_RACCOURCI, (LPCSTR)pRaccourci->GetText()) ;

	if ( MessageBox( Message, NULL, MB_ICONQUESTION | MB_YESNO ) == IDYES )
		{
		pIcone->SupprimeRaccourci( NoSel ) ;
		_Liste.DeleteItem( NoSel ) ;
		_Liste.Arrange( LVA_DEFAULT ) ;
		}
	FautRester(FALSE) ;
	}

///////////////////////////////////////////////////////////////////////////////
// OnProprietes
//	Saisir les proprietes du raccourci selectionne
///////////////////////////////////////////////////////////////////////////////
void	CWndGroupe::OnProprietes( void )
	{
	const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;

	if ( NoSel != -1 )
		{
		CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;
		FautRester() ;
		if ( pIcone->Proprietes( NoSel ))
			{
			CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( NoSel ) ;
			ASSERT_VALID( pRaccourci ) ;

			const int Indice	=	_ListeIcones.Add( pRaccourci->GetIcone()) ;
			const	CString		Texte( pRaccourci->GetText()) ;

			_Liste.SetItem( NoSel, 0, LVIF_TEXT | LVIF_IMAGE, Texte, Indice, 0, 0, 0 ) ;
			}
		FautRester( FALSE ) ;
		}
	}

void	CWndGroupe::OnSupprimer( void )
	{
	const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
	SupprimeRaccourci( NoSel ) ;
	}


BOOL CIconeGroupe::Proprietes( int IndiceRacc )
{
	CRaccourci*	pRaccourci	=	(CRaccourci*)_Raccourcis[IndiceRacc] ;
	CPropsRaccourci	Dlg( AfxGetMainWnd()) ;

	Dlg.m_Nom				=	pRaccourci->GetText() ;
	Dlg.m_Commande			=	pRaccourci->GetCommande() ;
	Dlg._NomFichierIcone	=	pRaccourci->GetFichierIcone() ;
	Dlg._IndiceIcone		=	(int)pRaccourci->GetIndiceIcone() ;

	if ( Dlg.DoModal() == IDCANCEL )
		return FALSE ;

	pRaccourci->SetText( Dlg.m_Nom ) ;
	pRaccourci->SetCommande( Dlg.m_Commande ) ;
	pRaccourci->SetIcone( Dlg._NomFichierIcone, (WORD)Dlg._IndiceIcone ) ;

	Modifiee( TRUE ) ;
	return TRUE ;
}
/////////////////////////////////////////////////////////////////////////////
// CPropsGroupe dialog


CPropsGroupe::CPropsGroupe(CWnd* pParent /*=NULL*/)
	: CDialog(CPropsGroupe::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropsGroupe)
	m_Nom = _T("");
	//}}AFX_DATA_INIT
}


void CPropsGroupe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropsGroupe)
	DDX_Text(pDX, IDC_NOM, m_Nom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropsGroupe, CDialog)
	//{{AFX_MSG_MAP(CPropsGroupe)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropsGroupe message handlers

void CWndGroupe::OnSize(UINT nType, int cx, int cy) 
{
	CWndIcone::OnSize(nType, cx, cy);
	
	_Liste.SetWindowPos( &CWnd::wndTop, 0, 0, cx, cy, SWP_NOZORDER ) ;
}

BOOL CIconeGroupe::ConfirmeSuppression( void ) const
{
	CString	Chaine ;
	Chaine.Format( IDS_SUPPRIME_GROUPE, (LPCSTR)_Nom ) ;

	MessageBeep( MB_ICONQUESTION ) ;
	return ( AfxMessageBox( Chaine, MB_ICONQUESTION | MB_OKCANCEL ) == IDOK ) ;
}


//////////////////////////////////////////////////////////////////////////////
// Ajoute un raccourci vers le programmes du menu de demarrage
//////////////////////////////////////////////////////////////////////////////
void CIconeGroupe::AjouteProgrammes( void )
{	
	char	Rep[ _MAX_PATH ] ;
	DWORD	TailleRep	=	sizeof( Rep ) ;
	// rechercher le repertoire du menu programmes
	HKEY	hKey ;
	VERIFY( RegOpenKeyEx( HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",
						  0, KEY_READ, &hKey ) == ERROR_SUCCESS ) ;
	DWORD	Type	=	REG_SZ ;
	VERIFY( RegQueryValueEx( hKey ,"Programs", 0, &Type, (unsigned char*)Rep, &TailleRep ) == ERROR_SUCCESS ) ;
	RegCloseKey( hKey ) ;

	AjouteRep( Rep ) ;

	char	Nom[_MAX_FNAME ] ;
	_splitpath( Rep, NULL, NULL, Nom, NULL ) ;
	_Nom	=	Nom ;
}

//////////////////////////////////////////////////////////////////////////////
// Ajoute un raccourci pour chaque fichier du repertoire
//////////////////////////////////////////////////////////////////////////////
void CIconeGroupe::AjouteRep( const char * Rep )
{
	CWaitCursor	Curseur ;

	CString	Chemin	=	Rep + CString("\\*.*" );
	WIN32_FIND_DATA	FData ;
	HANDLE	hFF	=	FindFirstFile( Chemin, &FData ) ;
	BOOL	Continuer	=	(hFF != INVALID_HANDLE_VALUE ) ;

	while ( Continuer )
		{
		if ( lstrcmp( ".", FData.cFileName ) && lstrcmp( "..", FData.cFileName ))
			{
			CRaccourci	*	pRaccourci =	new	CRaccourci ;
			CString		NomFichier	=	Rep ;
			NomFichier	+=	"\\" ;
			NomFichier	+=	FData.cFileName ;

			pRaccourci->SetCommande( NomFichier ) ;
			pRaccourci->SetIcone( NomFichier, 0 ) ;

			char	Nom[_MAX_FNAME] ;
			_splitpath( NomFichier, 0,0, Nom, 0 ) ;
			pRaccourci->SetText( Nom ) ;

			_Raccourcis.Add( pRaccourci ) ;
			Modifiee(TRUE) ;

			}

		Continuer	=	FindNextFile( hFF, &FData ) ;
		}

	FindClose( hFF ) ;
}

BOOL CWndGroupe::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam >= IDM_COMMANDES  && wParam < (IDM_COMMANDES +100))
		{
		const	int	NoSel	=	_Liste.GetNextItem( -1, LVNI_SELECTED ) ;
		
		if ( NoSel != -1 )
			{
			ASSERT_VALID( _pIconeAssociee ) ;
			ASSERT( _pIconeAssociee->IsKindOf( RUNTIME_CLASS( CIconeGroupe ))) ;

			CIconeGroupe	*	pIcone	=	STATIC_DOWNCAST( CIconeGroupe, _pIconeAssociee ) ;

			CRaccourci*	pRaccourci	=	pIcone->GetRaccourcis( NoSel ) ;
			ASSERT_VALID( pRaccourci ) ;
			pRaccourci->Menu( wParam - IDM_COMMANDES ) ;
			}

		return TRUE ;
		}
	else
		return CWndIcone::OnCommand(wParam, lParam);
}
