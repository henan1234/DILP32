///////////////////////////////////////////////////////////////////////////////
// CLPIMemDC
//	DC en memoire avec une bitmap de taille donnee
///////////////////////////////////////////////////////////////////////////////
#ifndef __AFXWIN_H__
#include <afxwin.h>
#endif
#include "lpidc.h"

CLPIMemDC::CLPIMemDC( CDC & DCCompatible, int	Largeur, int Hauteur )
{
	VERIFY( CreateCompatibleDC( &DCCompatible )) ;
	
	_pBitmapCreee	=	new CBitmap ;
	ASSERT( _pBitmapCreee );	
	VERIFY( _pBitmapCreee->CreateCompatibleBitmap( &DCCompatible,
													Largeur, Hauteur )) ;
	
	_pOldBitmap	=	SelectObject( _pBitmapCreee ) ;
	ASSERT( _pOldBitmap ) ;
	
	ASSERT_VALID( this ) ;
}

CLPIMemDC::CLPIMemDC( CDC & DCCompatible, 
					  int Largeur, int Hauteur,
					  int BitsPixels, int Plans, LPBYTE lpBytes )
{
	VERIFY( CreateCompatibleDC( &DCCompatible )) ;

	_pBitmapCreee	=	new CBitmap ;
	ASSERT( _pBitmapCreee );	
	VERIFY( _pBitmapCreee->CreateBitmap( Largeur, Hauteur, Plans, BitsPixels, lpBytes )) ;
	_pOldBitmap		=	SelectObject( _pBitmapCreee ) ;
	
	ASSERT( _pOldBitmap ) ;
	ASSERT_VALID( this ) ;
}

CLPIMemDC::CLPIMemDC( CDC & DCCompatible, CBitmap & Bitmap )
{
	ASSERT_VALID( &DCCompatible ) ;
	ASSERT_VALID( &Bitmap ) ;
	
	VERIFY( CreateCompatibleDC( &DCCompatible )) ;
	_pOldBitmap		=	SelectObject( &Bitmap ) ;
	
	// la bitmap vient de l'exterieur, ne pas la detruire !
	_pBitmapCreee	=	0 ;
	ASSERT_VALID( this ) ;
}
		
CLPIMemDC::CLPIMemDC( CBitmap & Bitmap )
{
	ASSERT_VALID( &Bitmap ) ;
	
	VERIFY( CreateCompatibleDC( NULL )) ;
	_pOldBitmap		=	SelectObject( &Bitmap ) ;
	
	// la bitmap vient de l'exterieur, ne pas la detruire !
	_pBitmapCreee	=	0 ;
	ASSERT_VALID( this ) ;
}
		
CLPIMemDC::~CLPIMemDC()
{	
	ASSERT_VALID( this ) ;
	
	if ( _pOldBitmap )
		{
		ASSERT_VALID( _pOldBitmap ) ;
		SelectObject( _pOldBitmap ) ;
		}
		
	if ( _pBitmapCreee )
		{
		ASSERT_VALID( _pBitmapCreee ) ;
		_pBitmapCreee->DeleteObject() ;
		delete	_pBitmapCreee ;
		}
		
	DeleteDC() ;
}

#ifdef _DEBUG
void	CLPIMemDC::AssertValid( void ) const
{
	ASSERT( this ) ;
	CDC::AssertValid() ;
	ASSERT( _pOldBitmap ) ;
	
	ASSERT( m_hDC ) ;
}
#endif
		
