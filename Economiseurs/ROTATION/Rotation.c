// Partie specifique de l'economiseur
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <scrnsave.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"
#include "..\specif.h"

// ================================================================= Constantes
#define NB_BITMAPS	100
#define DEG_RAD(x)		((x) * 3.14 * 2.0  / 360.0)
#define SIN(x)				sin( DEG_RAD(x))
#define COS(x)				cos( DEG_RAD(x))
const char *	SPECIF_ValeurEnregistre		=	"Rot%346" ;
const char *	SPECIF_NomEconomiseur		=	"Rotation" ;

// ====================================================================== Types
typedef struct
	{
	HBITMAP	hBitmap ;
	int		Largeur ;
	int		Hauteur ;
	}
	ROTATION;
	
	
int			NbBitmaps = NB_BITMAPS ;
ROTATION	Rotation[NB_BITMAPS] ;
int			RotationCourante = 0 ;
int			CentreX, CentreY ;
int			Dx, Dy ;
int			DivTaille	=	3 ;

RECT		RectPrec ;

// Utiliser pour preparer l'image avant de la transferer a l'ecran
HDC			hTempDC ;
HBITMAP		hOldMemBitmap ;

// ================================================================= Variables

static	void	MemoBitmap( HDC hDCEcran )
{
	HDC	hMemDC ;
	HBITMAP	hOldBitmap ;
	int NoBitmap ;
	int	LargeurRef, HauteurRef ;
	double	Angle ;
	int		LargeurBordure ;
	int		Decalage ; 
	HDC		hRefDC ;
	HBITMAP	hRefBitmap, hOldRef ;

	LargeurRef = Largeur / DivTaille ;
	HauteurRef = Hauteur / DivTaille ;
	
	// Creation de la bitmap de reference
	hRefDC	=	CreateCompatibleDC( hDCEcran ) ;
	hRefBitmap	=	CreateCompatibleBitmap( hDCEcran, LargeurRef, HauteurRef ) ;
	hOldRef	=	SelectBitmap( hRefDC, hRefBitmap ) ;
	
	StretchBlt( hRefDC, 0, 0, LargeurRef, HauteurRef, hDCEcran, 0,0, GetSystemMetrics(SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), SRCCOPY ) ;
	
	hMemDC = CreateCompatibleDC( hDCEcran ) ;
	
	
   for ( NoBitmap = 0; NoBitmap < NbBitmaps; NoBitmap ++ )
   	{
		SetCursor( LoadCursor( hMainInstance, MAKEINTRESOURCE( IDC_CURSOR1 + (NoBitmap%6)))) ;
		// Calcul de la taille
		Angle = 360.0 * NoBitmap / NbBitmaps ;
		
		Rotation[NoBitmap].Hauteur	=	HauteurRef + abs((int)(5.0 * COS(Angle))) ;
		Rotation[NoBitmap].Largeur	=	(int)(LargeurRef * SIN(Angle)) ;
		LargeurBordure				=	abs((int)(90.0 * COS( Angle ))) ;
		Rotation[NoBitmap].hBitmap	=	CreateCompatibleBitmap( hDCEcran, abs(Rotation[NoBitmap].Largeur)+ LargeurBordure, Rotation[NoBitmap].Hauteur ) ;

		hOldBitmap					=	SelectBitmap( hMemDC, Rotation[NoBitmap].hBitmap ) ;
		
		if ( Rotation[NoBitmap].Largeur >= 0 )
			{
			HBRUSH	hOldBrush ;
			
			if ( Angle > 90.0)
				Decalage = LargeurBordure ;
			else
				Decalage = 0 ;
				
			hOldBrush	=	SelectBrush( hMemDC, GetStockObject( GRAY_BRUSH )) ;
			PatBlt( hMemDC, 0, 0, Rotation[NoBitmap].Largeur+LargeurBordure, Rotation[NoBitmap].Hauteur, PATCOPY ) ;
			
			SelectBrush( hMemDC, hOldBrush ) ;
			
			StretchBlt( hMemDC, Decalage, 0, Rotation[NoBitmap].Largeur, Rotation[NoBitmap].Hauteur, 
							hRefDC, 0, 0, LargeurRef, HauteurRef, SRCCOPY ) ;
			}
		else
			{
			HBRUSH	hOldBrush ;
			
			if ( Angle > 270.0)
				Decalage = LargeurBordure ;
			else
				Decalage = 0 ;
			
			Rotation[NoBitmap].Largeur = -Rotation[NoBitmap].Largeur ;
			hOldBrush	=	SelectBrush( hMemDC, GetStockObject( GRAY_BRUSH )) ;
				
			PatBlt( hMemDC, 0, 0, Rotation[NoBitmap].Largeur+LargeurBordure, Rotation[NoBitmap].Hauteur, PATCOPY ) ;
			SelectBrush( hMemDC, hOldBrush ) ;
			
			StretchBlt( hMemDC, Decalage, 0, Rotation[NoBitmap].Largeur, Rotation[NoBitmap].Hauteur, 
							hRefDC, LargeurRef, 0,-LargeurRef, HauteurRef, SRCCOPY ) ;
			}
		
		Rotation[NoBitmap].Largeur += LargeurBordure ;
		
		SelectBitmap( hMemDC, hOldBitmap ) ;
	   }
	
	DeleteDC( hMemDC ) ;
	
	SelectBitmap( hRefDC, hOldRef ) ;
	DeleteBitmap( hRefBitmap ) ;
	DeleteDC( hRefDC ) ;
}

