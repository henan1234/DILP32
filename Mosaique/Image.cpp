// Image.cpp: implementation of the CImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mosaique.h"
#include "Image.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImage::CImage( LPCSTR	pBitmapName )
{
	_Nom	=	pBitmapName ;
	

	_hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(), pBitmapName,
									IMAGE_BITMAP, 0,0, LR_LOADFROMFILE ) ;

	if ( _hBitmap )
		{
		BITMAP	sBitmap ;
		GetObject( _hBitmap, sizeof( sBitmap ), &sBitmap ) ;

		_Taille.cx	=	sBitmap.bmWidth ;
		_Taille.cy	=	sBitmap.bmHeight ;
		}
	else
		throw( new CNotSupportedException )  ;
}

CImage::~CImage()
{
	DeleteObject() ;
}

const CString & CImage::Nom()
{
	return _Nom ;
}

CSize CImage::Taille()
{	
	return _Taille ;
}

int CImage::Largeur()
{
	return _Taille.cx ;
}

int CImage::Hauteur()
{
	return _Taille.cy ;
}

HBITMAP CImage::Handle()
{
	if ( ! _hBitmap )
		_hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(), _Nom,
									IMAGE_BITMAP, 0,0, LR_LOADFROMFILE ) ;

	return _hBitmap ;
}

void CImage::DeleteObject()
{
	if ( _hBitmap )
		{
		::DeleteObject( _hBitmap ) ;
		_hBitmap	=	0 ;
		}
}


void	CImage::Dessine( CDC & Dc, int x, int y, double FacteurZoom )
	{
	if ( ! _hBitmap )
		{
		_hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(), _Nom,
									IMAGE_BITMAP, 0,0, LR_LOADFROMFILE ) ;
		}

	CSize	Taille ;
	Taille.cx	=	(int)(_Taille.cx * FacteurZoom) ;
	Taille.cy	=	(int)(_Taille.cy * FacteurZoom) ;

	CDC	MemDC ;
	MemDC.CreateCompatibleDC( NULL ) ;
	HBITMAP hOldBitmap	=	(HBITMAP)SelectObject( MemDC, _hBitmap ) ;

	Dc.StretchBlt( x, y, Taille.cx, Taille.cy,
				   &MemDC, 0, 0, _Taille.cx, _Taille.cy,
				   SRCCOPY ) ;

	SelectObject( MemDC, hOldBitmap ) ;
	DeleteDC( MemDC ) ;
	}


void CImage::Dessine(CDC & Dc, int x, int y, int l, int h, int Centre )
{
	const double FacteurX	=	(double)l / (double)(_Taille.cx) ;
	const double FacteurY	=	(double)h / (double)_Taille.cy ;
	const double Facteur	=	min( FacteurX, FacteurY ) ;

	const int	L	=	(int)(_Taille.cx * Facteur) ;
	const int	H	=	(int)(_Taille.cy * Facteur) ;


	if ( ! _hBitmap )
		{
		_hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(), _Nom,
									IMAGE_BITMAP, 0,0, LR_LOADFROMFILE ) ;
		}

	CDC	MemDC ;
	MemDC.CreateCompatibleDC( NULL ) ;
	HBITMAP hOldBitmap	=	(HBITMAP)SelectObject( MemDC, _hBitmap ) ;

	if ( Centre & CENTREH )
		x	+= (l-L)/2 ;

	if ( Centre & CENTREV )
		y += (h-H) /2 ;

	Dc.StretchBlt( x, y, L, H,
				   &MemDC, 0, 0, _Taille.cx, _Taille.cy,
				   SRCCOPY ) ;

	SelectObject( MemDC, hOldBitmap ) ;
	DeleteDC( MemDC ) ;}
