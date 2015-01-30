// Partie specifique de l'economiseur
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <string.h>
#include <stdlib.h>
#include "resource.h"
#include "..\specif.h"

// ================================================================= Constantes
#define NB_MAX_PASSANTS	100

const char * SPECIF_NomEconomiseur = "Promenade" ;
const char * SPECIF_ValeurEnregistre	=	"Pr0984" ;

typedef enum	{ BOULE, CUBE } TYPE_PASSANT ;

// ====================================================================== Types
typedef struct
	{
	TYPE_PASSANT	Type ;
	int	x ;
	int	y ;
	int	dx ;
	int	dy ;
	int	Largeur ;
	int	Hauteur ;
	int	Longueur ;
	int	Altitude ;
	int	Dv ;
	
	COLORREF Couleur ;
	}
	PASSANT ;
	
int	NbPassants ;
PASSANT	Passants[NB_MAX_PASSANTS] ;
int	NbMaxPassants = 5 ;

int	LargeurEcran	;
int HauteurEcran	;
HDC	hMemDC	;
HBITMAP	hBitmap	;
HBITMAP	hOldBitmap ;

#define NB_MAX_RECTS		NB_MAX_PASSANTS
RECT	RectsAffichage[ NB_MAX_RECTS ] ;
int		NbRectsAAfficher ;

extern HINSTANCE hMainInstance ;

HBITMAP	hBMFond ;

// ================================================================= Variables

// --------------------------------------------------------------------------------------------------
// GenereUnPassant
// --------------------------------------------------------------------------------------------------
static __inline void NEAR PASCAL GenereUnPassant( LPRECT lpR )
{
	Passants[NbPassants].Type	=	Alea( BOULE, CUBE ) ;
	Passants[NbPassants].x =	Alea( lpR->left, lpR->right ) ;
	Passants[NbPassants].y =   Alea( lpR->top,  lpR->bottom ) ;
	do
		{
		Passants[NbPassants].dx =	Alea( -2, 2 ) ;
		Passants[NbPassants].dy =	Alea( -2, 2 ) ;
		Passants[NbPassants].Dv =   Alea( -2, 2 ) ;
		}
	while ( !Passants[NbPassants].dx && !Passants[NbPassants].dy && !Passants[NbPassants].Dv ) ;
	
	Passants[NbPassants].Largeur =	Alea( 5, 30 ) ;
	if ( Passants[NbPassants].Type == CUBE )
		Passants[NbPassants].Hauteur =   Alea( 5, 30 ) ;
	else
		Passants[NbPassants].Hauteur =   Passants[NbPassants].Largeur ;
	Passants[NbPassants].Longueur=	Alea( 5, 30 ) ;
	Passants[NbPassants].Altitude=	Alea( 1, 20 ) ;
	
	
	Passants[NbPassants].Couleur = 	GetNearestColor( hMemDC, RGB( Alea( 9, 254 ), Alea( 10,255), Alea( 11, 253 ))) ;
	
	NbPassants ++ ;
}
// --------------------------------------------------------------------------------------------------
// CalculeRectangle
// --------------------------------------------------------------------------------------------------
static __inline void NEAR PASCAL CalculeRectangles( PASSANT *pPassant, PRECT pHaut, PRECT pBas, PRECT pOmbre, LPRECT pFenetre ) 
{
	int	MilieuX, MilieuY ;
	
	pHaut->left	= pPassant->x - pPassant->Largeur ;
	pHaut->right = pPassant->x + pPassant->Largeur ;
	pHaut->top	= pPassant->y - pPassant->Hauteur ;
	pHaut->bottom= pPassant->y + pPassant->Hauteur ;
	
	pBas->left		= pPassant->x - (pPassant->Largeur * 9 / 10 );
	pBas->right	 	= pPassant->x + (pPassant->Largeur * 9 / 10 );
	pBas->top			= pPassant->y - (pPassant->Hauteur * 9 / 10 );
	pBas->bottom		= pPassant->y + (pPassant->Hauteur * 9 / 10 );
	
	MilieuX			= pFenetre->left+ ( pFenetre->right-pFenetre->left)/2 ;
	MilieuY			= pFenetre->top+ ( pFenetre->bottom-pFenetre->top)/2 ;
	
	InflateRect( pBas, -1, -1 ) ;
	OffsetRect( pHaut, (pPassant->x-MilieuX)/(40-pPassant->Altitude), (pPassant->y-MilieuY)/(40-pPassant->Altitude)) ;
	InflateRect( pHaut, pPassant->Altitude / 10, pPassant->Altitude / 10 ) ;
	
	(*pOmbre) = (*pBas) ;
	OffsetRect( pOmbre, pBas->left - pHaut->left, pBas->top - pHaut->top ) ;
}

