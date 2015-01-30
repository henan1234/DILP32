/////////////////////////////////////////////
//////////////////////////////////
// GOUTTES.C
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <commctrl.h>
#include <math.h>
#include "resource.h"
#include "..\specif.h"
#include <wing.h>

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
const	char *	SPECIF_NomEconomiseur	=	"Incendie" ;
const	char *	SPECIF_ValeurEnregistre =	"500° Au feu" ;

#define HAUTEUR_MAX_FLAMME		70

///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC		hDCReference=0 ;
HBITMAP hOldReference = 0 ;
HDC		hDCIntermediaire=0 ;
HBITMAP hOldIntermediaire = 0 ;
HDC		hDCMemo ;
HBITMAP	hOldMemo ;

typedef	BYTE*	T_LIGNE ;
T_LIGNE*	Valeurs ;
int		HauteurReference ;

int		LargeurTableau, HauteurTableau ;

int		Refroidissement	=	8 ;
int		Dispersion		=	3 ;
int		LargeurPoint	=	1 ;
int		HauteurPoint	=	1 ;
int		Propage 		=	2 ;
int		Convection		=	10 ;
POINT	Pt1, Pt2 ;
int		ProgressTemp	;
int		TempCourant ;
HDC		hDCDest, hDCSource ;
/////////////////////////////////////////////////////////////////////////////
// Charger la bitmap qui sert de reference pour les couleurs de la flamme
/////////////////////////////////////////////////////////////////////////////
void	ChargeReference()
{
	HBITMAP	hBitmap ;
	BITMAP	sBitmap ;

	if ( hOldReference && hDCReference )
		DeleteObject( SelectObject( hDCReference, hOldReference )) ;
	else
		hDCReference			=	WinGCreateDC() ;

	hBitmap					=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_REFERENCE )) ;
	GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;
	HauteurReference		=	sBitmap.bmHeight ;

	hOldReference			=	SelectObject( hDCReference, hBitmap ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Fait une interpolation d'une valeur comprise dans un intervalle vers un
// autre
///////////////////////////////////////////////////////////////////////////////
int		ChangeIntervalle( int Valeur, int DepMin, int DepMax, int DestMin, int DestMax )
{
	Valeur	-=	DepMin ;
	Valeur	=	Valeur * (DestMax-DestMin) /  (DepMax-DepMin ) ;
	Valeur	+=	DestMin ;

	return Valeur ;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_InitEconomiseur( HWND hWnd )
{
	int	i ;
	HautePriorite	=	TRUE ;
	NoircirEcran	=	FALSE ;

	LargeurTableau	=	(Largeur / LargeurPoint ) + 1;
	HauteurTableau	=	(Hauteur / HauteurPoint ) + 1;

	// Allocation du tableau de valeurs
	Valeurs	=	(T_LIGNE*)calloc( HauteurTableau, sizeof( T_LIGNE*)) ;
	for ( i = 0; i < HauteurTableau; i++)
		{
		Valeurs[i]	=	(BYTE*)calloc( LargeurTableau, sizeof(BYTE )) ;
		memset( Valeurs[i], 0, LargeurTableau*sizeof( BYTE )) ;
		}

	ChargeReference() ;

	hDCMemo				=	CreateCompatibleDC( NULL ) ;
	hOldMemo			=	SelectObject( hDCMemo,MemoEcran( Largeur, Hauteur )) ;

	hDCIntermediaire	=	CreateCompatibleDC( hDCReference ) ;
	hOldIntermediaire	=	SelectObject( hDCIntermediaire,
										  MemoEcran( Largeur, Hauteur )) ;

	Pt1.x	=	LargeurTableau - 10;
	Pt1.y	=	HauteurTableau- 1 ;
	Pt2.x	=	LargeurTableau - 1 ;
	Pt2.y	=	HauteurTableau - 10 ;

	SetTimer( hWnd, 1, 50, NULL ) ;
}

void	_inline BrulePoint( int x, int y )
{
	BYTE	Val ;
	int		xRef ;
	int		yRef ;

	xRef	=	Alea( -Dispersion, Dispersion ) ;
		
	// Vitesse de propagation
	if ( yRef < HauteurTableau-Propage )
		yRef	=	y + Alea( 1, Propage ) ;
	else
		yRef	=	y+1 ;
	

	Val	=	Valeurs[yRef][x+xRef] ;

	if ( Val == 0xFF )
		return ;
	
	if ( Val > 0 )
		Valeurs[y][x]	=	Val - 1 ;
	else
		Valeurs[y][x]	=	Val ;

	if ( Valeurs[y][x] > 0 )	// Les parties les plus froides sont considerees transparentes
			WinGBitBlt( hDCIntermediaire,
						x*LargeurPoint+2, y*HauteurPoint+2, LargeurPoint, HauteurPoint,
						hDCReference, 0,
						Valeurs[y][x] ) ;
}



///////////////////////////////////////////////////////////////////////////////
// GenereFlamme
///////////////////////////////////////////////////////////////////////////////
void	GenereFlamme()
{
	int x, y ;

	for ( y = max(0, Pt2.y - HAUTEUR_MAX_FLAMME ); y < Pt1.y-Propage; y++)
	for ( x	=max( 0, Pt1.x-Dispersion) ; x < min( LargeurTableau-Dispersion-1, Pt2.x); x ++ )
		if ( Valeurs[y][x] != 0xFF )
			BrulePoint( x, y ) ;
		else
			break ;
}			

void CALLBACK DDAInitialise( int x, int y, LPARAM lp )
{
	int	i	;
									  
	for ( i = y; i < min( y+5, HauteurTableau); i++ )
		Valeurs[i][x]	=	TempCourant ;

	if ( ! UnSur( 4 ))
		{
		TempCourant	+= ProgressTemp ;

		if ( TempCourant	> HauteurReference - HauteurPoint )
			{
			ProgressTemp	=	-1 ;
			TempCourant	=	HauteurReference - HauteurPoint ;
			}
		if ( TempCourant < 3 )
			{
			ProgressTemp	=	1 ;
			TempCourant	=	3 ;
			}
		}

	for ( i = y+5; i < HauteurTableau; i++)
		{
		Valeurs[i][x]	= 0xFF ;
		PatBlt( hDCIntermediaire, x*LargeurPoint, i*HauteurPoint,
				LargeurPoint, HauteurPoint, BLACKNESS ) ;
		}
}

void Transfert( HDC	hDst, HDC hSrc, int x1, int y1, int x2, y2 )
{
	int HauteurTransfert =	(y1-y2)/ 2 +(HAUTEUR_MAX_FLAMME*HauteurPoint) ;
	int	LargeurTransfert =	(x2-x1) / 2 ;

	WinGBitBlt( hDst, x1, y2 - (HAUTEUR_MAX_FLAMME*HauteurPoint), 
					  LargeurTransfert,
					  HauteurTransfert,
				hSrc,
					x1, y2 - (HAUTEUR_MAX_FLAMME*HauteurPoint)) ; 

	WinGBitBlt( hDst, x1+LargeurTransfert, y2 - (HAUTEUR_MAX_FLAMME*HauteurPoint)-HauteurTransfert, 
					  LargeurTransfert,
					  HauteurTransfert,
				hSrc,
					x1+LargeurTransfert, y-2 HauteurTransfert- (HAUTEUR_MAX_FLAMME*HauteurPoint)) ; 
}

void	CalculeNouvellePosition()
{
	POINT	TPt1, TPt2 ;
	int		TailleRect1, TailleRect2 ;

	TPt1	=	Pt1 ;
	TPt2	=	Pt2 ;

	if ( TPt1.x > 0)
			TPt1.x -- ;
		else
			if ( TPt1.y	> 0 )
				TPt1.y -- ;

	if ( TPt2.y > 0 )
		TPt2.y -- ;
	else
		if ( TPt2.x > 0 )
			TPt2.x -- ;

	TailleRect1	=	( Pt2.x - TPt1.x ) * (Pt2.y - TPt1.y) ;
	TailleRect2	=	( TPt2.x - Pt1.x ) * (TPt2.y - Pt1.y) ;

	if ( TailleRect1 <= TailleRect2 )
		Pt1	=	TPt1 ;
	else
		Pt2	=	TPt2 ;
}

///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
void 	SPECIF_Animation( HDC hDC, UINT NoTimer, LPRECT lpR )
{
	if ( UnSur( 3 ) )
		CalculeNouvellePosition() ;


	if ( Pt2.x <= 0 && Pt1.y <= 0)
		{
		Pt1.x	=	LargeurTableau - 10;
		Pt1.y	=	HauteurTableau- 1 ;
		Pt2.x	=	LargeurTableau - 1 ;
		Pt2.y	=	HauteurTableau - 10 ;

		// Inversion de l'image
		if ( UnSur( 2 ))
			WinGStretchBlt( hDCMemo, 0, 0, Largeur, Hauteur, hDCMemo, 0, Hauteur, Largeur, -Hauteur ) ;
		else
			WinGStretchBlt( hDCMemo, 0, 0, Largeur, Hauteur, hDCMemo, Largeur, 0, -Largeur, -Hauteur ) ;

		WinGBitBlt( hDC, 0, 0, Largeur, Hauteur, hDCMemo, 0, 0 ) ;
		}
		
	Transfert( hDCIntermediaire, hDCMemo,
			  Pt1.x*LargeurPoint, Pt1.y *HauteurPoint,
			  Pt2.x*LargeurPoint, Pt2.y * HauteurPoint ) ;
			  Pt2.y*HauteurPoint
	
	TempCourant	=	HauteurReference - HauteurPoint ;
	ProgressTemp=	-1 ;

	LineDDA( Pt1.x, Pt1.y, Pt2.x, Pt2.y, (LINEDDAPROC)DDAInitialise, 0 ) ;

	// Dessin de la flamme
	GenereFlamme() ;

	Transfert( hDC, hDCIntermediaire,
			  Pt1.x*LargeurPoint, Pt1.y *HauteurPoint,
			  Pt2.x*LargeurPoint, Pt2.y * HauteurPoint ) ;
			  Pt2.y*HauteurPoint
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
	if ( VerifVersion )
		{
		Dispersion		=	LitEntier( "Dispersion", Dispersion ) ;
		Refroidissement	=	LitEntier( "Refroidissement", Refroidissement );
		LargeurPoint	=	LitEntier( "LargeurPoint", LargeurPoint ) ;
		HauteurPoint	=	LitEntier( "HauteurPoint", HauteurPoint ) ;
		Convection		=	LitEntier( "Convection", Convection ) ;
		Propage			=	LitEntier( "Propagation", Propage ) ;
		}
}

void	SPECIF_EcrirePreferences(void)
{
	if ( VerifVersion )
		{
		EcritEntier( "Dispersion", Dispersion ) ;
		EcritEntier( "Refroidissement", Refroidissement );
		EcritEntier( "LargeurPoint", LargeurPoint ) ;
		EcritEntier( "HauteurPoint", HauteurPoint ) ;
		EcritEntier( "Convection", Convection);
		EcritEntier( "Propagation", Propage ) ;
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
						Convection			=	SendDlgItemMessage( hDlg, IDC_SPIN_CONVECTION, UDM_GETPOS, 0, 0 ) ;
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
