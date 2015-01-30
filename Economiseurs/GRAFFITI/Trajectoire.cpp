///////////////////////////////////////////////////////////////////////////////
// CTrajectoireCourbe
//	Ensemble de points
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "math.h"
#include "trajectoire.h"
#include "outil.h"

#define PI	3.14159

CTrajectoireCourbe::CTrajectoireCourbe( int Largeur, int Hauteur )
	{
	srand( GetCurrentTime()) ;

	_DistanceMax		=	100 + rand() % 500 ;
	_DistanceParcourue	=	0 ;
	_Angle				=	( rand() % (int)( PI * 40.0 ) ) / 20.0 ;
	_DeltaAngle			=	( rand() % (int)( PI * 60.0 ) ) / 60.0 - (PI / 2.0);
	_X					=	rand() % Largeur ;
	_Y					=	rand() % Hauteur ;
	}

void	CTrajectoireCourbe::PromeneOutil( CDC & Dc, COutil * pOutil)
	{
	const		int		Distance	= rand() % ( _DistanceMax / 20 ) + 2 ;
	const		int		x	=	_X	+	(int)( Distance * sin( _Angle )) ;
	const		int		y	=	_Y	+	(int)( Distance * cos( _Angle )) ;

	pOutil->Trace( Dc, _X, _Y, x, y ) ;
	_X	=	x ;
	_Y	=	y ;
	_Angle	+= _DeltaAngle ;

	_DeltaAngle += (double)( 5 - rand() % 11 ) / 20.0 ;

	_DistanceParcourue	+=	Distance ;
	}

BOOL	CTrajectoireCourbe::Fini( void ) const
	{
	return _DistanceParcourue >= _DistanceMax ;
	}


CTrajectoireRectiligne::CTrajectoireRectiligne( int Largeur, int Hauteur )
	{
	// Definition de l'equation de la trajectoire generale sous la
	// forme y	=	ax + b
	const double	a	=	(double)( 100 - rand() % 201 ) / 100.0 ;
	const double	b	=	rand() % Hauteur ;

	// Nombre de points
	const int	NbPoints	=	rand() % 20 + 8 ;

	_X.SetSize( NbPoints ) ;
	_Y.SetSize( NbPoints ) ;

	// Depart de la trajectoire
	double	x	=	50 + rand() % Largeur - 100 ;

	// Trouver des points de part et d'autre de la trajectoire
	for ( int i = 0; i < NbPoints; i++)
		{
		const double	Ecart=	rand() % 50 ;
		const double	y	=	a*x + b + Ecart ;

		_X[i]	=	(int)x ;
		_Y[i]	=	(int)y ;

		x += 5 + rand()%((int)(Ecart)/4+1) ;
		}

	_IndiceCourant	= 0 ;
	}

void	CTrajectoireRectiligne::PromeneOutil( CDC & Dc, COutil * pOutil)
	{
	pOutil->Trace( Dc, _X[_IndiceCourant], _Y[_IndiceCourant], 
					   _X[_IndiceCourant+1], _Y[_IndiceCourant+1]) ;
	_IndiceCourant ++ ;
	}

BOOL	CTrajectoireRectiligne::Fini( void ) const
	{
	return _IndiceCourant >= _X.GetUpperBound() ;
	}


