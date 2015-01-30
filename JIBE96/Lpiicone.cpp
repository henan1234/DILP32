///////////////////////////////////////////////////////////////////////////////
// Classe CLpiIcone
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "LpiIcone.h"
#include "LpiBitmap.h"


CLPIIcone::CLPIIcone( WORD IdRessource )
{
	_hIcone	=	LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE(IdRessource) ) ;
	_FautDetruire	=	TRUE ;
}

CLPIIcone::CLPIIcone( LPCSTR	ResourceName )
{
	_hIcone	=	LoadIcon( AfxGetResourceHandle(), ResourceName ) ;
	_FautDetruire	=	TRUE ;
}

CLPIIcone::CLPIIcone( CWnd * pWnd )
{
	_hIcone	=	(HICON)GetClassLong( pWnd->m_hWnd, GCL_HICON ) ;
	_FautDetruire	=	FALSE ;
}

CLPIIcone::CLPIIcone( LPCSTR	ExeName, int Indice  )
{
	_hIcone	=	ExtractIcon( AfxGetInstanceHandle(), ExeName, Indice ) ;
	_FautDetruire	=	TRUE ;
}

CLPIIcone::CLPIIcone( HICON	hIcone, BOOL Effacer  )
{
	_hIcone	=	hIcone ;
	_FautDetruire	=	Effacer ;
}

CLPIIcone::~CLPIIcone()
{
	if ( _FautDetruire )
		DestroyIcon( _hIcone ) ;
}

CLPIIcone::operator HICON( void ) const
{
	if ( _hIcone )
		return _hIcone ;
	else
		return	LoadIcon( NULL, IDI_QUESTION ) ;
}

CSize	CLPIIcone::Taille( void ) 
{
	return CSize( ::GetSystemMetrics( SM_CXICON ),
				  ::GetSystemMetrics( SM_CYICON )) ;
}

int		CLPIIcone::Largeur( void )
{
	return ::GetSystemMetrics( SM_CXICON ) ;
}


int		CLPIIcone::Hauteur( void )
{   return ::GetSystemMetrics( SM_CYICON ) ;
}

HRGN	CLPIIcone::CreateRegion( BOOL	Exterieur )
{
	// Creer une bitmap a partir de l'icone
	CLPIBitmap	Bitmap ;
	Bitmap.CreateBitmap( Largeur(), Hauteur(), 1, 1, NULL ) ;
	
	// Dessiner l'icone dans la bitmap
	HDC		hMemDC ;
	HGDIOBJ	hOld ;
	hMemDC	=	CreateCompatibleDC( NULL ) ;
	hOld	=	SelectObject( hMemDC, Bitmap.m_hObject ) ;
	DrawIconEx( hMemDC, 0, 0, _hIcone, GetSystemMetrics( SM_CXICON ), GetSystemMetrics( SM_CYICON ), 0, 0, DI_MASK) ;
	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;

	// Calculer la region
	HRGN hRegion	=	Bitmap.CreateRegion( Exterieur ? RGB(0,0,0) : RGB( 255, 255, 255 ) ) ;
	
	return hRegion ;
}

