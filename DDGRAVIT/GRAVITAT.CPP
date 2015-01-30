///////////////////////////////////////////////////////////////////////////////
// CEcoGravitation
//	Implementation de l'economiseur Gravitation
// Cet economiseur simule un bout d'espace et les forces de gravites entre
// les differents corps
// 4/4/97 : optimisation : on calcule une fois pour toute l'attraction qu'exerce
//			un corps en stockant Attraction = Masse * G
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "math.h"
#include "signal.h"
#include "resource.h"

#include <ddraw.h>
#include "ddutil.h"

#include "RectAffichage.h"
#include "EcoGravitation.h"
#include "Page1.h"
#include "Page2.h"
#include "PageGenese.h"
#include "PageComete.h"
#include "PagePhysique.h"
#include "PageAffichage.h"
#include "PageMasses.h"

#define ABS(x)	(x > 0 ? x : -x)

extern CRITICAL_SECTION	Critical ;

// Tableau des indices pouvant servir a une couleur d'etoile dans
// la palette utilisee
const BYTE	CouleursEtoiles[]	=	
	{
	170,	171,	172,	173,	174,	175,
	255,	254,	253,	252,	251,	250,	249,
	248,	247,	235,	238,	242,	196,
	243,	241,	240,	216,	208,	198,	139
	} ;
#define NB_COULEURS_ETOILES	(sizeof(CouleursEtoiles)/sizeof(CouleursEtoiles[0]))


const BYTE CouleursComete[]	=	
	{
	118,	119,	120,	121,	122,	123,	124,	125,	126,	127,
	240,	241,	242,	243,	244,	245,	246,	247,	248,	249,
	250,	251,	252,	253,	254,	255
} ;
#define NB_COULEURS_COMETE	(sizeof(CouleursComete)/sizeof(CouleursComete[0]))

int		CEcoGravitation::NbMaxCorps		;
int		CEcoGravitation::NbMinCorps		;
int		CEcoGravitation::NbInitCorps		;
int		CEcoGravitation::NbCorps			;
FLOTTANT	CEcoGravitation::CoeffDistance	;
FLOTTANT	CEcoGravitation::CoeffRayon		;
FLOTTANT	CEcoGravitation::DistanceMax ;
FLOTTANT	CEcoGravitation::_CoeffLiberation ;
FLOTTANT	CEcoGravitation::DeltaT ;
FLOTTANT	CEcoGravitation::_IntervalleTemps ;
FLOTTANT	CEcoGravitation::_DeltaVMax	;
DWORD	CEcoGravitation::DernierTemps ;
FLOTTANT	CEcoGravitation::_DecalageX ;
FLOTTANT	CEcoGravitation::_DecalageY ;
FLOTTANT	CEcoGravitation::_DecalageVx ;
FLOTTANT	CEcoGravitation::_DecalageVy ;
int			CEcoGravitation::_IndicePlusGros ;
FLOTTANT	CEcoGravitation::_CoeffTraveling ;
int			CEcoGravitation::_DensiteEtoiles ;
FLOTTANT	CEcoGravitation::_G ;
int			CEcoGravitation::_NbImagesSecondes ;
int			CEcoGravitation::_DelaiImages ;
DWORD		CEcoGravitation::_DerniereImage ;
CEcoGravitation::T_POUSSIERE	CEcoGravitation::_Poussieres[ NB_MAX_POUSSIERES ] ;
int			CEcoGravitation::_NbPoussieres	;
FLOTTANT	CEcoGravitation::_VentSolaire	;
int			CEcoGravitation::_ViePoussieres ;
int			CEcoGravitation::_NbMaxPoussieres ;
int			CEcoGravitation::_BruitPoussieres ;
int			CEcoGravitation::_TaillePoussieres ;
//FLOTTANT	CEcoGravitation::_Repere ;
int		CEcoGravitation::_Depart= 0 ;		// 0 : tous les corps partent avec une vitesse nulle
											// 1 : tous les corps partent en orbite circulaire autour du centre de gravite
											// 2 : tous les corps partent en orbite approximativement circulaire autour du centre de gravite

CEcoGravitation::T_CORPS		CEcoGravitation::_Corps[NB_MAX_CORPS] ;
CEcoGravitation::T_IMAGE		CEcoGravitation::_Bitmap[NB_BITMAPS] ;
CRectAffichage	CEcoGravitation::_Rectangles ;


BOOL			CEcoGravitation::_Effacer ;
BOOL			CEcoGravitation::_AfficherRepere ;
FLOTTANT		CEcoGravitation::_ZoomMax ;
FLOTTANT		CEcoGravitation::_ZoomInitial ;
FLOTTANT		CEcoGravitation::_TailleRepere ;
FLOTTANT		CEcoGravitation::_DistanceMax ;

POINTS			Explosions[100] ;
int				NbExplosions	=	0 ;

LPDIRECTDRAWSURFACE CEcoGravitation::_lpVertical ;
LPDIRECTDRAWSURFACE CEcoGravitation::_lpHorizontal ;
LPDIRECTDRAWSURFACE CEcoGravitation::_lpAxeVertical ;
LPDIRECTDRAWSURFACE CEcoGravitation::_lpAxeHorizontal ;
LPDIRECTDRAWSURFACE CEcoGravitation::_lpExplosion;

int NbCoups = 0 ;
///////////////////////////////////////////////////////////////////////////////
// Important ! Il doit exister un et un seul objet CEcoGravitation
///////////////////////////////////////////////////////////////////////////////
CEcoGravitation CeciEstMonEconomiseur( "Gravitation", "8597" ) ;
//CDIB	Explosion ;
LPDIRECTDRAWSURFACE	lpExplosion ;

// Juste pour eviter les divide by zero
void _cdecl ErreurFlottant( int sig )
{
}

CEcoGravitation::CEcoGravitation ( const CString & NomEconomiseur, const CString & ValeurEnregistre )
:CEconomiseur( NomEconomiseur, ValeurEnregistre )
	{
	// Initialisation des preferences pour le cas ou la version shareware
	// ne les lirais pas dans la registry
	NbMaxCorps			=	500 ;			// Nombre max de corps
	NbMinCorps			=	3 ;				// Nombre min de corps avant de regenerer
	NbInitCorps			=	150 ;			// Nombre initial de corps
	NbCorps				=	0 ;				// Nombre actuel de corps
	CoeffDistance		=	10. ;			// Coeff multiplicateur de distance

	_ZoomMax			=	3 ;
	_ZoomInitial		=	CoeffDistance ;

	CoeffRayon			=	0.15 ;			// Coeff multiplicateur de rayon ( pour les collisions )
	_DeltaVMax			=	100000 ;			// Vitesses relatives max pour collision 
	_IntervalleTemps	=	0.04 ;		// Intervalle fictif de temps entre deux calculs
											// plus il est fort, moins ca va vite
	_CoeffTraveling		=	0.01 ;			// Coefficient de deplacement de l'affichage
	_NbImagesSecondes	=	23 ;
	_VentSolaire		=	1 ;
	_ViePoussieres		=	4 ;
	_NbMaxPoussieres	=	300 ;
	_G					=	10000. ;
	_DensiteEtoiles		=	400 ;
	_BruitPoussieres	=	50 ;
	_TaillePoussieres	=	3 ;
	_Depart				=	3 ;
		
	_DecalageX	=	0 ;
	_DecalageY	=	0 ;
	_DecalageVx	=	0 ;
	_DecalageVy	=	0 ;

	_CreationComete	=	500000 ;
	_CoeffLiberation=	20 ;

	_AfficherRepere		=	TRUE ;

	_Bitmap[0].MasseMax	=	1.0 ;
	_Bitmap[1].MasseMax	=	2.0 ;
	_Bitmap[2].MasseMax	=	4.0 ;
	_Bitmap[3].MasseMax	=	8.0 ; 
	_Bitmap[4].MasseMax	=	16.0 ;
	_Bitmap[5].MasseMax	=	32.0 ;
	_Bitmap[6].MasseMax	=	64.0 ;
	_Bitmap[7].MasseMax	=	256.0 ;
	
	_Effacer	=	TRUE ;

	LitPreferences() ;

	// Calcul du delai entre deux images en millisecondes
	_DelaiImages	=	1000 / _NbImagesSecondes ;
	_DerniereImage	=	0 ;
	}


CEcoGravitation::~CEcoGravitation ()
{
}


