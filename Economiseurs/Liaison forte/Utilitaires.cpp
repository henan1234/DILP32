#include "..\economiseur generique\stdafx.h"
#include <math.h>
#include <signal.h>
#include "resource.h"
#include "..\economiseur generique\RectAffichage.h"
#include "LiaisonForte.h"
#include "utilitaires.h"

extern COLORREF	CouleurFond ;
extern COLORREF	AtomeSature ;
extern COLORREF	AtomeLibre ;
extern COLORREF	CouleurLien ;
extern int		Diviseur ;
extern int		NbLiens ;
extern int		NbMaxLiensParAtome ;
extern int		NbAtomes ;
extern CRectAffichage	NouveauxRectangles ;

extern double	X1, X2, X3, X4, X5, X6, X7, X8 ;
extern double	Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8 ;
extern T_ATOME	Atomes[ NB_MAX_ATOMES ] ;
extern T_ATOME	AtomesTries[ NB_MAX_ATOMES ] ;
extern T_LIEN	Liens[ NB_MAX_LIENS ] ;

inline	void	TroisD2DeuxD( double x, double y, double z, double & X, double & Y )
	{
	X	=	( (POINT_DE_FUITE-z)/POINT_DE_FUITE)* x + ( CLiaisons::Largeur/2 ) ;
	Y	=	( (POINT_DE_FUITE-z)/POINT_DE_FUITE)* y + ( CLiaisons::Hauteur/2 ) ;
	}

inline double RegleDe3( double Value, double MinSrc, double MaxSrc, double MinDest, double MaxDest )
	{
	return  (Value-MinSrc) /  (MaxSrc-MinSrc ) * (MaxDest-MinDest) + MinDest ; 
	}

