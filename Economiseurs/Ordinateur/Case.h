///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#ifndef _CASE_H_
#define _CASE_H_


class	CCase
	{
	public	:
		CCase() ;

		void	Affiche( CDC &, int x, int y ) ;
		char		_Car ;
		BOOL		_Clignote ;
		COLORREF	_CouleurFond ;
		COLORREF	_CouleurCar ;
public:
	void Clignote( CDC &, int x, int y, BOOL Allume );
	};

#endif
