///////////////////////////////////////////////////////////////////////////////
// ABEILLES.C
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <commctrl.h>
#include <math.h>
#include "resource.h"
#include "..\specif.h"

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
#define	NB_ABEILLES		4000
#define TAILLE_ABEILLES	2

const	char *	SPECIF_NomEconomiseur	=	"L'Essaim" ;
const	char *	SPECIF_ValeurEnregistre =	"FlvlD" ;

const	COLORREF	CouleursSaturee[]	=	{
											RGB( 255, 017, 017),
											RGB( 255, 113, 017),
											RGB( 255, 207, 017),
											RGB( 207, 255, 017),
											RGB( 113, 255, 017),
											RGB( 017, 255, 017),
											RGB( 017, 255, 113),
											RGB( 017, 255, 207),
											RGB( 017, 207, 255),
											RGB( 017, 113, 255),
											RGB( 017, 017, 255),
											RGB( 113, 017, 255),
											RGB( 207, 017, 255),
											RGB( 255, 017, 207),
											RGB( 224, 017, 113),
											RGB( 255, 017,  23)
											}; 

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////
typedef	struct
	{
	double	x ;
	double	y ;
	double	vx ;
	double	vy ;
	}
	T_ABEILLE ;

///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC			hDCMemo ;
HBITMAP		hOldMemo ;

POINT		PtCentral ;
int			dx, dy ;
T_ABEILLE	Abeilles[NB_ABEILLES] ;
int			NbMaxAbeilles	=	400 ;
int			NbAbeilles 		= 300 ;
int			CoeffAleatoire =	20;
double		CoeffAttraction	=	0.7 ;
double		CoeffVitesse	=	3.5 ;

HDC			hMemDC ;
HBITMAP		hBitmapGauche ;
HBITMAP		hBitmapDroite ;
double		PhaseCourante ;
double		LimiteVitesse = 10.0 ;
int	x ;

COLORREF	Couleur ;

void	FluctuationCouleur()
{
	static	int Indice	=	0 ;
	if ( Indice < sizeof( CouleursSaturee) / sizeof( CouleursSaturee[0] )-1)
		Indice ++ ;
	else
		Indice	=	0 ;

	Couleur	=	CouleursSaturee[Indice] ;
}
///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_InitEconomiseur( HWND hWnd )
{
	int	i ;
	NbAbeilles		=	NbMaxAbeilles ;

	LimiteVitesse	=	CoeffAttraction * 4.0 ;
	
	hDCMemo		=	CreateCompatibleDC( NULL ) ;
	hOldMemo	=	SelectObject( hDCMemo, MemoEcran( Largeur, Hauteur )) ;
	
	PtCentral.x	=	Alea( 0, Largeur );
	PtCentral.y	=	Alea( 0, Hauteur ) ;
	dx	=	1 ;
	dy	=	1 ;

	for ( i = 0; i < NbAbeilles; i++)
		{
		Abeilles[i].x	=	Alea( 0, Largeur ) ;
		Abeilles[i].y	=	Alea( 0, Hauteur ) ;
		Abeilles[i].vx	=	0 ;
		Abeilles[i].vy	=	0 ;
		}
	
	hMemDC			=	CreateCompatibleDC( hDCMemo ) ;
	hBitmapGauche	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_GAUCHE )) ;
	hBitmapDroite	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_DROITE )) ;
	PhaseCourante	=	0 ;

	Couleur	=	RGB( Alea(0, 255), Alea(0, 255), Alea(0, 255));
}

