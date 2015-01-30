// Loupes.cpp: implementation of the CLoupes class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <windowsx.h>
#include <math.h>
#include "Loupes.h"
#include <RectAffichage.h>
#include <RegistrationKey.h>
#include "ParametresLoupes.h"

///////////////////////////////////////////////////////////////////////////////
// Constantes
///////////////////////////////////////////////////////////////////////////////
#define FastBitBlt( h,x,y,l,j,i,a,b )	BitBlt( h,x,y,l,j,i,a,b, SRCCOPY ) ;

#define NB_MAX_RECTS	(NB_MAX_SPRITES)

#define PI				3.14159
#define DEUX_PI			(PI * 2.0)
#define	NB_MAX_COINS	8


///////////////////////////////////////////////////////////////////////////////
// Types
///////////////////////////////////////////////////////////////////////////////

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

int					CLoupes::NbMaxSprites	=	10 ;
CString				CLoupes::_Texte = "Loupes" ;
COLORREF			CLoupes::_CouleurTexte = RGB( 255, 0 , 0 ) ;


CRectAffichage		RectsAffichage ;
CRegistrationKey	Key( LOP_PATH, LOP_HIDDEN ) ;
CLoupes				ZeEconomiseur ;


///////////////////////////////////////////////////////////////////////////////
// Retourne une bitmap qui contient l'image de l'ecran, eventuellement retaillee
///////////////////////////////////////////////////////////////////////////////
HBITMAP MemoEcran( int Larg, int Haut )
{
	HDC	hDC ;
	HDC	hDCEcran ;
	HBITMAP	hBmpEcran ;
	HBITMAP	hOldEcran ;

	hDC			=	CreateDC( "display", 0, 0, 0 ) ;
	hDCEcran	=	CreateCompatibleDC( hDC ) ;

	hBmpEcran	=	CreateCompatibleBitmap( hDC, Larg, Haut  ) ;
    hOldEcran	=	(HBITMAP)SelectObject(	hDCEcran,	hBmpEcran ) ;

	SetStretchBltMode( hDCEcran, HALFTONE ) ;
	StretchBlt(	hDCEcran, 0,0, Larg, Haut, 
				hDC, 0,0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
				SRCCOPY ) ;

	DeleteDC( hDC ) ;
	SelectObject( hDCEcran, hOldEcran ) ;
	DeleteDC( hDCEcran ) ;

	return hBmpEcran ;
}

