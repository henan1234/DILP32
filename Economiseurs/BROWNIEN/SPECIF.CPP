// Partie specifique de l'economiseur
#define STRICT
#include "..\stdafx.h"
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include "resource.h"
#include "..\specif.h"
#include "..\animate.h"

// ================================================================= Constantes
const char*		SPECIF_NomEconomiseur	=	"Mouvement Brownien" ;
const char*		SPECIF_ValeurEnregistre	=	"MB//1471942" ;
#define			NB_MAX_CORPS		500		// En attendant une machine plus rapide, pas la peine de prevoir plus
#define			NB_MAX_COULEURS		8
#define			NB_BITMAPS			2
#define			NB_MAX_RECTS		100
#define			MAX_Z				1000
#define			MIN_Z				-100
#define			TAILLE_MAX			64
#define			TAILLE_MIN			8 
#define			NB_IMAGES			((TAILLE_MAX-TAILLE_MIN)/2)

// ================================================================= Types
typedef	struct
		{
		double	x ;
		double	y ;
		double	z ;
		double	vx ;
		double	vy ;
		double	vz ;

		int		Couleur ;
		int		IndiceImage ;
		}
		T_CORPS ;

extern		HANDLE hMainInstance ;
T_CORPS		Corps[NB_MAX_CORPS] ;

//HBITMAP		hBitmaps[NB_MAX_COULEURS][NB_IMAGES] ;
CDIBSurface*	pBitmaps[NB_MAX_COULEURS][NB_IMAGES] ;

///////////////////////////////////////////////////////////////////////////////
// Preferences
///////////////////////////////////////////////////////////////////////////////
int		NbCorps			=	8 ;				// Nombre de corps reellement geres
int		NombreCouleurs	=	2 ;				// Nombre de couleurs de corps
double	CoeffDistance	=	99999999.0 ;	// Coeff multiplicateur de distance
double	CoeffAttraction	=	99999999999.0 ;	// Coeff multiplicateur d'attraction
double	DeltaTMax		=	1.5 ;			// Tps max pris en compte entre deux animations
double	CoeffRebond		=	0.98 ;			// Coeff multiplicateur en cas de rebond
double	DeltaT ;							// Tps entre les deux animations
int		NbImages		=	NB_IMAGES ;
//HDC		hMemDC ;
DWORD	DernierTemps ;

CDIBPal	Palette ;
CDIBSurface*	pDCIntermediaire ;


RECT	RAAfficher ;
RECT	RectsAffichage[ NB_MAX_RECTS ] ;
int		NbRectsAAfficher ;

int		ChangeIntervalle( int Valeur, int DepMin, int DepMax, int DestMin, int DestMax )
{
	Valeur	-= DepMin ;
	Valeur	=	MulDiv( Valeur, DestMax-DestMin, DepMax-DepMin ) ;
	Valeur +=	DestMin ;
	return Valeur ;
}


// ==================================================================================================
// Rendre une valeur positive
// ==================================================================================================
void	Positif( double * pDouble )
{
	if ( (*pDouble) < 0.0 )
		(*pDouble) = -(*pDouble) ;

	if (*pDouble <= 0.5)
		(*pDouble) = 0.5 ;
}

// ==================================================================================================
// Rendre une valeur negative
// ==================================================================================================
void	Negatif( double * pDouble )
{
	if ( (*pDouble)> 0.0 )
		(*pDouble) = -(*pDouble) ;

	if (*pDouble >= -0.5)
		(*pDouble) = -0.5 ;
}

// ==================================================================================================
// Generation des corps
// ==================================================================================================
void	GenereCorps( void )
{   
	int	i ;
	
	for ( i = 0; i < NbCorps; i++)
		{
		Corps[i].x		=	Alea( 0,Largeur) ;
		Corps[i].y		=	Alea( 0,Hauteur) ;
		Corps[i].z		=	Alea( MIN_Z, MAX_Z ) ;
		Corps[i].vx		=	0 ;
		Corps[i].vy		=	0 ;
		Corps[i].vz		=	0 ;
		Corps[i].Couleur=	i % NombreCouleurs ;
		}
}

// ==================================================================================================
// Charger et retailler une bitmap
// ==================================================================================================
void	ChargeUneBitmap( CDIB*	pDibReference,
						 int i, int j,
						 int	Taille )
{
	pBitmaps[i][j]	=	new	CDIBSurface ;
	pBitmaps[i][j]->Create( Taille, Taille, &Palette ) ;
	pDibReference->StretchBits( pBitmaps[i][j], 0, 0, Taille, Taille,
								0, 32*i, 32, 32 ) ;
}