// --------------------------------------------------------------------------------------------------
// EffacePassant
// --------------------------------------------------------------------------------------------------
static void EffacePassant( HDC hDC, PASSANT * pPassant, LPRECT pFenetre ) 
{
	RECT	RectHaut, RectBas, Ombre ;
	RECT	Rect ;
	
	// Calcul des deux rectangles
	CalculeRectangles( pPassant, &RectHaut, &RectBas, &Ombre, pFenetre ) ;
	UnionRect( &Rect, &RectHaut, &RectBas ) ;
	UnionRect( &RectHaut, &Rect, &Ombre ) ;
	Rect = RectHaut ;
	InflateRect( &Rect, 20, 20 ) ;
	
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &Rect ) ;
}

// --------------------------------------------------------------------------------------------------
// EffacePassant
// --------------------------------------------------------------------------------------------------
static void AffichePassantCube( HDC hDC, PASSANT * pPassant, LPRECT pFenetre ) 
{  
	HBRUSH	hBrush, hOldBrush ;
	HPEN		hOldPen ;
	RECT	RectHaut, RectBas, RectOmbre ;
	POINT	Pt[4] ;
	int MilieuX, MilieuY ;

	MilieuX			= pFenetre->left+ ( pFenetre->right-pFenetre->left)/2 ;
	MilieuY			= pFenetre->top+ ( pFenetre->bottom-pFenetre->top)/2 ;
	
	// Calcul des deux rectangles
	CalculeRectangles( pPassant, &RectHaut, &RectBas, &RectOmbre, pFenetre ) ;
	
	// Ombre
	FillRect( hDC, &RectOmbre, GetStockObject( BLACK_BRUSH ) ) ;
	
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &RectOmbre ) ;
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &RectBas ) ;
	
	hBrush	=	CreateSolidBrush( pPassant->Couleur ) ;
	hOldBrush = SelectBrush( hDC, hBrush ) ;
	hOldPen	=	SelectPen( hDC, GetStockObject( BLACK_PEN )) ;
		
	// Cote haut
	if ( pPassant->y > MilieuY )
		{
		Pt[0].x = RectBas.left ;
		Pt[0].y = RectBas.top ;
		Pt[1].x = RectBas.right ;
		Pt[1].y = RectBas.top ;
		Pt[2].x = RectHaut.right ;
		Pt[2].y = RectHaut.top ;
		Pt[3].x = RectHaut.left ;
		Pt[3].y = RectHaut.top ;
		Polygon( hDC, Pt, 4 ) ;
	   }
	   
	// Cote bas 
	if ( pPassant->y < MilieuY )
		{
		Pt[0].x = RectBas.left ;
		Pt[0].y = RectBas.bottom ;
		Pt[1].x = RectBas.right ;
		Pt[1].y = RectBas.bottom ;
		Pt[2].x = RectHaut.right ;
		Pt[2].y = RectHaut.bottom ;
		Pt[3].x = RectHaut.left ;
		Pt[3].y = RectHaut.bottom ;
		Polygon( hDC, Pt, 4 ) ;
		}
		
	// Cote droit
	if ( pPassant->x < MilieuX )
		{
		Pt[0].x = RectBas.right ;
		Pt[0].y = RectBas.top ;
		Pt[1].x = RectBas.right ;
		Pt[1].y = RectBas.bottom ;
		Pt[2].x = RectHaut.right ;
		Pt[2].y = RectHaut.bottom ;
		Pt[3].x = RectHaut.right ;
		Pt[3].y = RectHaut.top ;
		Polygon( hDC, Pt, 4 ) ;
	   }
	   
	// Cote gauche
	if ( pPassant->x > MilieuX )
		{
		Pt[0].x = RectBas.left;
		Pt[0].y = RectBas.top ;
		Pt[1].x = RectBas.left ;
		Pt[1].y = RectBas.bottom ;
		Pt[2].x = RectHaut.left ;
		Pt[2].y = RectHaut.bottom ;
		Pt[3].x = RectHaut.left ;
		Pt[3].y = RectHaut.top ;
		Polygon( hDC, Pt, 4 ) ;
      }
	
	// Rectangle haut
	Rectangle( hDC, RectHaut.left, RectHaut.top, RectHaut.right, RectHaut.bottom ) ;
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &RectHaut ) ;
	
	SelectBrush( hDC, hOldBrush ) ;
	SelectPen( hDC, hOldPen ) ;
	DeleteBrush( hBrush ) ;
}