///////////////////////////////////////////////////////////////////////////////
// RegionOffset
// Calcule la region occupee par le sprite
//	ENTREES	:	Position x, y du sprite
//				Taille
//				Nb de coins
//				Angle de rotation courant
///////////////////////////////////////////////////////////////////////////////
HRGN CLoupes::RegionOffset( T_SPRITE * pSprite )
{
	HRGN	hRegion ;
	
	switch( pSprite->NbCoins )
			{
			case -1 :
				// Texte
				{
				HDC hDC	=	CreateDC( "display", NULL, NULL, NULL ) ;
				HDC hMemDC	=	CreateCompatibleDC( hDC ) ;
				BeginPath( hMemDC ) ;
				HFONT	hFonte	=	CreateFont( pSprite->Taille/2,
										pSprite->Taille / ( _Texte.GetLength() + 2 ),
										pSprite->Rotation*20, 0,
										FW_BOLD,
										FALSE, FALSE, FALSE,
										DEFAULT_CHARSET,
										OUT_DEFAULT_PRECIS,
										CLIP_TT_ALWAYS,
										DRAFT_QUALITY,
										DEFAULT_PITCH | FF_DONTCARE,
										"Arial" ) ;

				HFONT hOldFonte	=	(HFONT)SelectObject( hMemDC, hFonte ) ;

				SetTextAlign( hMemDC, TA_CENTER ) ;
				SetBkMode( hMemDC, TRANSPARENT ) ;
				TextOut( hMemDC, pSprite->x + pSprite->Taille/2, pSprite->y + pSprite->Taille/2, _Texte, _Texte.GetLength()) ;
				
				EndPath( hMemDC ) ;
				hRegion	=	PathToRegion( hMemDC ) ;

				SelectObject( hMemDC, hOldFonte ) ;
				DeleteObject( hFonte ) ;
				
				DeleteDC( hMemDC ) ;
				DeleteDC( hDC ) ;
				return hRegion ;				
				}

			case 0 :
			case 1 :
				///////////////////////////////////////////////////////////////
				// Loupe ronde
				///////////////////////////////////////////////////////////////
				hRegion	=	CreateEllipticRgn( pSprite->x+1, pSprite->y+1, pSprite->x + pSprite->Taille, pSprite->y + pSprite->Taille) ;
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
					Angle	=	(j * DEUX_PI / 5) + ((double)pSprite->Rotation) / 30.0 ;

					Pts[j].x	=	pSprite->x + pSprite->Taille/2 + (int)((pSprite->Taille/2)*sin( Angle )) ;

					if ( Pts[j].x < 0 )
						Pts[j].x = 0 ;

					Pts[j].y	=	pSprite->y + pSprite->Taille/2 + (int)((pSprite->Taille/2)*cos( Angle )) ;
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
				for ( j = 0; j < pSprite->NbCoins; j++)
					{
					Angle	=	(j * DEUX_PI / pSprite->NbCoins) + ((double)pSprite->Rotation) / 30.0 ;

					Pts[j].x	=	pSprite->x + pSprite->Taille/2 + (int)((pSprite->Taille/2)*sin( Angle )) ;

					//if ( Pts[j].x < 0 )
					//	Pts[j].x = 0 ;

					Pts[j].y	=	pSprite->y + pSprite->Taille/2 + (int)((pSprite->Taille/2)*cos( Angle )) ;
					//if ( Pts[j].y < 0 )
					//	Pts[j].y = 0 ;

					}

				hRegion	=	CreatePolygonRgn( Pts, pSprite->NbCoins, WINDING ) ;
				}
		}

	return hRegion ;
}

///////////////////////////////////////////////////////////////////////////////
// Efface un sprite
///////////////////////////////////////////////////////////////////////////////
void	__inline EffacerSprite( HDC hDC, T_SPRITE * pSprite )
{
	
	if ( hDCMemo )
		BitBlt( hDC,
			    pSprite->Rect.left, pSprite->Rect.top, pSprite->Rect.right-pSprite->Rect.left, pSprite->Rect.bottom-pSprite->Rect.top,
 				hDCMemo, pSprite->Rect.left, pSprite->Rect.top,
				SRCCOPY) ;
	else
		PatBlt( hDC,
				pSprite->Rect.left, pSprite->Rect.top, pSprite->Rect.right-pSprite->Rect.left, pSprite->Rect.bottom-pSprite->Rect.top,
				BLACKNESS ) ;

	RectsAffichage += pSprite->Rect ;
}

