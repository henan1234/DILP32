///////////////////////////////////////////////////////////////////////////////
// Interface de la classe CRectAffichage
// Un objet de cette classe gere un ensemble de rectangles a afficher ou a
// effacer
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "RectAffichage.h"

#define	GRANULARITE						1000

HANDLE	CRectAffichage::_hWinG		=	0 ;
int		CRectAffichage::_NbObjets	=	0 ;

#define WINGAPI WINAPI
typedef BOOL (WINGAPI WinGBitBltProc)(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc,int nYOriginSrc );
typedef BOOL (WINGAPI WinGStretchBltProc)(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc, int nYOriginSrc,int nWidthSrc,int nHeightSrc );

WinGBitBltProc*		FastBitBlt		=	0 ;
WinGStretchBltProc*	FastStretchBlt	=	0 ;

/*
 *  Clear the System Palette so that we can ensure an identity palette 
 *  mapping for fast performance.
 */

void ClearSystemPalette(void)
	{
	//*** A dummy palette setup
	struct
		{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
		} Palette =
		{
		0x300,
			256
			};
		
		HPALETTE ScreenPalette = 0;
		HDC ScreenDC;
		int Counter;
		UINT nMapped = 0;
		BOOL bOK = FALSE;
		int  nOK = 0;
		
		//*** Reset everything in the system palette to black
		for(Counter = 0; Counter < 256; Counter++)
			{
			Palette.aEntries[Counter].peRed = 0;
			Palette.aEntries[Counter].peGreen = 0;
			Palette.aEntries[Counter].peBlue = 0;
			Palette.aEntries[Counter].peFlags = PC_NOCOLLAPSE;
			}
		
		//*** Create, select, realize, deselect, and delete the palette
		ScreenDC = GetDC(NULL);
		ScreenPalette = CreatePalette((LOGPALETTE *)&Palette);
		
		if (ScreenPalette)
			{
			ScreenPalette = SelectPalette(ScreenDC,ScreenPalette,FALSE);
			nMapped = RealizePalette(ScreenDC);
			ScreenPalette = SelectPalette(ScreenDC,ScreenPalette,FALSE);
			bOK = DeleteObject(ScreenPalette);
			}
		
		nOK = ReleaseDC(NULL, ScreenDC);
		
		return;
	}


///////////////////////////////////////////////////////////////////////
// Limitation de l'Espace
///////////////////////////////////////////////////////////////////////
void	CRectAffichage::Espace( const CRect & Esp )
	{
	_Espace	=	Esp ;
	_Espace.NormalizeRect() ;
	}

	
///////////////////////////////////////////////////////////////////////
// UnionValable
//	Decide si ca vaut le coup de combiner les deux rectangles pour
//	optimiser l'affichage
///////////////////////////////////////////////////////////////////////
inline BOOL	CRectAffichage::UnionValable( const CRect &	R1, const CRect & R2 )
	{
	RECT	R ;
	if ( ! ::IntersectRect(&R, R1, R2 ))
		return FALSE ;

	const	CRect	Union			=	R1 | R2 ;
	const	int		SurfaceUnion	=	Union.Width() * Union.Height() ;
	const	int		Surfaces		=	(R1.Width() * R1.Height()) + (R2.Height() * R2.Width()) ;

	// On retourne VRAI meme si les surfaces sont identique car un 
	// bitblt vaut mieux que 2
	return	SurfaceUnion <= Surfaces ;
	}

///////////////////////////////////////////////////////////////////////
// LimiteRect
//	Decide si ca vaut le coup de combiner les deux rectangles pour
//	optimiser l'affichage
///////////////////////////////////////////////////////////////////////
void	CRectAffichage::LimiteRect( CRect &	R, int * pX, int * pY ) const
{
	*pX	=	0 ;
	*pY	=	0 ;

	if ( _Espace.IsRectEmpty())
		{
		(*pX)	=	0 ;
		(*pY)	=	0 ;
		return ;
		}

	if ( pX )
		*pX	=	0 ;

	if ( pY )
		*pY	=	0 ;

	if ( R.left < _Espace.left )
		{
		if ( pX )
			*pX		=	_Espace.left - R.left ;
		R.left	=	_Espace.left ;
		if ( R.left > R.right )
			{
			R.SetRectEmpty() ;
			return ;
			}
		}

	if ( R.top < _Espace.top )
		{
		if ( pY )
			*pY		=	_Espace.top - R.top ;
		R.top	=	_Espace.top ;

		if ( R.top > R.bottom )
			{
			R.SetRectEmpty() ;
			return ;
			}
		}
	
	if ( R.right > _Espace.right )
		{
		R.right	=	_Espace.right ;
		if ( R.right < R.left )
			{
			R.SetRectEmpty() ;
			return ;
			}
		}
		

	if ( R.bottom > _Espace.bottom )
		{
		R.bottom	=	_Espace.bottom ;
		if ( R.bottom < R.top )
			{
			R.SetRectEmpty() ;
			return ;
			}
		}
}