__inline void AccelereAbeille( T_ABEILLE * pAbeille )
	{
	double	DistanceCarre, DistanceX, DistanceY ;
	double	Distance	;

	DistanceX	=   (PtCentral.x - pAbeille->x)  ;
	DistanceY	=   (PtCentral.y - pAbeille->y)  ;

	DistanceCarre	=	DistanceX*DistanceX + DistanceY*DistanceY ;

	if ( DistanceCarre != 0 )
		{		
		Distance	=	sqrt( DistanceCarre) ;
	
		// ======================= Repartition des vecteurs d'attraction sur x et y
		pAbeille->vx	+=	( CoeffAttraction * DistanceX ) / Distance  + (double)Alea( -CoeffAleatoire, CoeffAleatoire)/10.0 ;
		pAbeille->vy	+=	( CoeffAttraction * DistanceY ) / Distance  + (double)Alea( -CoeffAleatoire, CoeffAleatoire)/10.0;

		if ( pAbeille->vx > LimiteVitesse )
			pAbeille->vx	=	LimiteVitesse ;
		if ( pAbeille->vx < -LimiteVitesse )
			pAbeille->vx	=	-LimiteVitesse ;

		if ( pAbeille->vy > LimiteVitesse )
			pAbeille->vy	=	LimiteVitesse ;
		if ( pAbeille->vy < -LimiteVitesse )
			pAbeille->vy	=	-LimiteVitesse  ;
		}
	}


