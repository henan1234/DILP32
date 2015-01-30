// IconeCommande.cpp : implementation file
//

#include "stdafx.h"
#include <process.h>
#include "jibe96.h"
#include "resource.h"
#include "icone.h"
#include "IconeCommande.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCommande dialog


CDlgCommande::CDlgCommande(CIcone * pIcone, CStringList & Commandes, CWnd* pParent /*=NULL*/)
	: CWndIcone(pIcone),
	_Commandes( Commandes )
{
	//{{AFX_DATA_INIT(CDlgCommande)
	m_Ligne = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCommande::DoDataExchange(CDataExchange* pDX)
{
	CWndIcone::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCommande)
	DDX_Control(pDX, IDC_LISTE_COMMANDES, m_Liste);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_CBString(pDX, IDC_COMBO1, m_Ligne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCommande, CWndIcone)
	//{{AFX_MSG_MAP(CDlgCommande)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCommande message handlers

IMPLEMENT_SERIAL( CIconeCommande, CIcone, 0 ) ;

CIconeCommande::CIconeCommande()
{
}

CIconeCommande::~CIconeCommande()
{
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void	CIconeCommande::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
{
	HICON	hIcone	=	AfxGetApp()->LoadIcon( IDI_COMMAND ) ;
	HRGN	hRegion =	Region( Pt ) ;
	CRect	R ;
	GetRgnBox( hRegion, R ) ;
	DeleteObject( hRegion ) ;

	Dc.DrawIcon( R.left + ( R.Width() - GetSystemMetrics( SM_CXICON ))/2,
				 R.top,
				 hIcone ) ;
	DestroyIcon( hIcone ) ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
HRGN	CIconeCommande::Region( CPoint Decalage ) const
{
	// Largeur de la fenetre ?
	CSize	Taille( GetMainSize()) ;


	switch( GetSide())
		{
		case ABE_LEFT :
		case ABE_RIGHT :
			Taille.cy	=	GetSystemMetrics( SM_CYICON ) + GetSystemMetrics( SM_CYCAPTION ) ;
			break ;

		case ABE_TOP :
		case ABE_BOTTOM :
			Taille.cx	=	GetSystemMetrics( SM_CXICON ) * 2 ;
			break ;

		default :
			ASSERT( FALSE ) ;
		}

	return CreateRectRgn( Decalage.x, Decalage.y,
						  Decalage.x+Taille.cx,
						  Decalage.y+Taille.cy ) ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
UINT	CIconeCommande::GetMenuID( void ) const
{
return IDR_MENU_REP ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL	CIconeCommande::ExecuteCommand( UINT NoCommande )
{
	return FALSE ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL	CIconeCommande::ExecuteCommand( void )
{
	return FALSE ;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void	CIconeCommande::Serialize( CArchive& ar )
{
	CIcone::Serialize( ar ) ;
	_CommandesTapees.Serialize( ar ) ;
}

#ifdef _DEBUG
void CIconeCommande::AssertValid( void ) const
{
	CIcone::AssertValid() ;
	_CommandesTapees.AssertValid() ;
}

void CIconeCommande::Dump( CDumpContext & dc ) const
{
	CIcone::Dump( dc ) ;
	_CommandesTapees.Dump( dc ) ;
}
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL CIconeCommande::ConfirmeSuppression( void ) const
{
	return TRUE ;
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
BOOL CIconeCommande::Proprietes( int IndiceRacc )
{
	return FALSE ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CIconeCommande::AccepteFichiers( HDROP )
{
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CWnd* CIconeCommande::OuvreFenetre( CRect & RectIcone, CWnd* pParent )
{
	ASSERT_VALID( this ) ;
	CDlgCommande	*	pWnd =	new	CDlgCommande( this, _CommandesTapees ) ;
	ASSERT( pWnd ) ;

	const DWORD	StyleEx	=	WS_EX_TOOLWINDOW ;
	const DWORD	Style	=	WS_POPUP | WS_VISIBLE | WS_BORDER | WS_THICKFRAME ;

	pWnd->Create( IDD_COMMANDE, pParent ) ;
	CRect RFenetre ;
	pWnd->GetClientRect( RFenetre ) ;

	const int LargeurVoulue	=	RFenetre.Width() ;
	const int HauteurVoulue	=	RFenetre.Height() ;

	pParent->ClientToScreen( RectIcone ) ;
	CRect	R( pWnd->AjusteRectangle( RectIcone, LargeurVoulue, HauteurVoulue, Style, StyleEx )) ;

	pWnd->SetWindowPos( pWnd, R.left, R.top, R.Width(), R.Height(),
						SWP_NOZORDER ) ;
	
	pWnd->ShowWindow( SW_SHOW ) ;
	return pWnd ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
CString CIconeCommande::GetTip( void )
{
	return "Pour taper des commandes dos" ;
}


void CDlgCommande::OnOK() 
{
	UpdateData(TRUE) ;

	WinExec( m_Ligne, SW_SHOW ) ;
	
	CWndIcone::OnOK();
}

BOOL CDlgCommande::OnInitDialog() 
{
	CWndIcone::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
