///////////////////////////////////////////////////////////////////////////////
// CEcoNeige
///////////////////////////////////////////////////////////////////////////////
#include "..\Economiseur Generique\stdafx.h"
#include <stdlib.h>

#include "..\Economiseur Generique\RectAffichage.h"
#include "flocon.h"

int	CFlocon::_VitesseVent	=	0 ;

CFlocon::CFlocon( int x, int y, COLORREF Couleur, int Taille )
{
	_Rect.SetRect( x, y, x+Taille, y+Taille ) ;
	_Taille	=	Taille ;
	_Couleur	=	Couleur ;
}





