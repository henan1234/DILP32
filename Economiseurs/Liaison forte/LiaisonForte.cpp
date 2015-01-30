///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
#include "..\economiseur generique\stdafx.h"
#include <math.h>
#include <signal.h>
#include "resource.h"
#include <RectAffichage.h>
#include "LiaisonForte.h"
#include "configuration.h"
#include "information.h"
#include <RegistrationKey.h>
#include "DlgNombres.h"
#include "PhysiqueDlg.h"
#include "DlgCouleurs.h"

#define LIMITE(x, i, a )	(x) < (i) ? (i) : (x) > (a) ? (a) : (x)


T_FANTOMELIEN	LiensCasses[ NB_MAX_LIENS ] ;
int	NbLiensCasses	=	0 ;

int		NbLiens	 ;
DWORD	DernierAffichage	= GetCurrentTime() ;
int		Diviseur		=	8 ;
CRITICAL_SECTION		SectionCritique ;

// Preferences
DWORD		ImagesSecondes	=	20 ;
COLORREF	CouleurFond	=	RGB( 192, 192, 192 ) ;
COLORREF	AtomeLibre	=	RGB( 255, 0, 0 ) ;
COLORREF	AtomeSature	=	RGB( 0, 0, 255 ) ;
COLORREF	CouleurLien	=	RGB( 0, 128, 0 ) ;
double		LongueurVoulue	=	100 ;
double		LongueurMax		=	200 ;
double		LongueurMin		=	90 ;
int			NbAtomes=	15 ;
double		Agitation		=	0.015 ;
double		Intensite		=	1.5 ;
double		Repulsion		=	1 ;
int			NbMaxLiensParAtome	=	6 ;
double		Amortissement	=	0.001 ;
T_ATOME	Atomes[ NB_MAX_ATOMES ] ;
T_ATOME	AtomesTries[ NB_MAX_ATOMES ] ;
T_LIEN	Liens[ NB_MAX_LIENS ] ;


CRegistrationKey	LaClef( LIF_PATH, LIF_HIDDEN ) ;

CLiaisons	ZeEconomiseur ;		// L'objet economiseur


CRectAffichage	DerniersRectangles, NouveauxRectangles ;	// Pour optimisation de l'affichage

CDC				DCMemoire ;									// DC Intermediaire pour affichage sans clignotement
CBitmap			Bitmap ;									// Bitmap du DC intermediaire
CBitmap*		pOldBitmapMemoire ;							// Memo bitmap initiale du dc intermediaure

double X1, X2, X3, X4, X5, X6, X7, X8 ;
double Y1, Y2, Y3, Y4, Y5, Y6, Y7, Y8 ;

#include "utilitaires.h"

#pragma message( "debut" )


#pragma message( "dessine cage" )




double inline abs( double v )
{
	return v >= 0 ? v : - v ;
}

// Juste pour eviter les divide by zero
void _cdecl ErreurFlottant( int sig )
{
}
#pragma message( "dessine atome" )


#pragma message( "constructeur" )
CLiaisons::CLiaisons(  ) :CEconomiseur( "Molecules" )
{
}


CLiaisons::~CLiaisons()
{
}

///////////////////////////////////////////////////////////////////////////////
// Sature
//	Determine si un atome a tous ses liens satures
///////////////////////////////////////////////////////////////////////////////
inline BOOL CLiaisons::Sature( int iAtome )
{
	ASSERT( iAtome >= 0 ) ;
	ASSERT( iAtome < NbAtomes ) ;

	return Atomes[iAtome].NbLiens >= Atomes[iAtome].NbMaxLiens ;
}


void CLiaisons::InitSave( HWND	hWnd )
{
	CEconomiseur::InitSave( hWnd ) ;

	signal( SIGFPE, ErreurFlottant ) ;
    
	if ( Apercu())
		NbAtomes	=	4 ;

	PlaceAtomes() ;

	InitializeCriticalSection( &SectionCritique ) ;

	SetTimer( hWnd, 1, 5000, NULL ) ;
}

