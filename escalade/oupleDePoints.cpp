// oupleDePoints.cpp: implementation of the CoupleDePoints class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "escalade.h"
#include "oupleDePoints.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CoupleDePoints::CoupleDePoints( Point p1, Point p2 )
	{
	_p1	=	p1 ;
	_p2	=	p2 ;
	}


Point CoupleDePoints::LePlusADroite() const
	{
	if ( _p1.x < _p2.x )
		return _p2 ;
	else
		return _p1 ;
	}

Point CoupleDePoints::LePlusAGauche() const
	{
	if ( _p1.x < _p2.x )
		return _p1 ;
	else
		return _p2 ;
	}

Point CoupleDePoints::LePlusBas() const
	{
	if ( _p1.y < _p2.y )
		return _p2 ;
	else
		return _p1 ;
	}

Point CoupleDePoints::LePlusHaut() const
	{
	if ( _p1.y < _p2.y )
		return _p1 ;
	else
		return _p2 ;
	}