///////////////////////////////////////////////////////////////////////////////
// Efface un rectangle
// Apres avoir remis du noir, on couvre la surface avec des etoiles aleatoires
// de densite constante
///////////////////////////////////////////////////////////////////////////////
inline void	CEcoGravitation::EffaceRectangle( HDC , const CRect & R )
	{
	CRect RD( R ) ;
	DDBLTFX	DDBltFx ;

	DDBltFx.dwSize	=	sizeof( DDBltFx ) ;
	DDBltFx.dwFillColor= RGB(0,0,0) ;

	_lpBackBuffer->Blt( RD, 0, RD, DDBLT_COLORFILL,
						&DDBltFx ) ;

	if ( _DensiteEtoiles )
		{
		int	Surface	=	(R.Width() * R.Height()) ;
		if ( Surface < _DensiteEtoiles )
			{
			static int Restant = 0 ;

			Restant += Surface ;

			if ( Restant >= _DensiteEtoiles )
				{
				Surface = _DensiteEtoiles ;
				Restant -= Surface ;
				}
			}

		Surface /=	_DensiteEtoiles ;

		for ( int i = 0; i < Surface ; i++)
			{
			CRect	REtoile ;
			REtoile.left = R.left + Alea( 0, R.Width()) ;
			REtoile.top = R.top + Alea( 0, R.Height()) ;
			REtoile.right = REtoile.left + 1 ;
			REtoile.bottom = REtoile.top + 1 ;

			DDBltFx.dwFillColor	=	RGB( Alea(0, 255), Alea(0, 255), Alea( 0, 255)) ;
			_lpBackBuffer->Blt( REtoile, 0, REtoile, DDBLT_COLORFILL, &DDBltFx ) ;
			}
		}
	}

///////////////////////////////////////////////////////////////////////////////
// RecherchePlusGros
//	Recherche l'indice du corps le plus massif
//	Indice stocke dans _IndicePlusGros
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::RecherchePlusGros( void )
{
	TriCorps() ;


	_IndicePlusGros	=	0 ;
}

///////////////////////////////////////////////////////////////////////////////
// Suppression d'un corps en retassant la fin du tableau
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::SupprimeCorps( int Indice )
{
	memmove( &_Corps[Indice], &_Corps[Indice+1], sizeof( T_CORPS ) * (NbCorps-Indice-1)) ;
	NbCorps -- ;

	RecherchePlusGros() ;
}

// ==================================================================================================
// ImagePourMasse
// Calcule l'indice de l'image en fonction de la masse du corps
// ENTREES :	Masse du corps celeste
// SORTIES :	Indice de la bitmap
// ==================================================================================================
int	CEcoGravitation::ImagePourMasse( FLOTTANT	Attraction )
{
	int i ;

	const FLOTTANT Masse	=	Attraction / _G ;


	for ( i = 0; i < NB_BITMAPS; i++)
		if ( Masse < _Bitmap[i].MasseMax )
			return i ;
			
	return NB_BITMAPS - 1 ;
}

// ==================================================================================================
// Generation des corps
// ==================================================================================================
void	CEcoGravitation::GenereCorps( void )
{   
	FLOTTANT	Angles[NB_MAX_CORPS] ;
	FLOTTANT	CentreX = 0 ;
	FLOTTANT	CentreY	= 0 ;
	FLOTTANT	AttractionTotale=0 ;

	int	i ;
	
	if ( Apercu())
		NbCorps	=	NB_BITMAPS ;
	else
		NbCorps	=	NbInitCorps ;

	// Positions de depart et masses
	if (_Depart != 3 ) 
		{
		for ( i = 0; i  < NbCorps; i++ )
			{
			if ( Apercu())
				_Corps[i].Image	=	(i%(NB_BITMAPS-1))+1 ;
			else
				_Corps[i].Image	=	Alea( 0, NB_BITMAPS - 1 ) ;

			_Corps[i].Attraction	=	_Bitmap[_Corps[i].Image].MasseMax * _G ;
			_Corps[i].Phase	=	0 ;

			// Angles et distances
			const FLOTTANT Distances	=	Alea( 0, Largeur ) *CoeffDistance ;
			Angles[i]		=	AngleAleatoire() ;

			_Corps[i].x		=	Distances * sin( Angles[i] ) ;
			_Corps[i].y		=	Distances * cos( Angles[i] ) ;
			_Corps[i].vx	=	0 ;
			_Corps[i].vy	=	0 ;

			CentreX += (_Corps[i].x * _Corps[i].Attraction) ;
			CentreY += (_Corps[i].y * _Corps[i].Attraction) ;
			AttractionTotale	+=	_Corps[i].Attraction ;
			}

		CentreX /= AttractionTotale ;
		CentreY /= AttractionTotale ;
		}

	switch( _Depart )
		{
		case 1 :		// Orbite circulaire autour du centre de gravite
		case 2 :		// Orbite circulaire approximative autour du centre de gravite
			for ( i = 0; i < NbCorps; i++ )
				{
				const FLOTTANT Distance	=	sqrt( (_Corps[i].x-CentreX)*(_Corps[i].x-CentreX)
												+ (_Corps[i].y-CentreY)*(_Corps[i].y-CentreY) ) ;

				const FLOTTANT Vitesse	=	VitesseOrbiteCirculaire( Distance, AttractionTotale ) ;
				const FLOTTANT VitesseReelle=	_Depart == 1 ? Vitesse/2 
															 : Vitesse * (FLOTTANT)Alea( 10, 120 ) / 100.0 ;

				// Tourne a droite ou a gauche aleatoirement
				const FLOTTANT EcartAngle	=	UnSur(2) ? PI/2 : -PI/2 ;

				_Corps[i].vx		=	VitesseReelle * sin( Angles[i] + EcartAngle ) ;
				_Corps[i].vy		=	VitesseReelle * cos( Angles[i] + EcartAngle ) ;
				}
			break ;

		case 3 :	// En orbite autour d'un soleil
		case 4 :	// En orbite autour d'un soleil, sens aleatoire
			GenereCorpsOrbites() ;
			break ;

		case 0 :
		default :
			///////////////////////////////////////////////////////////////////
			// Tous les corps partent avec une vitesse nulle
			///////////////////////////////////////////////////////////////////
			break ;			
		}

	RecherchePlusGros() ;
}

// ==================================================================================================
// Charge les bitmaps necessaires a l'affichage
// On calcule le nombre de phase de chaque bitmap en divisant la largeur par la hauteur (chaque
// phase est a cote es autres )
// ==================================================================================================
void	CEcoGravitation::ChargeBitmaps( void )
{
	HDC	hDC	=	CreateCompatibleDC( NULL ) ;

	const int BaseBitmaps	=	GetDeviceCaps( hDC, BITSPIXEL ) > 8 ? 3000 : 2000 ;
	CString		Base( GetDeviceCaps( hDC, BITSPIXEL ) > 8 ? "64_" : "" ) ;

	if (GetDeviceCaps( hDC, BITSPIXEL ) <= 8)
		{
		LPDIRECTDRAWPALETTE	lpPalette	=	DDLoadPalette( _lpDD, "B2001" ) ;

		_lpPrimary->SetPalette( lpPalette );
		_lpBackBuffer->SetPalette( lpPalette ) ;
		SetPalette( lpPalette );
		}
	DeleteDC( hDC ) ;
	
	for ( int i = 0; i < NB_BITMAPS; i++ )
		{
		CString	Nom ;
		Nom.Format( "B%d", BaseBitmaps + i ) ;

		_Bitmap[i].lpImage	=	DDLoadBitmap( _lpDD, Nom, 0, 0 ) ;
		
		DDSURFACEDESC ddsd ;
		ddsd.dwSize	=	sizeof( ddsd ) ;
		ddsd.dwFlags=	DDSD_HEIGHT | DDSD_WIDTH ;
		_Bitmap[i].lpImage->GetSurfaceDesc( &ddsd ) ;

		DDSetColorKey(  _Bitmap[i].lpImage, RGB(0,0,0)) ;

		_Bitmap[i].Rayon	=	ddsd.dwHeight / 2 ;
		_Bitmap[i].NbPhases	=	max( 1, ddsd.dwWidth / ddsd.dwHeight ) ;
		}

	_lpExplosion	=	DDLoadBitmap( _lpDD, Base + "EXPLOSION",0,0 ) ;
	DDSetColorKey( _lpExplosion, RGB(0,0,0)) ;

	_lpVertical = DDLoadBitmap( _lpDD, Base + "VERTICAL", 0, 0 ) ;
	_lpHorizontal = DDLoadBitmap( _lpDD, Base + "HORIZONTAL", 0, 0 ) ;
	_lpAxeVertical = DDLoadBitmap( _lpDD, Base + "AXEVERTICAL", 0, 0 ) ;
	_lpAxeHorizontal = DDLoadBitmap( _lpDD, Base + "AXEHORIZONTAL", 0, 0 ) ;

}


