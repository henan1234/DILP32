/////////////////////////////////////////////////////////////////////////////
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
#define NB_MAX_SPRITES	20
#define NB_MAX_RECTS	(NB_MAX_SPRITES)

#define PI				3.14159
#define DEUX_PI			(PI * 2.0)
const	char	*		SPECIF_NomEconomiseur	=	"Loupes" ;
const	char	*		SPECIF_ValeurEnregistre	=	"Lou-kjlh-pes" ;
#define	NB_MAX_COINS	8

///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////
typedef struct
	{
	int	x ;
	int	y ;
	int	Taille ;
	int	dx ;
	int	dy ;
	int	NbCoins ;
	int	Rotation ;
	RECT	Rect ;
	}
	T_SPRITE ;

///////////////////////////////////////////////////////////////////////////////
// Variables globales
///////////////////////////////////////////////////////////////////////////////
HDC			hDCMemo = 0 ;
HBITMAP		hOldMemo ;

HDC			hDCZoom ;
HBITMAP		hOldZoom ;

HDC			hDCIntermediaire = 0 ;
HBITMAP		hOldIntermediaire ;

T_SPRITE	Sprites[NB_MAX_SPRITES] ;
int			NbMaxSprites	=	5 ;
RECT		RectsAffichage[ NB_MAX_RECTS ] ;
int			NbRectsAffichage ;


///////////////////////////////////////////////////////////////////////////////
// RegionOffset
// Calcule la region occupee par le sprite
//	ENTREES	:	Position x, y du sprite
//				Taille
//				Nb de coins
//				Angle de rotation courant
///////////////////////////////////////////////////////////////////////////////
HRGN __inline RegionOffset( int x, int y, int Taille, int NbCoins, int Rotation )
{
	HRGN	hRegion ;
	
	switch( NbCoins )
			{
			case 0 :
				return NULL ;

			case 1 :
				///////////////////////////////////////////////////////////////
				// Loupe ronde
				///////////////////////////////////////////////////////////////
				hRegion	=	CreateEllipticRgn( x+1, y+1, x + Taille, y + Taille) ;
				break ;

			case 2 :
				///////////////////////////////////////////////////////////////
				// Loupe en etoile
				///////////////////////////////////////////////////////////////
				{
				POINT	Pts[5] ;
				POINT	Pt ;
				int		j ;
				double	Angle;

				for ( j = 0; j < 5; j++)
					{
					Angle	=	(j * DEUX_PI / 5) + ((double)Rotation) / 30.0 ;

					Pts[j].x	=	x + Taille/2 + (int)((Taille/2)*sin( Angle )) ;

					if ( Pts[j].x < 0 )
						Pts[j].x = 0 ;

					Pts[j].y	=	y + Taille/2 + (int)((Taille/2)*cos( Angle )) ;
					if ( Pts[j].y < 0 )
						Pts[j].y = 0 ;

					}


				// Changer la sequence 0 1 2 3 4 en 0 2 4 1 3 pour obtenir une etoile
				Pt		=	Pts[2] ;
				Pts[2]	=	Pts[4] ;
				Pts[4]	=	Pts[3] ;
				Pts[3]	=	Pts[1] ;
				Pts[1]	=	Pt ;

				hRegion	=	CreatePolygonRgn( Pts, 5, WINDING ) ;
				}
				break ;
			default :

				///////////////////////////////////////////////////////////////
				// Creation d'un polygone de NbCoins coins
				///////////////////////////////////////////////////////////////
				{
				POINT		Pts[NB_MAX_COINS] ;
				int 		j ;
				double		Angle ;
				
				// Calcul de la position de chaque coin
				for ( j = 0; j < NbCoins; j++)
					{
					Angle	=	(j * DEUX_PI / NbCoins) + ((double)Rotation) / 30.0 ;

					Pts[j].x	=	x + Taille/2 + (int)((Taille/2)*sin( Angle )) ;

					if ( Pts[j].x < 0 )
						Pts[j].x = 0 ;

					Pts[j].y	=	y + Taille/2 + (int)((Taille/2)*cos( Angle )) ;
					if ( Pts[j].y < 0 )
						Pts[j].y = 0 ;

					}

				hRegion	=	CreatePolygonRgn( Pts, NbCoins, WINDING ) ;
				}
		}

	return hRegion ;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	InitEconomiseur( HWND hWnd )
{
	hDCIntermediaire	=	FastCreateDC() ;
	hOldIntermediaire	=	SelectObject( hDCIntermediaire,	FastCreateBitmap( hDCIntermediaire,Largeur,Hauteur )) ;

	if ( NoircirEcran )
		{
		// Le fond est noir
		hDCMemo		=	0 ;
		PatBlt(	hDCIntermediaire, 0, 0, Largeur, Hauteur, BLACKNESS ) ;
		}
	else
		{
		// Memorisation de l'ecran
		hDCMemo		=	FastCreateDC( ) ;
		hOldMemo	=	SelectObject( hDCMemo, MemoEcran( Largeur, Hauteur )) ;
		FastBitBlt( hDCIntermediaire, 0, 0, Largeur, Hauteur, hDCMemo, 0, 0 ) ;
		}

	///////////////////////////////////////////////////////////////////////////
	// Zoom une fois pour toutes l'ecran, ca accelere
	hDCZoom				=	FastCreateDC() ;
	hOldZoom			=	SelectObject( hDCZoom, MemoEcran( Largeur*2, Hauteur*2 )) ;
}

///////////////////////////////////////////////////////////////////////////////
// Efface un sprite
///////////////////////////////////////////////////////////////////////////////
void	__inline EffacerSprite( HDC hDC, T_SPRITE * pSprite )
{
	
	if ( hDCMemo )
		FastBitBlt( hDC,
				  pSprite->Rect.left, pSprite->Rect.top, pSprite->Rect.right-pSprite->Rect.left, pSprite->Rect.bottom-pSprite->Rect.top,
 				  hDCMemo, pSprite->Rect.left, pSprite->Rect.top ) ;
	else
		PatBlt( hDC,
				pSprite->Rect.left, pSprite->Rect.top, pSprite->Rect.right-pSprite->Rect.left, pSprite->Rect.bottom-pSprite->Rect.top,
				BLACKNESS ) ;

	AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAffichage, &pSprite->Rect ) ;
}