// ==================================================================================================
// ==================================================================================================
void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	HCURSOR	hCurseur ;
	HDC	hDC =	CreateDC("display", 0, 0,0 ) ;
	
	hCurseur	=	SetCursor( LoadCursor( NULL, IDC_APPSTARTING )) ;
	MemoBitmap( hDC ) ;
	SetTimer( hWnd, 1, 50, 0);
	
	RotationCourante = NbBitmaps / 2 ;
	
	CentreX		=	Largeur / 2 ;
	CentreY		=	Hauteur / 2 ;
	
	Dx				=  2 ;
	Dy				=  2 ;
	SetRect( &RectPrec, CentreX - Rotation[RotationCourante+1].Largeur-1, CentreY - Rotation[RotationCourante+1].Hauteur-1,
						CentreX + Rotation[RotationCourante+1].Largeur+1, CentreY + Rotation[RotationCourante+1].Hauteur+1 ) ;
							  

	hTempDC			=	CreateCompatibleDC( hDC ) ;
	hOldMemBitmap	=	SelectObject( hTempDC,
									  CreateCompatibleBitmap( hDC, Largeur, Hauteur )) ;
	PatBlt( hTempDC, 0, 0, Largeur, Hauteur, BLACKNESS ) ;

	DeleteDC( hDC ) ;
	SetCursor( hCurseur ) ;
}  