// ==================================================================================================
// CalculeDistance
//	Calcule la distance entre deux corps
// ==================================================================================================
inline FLOTTANT	CEcoGravitation::CalculeDistance( const T_CORPS & T1, const T_CORPS & T2 )
{
	const FLOTTANT DX	=	T1.x - T2.x ;
	const FLOTTANT DY	=	T1.y - T2.y ;
	
	return sqrt( (DX*DX) + (DY*DY) ) ;
}

// ==================================================================================================
// CalculeDistance
//	Calcule la distance entre un corps et le centre de l'ecran
// ==================================================================================================
inline FLOTTANT	CEcoGravitation::CalculeDistance( const T_CORPS & T2 )
{
	return sqrt( (T2.x*T2.x) + (T2.y*T2.y) ) ;
}


// ============================================================================
// Collision
// Determine si deux corps sont entres en collision
// ENTREES :	@ des deux corps
// RETOUR :		VRAI s'il y a collision
// ============================================================================
inline BOOL CEcoGravitation::Collision( const T_CORPS & Corps1, const T_CORPS & Corps2 )
{
	register const FLOTTANT SommeRayon		=	(_Bitmap[Corps1.Image].Rayon + _Bitmap[Corps2.Image].Rayon)	* CoeffRayon ;
	
	return SommeRayon*CoeffDistance > CalculeDistance( Corps1, Corps2 ) ;
}


// ============================================================================
// Recherche l'etoile la plus proche d'un corps
// ============================================================================
int	CEcoGravitation::RechercheEtoilePlusProche( const T_CORPS & Cps )
{
	int	Indice	=	0 ;
	int Image	=	-1 ;
	FLOTTANT	Distance = 0 ;

	for ( register int i = 0; i < NbCorps; i++)
		{
		// Si l'image est celle d'une planete plus grosse, on prend celle la
		if ( _Corps[i].Image > Image )
			{
			Image	=	_Corps[i].Image ;
			Indice	=	i ;
			Distance=	CalculeDistance( _Corps[i], Cps ) ;
			}
		else
			// On ne prend en compte que les corps au moins aussi grand que
			// celui qu'on a deja
			if ( _Corps[i].Image == Image )
				{
				const FLOTTANT Dist	=	CalculeDistance( _Corps[i], Cps ) ;
				if ( Dist < Distance )
					{
					Indice		=	i ;
					Distance	=	Dist ;
					}
				}	
		}
	return Indice ;
}

// ============================================================================
// Calcule  la vitesse donnee par le vent solaire pour une comete
// ============================================================================
inline void	CEcoGravitation::CalculVentSolaire( const T_CORPS & Cps, FLOTTANT * pdx, FLOTTANT *pdy )
{
	const int Indice	= RechercheEtoilePlusProche( Cps ) ;
	*pdx	=	0 ;
	*pdy	=	0 ;

	const FLOTTANT	Distance	=	CalculeDistance( Cps, _Corps[Indice] )  / CoeffDistance ;
	if ( Distance != 0.0 )
		{
		(*pdx)	=	(Cps.x - _Corps[Indice].x )  * (_VentSolaire / Distance ) ;
		(*pdy)	=	(Cps.y - _Corps[Indice].y )  * (_VentSolaire / Distance ) ;
		}
}


// ============================================================================
// Generer un grain de poussiere de la queue de la comete
// ============================================================================
inline void	CEcoGravitation::GenerePoussiere( const T_CORPS & Cps )
{
	if ( _NbPoussieres >= _NbMaxPoussieres -1 )
		return ;

	int x, y ;

	UniversToPixel( Cps.x, Cps.y, &x, &y ) ;

	if (  (x < 0 && Cps.vx < 0 ) || ( x > Largeur && Cps.vx > 0 ) ||
		  (y < 0 && Cps.vy < 0 ) || ( y > Hauteur && Cps.vy > 0 ) )
		  return ;

	FLOTTANT	dx, dy ;
	CalculVentSolaire( Cps, &dx, &dy ) ;

	const FLOTTANT PourcentX		=	Alea( 100-_BruitPoussieres, 100+_BruitPoussieres ) ;
	const FLOTTANT PourcentY		=	Alea( 100-_BruitPoussieres, 100+_BruitPoussieres ) ;

	int	Height, Width ;
	DDGetSize( _Bitmap[IMAGE_COMETE].lpImage, &Height, &Width ) ;

	const FLOTTANT HauteurComete	=	Height / 2 ;

	_Poussieres[_NbPoussieres].x	=	Cps.x + Alea( -HauteurComete, HauteurComete )*CoeffDistance ;
	_Poussieres[_NbPoussieres].y	=	Cps.y + Alea( -HauteurComete, HauteurComete )*CoeffDistance ;

	_Poussieres[_NbPoussieres].vx	=	Cps.vx + (dx * (PourcentX / 100.0) );
	_Poussieres[_NbPoussieres].vy	=	Cps.vy + (dy * (PourcentY / 100.0) );

	const BYTE Couleur = Alea( 16, 64 ) ;
		_Poussieres[_NbPoussieres].Couleur	=	RGB( Couleur*2, Couleur*2, Couleur*4 ) ; //PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
	//_Poussieres[_NbPoussieres].Couleur	=	PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
	_Poussieres[_NbPoussieres].Vie	=	Alea( _ViePoussieres/2, _ViePoussieres ) * _NbImagesSecondes ;

	_Poussieres[_NbPoussieres].Taille	=	Alea( 1, _TaillePoussieres ) ;

	_NbPoussieres ++ ;
}


///////////////////////////////////////////////////////////////////////////////
// Affichage du repere autour du corps le plus gros
///////////////////////////////////////////////////////////////////////////////
inline void	CEcoGravitation::AfficheRepere()
{
	int	x, y ;
	UniversToPixel( _Corps[_IndicePlusGros].x, _Corps[_IndicePlusGros].y, &x, &y ) ;

	FLOTTANT	Ecart	=	_TailleRepere / CoeffDistance ;
	if ( Ecart <= 0.000000)
		Ecart	=	0.0001 ;

	FLOTTANT	Mult	=	1000000 ;
	int			NbFois	=	0 ;
	while ( TRUE  )
		{
		const int	Taille=(int)(Ecart*Mult) ;

		if ( Taille*5 <= Largeur )
			{
			AfficheRepere( x, y, Taille, PALETTEINDEX( 107 ), TRUE ) ;
			break ;
			}

		NbFois ++ ;
		if ( NbFois >= 1000)
			break ; // Pour eviter des plantages

		Mult /= 5.0 ;
		}

  // Affichage de l'origine

	AfficheVertical( _lpAxeVertical, x ) ;
	_Rectangles += CRect( x, 0, x+1, Hauteur ) ;
	
	AfficheHorizontal( _lpAxeHorizontal, y ) ;
	_Rectangles += CRect( 0, y, Largeur, y+1 ) ;
}

