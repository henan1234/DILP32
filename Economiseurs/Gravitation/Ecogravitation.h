///////////////////////////////////////////////////////////////////////////////
// CEcoGravitation
//	Interface de l'economiseur Gravitation
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include <math.h>

#ifndef _ECONOMISEUR_H_
#include "..\Economiseur Generique\Economiseur.h"
#endif
#include "..\Economiseur Generique\RectAffichage.h"

#define			NB_MAX_CORPS			1000		// En attendant une machine plus rapide, pas la peine de prevoir plus
#define			NB_MAX_POUSSIERES		1000
#define			NB_COLORS				1024
#define			IMAGE_GROSSE_PLANETE	(NB_BITMAPS-3)
#define			IMAGE_PETITE_PLANETE	0
#define			IMAGE_ETOILE			7

#define			NB_MAX_IMAGES			16
#define			NB_MAX_DECORS			16
#define			NB_MAX_ETOILES			5000
#define			NB_COMETE				6
#define			PI						3.14159265359
#define			NB_MAX_COULEURS_ETOILES 20
#define			NB_MAX_COULEURS_COMETES	20

#define			WM_USER_PARAMETERS		(WM_USER+1)

//#define			NB_TAILLES_IMAGES		11		// Mieux vaut qu'elle soit impaire
#include "..\..\Classes\DibPal.h"
#include "..\..\Classes\Dib.h"
#include "Skin.h"

class	CDIBSurface ;
class	COptions ;

#define FLOTTANT double

class CDlgProcess ;

class	CEcoGravitation	:	public CEconomiseur
{
	public :
		CEcoGravitation (  ) ;
		virtual	~CEcoGravitation () ;

		virtual	void Configuration( CPropertySheet * )  ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Animation( CDC&	Dc )  ;
		virtual void InitDC( CDC & ) {} ;
		virtual void FinDC( CDC & )  ;

		virtual	void Preferences() ;
		void	PreferencesShareWare() ;

		virtual void ValidePreferences() ;

		void SaveFile( const char * pFileName );
		void LoadFile( const char * pFileName );
		void DefaultParameters() ;

		typedef	struct
				{
				FLOTTANT	x ;				// Coordonnee x
				FLOTTANT	y ;				// Coordonnee y
				FLOTTANT	z ;				// Coordonnee z
				FLOTTANT	vx ;			// Vitesse x
				FLOTTANT	vy ;			// Vitesse y
				FLOTTANT	vz ;			// Vitesse z
				FLOTTANT	Attraction ;	// Masse * G ( calculee une fois pour toutes )
				int			Image ;			// Numero de l'image
				FLOTTANT	Phase ;			// Phase de l'image pour l'animation
				int			BruitPoussiere ;// Dispersion des poussieres ( cometes seulement )
				FLOTTANT	Rotation ;		// Vitesse et sens de rotation
				}
				T_CORPS ;

		typedef	struct
				{
				// Tableau de pointeurs sur des dibs
				// Premiere dimension : les differentes tailles
				// deuxieme dimension : les phases
				CDIB		** Images ;
				int			NbTailles ;	// Depend de la taille initiale de l'image, pas besoin de 50
										// tailles intermediaires pour des toutes petites images
				UINT		NbPhases ;
				UINT		Rayon ;
				}
				T_IMAGE ;

		///////////////////////////////////////////////////////////////////////
		// Gestion des poussieres generees par les cometes
		///////////////////////////////////////////////////////////////////////
		typedef struct
			{
			FLOTTANT	x ;
			FLOTTANT	y ;
			FLOTTANT	vx ;
			FLOTTANT	vy ;
			int			Taille ;
			COLORREF	Couleur ;
			FLOTTANT	Vie ;
			}
			T_POUSSIERE ;

	public :
		COptions* GetOptions();
		COptions	*	_pOptions ;
		static	T_POUSSIERE		_Poussieres[ NB_MAX_POUSSIERES ] ;
		static	int				_NbPoussieres	;
		static	int				_NbBoucles ;