///////////////////////////////////////////////////////////////////////
// Constructeurs/Destructeurs
///////////////////////////////////////////////////////////////////////
CRectAffichage::CRectAffichage()
	{
	_RectanglesOptimises	=	TRUE ;
	_Espace.SetRectEmpty() ;

	ResoudFonctions() ;
	
	_NbRects	=	0 ;
	//_pRects		=	(CRect*)malloc( sizeof( CRect )* GRANULARITE ) ;
	//_NbAlloues	=	GRANULARITE ;
	}

CRectAffichage::CRectAffichage( const CRectAffichage & Autre )
	{
	_RectanglesOptimises	=	TRUE ;
	_Espace	=	Autre._Espace ;

	(*this) += Autre ;

	ResoudFonctions() ;
	
	_NbRects	=	0 ;
	//_pRects		=	(CRect*)malloc( sizeof( CRect )* GRANULARITE ) ;
	//_NbAlloues	=	GRANULARITE ;
	}

CRectAffichage::CRectAffichage( const CRect & Esp )
	{
	_RectanglesOptimises	=	TRUE ;
	Espace( Esp ) ;
	ResoudFonctions() ;
	}

CRectAffichage::~CRectAffichage()
	{
	_NbObjets -- ;
	if ( _NbObjets == 0)
		FreeLibrary( (HINSTANCE)_hWinG ) ;

	//free( _pRects ) ;
	}

///////////////////////////////////////////////////////////////////////
// Ajout d'un rectangle a la liste
///////////////////////////////////////////////////////////////////////
void	CRectAffichage::Ajoute( const CRect & RAjoute )
	{
	if ( ! _Espace.IsRectEmpty())
		{
		// Verifier que le rectangle n'est pas completement en dehors de l'espace
		if ( RAjoute.right	< _Espace.left ||
			 RAjoute.left	> _Espace.right ||
			 RAjoute.top	> _Espace.bottom ||
			 RAjoute.bottom < _Espace.top )
			 return ;
		}
	
	for ( int i	 = 0; i < _NbRects; i++)
		{
		//if ( UnionValable( _pRects[i], RAjoute ))
		if ( UnionValable( _Rects[i], RAjoute ))
			{
			//_pRects[i]	|=	RAjoute ;
			CRect Nouveau	=	_Rects[i] | RAjoute ;

			// Supprime le rectangle
			memcpy( &_Rects[i], &_Rects[i+1], sizeof( CRect) * (_NbRects-i)) ;
			_NbRects -- ;

			// Ajoute ce nouveau rectangle
			Ajoute( Nouveau ) ;

			_RectanglesOptimises	=	FALSE ;
			return ;
			}
		}

	// Aucun rectangle valable n'a ete trouve, on l'ajoute a la fin
	/*
	if ( _NbRects + 1 >=	_NbAlloues )
		{
		_NbAlloues		=	(_NbRects+1+GRANULARITE) ;
		_pRects			=	(CRect*)realloc( _pRects, sizeof( CRect ) * _NbAlloues ) ;
		}
	
	*/
	if ( _NbRects >= MAX_RECTS )
		{
		_Rects[0]		|= RAjoute ;
		}
	else
		{
		//_pRects[_NbRects]	=	RAjoute ;
		//_NbRects ++ ;
		_Rects[	_NbRects]	= RAjoute ;
		_NbRects ++ ;
		}

	_RectanglesOptimises	=	FALSE ;
	}


///////////////////////////////////////////////////////////////////////
// Affichage des rectangles
///////////////////////////////////////////////////////////////////////
void CRectAffichage::BitBlt( HDC hDcDest, HDC hDcSrc, DWORD	RasterOp ) 
	{
	OptimiseRectangles() ;

	const	BOOL	Limite	=	! _Espace.IsRectEmpty() ;

	if ( (RasterOp	==	SRCCOPY) && FastBitBlt )
		// On peut utiliser WinG s'il est installe
		{
		for ( int i = 0; i < _NbRects; i++)
			{
			//CRect & R	=	_pRects[i] ;
			CRect R	=	_Rects[i] ;

			if ( Limite )			// A-t-on limite l'espace ?
				{
				int	DecalageX	;
				int	DecalageY	;

				LimiteRect( R, &DecalageX, &DecalageY ) ;

				FastBitBlt( hDcDest, R.left, R.top, R.Width(), R.Height(),
							hDcSrc, R.left+DecalageX, R.top+DecalageY ) ;
				}
			else
				FastBitBlt( hDcDest, R.left, R.top, R.Width(), R.Height(),
							hDcSrc, R.left, R.top ) ;
			}
		}
	else
		{
		for ( int i = 0; i < _NbRects; i++ )
			{
			//CRect	& R = _pRects[i] ;
			CRect R = _Rects[i] ;

			if ( Limite )			// A-t-on limite l'espace ?
				{
				int	DecalageX	;
				int	DecalageY	;

				LimiteRect( R, &DecalageX, &DecalageY ) ;

				::BitBlt( hDcDest, R.left, R.top, R.Width(), R.Height(),
						  hDcSrc, R.left+DecalageX, R.top+DecalageY, RasterOp ) ;
				}
			else
				::BitBlt( hDcDest, R.left, R.top, R.Width(), R.Height(),
						  hDcSrc, R.left, R.top, RasterOp ) ;
			}
		}
}

