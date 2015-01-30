///////////////////////////////////////////////////////////////////////////////
// EcoBrownien
// Interface de CEcoBrownien
///////////////////////////////////////////////////////////////////////////////
#ifndef _ECOBROWNIEN_H_
#define _ECOBROWNIEN_H_

#ifndef _ECONOMISEUR_H_
#include "..\Economiseur Generique\Economiseur.h"
#endif

#define			NB_MAX_CORPS		500		// En attendant une machine plus rapide, pas la peine de prevoir plus
#define			NB_MAX_COULEURS		8
#define			NB_BITMAPS			2
#define			NB_MAX_RECTS		100
#define			MAX_Z				1000
#define			MIN_Z				-100
#define			TAILLE_MAX			64
#define			TAILLE_MIN			8 
#define			NB_IMAGES			((TAILLE_MAX-TAILLE_MIN)/2)

class	CEcoBrownien : public CEconomiseur
{
	public :
		CEcoBrownien( ) ;
		virtual	~CEcoBrownien() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Configuration( CPropertySheet * ) ;
		virtual	void Animation( CDC&	Dc ) ;
		virtual void InitDC( CDC & Dc ) {} ;
		virtual void FinDC( CDC & Dc ) {} ;

		virtual	BOOL PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) ;
		virtual	void Preferences() ;

	typedef	struct
			{
			double	x ;
			double	y ;
			double	z ;
			double	vx ;
			double	vy ;
			double	vz ;

			int		Couleur ;
			int		IndiceImage ;
			}
			T_CORPS ;

private :
		// ================================================================= Types
	T_CORPS		Corps[NB_MAX_CORPS] ;

	CDIBSurface*	pBitmaps[NB_MAX_COULEURS][NB_IMAGES] ;

	///////////////////////////////////////////////////////////////////////////////
	// Preferences
	///////////////////////////////////////////////////////////////////////////////
	int		NbCorps			;
	int		NombreCouleurs	;
	double	CoeffAttraction	;
	double	DeltaTMax		;
	double	CoeffRebond		;
	double	DeltaT ;
	int		NbImages	;
	DWORD	DernierTemps ;

	CDIBPal	Palette ;
	CDIBSurface*	pDCIntermediaire ;

	CRectAffichage	Affichage ;

	void	ChargeUneBitmap( CDIB*	pDibReference, int i, int j, int	Taille ) ;
	void	ChargeBitmaps( void ) ;
	static	int	ChangeIntervalle( int Valeur, int DepMin, int DepMax, int DestMin, int DestMax ) ;
	static	void	Positif( double * pDouble ) ;
	static	void	Negatif( double * pDouble ) ;
	void	GenereCorps( void ) ;
	inline static	double	CalculeDistance( T_CORPS T1, T_CORPS T2 ) ;
	inline double Attirance( double Attraction, int Couleur1, int Couleur2 ) ;
	inline void	Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 ) ;
	void	Affiche( T_CORPS	*	pCorps ) ;
	void	Efface( T_CORPS	*	pCorps ) ;
	void	CalculAccelerations( void ) ;
	void	ConfSpin( HWND hWnd, UINT Id, UINT IdEdit, int	Valeur, int Min, int Max ) ;
private:
	int _TailleMax;
	int _TailleMin;

	friend class CPage2 ;
} ;

#endif