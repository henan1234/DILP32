///////////////////////////////////////////////////////////////////////////////
// CIconeBoutonBouton : classe Bouton
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "shellapi.h"
#include "resource.h"
#include "Icone.h"
#include "IconeBouton.h"
#include "lpiicone.h"
#include "lpibitmap.h"
#include "raccourci.h"

IMPLEMENT_SERIAL( CIconeBouton, CObject, 0 ) ;

CIconeBouton::CIconeBouton()
{
}

CIconeBouton::~CIconeBouton()
{
}

void	CIconeBouton::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
{
	CLPIBitmap	Bitmap( IDB_BOUTON ) ;
	Bitmap.Affiche( &Dc, Pt.x, Pt.y ) ;

	HICON	hIcone	=	_Raccourci.GetIcone() ;

	CRect R = Rect() ;
	R.OffsetRect( Pt ) ;

	if ( hIcone )
		{
		const int LIcone	=	GetSystemMetrics( SM_CXSMICON ) + 2 ;
		const int HIcone	=	GetSystemMetrics( SM_CYSMICON ) + 2 ;

		DrawIconEx(	Dc.m_hDC,
					Pt.x + 2,
					Pt.y + ( Bitmap.Hauteur() - HIcone ) / 2,
					hIcone,
					LIcone,
					HIcone,
					0, 0, DI_NORMAL ) ;

		R.left	+=	LIcone ;
		}

	R.DeflateRect( 2, 2 ) ;

	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetTextColor( ::GetSysColor( COLOR_BTNTEXT )) ;
	Dc.SetBkColor( ::GetSysColor( COLOR_BTNFACE )) ;

	Dc.Draw3dRect( R, ::GetSysColor( COLOR_BTNSHADOW ), ::GetSysColor(  COLOR_BTNHILIGHT)) ;

	R.DeflateRect( 1,1 ) ;
	Dc.DrawText( _Raccourci.GetText(), R, DT_LEFT | DT_VCENTER | DT_SINGLELINE ) ;
}


UINT	CIconeBouton::GetMenuID( void ) const
{
	return IDR_MENU_BOUTON ;
}

BOOL	CIconeBouton::ExecuteCommand( UINT NoCommande )
{
	switch( NoCommande )
		{
		case ID_PROPRIETES :
			{
			CPropsRaccourci	Dlg( AfxGetMainWnd()) ;

			Dlg.m_Nom				=	_Raccourci.GetText() ;
			Dlg.m_Commande			=	_Raccourci.GetCommande() ;
			Dlg._NomFichierIcone	=	_Raccourci.GetFichierIcone() ;
			Dlg._IndiceIcone		=	_Raccourci.GetIndiceIcone() ;

			if ( Dlg.DoModal() == IDCANCEL )
				return FALSE ;

			_Raccourci.SetText( Dlg.m_Nom ) ;
			_Raccourci.SetCommande( Dlg.m_Commande ) ;
			_Raccourci.SetIcone( Dlg._NomFichierIcone, Dlg._IndiceIcone );

			Modifiee( TRUE ) ;
			Update() ;
			}
			break ;

		case ID_EXECUTER :
			_Raccourci.Active() ;
			break ;

		default :
			return FALSE ;
		}

	return TRUE ;
}

BOOL	CIconeBouton::ExecuteCommand( void )
{
	_Raccourci.Active() ;
	return TRUE ;
}

void	CIconeBouton::Serialize( CArchive& ar )
{
	CIcone::Serialize( ar ) ;
	_Raccourci.Serialize( ar ) ;
}

		// DEBUG
#ifdef _DEBUG
void CIconeBouton::AssertValid( void ) const
{
	CIcone::AssertValid() ;
	_Raccourci.AssertValid() ;
}

void CIconeBouton::Dump( CDumpContext & dc ) const
{
	CIcone::Dump( dc ) ;
	_Raccourci.Dump( dc ) ;
}

#endif

void CIconeBouton::AccepteFichiers( HDROP )
{
}

BOOL CIconeBouton::ConfirmeSuppression( void ) const
{
	return TRUE ;
}

CRect CIconeBouton::Rect( void ) const
{
	CLPIBitmap	Bitmap( IDB_BOUTON ) ;
	return CRect( 0, 0, Bitmap.Largeur(), Bitmap.Hauteur()) ;
}

HRGN CIconeBouton::Region( CPoint Pt ) const
{
	CLPIBitmap	Bitmap( IDB_BOUTON ) ;
	HRGN	hRegion	=	CreateRectRgn(0, 0, Bitmap.Largeur(), Bitmap.Hauteur() ) ;

	OffsetRgn( hRegion, Pt.x, Pt.y ) ;
	return hRegion ;
}

CString CIconeBouton::GetTip( void )
{
	return _Raccourci.GetText() ;
}