void CRectAffichage::PatBlt( HDC hDcDest, DWORD	RasterOp  )
	{
	OptimiseRectangles() ;

	const	BOOL	Limite	=	! _Espace.IsRectEmpty() ;

	for ( int i = 0; i < _NbRects; i++)
		{
		//CRect	& R=_pRects[i] ;
		CRect R = _Rects[i] ;

		if ( Limite )			// A-t-on limite l'espace ?
			{
			int	DecalageX	;
			int	DecalageY	;
			LimiteRect( R, &DecalageX, &DecalageY ) ;
			}

		::PatBlt(hDcDest, R.left, R.top, R.Width(), R.Height(), RasterOp ) ;
		}
	}

void CRectAffichage::FillRect( HDC hDcDest, COLORREF Couleur )
	{
	OptimiseRectangles() ;

	HBRUSH		hBrosse		=	CreateSolidBrush( Couleur ) ;
	const	BOOL	Limite	=	! _Espace.IsRectEmpty() ;

	for ( int i = 0; i < _NbRects; i++)
		{
		//CRect	& R	=	_pRects[i] ;
		CRect R = _Rects[i] ;

		if ( Limite )			// A-t-on limite l'espace ?
			{
			int	DecalageX	;
			int	DecalageY	;
			LimiteRect( R, &DecalageX, &DecalageY ) ;
			}

		::FillRect( hDcDest, R, hBrosse ) ;
		}

	DeleteObject( hBrosse ) ;
	}


///////////////////////////////////////////////////////////////////////
// Vidage des rectangles
///////////////////////////////////////////////////////////////////////
void	CRectAffichage::Vide()
	{
	_NbRects	=	0 ;
	}

			

///////////////////////////////////////////////////////////////////////
// Combinaison de deux listes de rectangles
///////////////////////////////////////////////////////////////////////
void CRectAffichage::operator +=( const CRectAffichage & ListeAjoute )
{
	for ( int i = 0; i < ListeAjoute._NbRects; i++ )
//		Ajoute( ListeAjoute._pRects[i] ) ;
		Ajoute( ListeAjoute._Rects[i] ) ;
}

void CRectAffichage::ResoudFonctions( void )
{
	_NbObjets ++ ;

	if ( _NbObjets == 1 )
		{
		_hWinG = LoadLibrary("WING32");
		if (_hWinG)
			{
			ClearSystemPalette() ;

			FastBitBlt		= (WinGBitBltProc*)		GetProcAddress((HINSTANCE)_hWinG,"WinGBitBlt");
			FastStretchBlt	= (WinGStretchBltProc*)	GetProcAddress((HINSTANCE)_hWinG, "WinGStretchBlt");
			}
		else
			{
			// Pas de WInG, on utilisera GDI
			FastBitBlt		=	0 ;
			FastStretchBlt	=	0 ;
			}
		}
	}


void	CRectAffichage::operator =( const CRectAffichage & Autre)
{
	_Espace		=	Autre._Espace ;
//	free( _pRects ) ;

//	_pRects		=	(CRect*)malloc( sizeof( CRect ) * Autre._NbAlloues ) ;
//	memcpy( _pRects, Autre._pRects, sizeof( CRect ) * Autre._NbRects ) ;
	memcpy( _Rects, Autre._Rects, sizeof( CRect ) * Autre._NbRects ) ;

	_NbRects	=	Autre._NbRects ;
//	_NbAlloues	=	Autre._NbAlloues ;

	_RectanglesOptimises	=	Autre._RectanglesOptimises ;
}

///////////////////////////////////////////////////////////////////////////////
// Les rectangles ont ete ajoutes un par un avec une optimisation au coup par
// coup
//	Avant de faire l'affichage global, on va tenter une derniere optimisation
///////////////////////////////////////////////////////////////////////////////
void CRectAffichage::OptimiseRectangles()
{
/*	if ( _RectanglesOptimises )
		return ;

	for ( int i = 0; i < _NbRects; i++)
		{
		CRect & r1	=	_Rects[i] ;

		for ( int j = i+1; j < _NbRects; j++)
			{
			CRect & r2	=	_Rects[j] ;

			if ( UnionValable( r1, r2 ))
				{
				// r1 et r2 sont des references, on fait donc la modif
				// directement dans le tableau
				r1 |= r2 ;
			
				// Supprime le tableau
				memcpy( &_Rects[j], &_Rects[j+1], sizeof( CRect ) * (_NbRects-j-1)) ;
				_NbRects -- ;
				}	
			}
		}

	_RectanglesOptimises	=	TRUE ;
*/
}
