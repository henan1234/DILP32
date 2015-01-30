// WndIcone.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "icone.h"
#include "WndIcone.h"
#include "IconeGroupe.h"
#include "jibe96view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndIcone

CWndIcone::CWndIcone( CIcone * pIcone )
{
	_FautRester	=	FALSE ;
	ASSERT( pIcone ) ;
	_pIconeAssociee	=	pIcone ;
}

CWndIcone::~CWndIcone()
{
}


BEGIN_MESSAGE_MAP(CWndIcone, CDialog)
	//{{AFX_MSG_MAP(CWndIcone)
	ON_WM_ACTIVATE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndIcone message handlers

void CWndIcone::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if ( nState	==	WA_INACTIVE && !_FautRester )
		{
		if ( ConfirmeFermetureAuto())
			{
			DestroyWindow() ;
			return ;
			}
		}
	CDialog::OnActivate(nState, pWndOther, bMinimized);
}

/////////////////////////////////////////////////////////////////////////////
// Gestion du booleen qui empeche la fermeture automatique de la fenetre
// quand on en active une autre.
/////////////////////////////////////////////////////////////////////////////
void CWndIcone::FautRester( BOOL R )
{
	_FautRester	=	R ;
}

///////////////////////////////////////////////////////////////////////////////
// Creation de la fenetre
//	Placer la fenetre au sommet de la pile
///////////////////////////////////////////////////////////////////////////////
int CWndIcone::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE ) ;
	
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Destruction de la fenetre
//	On commence par memoriser la taille de la fenetre pour la prochaine fois
///////////////////////////////////////////////////////////////////////////////
void CWndIcone::OnDestroy() 
{
	_FautRester	=	TRUE ;
	CRect	R ;
	GetClientRect( R ) ;

	ASSERT_VALID( _pIconeAssociee ) ;
	_pIconeAssociee->TailleFenetre( R.Size()) ;
	_FautRester	=	FALSE ;

	CDialog::OnDestroy();
}

BOOL CWndIcone::ConfirmeFermetureAuto( void )
{
	return TRUE ;
}

/////////////////////////////////////////////////////////////////////////////
// AjusteRectangle
//	Obtient un rectangle pour une fenetre cadre sur l'icone.
//	Si la fenetre a deja une taille enregistree, on ignore celle qui est
//	donnee en parametre.
//	On cadre le rectangle au bord de l'icone en fonction de la position de la
//	barre de jibe
/////////////////////////////////////////////////////////////////////////////
CRect CWndIcone::AjusteRectangle( const CRect & RIcone, int Largeur, int Hauteur, DWORD Style, DWORD StyleEx )
{
	ASSERT_VALID( _pIconeAssociee ) ;
	const CSize	Taille(	_pIconeAssociee->GetTailleFenetre() ) ;	

	CRect	RFenetre ;
	if ( Taille.cx != -1 && Taille.cy != -1 )
		RFenetre.SetRect( 0,0, Taille.cx, Taille.cy ) ;
	else
		RFenetre.SetRect( 0,0, Largeur, Hauteur ) ;

	// Agrandir le rectangle en fonction du style de fenetre demande
	AdjustWindowRectEx( RFenetre, Style, FALSE, StyleEx ) ;

	RFenetre.OffsetRect( - RFenetre.left, - RFenetre.top ) ;
	ASSERT( RFenetre.left == 0 ) ;		// Resultat de la ligne precedente
	ASSERT( RFenetre.top == 0 ) ;		

	// Cadrer la fenetre au bord de l'icone
	switch ( CIcone::GetSide() )
		{
		case ABE_RIGHT :
			// Cadrer la fenetre en haut a gauche de l'icone
			RFenetre.OffsetRect( RIcone.left - RFenetre.Width(),
								 RIcone.top ) ;
			break ;
			
		case ABE_LEFT :
			// Cadrer la fenetre a gauche de l'icone
			RFenetre.OffsetRect( RIcone.right, RIcone.top ) ;
			break ;

		case ABE_TOP :
		case ABE_BOTTOM :
		default :
			TRACE("Top/Bottom non supporte pour AjusteRectangle\n" ) ;
			ASSERT( FALSE ) ;
		}

	const	int	LargeurDesktop	=	GetSystemMetrics( SM_CXFULLSCREEN ) ;
	const	int	HauteurDesktop	=	GetSystemMetrics( SM_CYFULLSCREEN ) ;
	
	if ( RFenetre.bottom > HauteurDesktop )
		{
		if ( RFenetre.Height() < HauteurDesktop )
			RFenetre.OffsetRect( 0, HauteurDesktop - RFenetre.bottom ) ;
		else
			{
			RFenetre.top	=	0 ;
			RFenetre.bottom	=	HauteurDesktop ;
			}
		}

	if ( RFenetre.right > LargeurDesktop )
		{
		if ( RFenetre.Width() < LargeurDesktop )
			RFenetre.OffsetRect( LargeurDesktop - RFenetre.right, 0 ) ;
		else
			{
			RFenetre.right	=	LargeurDesktop ;
			RFenetre.left	=	0 ;
			}
		}

	return RFenetre ;
}

/////////////////////////////////////////////////////////////////////////////
// AjusteRectangle
//	Obtient un rectangle pour une fenetre cadre sur l'icone.
//	Deuxieme version : la fenetre ne peut pas etre retaillee
/////////////////////////////////////////////////////////////////////////////
void CWndIcone::AjusteRectangle( const CRect & RIcone )
{
	ASSERT( IsWindow( m_hWnd )) ;

	CRect	RFenetre ;
	GetWindowRect( RFenetre ) ;

	RFenetre.OffsetRect( - RFenetre.left, - RFenetre.top ) ;
	ASSERT( RFenetre.left == 0 ) ;		// Resultat de la ligne precedente
	ASSERT( RFenetre.top == 0 ) ;		


	// Cadrer la fenetre au bord de l'icone
	switch ( CIcone::GetSide() )
		{
		case ABE_RIGHT :
			// Cadrer la fenetre en haut a gauche de l'icone
			RFenetre.OffsetRect( RIcone.left - RFenetre.Width(),
								 RIcone.top ) ;
			break ;
			
		case ABE_LEFT :
			// Cadrer la fenetre a gauche de l'icone
			RFenetre.OffsetRect( RIcone.right, RFenetre.top ) ;
			break ;

		case ABE_TOP :
		case ABE_BOTTOM :
		default :
			TRACE("Top/Bottom non supporte pour AjusteRectangle\n" ) ;
			ASSERT( FALSE ) ;
		}

	const	int	LargeurDesktop	=	GetSystemMetrics( SM_CXFULLSCREEN ) ;
	const	int	HauteurDesktop	=	GetSystemMetrics( SM_CYFULLSCREEN ) ;
	
	if ( RFenetre.bottom > HauteurDesktop )
		RFenetre.OffsetRect( 0, HauteurDesktop - RFenetre.bottom ) ;

	if ( RFenetre.right > LargeurDesktop )
		RFenetre.OffsetRect( LargeurDesktop - RFenetre.right, 0 ) ;

	SetWindowPos( this, RFenetre.left, RFenetre.top, 0, 0, SWP_NOSIZE | SWP_NOZORDER ) ;
}