// ==================================================================================================
// Charge les bitmaps necessaires a l'affichage
// On calcule le nombre de phase de chaque bitmap en divisant la largeur par la hauteur (chaque
// phase est a cote es autres )
// ==================================================================================================
void	ChargeBitmaps( void )
{
	CDIB	Dib ;
	VERIFY( Dib.Load( IDB_PARTICULES )) ; 

	Palette.Create( &Dib ) ;
	hPalette	=	(HPALETTE)Palette.m_hObject ;

	for (  int i = 0; i < NombreCouleurs; i++)
		for ( int j	=	0; j < NbImages; j++)
		{
		ChargeUneBitmap( &Dib,
						 i, j,
						 ChangeIntervalle(j, 0, NbImages-1, TAILLE_MIN, TAILLE_MAX )) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Fonction appelee en cas d'erreur sur les nombres flottants
///////////////////////////////////////////////////////////////////////////////
extern "C" void _cdecl ErreurFlottant( int sig )
{
}

// ==================================================================================================
// ==================================================================================================
extern "C" void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	AfxSetResourceHandle( (HINSTANCE)hMainInstance ) ;

	NoircirEcran = TRUE ;
	HautePriorite = FALSE ;

	if ( Largeur < 500 || Hauteur < 400 )
		NbImages	=	NB_IMAGES / 2 ;

	signal( SIGFPE, ErreurFlottant ) ;
    
	DernierTemps	=	GetCurrentTime() ;

	ChargeBitmaps() ;
	pDCIntermediaire	=	new CDIBSurface ;
	pDCIntermediaire->Create( Largeur, Hauteur, &Palette ) ;

	GenereCorps() ;
	SetTimer( hWnd, 1,50, 0 ) ;
	NbRectsAAfficher	=	0 ;
}  

// ==================================================================================================
// CalculeDistance
//	Calcule la distance entre deux corps
// ==================================================================================================
double	__inline CalculeDistance( T_CORPS T1, T_CORPS T2 )
{
	double	DX, DY ;
	DX	=	T1.x - T2.x ;
	DY	=	T1.y - T2.y ;
	
	return sqrt( (DX*DX) + (DY*DY) ) ;
}

double Attirance( double Attraction, int Couleur1, int Couleur2 )
{
	if ( Couleur1 == Couleur2 )
		return -Attraction ;
                                         
	if ( abs( Couleur1-Couleur2 ) == NombreCouleurs/2 )
		return Attraction ;

	return 0.0 ;
}

// ============================================================================
// Accelere
// Calcule l'acceleration gravitationnelle reciproque qui s'exerce entre deux
// corps
// ENTREES	:	Les deux corps
// SORTIES	:	Les deux corps avec leurs vitesse modifiees
// ============================================================================
void	__inline Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 )
{
	double DistanceCarre, DistanceX, DistanceY, DistanceZ ;
	double Attraction ;
	double Attraction1, Attraction2 ;
	double	Distance	;
	
	// ================================================== Calcul de la distance
	DistanceX	=   (pCorps2->x - pCorps1->x) * CoeffDistance ;
	DistanceY	=   (pCorps2->y - pCorps1->y) * CoeffDistance ;
	DistanceZ	=   (pCorps2->z - pCorps1->z) * CoeffDistance ;
	
	DistanceCarre	=	DistanceX*DistanceX + DistanceY*DistanceY + DistanceZ*DistanceZ ;
	
	if ( DistanceCarre > 0.5 )
		{		
		Distance	=	sqrt( DistanceCarre) ;
		// ================================= Calcul de la force global d'attraction
		Attraction		=	CoeffAttraction / DistanceCarre;

		Attraction1		=	Attirance( Attraction, pCorps1->Couleur, pCorps2->Couleur ) ;
		Attraction2		=	Attirance( Attraction, pCorps2->Couleur, pCorps1->Couleur ) ;

		// ======================= Repartition des vecteurs d'attraction sur x et y
		pCorps1->vx	+=	( Attraction1 * DistanceX ) ;
		pCorps2->vx	-=	( Attraction2 * DistanceX ) ;
		
		pCorps1->vy	+=	( Attraction1 * DistanceY ) ;
		pCorps2->vy	-=	( Attraction2 * DistanceY ) ;
		
		pCorps1->vz	+=	( Attraction1 * DistanceZ ) ;
		pCorps2->vz	-=	( Attraction2 * DistanceZ ) ;
		}
}

// ============================================================================
// Affiche
// ============================================================================
void	__inline Affiche( T_CORPS	*	pCorps )
{
	const int Indice	=	pCorps->IndiceImage ;
	const int L	=	pBitmaps[pCorps->Couleur][Indice]->GetWidth() ;
	const int H =	pBitmaps[pCorps->Couleur][Indice]->GetHeight() ;

	RECT		R ;
	R.left	=	(int)pCorps->x  ;
	R.top	=	(int)pCorps->y  ;

	R.right	=	R.left + L ;
	R.bottom=	R.top + H ;

	if ( (R.left >= 0) && (R.right < Largeur) && (R.top >= 0) && (R.bottom < Hauteur) )
		{
		pBitmaps[pCorps->Couleur][Indice]->CopyBits( pDCIntermediaire,
													 R.left, R.top,	L, H,
													 0,0,
													 PALETTEINDEX(0)) ;
			
		AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &R ) ;
		}
}