///////////////////////////////////////////////////////////////////////////////
// AfficherSprite
//	Effacer, bouger et afficher un sprite
//	ENTREES :	hDC
//				@ du sprite
//	SORTIES :
//	RETOUR :
///////////////////////////////////////////////////////////////////////////////
void	__inline AfficherSprite( HDC hDC, T_SPRITE * pSprite )
{
	HRGN	hRegionAfficher ;
	
	pSprite->x	+=	pSprite->dx ;
	pSprite->y	+=	pSprite->dy ;
	pSprite->Rotation ++ ;

	hRegionAfficher	=	RegionOffset( pSprite->x+ pSprite->dx, pSprite->y + pSprite->dy, 
									  pSprite->Taille, pSprite->NbCoins, pSprite->Rotation + 1 ) ;

	if ( ! hRegionAfficher )
		{
		SetTextColor( hDC, RGB( 255, 0, 0 )) ;
		SetBkColor( hDC, 0 ) ;
		SetBkMode( hDC, TRANSPARENT ) ;

		SetRect( &pSprite->Rect,
				 pSprite->x*2-pSprite->Taille/2, pSprite->y*2-pSprite->Taille/2,
				 pSprite->x*2+pSprite->Taille/2, pSprite->y*2+pSprite->Taille/2 ) ;

		DrawText( hDC, "Unregistered shareware", -1, &pSprite->Rect, DT_CENTER | DT_WORDBREAK ) ;

		AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAffichage, &pSprite->Rect ) ;
		}
	else
		{
		GetRgnBox( hRegionAfficher, &pSprite->Rect ) ;

		// Afficher nouveau sprite
		SelectClipRgn( hDC, hRegionAfficher ) ;

		if ( NoircirEcran )
			BitBlt(	hDC, pSprite->x, pSprite->y, pSprite->Taille, pSprite->Taille,
					hDCZoom, pSprite->x*2+pSprite->Taille/2, pSprite->y*2+pSprite->Taille/2,
					SRCPAINT) ;
		else
			FastBitBlt(	hDC, pSprite->x, pSprite->y, pSprite->Taille, pSprite->Taille,
						hDCZoom, pSprite->x*2+pSprite->Taille/2, pSprite->y*2+pSprite->Taille/2 ) ;
		
		SelectClipRgn( hDC, NULL ) ;

		// Calcul du rectangle utilise pour l'affichage
		AjouteRect( RectsAffichage, NB_MAX_RECTS, &NbRectsAffichage, &pSprite->Rect ) ;

		DeleteObject( hRegionAfficher );
		}
}



///////////////////////////////////////////////////////////////////////////////
// Creation d'un nouveau sprite
///////////////////////////////////////////////////////////////////////////////
void	NouveauSprite( T_SPRITE * pSprite )
{
	pSprite->x	=	Alea( 0, Largeur ) ;
	pSprite->y	=	Alea( 0, Hauteur ) ;

	pSprite->Taille=	Alea( 20, 200 ) ;
	
	do
		{					
		pSprite->dx	=	Alea( -10, 10 ) ;
		pSprite->dy	=	Alea( -10, 10 ) ;
		}
	while ( pSprite->dx == 0 && pSprite->dy == 0 ) ;

	pSprite->NbCoins	=	Alea( 0, NB_MAX_COINS ) ;

	pSprite->Rotation	=	0 ;
	SetRect( &pSprite->Rect, 0, 0, 0, 0 ) ;
}


