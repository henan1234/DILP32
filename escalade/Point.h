// Point.h: interface for the Point class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_H__6DA2009E_BA06_4FD6_AF2E_DCC393A7E625__INCLUDED_)
#define AFX_POINT_H__6DA2009E_BA06_4FD6_AF2E_DCC393A7E625__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Point  
{
public:
	Point(){};
	Point( double X, double Y  ) { x = X; y = Y; }

	operator CPoint() const { return CPoint( (int)x, (int)y ); }
	double x ;
	double y ;
};

#endif // !defined(AFX_POINT_H__6DA2009E_BA06_4FD6_AF2E_DCC393A7E625__INCLUDED_)