void CLiaisons::Configuration( CPropertySheet * pSheet )
{
		pSheet->AddPage( new CInformation ) ;

		pSheet->AddPage( new CDlgNombres );
		pSheet->AddPage( new CPhysiqueDlg ) ;
		pSheet->AddPage( new CDlgCouleurs ) ;

		//pSheet->AddPage( new CConfiguration ) ;


		CEconomiseur::Configuration( pSheet ) ;
}

		// Animation
void	CLiaisons::UpdateFenetre( CDC &, const CRect & )
{
}

///////////////////////////////////////////////////////////////////////////////
// Animation
// Appelee periodiquement par le thread d'economisage pour faire l'animation
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::Animation( CDC&	Dc )
{
	CalculeAcceleration() ;
	
	BougeAtomes() ;

	CasseLiens() ;
	CreerLiens() ;

	// Effacement dessin precedent
	EnterCriticalSection(&SectionCritique) ;
	DerniersRectangles.FillRect( DCMemoire, CouleurFond ) ;
	DessineCage( DCMemoire ) ;

	// Nouveau dessin
	DessineLiensCasses( DCMemoire ) ;
	Dessine(DCMemoire) ;
	
	// Transferer a l'ecran les nouvelles images et les effacements
	DerniersRectangles +=	NouveauxRectangles ;
	DerniersRectangles.BitBlt( Dc, DCMemoire ) ;

	DerniersRectangles	=	NouveauxRectangles ;
	NouveauxRectangles.Vide() ;
	LeaveCriticalSection(&SectionCritique) ;
}

void CLiaisons::InitDC( CDC & Dc )
{
	// Creation du DC intermediaire
	//CDC	Dc ;
	//Dc.CreateDC( "display", 0, 0, 0 ) ;
	DCMemoire.CreateCompatibleDC(&Dc) ;	

	Bitmap.CreateCompatibleBitmap( &Dc, Largeur, Hauteur ) ;
	pOldBitmapMemoire	=	DCMemoire.SelectObject( &Bitmap ) ;

	//Dc.DeleteDC() ;

	// Calcul des coordonnees ecran des coins de la cage une fois pour toutes
	TroisD2DeuxD( -CLiaisons::Largeur/2, -CLiaisons::Hauteur/2,0,	X1, Y1 ) ;
	TroisD2DeuxD( CLiaisons::Largeur/2, -CLiaisons::Hauteur/2, 0,	X2, Y2 ) ;
	TroisD2DeuxD( CLiaisons::Largeur/2, CLiaisons::Hauteur/2,	0,	X3, Y3 ) ;
	TroisD2DeuxD( -CLiaisons::Largeur/2, CLiaisons::Hauteur/2,0,	X4, Y4 ) ;
	TroisD2DeuxD( -CLiaisons::Largeur/2, -CLiaisons::Hauteur/2,	DISTANCE_MAX,	X5, Y5 ) ;
	TroisD2DeuxD( CLiaisons::Largeur/2, -CLiaisons::Hauteur/2,	DISTANCE_MAX,	X6, Y6 ) ;
	TroisD2DeuxD( CLiaisons::Largeur/2, CLiaisons::Hauteur/2,	DISTANCE_MAX,	X7, Y7 ) ;
	TroisD2DeuxD( -CLiaisons::Largeur/2, CLiaisons::Hauteur/2,	DISTANCE_MAX,	X8, Y8 ) ;

	CBrush Brosse( CouleurFond ) ;
	DCMemoire.FillRect( CRect(0, 0, Largeur, Hauteur), &Brosse ) ;
	Brosse.DeleteObject() ;
	NouveauxRectangles.Espace( CRect(0, 0, Largeur, Hauteur) ) ;

	DerniersRectangles.Vide() ;

	DerniersRectangles.Ajoute( CRect( 0, 0, Largeur, Hauteur )) ;
	}

void CLiaisons::FinDC( CDC & ) 
{
	DCMemoire.SelectObject( pOldBitmapMemoire ) ;
	DCMemoire.DeleteDC() ;
	Bitmap.DeleteObject() ;
}

