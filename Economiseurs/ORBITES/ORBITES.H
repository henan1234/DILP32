///////////////////////////////////////////////////////////////////////////////
// CEcoOrbite
///////////////////////////////////////////////////////////////////////////////
#ifndef __ORBITE_H__
#define __ORBITE_H__

#ifndef __ECONOMISEUR_H__
#include "..\Economiseur Generique\Economiseur.h"
#endif

#define	NB_MAX_POINTS		50

class	CEcoOrbite	:	public	CEconomiseur
	{
	public :
		CEcoOrbite() ;
		virtual ~CEcoOrbite() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual void InitConfig( HWND hWnd ) ;

		virtual	void Animation( CDC&	Dc, BOOL	PremiereFois ) ;

		virtual	BOOL PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) ;

		virtual	void Preferences() ;

	private :
		double				_Angles[ NB_MAX_POINTS ] ;
		int					_NbPoints ;
		CRectAffichage		_Affichage ;
		CDIBSurface*		_pIntermediaire ;
		double				_Step ;
		double				_RapportVitesse	;
		double				_RapportLongueur ;
		CDIB*				_pDIB ;
		CDIBPal*			_pPalette ;

		inline CPoint		CalculePos( CPoint Pt, double _Angle, int Rayon ) const ;
		inline void			Affiche( CPoint Pt ) ;
		inline void			Affiche( CPoint Pt1, CPoint Pt2 ) ;
	} ;

#endif