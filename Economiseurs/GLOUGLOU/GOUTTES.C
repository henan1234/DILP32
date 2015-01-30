///////////////////////////////////////////////////////////////////////////////
// Gestion des gouttes
///////////////////////////////////////////////////////////////////////////////
#include "glouglou.h"
#include "..\specif.h"
typedef struct
	{
	int			x ;
	int			y ;
	int			Vitesse ;
	int			Phase ;
	int			Hauteur ;
	int			Largeur ;
	} T_GOUTTE ;


static T_GOUTTE		Gouttes[NB_MAX_GOUTTES] ;
int				NbMaxGouttes	=	NB_MAX_GOUTTES ;
int				NbGouttes		=	0 ;


///////////////////////////////////////////////////////////////////////////////
//	EclateGoutte :
//	Affiche une goutte
///////////////////////////////////////////////////////////////////////////////
static void	EclateGoutte( HDC hDC, T_GOUTTE * pGoutte )
{
	HBITMAP	hBitmapGoutte ;
	BITMAP	sBitmap ;

	hBitmapGoutte	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_GOUTTE_11 )) ;
	GetObject( hBitmapGoutte, sizeof( sBitmap ), &sBitmap ) ;


	AfficheBitmapTransparent( hDC, pGoutte->x, pGoutte->y, sBitmap.bmWidth, sBitmap.bmHeight,
							  hBitmapGoutte, 0, 0 ) ;
	DeleteObject( hBitmapGoutte ) ;
}

///////////////////////////////////////////////////////////////////////////////
//	AfficheGoutte :
//	Affiche une goutte
///////////////////////////////////////////////////////////////////////////////
static void	AfficheGoutte( HDC hDC, T_GOUTTE * pGoutte)
{
	HBITMAP	hBitmapGoutte ;
	BITMAP	sBitmap ;

	SetBkColor( hDC, CouleurLiquide ) ;
		
	hBitmapGoutte	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_GOUTTE_1 + pGoutte->Phase )) ;
	GetObject( hBitmapGoutte, sizeof( sBitmap ), &sBitmap ) ;

	pGoutte->Largeur=	sBitmap.bmWidth ;
	pGoutte->Hauteur=	sBitmap.bmHeight ;

	AfficheBitmapTransparent( hDC, pGoutte->x, pGoutte->y, pGoutte->Largeur, pGoutte->Hauteur,
							  hBitmapGoutte, 0, 0 ) ;

	DeleteObject( hBitmapGoutte ) ;
}

///////////////////////////////////////////////////////////////////////////////
//	EffaceGoutte :
//	Efface une goutte
///////////////////////////////////////////////////////////////////////////////
static	void	EffaceGoutte( HDC hDC, T_GOUTTE *	pGoutte )
{
	FastBitBlt(	hDC, pGoutte->x, pGoutte->y, pGoutte->Largeur, pGoutte->Hauteur,
				hDCEcran, pGoutte->x, pGoutte->y ) ;
}
///////////////////////////////////////////////////////////////////////////////
// BougeUneGoutte
//	gere le mouvement d'une goutte
//	Dans un premier temps, elle se forme en haut de l'ecran
//	puis elle tombe
///////////////////////////////////////////////////////////////////////////////
static void	BougeUneGoutte( HDC	hDC, T_GOUTTE *	pGoutte )
{
	EffaceGoutte( hDC, pGoutte ) ;

	
	if ( pGoutte->Phase < NB_PHASES_CREATION )
		{
		// La goutte se forme en haut de l'ecran

		pGoutte->Phase ++ ;
		}
	else
		{
		// La goutte tombe
		pGoutte->y		+=	pGoutte->Vitesse ;
		if ( pGoutte->y + pGoutte->Hauteur > Niveau )
			pGoutte->Phase	=	NB_PHASES_CREATION + 1 ;
		}

	AfficheGoutte( hDC, pGoutte ) ;
}

///////////////////////////////////////////////////////////////////////////////
// AjouteUneGoutte
//	Ajoute une goutte dans le tableau
///////////////////////////////////////////////////////////////////////////////
static void	AjouteUneGoutte( void )
{
	Gouttes[NbGouttes].x		=	Alea( 0, Largeur ) ;
	Gouttes[NbGouttes].y		=	0 ;
	Gouttes[NbGouttes].Vitesse	=	Alea( 10, 30 ) ;
	Gouttes[NbGouttes].Phase	=	0 ;
	Gouttes[NbGouttes].Largeur	=	0 ;
	Gouttes[NbGouttes].Hauteur	=	0 ;

	NbGouttes++ ;
}

///////////////////////////////////////////////////////////////////////////////
// Gestion des gouttes : elles se forment en haut de l'ecran; grossissent puis
// tombent dans le liquide qui envahit l'ecran
///////////////////////////////////////////////////////////////////////////////
void		GestionGouttes( HDC hDC, COLORREF	CouleurLiquide, int NiveauLiquide )
{
	int	i	;

	if ( NbGouttes < NbMaxGouttes )
		AjouteUneGoutte() ;

	for ( i = NbGouttes-1; i >0 ; i--)
		{
		if ( Gouttes[i].Phase > NB_PHASES_CREATION )
			{
			EffaceGoutte( hDC, &Gouttes[i] ) ;
			// La goutte vient de tomber dans le liquide : on la supprime
			memmove( &Gouttes[i], &Gouttes[i+1], sizeof( T_GOUTTE ) * ( NbGouttes-i )) ;
			NbGouttes -- ;
			}
		else
			BougeUneGoutte( hDC, &Gouttes[i] ) ;
		}
}
