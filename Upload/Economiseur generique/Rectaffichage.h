///////////////////////////////////////////////////////////////////////////////
// Interface de la classe CRectAffichage
// Un objet de cette classe gere un ensemble de rectangles a afficher ou a
// effacer
///////////////////////////////////////////////////////////////////////////////
#ifndef __RECTAFFICHAGE_H_
#define __RECTAFFICHAGE_H_

class	CRectAffichage
	{
	public :
		///////////////////////////////////////////////////////////////////////
		// Constructeurs/Destructeurs
		///////////////////////////////////////////////////////////////////////
		CRectAffichage() ;
		CRectAffichage( const CRect & Espace ) ;	// Tout affichage sera limite a la taille fournie
		CRectAffichage( const CRectAffichage & ) ;
		virtual	~CRectAffichage() ;

		///////////////////////////////////////////////////////////////////////
		// Limitation de l'Espace
		///////////////////////////////////////////////////////////////////////
		void	Espace( const CRect & ) ;
		const	CRect & Espace(void ) const { return _Espace ; } ;

		///////////////////////////////////////////////////////////////////////
		// Ajout d'un rectangle a la liste
		///////////////////////////////////////////////////////////////////////
		void	Ajoute( const CRect & R ) ;
		inline void	Ajoute( int	x, int y, int l, int h ) 	{ Ajoute( CRect( x, y, x+l, y+h )) ;};

		///////////////////////////////////////////////////////////////////////
		// Affichage des rectangles
		///////////////////////////////////////////////////////////////////////
		void BitBlt( HDC hDCDest, HDC hDCSrc, DWORD RasterOp = SRCCOPY ) const ;
		inline void BitBlt( CDC&	DcDest, CDC& DcSrc, DWORD	RasterOp = SRCCOPY  ) const 
			{ BitBlt( DcDest.m_hDC, DcSrc.m_hDC, RasterOp ) ; } ;	

		void PatBlt( HDC hDcDest, DWORD	RasterOp = BLACKNESS ) const ;
		inline void PatBlt( CDC&	DcDest, DWORD	RasterOp = BLACKNESS ) const 
			{ PatBlt( DcDest.m_hDC, RasterOp ) ; } ;

		void FillRect( HDC hDcDest, COLORREF = RGB( 0,0,0 ) ) const ;
		inline void FillRect( CDC&	DcDest, COLORREF Couleur = RGB( 0,0,0 ) ) const
			{ FillRect( DcDest.m_hDC, Couleur ) ; } ;


		///////////////////////////////////////////////////////////////////////
		// Vidage des rectangles
		///////////////////////////////////////////////////////////////////////
		void	Vide() ;

		///////////////////////////////////////////////////////////////////////
		// Verifie qu'un rectangle est contenu dans l'espace de dessin
		///////////////////////////////////////////////////////////////////////
		void			LimiteRect( CRect &, int * DecX=0, int * DecY=0 ) const ;


		int		NbRectangles( void ) const { return _NbRects ; } ;
		const	CRect & Rectangle( int i ) const { ASSERT( i >= 0 && i < _NbRects ) ; return _pRects[i] ; } ;

		const CRect *	Rectangles() const { return _pRects ; } ;

	private :
		CRect		*			_pRects ;
		int						_NbRects ;
		int						_NbAlloues ;
		CRect					_Espace ;

		static BOOL		UnionValable( const CRect &, const CRect & ) ;
public:
	void operator +=( const CRectAffichage & );
	void operator =( const CRectAffichage & ) ;

	inline void operator +=( const CRect & R ) { Ajoute( R ) ; } ;

private:
	static int _NbObjets;
	static void ResoudFonctions( void );
	static HANDLE _hWinG;
	} ;

#endif
