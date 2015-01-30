///////////////////////////////////////////////////////////////////////////////
// CDirectDrawSurface
///////////////////////////////////////////////////////////////////////////////
#ifndef	__DIRECTDRAWSURFACE
#define	__DIRECTDRAWSURFACE

#ifndef __DDRAW_INCLUDED__
#include <ddraw.h>
#endif

class	CDirectDrawSurface
	{
	public :
		CDirectDrawSurface( LPDIRECTDRAW, int NbBackBuffers ) ;
		CDirectDrawSurface( LPDIRECTDRAW, int Largeur, int Hauteur, DWORD Flags = DDSCAPS_OFFSCREENPLAIN ) ;
		CDirectDrawSurface( LPDIRECTDRAW, const char * BitmapName ) ;
		CDirectDrawSurface( LPDIRECTDRAW, LPDIRECTDRAWSURFACE ) ;

		~CDirectDrawSurface() ;

	HRESULT	SetPalette(	LPDIRECTDRAWPALETTE ) ;
	HRESULT	Flip( LPDIRECTDRAWSURFACE, DWORD Flags ) ;
	HRESULT	BltFast( int x, int y, LPDIRECTDRAWSURFACE, int sx, int sy, int sw, int sh, DWORD Flag ) ;

	CDirectDrawSurface *	GetAttachedSurface() ;

	int		Width() const { return _Largeur ; } ;
	int		Height() const { return _Hauteur ; } ;

	operator LPDIRECTDRAWSURFACE( ) const { return _lpTheSurface ; } ;

	private :
		LPDIRECTDRAW		_lpDirectDraw ;
		LPDIRECTDRAWSURFACE _lpTheSurface ;
		int					_Largeur ;
		int					_Hauteur ;
	} ;

#endif