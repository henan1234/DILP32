///////////////////////////////////////////////////////////////////////////////
// CIconeHorloge
//	Derivee de CIconePeriodique
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winnls.h>
#include "resource.h"
#include "IconeHorloge.h"
#include "jibe96view.h"
#include "lpibitmap.h"

#define MINUTES		0
#define SECONDES	1
IMPLEMENT_SERIAL( CIconeHorloge, CIconePeriodique, 0 ) ;

CIconeHorloge::CIconeHorloge()
:_Mode( SECONDES ),
_DerniereHeure( CTime::GetCurrentTime()) 
{
}

void CIconeHorloge:: Update( void )
{
	// Mise a jour de l'heure
	CTime	Maintenant( CTime::GetCurrentTime());

	BOOL	Egal = Maintenant == _DerniereHeure ;

	if ( ! Egal )
		if ( _Mode == MINUTES )
			{
			Egal	=	( _DerniereHeure.GetHour() == Maintenant.GetHour())
						&& (_DerniereHeure.GetMinute() == Maintenant.GetMinute()) ;
			}

	if ( ! Egal )
		{
		CJibe96View::UpdateIcon( this ) ;
		_DerniereHeure	= Maintenant ;
		}
}

void CIconeHorloge::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	ASSERT_VALID( this ) ;
	
	switch ( _Mode )
		{
		case MINUTES :
		case SECONDES :
			{
			CLPIBitmap	Bitmap( Colors64K() ? IDB_HORLOGE : IDB_HORLOGE16 ) ;
			Bitmap.Affiche( &Dc, Pt.x, Pt.y ) ;

			CRect	R( Pt, Bitmap.Taille() ) ;
			R.DeflateRect( 4, 4 ) ;

			// Affiche le texte
			char	Texte[100] ;

			SYSTEMTIME	SystemTime ;
			GetLocalTime( &SystemTime ) ;
			if ( _Mode == SECONDES )
				GetTimeFormat( LOCALE_USER_DEFAULT, 0, &SystemTime, NULL, Texte, sizeof( Texte )) ;
			else
				GetTimeFormat( LOCALE_USER_DEFAULT, TIME_NOSECONDS, &SystemTime, NULL, Texte, sizeof( Texte )) ;
				
			CFont	F ;
			F.CreateFont( - R.Height(),
							R.Width() / (lstrlen(Texte)+1),
						  0,0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
						  OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
						  DRAFT_QUALITY, VARIABLE_PITCH | TMPF_TRUETYPE | FF_DONTCARE,
						  "Arial" ) ;
			CFont* pOldFont	=	Dc.SelectObject( &F ) ;
			const int m = Dc.SetBkMode( TRANSPARENT ) ;
			Dc.SetTextColor( RGB( 0xFF, 0xFF, 0xFF) ) ;
			R.OffsetRect( 1, 1 ) ;
			Dc.DrawText( Texte, -1, R, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE ) ;
			Dc.SetTextColor( RGB( 0x80, 0x80, 0x80) ) ;
			R.OffsetRect( -2, -2 ) ;
			Dc.DrawText( Texte, -1, R, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE ) ;
			Dc.SetTextColor( RGB( 0x00, 0x00, 0x00) ) ;
			R.OffsetRect( 1, 1 ) ;
			Dc.DrawText( Texte, -1, R, DT_CENTER | DT_VCENTER | DT_NOPREFIX | DT_SINGLELINE ) ;
			Dc.SetBkMode( m ) ;
			
			Dc.SelectObject( pOldFont ) ;
			F.DeleteObject() ;
			}
			break ;
		
	default :
		ASSERT( FALSE ) ;
	}
}

HRGN CIconeHorloge::Region( CPoint Decalage ) const
	{
	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( Colors64K() ? IDB_HORLOGE : IDB_HORLOGE16 ) ;
	BITMAP	sBitmap ;
	Bitmap.GetObject( sizeof( sBitmap ), &sBitmap ) ;
	Bitmap.DeleteObject() ;

	return CreateRectRgn( Decalage.x, Decalage.y,
						  Decalage.x + sBitmap.bmWidth,
						  Decalage.y + sBitmap.bmHeight ) ;
	}
	

