// Droite.cpp: implementation of the Droite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "escalade.h"
#include "Droite.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Droite::Droite( Point P1, Point P2 )
{
	// Pour eviter les pb de division par 0
	if ( P1.x == P2.x )
		{
		_Type	=	VERTICAL ;
		// Dans ce cas, _b est la coordonnee x de la droite, _a est indefinie
		_b	=	P1.x ;
		}
	else
		if ( P1.y == P2.y )
		{
		_Type	=	HORIZONTAL ;
		// Dans ce cas, _b est la coordonnee y de la droite, _a est indefinie
		_b		=	P1.y ;
		}
	else
		{
		_Type = NORMAL ;
		_a	=	(double)(P1.y-P2.y) / (double)(P1.x-P2.x) ;
		_b	=	(double)P1.y - (_a * P1.x) ;
		}
}

Droite::Droite( double a, double b )
{
	if ( a == 0 )
		{
		_Type = HORIZONTAL ;
		_b	=	b ;
		}
	else
		{
		_Type = NORMAL ;
		_a	=	a ;
		_b	=	b ;
		}
}
	
double Droite::CalculeY( double x )
{
	switch( _Type )
	{
	case	NORMAL:
		return _a * x + _b ;
	case	HORIZONTAL:
		return _b ;
	default:
		// N'importe quelle valeurs
		return _b ;
	}
}

double Droite::CalculeX( double y )
{
	switch( _Type )
	{
	case	NORMAL:
		return (y - _b ) / _a ;

	case	HORIZONTAL:
		// N'importe quelle valeurs
		return _b ;
	default:
		return _b ;
	}
}

CoupleDePoints Droite::PointADistance( Point Pt, double Distance )
{
	switch( _Type )
		{

		case VERTICAL:
			CoupleDePoints( Point( Pt.x, (Pt.y + Distance)),
							Point( Pt.x, (Pt.y - Distance))
							) ;

		case HORIZONTAL:
			CoupleDePoints( Point( (Pt.x + Distance), Pt.y ),
							Point( (Pt.x - Distance), Pt.y ));

		case NORMAL:
		default:
			{
			double x =	 sqrt( (Distance*Distance)/(_a*_a+1)) ;
			double X1	= Pt.x + x ;
			double X2	= Pt.x - x ;

			double Y1	=	CalculeY( X1 ) ;
			double Y2	=	CalculeY( X2 ) ;

			return CoupleDePoints( Point(X1,Y1), Point( X2,Y2)) ;
			}
		}
}

//
//	Calcule la droite perpendiculaire
Droite Droite::Perpendiculaire( Point Pt )
{
	switch( _Type )
		{
		case VERTICAL :
			// Construire une droite horizontal passant par Pt
			return Droite( Pt, Point( Pt.x + 10, Pt.y )) ;

		case HORIZONTAL:
			// Construire une droite verticale passant par Pt
			return Droite( Pt, Point( Pt.x, Pt.y + 10 )) ;

		default:
			double a2 = -(1/_a) ;
			double b2 = Pt.y - (a2*Pt.x) ;
			return Droite( a2, b2 ) ;
		}
}