// ============================================================================
// AfficheTousLesCorps
// ============================================================================
void	CEcoGravitation::AfficherTousLesCorps()
{
	CRect	R ;

	if ( _AfficherRepere && ! Apercu() ) 
		AfficheRepere () ;

	for ( int i = 0; i < NbCorps; i++)
		{
		const int	Rayon	=	_Bitmap[_Corps[i].Image].Rayon ;
		int x, y ;

		UniversToPixel( _Corps[i].x, _Corps[i].y, &x, &y ) ;
		
		SetRect( &R, x - Rayon, y - Rayon, x + Rayon, y + Rayon ) ;
				
		int DecalageX, DecalageY ;
		_Rectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

		if (! R.IsRectEmpty())
			{
			_Rectangles += R ;

			CRect	RSrc( DecalageX + (int)_Corps[i].Phase*Rayon*2,DecalageY,
						  DecalageX + (int)_Corps[i].Phase*Rayon*2+R.Width(),DecalageY+R.Height()
						) ;

			switch( _lpBackBuffer->BltFast( R.left, R.top, _Bitmap[_Corps[i].Image].lpImage, RSrc,   DDBLTFAST_SRCCOLORKEY  ))
				{
				case DDERR_SURFACELOST :
					{
					_lpPrimary->Restore() ;
					_lpBackBuffer->Restore() ;
					_Bitmap[_Corps[i].Image].lpImage->Restore() ;

					CString	Nom ;
					Nom.Format( "B%d", 2000 + _Corps[i].Image ) ;

					DDReLoadBitmap( _Bitmap[_Corps[i].Image].lpImage, Nom ) ;
					}
				};
			}
		
		// Changer de phase
		(_Corps[i].Phase) += DeltaT / _IntervalleTemps / 400.0 ;
		
		if ( _Corps[i].Phase >= _Bitmap[_Corps[i].Image].NbPhases)
			_Corps[i].Phase = 0 ;
		
		if ( _Corps[i].Image == IMAGE_COMETE )
				GenerePoussiere( _Corps[i] ) ;
		}
}

// ============================================================================
// Efface un corps
//
// ============================================================================
void	CEcoGravitation::EffacerTousLesCorps()
{
	const	int	NbRects	=	_Rectangles.NbRectangles() ;


	for ( int i = 0; i < NbRects; i++)
		EffaceRectangle( 0, _Rectangles.Rectangle( i ) ) ;
}



// ============================================================================
// Agglomeration
// Deux corps se rencontrent et se fondent pour en creer un plus gros
// ENTREES :	Indice des deux corps
// SORTIES :	rien
// ============================================================================
void	CEcoGravitation::Agglomeration( int	Indice1, int Indice2 )
{
	if ( _Corps[Indice1].Attraction < _Corps[Indice2].Attraction )
		{
		// Indice1 doit etre le plus gros des deux corps
		const int	i =	Indice1 ;
		Indice1 =	Indice2 ;
		Indice2 =	i ;
	    }
	    
	// Combiner les deux corps
	_Corps[Indice1].vx		=	( (_Corps[Indice1].vx*_Corps[Indice1].Attraction)
								 +(_Corps[Indice2].vx*_Corps[Indice2].Attraction)
								)
								/
								( _Corps[Indice1].Attraction+_Corps[Indice2].Attraction) ;
	_Corps[Indice1].vy		=	( (_Corps[Indice1].vy*_Corps[Indice1].Attraction)
								 +(_Corps[Indice2].vy*_Corps[Indice2].Attraction)
								)
								/
								( _Corps[Indice1].Attraction+_Corps[Indice2].Attraction) ;
	
	_Corps[Indice1].Attraction	+=	_Corps[Indice2].Attraction ;
	_Corps[Indice1].Image	=	ImagePourMasse(_Corps[Indice1].Attraction ) ;
	_Corps[Indice1].Phase	=	0 ;

	// Ce nouveau corps est peut etre le plus gros de tous
	if ( _Corps[Indice1].Attraction > _Corps[_IndicePlusGros].Attraction )
		RecherchePlusGros() ;

	// Supprimer le deuxieme corps
	SupprimeCorps( Indice2 ) ;

	AjouteExplosion( _Corps[Indice1].x, _Corps[Indice1].y ) ;
}

// ============================================================================
// Eclatement
// Deux corps se rencontrent et s'eparpillent en petits bouts
// ENTREES :	Indice des deux corps
// SORTIES :	rien
// ============================================================================
void	CEcoGravitation::Eclatement( int	Indice1, int Indice2 )
{
	// Nombre de fragments
	const int NbFragments	=	Alea( 6, 20 ) ;
	
	// La masse des fragments est une fraction de la somme totale des deux corps
	const FLOTTANT	Attraction	=	_Corps[Indice2].Attraction / NbFragments  ;
	const int		Image	=	ImagePourMasse( Attraction ) ;
	const FLOTTANT	Rayon	=	_Bitmap[Image].Rayon ;

	///////////////////////////////////////////////////////////////////////////
	// Position et vitesse moyenne
	///////////////////////////////////////////////////////////////////////////
	const FLOTTANT vx	=	((_Corps[Indice1].vx*_Corps[Indice1].Attraction) + (_Corps[Indice2].vy*_Corps[Indice2].Attraction))
						/ (_Corps[Indice1].Attraction + _Corps[Indice2].Attraction) ;
	const FLOTTANT vy	=	((_Corps[Indice1].vy*_Corps[Indice1].Attraction) + (_Corps[Indice2].vy*_Corps[Indice2].Attraction))
						/ (_Corps[Indice1].Attraction + _Corps[Indice2].Attraction) ;
	const FLOTTANT x	=	(_Corps[Indice1].x+_Corps[Indice2].x)/2 ;
	const FLOTTANT y	=	(_Corps[Indice1].y+_Corps[Indice2].y)/2 ;
	
	///////////////////////////////////////////////////////////////////////////
	// On doit commencer par enlever celui dont l'indice est le plus haut, ca
	// evite des calculs pour enlever l'autre
	///////////////////////////////////////////////////////////////////////////
	if ( Indice2 < Indice1 )
		{
		const int i = Indice2 ;
		Indice2 =Indice1 ;
		Indice1 = i ;
		}
	
	// Suppression des deux corps eclates
	SupprimeCorps( Indice2 ) ;
	SupprimeCorps( Indice1 ) ;	

	// creation des Fragments
	// Choix d'une vitesse
	const FLOTTANT Vitesse		=	sqrt( vx*vx + vy*vy ) ;

	const FLOTTANT Distance		=	_Bitmap[Image].Rayon * 4 * CoeffDistance ;
				
	for ( int i = 0; (i < NbFragments) && (NbCorps < NbMaxCorps); i++ )
		{
		// Choix d'un angle
		const FLOTTANT AngleFragment	=	AngleAleatoire() ;
		const FLOTTANT	Vit				=	Vitesse * 100.0 / Alea( 90, 110 ) ;
		
		// Ajoute le corps a la liste
		const FLOTTANT	Cos	=	cos( AngleFragment ) ;
		const FLOTTANT	Sin	=	sin( AngleFragment ) ;
		_Corps[NbCorps].vx	=	vx + Vit * Sin ;
		_Corps[NbCorps].vy	=	vy + Vit * Cos ;

		_Corps[NbCorps].x	=	x	+	Distance * Sin ;
		_Corps[NbCorps].y	=	y	+	Distance * Cos ;

		_Corps[NbCorps].Attraction=	Attraction ;
		_Corps[NbCorps].Image=	Image ;
		_Corps[NbCorps].Phase=	0 ;
		
		NbCorps++ ;
		}

	RecherchePlusGros() ;

	///////////////////////////////////////////////////////////////////////////
	// En prime, creation de quelques poussieres
	///////////////////////////////////////////////////////////////////////////
	if ( _NbPoussieres >= _NbMaxPoussieres -1 )
		return ;

	int Px, Py ;
	UniversToPixel( x, y, &Px, &Py ) ;
	if (  (Px < 0 && vx < 0 ) || ( Px > Largeur && vx > 0 ) ||
		  (Py < 0 && vy < 0 ) || ( Py > Hauteur && vy > 0 ) )
		  return ;

	const int NbPouss	=	Alea( 5, 40 ) ;

	for ( i = 0; (i < NbPouss) && ( _NbPoussieres < _NbMaxPoussieres); i++)
		{
		// Ajoute le corps a la liste
		const FLOTTANT	Vit =	Vitesse * 100.0 / Alea( 100-_BruitPoussieres, 100+_BruitPoussieres ) ;
		// Choix d'un angle
		const FLOTTANT AngleFragment	=	AngleAleatoire() ;
		const FLOTTANT	Cos	=	cos( AngleFragment ) ;
		const FLOTTANT	Sin	=	sin( AngleFragment ) ;
	
		_Poussieres[_NbPoussieres].x	=	x ;
		_Poussieres[_NbPoussieres].y	=	y ;

		_Poussieres[_NbPoussieres].vx	=	vx + Vit * Sin ;
		_Poussieres[_NbPoussieres].vy	=	vy + Vit * Cos ;

		const BYTE Couleur = Alea( 16, 127 ) ;
		_Poussieres[_NbPoussieres].Couleur	=	RGB( Couleur, Couleur, Couleur*2 ) ; //PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
		_Poussieres[_NbPoussieres].Vie		=	Alea( _ViePoussieres/2, _ViePoussieres ) * _NbImagesSecondes ;
		_Poussieres[_NbPoussieres].Taille	=	Alea( 1, _TaillePoussieres ) ;

		_NbPoussieres ++ ;
		}

	AjouteExplosion( _Corps[Indice1].x, _Corps[Indice1].y ) ;
}