///////////////////////////////////////////////////////////////////////////////
//	Fin de l'economiseur
///////////////////////////////////////////////////////////////////////////////
void 	Fin( void )
{
	if ( hDCMemo )
		{
		DeleteObject( SelectObject( hDCMemo, hOldMemo )) ;
		DeleteDC( hDCMemo ) ;	
		}
		
	DeleteObject( SelectObject( hDCIntermediaire, hOldIntermediaire )) ;
	DeleteDC( hDCIntermediaire ) ;
	hDCIntermediaire	=	0 ;

	DeleteObject( SelectObject( hDCZoom, hOldZoom )) ;
	DeleteDC( hDCZoom ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Animation
///////////////////////////////////////////////////////////////////////////////
DWORD _stdcall SPECIF_Animation( LPVOID p /*HDC hDC, UINT NoTimer, LPRECT lpR*/ )
{
	int 	i ;
	HDC		hDC ;

	SPECIF_LirePreferences() ;
	InitEconomiseur( hWndPrincipale ) ;

	hDC	=	GetDC( hWndPrincipale ) ;

	///////////////////////////////////////////////////////////////////////////
	// Creation des sprites initiaux
	///////////////////////////////////////////////////////////////////////////
	for ( i = 0; i < NbMaxSprites; i++)
		NouveauSprite( &Sprites[i] ) ;

	SetEvent( hEventInitFini ) ;

	while ( ! Fini )		// Tant que dure le thread
		{
		NbRectsAffichage	=	0 ;

		for ( i = 0; i < NbMaxSprites; i ++ )
			EffacerSprite( hDCIntermediaire, &Sprites[i] ) ;

		///////////////////////////////////////////////////////////////////////////
		// Bouger les sprites existants
		///////////////////////////////////////////////////////////////////////////
		for ( i	= NbMaxSprites-1; i >= 0; i-- ) // On part de la fin a cause des suppressions
			{
			if ( Sprites[i].x > Largeur || Sprites[i].y > Hauteur ||
				 Sprites[i].x + Sprites[i].Taille < 0 || Sprites[i].y + Sprites[i].Taille < 0 )
				NouveauSprite( &Sprites[i] ) ;

			AfficherSprite( hDCIntermediaire, &Sprites[i] ) ;
			}

		AfficheRectangles( RectsAffichage, NbRectsAffichage, hDC, hDCIntermediaire ) ;
		}

	ReleaseDC( hWndPrincipale, hDC ) ;
	
	Fin() ;

	SetEvent( hEventFini ) ;

	return 0 ;
}

 
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{
	if ( ! NoircirEcran )
		FastBitBlt( hDC, lpR->left, lpR->top, Largeur, Hauteur,hDCMemo, 0, 0 );
}

void	SPECIF_LirePreferences(void)
{
	NoircirEcran =	LitEntier( "Noircir écran", FALSE ) ;
	NbMaxSprites =	LitEntier( "NbMaxLoupes", NbMaxSprites ) ;
	NoircirEcran =	LitEntier( "NoircirEcran", NoircirEcran ) ;
}

void	SPECIF_EcrirePreferences(void)
{
	EcritEntier( "Noircir écran", NoircirEcran ) ;
	EcritEntier( "NbMaxLoupes", NbMaxSprites ) ;
	EcritEntier( "NoircirEcran", NoircirEcran ) ;
}

BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, unsigned Message, WPARAM wParam , LPARAM lParam )
{ 
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			SPECIF_LirePreferences() ;
			CheckDlgButton( hDlg, IDC_NOIR, NoircirEcran ) ;
			SendDlgItemMessage( hDlg, IDC_NB_LOUPES, TBM_SETRANGE, TRUE, MAKELPARAM( 1, NB_MAX_SPRITES )) ;
			SendDlgItemMessage( hDlg, IDC_NB_LOUPES, TBM_SETPAGESIZE, TRUE, 10 ) ;
			SendDlgItemMessage( hDlg, IDC_NB_LOUPES, TBM_SETLINESIZE, TRUE, 1 ) ;
			SendDlgItemMessage( hDlg, IDC_NB_LOUPES, TBM_SETPOS, TRUE, (LPARAM)NbMaxSprites ) ;
			return FALSE ; 	// Pour centrer la fenetre
			}
			break ;
		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					NoircirEcran	=	IsDlgButtonChecked( hDlg, IDC_NOIR ) ;
					NbMaxSprites	=	SendDlgItemMessage( hDlg, IDC_NB_LOUPES, TBM_GETPOS, 0, 0 ) ;
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
