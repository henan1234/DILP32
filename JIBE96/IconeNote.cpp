///////////////////////////////////////////////////////////////////////////////
// CIconeNote
//	Classe d'icones contenant une note
//	Trois etats possibles :
//		MIN :	petite icone et chaine sur la meme ligne
//		MOY :	petite icone et chaine sur plusieurs lignes
//		MAX :	grande icone et chaine sur plusieurs lignes
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "icone.h"
#include "iconenote.h"
#include "jibe96View.h"

IMPLEMENT_SERIAL( CIconeNote, CObject, 0 ) ;

CIconeNote::CIconeNote()
:_Texte( "Note..." ),
_Etat( ETAT_MOY ),
_NoIcone( 0 ),
_CouleurFond( RGB( 255, 255, 128 ))
	{
	}

CIconeNote::~CIconeNote()
	{
	}

void	CIconeNote::Affiche( CDC	&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	CBrush	Brosse( _CouleurFond ) ;
	CRect	R	=	Rect() ;
	R.OffsetRect( Pt ) ;
	Dc.FillRect( R, &Brosse ) ;
	Brosse.DeleteObject() ;

	Dc.DrawEdge( R, Selectionnee ? BDR_RAISEDOUTER : BDR_SUNKENOUTER, BF_RECT ) ;

	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetTextColor( 0 ) ;
	Dc.SetBkMode( TRANSPARENT ) ;
			
	CString	Nom ;
	Nom.Format( "NOTE%d", _NoIcone ) ;
	HICON	hIcone	=	LoadIcon( AfxGetResourceHandle(), Nom ) ;
	

	switch ( _Etat )
		{
		case ETAT_MAX :
			{
			R.top += GetSystemMetrics( SM_CYICON ) ;
			Dc.DrawText( _Texte, -1, R, DT_LEFT | DT_TOP | DT_WORDBREAK ) ;
			Dc.DrawIcon( Pt, hIcone ) ;
			}
			break ;

		case ETAT_MOY :
			{
			// La place prise par l'icone est
			R.top += GetSystemMetrics( SM_CYSMICON ) ;
			Dc.DrawText( _Texte, -1, R, DT_LEFT | DT_TOP | DT_WORDBREAK ) ;
			DrawIconEx( Dc.m_hDC, Pt.x, Pt.y, hIcone,
						GetSystemMetrics( SM_CXSMICON ), GetSystemMetrics( SM_CYSMICON ), 0, 0, DI_NORMAL );
			}
			break ;

		case ETAT_MIN :
			{
			R.left += GetSystemMetrics( SM_CXSMICON ) ;
			Dc.DrawText( _Texte, -1, R, DT_LEFT | DT_TOP ) ;
			DrawIconEx( Dc.m_hDC, Pt.x, Pt.y, hIcone,
						GetSystemMetrics( SM_CXSMICON ), GetSystemMetrics( SM_CYSMICON ), 0, 0, DI_NORMAL );
			}
		}
		

	DestroyIcon( hIcone ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Calculer la region occupee par l'icone en fonction de son etat present
///////////////////////////////////////////////////////////////////////////////
HRGN	CIconeNote::Region( CPoint Decalage ) const
	{
	const CSize	Taille	=	TailleEtat() ;
	HRGN	hRegion =	CreateRectRgn( 0, 0, Taille.cx, Taille.cy ) ;
	OffsetRgn( hRegion, Decalage.x, Decalage.y ) ;
	return hRegion ;
	}

///////////////////////////////////////////////////////////////////////////////
// Archivage
///////////////////////////////////////////////////////////////////////////////
void	CIconeNote::Serialize( CArchive& ar )
	{
	CIcone::Serialize( ar ) ;
	if ( ar.IsStoring())
		{
		ASSERT_VALID( this ) ;
		ar << _Texte ;
		ar << _Etat ;
		ar << _NoIcone ;
		ar << _CouleurFond ;
		}
	else
		{
		ar >> _Texte ;
		ar >> _Etat ;
		ar >> _NoIcone ;
		ar >> _CouleurFond ;
		ASSERT_VALID( this ) ;
		}
	}

// DEBUG
#ifdef _DEBUG
void CIconeNote::AssertValid( void ) const
	{
	CIcone::AssertValid() ;
	ASSERT( _Etat	==	ETAT_MIN || _Etat	== ETAT_MOY || _Etat == ETAT_MAX ) ;
	}

void CIconeNote::Dump( CDumpContext & Dc ) const
	{
	Dc << "Note :"  ;
	CIcone::Dump( Dc ) ;

	Dc << _Texte << "\nEtat : " << _Etat ;
	Dc << " NoIcone : " << _NoIcone << "\n" ;
	}
#endif

///////////////////////////////////////////////////////////////////////////////
// Calculer et retourner la taille actuelle de l'icone note en fonction de son
// etat actuel
///////////////////////////////////////////////////////////////////////////////
CSize	CIconeNote::TailleEtat( void ) const 
	{
	const	CSize	Taille	=	GetMainSize() ;
	const	UINT	Side	=	GetSide() ;
	
	switch( _Etat )
		{
		case ETAT_MIN :
			if ( Side == ABE_LEFT || Side	==	ABE_RIGHT )
				return CSize( Taille.cx, GetSystemMetrics(SM_CYSMICON) ) ;	// Petites icones
			else
				return CSize( GetSystemMetrics( SM_CXSMICON ), Taille.cy ) ;

		default : // Moyenne ou max
			{
			CDC	DC ;
			DC.CreateCompatibleDC( NULL ) ;
			DC.SelectStockObject( ANSI_VAR_FONT ) ;

			CRect	R ;
			
			if ( Side == ABE_LEFT || Side == ABE_RIGHT )
				R.SetRect( 0, 0, Taille.cx, 0 ) ;
			else
				R.SetRect( 0, 0, 0, Taille.cy ) ;

			DC.DrawText( _Texte, -1, R, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_CALCRECT ) ;

			if ( _Etat == ETAT_MOY )
				R.bottom+= GetSystemMetrics( SM_CYSMICON ) ;
			else
				R.bottom+=GetSystemMetrics( SM_CYICON ) ;


			if ( Side == ABE_LEFT || Side == ABE_RIGHT )
				R.right	=	max( R.right, R.left + Taille.cx );
			else
				R.bottom=	max( R.bottom, R.top + Taille.cy ) ;

			return R.Size() ;
			}
		}
	}
/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog


CNoteDlg::CNoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNoteDlg)
	m_Affichage = -1;
	//}}AFX_DATA_INIT
}


void CNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoteDlg)
	DDX_Control(pDX, IDC_ICONES, m_Icones);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoteDlg, CDialog)
	//{{AFX_MSG_MAP(CNoteDlg)
	ON_BN_CLICKED(IDC_COULEUR, OnCouleur)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ICONES, OnItemchangedIcones)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg message handlers

void CNoteDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL CNoteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Remplir la liste d'icones avec les icones notes
	_Images.Create( GetSystemMetrics( SM_CXICON ),
					GetSystemMetrics( SM_CYICON ),
					TRUE, 10, 2 ) ;
	int	i	=	0 ;

	m_Icones.SetImageList( &_Images, LVSIL_NORMAL ) ;

	while (TRUE )
		{
		CString	Nom ;
		Nom.Format( "NOTE%d", i ) ;

		HICON	hIcone	=	LoadIcon( AfxGetResourceHandle(), Nom ) ;
		if ( ! hIcone )
			break ;

		const int	Indice = _Images.Add( hIcone ) ;

		CString	Texte ;
		Texte.Format( "%d", i ) ;

		const int Ind = m_Icones.InsertItem( i, Texte, Indice ) ;
		if ( i == (int)m_NoIcone )
			m_Icones.SetItem( Ind, 0, LVIF_STATE, NULL, 0,
								   LVIS_SELECTED|LVIS_FOCUSED,
								   LVIS_SELECTED|LVIS_FOCUSED,
								   0 ) ;

		i++ ;
		}

	// Selectionner l'icone choisie pour la note
	// Selectionner cet item
	m_Icones.SetItem( m_NoIcone, 0, LVIF_STATE, NULL, 0,
							   LVIS_SELECTED|LVIS_FOCUSED,
							   LVIS_SELECTED|LVIS_FOCUSED,
							   0 ) ;

	m_Icones.SetBkColor( m_Couleur ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CIconeNote::ExecuteCommand( void )
{
	switch( _Etat )
		{
		case ETAT_MIN :
			_Etat	=	ETAT_MOY ;
			break ;
		case ETAT_MOY :
			_Etat	=	ETAT_MAX ;
			break ;	
		default :
			_Etat	=	ETAT_MIN ;
			break ;
		}

	return TRUE ;
}

BOOL CIconeNote::ExecuteCommand( UINT NoCommande )
	{
	switch( NoCommande )
		{
		case ID_NOTE_MAXIMUM :
			_Etat	=	ETAT_MAX ;
			CJibe96View::UpdateIcon(0, TRUE) ;
			break ;
		case ID_NOTE_MOYEN :
			_Etat	=	ETAT_MOY ;
			CJibe96View::UpdateIcon(0, TRUE) ;
			break ;	
		case ID_NOTE_MINIMUM :
			_Etat	=	ETAT_MIN ;
			CJibe96View::UpdateIcon(0, TRUE) ;
			break ;

		case ID_NOTE_COULEUR :
			{
			CColorDialog	Dlg( _CouleurFond, CC_FULLOPEN | CC_RGBINIT, 0 ) ;

			if ( Dlg.DoModal() == IDOK )
				{
				_CouleurFond	=	Dlg.GetColor() ;
				Update() ;
				}
			}
			break ;

		case ID_NOTE_ICONE :
			{
			CNoteDlg	Dlg ;
			Dlg.m_Affichage	=	_Etat ;
			Dlg.m_NoIcone	=	_NoIcone ;
			Dlg.m_Couleur	=	_CouleurFond ;

			if ( Dlg.DoModal()	== IDCANCEL )
				return FALSE ;

			_Etat	=	Dlg.m_Affichage ;
			_NoIcone=	Dlg.m_NoIcone	;
			_CouleurFond	=	Dlg.m_Couleur ;

			Update() ;
			return TRUE ;
			}

		default :
			return FALSE ;
		}

	return TRUE ;
}

void CNoteDlg::OnCouleur() 
{
	CColorDialog	Dlg( m_Couleur, CC_FULLOPEN | CC_RGBINIT, this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		m_Couleur	=	Dlg.GetColor() ;
		m_Icones.SetBkColor( m_Couleur ) ;
		m_Icones.InvalidateRect( NULL, TRUE ) ;
		}
}

UINT CIconeNote::GetMenuID( void ) const
{
	return IDR_MENU_NOTE ;
}

CString CIconeNote::TipText( void ) const
{
	return _Texte ;
}

void CNoteDlg::OnItemchangedIcones(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if ( pNMListView->uNewState & LVIS_SELECTED )
		m_NoIcone	=	pNMListView->iItem ;
	
	*pResult = 0;
}


CString CIconeNote::GetTip( void )
{
	return	_Texte ;
}

///////////////////////////////////////////////////////////////////////////////
// Ouvre la fenetre contextuelle de l'icone sur un clic
///////////////////////////////////////////////////////////////////////////////
CWnd* CIconeNote::OuvreFenetre( CRect & RectIcone, CWnd * pParent )
{
	ASSERT_VALID( this ) ;
	CWndNote	*	pWnd =	new	CWndNote( this ) ;
	ASSERT( pWnd ) ;

	const int LargeurVoulue	=	GetSystemMetrics( SM_CXICONSPACING ) * 4 ;
	const int HauteurVoulue	=	GetSystemMetrics( SM_CYICONSPACING ) * 4 ;
	const DWORD	StyleEx	=	WS_EX_TOOLWINDOW ;
	const DWORD	Style	=	WS_POPUP | WS_BORDER | WS_THICKFRAME ;

	CRect	R( pWnd->AjusteRectangle( RectIcone, LargeurVoulue, HauteurVoulue, Style, StyleEx )) ;

	pParent->ClientToScreen( R ) ;
	LPCTSTR	pClass	=	
	AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW,
						 LoadCursor( AfxGetResourceHandle(),
						 MAKEINTRESOURCE( IDC_CURSOR )),
						 (HBRUSH)(COLOR_BTNFACE + 1 ),
						 0 ) ;

	pWnd->CreateEx( StyleEx,
					pClass, "", Style,
					R.left, R.top, R.Width(), R.Height(),
					pParent->m_hWnd, 0 ) ;
			
	DerouleFenetre( pWnd, R ) ;
	return pWnd ;
}

