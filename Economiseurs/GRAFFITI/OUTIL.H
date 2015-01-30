///////////////////////////////////////////////////////////////////////////////
// Classe generique Outil
///////////////////////////////////////////////////////////////////////////////
#ifndef _OUTIL_H_
#define _OUTIL_H_

class	COutil	:	public	CObject
	{
	public :
		COutil() ;
		virtual	~COutil() {} ;
		virtual	void	Trace( CDC &, int, int, int, int ) ;

	protected :
		static	COLORREF		CouleurHasard( void ) ;
		static int Alea( int, int );
		virtual void	PointDeLigneDroite( CDC &, int, int ) = 0;
		void	InitPoids( int i ) { _UnSur = i; _Poids	=	0 ; } ;

	private :
		BOOL	Poids( void ) ;
		CDC*		_pDCLigneDroite ;
		static void	CALLBACK LineDDAProc( int, int, LPARAM ) ;
		int	_Poids ;
		int _UnSur ;
protected:
	static COLORREF InterpoleCouleur( int, int, int, COLORREF, COLORREF );
	} ;


class	CStylo	:	public	COutil
	{
	public :
		CStylo() ;
		~CStylo() ;
		virtual	void	Trace( CDC &, int, int, int, int ) ;

	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) {} ;
	protected :
		CPen	_Pen ;
	} ;

class	CPlume : public COutil
	{
	public	:
		CPlume() ;
		~CPlume() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		CPen	_Pen ;
		int		_dx ;
		int		_dy ;
	} ;


class	CCraie : public COutil
	{
	public :
		CCraie() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	_Couleur ;
		int			_Largeur ;
		int			_Hauteur ;
	} ;

class	CCraieGrasse : public COutil
	{
	public :
		CCraieGrasse() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	_Couleur ;
		int			_Largeur ;
	} ;

class	CAerographe : public	COutil
	{
	public :
		CAerographe() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	_Couleur ;
		int			_Largeur ;
	} ;


class	CEstompe : public	COutil
	{
	public :
		CEstompe() ;
		~CEstompe() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	CouleurMoyenne( CDC &, int, int ) ;
		int			_Largeur ;
		CDC			_MemDC ;
		CBitmap*	_pOld ;
	} ;

class CDoigt : public	COutil
	{
	public :
		CDoigt() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		int	_Largeur ;
		int	_Poids ;
	} ;

class	CSurligneur : public COutil
	{
	public :
		CSurligneur() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	_Couleur ;
		int			_Largeur ;
		int			_Force ;
		CRect		_DernierRectangle ;
	} ;

class CPinceau : public COutil
	{
	public :
		CPinceau() ;
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;
	private :
		COLORREF	_Couleur ;
		int			_Largeur ;
		int			_Hauteur ;
	} ;

class CGrosPinceau : public	COutil
	{
	public :
		CGrosPinceau() ;
		
	protected :
		virtual void	PointDeLigneDroite( CDC &, int, int ) ;

	private :

		typedef struct
			{
			int		x ;
			int		y ;
			int		Couleur ;
			int		Hauteur ;
			HANDLE	hParamsRecopies ;
			} T_PARAMS ;

		static	DWORD _stdcall	Thread( LPVOID ) ;
		COLORREF	_Couleur ;
		int			_Hauteur ;
	} ;

class	CHachures : public COutil
	{
	public :
		CHachures() ;
		~CHachures() ;

		void	Trace( CDC &, int, int, int, int ) ;
		virtual void	PointDeLigneDroite( CDC &, int, int ) {} ;

	protected :
		virtual		void	TraceDansRegion( HRGN ) ;

		COLORREF	_Couleur ;
		POINT	*	_pPts ;
		int			_NbPoints ;
	} ;


class	CCrayonGris : public CHachures
	{
	public :
		CCrayonGris() ;
	} ;


#endif