		void	GenerePoussiere( const T_CORPS & pCorps ) ;
		void	AfficherPoussieres() ;
		void	AvancerPoussieres( FLOTTANT	Delai ) ;

		static int		NbCorps			;
		static FLOTTANT	DeltaT ;
		static DWORD	DernierTemps ;

		static FLOTTANT	_DecalageX ;
		static FLOTTANT	_DecalageY ;
		static FLOTTANT	_DecalageVx ;
		static FLOTTANT _DecalageVy ;
		static DWORD	_DebutSysteme ;

		static int		_IndicePlusGros ;
		static int		_DelaiImages ;
		static DWORD	_DerniereImage ;
		
		static T_CORPS		_Corps[NB_MAX_CORPS] ;
		static T_IMAGE		_Bitmap[NB_MAX_IMAGES] ;

		static	CString		_DernierEvenement ;
		
		///////////////////////////////////////////////////////////////////////
		// Preferences
		///////////////////////////////////////////////////////////////////////
		//static BOOL		_AfficherRepere ;
		static FLOTTANT _ZoomInitial ;
		
		///////////////////////////////////////////////////////////////////////
		// Gestion des rectangles pour optimiser l'affichage
		///////////////////////////////////////////////////////////////////////
		static CRectAffichage	_NouveauxRectangles, _DerniersRectangles ;
		static CDIBSurface*	pDCIntermediaire ;


		CDIBPal	Palette ;
		
		int		ImagePourMasse( FLOTTANT	Masse ) ;
		void	GenereCorps( void ) ;
		void	ChargeBitmaps() ;
		void	CalculAccelerations( void ) ;

		///////////////////////////////////////////////////////////////////////
		// Fonctions mathematiques
		///////////////////////////////////////////////////////////////////////
		// ==================================================================================================
		// CalculeDistance
		//	Calcule la distance entre deux corps
		// ==================================================================================================
		static FLOTTANT CalculeDistance2D( const T_CORPS & T1, const T_CORPS & T2 )
			{
			const FLOTTANT DX	=	T1.x - T2.x ;
			const FLOTTANT DY	=	T1.y - T2.y ;
			
			return sqrt( (DX*DX) + (DY*DY) ) ;
			}
		static FLOTTANT	CalculeDistance( const T_CORPS & T1, const T_CORPS & T2 ) ;

		static FLOTTANT CalculeDistance2D( const T_CORPS & T2 )
			{
			return sqrt( (T2.x*T2.x) + (T2.y*T2.y) ) ;
			}

		static FLOTTANT CalculeDistance3D( const T_CORPS & T2 )
			{
			return sqrt( (T2.x*T2.x) + (T2.y*T2.y) + (T2.z*T2.z) ) ;
			}

		static 	FLOTTANT	CalculeDistance( const T_CORPS & T2 ) ;

