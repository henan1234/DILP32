// La fonction SortieRect calcule les coordonnees d'un point de sortie
// d'une droite passant par le centre d'un rectangle

///////////////////////////////////////////////////////////////////////////////
// DistanceCarre
// Calcule la distance qui separe deux points
///////////////////////////////////////////////////////////////////////////////
static double	DistanceCarre( const CPoint &Pt1, const CPoint& Pt2 )
{
	const double	Dx	=	Pt1.x - Pt2.x ;
	const double	Dy	=	Pt1.y - Pt2.y ;
	
	return Dx*Dx + Dy*Dy ;
}

///////////////////////////////////////////////////////////////////////////////
// PtSurBordRect
// Determine si un point est sur un des cotes d'un rectangle
///////////////////////////////////////////////////////////////////////////////
static BOOL PtSurBordRect( const CRect & Rectangle, const CPoint & Pt )
{
	CRect	R( Rectangle) ;
	R.NormalizeRect() ;
	
	// Sur le bord gauche ou droit ?
	if ( (Pt.x == R.left ) || ( Pt.x == R.right ))
		return (Pt.y <= R.bottom) && (Pt.y >= R.top) ;
		
	// Sur le bord haut ou bas
	if ( (Pt.y == R.top ) || (Pt.y == R.bottom))
		return (Pt.x <= R.right) && ( Pt.x >= R.left ) ;
		
	return FALSE ;		
}

///////////////////////////////////////////////////////////////////////////////
// IntersectionHorizontale
//	Calcule le point d'intersection d'une droite dont on donne l'equation sous
//	la forme y = ax + b avec une droite horizontale y = k
///////////////////////////////////////////////////////////////////////////////
static	CPoint	IntersectionHorizontale( double a, double b, int y )
{
	ASSERT( a != 0.0 ) ;
	const int	x	=	(int)(( y - b ) / a );
	return CPoint( x, y ) ;
}


///////////////////////////////////////////////////////////////////////////////
// IntersectionVerticale
//	Calcule le point d'intersection d'une droite dont on donne l'equation sous
//	la forme y = ax + b avec une droite verticale x = k
///////////////////////////////////////////////////////////////////////////////
static	CPoint	IntersectionVerticale( double a, double b, int x )
{
	const int	y	=	(int)(a*x + b) ;
	return CPoint( x, y ) ;
}

///////////////////////////////////////////////////////////////////////////////
// SortieRect
//	Calcule le point de sortie d'une droite qui part du centre d'un rectange
//	et qui va vers un point donne
///////////////////////////////////////////////////////////////////////////////
CPoint	SortieRect( const CRect	& Rectangle, const CPoint	Point )
{
	CRect	R( Rectangle ) ;
	R.NormalizeRect() ;
	CPoint	Centre( R.left + R.Width()/2, R.top + R.Height()/2 ) ;
	
	// Quelques cas particuliers
	if ( Centre.x	==	Point.x )
		{
		if ( Centre.y < Point.y )
			// Sortie par le milieu du cote bas
			return CPoint( Centre.x, R.bottom ) ;
		else
			// Sortie par le milieu du cote haut
			return CPoint( Centre.x, R.top ) ;
		}
	
	if ( Centre.y == Point.y )
		{
		if ( Centre.x < Point.x )
			// Sortie par le milieu du cote droit
			return CPoint( R.right, Centre.y ) ;
		else
			// Sortie par le milieu du cote gauche
			return CPoint( R.left, Centre.y ) ;
		}
		
	// Calcul de l'equation de la droite qui joint le centre du rectangle
	// au point sous la forme y	= ax + b
	// Les cas particuliers plus haut permettent de simplifier les calculs
	ASSERT( Centre.x != Point.x ) ;	
	
	const double	a	=	(double)(Point.y-Centre.y) / (double)(Point.x-Centre.x) ;
	const double	b	=	Centre.y - a * Centre.x ;
	
	// Calculer les points d'intersection avec les droites confondues aux
	// cotes du rectangle
	
	CPoint	PointsRetenus[2]	;	
	int		NbPtsRetenus	=	0 ;
	
	// Intersection avec le bord gauche (droite verticale )
	CPoint Pt	=	IntersectionVerticale( a,b, R.left ) ;
 	
 	if ( PtSurBordRect( R, Pt ))
 		{
 		// Le point calcule est un bon candidat au point de sortie
 		PointsRetenus[NbPtsRetenus]	=	Pt ;
 		NbPtsRetenus				++ ;
 		}
 	
	// Intersection avec le bord droit (droite verticale )
	Pt	=	IntersectionVerticale( a,b, R.right ) ;
 	if ( PtSurBordRect( R, Pt ))
 		{
 		// Le point calcule est un bon candidat au point de sortie
 		PointsRetenus[NbPtsRetenus]	=	Pt ;
 		NbPtsRetenus				++ ;
 		}
 	
 	if ( NbPtsRetenus < 2 )
 		{
	 	// Intersection avec le bord haut (droite horizontale )
		Pt	=	IntersectionHorizontale( a, b, R.top ) ;
	 	if ( PtSurBordRect( R, Pt ))
	 		{
	 		// Le point calcule est un bon candidat au point de sortie
	 		PointsRetenus[NbPtsRetenus]	=	Pt ;
	 		NbPtsRetenus				++ ;
	 		}
	 	
	 	if ( NbPtsRetenus < 2 )
	 		{
		 	// Intersection avec le bord bas(droite horizontale )
			Pt	=	IntersectionHorizontale( a, b, R.bottom ) ;
		 	if ( PtSurBordRect( R, Pt ))
		 		{
		 		// Le point calcule est un bon candidat au point de sortie
		 		PointsRetenus[NbPtsRetenus]	=	Pt ;
		 		NbPtsRetenus				++ ;
		 		}
			}
		} 	
		
	ASSERT( NbPtsRetenus == 2 ) ;
	if ( DistanceCarre( Point, PointsRetenus[0] ) < DistanceCarre( Point, PointsRetenus[1] )) 
		return PointsRetenus[0] ;
	else
		return PointsRetenus[1] ;
}
