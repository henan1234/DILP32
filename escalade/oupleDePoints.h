// oupleDePoints.h: interface for the CoupleDePoints class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUPLEDEPOINTS_H__CA5E3F0F_347C_4BD2_B58A_A0F2C71A2947__INCLUDED_)
#define AFX_OUPLEDEPOINTS_H__CA5E3F0F_347C_4BD2_B58A_A0F2C71A2947__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "point.h"

class CoupleDePoints  
{
public:
	CoupleDePoints() {};
	CoupleDePoints( Point p1, Point p2 );

	Point LePlusADroite() const ;
	Point LePlusAGauche() const ;
	Point LePlusBas() const ;
	Point LePlusHaut() const ;

	void	SetPoints( Point P1, Point P2 ) { _p1 = P1; _p2 = P2 ; }
	void	GetPoints( Point * P1, Point * P2 ) const { (*P1)=_p1; (*P2)=_p2 ; }

private:
	Point _p1 ;
	Point _p2 ;

};

#endif // !defined(AFX_OUPLEDEPOINTS_H__CA5E3F0F_347C_4BD2_B58A_A0F2C71A2947__INCLUDED_)
