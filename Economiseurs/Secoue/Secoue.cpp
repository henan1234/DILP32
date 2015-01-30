#include "..\stdafx.h"

#include "secoue.h"

CSecoue	LEconomiseur( "Secoue l'ecran", "�0�897" ) ;

HDC	hDCOriginal ;
HBITMAP	hBitmapOriginal, hOldOriginal ;
HDC	hDCMemoire ;
HBITMAP	hBitmapMemoire, hOldBitmap ;
DWORD	RasterOp	=	SRCCOPY ;

CSecoue::CSecoue( const CString & NomEconomiseur, const CString & ValeurEnregistre )
:CEconomiseur( NomEconomiseur, ValeurEnregistre )
	{
	}

CSecoue::~CSecoue()
	{
	}

void CSecoue::InitSave( HWND	hWnd )
	{
	CEconomiseur::InitSave( hWnd ) ;

	HDC	hDC				=	CreateDC( "display", 0, 0, 0 ) ;
	hDCMemoire			=	CreateCompatibleDC( hDC ) ;
	hDCOriginal			=	CreateCompatibleDC( hDC ) ;
	hBitmapOriginal		=	CreateCompatibleBitmap( hDC, Largeur, Hauteur ) ;
	DeleteDC( hDC ) ;

	CBitmap * pBitmap	=	MemoriseEcran(Largeur, Hauteur ) ;

	hBitmapMemoire	=	(HBITMAP)*pBitmap ;
	hOldBitmap	=	(HBITMAP)SelectObject( hDCMemoire, hBitmapMemoire ) ;

	hOldOriginal	=	(HBITMAP)SelectObject( hDCOriginal, hBitmapOriginal ) ;

	BitBlt( hDCOriginal, 0, 0, Largeur, Hauteur, hDCMemoire, 0, 0, SRCCOPY ) ;


	SetTimer( hWnd, 1, 10000, NULL ) ;
	}

void CSecoue::Configuration( CPropertySheet * )
	{
	}

void CSecoue::Animation( CDC&	Dc )
	{
	int	x	=	Alea( 0, Largeur - 50 ) ;
	int	y	=	Alea( 0, Hauteur - 50 ) ;
	int	l	=	Alea( 50, 300 ) ;
	int	h	=	Alea( 50, 300 ) ;

	int dx	=	Alea( -2, 2 ) ;
	int dy	=	Alea( -2, 2 ) ;

	BitBlt( hDCMemoire, x, y, l, h, hDCMemoire, x+dx, y+dy, SRCCOPY ) ;
	BitBlt( Dc.m_hDC, x, y, l, h, hDCMemoire, x, y, RasterOp ) ;
	}
void CSecoue::InitDC( CDC & ) 
	{
	}

void CSecoue::FinDC( CDC & )
	{
	SelectObject( hDCMemoire, hOldBitmap ) ;
	DeleteDC( hDCMemoire ) ;
	DeleteObject( hBitmapMemoire ) ;

	SelectObject ( hDCOriginal, hOldOriginal ) ;
	DeleteDC( hDCOriginal ) ;
	DeleteObject( hBitmapOriginal ) ;
	}

void CSecoue::Preferences()
	{
	}
void CSecoue::ValidePreferences()
	{
	}

void	CSecoue::PeintFenetre( CDC & Dc, const CRect& R)
{
	BitBlt( Dc.m_hDC, R.left, R.top, R.Width(), R.Height(), hDCMemoire, R.left, R.top, SRCCOPY ) ;
}


void CSecoue::OnTimer( UINT IdTimer )
	{
	switch( Alea( 1, 3 ))
		{
		case 1 :	RasterOp	=	SRCCOPY ; break ;
		case 2 :	RasterOp	=	SRCAND; break ;
		case 3 :	RasterOp	=	SRCPAINT ; break ;
		}

	BitBlt( hDCMemoire, 0, 0, Largeur, Hauteur, hDCOriginal, 0, 0, SRCCOPY ) ;
	InvalidateRect( _hWnd, NULL, FALSE ) ;
	SetTimer( _hWnd, 1, 1000 * Alea( 1, 30 ), NULL ) ;
	}