// ============================================================================
// Rencontre
// Gere la rencontre de deux corps
// Si les deux masses sont tres differentes, le plus gros absorbe le plus petit
// sinon si les vitesses sont tres differentes, les deux eclatent
// ENTREES :	indice des deux corps
// ============================================================================
void	CEcoGravitation::Rencontre( int	Indice1, int Indice2 )
{
	int		ImageMin ;
	int		ImageMax ;
	FLOTTANT	DeltaV ;

	const FLOTTANT	x	=	(_Corps[Indice1].x+_Corps[Indice2].x) / 2 ;
	const FLOTTANT	y	=	(_Corps[Indice1].y+_Corps[Indice2].y) / 2 ;
	
	// De toutes facons, si on a deja trop de corps a gerer, on les agglomere
	if ( NbCorps > NbMaxCorps-5)
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}

	// Si les deux corps sont deja petits, on les agglomere
	if ( _Corps[Indice1].Image <= IMAGE_PETITE_PLANETE &&
		 _Corps[Indice2].Image <= IMAGE_PETITE_PLANETE )
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}
		 	
	if ( _Corps[Indice1].Attraction > _Corps[Indice2].Attraction )
		{
		ImageMax	=	_Corps[Indice1].Image ;
		ImageMin	=	_Corps[Indice2].Image ;
		}
	else
		{
		ImageMax	=	_Corps[Indice2].Image ;
		ImageMin	=	_Corps[Indice1].Image ;
		}

	// Si les masses sont tres differentes, le plus gros absorbe le plus petit			
	if ( ImageMax > (ImageMin + 1) )
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}
		
	// Les corps sont a peu pres semblables, ce qui se passe depend de la
	// vitesse a laquelle ils se rentrent dedans
		
	// Calculer la difference des vitesses
	DeltaV	=sqrt((_Corps[Indice1].vx-_Corps[Indice2].vx)*(_Corps[Indice1].vx-_Corps[Indice2].vx)+
			 (_Corps[Indice1].vy-_Corps[Indice2].vy)*(_Corps[Indice1].vy-_Corps[Indice2].vy));
		
	if ( (DeltaV*_IntervalleTemps) > _DeltaVMax )
		Eclatement( Indice1, Indice2 ) ;
	else
		Agglomeration( Indice1, Indice2 ) ;
}

// ============================================================================
// CalculeAcceleration
// Calcule les forces d'attraction entre tous les corps
// ============================================================================
void	CEcoGravitation::CalculAccelerations( void )
{
	int	i, j ;

	_DistanceMax	=	0 ;

	for ( i = 0; i < NbCorps; i++)
		{
/*		// Ce corps est il perdu a tout jamais	?
		if ( LostInSpace( _Corps[i] ))
			{
			// Elimination du corps, trop loin du centre
			SupprimeCorps( i ) ;
			}
		// Le corps est toujours la, Attraction avec les suivants
		else
			{
			const FLOTTANT Distance	=	CalculeDistance( _Corps[i] ) ;
			if ( Distance > _DistanceMax )
				_DistanceMax	=	Distance ;
*/
			for ( j = i + 1; j < NbCorps; j++ )
				{
				// Les deux corps entrent-ils en collision ?
				if ( Collision( _Corps[i], _Corps[j]) )
					Rencontre( i, j ) ;
				else
					Accelere( &_Corps[i], &_Corps[j] ) ;
				}
			}
//		}
}

// ============================================================================
// Recale l'origine sur le corps le plus massif
// Pour que ce soit plus joli, on decale pas tout en une fois
// ============================================================================
void	CEcoGravitation::Recentre( void )
{
	const FLOTTANT	Dist	=	CalculeDistance( _Corps[_IndicePlusGros] ) / CoeffDistance ;

	if ( Dist < Largeur / 8 )
		{
		_DecalageX	=	0 ;
		_DecalageY	=	0 ;
		_DecalageVx	=	_Corps[_IndicePlusGros].vx * 0.5 ;
		_DecalageVy	=	_Corps[_IndicePlusGros].vx * 0.5 ;
		return ;
		}
	else
	if ( Dist	< Largeur/3 )
		{
		_DecalageX	=	_Corps[_IndicePlusGros].x  * _CoeffTraveling / 2 ;
		_DecalageY	=	_Corps[_IndicePlusGros].y  * _CoeffTraveling / 2 ;
		_DecalageVx	=	_Corps[_IndicePlusGros].vx * _CoeffTraveling ;
		_DecalageVy	=	_Corps[_IndicePlusGros].vy * _CoeffTraveling ;
		}
	else
		{
		_DecalageX	=	_Corps[_IndicePlusGros].x * _CoeffTraveling ;
		_DecalageY	=	_Corps[_IndicePlusGros].y * _CoeffTraveling ;

		_DecalageVx	=	_Corps[_IndicePlusGros].vx * _CoeffTraveling ;
		_DecalageVy	=	_Corps[_IndicePlusGros].vy * _CoeffTraveling ;
		}
}



///////////////////////////////////////////////////////////////////////////////	
// PeintFenetre
//	Peint la fenetre dans son etat initial
///////////////////////////////////////////////////////////////////////////////	
void	CEcoGravitation::PeintFenetre( CDC & Dc, const CRect& R)
{
	EffaceRectangle(Dc.m_hDC, R) ;

	_Rectangles += R ;

	Dc.PatBlt( R.left, R.right, R.Width(), R.Height(), BLACKNESS ) ;

	if ( _DensiteEtoiles )
		{
		const int	Surface	=	(R.Width() * R.Height() / _DensiteEtoiles) + 1  ;

		for ( int i = 0; i < Surface ; i++)
			Dc.SetPixelV(	Alea( R.left, R.right-1 ),
							Alea( R.top, R.bottom-1 ),
							PALETTEINDEX( CouleursEtoiles[ Alea( 0, NB_COULEURS_ETOILES )])) ;
		}
}