///////////////////////////////////////////////////////////////////////////////
// AfficherSprite
//	Effacer, bouger et afficher un sprite
//	ENTREES :	hDC
//				@ du sprite
//	SORTIES :
//	RETOUR :
///////////////////////////////////////////////////////////////////////////////
void	__inline CLoupes::AfficherSprite( HDC hDC, T_SPRITE * pSprite )
{
	HRGN	hRegionAfficher ;
	
	pSprite->x	+=	pSprite->dx ;
	pSprite->y	+=	pSprite->dy ;
	pSprite->Rotation += pSprite->VitesseRotation ;

	hRegionAfficher	=	RegionOffset( pSprite ) ;

	if ( hRegionAfficher )
		{
		GetRgnBox( hRegionAfficher, &pSprite->Rect ) ;
		InflateRect( &pSprite->Rect, 2, 2 ) ;

		// Afficher nouveau sprite
		SelectClipRgn( hDC, hRegionAfficher ) ;

		if ( NoircirEcran )
			{
			DWORD RasterOp ;

			if ( pSprite->NbCoins == -1 )
				RasterOp	=	SRCINVERT ;
			else
				RasterOp	=	SRCPAINT ;

			BitBlt(	hDC, pSprite->x, pSprite->y, pSprite->Taille, pSprite->Taille,
					hDCZoom, pSprite->x*2+pSprite->Taille/2, pSprite->y*2+pSprite->Taille/2,
					RasterOp) ;
			}
		else
			FastBitBlt(	hDC, pSprite->x, pSprite->y, pSprite->Taille, pSprite->Taille,
						hDCZoom, pSprite->x*2+pSprite->Taille/2, pSprite->y*2+pSprite->Taille/2 ) ;

		//FrameRgn( hDC, hRegionAfficher, (HBRUSH)GetStockObject(BLACK_BRUSH), 1, 1 ) ;

		SelectClipRgn( hDC, NULL ) ;
		
		DeleteObject( hRegionAfficher );
		}
	else
		{
		// Texte
		HFONT	hFonte	=	CreateFont( pSprite->Taille/2,
										pSprite->Taille / ( _Texte.GetLength() + 2 ),
										pSprite->Rotation*20, 0,
										FW_BOLD,
										FALSE, FALSE, FALSE,
										DEFAULT_CHARSET,
										OUT_DEFAULT_PRECIS,
										CLIP_TT_ALWAYS,
										DRAFT_QUALITY,
										DEFAULT_PITCH | FF_DONTCARE,
										"Arial" ) ;

		HFONT hOldFonte	=	(HFONT)SelectObject( hDC, hFonte ) ;

		SetTextAlign( hDC, TA_CENTER ) ;
		SetRect( &pSprite->Rect, pSprite->x, pSprite->y, pSprite->x + pSprite->Taille, pSprite->y + pSprite->Taille ) ;

		SetTextColor( hDC, _CouleurTexte) ;
		SetBkMode( hDC, TRANSPARENT ) ;

		TextOut( hDC, pSprite->x + pSprite->Taille/2, pSprite->y + pSprite->Taille/2, _Texte, _Texte.GetLength()) ;
		SIZE	Size ;
		GetTextExtentPoint32( hDC, _Texte, _Texte.GetLength(), &Size ) ;
		
		const int DiffX	=	Size.cx - pSprite->Taille ;

		if ( DiffX > 0 )
			{
			pSprite->Rect.right += DiffX ;
			pSprite->Rect.left -= DiffX ;
			}

		const int DiffY	=	Size.cy - pSprite->Taille ;

		if ( DiffY > 0 )
			{
			pSprite->Rect.bottom += DiffY ;
			pSprite->Rect.top -= DiffY ;
			}

		//pSprite->Rect.right	=	max( pSprite->Rect.right, pSprite->Rect.left + Size.cx ) ;
		//pSprite->Rect.bottom =	max( pSprite->Rect.bottom, pSprite->Rect.top + Size.cy ) ;

		SelectObject( hDC, hOldFonte ) ;
		DeleteObject( hFonte ) ;

		InflateRect( &pSprite->Rect,pSprite->Taille/2,pSprite->Taille/2 ) ;
		} 

		
	// Calcul du rectangle utilise pour l'affichage
	RectsAffichage += pSprite->Rect ;

}



