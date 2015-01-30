// Droite.h: interface for the Droite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DROITE_H__BE3930CB_1B78_486A_9DDB_C08CD88A3D39__INCLUDED_)
#define AFX_DROITE_H__BE3930CB_1B78_486A_9DDB_C08CD88A3D39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Droite y = ax+b ;
#define NORMAL	0
#define VERTICAL 1
#define HORIZONTAL 2
#include "oupledepoints.h"

class Droite  
{
public:
	Droite( Point P1, Point P2 );
	Droite( double a, double b ) ;

	double CalculeY( double x ) ;
	double CalculeX( double y ) ;
	CoupleDePoints PointADistance( Point Pt, double Distance ) ;
	Droite Perpendiculaire( Point Pt ) ;

private:
	double	_a ;
	double	_b ;
	int		_Type ;	// 0: normal; 1: vertical; 2: horizontale
};

#endif // !defined(AFX_DROITE_H__BE3930CB_1B78_486A_9DDB_C08CD88A3D39__INCLUDED_)
