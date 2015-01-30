///////////////////////////////////////////////////////////////////////////////
// CEcoGravitation
//	Implementation de l'economiseur Gravitation
// Cet economiseur simule un bout d'espace et les forces de gravites entre
// les differents corps
// 4/4/97 : optimisation : on calcule une fois pour toute l'attraction qu'exerce
//			un corps en stockant Attraction = Masse * G
///////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"
#include "math.h"
#include "signal.h"
#include "resource.h"

#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\DibPal.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "EcoGravitation.h"
#include "Page1.h"
#include "Page2.h"
#include "PageGenese.h"
#include "PageComete.h"
#include "PagePhysique.h"
#include "PageAffichage.h"
#include "PageMasses.h"

#define ABS(x)	(x > 0 ? x : -x)

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

int		CEcoGravitation::_Depart= 0 ;		// 0 : tous les corps partent avec une vitesse nulle
											// 1 : tous les corps partent en orbite circulaire autour du centre de gravite
											// 2 : tous les corps partent en orbite approximativement circulaire autour du centre de gravite

CEcoGravitation::T_CORPS		CEcoGravitation::_Corps[NB_MAX_CORPS] ;
CEcoGravitation::T_IMAGE		CEcoGravitation::_Bitmap[NB_BITMAPS] ;
CRectAffichage	CEcoGravitation::_NouveauxRectangles ;
CRectAffichage	CEcoGravitation::_DerniersRectangles ;
CDIBSurface*	CEcoGravitation::pDCIntermediaire ;
BOOL			CEcoGravitation::_Effacer ;
BOOL			CEcoGravitation::_AfficherRepere ;
FLOTTANT		CEcoGravitation::_ZoomMax ;
FLOTTANT		CEcoGravitation::_ZoomInitial ;
FLOTTANT		CEcoGravitation::_TailleRepere ;
FLOTTANT		CEcoGravitation::_DistanceMax ;


POINTS			Explosions[100] ;
int				NbExplosions	=	0 ;
BOOL			CEcoGravitation::_ChangeResolution	=	FALSE ;

typedef struct
	{
	RECT	R ;
	CDIB * pDib ;
	}
	T_ELEMENT_DECOR ;

#define NB_ELEMENTS_DECOR	6

T_ELEMENT_DECOR	ElementsDecors[NB_ELEMENTS_DECOR] ;


///////////////////////////////////////////////////////////////////////////////
// Important ! Il doit exister un et un seul objet CEcoGravitation
///////////////////////////////////////////////////////////////////////////////
CEcoGravitation CeciEstMonEconomiseur( "Gravitation shareware", "8597" ) ;
CDIB	Explosion ;

// Juste pour eviter les divide by zero
void _cdecl ErreurFlottant( int sig )
{
}