// --------------------------------------------------------------------------------------------------
// EffacePassant
// --------------------------------------------------------------------------------------------------
static __inline void NEAR PASCAL AffichePassantBoule( HDC hDC, PASSANT * pPassant, LPRECT pFenetre ) 
{  
	HBRUSH	hBrush, hOldBrush ;
	HPEN		hOldPen ;
	RECT	RectHaut, RectBas, RectOmbre ;
	int		Largeur, Hauteur ;
	
	// Calcul des deux rectangles
	CalculeRectangles( pPassant, &RectHaut, &RectBas, &RectOmbre, pFenetre ) ;
	
	// Ombre
	hOldBrush	=	SelectBrush( hDC, GetStockObject( BLACK_BRUSH )) ;
	hOldPen		=	SelectPen( hDC, GetStockObject( NULL_PEN )) ;
	Ellipse( hDC, RectOmbre.left, RectOmbre.top, RectOmbre.right, RectOmbre.bottom ) ;
	
	hBrush	=	CreateSolidBrush( pPassant->Couleur ) ;
	SelectBrush( hDC, hBrush ) ;
	SelectPen( hDC, GetStockObject( BLACK_PEN )) ;
		
	Ellipse( hDC, RectHaut.left, RectHaut.top, RectHaut.right, RectHaut.bottom ) ;	
	SelectBrush( hDC, hOldBrush ) ;
	
	Largeur = RectHaut.right-RectHaut.left ;
	Hauteur = RectHaut.bottom-RectHaut.top ;
		
	SelectBrush( hDC, GetStockObject( WHITE_BRUSH )) ;
	SelectPen( hDC, GetStockObject( NULL_PEN )) ;
		
	Ellipse( hDC, RectHaut.left+Largeur/4, RectHaut.top+Hauteur/4, RectHaut.left + Largeur/2, RectHaut.top + Hauteur/2 ) ;
		
		
	SelectBrush( hDC, hOldBrush ) ;
	SelectPen( hDC, hOldPen ) ;
	DeleteBrush( hBrush ) ;
}



// --------------------------------------------------------------------------------------------------
// BougeUnPassant
// --------------------------------------------------------------------------------------------------
static __inline void NEAR PASCAL BougeUnPassant( HDC hDC, LPRECT lpR,PASSANT * pPassant )
{
	
	// Effacer l'ancienne position
	EffacePassant( hDC, pPassant, lpR ) ;
	
	// Bouger le passant
	pPassant->x	+= pPassant->dx ;
	pPassant->y	+=	pPassant->dy ;
	

	if ( pPassant->x < 0 )
		pPassant->dx = 5 ;
	else
		if ( pPassant->x > GetSystemMetrics(SM_CXSCREEN))
			pPassant->dx = -5 ;

	if ( pPassant->y < 0 )
		pPassant->dy = 5 ;
	else
		if ( pPassant->y > GetSystemMetrics(SM_CYSCREEN))
			pPassant->dx = -5 ;
			
	if ( UnSur( 50 ) )
		{
			do
				{
				pPassant->dx =	2 - Alea( 0, 5 ) ;
				pPassant->dy =	2 - Alea( 0, 5 ) ;
			   }
			while ( !pPassant->dx && !pPassant->dy ) ;
		}
	
	pPassant->Altitude += pPassant->Dv ;
	
	if ( pPassant->Altitude <= 0)
		{
		pPassant->Altitude = 1 ;
		pPassant->Dv = -pPassant->Dv ;
		}
		
	if ( pPassant->Altitude >= 29)
		{
		pPassant->Altitude = 29 ;
		pPassant->Dv = -pPassant->Dv ;
		}
	
	// Afficher le passant
	if ( pPassant->Type == CUBE )
		AffichePassantCube( hDC, pPassant, lpR ) ;
	else
		AffichePassantBoule( hDC, pPassant, lpR ) ;
	
	
}

