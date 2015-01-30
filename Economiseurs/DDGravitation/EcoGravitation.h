///////////////////////////////////////////////////////////////////////////////
// CEcoGravitation
//	Interface de l'economiseur Gravitation
///////////////////////////////////////////////////////////////////////////////
#ifndef _ECOGRAVITATION_H_
#define _ECOGRAVITATION_H_
#ifndef __DDRAW_INCLUDED__
#include <ddraw.h>
#endif
#ifndef _ECONOMISEUR_H_
#include "..\Economiseur Generique\Economiseur.h"
#endif

#define			NB_MAX_CORPS			1000		// En attendant une machine plus rapide, pas la peine de prevoir plus
#define			NB_MAX_POUSSIERES		1000
#define			NB_COLORS				1024
#define			IMAGE_COMETE			1
#define			IMAGE_GROSSE_PLANETE	(NB_BITMAPS-3)
#define			IMAGE_PETITE_PLANETE	0
#define			IMAGE_ETOILE			7

#define			NB_BITMAPS				8
#define			NB_COMETE				6
#define			PI						3.14159265359

#include "..\..\Classes\DibPal.h"

class	CDibSurface ;
#define FLOTTANT double

class CDirectDrawSurface	;
class	CEcoGravitation	:	public CEconomiseur
{
	public :
		CEcoGravitation ( const CString & NomEconomiseur, const CString & ValeurEnregistre ) ;
		virtual	~CEcoGravitation () ;

		virtual	void Configuration( CPropertySheet * )  ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Animation( CDC&	Dc )  ;
		virtual void InitDC( CDC & ) ;
		virtual void FinDC( CDC & ) ;

		virtual	void Preferences() ;
		virtual void ValidePreferences() ;

		typedef	struct
				{
				FLOTTANT	x ;
				FLOTTANT	y ;
				FLOTTANT	vx ;
				FLOTTANT	vy ;
				//FLOTTANT	Masse ;
				FLOTTANT	Attraction ;
				BYTE		Image ;
				FLOTTANT	Phase ;
				}
				T_CORPS ;

		typedef	struct
				{
//				CDIB		Image ;
				CDirectDrawSurface * lpImage ;
				FLOTTANT	MasseMax ;
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

	protected :
		virtual BOOL	ChargeEtat( const char * ) ;
		virtual	BOOL	SauveEtat( const char * )  ;

	private :
		static	T_POUSSIERE		_Poussieres[ NB_MAX_POUSSIERES ] ;
		static	int				_NbPoussieres	;
		static	int				_NbMaxPoussieres ;
		static	FLOTTANT		_VentSolaire	;
		static	int				_ViePoussieres ;
		static	int				_BruitPoussieres ;
		static	int				_TaillePoussieres ;

		inline	void	GenerePoussiere( const T_CORPS & pCorps ) ;
		inline	void	AfficherPoussieres() ;
		inline	void	AvancerPoussieres() ;

		static int		NbCorps			;
		static FLOTTANT	DistanceMax ;
		static FLOTTANT	DeltaT ;
		static DWORD	DernierTemps ;

		static FLOTTANT	_DecalageX ;
		static FLOTTANT	_DecalageY ;
		static FLOTTANT	_DecalageVx ;
		static FLOTTANT _DecalageVy ;

		static int		_IndicePlusGros ;
		static int		_DelaiImages ;
		static DWORD	_DerniereImage ;
		
		static T_CORPS		_Corps[NB_MAX_CORPS] ;
		static T_IMAGE		_Bitmap[NB_BITMAPS] ;
		//static FLOTTANT			_Repere ;			// Pour afficher le repere autour du plus gros corps

		///////////////////////////////////////////////////////////////////////
		// Preferences
		///////////////////////////////////////////////////////////////////////
		static int		NbMaxCorps		;
		static int		NbMinCorps		;
		static int		NbInitCorps		;
		static FLOTTANT	CoeffDistance	;
		static FLOTTANT	CoeffRayon		;
		static FLOTTANT	DeltaTMax		;
		static FLOTTANT	_IntervalleTemps ;
		static FLOTTANT	_CoeffLiberation ;
		static FLOTTANT	_DeltaVMax	;
		static FLOTTANT	_CoeffTraveling	;
		static int		_DensiteEtoiles ;
		static int		_NbImagesSecondes ;
		static FLOTTANT	_G	;	// constante de gravitation
		static int		_Depart ;
		static BOOL		 _Effacer;
		static BOOL		_AfficherRepere ;
		static FLOTTANT _ZoomMax ;
		static FLOTTANT _ZoomInitial ;
		static FLOTTANT	_TailleRepere ;
		static FLOTTANT _DistanceMax ;

		///////////////////////////////////////////////////////////////////////
		// Gestion des rectangles pour optimiser l'affichage
		///////////////////////////////////////////////////////////////////////
		static CRectAffichage	_NouveauxRectangles, _DerniersRectangles ;

		static LPDIRECTDRAW			lpDD ;
		static LPDIRECTDRAWSURFACE	lpPrimary ;
		static LPDIRECTDRAWPALETTE	lpPalette ;
		static LPDIRECTDRAWSURFACE	lpIntermediaire ;
		
		int	ImagePourMasse( FLOTTANT	Masse ) ;
		void	GenereCorps( void ) ;
		void	ChargeBitmaps( void ) ;
		void	CalculAccelerations( void ) ;

		///////////////////////////////////////////////////////////////////////
		// Fonctions mathematiques
		///////////////////////////////////////////////////////////////////////
		static inline	FLOTTANT	CalculeDistance( const T_CORPS & T1, const T_CORPS & T2 ) ;
		static inline			FLOTTANT	CalculeDistance( const T_CORPS & T2 ) ;
		inline	void	Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 ) ;
		
		inline	void	CalculVentSolaire( const T_CORPS & Cps, FLOTTANT * pdx, FLOTTANT *pdy ) ;

		///////////////////////////////////////////////////////////////////////
		// Fonctions d'affichage 
		///////////////////////////////////////////////////////////////////////
		inline void		AfficheRepere() ;
		inline	void	AfficherTousLesCorps( ) ;
		inline	void	EffacerTousLesCorps( ) ;
		inline	int		RechercheEtoilePlusProche( const T_CORPS & Cps ) ;
				void	EffaceRectangle( const CRect & ) ;
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

	int _CreationComete;
	inline FLOTTANT AngleAleatoire( void );
	inline void GenereUneComete( void );

	friend	class	CPage2 ;
	friend	class	CPageGenese ;
	friend	class	CPageComete ;
	friend	class	CPagePhysique ;
	friend	class	CPageAffichage ;
	friend	class	CPageMasses ;

private:
	static void AjouteExplosion( int x , int y );
	static void AfficheExplosion( FLOTTANT x, FLOTTANT y );
	static void AfficheRepere( int x, int y, int Taille, COLORREF Couleur, BOOL Rectangles );
	static inline void CalculZoom();
	static void TriCorps( void );
	void	GenereSatellites( int Indice, int NbSatellites, int ImageMax, FLOTTANT DistanceMin, FLOTTANT DistanceMax );
	void	GenereCorpsOrbites();
	static inline FLOTTANT CalculeVitesseLiberation( const T_CORPS & );
	static inline FLOTTANT VitesseOrbiteCirculaire( const FLOTTANT & Distance, const FLOTTANT & Masse );
	static inline void UniversToPixel( int x, int y, int * px, int * py );
	static inline BOOL LostInSpace( const T_CORPS & );
	};

#endif
