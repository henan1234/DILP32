extern void	TroisD2DeuxD( double x, double y, double z, double & X, double & Y ) ;
extern double RegleDe3( double Value, double MinSrc, double MaxSrc, double MinDest, double MaxDest ) ;
extern void	EloigneCouleur( double z, BYTE & Rouge, BYTE & Vert, BYTE & Bleu ) ;
extern int CalculDiametre(const double z, const double DiametreMax ) ;
extern double LongueurLien( const T_LIEN & Lien ) ;
extern double DistanceLien( const T_LIEN & Lien ) ;
extern int	_cdecl CompareAtomes( const void * El1, const void * El2 ) ;
extern int	_cdecl CompareLiens( const void * El1, const void * El2 ) ;
extern void	DessineCage( CDC & Dc ) ;
///////////////////////////////////////////////////////////////////////////////
// Decide s'il faut plutot dessiner un atome qu'un lien en fonction des
// distances
///////////////////////////////////////////////////////////////////////////////
extern BOOL PlutotUnAtome( T_ATOME * AtomesTries, int IndiceLien, int IndiceAtome ) ;
double LongueurLienCarre( int iLien ) ;
double	LongueurLien( int iLien ) ;
double	LongueurLien( const T_LIEN & ) ;
extern void DessineAtome( CDC & , const T_ATOME & ) ;
extern void DessineLien( CDC & , const T_LIEN & ) ;
extern	void AjouteRectangleLien( CRect & ) ;
extern void	CalculeCoordonneesSortieLien( const T_ATOME & Atome1, const T_ATOME & Atome2, double & SortieX, double & SortieY, double & SortieZ ) ;