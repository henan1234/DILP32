///////////////////////////////////////////////////////////////////////////////
// Bulles
///////////////////////////////////////////////////////////////////////////////
#include "glouglou.h"
#include "..\specif.h"
///////////////////////////////////////////////////////////////////////////////
//	TYPES
///////////////////////////////////////////////////////////////////////////////
typedef struct
	{
    POINT		Position ;
    int			Montee ;
    WORD		NoImage ;
	int			Largeur ;
	int			Hauteur ;
	COLORREF	Couleur ;
	}
	T_BULLE ;

T_BULLE	Bulles[NB_MAX_BULLES ] ;
int		NbBulles ;
int		NbMaxBulles ;

///////////////////////////////////////////////////////////////////////////////
// Efface une bulle de l'ecran
///////////////////////////////////////////////////////////////////////////////
static void EffaceBulle( HDC hDC, T_BULLE * pBulle)
{
	HDC	hTempDC ;
	HBITMAP	hTempBitmap ;
	HBITMAP	hOld ;

	hTempDC		=	FastCreateDC( ) ;
	hTempBitmap	=	CreateCompatibleBitmap( hDC, pBulle->Largeur, pBulle->Hauteur ) ;
	hOld		=	SelectObject( hTempDC, hTempBitmap ) ;

	/////////////////////////////////////////////////////////////////////////
	FastBitBlt( hTempDC, 0, 0, pBulle->Largeur, pBulle->Hauteur,
			hDCEcran, pBulle->Position.x, pBulle->Position.y ) ;
					
	{
	HDC	hMemDC ;
	HBITMAP	hBm, hOld ;

	hMemDC	=	FastCreateDC( ) ;
	hBm		=	CreateBitmap( pBulle->Largeur, pBulle->Hauteur, 1, 1, 0 ) ;
	hOld	=	SelectObject( hMemDC, hBm ) ;
	PatBlt( hMemDC, 0, 0, pBulle->Largeur, pBulle->Hauteur, WHITENESS ) ;
	
	SetBkColor( hTempDC, CouleurLiquide ) ;
	BitBlt( hTempDC, 0,0, pBulle->Largeur, pBulle->Hauteur,
			hMemDC, 0,0, SRCAND ) ;

	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;
	DeleteObject( hBm ) ;
	}	
	
	FastBitBlt(	hDC, pBulle->Position.x, pBulle->Position.y, pBulle->Largeur, pBulle->Hauteur,
					hTempDC, 0, 0 ) ;

	SelectObject( hTempDC, hOld ) ;
	DeleteDC( hTempDC ) ;
	DeleteObject( hTempBitmap );

}

///////////////////////////////////////////////////////////////////////////////
// Affiche une bulle
///////////////////////////////////////////////////////////////////////////////
static	void	AfficheBulle( HDC hDC, T_BULLE *	pBulle )
{
	HDC	hMemDC ;
	HBITMAP	hBitmapBulle ;
	HBITMAP	hOld ;

	SetTextColor( hDC, 0 ) ;
	SetBkColor( hDC, pBulle->Couleur ) ;
	
	hBitmapBulle	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE(	IDB_BULLE1 + pBulle->NoImage )) ;

	hMemDC	=	FastCreateDC(  ) ;
	hOld	=	SelectObject( hMemDC, hBitmapBulle ) ;

	BitBlt( hDC, pBulle->Position.x, pBulle->Position.y, pBulle->Largeur, pBulle->Hauteur,
			hMemDC, 0, 0, SRCPAINT ) ;

	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;
	DeleteObject( hBitmapBulle ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Eclate une bulle
///////////////////////////////////////////////////////////////////////////////
static	void	EclateBulle( HDC hDC, T_BULLE *	pBulle )
{
	HDC	hMemDC ;
	HBITMAP	hBitmapBulle ;
	HBITMAP	hOld ;

	SetTextColor( hDC, 0 ) ;
	
	hBitmapBulle	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE(	IDB_ECLATE1 + pBulle->NoImage )) ;

	hMemDC	=	FastCreateDC( ) ;
	hOld	=	SelectObject( hMemDC, hBitmapBulle ) ;

	BitBlt( hDC, pBulle->Position.x, pBulle->Position.y, pBulle->Largeur, pBulle->Hauteur, 
			hMemDC, 0, 0, SRCPAINT ) ;


	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;
	DeleteObject( hBitmapBulle ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Monte une bulle
///////////////////////////////////////////////////////////////////////////////
static void	MonteBulle( T_BULLE * pBulle )
{
	pBulle->Position.y	-= pBulle->Montee ;
	pBulle->Position.x	+=	Alea( -2, 2 ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Gestion des bulles
///////////////////////////////////////////////////////////////////////////////
void MonteeDesBulles( HDC hDC )
{
	int	i ;

	if ( NbBulles < NbMaxBulles )
		{
		HBITMAP	hBitmap ;
		BITMAP	sBitmap ;

		///////////////////////////////////////////////////////////////////////
		// Creer une nouvelle bulle
		///////////////////////////////////////////////////////////////////////
		Bulles[ NbBulles ].Position.x	=	Alea( 0, Largeur ) ;
		Bulles[ NbBulles ].Position.y	=	Hauteur ;
		Bulles[ NbBulles ].Montee		=	Alea( 3, 6 ) ;
		Bulles[ NbBulles ].NoImage		=	Alea( 0, NB_MAX_IMAGES_BULLES -1 ) ;

		hBitmap	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE(IDB_BULLE1 + Bulles[ NbBulles ].NoImage )) ;
		GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;
		DeleteObject( hBitmap ) ;

		Bulles[ NbBulles ].Largeur	=	sBitmap.bmWidth ;
		Bulles[ NbBulles ].Hauteur	=	sBitmap.bmHeight ;
		Bulles[ NbBulles ].Couleur	=	UnSur( 2 ) ? CouleurLiquide : RGB(255,255,255) ;

		NbBulles	++ ;
		}
	

	for ( i = NbBulles-1; i >0 ; i--)
		{
		SetBkColor( hDC, CouleurLiquide ) ;
		EffaceBulle( hDC, &Bulles[i] ) ;
		MonteBulle( &Bulles[i]) ;
		AfficheBulle( hDC, &Bulles[i] ) ;

		if ( Bulles[i].Position.y <= Niveau + 4 )
			{
			EffaceBulle( hDC, &Bulles[i] ) ;
			EclateBulle( hDC, &Bulles[i] ) ;

			// Supprimer la bulle
			memmove( &Bulles[i], &Bulles[i+1], sizeof( T_BULLE ) * ( NbBulles-i )) ;
			NbBulles -- ;
			}
		}
}

