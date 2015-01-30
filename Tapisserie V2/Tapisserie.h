//
//	Tapisserie
//
#ifndef _TAPISSERIE_H_
#define _TAPISSERIE_H_

class	CTapisserie : public CObject
{
	public :
		CTapisserie( const char *, BOOL Mosaique=FALSE, int NbMinutes=1, BOOL ChangeCouleur=FALSE, COLORREF Couleur = GetSysColor( COLOR_DESKTOP ) ) ;
		~CTapisserie() ;

		const CString	Nom() const { return _Nom ; } ;
		BOOL			Mosaique() const { return _Mosaique ; } ;
		void			Mosaique( BOOL ) ;

		int				NbMinutes( void ) const { return _NbMinutes; } ;
		void			NbMinutes( int Nb) { _NbMinutes = Nb ; } ;

		void			Active() ;

		void			ChangeCouleur( BOOL b ) { _ChangeCouleur = b ; } ;
		BOOL			ChangeCouleur() const { return _ChangeCouleur ; }

		void			Couleur( COLORREF c ) { _Couleur	=	c ; }
		COLORREF		Couleur() const { return _Couleur ; } 
		
		HBITMAP			GetBitmap() ;

		void			SetIndiceImage( int i )  { _IndiceImage = i ; }
		int				GetIndiceImage(void)	 { return _IndiceImage ; }
	private :
		CString			_Nom ;
		BOOL			_Mosaique ;
		int				_NbMinutes ;
		BOOL			_ChangeCouleur ;
		COLORREF		_Couleur ;
		HBITMAP			_hBitmap ;
		int				_IndiceImage ;
} ;

#endif
