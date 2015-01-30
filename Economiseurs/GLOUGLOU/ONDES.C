///////////////////////////////////////////////////////////////////////////////
//	Ondes
///////////////////////////////////////////////////////////////////////////////
#include "glouglou.h"

typedef	struct
	{
	int			y ;
	int			x ;
	int			Largeur ;
	int			Hauteur ;
	BOOL		Grossi ;
	}
	T_ONDE ;

int	NbMaxOndes =	NB_MAX_ONDES ;
int	NbOndes	=	0;

T_ONDE	Ondes[NB_MAX_ONDES] ;

///////////////////////////////////////////////////////////////////////////////
// AjouteUneOnde
///////////////////////////////////////////////////////////////////////////////
void	AjouteUneOnde()
{
	Ondes[NbOndes].y	=	Alea( Niveau, HauteurEcran ) ;
	Ondes[NbOndes].x	=	Alea( 0, LargeurEcran );
	Ondes[NbOndes].Largeur=	Alea( 10, 100 );
	Ondes[NbOndes].Hauteur=	Alea( 2, 4 ) ;

	Ondes[NbOndes].Grossi	=	TRUE ;
	NbOndes ++ ;
}			   					 

///////////////////////////////////////////////////////////////////////////////
// AfficheOnde
///////////////////////////////////////////////////////////////////////////////
void	AfficherOnde( HDC	hDC, T_ONDE* pOnde )
{
	if ( pOnde->Grossi )
		BitBlt( hDC, pOnde->x, pOnde->y, pOnde->Largeur, pOnde->Hauteur,
				hDCEcran, pOnde->x + 1, pOnde->y + 1,
				SRCCOPY ) ;
	else
		BitBlt( hDC, pOnde->x, pOnde->y, pOnde->Largeur, pOnde->Hauteur,
				hDCEcran, pOnde->x - 1, pOnde->y - 1,
				SRCCOPY ) ;

	pOnde->Grossi	=	! pOnde->Grossi ;
}

///////////////////////////////////////////////////////////////////////////////
// Gestion des ondes
///////////////////////////////////////////////////////////////////////////////
void	GestionOndes( HDC	hDC )
{
	int	i	;
	HBRUSH	hBrosse, hOld ;

	if ( NbOndes	< NbMaxOndes )
		AjouteUneOnde() ;

	hBrosse	=	CreateSolidBrush( CouleurLiquide ) ;
	hOld	=	SelectObject( hDC, hBrosse ) ;
	for ( i = NbOndes-1; i >0 ; i--)
		if ( Ondes[i].y	< (Niveau+50))
			// Supprimer cette onde
			{
			memmove( &Ondes[i], &Ondes[i+1], sizeof( T_ONDE ) * ( NbOndes-i )) ;
			NbOndes -- ;
			}
		else
			AfficherOnde( hDC, &Ondes[i] ) ;

	SelectObject( hDC, hOld ) ;
	DeleteObject( hBrosse ) ;
}