// ============================================================================
DWORD _stdcall SPECIF_Animation( LPVOID lp  )
// ============================================================================
{  
	HDC			hMemDC ;
	HBITMAP		hOldBitmap ;
	RECT		NouveauRect ;
	RECT		RectTotal ;
	HDC			hDC ;

	SPECIF_InitEconomiseur( hWndPrincipale ) ;

	hDC			=	GetDC( hWndPrincipale ) ;

	SetEvent( hEventInitFini ) ;

		
	while ( ! Fini )
		{
		// Nouvelle rotation
		if ( RotationCourante >= NbBitmaps )
				RotationCourante = 0 ;
		
		if ( CentreX + Dx - Rotation[RotationCourante].Largeur / 2 < 0 )
			Dx = Alea( 1, 5 ) ;
			
		 if ( CentreX + Dx + Rotation[RotationCourante].Largeur / 2 > Largeur )
		  		Dx	=	0 - Alea( 1, 5 ) ;
		
		if ( CentreY + Dy - Rotation[RotationCourante].Hauteur/ 2 < 0 )
			Dy = Alea( 1, 5 ) ;

		if ( (CentreY + Dy + Rotation[RotationCourante].Hauteur / 2) > Hauteur )
			 Dy	=	0 - Alea( 1, 5 ) ;
		
		CentreX += Dx ;
		CentreY += Dy ;
		
		NouveauRect.left	= CentreX	-	Rotation[RotationCourante].Largeur / 2 ;
		NouveauRect.top	= CentreY	-	Rotation[RotationCourante].Hauteur / 2 ;
		NouveauRect.right	=	NouveauRect.left + Rotation[RotationCourante].Largeur ;
		NouveauRect.bottom=	NouveauRect.top + Rotation[RotationCourante].Hauteur ;
		
		// Effacer l'ancienne
		PatBlt( hTempDC, RectPrec.left, RectPrec.top,
				RectPrec.right-RectPrec.left,
				RectPrec.bottom-RectPrec.top,
				BLACKNESS ) ;

		// Afficher la nouvelle rotation
		hMemDC		= CreateCompatibleDC( hDC ) ;
		hOldBitmap	=	SelectBitmap( hMemDC, Rotation[RotationCourante].hBitmap ) ;
		FastBitBlt( hTempDC, NouveauRect.left, NouveauRect.top, Rotation[RotationCourante].Largeur, Rotation[RotationCourante].Hauteur,
					hMemDC, 0, 0 ) ;
		SelectBitmap( hMemDC, hOldBitmap ) ;
		DeleteDC( hMemDC ) ;
		
		UnionRect( &RectTotal, &NouveauRect, &RectPrec ) ;

		FastBitBlt( hDC, RectTotal.left, RectTotal.top,
					RectTotal.right-RectTotal.left,
					RectTotal.bottom - RectTotal.top,
					hTempDC,
					RectTotal.left, RectTotal.top ) ;

		RectPrec =	NouveauRect ;
		RotationCourante ++  ;

		Sleep( 10 ) ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;
	SPECIF_Fin( hWndPrincipale ) ;

	return 0 ;
}

// ============================================================================
// SPECIF_Fin
// Fin de l'economiseur
// ============================================================================
void SPECIF_Fin( HWND hWnd )
{
	int	i	;
	
	for ( i = 0; i < NbBitmaps; i++ )
		DeleteBitmap( Rotation[i].hBitmap ) ;

	DeleteObject( SelectObject( hTempDC, hOldMemBitmap )) ;
	DeleteDC( hTempDC ) ;
}

			
// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	TRUE ;
	NbBitmaps		=	LitEntier( "Nb Phases", NbBitmaps ) ;
	DivTaille		=	LitEntier( "DivTaille", DivTaille ) ;

	if ( DivTaille < 1 )
		DivTaille	=	1 ;
	else
		if ( DivTaille > 10 )
			DivTaille	=	10 ;

	if ( NbBitmaps < 2 )
		NbBitmaps = 2 ;
	else
		if ( NbBitmaps >= NB_BITMAPS )
			NbBitmaps	=	NB_BITMAPS ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
	EcritEntier( "Nb Phases", NbBitmaps ) ;
	EcritEntier( "DivTaille", DivTaille ) ;
}

// ============================================================================
// SPECIF_ValideParametres
// Valide les parametres saisis dans la boite de dialogue
// ============================================================================
BOOL	SPECIF_ValideParametres(  HWND hWnd )
{
	BOOL Translated ;
	
	NbBitmaps = GetDlgItemInt( hWnd, IDC_NB_PASSANTS,  &Translated, FALSE ) ;
	
	if ( NbBitmaps<= 0 || NbBitmaps> NB_BITMAPS )
		{
		char	T[500] ;
		wsprintf( T, "Veuillez donner une valeur entre 1 et %d", (int)(NB_BITMAPS)) ;
		
		MessageBox( hWnd, T, "Erreur", MB_OK | MB_ICONSTOP ) ;
		return FALSE ;
		}
		
	return TRUE ;
}



// ============================================================================
// SPECIF_ConfInitDialog
// Initialiser la boite de configuration
// ============================================================================

// ============================================================================
// SPECIF_ConfCommande
// WM_COMMAND
// ============================================================================
BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			SPECIF_LirePreferences() ;
			SetDlgItemInt( hDlg, IDC_NB_PASSANTS, NbBitmaps, FALSE ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDC_APPLIQUER :
					
					SPECIF_ValideParametres( hDlg ) ;
					InvalidateRect( hDlg, NULL, TRUE ) ;
					break ;
					
				case IDOK :
					
					if ( SPECIF_ValideParametres(hDlg))
						{
						SPECIF_EcrirePreferences() ;
						EndDialog( hDlg, TRUE ) ;
						}
					return TRUE ;
					
				default :
					return FALSE ;
				}
		}

	return FALSE ;
}

void SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
}