// Partie specifique de l'economiseur
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include "\wing\include\wing.h"
#include <commctrl.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>

#include "resource.h"
#include "..\specif.h"


// ================================================================= Constantes
const char*		SPECIF_NomEconomiseur	=	"Gridium" ;
const char*		SPECIF_ValeurEnregistre	=	"Grid1942" ;
#define			HAUTEUR_CASE		max(1, Hauteur / HauteurGrille )
#define			LARGEUR_CASE		HAUTEUR_CASE

#define			LARGEUR_GRILLE		100
#define			HAUTEUR_GRILLE		100
#define			NB_MAX_NEUTRONS	((LARGEUR_GRILLE*HAUTEUR_GRILLE)/4)
#define			NB_MAX_RECTS		10000
#define			PI					3.14159
#define			VITESSE_NEUTRONS	1.1
#define			DECALAGE_X		((Largeur-(LARGEUR_CASE*LargeurGrille))/2)
#define			DECALAGE_Y		((Hauteur-(HAUTEUR_CASE*HauteurGrille))/2)

typedef	struct
	{
	double	x ;
	double	y ;
	double vx ;
	double vy ;
	}
	NEUTRON ;

// ================================================================= Types

HDC	hDCAtomes ;					// Memorisation de l'affichage des atomes
HBITMAP	hOldAtomes ;
HDC hDCIntermediaire ;
HBITMAP	hOldIntermediaire ;

RECT	RAAfficher ;
RECT	RectsAffichage[ NB_MAX_RECTS ] ;
int		NbRectsAAfficher ;
BYTE	Atomes[LARGEUR_GRILLE][HAUTEUR_GRILLE] ;
NEUTRON	Neutrons[ NB_MAX_NEUTRONS ] ;
int		NbNeutrons	=	0 ;
double	DensiteAtomes	= 0.1 ;
int		LargeurGrille =	LARGEUR_GRILLE ;
int		HauteurGrille =	HAUTEUR_GRILLE ;
double	RayonAtome ;
HBITMAP	hBrise ;
HDC		hDCNeutron ;
HBITMAP	hOldNeutron ;

// ==================================================================================================
// GenereNeutron
// ==================================================================================================
void	GenereNeutron( int i, int j )
{
	double	Angle ;

	if ( NbNeutrons >=	NB_MAX_NEUTRONS )
		return ;

	Angle	=	(double)Alea( 0, (int)PI*200 )/ 100.0 ;

	Neutrons[NbNeutrons].x		=	i * LARGEUR_CASE ;
	Neutrons[NbNeutrons].y		=	j * HAUTEUR_CASE ;
	Neutrons[NbNeutrons].vx		=	sin( Angle ) * VITESSE_NEUTRONS ;
	Neutrons[NbNeutrons].vy		=	cos( Angle ) * VITESSE_NEUTRONS ;
	
	NbNeutrons ++ ;
}


HBITMAP	GetAtomeBitmap( int	Id, int	LargeurCase, int	HauteurCase )
{
	HBITMAP	hLoad ;
	HDC		hMemDC1, hMemDC2 ;
	HBITMAP hResult, hOld1, hOld2 ;
	BITMAP	sBitmap ;
	int		Largeur, Hauteur ;
	HDC		hDC ;

	// Taille de l'atome
	Largeur	=	max( 2, (int)(LargeurCase	*	DensiteAtomes * 2)) ;
	Hauteur =	max( 2, (int)(HauteurCase	*	DensiteAtomes * 2)) ;

	hDC		=	CreateIC( "display", 0,0,0 ) ;

	hLoad	=	LoadBitmap( hMainInstance, MAKEINTRESOURCE( Id )) ;
	GetObject( hLoad, sizeof(sBitmap), &sBitmap ) ;
	hResult	=	CreateCompatibleBitmap( hDC, Largeur, Hauteur );
	
	hMemDC1	=	CreateCompatibleDC( hDC );
	hMemDC2	=	CreateCompatibleDC( hDC );

	DeleteDC( hDC ) ;

	hOld1	=	SelectObject( hMemDC1, hLoad ) ;
	hOld2	=	SelectObject( hMemDC2, hResult ) ;

	StretchBlt( hMemDC2, 0, 0, Largeur, Hauteur,
				hMemDC1, 0, 0, sBitmap.bmWidth, sBitmap.bmHeight, SRCCOPY ) ;

	SelectObject( hMemDC1, hOld1 ) ;
	SelectObject( hMemDC2, hOld2 ) ;

	DeleteObject( hLoad ) ;

	DeleteDC( hMemDC1 ) ;
	DeleteDC( hMemDC2 ) ;
	return hResult ;
}

