///////////////////////////////////////////////////////////////////////////////
// EcoBrownien
// Implementation de CEcoBrownien
///////////////////////////////////////////////////////////////////////////////
#include "..\Economiseur Generique\stdafx.h"
#include <math.h>
#include <signal.h>
#include "..\..\Classes\Dib.h"
#include "..\..\Classes\DibSurface.h"
#include "..\..\Classes\Dibpal.h"
#include "..\Economiseur Generique\RectAffichage.h"
#include "resource.h"
#include "Brownien.h"
#include "Page1.h"
#include "page2.h"

CEcoBrownien	MonEconomiseur ;

///////////////////////////////////////////////////////////////////////////////
// Fonction appelee en cas d'erreur sur les nombres flottants
///////////////////////////////////////////////////////////////////////////////
extern "C" void _cdecl ErreurFlottant( int sig )
{
}

CEcoBrownien::CEcoBrownien()
:CEconomiseur( "Mouvement brownien", "tsoin" )
{
	NbCorps			=	8 ;				// Nombre de corps reellement geres
	NombreCouleurs	=	2 ;				// Nombre de couleurs de corps
	CoeffAttraction	=	50.0 ;	// Coeff multiplicateur d'attraction
	DeltaTMax		=	1.5 ;			// Tps max pris en compte entre deux animations
	CoeffRebond		=	0.98 ;			// Coeff multiplicateur en cas de rebond
	DeltaT ;							// Tps entre les deux animations
	pDCIntermediaire	=	0 ;
	NbImages		=	NB_IMAGES ;
	_TailleMin		=	TAILLE_MIN ;
	_TailleMax		=	TAILLE_MAX ;
}

CEcoBrownien::~CEcoBrownien()
{
}

// ==================================================================================================
// Rendre une valeur positive
// ==================================================================================================
void	CEcoBrownien::Positif( double * pDouble )
{
	if ( (*pDouble) < 0.0 )
		(*pDouble) = -(*pDouble) ;

	if (*pDouble <= 0.5)
		(*pDouble) = 0.5 ;
}

// ==================================================================================================
// Rendre une valeur negative
// ==================================================================================================
void	CEcoBrownien::Negatif( double * pDouble )
{
	if ( (*pDouble)> 0.0 )
		(*pDouble) = -(*pDouble) ;

	if (*pDouble >= -0.5)
		(*pDouble) = -0.5 ;
}

// ==================================================================================================
// Generation des corps
// ==================================================================================================
void	CEcoBrownien::GenereCorps( void )
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

int		CEcoBrownien::ChangeIntervalle( int Valeur, int DepMin, int DepMax, int DestMin, int DestMax )
{
	Valeur	-= DepMin ;
	Valeur	=	MulDiv( Valeur, DestMax-DestMin, DepMax-DepMin ) ;
	Valeur +=	DestMin ;
	return Valeur ;
}

