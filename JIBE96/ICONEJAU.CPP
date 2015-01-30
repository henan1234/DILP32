///////////////////////////////////////////////////////////////////////////////
// CIconeJauge
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winnls.h>
#include "IconeJauge.h"
#include "DlgSeuilAlarme.h"
#include "Jibe96View.h"
#include "lpibitmap.h"

IMPLEMENT_DYNAMIC( CIconeJauge, CIconePeriodique ) ;

CIconeJauge::CIconeJauge()
:_PourcentageAlarme( 10 ),
_DernierPourcentage( 0 ),
_AlarmeAffichee( FALSE )
	{
	}

CIconeJauge::~CIconeJauge()
	{
	}

void	CIconeJauge::Update()
	{
	BOOL	Upd	=	FALSE ;
	const UINT	Pourcentage	=	GetPourcentage() ;

	if ( Pourcentage != _DernierPourcentage )
		{
		_DernierPourcentage = Pourcentage ;
		Upd		=	TRUE ;
		}

	if ( _DernierPourcentage < _PourcentageAlarme )
		{
		_AlarmeAffichee	=	!	_AlarmeAffichee ;
		Upd		=	TRUE ;
		}

	if ( Upd )
		CJibe96View::UpdateIcon( this ) ;
	}

void	CIconeJauge::Serialize( CArchive & ar )
	{
	CIconePeriodique::Serialize( ar ) ;

	if ( ar.IsStoring())
		ar << _PourcentageAlarme ;
	else
		ar >> _PourcentageAlarme ;
	}

#ifdef _DEBUG
void	CIconeJauge::AssertValid( void ) const
	{
	CIconePeriodique::AssertValid() ;
	ASSERT( _PourcentageAlarme >= 0 && _PourcentageAlarme <= 100) ;
	}
#endif

void CIconeJauge::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	// Affiche le fond
	CLPIBitmap	Bitmap( GetIDBitmap()) ;
	Bitmap.Affiche( &Dc, Pt.x, Pt.y ) ;
	
	// Affiche la jauge
	CRect	R( Pt, CSize( Bitmap.Largeur(), Bitmap.Hauteur() )) ;
	const	UINT	Valeur	=	GetPourcentage() ;
	CBrush	Brosse( GetCouleurBarre( ((UINT)Valeur <= _PourcentageAlarme )
									  && _AlarmeAffichee )) ;

	CRect	RJauge( R ) ;
	RJauge.InflateRect( -2, -4 ) ;
	RJauge.right	=	ChangeIntervalle( Valeur, 0, 100, RJauge.left, RJauge.right ) ;
	CBrush*	pOldB	=	Dc.SelectObject( &Brosse ) ;
	Dc.PatBlt( RJauge.left, RJauge.top, RJauge.Width(), RJauge.Height(),
			   PATINVERT ) ;
	Dc.SelectObject( pOldB ) ;
	Brosse.DeleteObject() ;
	
	const	CString Texte	=GetText( Valeur ) ;
	//Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	const int Bk = Dc.SetBkMode( TRANSPARENT ) ;
	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.DrawText( Texte, -1, R, DT_VCENTER | DT_CENTER | DT_SINGLELINE ) ;
	Dc.SetBkMode( Bk ) ;

	// Affiche la barre d'alarme
	CRect	RAlarme( R ) ;
	RAlarme.InflateRect( -2, -4 ) ;
	RAlarme.left	=	ChangeIntervalle( _PourcentageAlarme, 0, 100,
										  RAlarme.left, RAlarme.right ) ;
	RAlarme.right	=	RAlarme.left + 1 ;

	CBrush	Br( Valeur <= _PourcentageAlarme && _AlarmeAffichee  ?
				RGB( 255, 255, 0) : RGB( 255, 0, 0 ) ) ;
	Dc.FillRect( RAlarme, &Br ) ;
	Br.DeleteObject() ;
	
	if ( Selectionnee )
		{
		R.InflateRect( -1, -1 ) ;
		Dc.DrawFocusRect( R ) ;
		}
	}

HRGN CIconeJauge::Region( CPoint Decalage ) const
	{
	CLPIBitmap	Bitmap( GetIDBitmap() ) ;
	
	return CreateRectRgn( Decalage.x, Decalage.y,
						  Decalage.x + Bitmap.Largeur(),
						  Decalage.y + Bitmap.Hauteur() ) ;
	}
	

UINT CIconeJauge::ChangeIntervalle( DWORD Valeur, DWORD DepMin, DWORD DepMax, DWORD DstMin, DWORD DstMax )
{
	DWORD	Val = Valeur ;
	Val -=	DepMin ;
	Val	=	Valeur * (DstMax-DstMin) / (DepMax-DepMin) ;
	Val +=	DstMin ;

	return (UINT)Val ;
}

CString CIconeJauge::GetText( UINT Pourcentage )
{
	CString	Texte ;
	Texte.Format( "%d%%", Pourcentage ) ;
	return Texte ;
}

const UINT & CIconeJauge::GetPourcentageAlarme( void ) const
{
	return _PourcentageAlarme ;
}

void	CIconeJauge::SetPourcentageAlarme( UINT Alarme )
	{
	ASSERT( Alarme >= 0 ) ;
	ASSERT( Alarme <= 100 ) ;

	if ( _PourcentageAlarme != Alarme )
		{
		_PourcentageAlarme	=	Alarme ;
		Modifiee( TRUE ) ;
		CJibe96View::UpdateIcon( this ) ;
		}

	}

CString CIconeJauge::FormatNumber( DWORD Val )
{
	CString	Chaine ;
	Chaine.Format( "%ld", Val ) ;

	char	Buffer[100] ;

	GetNumberFormat( LOCALE_USER_DEFAULT,
					 0,
					 Chaine,
					 NULL,
					 Buffer,
					 sizeof( Buffer )) ;

	return Buffer ;
}

CString CIconeJauge::FormatNumber( double Val )
{
	CString	Chaine ;
	Chaine.Format( "%f", Val ) ;

	char	Buffer[100] ;

	GetNumberFormat( LOCALE_USER_DEFAULT,
					 0,
					 Chaine,
					 NULL,
					 Buffer,
					 sizeof( Buffer )) ;

	return Buffer ;
}

CWnd* CIconeJauge::OuvreFenetre( CRect & RectIcone, CWnd * pParent )
{
	CDlgSeuilAlarme*	pWnd	=	new CDlgSeuilAlarme( this ) ;
	pWnd->Create( IDD_SEUIL_ALARME, pParent ) ;

	pParent->ClientToScreen( RectIcone ) ;
	pWnd->AjusteRectangle( RectIcone ) ;

	pWnd->ShowWindow( SW_SHOW ) ;

	return pWnd ;
}