UINT CIconeHorloge::GetMenuID( void ) const
{
	return IDR_MENU_HORLOGE ;
}

BOOL CIconeHorloge::ExecuteCommand( void )
{
	switch( _Mode )
		{
		case SECONDES :
			_Mode	=	MINUTES ;
			break ;

		case MINUTES :
			_Mode	=	SECONDES ;
			break ;

		}

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// ExecuteCommand
//	Gestion du menu contextuel de l'icone
///////////////////////////////////////////////////////////////////////////////
BOOL CIconeHorloge::ExecuteCommand( UINT Commande )
{
	switch( Commande )
		{
		case ID_HORLOGE_CHANGERLHEURE :
			///////////////////////////////////////////////////////////////////
			// Lancement du module du panneau de controle qui permet de regler
			// l'heure
			///////////////////////////////////////////////////////////////////
			WinExec( "CONTROL.EXE TIMEDATE.CPL", SW_SHOWDEFAULT ) ;
			break ;

		default :
			return FALSE ;
		}

	return TRUE ;
}
void	CIconeHorloge::Serialize( CArchive & ar )
	{
	CIconePeriodique::Serialize( ar ) ;
	if ( ar.IsStoring())
		ar << _Mode ;
	else
		ar >> _Mode ;
	}


IMPLEMENT_SERIAL( CIconeDate, CIconePeriodique, 0 ) ;

CIconeDate::CIconeDate()
:_FormatLong( TRUE ),
_DerniereDate( CTime::GetCurrentTime()) 
{
}

void CIconeDate:: Update( void )
{
	// Mise a jour de la date
	CTime	Maintenant( CTime::GetCurrentTime());
	
	BOOL	Egal = (Maintenant.GetYear() == _DerniereDate.GetYear()) &&
				   (Maintenant.GetMonth() == _DerniereDate.GetMonth()) &&
				   (Maintenant.GetDay() == _DerniereDate.GetDay()) ;

	if ( ! Egal )
		{
		CJibe96View::UpdateIcon( this ) ;
		_DerniereDate	= Maintenant ;
		}
}

void CIconeDate::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	ASSERT_VALID( this ) ;
	
	// Affichage du fond
	CLPIBitmap Bitmap( Colors64K() ? IDB_DATE : IDB_DATE16 ) ;
	Bitmap.Affiche( &Dc, Pt.x, Pt.y ) ;

	CRect	R( Pt, CSize( Bitmap.Largeur(), Bitmap.Hauteur() )) ;

	// Affiche le texte
	char	Texte[100] ;

	SYSTEMTIME	SystemTime ;
	GetLocalTime( &SystemTime ) ;
	CFont	F ;
	DWORD	Style ;

	R.InflateRect( -2, -2 ) ;


	if ( _FormatLong )
		{
		GetDateFormat( LOCALE_USER_DEFAULT,DATE_LONGDATE,
					   &SystemTime,NULL,Texte,sizeof( Texte )) ;
		F.CreateFont( (R.Height()/3), - R.Width()/ (lstrlen(Texte)/2),
				  0,0, FW_BOLD,FALSE, FALSE, FALSE,
				  ANSI_CHARSET,OUT_DEFAULT_PRECIS,
				  CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
				  VARIABLE_PITCH | TMPF_TRUETYPE | FF_DONTCARE,
				  "Arial" ) ;
		Style	=	DT_CENTER | DT_TOP | DT_WORDBREAK ;
		}
	else
		{
		GetDateFormat( LOCALE_USER_DEFAULT,DATE_SHORTDATE,
					   &SystemTime,NULL,Texte,sizeof( Texte )) ;
		F.CreateFont( - R.Height()/2, - R.Width()/ lstrlen(Texte)+2,
				  0,0, FW_BOLD,FALSE, FALSE, FALSE,
				  ANSI_CHARSET,OUT_DEFAULT_PRECIS,
				  CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
				  VARIABLE_PITCH | TMPF_TRUETYPE | FF_DONTCARE,
				  "Arial" ) ;
		Style	=	DT_CENTER | DT_VCENTER | DT_SINGLELINE ;
		}
	
	
	CFont* pOldFont	=	Dc.SelectObject( &F ) ;
	const int m = Dc.SetBkMode( TRANSPARENT ) ;
	Dc.SetTextColor( RGB( 0xFF, 0xFF, 0xFF) ) ;
	R.OffsetRect( 1, 1 ) ;
	Dc.DrawText( Texte, -1, R, Style ) ;
	Dc.SetTextColor( RGB( 0x80, 0x80, 0x80) ) ;
	R.OffsetRect( -2, -2 ) ;
	Dc.DrawText( Texte, -1, R, Style ) ;
	Dc.SetTextColor( RGB( 0x00, 0x00, 0x00) ) ;
	R.OffsetRect( 1, 1 ) ;
	Dc.DrawText( Texte, -1, R, Style ) ;
	Dc.SetBkMode( m ) ;
	
	Dc.SelectObject( pOldFont ) ;
	F.DeleteObject() ;

	if ( Selectionnee )
		{
		R.InflateRect( -1, -1 ) ;
		Dc.DrawFocusRect( R ) ;
		}
}

