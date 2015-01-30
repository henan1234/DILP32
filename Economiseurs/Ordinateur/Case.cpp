///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "case.h"
CCase::CCase()
	{
	_Car		=	' ' ;
	_Clignote	=	FALSE ;
	_CouleurFond	=	0 ;
	_CouleurCar		=	RGB( 0, 255, 0 ) ;
	}

void	CCase::Affiche( CDC & Dc, int x, int y )
	{
	Dc.SetTextColor( _CouleurCar ) ;
	Dc.SetBkColor( _CouleurFond ) ;
	Dc.TextOut( x, y, &_Car, 1 ) ;
	}


void CCase::Clignote( CDC & Dc, int x, int y, BOOL ClignoteAllume )
{
	if ( ! _Clignote )
		return ;

	if ( ClignoteAllume )
		{
		Dc.SetTextColor( _CouleurCar ) ;
		Dc.SetBkColor( _CouleurFond ) ;
		}
	else
		{
		Dc.SetTextColor( _CouleurFond ) ;
		Dc.SetBkColor( _CouleurCar ) ;
		}

	Dc.TextOut( x, y, &_Car, 1 ) ;
	
	
}