void CLiaisons::Preferences()
{
	CRegistrationKey	*	pKey	=	CRegistrationKey::GetKey() ;

	if ( !pKey->IsLocked())
		{
		Preference( "Intensite", Intensite ) ;
		Preference( "Amortissement", Amortissement	) ;
		Preference( "Agitation", Agitation	) ;
		Preference( "Repulsion", Repulsion ) ;
		Preference("Couleur de fond", CouleurFond ) ;
		Preference("Couleur des liens", CouleurLien ) ;
		Preference("Couleur sature", AtomeSature ) ;
		Preference("Couleur libre", AtomeLibre ) ;
		Preference( "Images par seconde", ImagesSecondes ) ;
		Preference( "Longueur", LongueurVoulue	) ;
		Preference( "Longueur Max", LongueurMax ) ;
		Preference( "Longueur Min", LongueurMin	) ;
		}

	Preference( "Nb Atomes", NbAtomes ) ;
	Preference( "NbMax liens par atome", NbMaxLiensParAtome ) ;
	
}

void CLiaisons::ValidePreferences()
{
	if ( NbAtomes > NB_MAX_ATOMES )
		NbAtomes	=	NB_MAX_ATOMES  ;

	if (NbAtomes < 2 )
		NbAtomes	=	2 ;

	if( NbMaxLiensParAtome > NB_MAX_LIENS_PAR_ATOME )
		NbMaxLiensParAtome = NB_MAX_LIENS_PAR_ATOME ;

	if ( NbMaxLiensParAtome < 1 )
		NbMaxLiensParAtome = 1 ;
}

///////////////////////////////////////////////////////////////////////////////
// Placer les atomes aleatoirement
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::PlaceAtomes( void )
{	
	const int MinX	=	-Largeur/2 ;
	const int MaxX	=	Largeur/2 ;
	const int MinY	=	-Hauteur/2 ;
	const int MaxY	=	Hauteur/2 ;
	const int MinZ	=	0 ;
	const int MaxZ	=	(int)DISTANCE_MAX ;

	NbLiens	=	0 ;
	for ( int i = 0; i < NbAtomes; i++ )
		{
		Atomes[i].x	=	Alea( MinX, MaxX ) ;
		Atomes[i].y	=	Alea( MinY, MaxY ) ;
		Atomes[i].z	=	Alea( MinZ, MaxZ ) ;
		Atomes[i].Vx=	0 ;
		Atomes[i].Vy=	0 ;
		Atomes[i].Vz=	0 ;
		Atomes[i].NbLiens	=	0 ;
		Atomes[i].NbMaxLiens=	Alea( 1, NbMaxLiensParAtome ) ;
		}
}


///////////////////////////////////////////////////////////////////////////////
// LierAtomes
//	Construire un lien entre deux atomes
// ENTREES :	Indice du lien a creer dans le tableau des liens
//				Indice des deux atomes a creer dans chaque tableau
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::LierAtomes( int IndiceLien, int Atome1, int Atome2 )
{
	if ( Atome1 < 0 )
		return ;

	if ( Atome1 > NbAtomes )
		return ;

	if ( Atome2 < 0 )
		return ;

	if ( Atome2 > NbAtomes )
		return ;

	if ( Sature( Atome1 ))
		return ;

	if ( Sature( Atome2 ))
		return ;

	Liens[IndiceLien].Atome1	=	Atome1 ;
	Liens[IndiceLien].Atome2	=	Atome2 ;

	Atomes[Atome1].AtomesLies[Atomes[Atome1].NbLiens]	=	Atome2 ;
	Atomes[Atome1].NbLiens ++ ;

	Atomes[Atome2].AtomesLies[Atomes[Atome2].NbLiens]	=	Atome1 ;
	Atomes[Atome2].NbLiens ++ ;
}