// ==================================================================================================
// Generation des corps
// ==================================================================================================
void	GenereAtomes( void )
{   
	HBITMAP	hBitmap, hOld ;
	HDC		hMemDC ;
	int	i, j ;
	BITMAP	sBitmap ;

	PatBlt( hDCAtomes, 0,0,Largeur, Hauteur, BLACKNESS ) ;
	hBitmap	=	GetAtomeBitmap( IDB_ATOME, LARGEUR_CASE, HAUTEUR_CASE ) ;
	GetObject( hBitmap, sizeof( sBitmap), &sBitmap );

	hMemDC	=	CreateCompatibleDC( hDCAtomes ) ;
	hOld	=	SelectObject( hMemDC, hBitmap ) ;

	for ( i = 0; i < LargeurGrille; i++)
		for ( j = 0; j < HauteurGrille; j++)
			{
			Atomes[i][j]	=	TRUE ;
			WinGBitBlt( hDCAtomes, DECALAGE_X + i * LARGEUR_CASE, DECALAGE_Y + j * HAUTEUR_CASE, sBitmap.bmWidth, sBitmap.bmHeight,
						hMemDC, 0,0 ) ;
			}

	SelectObject( hMemDC, hOld ) ;
	DeleteObject( hBitmap ) ;
	DeleteDC( hMemDC ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Fonction appelee en cas d'erreur sur les nombres flottants
///////////////////////////////////////////////////////////////////////////////
int ErreurFlottant( int sig )
{
	return 0 ;
}


// ==================================================================================================
// ==================================================================================================
void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	HDC	hDC ;

	SetTimer( hWnd, 1,50, 0 ) ;
	NoircirEcran = TRUE ;
	signal( SIGFPE, ErreurFlottant ) ;
    
	hDC = CreateIC("display", 0, 0, 0 );
	hDCAtomes			=	WinGCreateDC() ; 
	hOldAtomes			=	SelectObject( hDCAtomes, CreateCompatibleBitmap( hDC, Largeur, Hauteur )) ;
	hDCIntermediaire	=	WinGCreateDC() ; 
	hOldIntermediaire	=	SelectObject( hDCIntermediaire, CreateCompatibleBitmap( hDC, Largeur, Hauteur )) ;
	DeleteDC( hDC );

	NbNeutrons			=	0 ;
	RayonAtome			=	LARGEUR_CASE * DensiteAtomes ;

	hBrise				=	GetAtomeBitmap( IDB_ATOME_BRISE,
											(int)(LARGEUR_CASE / DensiteAtomes),
											(int)(HAUTEUR_CASE / DensiteAtomes) ) ;
	
	GenereAtomes() ;
	GenereNeutron( LargeurGrille/2, HauteurGrille/2 ) ;
	NbRectsAAfficher		=	0 ;
	WinGBitBlt( hDCIntermediaire, 0, 0, Largeur, Hauteur, hDCAtomes, 0, 0 ) ;

	hDCNeutron			=	WinGCreateDC() ; 
	hOldNeutron			=	SelectObject( hDCNeutron, LoadBitmap( hMainInstance, MAKEINTRESOURCE(IDB_NEUTRON) )) ;
}  

// ==================================================================================================
// CalculeDistance
//	Calcule la distance entre deux corps
// ==================================================================================================
double	__inline CalculeDistance( double x1, double y1, double x2, double y2 )
{
	double	DX, DY ;
	DX	=	x1 - x2 ;
	DY	=	y1 - y2 ;
	
	return sqrt( (DX*DX) + (DY*DY) ) ;
}

void	__inline EffaceNeutron( i )
{
	RECT	R ;
	SetRect( &R, (int)Neutrons[i].x, (int)Neutrons[i].y,
				 (int)Neutrons[i].x + 3, (int)Neutrons[i].y + 3 ) ;

	OffsetRect( &R, +DECALAGE_X, +DECALAGE_Y ) ;
	WinGBitBlt( hDCIntermediaire, R.left, R.top, R.right-R.left, R.bottom-R.top, hDCAtomes, R.left, R.top ) ;

	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &R ) ;
}