///////////////////////////////////////////////////////////////////////////////
// Efface une des abeilles
///////////////////////////////////////////////////////////////////////////////
__inline void	EffaceAbeille( HDC hDC, T_ABEILLE *	pAbeille )
	{
	FastBitBlt( hDC, (int)pAbeille->x,(int)pAbeille->y,
				TAILLE_ABEILLES, TAILLE_ABEILLES,  hDCMemo,
				(int)pAbeille->x,(int)pAbeille->y ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// Affiche une abeille
///////////////////////////////////////////////////////////////////////////////
__inline void	AfficheAbeille( HDC hDC, T_ABEILLE * pAbeille )
	{
	PatBlt( hDC, (int)pAbeille->x,(int)pAbeille->y,
			TAILLE_ABEILLES, TAILLE_ABEILLES, PATCOPY ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
DWORD _stdcall SPECIF_Animation( LPVOID p )
{
	int	i	;
	HBITMAP	hOld ;
	HBRUSH	hOldBr ;
	HDC		hDC ;
	
	SPECIF_LirePreferences() ;
	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	SetEvent( hEventInitFini ) ;

	hDC	=	GetDC( hWndPrincipale ) ;
	
	while ( ! Fini )
		{
		hOldBr	=	SelectObject( hDC, CreateSolidBrush( Couleur )) ;
		FluctuationCouleur() ;

		for ( i = 0; i < NbAbeilles; i++)
			{
			EffaceAbeille( hDC, &Abeilles[i] ) ;

			AccelereAbeille( &Abeilles[i] ) ;

			//Avancer
			Abeilles[i].x	+=	Abeilles[i].vx ;
			Abeilles[i].y	+=	Abeilles[i].vy ;

			AfficheAbeille( hDC, &Abeilles[i] ) ;
			}
		
		DeleteObject( SelectObject( hDC, hOldBr ));
		
		// Effacer
		PatBlt( hDC, PtCentral.x, PtCentral.y, 16, 16, BLACKNESS ) ;

		// Deplacer le point d'attraction
		x = (int)(dx * CoeffVitesse) + Alea( -1, +1 ) ;
		PtCentral.x	+=	x ;
		PtCentral.y	+=	(int)(dy * CoeffVitesse) + Alea( -1, +1 ) ;

		PhaseCourante	+= 0.5 ;
		if ( PhaseCourante >= 4.0 )
			PhaseCourante = 0.0 ;
		
		if ( x > 0)
			hOld	=	SelectObject( hMemDC, hBitmapDroite ) ;
		else
			hOld	=	SelectObject( hMemDC, hBitmapGauche ) ;

		BitBlt( hDC, PtCentral.x, PtCentral.y, 16, 16, hMemDC, (int)PhaseCourante*16, 0, SRCPAINT ) ;

		SelectObject( hMemDC, hOld ) ;


		///////////////////////////////////////////////////////////////////////////
		// Gestion du mouvement du point central
		///////////////////////////////////////////////////////////////////////////
		if ( PtCentral.x >= Largeur )
			dx	= -1 ;
		else
			if (PtCentral.x <= 0)
				dx	=	1 ;
			else
				if (UnSur( 50))
					dx	=	-dx ;

		if ( PtCentral.y >= Hauteur )
			dy	= -1 ;
		else
			if (PtCentral.y <= 0)
				dy	=	1 ;
			else
				if ( UnSur( 50 ))
					dy	=	-dy ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;

	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
//	Fin de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_Fin( HWND hWnd )
{
	DeleteObject( SelectObject( hDCMemo, hOldMemo )) ;
	DeleteDC( hDCMemo ) ;	

	DeleteDC( hMemDC ) ;
	DeleteObject( hBitmapGauche ) ;
	DeleteObject( hBitmapDroite ) ;
}
 
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	FastBitBlt( hDC, 0, 0, Largeur, Hauteur, hDCMemo, 0, 0 ) ;
}

void	SPECIF_LirePreferences(void)
{
	NoircirEcran	=	FALSE ;
	CoeffAleatoire	=	LitEntier( "CoeffAleatoire",  CoeffAleatoire ) ;
	CoeffVitesse	=	LitDouble( "CoeffVitesse",  CoeffVitesse ) ;
	CoeffAttraction	=	LitDouble( "CoeffAttraction",  CoeffAttraction ) ;
	NbMaxAbeilles	=	LitEntier( "MaxAbeilles",	NbMaxAbeilles ) ;

	NbMaxAbeilles	=	min( NB_ABEILLES, max( 0, NbMaxAbeilles )) ;
}

void	SPECIF_EcrirePreferences(void)
{
	EcritEntier( "CoeffAleatoire",  CoeffAleatoire ) ;
	EcritDouble( "CoeffVitesse", 	CoeffVitesse ) ;
	EcritDouble( "CoeffAttraction", CoeffAttraction ) ;
	EcritEntier( "MaxAbeilles",	NbMaxAbeilles ) ;
}

static	void	ConfSlider( HWND hWnd, UINT Id, int	Valeur, int Min, int Max )
{
	SendDlgItemMessage( hWnd, Id, TBM_SETRANGE, TRUE, MAKELPARAM( Min, Max )) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETPAGESIZE, TRUE, 10 ) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETLINESIZE, TRUE, 1 ) ;
	SendDlgItemMessage( hWnd, Id, TBM_SETPOS, TRUE, (LPARAM)Valeur ) ;
}

BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam , LPARAM lParam )
{ 
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			SPECIF_LirePreferences() ;
			// Nombre d'abeilles
			ConfSlider( hDlg, IDC_NB_ABEILLES,	NbMaxAbeilles, 0, NB_ABEILLES ) ;
			ConfSlider( hDlg, IDC_ALEATOIRE,	CoeffAleatoire, 0, 30 ) ;
			ConfSlider( hDlg, IDC_VITESSE,		(int)(CoeffVitesse*10), 5, 90 ) ;
			ConfSlider( hDlg, IDC_ATTRACTION,	(int)(CoeffAttraction*100), 10, 450 ) ;

			return FALSE ; 	// Pour centrer la fenetre
			}
			break ;
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					NbMaxAbeilles	=	SendDlgItemMessage( hDlg, IDC_NB_ABEILLES, TBM_GETPOS , 0, 0 ) ;
					CoeffAleatoire	=	SendDlgItemMessage( hDlg, IDC_ALEATOIRE, TBM_GETPOS , 0, 0 ) ;
					CoeffVitesse	=	(double)SendDlgItemMessage( hDlg, IDC_VITESSE, TBM_GETPOS , 0, 0 ) / 10.0 ;
					CoeffAttraction	=	(double)SendDlgItemMessage( hDlg, IDC_ATTRACTION, TBM_GETPOS , 0, 0 ) / 100.0 ;
					SPECIF_EcrirePreferences() ;
					EndDialog( hDlg, IDOK ) ;
					break ;

				default :
					return FALSE ;
				}
			break ;

		default :
			return FALSE ;
		}
	return TRUE ;
}
