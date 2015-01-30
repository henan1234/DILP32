///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.H
//	Interface de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////

#ifndef _ECONOMISEUR_H_
#include "..\economiseur generique\economiseur.h"

#define NB_MAX_ATOMES	50
#define NB_MAX_LIENS_PAR_ATOME	8
#define NB_MAX_LIENS	(NB_MAX_ATOMES*NB_MAX_LIENS_PAR_ATOME)
#define PI					3.14159
#define	DISTANCE_MAX		500.0
#define POINT_DE_FUITE		800.0

#define DIAMETRE_MAX_ATOME	40.0
#define DIAMETRE_MAX_LIEN	10

typedef struct
	{
	double x ;
	double y ;
	double z ;
	double Vx ;
	double Vy ;
	double Vz ;
	int NbLiens ;
	int NbMaxLiens ;
	int	AtomesLies[NB_MAX_LIENS_PAR_ATOME] ;
	}
	T_ATOME ;

typedef struct
	{
	int	Atome1 ;
	int	Atome2 ;
	}
	T_LIEN ;

typedef struct
	{
	POINT Origine ;
	POINT Destination ;
	}
	T_FANTOMELIEN ;


class	CLiaisons : public CEconomiseur
	{
	public :
		virtual void PeintFenetre( CDC & Dc, const CRect & R );
		CLiaisons( ) ;
		virtual	~CLiaisons() ;

		virtual	void InitSave( HWND	hWnd )  ;

		virtual	void Configuration( CPropertySheet * ) ;

		// Animation
		void		UpdateFenetre( CDC &, const CRect & ) ;
		virtual	void Animation( CDC&	Dc ) ;
		virtual void InitDC( CDC & )  ;
		virtual void FinDC( CDC & )  ;

		virtual	void Preferences() ;
		virtual void ValidePreferences() ;

private:
	virtual	void	OnTimer(UINT IdTimer) ;

	static inline void DessineBoutDeLien( CDC & Dc, double Sx, double Sy, double Sz, double Dx, double Dy, double Dz, COLORREF Couleur );
	
	static inline void DessineLiensCasses( CDC & Dc );
	static void	Dessine( CDC & Dc ) ;

	static BOOL Sature( int iAtome );
	
	void SupprimeLien( int Atome, int AtomeLie );
	void CreerLiens( void );
	void CasseLiens( void );
	inline void BougeAtomes( );
	static inline void CalculeAcceleration( void );
	static inline void CalculForces();
	static BOOL DejaLie( int Atome1, int Atome2 );

	void LierAtomes( int IndiceLien, int Atome1, int Atome2 );
	void PlaceAtomes( void );

	friend class CConfiguration ;
	friend class CDlgNombres ;


	static void Repulsions( void );
	BYTE	ChangeComposante( BYTE Composante ) ;
	} ;

#endif