void	__inline AfficheNeutron( int i )
{
	RECT	R ;
	SetRect( &R, (int)Neutrons[i].x, (int)Neutrons[i].y,
				 (int)Neutrons[i].x + 3, (int)Neutrons[i].y + 3 ) ;
	
	OffsetRect( &R, +DECALAGE_X, +DECALAGE_Y ) ;

	WinGBitBlt( hDCIntermediaire, R.left, R.top, R.right-R.left, R.bottom-R.top,
				hDCNeutron, 0, 0 ) ;

	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &R ) ;
}

///////////////////////////////////////////////////////////////////////////////
// ExploseAtome
//	Qu'est ce que ca fait ?
// ENTREES	:	coordonnees (indices ) de l'atome qui ramasse
///////////////////////////////////////////////////////////////////////////////
void	ExploseAtome( HDC hDC, int x, int y )
{
	RECT	R ;
	BITMAP	sBitmap ;
	HDC		hMemDC ;
	HBITMAP	hOld ;

	SetRect( &R,	x* LARGEUR_CASE, y* HAUTEUR_CASE, (x+1)*LARGEUR_CASE, (y+1)*HAUTEUR_CASE ) ;
	OffsetRect( &R, DECALAGE_X, DECALAGE_Y ) ;
	Atomes[x][y]	=	FALSE ;	// l'est plus la
	PatBlt( hDCAtomes,	R.left, R.top, R.right-R.left, R.bottom-R.top, BLACKNESS ) ;
	PatBlt( hDCIntermediaire,	R.left, R.top, R.right-R.left, R.bottom-R.top, BLACKNESS ) ;

	
	GetObject( hBrise, sizeof( sBitmap ), &sBitmap ) ;
	R.right	=	R.left	+ sBitmap.bmWidth ;
	R.bottom=	R.top	+ sBitmap.bmHeight ;

	hMemDC		=	CreateCompatibleDC( hDCAtomes ) ;
	hOld		=	SelectObject( hMemDC, hBrise ) ;

	WinGBitBlt( hDC, R.left, R.top, sBitmap.bmWidth, sBitmap.bmHeight,	hMemDC, 0, 0 ) ;

	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;

	R.right		=	R.left + sBitmap.bmWidth ;
	R.bottom	=	R.top + sBitmap.bmHeight ;

	// L'effacer immediatement
	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAAfficher, &R ) ;
}

BOOL	CollisionAtome( HDC hDC, int i, int x, int y )
{
	double Distance ;
	
	if ( x < 0 || x >= LargeurGrille || y < 0|| y >= HauteurGrille )
		return FALSE ;

	if ( ! Atomes[x][y] )	// L'atome n'est deja plus la
		return FALSE ;
								 	
	Distance = CalculeDistance( Neutrons[i].x, Neutrons[i].y, x * LARGEUR_CASE, y * HAUTEUR_CASE ) ;

	if ( Distance < RayonAtome )
		{
		// Paf !
		// Neutron perdu
		memmove( &Neutrons[i], &Neutrons[i+1], sizeof( NEUTRON ) * ( NbNeutrons - i-1 )) ;

		NbNeutrons -- ;

		// Atome explose
		ExploseAtome( hDC, x, y ) ;
					 
		// Deux nouveaux  neutrons
		GenereNeutron( x, y ) ;
		GenereNeutron( x, y ) ;
		return TRUE ;
		}

	return FALSE ;
}