// --------------------------------------------------------------------------------------------------
// Collision
//
// --------------------------------------------------------------------------------------------------
int Collision( PASSANT * pPassant, int Indice )
{
	RECT	RTest ;
	RECT	RCourant ;
	RECT	RRes ;
	int i ;
	
	SetRect( &RTest, pPassant->x, pPassant->y, pPassant->x + pPassant->Largeur, pPassant->y + pPassant->Hauteur ) ;
	OffsetRect(&RTest, pPassant->dx, pPassant->dy ) ;
	
	for ( i = 0; i < NbPassants; i++)
		if ( i != Indice )
			{
			SetRect( &RCourant, Passants[i].x, Passants[i].y, Passants[i].x + Passants[i].Largeur, Passants[i].y + Passants[i].Hauteur ) ;
			if ( IntersectRect(&RRes, &RTest, &RCourant ))
				return i ;
			}
	return -1 ;
}

// --------------------------------------------------------------------------------------------------
// PassantVisible
// --------------------------------------------------------------------------------------------------
static __inline BOOL PassantVisible( PASSANT * pPassant, LPRECT lpR )
{
	POINT Pt ;
	RECT	R = *lpR ;
	
	Pt.x = pPassant->x ;
	Pt.y = pPassant->y ;
	
	InflateRect( &R, 200, 200 ) ;
	return PtInRect( &R, Pt) ;
}

// --------------------------------------------------------------------------------------------------
// ChangeSiCollision
// Fait rebondir le passant s'il entre en collision avec un autre
// --------------------------------------------------------------------------------------------------
void	ChangeSiCollision( PASSANT * pPassant, int i, HDC hDC, LPRECT lpR )
{
	int	Collis =  Collision( pPassant, i ) ;
	// Verifie le haut si le passant se dirige vers le haut
	if ( Collis != -1 )
		{
		pPassant->dy = -pPassant->dy ;
		pPassant->dx = -pPassant->dx ;
		
		if ( Collision( pPassant, i ) == Collis )
			{
			memmove( &Passants[i], &Passants[i+1], sizeof( PASSANT ) * (NbPassants-i)) ;
			NbPassants -- ;
			EffacePassant( hDC, pPassant, lpR ) ;
			}
		}
}


// ==================================================================================================
// ==================================================================================================
void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	HDC	hDC ;

	NbPassants = 0 ;
	SetTimer( hWnd, 1, 50, 0);

	LargeurEcran	=	GetSystemMetrics( SM_CXSCREEN ) ;
	HauteurEcran	=	GetSystemMetrics( SM_CYSCREEN ) ;

	hDC		=	CreateDC( "display", 0, 0, 0 ) ;
	hMemDC	=	CreateCompatibleDC( hDC ) ;
	// memorise l'ecran tel qu'il est pour servir de fond

	hBMFond		=	CreateCompatibleBitmap( hDC, LargeurEcran, HauteurEcran ) ;
	hOldBitmap	=	SelectObject( hMemDC, hBMFond ) ;
	BitBlt( hMemDC, 0, 0, LargeurEcran, HauteurEcran, hDC, 0, 0, SRCCOPY ) ;

	// Bitmap pour le double buffer
	hBitmap	=	CreateCompatibleBitmap( hDC, LargeurEcran, HauteurEcran ) ;
	SelectObject( hMemDC, hBitmap ) ;

	DeleteDC( hDC ) ;
}  