// ==================================================================================================
// Charger et retailler une bitmap
// ==================================================================================================
void	CEcoBrownien::ChargeUneBitmap( CDIB*	pDibReference,
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
void	CEcoBrownien::ChargeBitmaps( void )
{
	CDIB	Dib ;
	VERIFY( Dib.Load( IDB_PARTICULES )) ; 

	Palette.Create( &Dib ) ;
	SetPalette( (HPALETTE)Palette.m_hObject ) ;

	for (  int i = 0; i < NombreCouleurs; i++)
		for ( int j	=	0; j < NbImages; j++)
		{
		ChargeUneBitmap( &Dib,
						 i, j,
						 ChangeIntervalle(j, 0, NbImages-1, _TailleMin, _TailleMax )) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur en mode animation
///////////////////////////////////////////////////////////////////////////////
void CEcoBrownien::InitSave( HWND	hWnd ) 
{
	CEconomiseur::InitSave( hWnd ) ;

	NoircirEcran = TRUE ;
	HautePriorite = FALSE ;

	if( Apercu() )
		{
		NbImages	/=	2 ;
		_TailleMax	/=	2 ;
		}
		
	signal( SIGFPE, ErreurFlottant ) ;
    
	DernierTemps	=	GetCurrentTime() ;

	ChargeBitmaps() ;
	pDCIntermediaire	=	new CDIBSurface ;
	pDCIntermediaire->Create( Largeur, Hauteur, &Palette ) ;

	GenereCorps() ;
	SetTimer( hWnd, 1,50, 0 ) ;
	Affichage.Espace( CRect( 0,0, Largeur, Hauteur )) ;
}


// ==================================================================================================
// CalculeDistance
//	Calcule la distance entre deux corps
// ==================================================================================================
double	CEcoBrownien::CalculeDistance( T_CORPS T1, T_CORPS T2 )
{
	double	DX, DY,DZ ;
	DX	=	T1.x - T2.x ;
	DY	=	T1.y - T2.y ;
	DZ	=	T1.z - T2.z ;
	
	return sqrt( (DX*DX) + (DY*DY) + (DZ*DZ)) ;
}

// ==================================================================================================
// Calcule l'attraction ou la repulsion entre deux particules
//	Regles :	Si le nombre de charges est impaire, toutes les particules s'attirent
//				Sinon, deux particules de meme charge se repoussent, les autres s'attirent
// ==================================================================================================
double CEcoBrownien::Attirance( double Attraction, int Couleur1, int Couleur2 )
{
	if ( NombreCouleurs & 0x001 )
		return Attraction ;

	if ( Couleur1 == Couleur2 )
		return -Attraction ;                                 
	else
		return Attraction ;
}

// ============================================================================
// Accelere
// Calcule l'acceleration gravitationnelle reciproque qui s'exerce entre deux
// corps
// ENTREES	:	Les deux corps
// SORTIES	:	Les deux corps avec leurs vitesse modifiees
// ============================================================================
void	CEcoBrownien::Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 )
{
	// ================================================== Calcul de la distance
	const double DistanceX		=   (double)(pCorps2->x - pCorps1->x) ;
	const double DistanceY		=   (double)(pCorps2->y - pCorps1->y) ;
	const double DistanceZ		=   (double)(pCorps2->z - pCorps1->z) ;

	const double Distance		=	sqrt((DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + ( DistanceZ * DistanceZ ));
	const double DistanceCube	=	Distance * Distance * Distance ;

	if ( DistanceCube	!= 0 )
		{
		const double	x1	=	CoeffAttraction * DistanceX / DistanceCube ;
		const double	y1	=	CoeffAttraction * DistanceY / DistanceCube ;
		const double	z1	=	CoeffAttraction * DistanceZ / DistanceCube ;
		const double	x2	=	CoeffAttraction * DistanceX / DistanceCube ;
		const double	y2	=	CoeffAttraction * DistanceY / DistanceCube ;
		const double	z2	=	CoeffAttraction * DistanceZ / DistanceCube ;

		pCorps1->vx	+=	Attirance( x1, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;
		pCorps2->vx	-=	Attirance( x2, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;
		
		pCorps1->vy	+=	Attirance( y1, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;
		pCorps2->vy	-=	Attirance( y2, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;

		pCorps1->vz	+=	Attirance( z1, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;
		pCorps2->vz	-=	Attirance( z2, pCorps1->Couleur, pCorps2->Couleur ) * DeltaT ;
		}
}

// ============================================================================
// Affiche
// ============================================================================
void	CEcoBrownien::Affiche( T_CORPS	*	pCorps )
{
	const int Indice	=	pCorps->IndiceImage ;
	const int L	=	pBitmaps[pCorps->Couleur][Indice]->GetWidth() ;
	const int H =	pBitmaps[pCorps->Couleur][Indice]->GetHeight() ;

	CRect R ;
	R.left	=	(int)pCorps->x  ;
	R.top	=	(int)pCorps->y  ;

	R.right	=	R.left + L ;
	R.bottom=	R.top + H ;

	if ( (R.left >= 0) && (R.right < Largeur) && (R.top >= 0) && (R.bottom < Hauteur) )
		{
		int	DecalageX, DecalageY ;

		Affichage.LimiteRect(R, &DecalageX, &DecalageY ) ;
		pBitmaps[pCorps->Couleur][Indice]->CopyBits( pDCIntermediaire,
													 R.left, R.top,	L, H,
													 DecalageX, DecalageY,
													 PALETTEINDEX(0)) ;
		Affichage.Ajoute( R ) ;
		}
}

// ============================================================================
// Efface, on se contente juste de marquer la zone a reafficher
// ============================================================================
void	CEcoBrownien::Efface( T_CORPS	*	pCorps )
{
	CRect R ;
	const int L	=	pBitmaps[pCorps->Couleur][pCorps->IndiceImage]->GetWidth() ;
	const int H	=	pBitmaps[pCorps->Couleur][pCorps->IndiceImage]->GetHeight() ;

	R.left	=	max( 0, (int)pCorps->x ) ;
	R.top	=	max( 0, (int)pCorps->y ) ;
	R.right	=	min( Largeur-1, R.left + L ) ;
	R.bottom=	min( Hauteur-1, R.top + H ) ;

	Affichage.LimiteRect( R ) ;

	PatBlt( pDCIntermediaire->GetHDC(), R.left, R.top, R.right-R.left, R.bottom-R.top, BLACKNESS ) ;

	Affichage.Ajoute( R ) ;
}

// ============================================================================
// CalculeAcceleration
// ============================================================================
void	CEcoBrownien::CalculAccelerations( void )
{
	int	i, j ;

	// Attraction normale entre les corps
	for ( i = 0; i < NbCorps; i++)
		for ( j = i + 1; j < NbCorps; j++ )
			Accelere( &Corps[i], &Corps[j] ) ;
}

int	CompareCorps( const void * elem1, const void * elem2 )
{
	CEcoBrownien::T_CORPS*	pCorps1 ;
	CEcoBrownien::T_CORPS*	pCorps2 ;
	pCorps1		=	(CEcoBrownien::T_CORPS*)elem1 ;
	pCorps2		=	(CEcoBrownien::T_CORPS*)elem2 ;

	return (int)(pCorps1->z - pCorps2->z) ;
}

void CEcoBrownien::Animation( CDC&	Dc )
{
	int	i	;
	DWORD	TempsCourant ;

	Affichage.Vide() ;

	// Calcul des interactions qu'exercent les corps les uns sur les autres
	CalculAccelerations() ;
	
	// Pour garder une vitesse constante quelle que soit le temps mis pour les calculs
	TempsCourant	=	GetCurrentTime ();
	DeltaT			=	TempsCourant-DernierTemps;
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
		
	Affichage.BitBlt( Dc, *pDCIntermediaire->GetDC()) ;
}


void	CEcoBrownien::ConfSpin( HWND hWnd, UINT Id, UINT IdEdit, int	Valeur, int Min, int Max )
{
	SendDlgItemMessage( hWnd, Id, UDM_SETBUDDY, (WPARAM)GetDlgItem( hWnd, IdEdit ), 0 ) ;
	SendDlgItemMessage( hWnd, Id, UDM_SETRANGE, 0, (LPARAM)MAKELONG( Max, Min ) ) ;
	SendDlgItemMessage( hWnd, Id, UDM_SETPOS, 0, (LPARAM)MAKELONG( Valeur, 0 ) ) ;

	SetDlgItemInt	  ( hWnd, IdEdit, Valeur, TRUE ) ;
}

BOOL CEcoBrownien::PreprocessConfigDlgMessage( HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam )
	{
		switch( Message )
		{
		case WM_INITDIALOG :
			{
			LitPreferences() ;
			CheckDlgButton( hDlg, IDC_PRIORITE, HautePriorite ) ;

			NbCorps	=	min( NbCorps, NB_MAX_CORPS ) ;

			ConfSpin( hDlg, IDC_BUDDY1, IDC_NB_PARTICULES, NbCorps, 2, NB_MAX_CORPS ) ;
			ConfSpin( hDlg, IDC_BUDDY2, IDC_NB_CHARGES, NombreCouleurs, 1, NB_MAX_COULEURS ) ;
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
					NombreCouleurs	=	min( NB_MAX_COULEURS, max(1, NombreCouleurs )) ;

					EcritPreferences() ;
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

void CEcoBrownien::Preferences()
{
	NoircirEcran	=	TRUE ;
	
	Preference( "Haute Priorite",	HautePriorite ) ;
	Preference( "NbCorps",	NbCorps ) ;
	Preference( "Couleurs", NombreCouleurs ) ;

	NbCorps	=	max( 2, min( NB_MAX_CORPS, NbCorps )) ;
	NombreCouleurs= max( 1, min( NB_MAX_COULEURS, NombreCouleurs )) ;

	if ( ! ShareWare())
		{
		Preference(	"CoeffAttraction",		CoeffAttraction ) ;
		Preference(	"CoeffRebond",			CoeffRebond ) ;
		Preference(	"DeltaTMax",			DeltaTMax		) ;
		}
}

void CEcoBrownien::Configuration( CPropertySheet * pPropSheet )
	{
	pPropSheet->AddPage( new CPage1 ) ;
	pPropSheet->AddPage( new CPage2 ) ;

	pPropSheet->SetTitle( "Configuration" ) ;

	}