BOOL __inline Collision( HDC hDC, int i )
{
	int	xA, yA ;

	if ( (int)Neutrons[i].x < -DECALAGE_X || (int)Neutrons[i].x >= Largeur-DECALAGE_X || (int)Neutrons[i].y < -DECALAGE_Y || (int)Neutrons[i].y >= Hauteur-DECALAGE_Y )
		{
		// Neutron perdu
		memmove( &Neutrons[i], &Neutrons[i+1], sizeof( NEUTRON ) * ( NbNeutrons - i - 1 )) ;
		NbNeutrons -- ;
		return TRUE ;
		}

	// Trouver l'atome le plus proche
	xA	=	(int)((Neutrons[i].x - 0.5)/ LARGEUR_CASE ) ;
	yA	=	(int)((Neutrons[i].y - 0.5)/ HAUTEUR_CASE ) ;

	if (CollisionAtome( hDC, i, xA, yA ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA-1, yA + 1))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA-1, yA ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA-1, yA - 1 ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA, yA + 1 ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA, yA - 1 ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA+1, yA + 1))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA+1, yA ))
		return TRUE ;

	if (CollisionAtome( hDC, i, xA+1, yA - 1 ))
		return TRUE ;

	return FALSE ;
}


// ============================================================================
// Cette fonction est un thread
DWORD _stdcall SPECIF_Animation( LPVOID lp  )
// ============================================================================
{
	int	i	;
	HDC	hDC ;

	SPECIF_LirePreferences() ;
	SPECIF_InitEconomiseur(hWndPrincipale) ;

	SetEvent( hEventInitFini ) ;
	
	// ============================================================================ Remettre un fond noir	
	hDC	=	GetDC( hWndPrincipale ) ;

	while ( ! Fini )
		{
		NbRectsAAfficher	=	0 ;

		for ( i = NbNeutrons - 1; i >= 0; i--)
			{
			EffaceNeutron( i ) ;
			Neutrons[i].x	+=	Neutrons[i].vx ;
			Neutrons[i].y	+=	Neutrons[i].vy ;

			if ( ! Collision( hDC, i ))
				AfficheNeutron( i ) ;
			}

		AfficheRectangles( RectsAffichage, NbRectsAAfficher, hDC, hDCIntermediaire ) ;
		
		if ( NbNeutrons == 0)
			{
			GenereAtomes() ;
			GenereNeutron( LargeurGrille/2, HauteurGrille/2 ) ;
			WinGBitBlt( hDCIntermediaire, 0,0, Largeur, Hauteur, hDCAtomes, 0, 0 ) ;
			WinGBitBlt( hDC, 0,0, Largeur, Hauteur, hDCAtomes, 0, 0 ) ;
			}
		}
	ReleaseDC( hWndPrincipale, hDC ) ;

	return 0 ;
}

// ============================================================================
// SPECIF_Fin
// Fin de l'economiseur
// ============================================================================
void SPECIF_Fin( HWND hWnd )
{
	DeleteObject( SelectObject( hDCAtomes, hOldAtomes )) ;
	DeleteDC( hDCAtomes ) ;
	DeleteObject (hBrise ) ;
	DeleteObject( SelectObject( hDCIntermediaire, hOldIntermediaire )) ;
	DeleteDC( hDCIntermediaire ) ;
	DeleteObject( SelectObject( hDCNeutron, hOldNeutron)) ;
	DeleteDC( hDCNeutron );
}

 
// ============================================================================
// SPECIF_PaintFenetre
// Peindre la fenetre
// ============================================================================
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{  
	WinGBitBlt( hDC, 0, 0, Largeur, Hauteur, hDCIntermediaire, 0, 0 ) ;
}


// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	DensiteAtomes	=	LitDouble( "Rayon atomes", DensiteAtomes ) ;
	LargeurGrille=	LitEntier( "Quantité Matière", LargeurGrille ) ;
	LargeurGrille=	min( LARGEUR_GRILLE, max( 2, LargeurGrille )) ;
	HauteurGrille=	LargeurGrille ;
}							  

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
	EcritDouble( "Rayon atomes", DensiteAtomes ) ;
	EcritEntier( "Quantité Matière", LargeurGrille ) ;
}