///////////////////////////////////////////////////////////////////////////////
// Creation d'un nouveau sprite
///////////////////////////////////////////////////////////////////////////////
void	CLoupes::NouveauSprite( T_SPRITE * pSprite )
{
	pSprite->x	=	Alea( 0, Largeur ) ;
	pSprite->y	=	Alea( 0, Hauteur ) ;

	pSprite->Taille=	Alea( 20, 300 ) ;
	
	do
		{					
		pSprite->dx	=	Alea( -8, 8 ) ;
		pSprite->dy	=	Alea( -8, 8 ) ;
		}
	while ( pSprite->dx == 0 && pSprite->dy == 0 ) ;

	pSprite->NbCoins	=	Alea( -2, NB_MAX_COINS ) ;

	pSprite->Rotation	=	0 ;

	pSprite->VitesseRotation	=	Alea( -8, 8 ) ;

	SetRect( &pSprite->Rect, 0, 0, 0, 0 ) ;
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoupes::CLoupes()
:CEconomiseur( "Loupes" )
{
	NoircirEcran	=	TRUE ;

	if ( Key.IsLocked())
		{
		_Texte.LoadString( IDS_UNREGISTERED_SHAREWARE ) ;
		}
	else
		{
		char	Buffer[100] ;
		DWORD	Taille	=	sizeof( Buffer ) ;
		if ( ! GetUserName( Buffer, &Taille )) ;
			Taille	=	0 ;

		if ( Taille == 0 )
			{
			Taille	=	sizeof( Buffer ) ;
			if ( ! GetComputerName( Buffer, &Taille ))
				Taille	= 0 ;

			if ( Taille	==	0 )
				strcpy( Buffer,"Loupes" ) ;
			}

		_Texte	=	Buffer ;
		}
}

CLoupes::~CLoupes()
{

}

void CLoupes::InitSave( HWND	hWnd )
	{
	CEconomiseur::InitSave( hWnd ) ;

	///////////////////////////////////////////////////////////////////////////
	// Creation des sprites initiaux
	///////////////////////////////////////////////////////////////////////////
	for ( int i = 0; i < NbMaxSprites; i++)
		NouveauSprite( &Sprites[i] ) ;
	
	
	HDC	hDC	=	CreateDC( "display", 0 ,0,  0 ) ;
	
	// Creation du DC intermediaire
	hDCIntermediaire	=	CreateCompatibleDC( hDC ) ;
	hOldIntermediaire	=	(HBITMAP)SelectObject( hDCIntermediaire, CreateCompatibleBitmap( hDC,Largeur,Hauteur )) ;

	if ( NoircirEcran )
		{
		// Le fond est noir
		hDCMemo		=	0 ;
		PatBlt(	hDCIntermediaire, 0, 0, Largeur, Hauteur, BLACKNESS ) ;
		}
	else
		{
		// Memorisation de l'ecran
		hDCMemo		=	CreateCompatibleDC( hDC ) ;
		hOldMemo	=	(HBITMAP)SelectObject( hDCMemo, ::MemoEcran( Largeur, Hauteur )) ;
		FastBitBlt( hDCIntermediaire, 0, 0, Largeur, Hauteur, hDCMemo, 0, 0 ) ;
		}

	///////////////////////////////////////////////////////////////////////////
	// Zoom une fois pour toutes l'ecran, ca accelere
	hDCZoom				=	CreateCompatibleDC( NULL ) ;
	hOldZoom			=	(HBITMAP)SelectObject( hDCZoom, ::MemoEcran( Largeur*2, Hauteur*2 )) ;

	DeleteDC( hDC ) ;
	}



void CLoupes::Configuration( CPropertySheet * pProp )
	{
	pProp->AddPage( new CParametresLoupes ) ;
	CEconomiseur::Configuration( pProp ) ;
	}


void CLoupes::UpdateFenetre( CDC &, const CRect & )
	{
	}


void CLoupes::Animation( CDC&	Dc )
	{
	RectsAffichage.Vide() ;

	for ( int i = 0; i < NbMaxSprites; i ++ )
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

	RectsAffichage.BitBlt( Dc.m_hDC, hDCIntermediaire ) ;
	}


void CLoupes::InitDC( CDC & Dc )
	{

	}

void CLoupes::FinDC( CDC & )
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


void CLoupes::Preferences()
	{
	CEconomiseur::Preferences() ;

	Preference( "Fond noir", NoircirEcran ) ;
	Preference( "Nb loupes", NbMaxSprites ) ;

	if ( ! Key.IsLocked())
		{
		Preference( "Texte",	_Texte ) ;
		Preference( "Couleur texte", _CouleurTexte ) ;
		}
	}