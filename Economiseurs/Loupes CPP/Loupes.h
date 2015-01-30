// Loupes.h: interface for the CLoupes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOUPES_H__D5283EC1_43D3_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_LOUPES_H__D5283EC1_43D3_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <economiseur.h>
#define NB_MAX_SPRITES	30

typedef struct
	{
	int	x ;
	int	y ;
	int	Taille ;
	int	dx ;
	int	dy ;
	int	NbCoins ;
	int	Rotation ;
	RECT	Rect ;
	int	VitesseRotation ;
	}
	T_SPRITE ;

class CLoupes : public CEconomiseur  
{
	public :
		CLoupes(  ) ;
		virtual	~CLoupes() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Configuration( CPropertySheet * )  ;

		// Animation
		void		UpdateFenetre( CDC &, const CRect & ) ;
		virtual	void Animation( CDC&	Dc )  ;
		virtual void InitDC( CDC & )  ;
		virtual void FinDC( CDC & ) ;

		virtual	void Preferences() ;

	private :
		static	CString		_Texte;
		static	COLORREF	_CouleurTexte ;
		HRGN	RegionOffset( T_SPRITE * ) ;

		void	__inline AfficherSprite( HDC hDC, T_SPRITE * pSprite ) ;
		void	NouveauSprite( T_SPRITE * pSprite ) ;
		void AjouteRect( RECT*	TabRects, int NbMaxRects, int * pNbRects, const RECT * pR ) ;

		static	int	NbMaxSprites ;

	friend class	CParametresLoupes ;
	};

#endif // !defined(AFX_LOUPES_H__D5283EC1_43D3_11D1_AEF5_444553540000__INCLUDED_)
