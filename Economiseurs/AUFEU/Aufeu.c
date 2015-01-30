///////////////////////////////////////////////////////////////////////////////
// GOUTTES.C
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <commctrl.h>
#include <math.h>
#include "resource.h"
#include "..\specif.h"

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
#define	LARGEUR		80
#define HAUTEUR		150

#define LARGEUR_BITMAP	(LARGEUR*LargeurPoint)
#define HAUTEUR_BITMAP	(HAUTEUR*HauteurPoint)
const	char *	SPECIF_NomEconomiseur	=	"Au Feu V2 !" ;
const	char *	SPECIF_ValeurEnregistre =	"500° Au feu" ;


///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC		hDCReference=0 ;
HBITMAP hOldReference = 0 ;
HDC		hDCIntermediaire=0 ;
HBITMAP hOldIntermediaire = 0 ;
HDC		hDCMemo ;
HBITMAP	hOldMemo ;
BYTE 	Valeurs[HAUTEUR][LARGEUR] ;
int		HauteurReference ;

int		Refroidissement	=	8 ;
int		Dispersion		=	2 ;
int		LargeurFeu		=	LARGEUR/2 ;
int		xFeu, yFeu ;
int		LargeurPoint	=	1 ;
int		HauteurPoint	=	1 ;
int		Propage 		=	2 ;
int		dx ;
int		dy ;
int		Convection		=	5 ;
int		SensFeu			=	1 ;
int		Chaos			=	5 ;

