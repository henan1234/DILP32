///////////////////////////////////////////////////////////////////////////////
// CDirectDrawSurface
///////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"
#include <ddraw.h>
#include "DirectDrawSurface.h"


CDirectDrawSurface::CDirectDrawSurface( LPDIRECTDRAW lpDD , int NbBackBuffers )
	{
	ASSERT( lpDD ) ;

	_lpDirectDraw	=	lpDD ;

	DDSURFACEDESC ddsd ;

	ddsd.dwSize		=	sizeof( ddsd ) ;
	ddsd.dwFlags	=	DDSD_CAPS ;
	ddsd.ddsCaps.dwCaps	=	DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP ;
	ddsd.dwBackBufferCount	=	NbBackBuffers ;


	_lpDirectDraw->CreateSurface( &ddsd, &_lpTheSurface, NULL ) ;
	}

CDirectDrawSurface::CDirectDrawSurface( LPDIRECTDRAW, int Largeur, int Hauteur, DWORD Flags )
	{
	}

CDirectDrawSurface::CDirectDrawSurface( LPDIRECTDRAW, const char * BitmapName )
	{
	}

CDirectDrawSurface::CDirectDrawSurface( LPDIRECTDRAW lpDD, LPDIRECTDRAWSURFACE lpSurface )
	{
	ASSERT( lpDD ) ;
	ASSERT( lpSurface ) ;

	_lpDirectDraw	=	lpDD ;
	_lpTheSurface	=	lpSurface ;
	}

CDirectDrawSurface::~CDirectDrawSurface() 
	{
	_lpTheSurface->Release() ;
	}

HRESULT	CDirectDrawSurface::SetPalette(	LPDIRECTDRAWPALETTE lpPalette )
	{
	ASSERT( lpPalette ) ;
	ASSERT( _lpDirectDraw ) ;
	ASSERT( _lpTheSurface ) ;

	return _lpTheSurface->SetPalette( lpPalette ) ;
	}

HRESULT	CDirectDrawSurface::Flip( LPDIRECTDRAWSURFACE lpSurface, DWORD Flags )
	{
	ASSERT( _lpDirectDraw ) ;
	ASSERT( _lpTheSurface ) ;

	return _lpTheSurface->Flip( lpSurface, Flags ) ;
	}

HRESULT	CDirectDrawSurface::BltFast( int x, int y, LPDIRECTDRAWSURFACE lpSurface, int sx, int sy, int sw, int sh, DWORD Flag )
	{
	ASSERT( _lpDirectDraw ) ;
	ASSERT( _lpTheSurface ) ;

	CRect	R( sx, sy, sx+sw, sy+sh ) ;

	return _lpTheSurface->BltFast( x, y, lpSurface, R, Flag ) ;
	}

CDirectDrawSurface *	CDirectDrawSurface::GetAttachedSurface()
	{
	ASSERT( _lpDirectDraw ) ;
	ASSERT( _lpTheSurface ) ;

	DDSCAPS	DdsCaps ;
	LPDIRECTDRAWSURFACE lpSurface ;

	DdsCaps.dwCaps	=	DDSCAPS_BACKBUFFER ;

	_lpTheSurface->GetAttachedSurface( &DdsCaps, &lpSurface ) ;

	return & CDirectDrawSurface( _lpDirectDraw, lpSurface ) ;
	}

