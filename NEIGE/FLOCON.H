///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#ifndef _FLOCON_H_
#define _FLOCON_H_

class	CRectAffichage ;
class	CDIBSurface ;

class CFlocon
	{
	public	:
		CFlocon( int x, int y, COLORREF Couleur, int Taille ) ;

		inline	void Bouge()
			{
			const	int dx	=	rand()%11 - 6 + _VitesseVent ;
			const	int	dy	=	_Taille - rand()%2 ;

			_Rect.OffsetRect( dx, dy ) ;
			}

		static inline	void ChangeVent( int VitesseVent ) { _VitesseVent	=	VitesseVent ; } ;


		inline	void Affiche( HDC hDC )
				{
				PatBlt( hDC, _Rect.left, _Rect.top, _Rect.Width(), _Rect.Height(), WHITENESS ) ;
				}

		const	CRect	&	Rectangle( void ) const { return _Rect ; } ;

		int		VitesseVent( void ) const { return _VitesseVent ; } ;
	private :
		CRect		_Rect ;
		COLORREF	_Couleur ;
		int			_Taille ;

		static	int	_VitesseVent ;
	} ;

#endif 