// ============================================================================
DWORD _stdcall SPECIF_Animation( LPVOID lp  )
// ============================================================================
{  
	HDC			hDC ;
	RECT		R ;
	int i ;
	HDC	hMDC ;
	HBITMAP	hOBitmap ;		
	
	SPECIF_InitEconomiseur( hWndPrincipale ) ;

	hDC			=	GetDC( hWndPrincipale ) ;
	GetClientRect( hWndPrincipale, &R ) ;

	NbRectsAAfficher	=	0 ;
	hMDC				=	CreateCompatibleDC( hDC ) ;
	hOBitmap			=	SelectObject( hMDC, hBMFond ) ;
	BitBlt( hDC, R.left, R.top, R.right-R.left, R.bottom-R.top, hMDC, 0, 0, SRCCOPY ) ;

	SetEvent( hEventInitFini ) ;

		
	while ( ! Fini )
		{
		BitBlt( hMemDC, 0, 0, LargeurEcran, HauteurEcran, hMDC, 0, 0, SRCCOPY ) ;
	
		if ( NbPassants < NbMaxPassants )
			GenereUnPassant( &R ) ;
			
		for ( i = 0; i < NbPassants; i++)
			{
			BougeUnPassant( hMemDC, &R, &Passants[i] ) ;
			ChangeSiCollision( &Passants[i], i, hMemDC, &R ) ;
			}
			

		AfficheRectangles( RectsAffichage, NbRectsAAfficher, hDC, hMemDC ) ;

		i = 0 ;
		while ( i < NbPassants )
			if ( PassantVisible( &Passants[i], &R ))
				i ++ ;
			else
				{
				memmove( &Passants[i], &Passants[i+1], sizeof( PASSANT ) * (NbPassants-i)) ;
				NbPassants -- ;
				}
		}

	SelectObject( hMDC, hOBitmap );
	DeleteDC( hMDC ) ;
	return 0 ;
}

// ============================================================================
// SPECIF_Fin
// Fin de l'economiseur
// ============================================================================
void SPECIF_Fin( HWND hWnd )
{
	SelectObject( hMemDC, hOldBitmap ) ;
	DeleteObject( hBitmap ) ;
	DeleteDC( hMemDC ) ;

	DeleteObject( hBMFond ) ;
}

			
// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	FALSE ;
//	HautePriorite	=	LitEntier(	"Haute Priorite", TRUE ) ;
	NbMaxPassants	=	LitEntier(	"Nombre", 12 ) ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
//	EcritEntier(	"Haute Priorite", HautePriorite ) ;  
	EcritEntier(	"Nombre", NbMaxPassants ) ;             
}


// ============================================================================
// SPECIF_ConfCommande
// WM_COMMAND
// ============================================================================
BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			SPECIF_LirePreferences() ;
			SetDlgItemInt( hDlg, IDC_NB_PASSANTS, NbMaxPassants, FALSE ) ;


			SendDlgItemMessage( hDlg, IDC_UPOWN, UDM_SETBUDDY, (WPARAM)GetDlgItem( hDlg, IDC_NB_PASSANTS ), 0 ) ;
			SendDlgItemMessage( hDlg, IDC_UPOWN, UDM_SETRANGE, 0, (LPARAM)MAKELONG( NB_MAX_PASSANTS, 1 ) ) ;
			SendDlgItemMessage( hDlg, IDC_UPOWN, UDM_SETPOS, 0, (LPARAM)MAKELONG( NbMaxPassants, 0 ) ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					{
					BOOL	tr ;
					NbMaxPassants =	GetDlgItemInt( hDlg, IDC_NB_PASSANTS, &tr, TRUE ) ;

					NbMaxPassants	=	min( NB_MAX_PASSANTS, max(1, NbMaxPassants )) ;

					SPECIF_EcrirePreferences() ;
					}
					break ;
				}
			break ;

		default :
			return FALSE ;
		}

	return FALSE ;
}

void SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	HDC	hMDC ;
	HBITMAP	hOBitmap ;

	hMDC	=	CreateCompatibleDC( hDC ) ;
	hOBitmap	=	SelectObject( hMDC, hBMFond ) ;

	BitBlt( hDC, 0, 0, LargeurEcran, HauteurEcran, hMDC, 0, 0, SRCCOPY ) ;

	SelectObject( hMDC, hOBitmap ) ;
	DeleteDC( hMDC ) ;
}