// ============================================================================
// Efface, on se contente juste de marquer la zone a reafficher
// ============================================================================
void	__inline Efface( T_CORPS	*	pCorps )
{
	RECT	R ;
	const int L	=	pBitmaps[pCorps->Couleur][pCorps->IndiceImage]->GetWidth() ;
	const int H	=	pBitmaps[pCorps->Couleur][pCorps->IndiceImage]->GetHeight() ;

	R.left	=	max( 0, (int)pCorps->x ) ;
	R.top	=	max( 0, (int)pCorps->y ) ;
	R.right	=	min( Largeur-1, R.left + L ) ;
	R.bottom=	min( Hauteur-1, R.top + H ) ;

	PatBlt( pDCIntermediaire->GetHDC(), R.left, R.top, R.right-R.left, R.bottom-R.top, BLACKNESS ) ;
		
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &R ) ;
}

// ============================================================================
// CalculeAcceleration
// ============================================================================
void	CalculAccelerations( void )
{
	int	i, j ;

	// Attraction normale entre les corps
	for ( i = 0; i < NbCorps; i++)
		for ( j = i + 1; j < NbCorps; j++ )
			Accelere( &Corps[i], &Corps[j] ) ;
}

int	CompareCorps( const void * elem1, const void * elem2 )
{
	T_CORPS*	pCorps1 ;
	T_CORPS*	pCorps2 ;
	pCorps1		=	(T_CORPS*)elem1 ;
	pCorps2		=	(T_CORPS*)elem2 ;

	return (int)(pCorps1->z - pCorps2->z) ;
}

// ============================================================================
extern "C" void SPECIF_Animation( HDC hDC, UINT NoTimer, LPRECT lpR  )
// ============================================================================
{
	int	i	;
	DWORD	TempsCourant ;

	NbRectsAAfficher	=	0 ;

	// Calcul des interactions qu'exercent les corps les uns sur les autres
	CalculAccelerations() ;
	
	// Pour garder une vitesse constante quelle que soit le temps mis pour les calculs
	TempsCourant	=	GetCurrentTime ();
	DeltaT			=	(TempsCourant-DernierTemps)/1000.0 ;
	DernierTemps	=	TempsCourant ;

	if ( DeltaT > DeltaTMax )
		DeltaT	=	DeltaTMax ;


	for ( i = 0; i < NbCorps; i++)
		{
		Efface( &Corps[i] ) ;
		
		Corps[i].x	+=	Corps[i].vx * DeltaT ;
		Corps[i].y	+=	Corps[i].vy	* DeltaT ;
		Corps[i].z	+=	Corps[i].vz	* DeltaT ;
		Corps[i].IndiceImage	= ChangeIntervalle( (int)Corps[i].z, MIN_Z, MAX_Z, 0, NbImages-1 ) ;
		Corps[i].IndiceImage	=	max( 0, min( Corps[i].IndiceImage, NbImages-1 )) ;
		
		const int L=	pBitmaps[Corps[i].Couleur][Corps[i].IndiceImage]->GetWidth() ;
		const int H=	pBitmaps[Corps[i].Couleur][Corps[i].IndiceImage]->GetHeight() ;

		// Verifier que la particule ne sort pas de l'ecran
		if ( Corps[i].x	< 0)
			{
			Corps[i].x	=	0;
			Corps[i].vx *= CoeffRebond ;
			Positif( &Corps[i].vx ) ;
			}
		else
		if ( Corps[i].x + L> Largeur )
			{
			Negatif( &Corps[i].vx ) ;
			Corps[i].vx *= CoeffRebond ;
			Corps[i].x	=	Largeur-L ;
			}

		if ( Corps[i].y	< 0 )
			{
			Positif( &Corps[i].vy ) ;
			Corps[i].vy *= CoeffRebond ;
			Corps[i].y	=	0 ;
			}
		else
		if ( Corps[i].y + H > Hauteur )
			{
			Negatif( &Corps[i].vy ) ;
			Corps[i].vy *= CoeffRebond ;
			Corps[i].y	=	Hauteur-H ;
			}

		if ( Corps[i].z	< MIN_Z  )
			{
			Positif( &Corps[i].vz ) ;
			Corps[i].vz *= CoeffRebond ;
			Corps[i].z	=	MIN_Z  ;
			}
		else
		if ( Corps[i].z > MAX_Z )
			{
			Negatif( &Corps[i].vz ) ;
			Corps[i].vz *= CoeffRebond ;
			Corps[i].z	=	MAX_Z ;
			}
		}

	// Trier : les plus loins d'abord
	qsort( Corps, NbCorps, sizeof( Corps[0] ), CompareCorps ) ;

	for ( i = 0; i < NbCorps; i++)
		Affiche( &Corps[i] ) ;
		
	AfficheRectangles( RectsAffichage, NbRectsAAfficher, hDC, pDCIntermediaire->GetHDC()) ;
}