CEcoGravitation::CEcoGravitation ( const CString & NomEconomiseur, const CString & ValeurEnregistre )
:CEconomiseur( NomEconomiseur, ValeurEnregistre )
	{
	// Initialisation des preferences pour le cas ou la version shareware
	// ne les lirais pas dans la registry
	NbMaxCorps			=	300 ;			// Nombre max de corps
	NbMinCorps			=	3 ;				// Nombre min de corps avant de regenerer
	NbInitCorps			=	50 ;			// Nombre initial de corps
	NbCorps				=	0 ;				// Nombre actuel de corps

	_Depart				=	3 ;

	_G					=	200000. ;
	CoeffDistance		=	5. ;			// Coeff multiplicateur de distance
	_IntervalleTemps	=	2.0000000000000001e-004 ;		// Intervalle fictif de temps entre deux calculs
	CoeffRayon			=	0.15 ;			// Coeff multiplicateur de rayon ( pour les collisions )
	_CoeffLiberation	=	20 ;
	_DeltaVMax			=	1 ;			// Vitesses relatives max pour collision 

	_ZoomMax			=	1 ;
	_ZoomInitial		=	CoeffDistance ;

	_VentSolaire		=	400 ;
	_CreationComete		=	500 ;
	_NbMaxPoussieres	=	200 ;
	_TaillePoussieres	=	2 ;
	_BruitPoussieres	=	50 ;
	_ViePoussieres		=	3 ;

	_CoeffTraveling		=	0.01 ;			// Coefficient de deplacement de l'affichage
	_NbImagesSecondes	=	25 ;
	_DensiteEtoiles		=	400 ;
	_Depart				=	3 ;
		
	// Valeurs caracteristiques du systeme solaire
	_Bitmap[0].MasseMax	=	1 ;
	_Bitmap[1].MasseMax	=	2 ;
	_Bitmap[2].MasseMax	=	4 ;
	_Bitmap[3].MasseMax	=	8 ; 
	_Bitmap[4].MasseMax	=	16 ;
	_Bitmap[5].MasseMax	=	32 ;
	_Bitmap[6].MasseMax	=	64 ;
	_Bitmap[7].MasseMax	=	256 ;
	

	_ChangeResolution	=	FALSE ;
	_Effacer			=	TRUE ;
	_AfficherRepere		=	FALSE ;

	_DecalageX	=	0 ;
	_DecalageY	=	0 ;
	_DecalageVx	=	0 ;
	_DecalageVy	=	0 ;


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
inline void	CEcoGravitation::EffaceRectangle( const CRect & R )
	{

	pDCIntermediaire->FillBits( R.left, R.top, R.Width(), R.Height(), PALETTEINDEX( 0 ) ) ;

	if ( ! Apercu())
		{
		// Eventuellement afficher un element de decor
		for ( int i = 0; i < NB_ELEMENTS_DECOR; i++)
			{
			RECT Rect ;
			if ( ::IntersectRect( &Rect, &ElementsDecors[i].R, R ))
				ElementsDecors[i].pDib->CopyBits( pDCIntermediaire, &Rect,
												  Rect.left - ElementsDecors[i].R.left, 
												  Rect.top - ElementsDecors[i].R.top,
												  PALETTEINDEX( 0 )) ;
			}
		}

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
			pDCIntermediaire->SetPixelV(	Alea( R.left, R.right-1 ),
											Alea( R.top, R.bottom-1 ),
											PALETTEINDEX( CouleursEtoiles[ Alea( 0, NB_COULEURS_ETOILES )])) ;
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
/*
	for ( int i = 1; i < NbCorps; i++)
		if ( _Corps[i].Attraction > _Corps[_IndicePlusGros].Attraction )
			_IndicePlusGros	=	i ;*/
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
	PlaceDecors() ;
}

// ==================================================================================================
// Charge les bitmaps necessaires a l'affichage
// On calcule le nombre de phase de chaque bitmap en divisant la largeur par la hauteur (chaque
// phase est a cote es autres )
// ==================================================================================================
void	CEcoGravitation::ChargeBitmaps( void )
{
	const int BaseBitmaps	=	2000 ;
	
	for ( int i = 0; i < NB_BITMAPS; i++ )
		{
		_Bitmap[i].Image.Load( BaseBitmaps+i ) ;

		_Bitmap[i].Rayon		=	_Bitmap[i].Image.GetHeight() / 2 ;

		_Bitmap[i].NbPhases	=	max( 1, _Bitmap[i].Image.GetWidth() / _Bitmap[i].Image.GetHeight() ) ;
		}

	Explosion.Load(IDB_EXPLOSION) ;

	// Charge les bitmaps d'elements de decor
	ElementsDecors[0].pDib	=	new CDIB ;
	ElementsDecors[1].pDib	=	new CDIB ;
	ElementsDecors[2].pDib	=	new CDIB ;
	ElementsDecors[3].pDib	=	new CDIB ;
	ElementsDecors[4].pDib	=	new CDIB ;
	ElementsDecors[5].pDib	=	new CDIB ;
	ElementsDecors[6].pDib	=	new CDIB ;

	ElementsDecors[0].pDib->Load( IDR_DECOR0 );
	ElementsDecors[1].pDib->Load( IDR_DECOR1 );
	ElementsDecors[2].pDib->Load( IDR_DECOR2 );
	ElementsDecors[3].pDib->Load( IDR_DECOR3 );
	ElementsDecors[4].pDib->Load( IDR_DECOR4 );
	ElementsDecors[5].pDib->Load( IDR_DECOR5 );
	ElementsDecors[6].pDib->Load( IDR_DECOR6 );
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation du screen saver en mode animation
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::InitSave( HWND	hWnd )
	{
	if ( ! Apercu())
		if ( _ChangeResolution )
		{
		if ( ! ChangeResolution( 1280, 1024, COLOR_256 ))
		if ( ! ChangeResolution( 1152, 864, COLOR_256 ))
		if ( ! ChangeResolution( 1024, 768, COLOR_256 ))
		if ( ! ChangeResolution( 800, 600, COLOR_256 ))
		if ( ! ChangeResolution( 1280, 1023, -1 ))
		if ( ! ChangeResolution( 1152, 864, -1 ))
		if ( ! ChangeResolution( 1024, 768, -1 ))
			   ChangeResolution( 800, 600, -1 ) ;
		}

	signal( SIGFPE, ErreurFlottant ) ;
    
	NoircirEcran = TRUE ;
	CEconomiseur::InitSave( hWnd ) ;
	
	_ZoomInitial	=	CoeffDistance ;
	_TailleRepere	=	(min( Largeur, Hauteur )/6)/10 ;
	
	ChargeBitmaps() ;
	GenereCorps() ;
	
	Palette.Create( &_Bitmap[0].Image ) ;
	SetPalette( (HPALETTE)Palette.m_hObject ) ;

	///////////////////////////////////////////////////////////////////////////
	// DC Intermediaire pour affichage sans clignotement
	///////////////////////////////////////////////////////////////////////////
	pDCIntermediaire	=	new CDIBSurface ;
	pDCIntermediaire->Create( Largeur, Hauteur, &Palette ) ;

	EffaceRectangle( CRect( 0, 0, Largeur, Hauteur )) ;

	_DerniersRectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;
	_NouveauxRectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;

	DernierTemps		=	GetCurrentTime() ;
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
	const int PlusProche	=	RechercheEtoilePlusProche(Cps) ;

	const FLOTTANT	Distance	=	CalculeDistance( Cps, _Corps[PlusProche] ) ; // / CoeffDistance ;
	if ( Distance == 0.0 )
		{
		*pdx	=	0 ;
		*pdy	=	0 ;
		}
	else
		{
		*pdx	=	(Cps.x - _Corps[PlusProche].x )  * (_VentSolaire / Distance ) ;
		*pdy	=	(Cps.y - _Corps[PlusProche].y )  * (_VentSolaire / Distance ) ;
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

	const FLOTTANT PourcentX		=	Alea( 100-Cps.BruitPoussiere, 100+Cps.BruitPoussiere ) ;
	const FLOTTANT PourcentY		=	Alea( 100-Cps.BruitPoussiere, 100+Cps.BruitPoussiere ) ;
	const int HauteurComete			=	_Bitmap[IMAGE_COMETE].Image.GetHeight() / 2 ;

	_Poussieres[_NbPoussieres].x	=	Cps.x + Alea( -HauteurComete, HauteurComete )*CoeffDistance ;
	_Poussieres[_NbPoussieres].y	=	Cps.y + Alea( -HauteurComete, HauteurComete )*CoeffDistance ;

	_Poussieres[_NbPoussieres].vx	=	Cps.vx + (dx * (PourcentX / 100.0) );
	_Poussieres[_NbPoussieres].vy	=	Cps.vy + (dy * (PourcentY / 100.0) );

	_Poussieres[_NbPoussieres].Couleur	=	PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
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
			if ( NbFois & 1 )
				{
				AfficheRepere( x, y, Taille, PALETTEINDEX( 105 ), TRUE ) ;
				AfficheRepere( x, y, Taille*10, PALETTEINDEX( 220 ), FALSE ) ;
				}
			else
				{
				AfficheRepere( x, y, Taille, PALETTEINDEX( 107 ), TRUE ) ;
				AfficheRepere( x, y, Taille*10, PALETTEINDEX( 127 ), FALSE ) ;
				}
			break ;
			}

		NbFois ++ ;
		if ( NbFois >= 1000)
			break ; // Pour eviter des plantages

		Mult /= 5.0 ;
		}

  // Affichage de l'origine
	pDCIntermediaire->FillBits( x, 0,1, Hauteur, PALETTEINDEX( 143 )) ;
	_NouveauxRectangles += CRect( x, 0, x+1, Hauteur ) ;
	pDCIntermediaire->FillBits( 0, y, Largeur, 1, PALETTEINDEX( 143 )) ;
	_NouveauxRectangles += CRect( 0, y, Largeur, y+1 ) ;
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
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

		if (! R.IsRectEmpty())
			{
			_NouveauxRectangles += R ;

			_Bitmap[_Corps[i].Image].Image.CopyBits( pDCIntermediaire,
													R.left, R.top,	R.right-R.left, R.bottom-R.top,
													DecalageX + (int)_Corps[i].Phase*Rayon*2,DecalageY,
													PALETTEINDEX( 0 )) ;
			}
		
		// Changer de phase
		(_Corps[i].Phase) += DeltaT / _IntervalleTemps / 400.0 ;
		
		if ( _Corps[i].Phase >= _Bitmap[_Corps[i].Image].NbPhases)
			_Corps[i].Phase = 0 ;

		// Generer de la poussiere si le corps est une comete
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
	const	int	NbRects	=	_DerniersRectangles.NbRectangles() ;

	for ( int i = 0; i < NbRects; i++)
		EffaceRectangle( _DerniersRectangles.Rectangle( i ) ) ;
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

	AjouteExplosion( (int)_Corps[Indice1].x, (int)_Corps[Indice1].y ) ;
	
	// Ce nouveau corps est peut etre le plus gros de tous
	if ( _Corps[Indice1].Attraction > _Corps[_IndicePlusGros].Attraction )
		RecherchePlusGros() ;

	// Supprimer le deuxieme corps
	SupprimeCorps( Indice2 ) ;

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
	
	AjouteExplosion( (int)_Corps[Indice1].x, (int)_Corps[Indice1].y ) ;

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

	const int NbPouss	=	Alea( 5, 50 ) ;

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

		_Poussieres[_NbPoussieres].Couleur	=	PALETTEINDEX( Alea(1, 255)) ; // PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
		_Poussieres[_NbPoussieres].Vie		=	Alea( _ViePoussieres/2, _ViePoussieres ) * _NbImagesSecondes ;
		_Poussieres[_NbPoussieres].Taille	=	Alea( 1, _TaillePoussieres ) ;

		_NbPoussieres ++ ;
		}
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

	if ( Dist < Largeur / 4 )
		{
		_DecalageX	=	0 ;
		_DecalageY	=	0 ;
		_DecalageVx	=	0 ; //_Corps[_IndicePlusGros].vx * 0.5 ;
		_DecalageVy	=	0 ; //_Corps[_IndicePlusGros].vx * 0.5 ;
		return ;
		}
	else
	if ( Dist	< Largeur / 2 )
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

// ============================================================================
// C'est d'ici que part l'animation
// ============================================================================
void CEcoGravitation::Animation( CDC&	Dc ) 
	{
	//static	DWORD	NbCoups	=	0 ;
	int	i	;

	// Pour garder une vitesse constante quelle que soit le temps mis pour les calculs
	const DWORD TempsCourant	=	GetCurrentTime ();
	DeltaT			=	(TempsCourant-DernierTemps) * _IntervalleTemps ;
	DernierTemps	=	TempsCourant ;
	
		
	// Calcul des interactions qu'exercent les corps les uns sur les autres
	CalculAccelerations() ;

	// Deplace les corps
	for ( i = 0; i < NbCorps; i++)
		{
		_Corps[i].x	+=	(_Corps[i].vx * DeltaT) ;
		_Corps[i].y	+=	(_Corps[i].vy * DeltaT)  ;
		}

	//NbCoups ++ ;

	// Est-il temps de s'occuper de l'affichage ?
	if ( TempsCourant >= _DerniereImage + _DelaiImages )
		{
		
		//Recentre() ;
		CalculZoom() ;

		// Generation aleatoire de comete
		if ( NbCorps <= NbInitCorps / 2 )
			if ( UnSur( _CreationComete ))
					GenereUneComete() ;

		if ( _Effacer )
			EffacerTousLesCorps() ;

		AfficherTousLesCorps() ;
		AvancerPoussieres( (TempsCourant - _DerniereImage) * _IntervalleTemps ) ;
		AfficherPoussieres() ;

		AfficheExplosions() ;
		NbExplosions	=	0 ;

		// Transferer a l'ecran les nouvelles images et les effacements
		_DerniersRectangles +=	_NouveauxRectangles ;
		_DerniersRectangles.BitBlt( Dc.m_hDC, pDCIntermediaire->GetHDC()) ;

		_DerniersRectangles	=	_NouveauxRectangles ;
		_NouveauxRectangles.Vide() ;

		_DerniereImage	=	TempsCourant ;

		// Regenerer tous les corps si leur nombre est devenu trop petit
		if ( NbCorps < NbMinCorps )
			{
			InvalidateRect( _hWnd, NULL, TRUE ) ;
			GenereCorps() ;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////	
// PeintFenetre
//	Peint la fenetre dans son etat initial
///////////////////////////////////////////////////////////////////////////////	
void	CEcoGravitation::PeintFenetre( CDC & Dc, const CRect& R)
{
	EffaceRectangle(R) ;
	_DerniersRectangles += R ;
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
	Preference( "Changer resolution", _ChangeResolution ) ;

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
inline void	CEcoGravitation::AvancerPoussieres( FLOTTANT Delai )
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
			_Poussieres[i].x	+= (_Poussieres[i].vx * Delai) ;
			_Poussieres[i].y	+= (_Poussieres[i].vy * Delai) ;
			}
		}
}


///////////////////////////////////////////////////////////////////////////////
// Affichage des grains de poussieres generes par les cometes
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AfficherPoussieres()
{
	int dx, dy ;
	int x, y ;
		
	for ( int i = 0; i < _NbPoussieres; i++)
		{
		UniversToPixel( _Poussieres[i].x, _Poussieres[i].y, &x, &y ) ;
		
		if ( (x >=0) && (y >= 0) && (x < Largeur) && (y < Hauteur) )
			{
			CRect	R( x, y, x + _Poussieres[i].Taille, y + _Poussieres[i].Taille ) ;

			_NouveauxRectangles.LimiteRect( R, &dx, &dy ) ;
			_NouveauxRectangles += R ;

			pDCIntermediaire->FillBits( x, y, _Poussieres[i].Taille, _Poussieres[i].Taille, _Poussieres[i].Couleur ) ;
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



///////////////////////////////////////////////////////////////////////////////
// Generation aleatoire d'une comete
///////////////////////////////////////////////////////////////////////////////
inline void CEcoGravitation::GenereUneComete( void )
{
	if ( NbCorps >= NbMaxCorps-1 )
		return ;

	const FLOTTANT	Distance	=	Alea( max(Largeur, Hauteur)/2, max( Largeur, Hauteur)) * CoeffDistance ;
	const FLOTTANT	Angle		=	AngleAleatoire() ;
	const FLOTTANT	Vitesse		=	VitesseOrbiteCirculaire( Distance, _Corps[_IndicePlusGros].Attraction ) ;

	// Pour ne pas obtenir un orbite circulaire, on diminue un peu la vitesse
	const FLOTTANT	VitesseReelle	=	Vitesse * (FLOTTANT)Alea( 10, 60 ) / 100.0 ;
	
	_Corps[NbCorps].vx	=	VitesseReelle * sin( Angle + PI/2 ) + _Corps[_IndicePlusGros].vx ;
	_Corps[NbCorps].vy	=	VitesseReelle * cos( Angle + PI/2 ) + _Corps[_IndicePlusGros].vy ;

	_Corps[NbCorps].x	=	_Corps[_IndicePlusGros].x	+	Distance * sin( Angle ) ;
	_Corps[NbCorps].y	=	_Corps[_IndicePlusGros].y	+	Distance * cos( Angle ) ;

	_Corps[NbCorps].Attraction=	_Bitmap[ IMAGE_COMETE ].MasseMax  * _G ;
	_Corps[NbCorps].Image=	IMAGE_COMETE ;
	_Corps[NbCorps].Phase=	0 ;

	// Coefficient de dispersion des poussieres propre a chaque comete
	_Corps[NbCorps].BruitPoussiere	=	(int)(_BruitPoussieres *  Alea( 60, 140 ) / 100.0 ) ;
	if ( _Corps[NbCorps].BruitPoussiere < 0 )
		_Corps[NbCorps].BruitPoussiere = 0 ;
	else
		if ( _Corps[NbCorps].BruitPoussiere > 100 )
			_Corps[NbCorps].BruitPoussiere	=	100 ;

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
	
	pPropSheet->SetTitle( "Gravitation settings" ) ;

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
inline FLOTTANT CEcoGravitation::CalculeVitesseLiberation( const T_CORPS & Corps )
{
	const FLOTTANT	Distance	=	CalculeDistance( Corps ) ;
	return sqrt( 2 * _Corps[_IndicePlusGros].Attraction / Distance ) ;	
}

// ============================================================================
// Converti les coordonnees dans l'univers en coordonnees sur l'ecran
// ============================================================================
inline void CEcoGravitation::UniversToPixel( FLOTTANT x, FLOTTANT y, int * px, int * py )
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

	for ( i = 0; i < _NbPoussieres; i++ )
		{
		_Poussieres[i].x -= _DecalageX ;
		_Poussieres[i].y -= _DecalageY ;

		_Poussieres[i].vx-= _DecalageVx ;
		_Poussieres[i].vy-= _DecalageVy ;
		}

	/*for ( i = 0; i < NbExplosions; i++)
		{
		Explosions[i].x	-= _DecalageX ;
		Explosions[i].y	-= _DecalageY ;
		}*/
}

///////////////////////////////////////////////////////////////////////////////
// Affichage des lignes du repere, l'origine est affichee a part
///////////////////////////////////////////////////////////////////////////////
inline void CEcoGravitation::AfficheRepere( int x, int y, int Taille, COLORREF Couleur, BOOL Rectangles )
{
	///////////////////////////////////////////////////////////////////////////
	// Traits verticaux
	///////////////////////////////////////////////////////////////////////////
	for ( int i = x+Taille; i < Largeur-1; i += Taille )
		{
		pDCIntermediaire->FillBits( i, 0,1, Hauteur, Couleur) ;
		if ( Rectangles )
			_NouveauxRectangles += CRect( i, 0, i+1, Hauteur ) ;
		}

	for ( i = x-Taille; i > 0; i -= Taille )
		{
		pDCIntermediaire->FillBits( i, 0,1, Hauteur, Couleur) ;
		if ( Rectangles )
			_NouveauxRectangles += CRect( i, 0, i+1, Hauteur ) ;
		}
		
	///////////////////////////////////////////////////////////////////////////
	// Traits horizontaux
	///////////////////////////////////////////////////////////////////////////
	for ( i = y+Taille; i < Hauteur-1; i += Taille )
		{
		pDCIntermediaire->FillBits( 0, i, Largeur, 1, Couleur) ;

		if ( Rectangles )
			_NouveauxRectangles += CRect( 0, i, Largeur, i+1 ) ;
		}

	for ( i = y-Taille; i > 0; i -= Taille )
		{
		pDCIntermediaire->FillBits( 0, i, Largeur, 1, Couleur) ;

		if ( Rectangles )
			_NouveauxRectangles += CRect( 0, i, Largeur, i+1 ) ;
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

inline void CEcoGravitation::TriCorps()
	{
	qsort( _Corps, NbCorps, sizeof( T_CORPS ), CompareCorps ) ;
	}

void CEcoGravitation::AfficheExplosions()
{
	for ( int i = 0; i < NbExplosions; i++)
		{
		CRect R ;
		R.left	=	Explosions[i].x - Explosion.GetWidth() / 2 ;
		R.top	=	Explosions[i].y - Explosion.GetHeight() / 2 ;

		R.right	=	R.left + Explosion.GetWidth() ;
		R.bottom=	R.top + Explosion.GetHeight() ;
				
		int DecalageX, DecalageY ;
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

		if (! R.IsRectEmpty())
			{
			_NouveauxRectangles += R ;

			Explosion.CopyBits( pDCIntermediaire,
								R.left, R.top,	R.right-R.left, R.bottom-R.top,
								DecalageX,DecalageY,
								PALETTEINDEX( 0 )) ;
			}
	}
}


///////////////////////////////////////////////////////////////////////////////
// AjouteExplosion
// Ajoute une explosion a la liste.
// ENTREES :	Coordonnees x et y ( univers )
// SORTIES :	rien
// REMARQUE :
//	On stocke les coordonnees ECRAN pour etre certain que l'explosion va
//	s'afficher a l'endroit ou on a vu les corps se rencontrer, meme si le
//	repere change d'ici au prochain affichage
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AjouteExplosion( int x , int y )
{
	if ( NbExplosions >= sizeof(Explosions)/sizeof(Explosions[0]))
		return ;

	int Px, Py ;
	UniversToPixel( x, y, &Px, &Py ) ;

	Explosions[NbExplosions].x	=	Px ;
	Explosions[NbExplosions].y	=	Py ;

	NbExplosions ++ ;
}

void CEcoGravitation::FinDC( CDC & )
	{
	}


///////////////////////////////////////////////////////////////////////////////
// Placer les elements de decors
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::PlaceDecors( void )
{
	if ( Apercu())
		return ;

	for ( int i = 0; i < NB_ELEMENTS_DECOR; i++)
		{
		const int	TailleX	=	ElementsDecors[i].pDib->GetWidth() ;
		const int	TailleY	=	ElementsDecors[i].pDib->GetHeight() ;

		BOOL Chevauche ;

		if ( i == 0 )
			{
			ElementsDecors[i].R.left	=	Largeur - TailleX ;
			ElementsDecors[i].R.top		=	Hauteur - TailleY  ;
			ElementsDecors[i].R.right	=	ElementsDecors[i].R.left +TailleX  ;
			ElementsDecors[i].R.bottom	=	ElementsDecors[i].R.top	+ TailleY ;
			}
		else
			{
			do
				{
				ElementsDecors[i].R.left	=	Alea( 0, Largeur - TailleX ) ;
				ElementsDecors[i].R.top		=	Alea( 0, Hauteur - TailleY ) ;
				ElementsDecors[i].R.right	=	ElementsDecors[i].R.left	+TailleX  ;
				ElementsDecors[i].R.bottom	=	ElementsDecors[i].R.top	+ TailleY ;

				Chevauche	=	FALSE ;
				for ( int j = 0; j < i; j++)
					{
					RECT R ;
					if ( IntersectRect( &R, &ElementsDecors[i].R, &ElementsDecors[j].R ))
						{
						Chevauche	=	TRUE ;
						break ;
						}
					}
				}
			while ( Chevauche ) ;
			}
		}
}