LRESULT	CALLBACK	DessinWndProc( HWND hWnd, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_PAINT :
			{
			PAINTSTRUCT	Ps ;
			HDC			hDC	;
			RECT		R ;
			int			i, j ;
			const		double	Taille	=	50 ;
			HBITMAP		hBitmap, hOld ;
			HDC			hMemDC ;
			BITMAP		sBitmap ;

			hDC	=	BeginPaint( hWnd, &Ps ) ;
			GetClientRect( hWnd, &R ) ;
			
			hBitmap		=	GetAtomeBitmap( IDB_ATOME, (int)Taille, (int)Taille ) ;
			GetObject( hBitmap, sizeof(sBitmap), &sBitmap ) ;

			hMemDC		=	CreateCompatibleDC( hDC ) ;
			hOld		=	SelectObject( hMemDC, hBitmap ) ;

			for ( i = R.left; i < R.right; i+= (int)Taille )
				for ( j = R.top; j < R.bottom; j += (int)Taille  )
					WinGBitBlt( hDC, i, j, sBitmap.bmWidth, sBitmap.bmHeight,
								hMemDC, 0, 0 ) ;

			SelectObject( hMemDC, hOld ) ;
			DeleteObject( hBitmap );
			DeleteDC( hMemDC ) ;

			EndPaint( hWnd, &Ps ) ;
			}
			break ;

		default :
			return DefWindowProc( hWnd, Message, wParam, lParam ) ;
		}
	return 0 ;
}

// ============================================================================
// SPECIF_ConfCommande
// WM_COMMAND
// ============================================================================
BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			RECT	R ;
			POINT	Pt ;
			WNDCLASS	Class ;

			SPECIF_LirePreferences();

			// Creation de la fenetre affichant la densite des atomes
			GetWindowRect( GetDlgItem( hDlg, IDC_CADRE ), &R ) ;

			InflateRect( &R, -2, -2 ) ;

			Class.style		=	CS_VREDRAW | CS_HREDRAW ;
			Class.lpfnWndProc=	DessinWndProc ;
			Class.cbClsExtra=	0 ;
			Class.cbWndExtra=	0 ;
			Class.hInstance	=	hMainInstance ;
			Class.hIcon		=	0 ;
			Class.hCursor	=	LoadCursor( NULL, IDC_ARROW ) ;
			Class.hbrBackground =	GetStockObject( BLACK_BRUSH ) ;
			Class.lpszMenuName=	NULL ;
			Class.lpszClassName=	"Dessin" ;

			RegisterClass( &Class ) ;
			Pt.x	=	R.left ;
			Pt.y	=	R.top ;
			ScreenToClient( hDlg, &Pt ) ;
			R.left	=	Pt.x ;
			R.top	=	Pt.y ;

			Pt.x	=	R.right;
			Pt.y	=	R.bottom ;
			ScreenToClient( hDlg, &Pt ) ;
			R.right	=	Pt.x ;
			R.bottom=	Pt.y ;

			CreateWindow( "Dessin", "",
							WS_CHILD | WS_VISIBLE | WS_BORDER,
						   R.left, R.top, R.right-R.left, R.bottom-R.top,
						   hDlg,
						   (HMENU)200,
						   hMainInstance,
						   NULL ) ;

			// Slider quantite de matiere
			SendDlgItemMessage( hDlg, IDC_QUANTITE, TBM_SETRANGE, TRUE, MAKELPARAM( 2, LARGEUR_GRILLE )) ;
			SendDlgItemMessage( hDlg, IDC_QUANTITE, TBM_SETPAGESIZE, TRUE, 10 ) ;
			SendDlgItemMessage( hDlg, IDC_QUANTITE, TBM_SETLINESIZE, TRUE, 1 ) ;
			SendDlgItemMessage( hDlg, IDC_QUANTITE, TBM_SETPOS, TRUE, (LPARAM)LargeurGrille ) ;
			}
			break ;


		case WM_NOTIFY :
			{
			LPNMHDR	lpHdr	=	(LPNMHDR)lParam ;

			if ( lpHdr->code == UDN_DELTAPOS )
				{
				NM_UPDOWN FAR *	lpUpDown	=	(NM_UPDOWN FAR *)lParam ;

				if ( lpUpDown->iDelta > 0 )
					DensiteAtomes -= 0.01 ;
				else
					DensiteAtomes += 0.01 ;

				if ( DensiteAtomes > 0.8)
					DensiteAtomes	=	0.8 ;
				if ( DensiteAtomes < 0.01 )
					DensiteAtomes = 0.01 ;

				InvalidateRect( GetDlgItem( hDlg, 200), NULL, TRUE ) ;
				UpdateWindow( GetDlgItem( hDlg, 200) ) ;
				}
			}
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					{
					LargeurGrille	=	SendDlgItemMessage( hDlg, IDC_QUANTITE, TBM_GETPOS, 0, 0 ) ;
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