/////////////////////////////////////////////////////////////////////////////
// Charger la bitmap qui sert de reference pour les couleurs de la flamme
/////////////////////////////////////////////////////////////////////////////
void	ChargeReference()
{
	HBITMAP	hBitmap ;
	BITMAP	sBitmap ;
	int		Base ;
	HDC		hDC ;

	hDC	=	CreateIC( "display", 0,0,0 ) ;

	if ( (int)pow( 2, GetDeviceCaps(hDC, BITSPIXEL )) * GetDeviceCaps( hDC, PLANES ) >= 65000 )
		Base	=	IDB_REFERENCE ;
	else
		Base	=	IDB_REFERENCE_16 ;
	
	DeleteDC( hDC ) ;


	if ( hOldReference && hDCReference )
		{
		DeleteObject( SelectObject( hDCReference, hOldReference )) ;
		}
	else
		hDCReference			=	FastCreateDC() ;

	hBitmap					=	LoadBitmap( hMainInstance,
											MAKEINTRESOURCE( Base + Alea( 0, 2 ) )) ;

	GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;
	HauteurReference		=	sBitmap.bmHeight ;
	hOldReference			=	SelectObject( hDCReference, hBitmap ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Fait une interpolation d'une valeur comprise dans un intervalle vers un
// autre
///////////////////////////////////////////////////////////////////////////////
int	__inline ChangeIntervalle( int Valeur, int DepMin, int DepMax, int DestMin, int DestMax )
{
	Valeur	-=	DepMin ;
	Valeur	=	Valeur * (DestMax-DestMin) /  (DepMax-DepMin ) ;
	Valeur	+=	DestMin ;

	return Valeur ;
}

void	ChaleurInitiale( int y, int Largeur )
{
	int	i	;
	for ( i =	0; i < (LARGEUR-Largeur)/2; i++)
		Valeurs[y][i]	=	0 ;

	for ( i	=	(LARGEUR-Largeur) / 2; i < (LARGEUR+Largeur) / 2; i++)
		{
		int	Distance	=	(LARGEUR/2)-i ;
		if ( Distance < 0)
			Distance	=	-Distance ;

		Valeurs[y][i]	=	(BYTE)ChangeIntervalle( Distance, Largeur/2, 0, HauteurReference/2, HauteurReference-HauteurPoint ) ;
		}

	for ( i =	(LARGEUR+Largeur)/2; i < LARGEUR; i++)
		Valeurs[y][i]	=	0 ;

}

/////////////////////////////////////////////////////////////////////////////
// LargeurDuFeu
/////////////////////////////////////////////////////////////////////////////
void	__inline LargeurDuFeu()
{
	ChaleurInitiale( HAUTEUR-4, LargeurFeu ) ;
	ChaleurInitiale( HAUTEUR-3, LargeurFeu*4/5 ) ;
	ChaleurInitiale( HAUTEUR-2, LargeurFeu*3/4 ) ;
	ChaleurInitiale( HAUTEUR-1, LargeurFeu/2 ) ;
	
	if ( UnSur( 3 ))
		LargeurFeu	+=	SensFeu ;

	if ( LargeurFeu	<= Dispersion*2 )
		{
		ChargeReference() ;

		LargeurFeu	=	Dispersion*2 +1   ;
		SensFeu		=	1 ;
		}

	if ( LargeurFeu > LARGEUR-Dispersion)
		{
		LargeurFeu	=	LARGEUR-Dispersion ;
		SensFeu	=	-1 ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_InitEconomiseur( HWND hWnd )
{
	NoircirEcran	=	FALSE ;

	if ( Largeur < LARGEUR * LargeurPoint || Hauteur < HAUTEUR * HauteurPoint )
		{
		LargeurPoint	=	1 ;
		HauteurPoint	=	1 ;
		}

	ChargeReference() ;

	hDCMemo				=	FastCreateDC( ) ;
	hOldMemo			=	SelectObject( hDCMemo,MemoEcran( Largeur, Hauteur )) ;

	hDCIntermediaire	=	FastCreateDC( ) ;
	hOldIntermediaire	=	SelectObject( hDCIntermediaire,
										  FastCreateBitmap(	hDCIntermediaire,
										  					LARGEUR_BITMAP+4,
										  					HAUTEUR_BITMAP+8)) ;

	memset( Valeurs, 0, sizeof( Valeurs )) ;

	SetTimer( hWnd, 1, 60, NULL ) ;

	LargeurFeu	=	Alea( LARGEUR/4, LARGEUR/3 ) ;
	LargeurDuFeu() ;

	xFeu	=	(Largeur-LARGEUR_BITMAP)/2 ;
	yFeu	=	min( (Hauteur-HAUTEUR_BITMAP)/2, Hauteur-HAUTEUR_BITMAP);
	dx	=	0 ;
	dy	=	-1 ;
	SensFeu	=	1 ;
}

void	_inline BrulePoint( int x, int y )
{
	BYTE	Val ;
	int		xRef ;
	int		yRef ;

	// Ce qui se trouve en dessous, plutot proche du centre
	xRef	=	Alea( -(Dispersion/2), Dispersion ) ;
	if ( x <= LARGEUR/2)
		xRef	=	x-xRef ;
	else
		xRef	=	x+xRef ;

	// Vitesse de propagation
	if ( y > 0  && UnSur(Chaos) )
		yRef	=	y - 1 ;
	else
		{
		yRef	=	y + Alea( 1, Propage ) ;
		if ( yRef > HAUTEUR-1 )
			yRef	=	HAUTEUR-1 ;
		}
	

	Val	=	Valeurs[yRef][xRef] ;
	
	if ( Val > 0 )
		{
		// La temperature diminue a mesure qu'on monte
		if ( UnSur( Refroidissement ))
			Valeurs[y][x]	=	Val - 1 ;
		else
			Valeurs[y][x]	=	Val ;
		}
	else
		Valeurs[y][x]	=	Val ;

	if ( Valeurs[y][x] )	// Les parties les plus froides sont considerees transparentes
			FastBitBlt( hDCIntermediaire,
						x*LargeurPoint+2, y*HauteurPoint+2, LargeurPoint, HauteurPoint,
						hDCReference, 0,
						Valeurs[y][x] ) ;
	else
		// Simulation de la convection de l'air au dessus du feu
		if ( UnSur(Convection ) &&
			 (x > (LARGEUR-LargeurFeu)/2) && (x < (LARGEUR+LargeurFeu)/2) )
			FastBitBlt( hDCIntermediaire,
						x*LargeurPoint+2, y*HauteurPoint+2, LargeurPoint, HauteurPoint,
						hDCMemo,
						xFeu + x * LargeurPoint + 2 + Alea(-1, 1 ),
						yFeu + y * HauteurPoint + 2 + Alea(-1, 1 ) ) ;
			
}

///////////////////////////////////////////////////////////////////////////////
// GenereFlamme
///////////////////////////////////////////////////////////////////////////////
void	_inline GenereFlamme()
{
	int x, y ;

	for ( y = 1; y < HAUTEUR-1; y++)
		for ( x	= Dispersion+1; x < LARGEUR-Dispersion-1; x ++ )
			BrulePoint( x, y ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
DWORD __stdcall SPECIF_Animation( LPVOID lp )
{
	HDC	hDC ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	SetEvent( hEventInitFini ) ;

	hDC	=	GetDC( hWndPrincipale ) ;
	while ( ! Fini )
		{
		HBITMAP	hBitmap ;
		HBITMAP	hOld ;
		BITMAP	sBitmap ;

		hBitmap	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_CENDRE2 )) ;
		GetObject( hBitmap, sizeof( sBitmap ),&sBitmap ) ;
		hOld	=	SelectObject( hDCReference, hBitmap ) ;
		FastStretchBlt( hDCMemo, xFeu + ((LARGEUR-LargeurFeu/2)*LargeurPoint)/2,
								 yFeu + HAUTEUR_BITMAP-HauteurPoint,
					 			LargeurFeu/2*LargeurPoint,
					 			HauteurPoint,
						hDCReference, 0, 0, sBitmap.bmWidth, sBitmap.bmHeight ) ;
		SelectObject( hDCReference, hOld ) ;
		DeleteObject( hBitmap ) ;

		// Etat initial du dc intermediaire
		FastBitBlt( hDCIntermediaire, 0, 0, LARGEUR_BITMAP+4, HAUTEUR_BITMAP+8, hDCMemo, xFeu, yFeu) ;

		
		// Dessin de la flamme
		GenereFlamme() ;
		FastBitBlt( hDC,
					xFeu,
					yFeu, LARGEUR_BITMAP+4, HAUTEUR_BITMAP+4, hDCIntermediaire, 0, 0 ) ;

		// Dessiner des braises sous le feu
		//FastBitBlt( hDCIntermediaire, 0, 0, LARGEUR_BITMAP+4, HAUTEUR_BITMAP+8, hDCMemo, xFeu, yFeu) ;

		LargeurDuFeu() ;

		// Deplacement aleatoire du feu
		if ( UnSur( 3 ))
			{
			if ( UnSur( 30 ))
				{
				do
					{
					dx	=	Alea( -1, 1 ) ;
					dy	=	Alea( -1, 1 ) ;
					}
				while ( ! dx || ! dy ) ;
				}

			if ( xFeu + (LARGEUR-LargeurFeu)*LargeurPoint/2 > Largeur )
				dx	=	-1 ;
			else
			if ( xFeu + (LARGEUR-LargeurFeu)*LargeurPoint/2 < 0 )
				dx	=	1 ;

			if ( yFeu + HAUTEUR_BITMAP > Hauteur )
				dy	=	-1 ;
			else
				if ( yFeu < -HAUTEUR_BITMAP  )
					dy	=	1 ;

			xFeu	+=	dx ;
			yFeu	+=	dy ;
			}
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
	DeleteObject( SelectObject( hDCMemo, hOldMemo)) ;
	DeleteDC( hDCMemo) ;	
	DeleteObject( SelectObject( hDCIntermediaire, hOldIntermediaire)) ;
	DeleteDC( hDCIntermediaire) ;	
	DeleteObject( SelectObject( hDCReference, hOldReference)) ;
	DeleteDC( hDCReference) ;	
}
 
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	BitBlt( hDC, 0, 0, Largeur, Hauteur, hDCMemo, 0, 0, SRCCOPY ) ;
}

void	SPECIF_LirePreferences(void)
{
	if ( VerifVersion() )
		{
		Dispersion		=	LitEntier( "Dispersion", Dispersion ) ;
		Refroidissement	=	LitEntier( "Refroidissement", Refroidissement );
		LargeurPoint	=	LitEntier( "LargeurPoint", LargeurPoint ) ;
		HauteurPoint	=	LitEntier( "HauteurPoint", HauteurPoint ) ;
		Convection		=	LitEntier( "Convection", Convection ) ;
		Chaos			=	LitEntier( "Chaos", Chaos ) ;
		}
}

void	SPECIF_EcrirePreferences(void)
{
	if ( VerifVersion() )
		{
		EcritEntier( "Dispersion", Dispersion ) ;
		EcritEntier( "Refroidissement", Refroidissement );
		EcritEntier( "LargeurPoint", LargeurPoint ) ;
		EcritEntier( "HauteurPoint", HauteurPoint ) ;
		EcritEntier( "Convection", Convection);
		EcritEntier( "Chaos", Chaos);
		}
}

BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam , LPARAM lParam )
{ 
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			SPECIF_LirePreferences() ;
			if ( ! VerifVersion())
				{
				EnableWindow( GetDlgItem( hDlg, IDC_DISPERSION ), FALSE ) ;
				EnableWindow( GetDlgItem( hDlg, IDC_SPIN_DISPERSION ), FALSE ) ;
				EnableWindow( GetDlgItem( hDlg, IDC_REFROID), FALSE ) ;
				EnableWindow( GetDlgItem( hDlg, IDC_SPIN_REFROID ), FALSE ) ;
				EnableWindow( GetDlgItem( hDlg, IDC_CONVECTION ), FALSE ) ;
				EnableWindow( GetDlgItem( hDlg, IDC_SPIN_CONVECTION ), FALSE ) ;
				}
			else
				{
				SendDlgItemMessage( hDlg, IDC_SPIN_DISPERSION, UDM_SETRANGE, 0, (LPARAM)MAKELONG( 2, 8) ) ;
				SendDlgItemMessage( hDlg, IDC_SPIN_DISPERSION, UDM_SETPOS, 0, (LPARAM)MAKELONG( Dispersion, 0 ) ) ;
				
				SendDlgItemMessage( hDlg, IDC_SPIN_REFROID, UDM_SETRANGE, 0, (LPARAM)MAKELONG( 2, 300) ) ;
				SendDlgItemMessage( hDlg, IDC_SPIN_REFROID, UDM_SETPOS, 0, (LPARAM)MAKELONG( Refroidissement, 0 ) ) ;
				
				SendDlgItemMessage( hDlg, IDC_SPIN_CONVECTION, UDM_SETRANGE, 0, (LPARAM)MAKELONG( 2, 300) ) ;
				SendDlgItemMessage( hDlg, IDC_SPIN_CONVECTION, UDM_SETPOS, 0, (LPARAM)MAKELONG( Convection, 0 ) ) ;

				SendDlgItemMessage( hDlg, IDC_SPIN_CHAOS, UDM_SETRANGE, 0, (LPARAM)MAKELONG( 2, 20) ) ;
				SendDlgItemMessage( hDlg, IDC_SPIN_CHAOS, UDM_SETPOS, 0, (LPARAM)MAKELONG( Chaos, 0 ) ) ;
				}
			return FALSE ; 	// Pour centrer la fenetre
			}
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					if (VerifVersion())
						{
						Dispersion		=	SendDlgItemMessage( hDlg, IDC_SPIN_DISPERSION, UDM_GETPOS, 0, 0 ) ;
						Refroidissement	=	SendDlgItemMessage( hDlg, IDC_SPIN_REFROID, UDM_GETPOS, 0, 0 ) ;
						Convection		=	SendDlgItemMessage( hDlg, IDC_SPIN_CONVECTION, UDM_GETPOS, 0, 0 ) ;
						Chaos			=	SendDlgItemMessage( hDlg, IDC_SPIN_CHAOS, UDM_GETPOS, 0, 0 ) ;
						}

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