		// ============================================================================
		// Converti les coordonnees dans l'univers en coordonnees sur l'ecran
		// ============================================================================
		static void CEcoGravitation::UniversToPixel( FLOTTANT x, FLOTTANT y, FLOTTANT, int * px, int * py ) ;
		inline	void	Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 ) ;
		
		inline	void	CalculVentSolaire( const T_CORPS & Cps, FLOTTANT * pdx, FLOTTANT *pdy ) ;

		///////////////////////////////////////////////////////////////////////
		// Fonctions d'affichage 
		///////////////////////////////////////////////////////////////////////
		inline void		AfficheRepere() ;
		void			AfficherTousLesCorps( ) ;
		inline	void	EffacerTousLesCorps( ) ;
		inline	int		RechercheEtoilePlusProche( const T_CORPS & Cps ) ;
		inline void		EffaceRectangle( const CRect & ) ;
		void			AfficheEtoiles( CDIB * pDib, const CRect & R ) ;
		virtual void	PeintFenetre( CDC &, const CRect & ) ;
		
		///////////////////////////////////////////////////////////////////////
		// Collisions
		///////////////////////////////////////////////////////////////////////
		inline	BOOL	Collision( const T_CORPS & Corp1, const T_CORPS & Corp2 ) ;
		void	Agglomeration( int	Indice1, int Indice2 ) ;
		void	Eclatement( int	Indice1, int Indice2 ) ;
		void	Rencontre( int	Indice1, int Indice2 ) ;

		///////////////////////////////////////////////////////////////////////
		// Modification du repere pour continuer a voir quelque chose
		///////////////////////////////////////////////////////////////////////
		static void	Recentre( ) ;
		static void	RecherchePlusGros( void ) ;

		static void	SupprimeCorps( int Indice )	 ;

		///////////////////////////////////////////////////////////////////////
		// Gestion de la boite de dialogue de configuration
		///////////////////////////////////////////////////////////////////////
		static void	ConfSlider( HWND hWnd, UINT Id, UINT NoTexte, int	Valeur, int Min, int Max ) ; 

	FLOTTANT AngleAleatoire( void );
	inline void GenereUneComete( void );

	friend	class	CPagesParametres ;

	static void		AjouteExplosion( int x , int y );
	static void		AfficheExplosions();
	static void		AfficheRepere( int x, int y, int Taille, COLORREF Couleur, BOOL Rectangles );
	static void		CalculZoom();
	static void		TriCorps( void );
	void			GenereSatellites( int Indice, int NbSatellites, int ImageMax, FLOTTANT DistanceMin, FLOTTANT DistanceMax );
	void	GenereCorpsOrbites();
	static inline FLOTTANT CalculeVitesseLiberation( const T_CORPS & );
	static FLOTTANT VitesseOrbiteCirculaire( const FLOTTANT & Distance, const FLOTTANT & Masse );
	static inline BOOL LostInSpace( const T_CORPS & );

private:
	static CSkin*		_pSkin ;

	static void AfficheInfos();
	static void DecaleElementsDecors( FLOTTANT dx, FLOTTANT dy );
	void LitImagesPlanetes( const TCHAR * pFileName );
	static FLOTTANT _RapportTailleBitmaps;
	void MetEnOrbiteAutour( T_CORPS &, const T_CORPS &, FLOTTANT );
	void GenereCorpsShareware();
	static void AfficherDecors();
	static void CalculeMinEtMaxZ( void );
	static FLOTTANT	_MaxZ ;
	static FLOTTANT _MinZ ;
	static int		_NbAffiches ;

	static inline int CalculeIndiceTaille( FLOTTANT z, int NbTailles );
	void RegisterDocTypes();
	void LitFlottants( FLOTTANT & F1, FLOTTANT & F2, FLOTTANT & F3, const char * pSection, UINT Rubrique );
	void LitFichier( FLOTTANT & Value, const char * pFichier, const char * pSection, UINT IdsValue );
	void LitInfosPlanetes( const char * NomPlanete, int IndicePlanete );
	void GenereDeFichier();
	void GenereVitessesOrbites( FLOTTANT CentreX, FLOTTANT CentreY, FLOTTANT CentreZ, FLOTTANT AttractionTotale, FLOTTANT Angles[] );
	void GenerePositionsAleatoires( FLOTTANT & CentreX, FLOTTANT & CentreY, FLOTTANT & CentreZ, FLOTTANT & AttractionTotale, FLOTTANT Angles[] );
	void PlaceDecors( void );

	typedef struct
		{
		FLOTTANT x ;
		FLOTTANT y ;
		CDIB Dib ;
		}
	T_ELEMENT_DECOR ;


	static T_ELEMENT_DECOR	_ElementsDecors[NB_MAX_DECORS] ;
	static int				_MaxHauteurDecor ; // Hauteur max des images de fond
	static int				_MaxLargeurDecor ;
	static int				_NbExplosions ;
	static POINTS			_Explosions[100] ;
	static CDIB				_Explosion ;

	void RemplirTableauDImages( T_IMAGE *, CDIB & ToutesLesPhases ) ;
	void ParametresApercu() ;
};