/////////////////////////////////////////////////////////////////////////////
// CWndNote

CWndNote::CWndNote( CIcone * pIcone )
:CWndIcone( pIcone )
{
}

CWndNote::~CWndNote()
{
}


BEGIN_MESSAGE_MAP( CWndNote, CWndIcone )
	//{{AFX_MSG_MAP(CWndNote)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndNote message handlers

int CWndNote::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWndIcone ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	VERIFY( _ToolBar.Create( this, 
							 WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS | CBRS_TOP | CBRS_SIZE_FIXED, 2 )) ;
	VERIFY( _ToolBar.LoadToolBar( IDR_EDIT )) ;

	ASSERT_VALID( _pIconeAssociee ) ;
	CRect	R ;
	GetClientRect(R) ; 
	VERIFY( _Edit.Create( WS_CHILD | WS_VISIBLE | 
				  ES_MULTILINE | ES_WANTRETURN | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
				  R,
				  this,
				  1 )) ;

	CIconeNote*	pIcone	=	STATIC_DOWNCAST( CIconeNote, _pIconeAssociee ) ;

	_Edit.SetFont( CFont::FromHandle((HFONT)GetStockObject( ANSI_VAR_FONT ))) ;

	_Edit.SetWindowText( pIcone->GetText()) ;
	return 0;
}

