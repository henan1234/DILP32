///////////////////////////////////////////////////////////////////////////////
// CIconeSeparateur
//	Classe d'icones contenant un separateur
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "icone.h"
#include "iconeSeparateur.h"

IMPLEMENT_SERIAL( CIconeSeparateur, CObject, 0 ) ;

CIconeSeparateur::CIconeSeparateur()
	{
	_Hauteur	=	::GetSystemMetrics( SM_CYCAPTION ) ;
	}

CIconeSeparateur::~CIconeSeparateur()
	{
	}

void	CIconeSeparateur::Affiche( CDC	&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	CRect	R=Rect() ;

	R.OffsetRect( Pt ) ;

	if ( Selectionnee )
		Dc.DrawEdge( R, EDGE_RAISED, BF_RECT ) ;
	else
		Dc.DrawEdge( R, EDGE_ETCHED, BF_RECT ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Calculer la region occupee par l'icone en fonction de son etat present
///////////////////////////////////////////////////////////////////////////////
HRGN	CIconeSeparateur::Region( CPoint Decalage ) const
	{
	CRect	R =	Rect() ;
	HRGN	hRegion	=	CreateRectRgn( 0, 0, R.Width(), R.Height() ) ;
	OffsetRgn( hRegion, Decalage.x, Decalage.y ) ;
	return hRegion ;
	}

///////////////////////////////////////////////////////////////////////////////
// Archivage
///////////////////////////////////////////////////////////////////////////////
void	CIconeSeparateur::Serialize( CArchive& ar )
	{
	CIcone::Serialize( ar ) ;
	if ( ar.IsStoring())
		{
		ASSERT_VALID( this ) ;
		ar << _Hauteur ;
		}
	else
		{
		ar >> _Hauteur ;
		ASSERT_VALID( this ) ;
		}
	}

// DEBUG
#ifdef _DEBUG
void CIconeSeparateur::AssertValid( void ) const
	{
	CIcone::AssertValid() ;
	ASSERT( _Hauteur > 0 ) ;
	}

void CIconeSeparateur::Dump( CDumpContext & Dc ) const
	{
	CIcone::Dump( Dc ) ;

	Dc << _Hauteur << "\n" ;
	}
#endif


BOOL CIconeSeparateur::ExecuteCommand( void )
{
	CSeparateurDlg	Dlg ;
	Dlg.m_Hauteur	=	_Hauteur ;

	if ( Dlg.DoModal() != IDOK )
		return FALSE ;

	_Hauteur	=	Dlg.m_Hauteur ;

	return TRUE ;
}

BOOL CIconeSeparateur::ExecuteCommand( UINT NoCommande )
	{
	switch( NoCommande )
		{
		case ID_PROPRIETES :
			return ExecuteCommand() ;

		default :
			return FALSE ;
		}
}

UINT CIconeSeparateur::GetMenuID( void ) const
{
	return IDR_MENU_SEPARATEUR ;
}



CString CIconeSeparateur::GetTip( void )
{
	return	"" ;
}
/////////////////////////////////////////////////////////////////////////////
// CSeparateurDlg dialog


CSeparateurDlg::CSeparateurDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeparateurDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSeparateurDlg)
	m_Hauteur = 0;
	//}}AFX_DATA_INIT
}


void CSeparateurDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSeparateurDlg)
	DDX_Control(pDX, IDC_HAUTEUR, m_WndHauteur);
	DDX_Control(pDX, IDC_DESSIN, m_Dessin);
	DDX_Control(pDX, IDC_SPIN1, m_Spinner);
	DDX_Text(pDX, IDC_HAUTEUR, m_Hauteur);
	DDV_MinMaxInt(pDX, m_Hauteur, 1, 50);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSeparateurDlg, CDialog)
	//{{AFX_MSG_MAP(CSeparateurDlg)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeparateurDlg message handlers

BOOL CSeparateurDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Spinner.SetBuddy( &m_WndHauteur ) ;
	m_Spinner.SetRange( 1, 50 ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSeparateurDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	UpdateData( TRUE ) ;
	CDC	* pDc = m_Dessin.GetDC( ) ;

	CRect	R ;
	m_Dessin.GetClientRect( R ) ;

	CBrush	Brosse( ::GetSysColor( COLOR_WINDOW )) ;
	pDc->FillRect( R, &Brosse ) ;
	Brosse.DeleteObject() ;

	int Milieu	=	(R.bottom-R.top) / 2 ;

	CRect	RSep ;
	RSep.left	=	R.left + ( R.Width() - m_Hauteur ) / 2 ;
	RSep.top	=	R.top + ( R.Height() - m_Hauteur ) / 2 ;
	RSep.right	=	RSep.left + m_Hauteur ;
	RSep.bottom	=	RSep.top + m_Hauteur ;

	pDc->DrawEdge( RSep, EDGE_ETCHED, BF_RECT ) ;
	
	m_Dessin.ReleaseDC(pDc) ;
}

CRect CIconeSeparateur::Rect( void ) const
{
	const CSize	Size	=	GetMainSize() ;
	const UINT	Side	=	GetSide() ;
	
	switch( Side )
		{
		case ABE_RIGHT :
		case ABE_LEFT :
			return CRect( 0,0, Size.cx, _Hauteur ) ;

		case ABE_TOP :
		case ABE_BOTTOM :
			return CRect( 0,0, _Hauteur, Size.cy ) ;

		default :
			ASSERT( FALSE ) ;
			return CRect(0,0,0,0) ;
		}
}

