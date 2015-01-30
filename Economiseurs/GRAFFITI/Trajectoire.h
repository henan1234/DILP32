///////////////////////////////////////////////////////////////////////////////
// CTrajectoire
//	Ensemble de points
///////////////////////////////////////////////////////////////////////////////
#ifndef _TRAJECTOIRE_H_
#define _TRAJECTOIRE_H_
class	COutil ;

class	CTrajectoire : public	CObject
	{
	public :
	virtual	void	PromeneOutil( CDC&, COutil * ) = 0 ;
	virtual BOOL	Fini( void ) const = 0 ;
	} ;

class	CTrajectoireCourbe	:	public	CTrajectoire
	{
	public :
		CTrajectoireCourbe( int Largeur, int Hauteur ) ;

		virtual void	PromeneOutil( CDC &, COutil * ) ;
		virtual BOOL	Fini( void ) const ;

	private :
		int		_X ;
		int		_Y ;
		double	_Angle ;
		double	_DeltaAngle ;
		int		_DistanceMax ;
		int		_DistanceParcourue ;
	} ;


class	CTrajectoireRectiligne : public CTrajectoire
	{
	public :
		CTrajectoireRectiligne( int Largeur, int Hauteur ) ;

		virtual void	PromeneOutil( CDC &, COutil * ) ;
		virtual BOOL	Fini( void ) const ;

	private :
		CUIntArray	_X ;
		CUIntArray	_Y ;
		int			_IndiceCourant ;
	} ;
#endif