///////////////////////////////////////////////////////////////////////////////
// Dessiner les atomes et leurs liens.
// L'ordre dans lequel ils sont dessines en l'inverse de z, pour la 3d
// C'est du Z buffering pour pas cher
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::Dessine( CDC & Dc )
{
	const DWORD	Maintenant	=	GetCurrentTime() ;

	if ( Maintenant - DernierAffichage > 1000/ImagesSecondes )
		Diviseur ++ ;
	else
	if ( Maintenant - DernierAffichage < 1000/ImagesSecondes )
		if ( Diviseur > 1 )
			Diviseur -- ;

	DernierAffichage	=	Maintenant ;

	///////////////////////////////////////////////////////////////////////////
	// Construction d'un tableau d'atomes trie en fonction de la distance
	// On ne peut pas trier le vrai tableau, a cause des liens
	///////////////////////////////////////////////////////////////////////////
	memcpy( AtomesTries, Atomes, sizeof( Atomes[ 0 ] ) * NbAtomes ) ;
	qsort( AtomesTries, NbAtomes, sizeof( Atomes[0] ), CompareAtomes ) ;

	qsort( Liens, NbLiens, sizeof( Liens[0] ), CompareLiens ) ;
	
	// Les atomes et les liens sont tries dans l'ordre decroissant de distance

	CGdiObject*	pOld	=	Dc.SelectStockObject( NULL_PEN ) ;
	
	const double	LgLong	=	LongueurVoulue * 1.2 ;
	const double	LgCourt	=	LongueurVoulue * 0.8 ;

	int	IndiceLien	=	0 ;
	int IndiceAtome	=	0 ;

	while ( (IndiceLien < NbLiens) || (IndiceAtome < NbAtomes) )
		if ( PlutotUnAtome( AtomesTries, IndiceLien, IndiceAtome ) )
			// Dessiner Atome
			{
			DessineAtome( Dc, AtomesTries[IndiceAtome] ) ;
			IndiceAtome ++ ;
			}
		else
			{
			DessineLien( Dc, Liens[IndiceLien] ) ;
			IndiceLien ++ ;
			}

	Dc.SelectObject( pOld ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Determine si deux atomes sont deja lies ou non
///////////////////////////////////////////////////////////////////////////////
inline BOOL CLiaisons::DejaLie( int Atome1, int Atome2 )
{
	if ( Atome1 == -1 || Atome2 == -1 )
		return FALSE ;

	if ( Atome1 < 0 || Atome1 >= NbAtomes )
		return FALSE ;

	if ( Atome1 == Atome2 )
		return TRUE ;

	for ( int i = 0; i < Atomes[Atome1].NbLiens; i++ )
		if( Atomes[Atome1].AtomesLies[i] == Atome2 )
			return TRUE ;

	return FALSE ;
}

void CLiaisons::CalculeAcceleration( void )
{
	for ( int i = 0; i < NbLiens; i++ )
		{
		const	int Indice1	=	Liens[i].Atome1 ;
		const	int Indice2	=	Liens[i].Atome2 ;

		if ( Indice1 < 0 || Indice1 >= NbAtomes )
			break ;

		if ( Indice2 < 0 || Indice2 >= NbAtomes )
			break ;

		// ================================================== Calcul de la distance
		const double DistanceX		=   (Atomes[Indice1].x - Atomes[Indice2].x) ;
		const double DistanceY		=   (Atomes[Indice1].y - Atomes[Indice2].y) ;
		const double DistanceZ		=	(Atomes[Indice1].z - Atomes[Indice2].z) ;

		const double DistanceCarre		=	( (DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + ( DistanceZ * DistanceZ )) ;
		const double Distance			=	sqrt( DistanceCarre ) ;
		const double DistanceCube		=	Distance * Distance * Distance ;

		if ( DistanceCarre	>= 1 )
			{
			double	Force	=	(double)(LongueurVoulue-Distance) * Intensite ;
			Force *= abs( Force ) ;

			const double	ForceX	=	Force * (DistanceX / DistanceCube ) ;
			const double	ForceY	=	Force * (DistanceY / DistanceCube ) ;
			const double	ForceZ	=	Force * (DistanceZ / DistanceCube ) ;

			Atomes[Indice1].Vx	+=	ForceX ;
			Atomes[Indice2].Vx	-=	ForceX ;
			
			Atomes[Indice1].Vy	+=	ForceY ;
			Atomes[Indice2].Vy	-=	ForceY ;

			Atomes[Indice1].Vz	+=	ForceZ ;
			Atomes[Indice2].Vz	-=	ForceZ ;
			}
		}

	Repulsions() ;
}

///////////////////////////////////////////////////////////////////////////////
// BougeAtomes
// Calcule le deplacement des atomes en s'assurant qu'ils ne sortent pas de l'ecran
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::BougeAtomes( )
{
	const double MinX	=	-Largeur/2 ;
	const double MaxX	=	Largeur/2 ;
	const double MinY	=	-Hauteur/2 ;
	const double MaxY	=	Hauteur/2 ;
	const double MinZ	=	0 ;
	const double MaxZ	=	DISTANCE_MAX ;

	for ( int i = 0; i < NbAtomes; i++)
		{
		Atomes[i].x += Atomes[i].Vx ;
		Atomes[i].y += Atomes[i].Vy ;
		Atomes[i].z += Atomes[i].Vz ;

		// Leger amortissement du a une perte d'energie
		Atomes[i].Vx *= 1 - Amortissement ;
		Atomes[i].Vy *= 1 - Amortissement ;
		Atomes[i].Vz *= 1 - Amortissement ;

		// Agitation termique ( pour mettre un peu d'animation )
		Atomes[i].Vx += Alea( -10, 10 ) * Agitation ;
		Atomes[i].Vy += Alea( -10, 10 ) * Agitation ;
		Atomes[i].Vz += Alea( -10, 10 ) * Agitation ;

				if ( Atomes[i].x > MaxX )
			{
			Atomes[i].Vx	=	- abs( Atomes[i].Vx ) *  (1-Amortissement) ;
			Atomes[i].x		=	MaxX ;
			}

		if ( Atomes[i].x < MinX )
			{
			Atomes[i].Vx	=	abs( Atomes[i].Vx ) *  (1-Amortissement)  ;
			Atomes[i].x		=	MinX ;
			}

		if ( Atomes[i].y > MaxY )
			{
			Atomes[i].Vy	=	-abs( Atomes[i].Vy ) *  (1-Amortissement) ;
			Atomes[i].y		=	MaxY ;
			}

		if ( Atomes[i].y < MinY )
			{
			Atomes[i].Vy	=	abs( Atomes[i].Vy ) *  (1-Amortissement) ;
			Atomes[i].y		=	MinY ;
			}


		if ( Atomes[i].z < MinZ )
			{
			Atomes[i].Vz	=	abs( Atomes[i].Vz ) * (1- Amortissement ) ;
			Atomes[i].z		=	MinZ ;
			}

		if ( Atomes[i].z > MaxZ )
			{
			Atomes[i].Vz	=	-abs( Atomes[i].Vz ) * (1-Amortissement ) ;
			Atomes[i].z		=	MaxZ ;
			}
		}
}


void CLiaisons::CasseLiens( void )
{
	const double DistanceMaxCarre	=	LongueurMax * LongueurMax ;

	for ( int i = NbLiens-1; i >= 0; i-- )
		if ( LongueurLienCarre( i ) > DistanceMaxCarre )
			{
			if ( NbLiensCasses < NB_MAX_LIENS )
				{
				double X, Y ;
				TroisD2DeuxD( Atomes[Liens[i].Atome1].x, Atomes[Liens[i].Atome1].y, Atomes[Liens[i].Atome1].z,
							  X, Y ) ;
				LiensCasses[NbLiensCasses].Origine.x	=	(int)X ;
				LiensCasses[NbLiensCasses].Origine.y	=	(int)Y ;

				TroisD2DeuxD( Atomes[Liens[i].Atome2].x, Atomes[Liens[i].Atome2].y, Atomes[Liens[i].Atome2].z,
							  X, Y ) ;
				LiensCasses[NbLiensCasses].Destination.x	=	(int)X ;
				LiensCasses[NbLiensCasses].Destination.y	=	(int)Y ;

				NbLiensCasses ++ ;
				}

			SupprimeLien( Liens[i].Atome1, Liens[i].Atome2 ) ;
			SupprimeLien( Liens[i].Atome2, Liens[i].Atome1 ) ;

			// Casse le lien !
			memmove( &Liens[i], &Liens[i+1], sizeof( Liens[0] ) * (NbLiens-i)) ;
			NbLiens -- ;
			}
}


void CLiaisons::CreerLiens( void )
{
	// On calcule sur les distances au carre, ca evite le calcul des racines carrees
	const double DistanceMinCarre	=	LongueurMin * LongueurMin ;
	
	for ( int i = 0; i < NbAtomes; i++ )
		if ( ! Sature( i ) )
			{
			// Cet atome a une liaison libre, on essaie de trouver un autre atome
			// non sature suffisament proche
			if ( NbLiens >= NB_MAX_LIENS )
				return ;

			for ( int j = i+1; j < NbAtomes; j++)
				if ( ! Sature( j ) && !DejaLie( i, j ))
					{
					// Distance separant les atomes
					const double DistanceX		=   (Atomes[i].x - Atomes[j].x)  ;
					const double DistanceY		=   (Atomes[i].y - Atomes[j].y)  ;
					const double DistanceZ		=   (Atomes[i].z - Atomes[j].z)  ;

					const double DistanceCarre	=	(DistanceX * DistanceX )
												  + (DistanceY * DistanceY )
												  + (DistanceZ * DistanceZ ) ;
					
					if ( DistanceCarre <= DistanceMinCarre )
						{
						// Creation du lien
						LierAtomes( NbLiens, i, j ) ;
						NbLiens ++ ;
						}
					}
		
			}
}

///////////////////////////////////////////////////////////////////////////////
// SupprimeLien
//	Suppression d'un lien
// ENTREE :	Indice de l'atome dont on supprime un lien
//			Indice de l'atome avec lequel il ete lie
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::SupprimeLien( int Atome, int AtomeLie )
{
	for ( int i = 0; i < Atomes[Atome].NbLiens; i++ )
		if ( Atomes[Atome].AtomesLies[i] == AtomeLie )
			{
			memmove( &Atomes[Atome].AtomesLies[i],
					 &Atomes[Atome].AtomesLies[i+1],
					 sizeof( Atomes[0].AtomesLies[0] ) * (Atomes[Atome].NbLiens - i));

			Atomes[Atome].NbLiens -- ;
			break ;
			}
}



void CLiaisons::DessineLiensCasses( CDC & Dc )
{
	CPen	Pen( PS_DOT, 0, RGB( 255, 0, 0)) ;
	Dc.SetBkColor( CouleurFond );

	CPen*	pOld	=	Dc.SelectObject( &Pen ) ;
	for ( int i = NbLiensCasses-1; i >= 0; i-- )
		{
		Dc.MoveTo( LiensCasses[i].Origine.x, LiensCasses[i].Origine.y ) ;
		Dc.LineTo( LiensCasses[i].Destination.x, LiensCasses[i].Destination.y ) ;

		AjouteRectangleLien( CRect( LiensCasses[i].Origine, LiensCasses[i].Destination ) ) ;
		
		int	DistanceX	= LiensCasses[i].Origine.x	- LiensCasses[i].Destination.x ;
		int	DistanceY	= LiensCasses[i].Origine.y	- LiensCasses[i].Destination.y ;

		if ( DistanceX > 10 || DistanceY > 10 )
			{
			LiensCasses[i].Origine.x -= DistanceX / 8 ;
			LiensCasses[i].Destination.x += DistanceX / 8 ;
			LiensCasses[i].Origine.y -= DistanceY / 8 ;
			LiensCasses[i].Destination.y += DistanceY / 8 ;
			}	
		else
			{
			memmove( &LiensCasses[i], &LiensCasses[i+1], sizeof( LiensCasses[0] )*(NbLiensCasses-i)) ;
			NbLiensCasses -- ;
			}
		}

	Dc.SelectObject( pOld ) ;
	Pen.DeleteObject() ;
}



///////////////////////////////////////////////////////////////////////////////
// Les atomes lies au meme atome se repoussent les un les autres, ca devrait
// permettre de "deplier" les liens entre les atomes
///////////////////////////////////////////////////////////////////////////////
void CLiaisons::Repulsions( void )
{
	// Boucle sur tous les atomes
	for ( int i = 0; i < NbAtomes; i++)
		// Boucle sur les liens de l'atome
		for ( int j = 0; j < Atomes[i].NbLiens-1; j++)
			{
			const int iAtome1	=	Atomes[i].AtomesLies[j] ;
			if ( iAtome1 < 0 || iAtome1 > NbAtomes )
				break ;

			///////////////////////////////////////////////////////////////////
			// Parcours des atomes lies a l'atome courant, ce sont ces atomes
			// qui se repoussent mutuellement
			///////////////////////////////////////////////////////////////////
			// boucle sur les autres liens de l'atome
			for ( int k = j+1; k < Atomes[i].NbLiens; k++)
				if ( ! DejaLie( j, k ))
				{
				const int iAtome2	=	Atomes[i].AtomesLies[k] ;
				if ( iAtome2 < 0 || iAtome2 > NbAtomes )
					break ;
			
				// ================================================== Calcul de la distance
				const double DistanceX		=   (Atomes[iAtome1].x - Atomes[iAtome2].x)  ;
				const double DistanceY		=   (Atomes[iAtome1].y - Atomes[iAtome2].y)  ;
				const double DistanceZ		=   (Atomes[iAtome1].z - Atomes[iAtome2].z)  ;

				const double DistanceCarre		=	(DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + ( DistanceZ * DistanceZ );
				const double Distance			=	sqrt( DistanceCarre ) ;
				const double DistanceCube		=	Distance * Distance * Distance ;

				if ( DistanceCube != 0 )
					{
					const double	Force	=	-abs(Distance) * Repulsion ;
					
					const double	ForceX	=	Force * (DistanceX / DistanceCube ) ;
					const double	ForceY	=	Force * (DistanceY / DistanceCube ) ;
					const double	ForceZ	=	Force * (DistanceZ / DistanceCube ) ;

					Atomes[iAtome1].Vx	-=	ForceX ;
					Atomes[iAtome2].Vx	+=	ForceX ;
					
					Atomes[iAtome1].Vy	-=	ForceY ;
					Atomes[iAtome2].Vy	+=	ForceY ;

					Atomes[iAtome1].Vz	-=	ForceZ ;
					Atomes[iAtome2].Vz	+=	ForceZ ;
					}
				}
			}
}

void CLiaisons::PeintFenetre(CDC & Dc, const CRect & R)
{
	Dc.BitBlt( R.left, R.top, R.Width(), R.Height(), &DCMemoire, 0, 0, SRCCOPY ) ;
}


BYTE	CLiaisons::ChangeComposante( BYTE Composante )
{
	const int	Delta	=	Alea( -16, 16 ) ;
	int			Nouveau	=	Composante+Delta ;

	if ( Nouveau < 0 )
		Nouveau	=	 0 ;

	if( Nouveau > 255 )
		Nouveau = 255 ;

	return LOBYTE( Nouveau ) ;
}

void CLiaisons::OnTimer( UINT IdTimer )
{
	EnterCriticalSection(&SectionCritique) ;
	CouleurFond	=	RGB( ChangeComposante( GetRValue( CouleurFond )),
						 ChangeComposante( GetGValue( CouleurFond )),
						 ChangeComposante( GetBValue( CouleurFond ))) ;

	DerniersRectangles.Vide() ;

	DerniersRectangles.Ajoute( CRect( 0, 0, Largeur, Hauteur )) ;
	DerniersRectangles.FillRect( DCMemoire, CouleurFond ) ;
	DessineCage( DCMemoire ) ;
	LeaveCriticalSection( &SectionCritique ) ;
}

#pragma message ( "fin du fichier" )
