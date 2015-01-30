// TasDeSable.h: interface for the CTasDeSable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TASDESABLE_H__CE3988E1_4ED6_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_TASDESABLE_H__CE3988E1_4ED6_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Economiseur.h>

class CTasDeSable : public CEconomiseur  
{
	public :
		CTasDeSable(  ) ;
		virtual	~CTasDeSable() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Configuration( CPropertySheet * )  ;

		// Animation
		virtual	void Animation( CDC&	Dc )  ;
		virtual void InitDC( CDC & ) ;
		virtual void FinDC( CDC & ) ;

		virtual	void Preferences() ;

	private:
		static BOOL CTasDeSable::ToutEnBas() ;
		static BOOL CTasDeSable::ToutEnHaut() ;
		static void	__inline Affiche( HDC hDC, int x, int y ) ;
		static void	DescentAGauche( HDC hDC, int Indice, double Val ) ;
		static void	DescentADroite( HDC hDC, int Indice, double Val ) ;
		static void	Descend( HDC hDC, int Indice, double	Val ) ;
		static void	__inline MonteADroite( HDC hDC, int Indice, double Val ) ;
		static void	__inline MonteAGauche( HDC hDC, int Indice, double  Val ) ;
		static	void	Monte( HDC hDC, int Indice, double Val ) ;


		friend class	CConfiguration ;
};

#endif // !defined(AFX_TASDESABLE_H__CE3988E1_4ED6_11D1_AEF5_444553540000__INCLUDED_)
