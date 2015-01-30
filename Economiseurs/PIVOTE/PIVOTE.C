///////////////////////////////////////////////////////////////////////////////
// PIVOTE.C
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <math.h>
//#include "resource.h"
#include "..\specif.h"

#define PI			3.14159

double	Angle	=	0.0 ;

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
const	char *	SPECIF_NomEconomiseur	=	"Pivote" ;
const	char *	SPECIF_ValeurEnregistre =	"pie qui vote" ;

///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC			hDCMemo = 0 ;
HBITMAP		hOldMemo ;

HDC			hDCIntermediaire ;
HBITMAP		hOldIntermediaire ;

int			NbLignes		=	16;
int			NbColonnes		=	16 ;
double		CoeffDistance	=	1.0 ;
RECT		R ;
int			LargeurMemo, HauteurMemo ;
int	MilieuX		;	
int	MilieuY		;	
int	LargeurCase	;
int	HauteurCase	;

double* pAngles ;

double	CalculeAngle( double x, double y )
	{
	if ( x == 0.0 )
		{
		if ( y > 0 )
			return PI/2 ;
		else
			return -PI/2 ;
		}

	return atan2( y, x ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	InitEconomiseur( HWND hWnd )
{
	int x, y ;

	NoircirEcran	=	TRUE ;

	LargeurMemo	=	Largeur/2 ;
	HauteurMemo	=	Hauteur/2 ;

	MilieuX		=	LargeurMemo / 2 ;
	MilieuY		=	HauteurMemo / 2 ;
	LargeurCase	=	LargeurMemo / NbColonnes;
	HauteurCase	=	HauteurMemo / NbLignes ;


	hDCMemo		=	FastCreateDC(  ) ;
	hOldMemo	=	SelectObject( hDCMemo, MemoEcran( LargeurMemo, HauteurMemo )) ;

	hDCIntermediaire	=	FastCreateDC() ;
	hOldIntermediaire	=	SelectObject( hDCIntermediaire, 
										  CreateCompatibleBitmap( hDCMemo, Largeur, Hauteur )) ;

	SetRect( &R, 0, 0, Largeur, Hauteur ) ;

	pAngles	=	malloc( sizeof( double ) * NbLignes * NbColonnes ) ;

	for ( x	=	0; x < NbColonnes; x ++)
		for ( y	=	0; y < NbLignes; y ++ )
			{
			const double	EcartX		=	(x*LargeurCase)-MilieuX ;
			const double	EcartY		=	(y*HauteurCase)-MilieuY ;
			pAngles[y*NbColonnes + x ]	=	CalculeAngle( EcartX, EcartY ) ;
			}

	SetEvent( hEventInitFini ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
DWORD _stdcall SPECIF_Animation(LPVOID p)
{
	HDC	hDC	 ;

	int			x, y ;
	RECT		RCase ;
	RECT		REfface ;
	int	DecalageX	;	
	int	DecalageY	;
	
	SPECIF_LirePreferences() ;
	InitEconomiseur(hWndPrincipale) ;
	
	DecalageX	=	Largeur/2 - MilieuX ;
	DecalageY	=	Hauteur/2 - MilieuY ;
	
	hDC	=	GetDC( hWndPrincipale ) ;
	
	while ( ! Fini )
		{
		REfface	=	R ;

		SetRectEmpty( &R ) ;
		PatBlt( hDCIntermediaire,
				REfface.left, REfface.top,
				REfface.right-REfface.left,
				REfface.bottom-REfface.top,
				BLACKNESS ) ;

		for ( x	=	0; x < NbColonnes; x ++)
			for ( y	=	0; y < NbLignes; y ++ )
				{
				const double	EcartX		=	(x*LargeurCase)-MilieuX ;
				const double	EcartY		=	(y*HauteurCase)-MilieuY ;
				const double	AngleCase	=	pAngles[y*NbColonnes + x ] + Angle ;
				const double	Distance	=	sqrt( EcartX * EcartX + EcartY * EcartY ) ;

				const int		PosX	=	MilieuX + (int)(Distance * cos(AngleCase) * CoeffDistance ) ;
				const int		PosY	=	MilieuY + (int)(Distance * sin(AngleCase) * CoeffDistance ) ;

				FastBitBlt( hDCIntermediaire, DecalageX + PosX, DecalageY + PosY, LargeurCase+1, HauteurCase+1,
							hDCMemo, x * LargeurCase, y * HauteurCase ) ;

				SetRect( &RCase, PosX, PosY, PosX + LargeurCase, PosY + HauteurCase ) ;
				OffsetRect( &RCase, DecalageX, DecalageY ) ;
				UnionRect( &R, &R, &RCase ) ;
				}

		UnionRect( &R, &R, &REfface ) ;

		FastBitBlt( hDC,
					R.left, R.top,
					R.right-R.left,
					R.bottom-R.top,
					hDCIntermediaire,
					R.left, R.top ) ;
	
		Angle += 0.05 ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;
	SPECIF_Fin( hWndPrincipale ) ;
	return 0 ;
}
	
///////////////////////////////////////////////////////////////////////////////
//	Fin de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_Fin( HWND hWnd )
{
	DeleteObject( SelectObject( hDCMemo, hOldMemo )) ;
	DeleteDC( hDCMemo ) ;	

	DeleteObject( SelectObject( hDCIntermediaire, hOldIntermediaire )) ;
	DeleteDC( hDCIntermediaire ) ;

	free( pAngles ) ;
}
 
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
}

void	SPECIF_LirePreferences(void)
{
	NbLignes	=	LitEntier( "NbLignes", NbLignes ) ;
	NbColonnes	=	LitEntier( "NbColonnes", NbColonnes ) ;
	CoeffDistance=	LitDouble( "Coeff Distance", CoeffDistance ) ;
}

void	SPECIF_EcrirePreferences(void)
{
	EcritEntier( "NbLignes", NbLignes ) ;
	EcritEntier( "NbColonnes", NbColonnes ) ;
	EcritDouble( "Coeff Distance", CoeffDistance ) ;
}

BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam , LPARAM lParam )
{ 
	switch( Message )
		{
		case WM_INITDIALOG :
			return FALSE ; 	// Pour centrer la fenetre
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
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