///////////////////////////////////////////////////////////////////////////////	
// Lecture/Ecriture des preferences
///////////////////////////////////////////////////////////////////////////////	
void CEcoGravitation::Preferences()
	{
	Preference( "Nb Max de corps",	NbMaxCorps ) ;
	Preference( "Nb Min de corps",	NbMinCorps ) ;
	Preference( "Nb Init de corps", NbInitCorps ) ;
	Preference( "Densite d'etoiles", _DensiteEtoiles ) ;
	Preference( "Constante de gravitation (G)", _G ) ;
	Preference( "Methode de depart", _Depart ) ;
	Preference( "Effacer trajectoires", _Effacer ) ;
	Preference( "Afficher repere", _AfficherRepere ) ;

	if ( ! ShareWare())
		{
		Preference( "Images par secondes",			_NbImagesSecondes ) ;
		Preference(	"Multiplicateur distance",		CoeffDistance	) ;
		Preference(	"Rapport de rayon",				CoeffRayon 	) ;
		Preference(	"Vitesse collision max",		_DeltaVMax	) ;
		Preference(	"Multiplicateur vitesse de liberation", 	_CoeffLiberation ) ;
		Preference( "Intervalle de Temps",			_IntervalleTemps ) ;
		Preference( "Rapport traveling",			_CoeffTraveling ) ;
		Preference( "Vent solaire",					_VentSolaire ) ;
		Preference( "Duree de vie poussieres",		_ViePoussieres ) ;
		Preference( "Nb Max de poussieres",			_NbMaxPoussieres ) ;
		Preference( "Bruit poussieres",				_BruitPoussieres ) ;
		//Preference( "Repere",						_Repere ) ;
		Preference( "Frequence de creation de comete", _CreationComete ) ;
		Preference( "Taille poussieres",			_TaillePoussieres ) ;
		Preference( "Zoom Maximum",					_ZoomMax ) ;


		Preference( "Masse 0", _Bitmap[0].MasseMax ) ;
		Preference( "Masse 1", _Bitmap[1].MasseMax ) ;
		Preference( "Masse 2", _Bitmap[2].MasseMax ) ;
		Preference( "Masse 3", _Bitmap[3].MasseMax ) ;
		Preference( "Masse 4", _Bitmap[4].MasseMax ) ;
		Preference( "Masse 5", _Bitmap[5].MasseMax ) ;
		Preference( "Masse 6", _Bitmap[6].MasseMax ) ;
		Preference( "Masse 7", _Bitmap[7].MasseMax ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Fait bouger les grains de poussieres
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::AvancerPoussieres()
{
	int x, y ;

	for ( int i = 0; i < _NbPoussieres; i++)
		{
		UniversToPixel( _Poussieres[i].x, _Poussieres[i].y, &x, &y ) ;

		if ( _Poussieres[i].Vie <= 0 || x < 0 || y < 0 || x > Largeur || y > Hauteur )
			{
			// Suppression de la poussiere
			memcpy( &_Poussieres[i], &_Poussieres[i+1], sizeof( _Poussieres[i] ) * (_NbPoussieres-i-1)) ;
			_NbPoussieres -- ;
			i-- ;
			}
		else
			{
			_Poussieres[i].x	+= (_Poussieres[i].vx * DeltaT) - _DecalageX ;
			_Poussieres[i].y	+= (_Poussieres[i].vy * DeltaT) - _DecalageY ;

			_Poussieres[i].vx	-= _DecalageVx ;
			_Poussieres[i].vy	-= _DecalageVy ;
			}
		}
}


///////////////////////////////////////////////////////////////////////////////
// Affichage des grains de poussieres generes par les cometes
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AfficherPoussieres()
{
	DDBLTFX DDBltFx ;
	DDBltFx.dwSize	=	sizeof( DDBltFx ) ;

	int dx, dy ;
	int x, y ;
		
	for ( int i = 0; i < _NbPoussieres; i++)
		{
		UniversToPixel( _Poussieres[i].x, _Poussieres[i].y, &x, &y ) ;
		
		if ( (x >=0) && (y >= 0) && (x < Largeur) && (y < Hauteur) )
			{
			CRect	R( x, y, x + _Poussieres[i].Taille, y + _Poussieres[i].Taille ) ;

			_Rectangles.LimiteRect( R, &dx, &dy ) ;
			_Rectangles += R ;

			//const BYTE	Composante=Alea(10, 255) ;
			DDBltFx.dwFillColor	=	_Poussieres[i].Couleur ; //RGB( Composante, Composante, Composante ) ;
			_lpBackBuffer->Blt( R, 0, R, DDBLT_COLORFILL, &DDBltFx ) ;
			_Poussieres[i].Vie -- ;
			}
		}

}

///////////////////////////////////////////////////////////////////////////////
// Validation des preferences
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::ValidePreferences()
{
	CEconomiseur::ValidePreferences() ;

	// Nombres de corps
	if ( NbMaxCorps < 2 )
		NbMaxCorps = 2 ;

	if ( NbMaxCorps >= NB_MAX_CORPS )
		NbMaxCorps = NB_MAX_CORPS -1 ;

	if ( NbMinCorps < 1 )
		NbMinCorps = 1 ;

	if ( NbMinCorps >= NbMaxCorps )
		NbMinCorps = NbMaxCorps ;

	if ( NbInitCorps < NbMinCorps )
		NbInitCorps = NbMinCorps ;

	if ( NbInitCorps > NbMaxCorps )
		NbInitCorps = NbMaxCorps ;

	// Nombres de poussieres
	if ( _NbMaxPoussieres >= NB_MAX_POUSSIERES )
		_NbMaxPoussieres = NB_MAX_POUSSIERES - 1 ;

	if ( _NbMaxPoussieres < 0 )
		_NbMaxPoussieres = 0 ;

	if ( _NbImagesSecondes < 1 )
		_NbImagesSecondes = 1 ;

	if ( _NbImagesSecondes > 50 )
		_NbImagesSecondes	=	50 ;
}


BOOL	CEcoGravitation::ChargeEtat( const char * Nom)
	{
	return FALSE ;
	}

BOOL	CEcoGravitation::SauveEtat( const char * Nom )
	{
	return FALSE ;
	}



///////////////////////////////////////////////////////////////////////////////
// Generation aleatoire d'une comete
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::GenereUneComete( void )
{
	if ( NbCorps >= NbMaxCorps-1 )
		return ;

	const FLOTTANT	Distance	=	Alea( max(Largeur, Hauteur)/2, max( Largeur, Hauteur)) * CoeffDistance ;
	const FLOTTANT	Angle		=	AngleAleatoire() ;
	const FLOTTANT	Vitesse		=	VitesseOrbiteCirculaire( Distance, _Corps[_IndicePlusGros].Attraction ) ;

	// Pour ne pas obtenir un orbite circulaire, on diminue un peu la vitesse
	const FLOTTANT	VitesseReelle	=	Vitesse * (FLOTTANT)Alea( 20, 60 ) / 100.0 ;
	
	_Corps[NbCorps].vx	=	VitesseReelle * sin( Angle + PI/2 ) + _Corps[_IndicePlusGros].vx ;
	_Corps[NbCorps].vy	=	VitesseReelle * cos( Angle + PI/2 ) + _Corps[_IndicePlusGros].vy ;

	_Corps[NbCorps].x	=	_Corps[_IndicePlusGros].x	+	Distance * sin( Angle ) ;
	_Corps[NbCorps].y	=	_Corps[_IndicePlusGros].y	+	Distance * cos( Angle ) ;

	_Corps[NbCorps].Attraction=	_Bitmap[ IMAGE_COMETE ].MasseMax  * _G ;
	_Corps[NbCorps].Image=	IMAGE_COMETE ;
	_Corps[NbCorps].Phase=	0 ;
	
	NbCorps++ ;
}

///////////////////////////////////////////////////////////////////////////////
// Choix d'un angle aleatoire ( exprime en radian 0..2*PI)
///////////////////////////////////////////////////////////////////////////////
inline FLOTTANT CEcoGravitation::AngleAleatoire( void )
{
	return (FLOTTANT)Alea( 0, (int)(PI*20000.0) ) / 10000.0 ;
}


void	CEcoGravitation::Configuration( CPropertySheet * pPropSheet )
	{
	pPropSheet->AddPage( new CPage1 ) ;
	pPropSheet->AddPage( new CPage2 ) ;
	pPropSheet->AddPage( new CPageGenese ) ;
	pPropSheet->AddPage( new CPagePhysique ) ;
	pPropSheet->AddPage( new CPageComete ) ;
	pPropSheet->AddPage( new CPageMasses ) ;
	pPropSheet->AddPage( new CPageAffichage ) ;
	
	pPropSheet->SetTitle( "Configuration de Gravitation" ) ;

	CEconomiseur::Configuration( pPropSheet ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Calcule la vitesse d'orbite circulaire autour d'un corps dont on donne la
// masse en fonction de la distance
// formule :
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
//			v	=	sqrt( GM/d )
///////////////////////////////////////////////////////////////////////////////
inline FLOTTANT CEcoGravitation::VitesseOrbiteCirculaire( const FLOTTANT & Distance, const FLOTTANT & Attraction )
{
	return sqrt( Attraction / Distance ) ;
}

///////////////////////////////////////////////////////////////////////////////
// LostInSpace !
// Retourne VRAI si on peut considerer le corps comme perdu dans l'espace :
//	S'il est toujours a l'ecran, on le garde
//	Sinon on calcule sa vitesse de liberation du corps le plus gros
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
///////////////////////////////////////////////////////////////////////////////
inline BOOL CEcoGravitation::LostInSpace( const T_CORPS & Corps )
{
	int x, y ;
	
	UniversToPixel( Corps.x, Corps.y, &x, &y ) ;
	
	///////////////////////////////////////////////////////////////////////////
	// Si le corps est visible a l'ecran, on le garde de toutes facons
	///////////////////////////////////////////////////////////////////////////
	if ( x > 0 && x < Largeur )
		return FALSE ;

	if ( y > 0 && y < Hauteur )
		return FALSE ;

	if ( x > Largeur && Corps.vx < 0 )
		// Le corps revient vers l'ecran
		return FALSE ;

	if ( x < 0 && Corps.vx > 0)
		return FALSE ;

	if ( y > Hauteur && Corps.vy < 0 )
		// Le corps revient vers l'ecran
		return FALSE ;

	if ( y < 0 && Corps.vy > 0)
		return FALSE ;

	const FLOTTANT	Ve		=	CalculeVitesseLiberation( Corps ) ;
	const FLOTTANT	Vx		=	Corps.vx - _Corps[_IndicePlusGros].vx ;
	const FLOTTANT	Vy		=	Corps.vy - _Corps[_IndicePlusGros].vy ;

	const FLOTTANT	V		=	sqrt( Vx*Vx + Vy*Vy ) ;

	return V > ( Ve * _CoeffLiberation / 100.0 ) ;
}

// ============================================================================
// Accelere
// Calcule l'acceleration gravitationnelle reciproque qui s'exerce entre deux
// corps suivant la formule : F	=	GMm/d2  =>	a = F/m = GM/d2
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
// ENTREES	:	Les deux corps
// SORTIES	:	Les deux corps avec leurs vitesse modifiees
// ============================================================================
inline void	CEcoGravitation::Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 )
{
	// ================================================== Calcul de la distance
	const FLOTTANT DistanceX		=   (FLOTTANT)(pCorps2->x - pCorps1->x)  ;
	const FLOTTANT DistanceY		=   (FLOTTANT)(pCorps2->y - pCorps1->y)  ;

	const FLOTTANT Distance			=	sqrt( (DistanceX * DistanceX ) + ( DistanceY * DistanceY ) ) ;
	const FLOTTANT DistanceCube		=	Distance * Distance * Distance ;

	if ( DistanceCube	!= 0 )
		{
		pCorps1->vx	+=	pCorps2->Attraction * (DistanceX / DistanceCube * DeltaT) ;
		pCorps2->vx	-=	pCorps1->Attraction * (DistanceX / DistanceCube * DeltaT) ;
		
		pCorps1->vy	+=	pCorps2->Attraction * (DistanceY / DistanceCube * DeltaT) ;
		pCorps2->vy	-=	pCorps1->Attraction * (DistanceY / DistanceCube * DeltaT) ;
		}
}

// ============================================================================
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
// la formule :
//			ve	=	sqrt( 2GM/d )
// ============================================================================
FLOTTANT CEcoGravitation::CalculeVitesseLiberation( const T_CORPS & Corps )
{
	const FLOTTANT	Distance	=	CalculeDistance( Corps ) ;
	return sqrt( 2 * _Corps[_IndicePlusGros].Attraction / Distance ) ;	
}

// ============================================================================
// Converti les coordonnees dans l'univers en coordonnees sur l'ecran
// ============================================================================
inline void CEcoGravitation::UniversToPixel( int x, int y, int * px, int * py )
{
const FLOTTANT X = (x / CoeffDistance) + (double)(CEconomiseur::GetEconomiseur()->Largeur/2) ;

	if ( X > (double)INT_MAX )
		*px	=	INT_MAX-1 ;
	else
		if ( X < (double)INT_MIN )
			*px	=	INT_MIN+1 ;
		else
			*px	=	(int)X ;

	const FLOTTANT Y = (y / CoeffDistance) + (double)(CEconomiseur::GetEconomiseur()->Hauteur/2) ;

	if ( Y > (double)INT_MAX )
		*py	=	INT_MAX-1 ;
	else
		if ( Y < (double)INT_MIN )
			*py	=	INT_MIN+1 ;
		else
			*py =	(int)Y ;
}

// ============================================================================
// Genere tous les corps en orbite autour d'un soleil central
// ============================================================================
void CEcoGravitation::GenereCorpsOrbites()
{
	// Un gros corps au centre, les autres en orbite autour
	_Corps[0].x			=	0 ;
	_Corps[0].y			=	0 ;
	_Corps[0].vx		=	0 ;
	_Corps[0].vy		=	0 ;
	_Corps[0].Attraction=	_Bitmap[NB_BITMAPS-1].MasseMax * _G ;
	_Corps[0].Image		=	NB_BITMAPS-1 ;
	_Corps[0].Phase		=0 ;

	GenereSatellites( 0, NbCorps-1, NB_BITMAPS-2,
					 CoeffDistance*0.01*Largeur,
					 CoeffDistance*Largeur/2.0 ) ;
}

void CEcoGravitation::GenereSatellites( int Indice, int NbSatellites, int ImageMax, FLOTTANT DistanceMin, FLOTTANT DistanceMax )
	{
	for ( int i = Indice+1; i <= Indice+NbSatellites; i++ )
		{
		const FLOTTANT Distance	=	(FLOTTANT)Alea( 0, 10000) * (DistanceMax-DistanceMin) / 10000.0 + DistanceMin ;
		const FLOTTANT Angle	=	AngleAleatoire() ;
		
		const FLOTTANT Vitesse	=	VitesseOrbiteCirculaire( Distance, _Corps[Indice].Attraction ) ;

		// Tourne a droite ou a gauche aleatoirement
		FLOTTANT EcartAngle	;

		if ( _Depart == 3  )
			EcartAngle	=	-PI/2 ;
		else
			EcartAngle	=	UnSur(2) ? PI/2 : -PI/2 ;

		_Corps[i].vx		=	Vitesse* sin( Angle + EcartAngle ) + _Corps[Indice].vx ;
		_Corps[i].vy		=	Vitesse* cos( Angle + EcartAngle ) + _Corps[Indice].vy ;

		_Corps[i].x			=	_Corps[Indice].x + Distance*sin( Angle ) ;
		_Corps[i].y			=	_Corps[Indice].y + Distance*cos( Angle ) ;

		_Corps[i].Image		=	Alea( 0, ImageMax ) ;
		_Corps[i].Attraction=	_Bitmap[_Corps[i].Image].MasseMax * _G ;
		_Corps[i].Phase		=	0 ;

		if ( _Corps[i].Image > 3 && (i < NbSatellites-4) && UnSur( 10 ))
			{
			// Creer des satellites autour de ce corps
			const int	NbSatellites	=	Alea( 1, 4 ) ;

			GenereSatellites( i, NbSatellites, ImageMax-3, DistanceMin/10, DistanceMax/10 ) ;

			i += NbSatellites ;
			}
		}
	}


inline void CEcoGravitation::CalculZoom()
{
/*	FLOTTANT	MaxX	=	0 ;
	FLOTTANT	MaxY	=	0 ;
	FLOTTANT	NouveauCoeff	=	_DistanceMax * 2.0  / Largeur ;

	if ( NouveauCoeff > _ZoomInitial * _ZoomMax )
		NouveauCoeff	=	_ZoomInitial * _ZoomMax ;

	// Moyenne ponderee pour eviter les trops grands ecarts de zoom
	const FLOTTANT	PONDERATION_ZOOM	=	3.0 ;
	NouveauCoeff	=	((CoeffDistance*PONDERATION_ZOOM)+NouveauCoeff)/(PONDERATION_ZOOM + 1.0)  ;

	// Pour garder des queues de cometes avec une allure constante
	_VentSolaire *= CoeffDistance / NouveauCoeff ;

	CoeffDistance	=	NouveauCoeff ;
*/

	FLOTTANT	X = 0 ;
	FLOTTANT	Y = 0 ;
	FLOTTANT	MasseTotale = 0 ;
	FLOTTANT	MaxX	=	0 ;
	FLOTTANT	MaxY	=	0 ;
	FLOTTANT	MinX	=	0 ;
	FLOTTANT	MinY	=	0 ;

	for ( int i = 0; i < NbCorps; i++)
		{
		///////////////////////////////////////////////////////////////////////
		// Calcul du centre de gravite
		///////////////////////////////////////////////////////////////////////
		X	+=	_Corps[i].x * _Corps[i].Attraction ;
		Y	+=	_Corps[i].y * _Corps[i].Attraction ;

		MasseTotale	+=	_Corps[i].Attraction ;

		///////////////////////////////////////////////////////////////////////
		// Calcul de l'espace occupe
		///////////////////////////////////////////////////////////////////////
		if ( _Corps[i].x > MaxX )
			MaxX	=	_Corps[i].x ;

		if ( _Corps[i].y > MaxY )
			MaxY	=	_Corps[i].y ;

		if ( _Corps[i].x	< MinX )
			MinX	=	_Corps[i].x ;

		if ( _Corps[i].y < MinY )
			MinY	=	_Corps[i].y ;
		}

	X	/= MasseTotale ;
	Y	/= MasseTotale ;

	FLOTTANT	NouveauCoeff	=	((MaxX-MinX) + (MaxY-MinY)) * 2.0  / Largeur ;

	if ( NouveauCoeff > _ZoomInitial * _ZoomMax )
		NouveauCoeff	=	_ZoomInitial * _ZoomMax ;

	// Moyenne ponderee pour eviter les trops grands ecarts de zoom
	const FLOTTANT	PONDERATION_ZOOM	=	3.0 ;
	NouveauCoeff	=	((CoeffDistance*PONDERATION_ZOOM)+NouveauCoeff)/(PONDERATION_ZOOM + 1.0)  ;

	// Pour garder des queues de cometes avec une allure constante
	_VentSolaire *= CoeffDistance / NouveauCoeff ;

	CoeffDistance	=	NouveauCoeff ;

	Recentre() ;

	for ( i = 0; i < NbCorps; i++)
		if ( LostInSpace( _Corps[i] ))
			SupprimeCorps( i ) ;
		else
			{
			_Corps[i].vx	-= _DecalageVx ;
			_Corps[i].vy	-= _DecalageVy ;

			_Corps[i].x	-=	_DecalageX ;
			_Corps[i].y	-=	_DecalageY ;
			}
}

///////////////////////////////////////////////////////////////////////////////
// Affichage des lignes du repere, l'origine est affichee a part
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AfficheRepere( int x, int y, int Taille, COLORREF Couleur, BOOL Rectangles )
{
	///////////////////////////////////////////////////////////////////////////
	// Traits verticaux
	///////////////////////////////////////////////////////////////////////////
	for ( int i = x+Taille; i < Largeur-1; i += Taille )
		{
		AfficheVertical( _lpVertical, i ) ;
		if ( Rectangles )
			_Rectangles += CRect( i, 0, i+1, Hauteur ) ;
		}

	for ( i = x-Taille; i > 0; i -= Taille )
		{
		AfficheVertical( _lpVertical, i ) ;
		if ( Rectangles )
			_Rectangles += CRect( i, 0, i+1, Hauteur ) ;
		}
		
	///////////////////////////////////////////////////////////////////////////
	// Traits horizontaux
	///////////////////////////////////////////////////////////////////////////
	for ( i = y+Taille; i < Hauteur-1; i += Taille )
		{
		AfficheHorizontal( _lpHorizontal, i ) ;
		if ( Rectangles )
			_Rectangles += CRect( 0, i, Largeur, i+1 ) ;
		}

	for ( i = y-Taille; i > 0; i -= Taille )
		{
		AfficheHorizontal( _lpHorizontal, i ) ;
		
		if ( Rectangles )
			_Rectangles += CRect( 0, i, Largeur, i+1 ) ;
		}
}


int CompareCorps( const void *arg1, const void *arg2 )
	{
	const CEcoGravitation::T_CORPS * pCorps1 = (const CEcoGravitation::T_CORPS * )arg1 ;
	const CEcoGravitation::T_CORPS * pCorps2 = (const CEcoGravitation::T_CORPS * )arg2 ;

	const FLOTTANT Diff	=	 pCorps2->Attraction - pCorps1->Attraction ;
	if ( Diff > 0 )
		return 1 ;
	else
		if ( Diff < 0 )
			return -1 ;
	else
		return 0 ;
	}

void CEcoGravitation::TriCorps()
	{
	qsort( _Corps, NbCorps, sizeof( T_CORPS ), CompareCorps ) ;
	}

void CEcoGravitation::AfficheExplosion( FLOTTANT x, FLOTTANT y )
{
	int L, H ;
	DDGetSize( _lpExplosion, &L, &H ) ;

	CRect R ;
	int Px, Py ;
	UniversToPixel( x, y, &Px, &Py ) ;
	R.left	=	Px-L / 2 ;
	R.top	=	Py-H / 2 ;

	R.right	=	R.left + L ;
	R.bottom=	R.top + H ;
			
	int DecalageX, DecalageY ;
	_Rectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

	if (! R.IsRectEmpty())
		{
		_Rectangles += R ;

		_lpBackBuffer->BltFast( R.left, R.top, _lpExplosion,
								CRect( DecalageX, DecalageY, L-DecalageX, H-DecalageY ),
								DDBLTFAST_SRCCOLORKEY ) ;
		}
}

void CEcoGravitation::AjouteExplosion( int x , int y )
{
	if ( NbExplosions >= sizeof(Explosions)/sizeof(Explosions[0]))
		return ;

	Explosions[NbExplosions].x	=	x ;
	Explosions[NbExplosions].y	=	y ;

	NbExplosions ++ ;
}


///////////////////////////////////////////////////////////////////////////////
// Initialisation du screen saver en mode animation
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::InitSave( HWND	hWnd )
	{
	signal( SIGFPE, ErreurFlottant ) ;
    
	NoircirEcran = TRUE ;
	CEconomiseur::InitSave( hWnd ) ;

	_ZoomInitial	=	CoeffDistance ;
	_TailleRepere	=	(min( Largeur, Hauteur )/6)/10 ;
	
	ChargeBitmaps() ;
	GenereCorps() ;

		
	if ( _lpBackBuffer )
		{
		EffaceRectangle( 0, CRect( 0, 0, Largeur, Hauteur )) ;
		}

	_Rectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;
	_Rectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;

	DernierTemps		=	GetCurrentTime() ;
}

void CEcoGravitation::Calcul( void )
{
	int	i	;

	// Pour garder une vitesse constante quelle que soit le temps mis pour les calculs
	const DWORD TempsCourant	=	GetCurrentTime ();
	DeltaT			=	(TempsCourant-DernierTemps) * _IntervalleTemps ;
	DernierTemps	=	TempsCourant ;
	
	// Calcul des interactions qu'exercent les corps les uns sur les autres
	CalculAccelerations() ;

	// Deplace les corps
	EnterCriticalSection(&Critical) ;
	for ( i = 0; i < NbCorps; i++)
		{
		_Corps[i].x	+=	(_Corps[i].vx * DeltaT) ; // - _DecalageX ;
		_Corps[i].y	+=	(_Corps[i].vy * DeltaT) ; // - _DecalageY ;
		}
	LeaveCriticalSection(&Critical) ;

	NbCoups ++ ;
}


void CEcoGravitation::Affichage( void )
{
	CalculZoom() ;

	// Generation aleatoire de comete
	if ( NbCorps <= NbInitCorps / 10 )
		if ( UnSur( _CreationComete ))
				GenereUneComete() ;

	if ( _Effacer )
		EffacerTousLesCorps() ;

	_Rectangles.Vide() ;

	AfficherTousLesCorps() ;

	AvancerPoussieres() ;
	AfficherPoussieres() ;


	for ( int i = 0; i < NbExplosions; i++ )
		AfficheExplosion( Explosions[i].x, Explosions[i].y ) ;

	NbExplosions	=	0 ;
	/*
	HDC hDC ;
	if ( NbCoups > 1 )
	if ( _lpBackBuffer->GetDC( &hDC ) == DD_OK )
		{
		char Buffer [ 20 ] ;
		sprintf( Buffer, "%08d", NbCoups ) ;

		TextOut( hDC, 0, 0, Buffer, lstrlen( Buffer )) ;
		_lpBackBuffer->ReleaseDC( hDC ) ;
		}
	NbCoups = 0 ;
*/
	// Regenerer tous les corps si leur nombre est devenu trop petit
	if ( NbCorps < NbMinCorps )
		{
		GenereCorps() ;
		}
}

inline void CEcoGravitation::AfficheVertical( LPDIRECTDRAWSURFACE lpDessin, int x )
{
	int L, H ;
	DDGetSize( lpDessin, &L, &H ) ;

	for ( int y = 0; y < Hauteur; y += H )
		_lpBackBuffer->BltFast( x, y, lpDessin, CRect( 0, 0, 1, min( H, Hauteur-y)), 0 ) ;
}


inline void CEcoGravitation::AfficheHorizontal( LPDIRECTDRAWSURFACE lpDessin, int y )
{
	int L, H ;
	DDGetSize( lpDessin, &L, &H ) ;

	for ( int x = 0; x < Largeur; x += L )
		_lpBackBuffer->BltFast( x, y, lpDessin, CRect( 0, 0, min( L, Largeur-x), 1), 0 ) ;
}
