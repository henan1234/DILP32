///////////////////////////////////////////////////////////////////////////////
// CIcone : classe generique
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <math.h>
#include "resource.h"
#include "mainfrm.h"
#include "icone.h"
#include "jibe96View.h" 

IMPLEMENT_DYNAMIC( CIcone, CObject ) ;
  
CIcone::CIcone()
:_Modifiee( FALSE )				// Pas encore modifiee
{
	// La taille de la fenetre contextuelle n'est pas encore definie
	_TailleFenetre.cx	=	-1 ;
	_TailleFenetre.cy	=	-1 ;
}


CIcone::~CIcone()
{
}

///////////////////////////////////////////////////////////////////////////////
// Modifiee, VIRTUELLE
// Met a jour le flag indiquent si l'icone est modifiee ou non
// Si elle est modifiee, il faudra la sauvegarder
///////////////////////////////////////////////////////////////////////////////
void	CIcone::Modifiee( BOOL Mod )
{
	ASSERT_VALID( this ) ;
	_Modifiee	=	Mod ;
}

///////////////////////////////////////////////////////////////////////////////
// GetMenuID
//	Retourne l'ID du menu associe aux icones dans les ressources
//	0 pour indiquer pas de menu
///////////////////////////////////////////////////////////////////////////////
UINT		CIcone::GetMenuID( void ) const
	{
	return 0 ;
	}

///////////////////////////////////////////////////////////////////////////////
// ExecuteCommande
//	Execute une commande sur l'icone
//	ENTREES	:	No de l'action dans le menu contextuel
///////////////////////////////////////////////////////////////////////////////
BOOL CIcone::ExecuteCommand( UINT NoCommande )
	{
	return ExecuteCommand() ;
	}

///////////////////////////////////////////////////////////////////////////////
// ExecuteCommande
//	Execute la commande par defaut sur l'icone
///////////////////////////////////////////////////////////////////////////////
BOOL CIcone::ExecuteCommand( void )
	{
	return FALSE ;
	}

#ifdef _DEBUG
void	CIcone::AssertValid() const 
	{
	CObject::AssertValid() ;
	}

void	CIcone::Dump( CDumpContext & dc ) const
	{
	if ( _Modifiee )
		dc << "Modifiée\n" ;
	else
		dc << "Non modifiée\n" ;
	}

#endif

///////////////////////////////////////////////////////////////////////////////
// Rect, publique, virtuelle
// Retourne le rectangle occupe par l'icone aux coordonnees 0
// 
///////////////////////////////////////////////////////////////////////////////
CRect CIcone::Rect( void ) const
{
	CPoint Pt( 0,0) ;
	HRGN	hRegion	=	Region(Pt) ;

	CRect	R ;
	GetRgnBox( hRegion, R ) ;
	DeleteObject( hRegion ) ;

	return R ;
}


int CIcone::Hauteur( void ) const
{
	return Rect().Height() ;
}

int CIcone::Largeur( void ) const
{
	return Rect().Width() ;
}

void	CIcone::Serialize( CArchive & ar )
	{
	CObject::Serialize( ar ) ;
	_Modifiee	=	FALSE ;

	if ( ar.IsStoring())
		ar << _TailleFenetre.cx << _TailleFenetre.cy ;
	else
		ar >> _TailleFenetre.cx >> _TailleFenetre.cy ;
	}

BOOL CIcone::PtInIcon( CPoint Pt, CPoint PosIcon ) const
{
	HRGN	hRegion	=	Region( PosIcon ) ;
	const	BOOL	bRes	=	PtInRegion( hRegion, Pt.x, Pt.y ) ;
	DeleteObject( hRegion ) ;
	return bRes ;
}


void CIcone::Update( BOOL Efface )
{
	CJibe96View::UpdateIcon( this, Efface ) ;
}

CString CIcone::GetTip( void )
{
	return	"" ;
}

CSize CIcone::GetMainSize( void )
{
	return CJibe96View::GetSize() ;
}

UINT CIcone::GetSide( void )
{
	CMainFrame * pWnd	=	STATIC_DOWNCAST( CMainFrame, AfxGetMainWnd() ) ;

	return pWnd->GetSide() ;
}


// Retourne VRAI si l'ecran a 64K couleurs
BOOL CIcone::Colors64K( void )
{
	HDC hDC	=	CreateIC( "display", 0,0,0 ) ;

	const int	NbBits	=	GetDeviceCaps( hDC, BITSPIXEL ) ;
	const int	NbPlans	=	GetDeviceCaps( hDC, PLANES ) ;

	DeleteDC( hDC ) ;

	return pow( 2, NbBits*NbPlans) > 256 ; 
}


CWnd* CIcone::OuvreFenetre( CRect & RectFenetre, CWnd* pParent )
{
	return 0 ;
}


///////////////////////////////////////////////////////////////////////////////
// Memoriser la nouvelle taille de fenetre
///////////////////////////////////////////////////////////////////////////////
void CIcone::TailleFenetre( const CSize & Taille )
{
	if ( Taille != _TailleFenetre )
		{
		_TailleFenetre	= Taille ;	
		Modifiee( TRUE ) ;
		}
}

BOOL CIcone::ConfirmeSuppression( void ) const
{
	return TRUE ;
}

void CIcone::AccepteFichiers( HDROP )
{
}


///////////////////////////////////////////////////////////////////////////////
// Assombri l'icone quand sa fenetre est affichee
///////////////////////////////////////////////////////////////////////////////
void CIcone::Assombri( CDC & Dc, CPoint Pt )
{
	HRGN	hRegion	=	Region( Pt ) ;
	CBitmap	Bitmap ;	
	VERIFY( Bitmap.LoadBitmap( IDB_ASSOMBRIR )) ;
	CBrush	Brosse( &Bitmap ) ;

	Dc.SetROP2( R2_MASKPEN ) ;
	FillRgn( Dc, hRegion, Brosse ) ;

	Brosse.DeleteObject() ;
	Bitmap.DeleteObject() ;
	DeleteObject( hRegion ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Ouvre progressivement une fenetre
///////////////////////////////////////////////////////////////////////////////
void CIcone::DerouleFenetre( CWnd * pWnd, const CRect & R ) const
{
	ASSERT_VALID( pWnd ) ;

	// Calcul de la position de depart
	CRect RInitial( R ) ;
	switch( GetSide())
		{
		case ABE_LEFT :
			RInitial.right	=	RInitial.left ;
			break ;
		case ABE_RIGHT :
			RInitial.left	=	RInitial.right ;
			break ;
		case ABE_TOP :
			RInitial.bottom	=	RInitial.top ;
			break ;

		case ABE_BOTTOM :
			RInitial.top	=	RInitial.bottom ;
			break ;

		default :
			ASSERT( FALSE ) ;
		}

	while ( RInitial != R )
		{
		if ( RInitial.right < R.right )
			RInitial.right += (R.right-RInitial.right)/2 + 1 ;

		if ( RInitial.bottom < R.bottom )
			RInitial.bottom += (R.bottom-RInitial.bottom)/2 + 1 ;

		if ( RInitial.left > R.left )
			RInitial.left -= ( RInitial.left-R.left)/2 + 1 ;

		if ( RInitial.top > R.top )
			RInitial.top -= ( RInitial.top - R.top ) / 2 + 1 ;


		pWnd->SetWindowPos( &CWnd::wndTopMost, 
							RInitial.left, RInitial.top,
							RInitial.Width(), RInitial.Height(),
							SWP_SHOWWINDOW ) ;
		pWnd->UpdateWindow() ;
		}
}