HBRUSH CWndNote::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CWndIcone ::OnCtlColor(pDC, pWnd, nCtlColor);

	if ( nCtlColor	==	CTLCOLOR_EDIT )
		{
		ASSERT_VALID( _pIconeAssociee ) ;
		CIconeNote*	pIcone	=	STATIC_DOWNCAST( CIconeNote, _pIconeAssociee ) ;

		const COLORREF	Couleur	=	pIcone->GetCouleur() ;
		hbr	=	CreateSolidBrush( Couleur ) ;
		pDC->SetBkColor( Couleur ) ;
		pDC->SelectStockObject( ANSI_VAR_FONT ) ;
		}
	else
		hbr = CWndIcone::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

void CWndNote::OnSize(UINT nType, int cx, int cy) 
{
	CWndIcone ::OnSize(nType, cx, cy);

	const CSize	TailleTB(_ToolBar.CalcFixedLayout( TRUE, TRUE )) ;

	_ToolBar.SetWindowPos( &CWnd::wndTop, 0, 0, cx, TailleTB.cy, SWP_NOZORDER ) ;
	_Edit.SetWindowPos( &CWnd::wndTop, 0, TailleTB.cy, cx, cy-TailleTB.cy, SWP_NOZORDER ) ;
}

void CIconeNote::SetTexte( const CString & T )
{
	_Texte	=	T ;
	CJibe96View::UpdateIcon(0, TRUE) ;
}

BOOL CWndNote::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch( wParam )
		{
		case IDOK :
			{
			ASSERT_VALID( _pIconeAssociee ) ;
			CIconeNote*	pIcone	=	STATIC_DOWNCAST( CIconeNote, _pIconeAssociee ) ;
			
			CString	Texte ;
			_Edit.GetWindowText( Texte ) ;

			pIcone->SetTexte( Texte ) ;
			_Edit.SetModify( FALSE ) ;
			}
			// C'est expres qu'il n'y a pas de break

		case IDCANCEL :
			DestroyWindow() ;
			break ;

		case ID_EDIT_CUT :
			_Edit.Cut() ;
			break ;

		case ID_EDIT_COPY :
			_Edit.Copy() ;
			break ;

		case ID_EDIT_PASTE :
			_Edit.Paste() ;
			break ;

		case ID_EDIT_UNDO :
			_Edit.Undo() ;
			break ;

		default :
			return CWndIcone ::OnCommand(wParam, lParam);
		}

	return FALSE ;
}

void CIconeNote::AccepteFichiers( HDROP	hDropInfo )
{
	CWaitCursor	C ;

	const int	NbFichiers	=	DragQueryFile( hDropInfo, 0xFFFFFFFF, 0,0 ) ;

	if ( _Texte.Right(1) != "\n" )
		_Texte	+=	"\r\n" ;

	for ( int i = 0; i < NbFichiers; i++)
		{
		char	Nom[_MAX_PATH] ;
		DragQueryFile( hDropInfo, i, Nom, sizeof( Nom )) ;

		_Texte	+= Nom ;
		_Texte	+= "\r\n" ;
		}


	CJibe96View::UpdateIcon(0, TRUE) ;
}

BOOL CIconeNote::ConfirmeSuppression( void ) const
{
	MessageBeep( MB_ICONQUESTION ) ;

	return ( AfxMessageBox( IDS_SUPPRIME_NOTE, MB_ICONQUESTION | MB_OKCANCEL ) 
		     == IDOK ) ;
}

BOOL CWndNote::ConfirmeFermetureAuto( void )
{
	if ( _Edit.GetModify())
		{
		FautRester( TRUE ) ;
		if ( AfxMessageBox( IDS_CONFIRME_NOTE, MB_ICONQUESTION | MB_YESNO | MB_SYSTEMMODAL )==IDYES)
			{
			ASSERT_VALID( _pIconeAssociee ) ;
			CIconeNote*	pIcone	=	STATIC_DOWNCAST( CIconeNote, _pIconeAssociee ) ;
			
			CString	Texte ;
			_Edit.GetWindowText( Texte ) ;

			pIcone->SetTexte( Texte ) ;
			_Edit.SetModify( FALSE ) ;
			}
		FautRester( FALSE ) ;
		}

	return TRUE ;
}