// ============================================================================
// SPECIF_Fin
// Fin de l'economiseur
// ============================================================================
extern "C" void SPECIF_Fin( HWND hWnd )
{
	delete pDCIntermediaire ;
}

 
// ============================================================================
// SPECIF_PaintFenetre
// Peindre la fenetre
// ============================================================================
extern "C" void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{  
}


// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
extern "C" void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	TRUE ;
	
	HautePriorite	=	LitEntier( "Haute Priorite",	HautePriorite ) ;
	NbCorps			=	LitEntier( "NbCorps",	NbCorps ) ;
	NbCorps			=	max( 2, min( NB_MAX_CORPS, NbCorps )) ;

	NombreCouleurs		=	LitEntier( "NombreCouleurs",		NombreCouleurs ) ;
	NombreCouleurs		=	max( 1, min( NB_MAX_COULEURS, 	NombreCouleurs )) ;

	if ( VerifVersion())
		{
		CoeffDistance	=LitDouble(	"CoeffDistance",		CoeffDistance	) ;
		CoeffAttraction	=LitDouble(	"CoeffAttraction",		CoeffAttraction ) ;
		CoeffRebond		=LitDouble(	"CoeffRebond",			CoeffRebond ) ;
		DeltaTMax		=LitDouble(	"DeltaTMax",			DeltaTMax		) ;
		}
}							  

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
extern "C" void SPECIF_EcrirePreferences( void )
{
	EcritEntier( "Haute Priorite",		HautePriorite ) ;
	EcritEntier( "NbCorps",				NbCorps ) ;
	EcritEntier( "NombreCouleurs", 			NombreCouleurs ) ;


	if ( VerifVersion())
		{
		EcritDouble(	"CoeffDistance",	CoeffDistance	) ;
		EcritDouble(	"CoeffAttraction",	CoeffAttraction	) ;
		EcritDouble(	"DeltaTMax",		DeltaTMax		) ;
		EcritDouble(	"CoeffRebond",		CoeffRebond ) ;
		}
}


static	void	ConfSpin( HWND hWnd, UINT Id, UINT IdEdit, int	Valeur, int Min, int Max )
{
	SendDlgItemMessage( hWnd, Id, UDM_SETBUDDY, (WPARAM)GetDlgItem( hWnd, IdEdit ), 0 ) ;
	SendDlgItemMessage( hWnd, Id, UDM_SETRANGE, 0, (LPARAM)MAKELONG( Max, Min ) ) ;
	SendDlgItemMessage( hWnd, Id, UDM_SETPOS, 0, (LPARAM)MAKELONG( Valeur, 0 ) ) ;

	SetDlgItemInt	  ( hWnd, IdEdit, Valeur, TRUE ) ;
}

// ============================================================================
// SPECIF_ConfCommande
// WM_COMMAND
// ============================================================================
extern "C" BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			AfxSetResourceHandle( (HINSTANCE)hMainInstance ) ;
			SPECIF_LirePreferences();
			CheckDlgButton( hDlg, IDC_PRIORITE, HautePriorite ) ;

			NbCorps	=	min( NbCorps, NB_MAX_CORPS ) ;

			ConfSpin( hDlg, IDC_BUDDY1, IDC_NB_PARTICULES, NbCorps, 2, NB_MAX_CORPS ) ;
			ConfSpin( hDlg, IDC_BUDDY2, IDC_NB_CHARGES, NombreCouleurs, 2, NB_MAX_COULEURS ) ;
			}
			break ;


		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					{
					BOOL	tr ;
					NbCorps	=	GetDlgItemInt( hDlg, IDC_NB_PARTICULES, &tr, TRUE ) ;
					NbCorps	=	min( NB_MAX_CORPS, max(2, NbCorps )) ;
				
					NombreCouleurs	=	GetDlgItemInt( hDlg, IDC_NB_CHARGES, &tr, TRUE ) ;
					NombreCouleurs	=	min( NB_MAX_COULEURS, max(2, NombreCouleurs )) ;

					SPECIF_EcrirePreferences() ;
					}
					return FALSE ;

				default :
					break ;
				}
			break ;

		default :
			return FALSE ;
		}

	return FALSE ;
}