inline void	EloigneCouleur( double z, BYTE & Rouge, BYTE & Vert, BYTE & Bleu )
	{
	Rouge	=	(BYTE)RegleDe3( z , DISTANCE_MAX*1.5, 0, GetRValue( CouleurFond ), Rouge	) ;
	Vert	=	(BYTE)RegleDe3( z , DISTANCE_MAX*1.5, 0, GetGValue( CouleurFond ), Vert		) ;
	Bleu	=	(BYTE)RegleDe3( z , DISTANCE_MAX*1.5, 0, GetGValue( CouleurFond ), Bleu		) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Calcule le diametre apparent d'un atome en fonction de sa distance
///////////////////////////////////////////////////////////////////////////////
inline int CalculDiametre(const double z, const double DiametreMax )
{
	return (int)( (POINT_DE_FUITE-z)/POINT_DE_FUITE* DiametreMax );
}

///////////////////////////////////////////////////////////////////////////////
// LongueurLien
//	Calcule la longueur d'un lien ( distance entre les deux atomes )
///////////////////////////////////////////////////////////////////////////////
inline double LongueurLien( const T_LIEN & Lien )
	{
	const	int Indice1	=	Lien.Atome1 ;
	const	int Indice2	=	Lien.Atome2 ;

	if ( Indice1 < 0 || Indice1 >= NbAtomes )
		return 0 ;

	if ( Indice2 < 0 || Indice2 >= NbAtomes )
		return 0 ;

	// ================================================== Calcul de la distance
	const double DistanceX		=   (Atomes[Indice1].x - Atomes[Indice2].x)  ;
	const double DistanceY		=   (Atomes[Indice1].y - Atomes[Indice2].y)  ;
	const double DistanceZ		=   (Atomes[Indice1].z - Atomes[Indice2].z)  ;

	const double DistanceCarre	=	(DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + ( DistanceZ * DistanceZ ) ;
	return sqrt( DistanceCarre ) ;	
}

///////////////////////////////////////////////////////////////////////////////
// Calcule la distance "moyenne" d'un lien ( distance du point central )
///////////////////////////////////////////////////////////////////////////////
inline double DistanceLien( const T_LIEN & Lien )
	{
	return ( Atomes[Lien.Atome1].z + Atomes[Lien.Atome2].z ) / 2.0 ;
	}

int	_cdecl CompareAtomes( const void * El1, const void * El2 )
{
	const T_ATOME *	p1	=	(const T_ATOME *)El1 ;
	const T_ATOME *	p2	=	(const T_ATOME *)El2 ;

	if ( p1->z < p2->z )
		return 1 ;
	else
		return -1 ;

}

int	_cdecl CompareLiens( const void * El1, const void * El2 )
{
	const T_LIEN *	p1	=	(const T_LIEN *)El1 ;
	const T_LIEN *	p2	=	(const T_LIEN *)El2 ;

	const double DistMoy1	=	DistanceLien( *p1 ) ;
	const double DistMoy2	=	DistanceLien( *p2 ) ;

	if ( DistMoy1 < DistMoy2 )
		return 1 ;
	else
		return -1 ;
}

///////////////////////////////////////////////////////////////////////////////
// Decide s'il faut plutot dessiner un atome qu'un lien en fonction des
// distances
///////////////////////////////////////////////////////////////////////////////
BOOL PlutotUnAtome( T_ATOME * AtomesTries, int IndiceLien, int IndiceAtome )
	{
	if ( IndiceLien >= NbLiens )
		return TRUE ;

	if ( IndiceAtome >= NbAtomes )
		return FALSE ;

	if ( AtomesTries[IndiceAtome].z < DistanceLien( Liens[IndiceLien] ))
		return FALSE ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// Dessine un atome
// Sa taille apparente depend de la distance
// Sa couleur depend du nombre de liaisons libres et de sa distance
///////////////////////////////////////////////////////////////////////////////
inline void DessineAtome(CDC & Dc, const T_ATOME & Atome )
{
	double X, Y ;

	TroisD2DeuxD( Atome.x, Atome.y, Atome.z, X, Y ) ;

	const int	Diametre	=	CalculDiametre( Atome.z, DIAMETRE_MAX_ATOME ) ;

	CRect	R ;			
	R.left	=	(int)(X - Diametre/2.0 ) ;
	R.top	=	(int)(Y - Diametre/2.0 ) ;

	R.right	=	R.left + Diametre ;
	R.bottom=	R.top + Diametre ;

	const int NbLiensLibres	=	Atome.NbMaxLiens - Atome.NbLiens ;

	// Choix de la couleur en fonction du nombre de liaisons libres
	BYTE	Rouge	=	(BYTE)RegleDe3( NbLiensLibres, 0, NbMaxLiensParAtome, GetRValue( AtomeSature ), GetRValue( AtomeLibre ) ) ;
	BYTE	Vert	=	(BYTE)RegleDe3( NbLiensLibres, 0, NbMaxLiensParAtome, GetGValue( AtomeSature ), GetGValue( AtomeLibre ) ) ;
	BYTE	Bleu	=	(BYTE)RegleDe3( NbLiensLibres, 0, NbMaxLiensParAtome, GetBValue( AtomeSature ), GetBValue( AtomeLibre ) ) ;
	
	// Choix de la saturation en fonction de la distance

//	EloigneCouleur( Atome.z, Rouge, Vert, Bleu ) ;
	//Rouge	=	(BYTE)RegleDe3( Atome.z, DISTANCE_MAX, 0, GetRValue( CouleurFond ), Rouge ) ;
	//Vert	=	(BYTE)RegleDe3( Atome.z, DISTANCE_MAX, 0, GetGValue( CouleurFond ), Vert ) ;
	//Bleu	=	(BYTE)RegleDe3( Atome.z, DISTANCE_MAX, 0, GetBValue( CouleurFond ), Bleu ) ;

	const int NbGradients	=	(int)Diametre/Diviseur + 1;

	for ( int i = 0; i < NbGradients; i++)
		{
		BYTE	Rg	=	(BYTE)RegleDe3( i, 0, NbGradients*2, Rouge, 255 ) ;
		BYTE	Gr	=	(BYTE)RegleDe3( i, 0, NbGradients*2, Vert, 255 ) ;
		BYTE	Bl	=	(BYTE)RegleDe3( i, 0, NbGradients*2, Bleu, 255 ) ;

		EloigneCouleur( Atome.z, Rg, Gr, Bl ) ;
		CBrush Brosse( Dc.GetNearestColor( RGB( Rg, Gr, Bl ))) ;
		//CBrush Brosse( Dc.GetNearestColor(RGB(
		//					(BYTE)RegleDe3( i, 0, NbGradients*2, Rouge, 255 ),
		//					(BYTE)RegleDe3( i, 0, NbGradients*2, Vert, 255 ),
		//					(BYTE)RegleDe3( i, 0, NbGradients*2, Bleu, 255 )
		//				  )
		//				  )
		//			  ) ;

		int	Decalage1	=	(int)RegleDe3( i, 0, NbGradients, 0, Diametre/4 ) ;
		int Decalage2	=	(int)RegleDe3( i, 0, NbGradients, 0, Diametre*0.525 ) ;

		CBrush * pOld = Dc.SelectObject( &Brosse ) ;
		Dc.Ellipse( R.left+ Decalage1,
					R.top + Decalage1,
					R.right - Decalage2,
					R.bottom- Decalage2 ) ;

		Dc.SelectObject(pOld) ;
		Brosse.DeleteObject() ;
		}

	NouveauxRectangles.LimiteRect( R ) ;
	NouveauxRectangles += R ;

}

inline	void	CalculeCoordonneesSortieLien( const T_ATOME & Atome1, const T_ATOME & Atome2, double & SortieX, double & SortieY, double & SortieZ )
	{
	const double Rayon	=	DIAMETRE_MAX_ATOME / 2.05 ; // On triche un peu !
	const double DeltaX	=	Atome2.x - Atome1.x ;
	const double DeltaY	=	Atome2.y - Atome1.y ;
	const double DeltaZ	=	Atome2.z - Atome1.z ;

	const double Distance	=	sqrt( (DeltaX*DeltaX)
									+ (DeltaY*DeltaY)
									+ (DeltaZ*DeltaZ)
									) ;

	SortieX		=	Atome1.x + ( DeltaX * Rayon / Distance ) ;
	SortieY		=	Atome1.y + ( DeltaY * Rayon / Distance ) ;
	SortieZ		=	Atome1.z + ( DeltaZ * Rayon / Distance ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// AjouteRectangleLien
//	Ajouter le rectangle correspondant au lien. Comme le lien n'occupe que la 
//	diagonale, on va essayer d'optimiser en ajouter deux petits rectangles
///////////////////////////////////////////////////////////////////////////////
void AjouteRectangleLien(CRect & R)
{
	// Deux petits rectangles valent peut etre mieux qu'un grand
	CRect R1( R.left, R.top, R.left+(R.right-R.left)/2, R.top+(R.bottom-R.top)/2 ) ;
	CRect R2( R.left+(R.right-R.left)/2, R.top+(R.bottom-R.top)/2, R.right, R.bottom )  ;
	
	R.NormalizeRect() ;
	R1.NormalizeRect() ;
	R2.NormalizeRect() ;
	R.InflateRect( 5, 5 ) ;
	R1.InflateRect( 5, 5 ) ;
	R2.InflateRect( 5, 5 ) ;
					
	if ( R.Width()*R.Height() <= (R1.Width()*R1.Height() + R2.Width()*R2.Height()))
		{
		NouveauxRectangles.LimiteRect( R ) ;
		NouveauxRectangles += R ;
		}
	else
		{
		NouveauxRectangles.LimiteRect( R1 ) ;
		NouveauxRectangles += R1 ;

		NouveauxRectangles.LimiteRect( R2 ) ;
		NouveauxRectangles += R2 ;
		}
}




double LongueurLienCarre( int iLien )
{
	const	int Indice1	=	Liens[iLien].Atome1 ;
	const	int Indice2	=	Liens[iLien].Atome2 ;

	if ( Indice1 < 0 || Indice1 >= NbAtomes )
		return 0 ;

	if ( Indice2 < 0 || Indice2 >= NbAtomes )
		return 0 ;

	// ================================================== Calcul de la distance
	const double DistanceX		=   (Atomes[Indice1].x - Atomes[Indice2].x)  ;
	const double DistanceY		=   (Atomes[Indice1].y - Atomes[Indice2].y)  ;
	const double DistanceZ		=   (Atomes[Indice1].z - Atomes[Indice2].z)  ;

	return	(DistanceX * DistanceX ) + ( DistanceY * DistanceY )  + ( DistanceZ * DistanceZ );
}



inline double LongueurLien( int iLien )
	{
	return LongueurLien( Liens[iLien ] ) ;
	}

void	DessineLien( CDC & Dc, const T_LIEN & Lien )
{
	double	SortieX1 ;
	double	SortieY1 ;
	double	SortieZ1 ;
	double	SortieX2 ;
	double	SortieY2 ;
	double	SortieZ2 ;

	CalculeCoordonneesSortieLien( Atomes[Lien.Atome1], Atomes[Lien.Atome2], SortieX1, SortieY1, SortieZ1 ) ;
	CalculeCoordonneesSortieLien( Atomes[Lien.Atome2], Atomes[Lien.Atome1], SortieX2, SortieY2, SortieZ2 ) ;

	double X1, Y1 ;
	TroisD2DeuxD( SortieX1, SortieY1, SortieZ1, X1, Y1 ) ;
	double X2, Y2 ;
	TroisD2DeuxD( SortieX2, SortieY2, SortieZ2, X2, Y2 ) ;

	const double MilieuZ	=	(SortieZ1 + SortieZ2) / 2.0 ;
	CRect R( (int)X1, (int)Y1, (int)X2, (int)Y2 ) ;


	// Calcul de la couleur du lien
	const int	Largeur	=	CalculDiametre( MilieuZ, DIAMETRE_MAX_LIEN ) ; //(int)RegleDe3( MilieuZ, 0, DISTANCE_MAX, DIAMETRE_MIN_LIEN, DIAMETRE_MAX_LIEN ) ;

	
	BYTE	Rouge	=	GetRValue( CouleurLien ) ; //(BYTE)RegleDe3( MilieuZ, 0, DISTANCE_MAX, GetRValue( CouleurLien ), GetRValue( CouleurFond )) ;
	BYTE	Vert	=	GetGValue( CouleurLien ) ; //(BYTE)RegleDe3( MilieuZ, 0, DISTANCE_MAX, GetGValue( CouleurLien ), GetGValue( CouleurFond )) ;
	BYTE	Bleu	=	GetBValue( CouleurLien ) ; //(BYTE)RegleDe3( MilieuZ, 0, DISTANCE_MAX, GetBValue( CouleurLien ), GetBValue( CouleurFond )) ;
	EloigneCouleur( MilieuZ, Rouge, Vert, Bleu ) ;

	CPen	Pinceau( PS_SOLID|PS_COSMETIC|PS_ENDCAP_ROUND, Largeur,
					 GetNearestColor( Dc, RGB( Rouge, Vert, Bleu ))) ;
	CPen * pOld = Dc.SelectObject( &Pinceau ) ;


	Dc.MoveTo( R.TopLeft()) ;
	Dc.LineTo( R.BottomRight()) ;

	Dc.SelectObject( pOld ) ;
	Pinceau.DeleteObject() ;

	AjouteRectangleLien( R ) ;

}