HRGN CIconeDate::Region( CPoint Decalage ) const
	{
	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( Colors64K() ? IDB_DATE : IDB_DATE16) ;
	BITMAP	sBitmap ;
	Bitmap.GetObject( sizeof( sBitmap ), &sBitmap ) ;
	Bitmap.DeleteObject() ;

	return CreateRectRgn( Decalage.x, Decalage.y,
						  Decalage.x + sBitmap.bmWidth,
						  Decalage.y + sBitmap.bmHeight ) ;
	}
	

UINT CIconeDate::GetMenuID( void ) const
{
	return IDR_MENU_DATE ;
}

BOOL CIconeDate::ExecuteCommand( void )
{
	_FormatLong	=	! _FormatLong ;
	return TRUE ;
}


///////////////////////////////////////////////////////////////////////////////
// ExecuteCommand
//	Gestion du menu contextuel de l'icone
///////////////////////////////////////////////////////////////////////////////
BOOL CIconeDate::ExecuteCommand( UINT Commande )
{
	switch( Commande )
		{
		case ID_HORLOGE_CHANGERLHEURE :
			///////////////////////////////////////////////////////////////////
			// Lancement du module du panneau de controle qui permet de regler
			// la date
			///////////////////////////////////////////////////////////////////
			WinExec( "CONTROL.EXE TIMEDATE.CPL", SW_SHOWDEFAULT ) ;
			break ;

		default :
			return FALSE ;
		}

	return TRUE ;
}

void	CIconeDate::Serialize( CArchive & ar )
	{
	CIconePeriodique::Serialize( ar ) ;

	if (ar.IsStoring())
		ar << _FormatLong ;
	else
		ar >> _FormatLong ;

	}

CString CIconeDate::GetTip( void )
{
	char	Texte[1024] ;
	SYSTEMTIME	SystemTime ;
	GetLocalTime( &SystemTime ) ;
	GetDateFormat( LOCALE_USER_DEFAULT,DATE_LONGDATE,
				   &SystemTime,NULL,Texte,sizeof( Texte )) ;
	return	Texte ;
}

CString CIconeHorloge::GetTip( void )
{
	char	Texte[1024] ;
	SYSTEMTIME	SystemTime ;
	GetLocalTime( &SystemTime ) ;
	GetTimeFormat( LOCALE_USER_DEFAULT,
				   0,
				   &SystemTime,
				   NULL,
				   Texte,
				   sizeof( Texte )) ;

	return Texte ;
}

