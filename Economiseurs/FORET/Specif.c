// Partie specifique de l'economiseur
#define STRICT
#include <windows.h>
#include <windowsx.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <commctrl.h>
#include "resource.h"
#include "..\specif.h"

// ================================================================= Constantes
#define DEG_RAD(x)		(((x)+180) * 3.14 * 2.0  / 360.0)
#define SIN(x)				sin( DEG_RAD(x))
#define COS(x)				cos( DEG_RAD(x))
#define LONGUEUR_MAX		200
#define LARGEUR_MAX		20
#define NB_MAX_SOMMETS_FEUILLE 10

const	char	*	SPECIF_NomEconomiseur	=	"Foret" ;
const	char	*	SPECIF_ValeurEnregistre	=	"ft][124" ;

extern	void	PeintPaysage( HDC, LPRECT ) ;

// ====================================================================== Types
typedef struct BRANCHE
			{
			POINT		Depart ;
			int			Epaisseur ;
			int			Angle ;
			int			Longueur ;
			int			LongueurVoulue ;
			int			NbBranchesMin ;
			int			NbBranchesMax ;
			struct 	BRANCHE FAR *	lpSuivante ;					   
			struct	BRANCHE FAR *	lpPrecedente ;
			}
			BRANCHE ;
			
// ================================================================= Variables
BRANCHE	FAR 	*	lpBranches = 0 ;
COLORREF	CouleurFeuilles ;
COLORREF	CouleurBranches ;
COLORREF	CouleurFruit ;
int			AngleArbre = 0 ;
BOOL		PousseeRapide = FALSE ;
int			ProbaBranche ;
UINT		NbBranches ;
UINT		NbSommetsFeuille ;
BOOL		Paysage = TRUE ;
UINT		NbArbres = 10 ;
UINT		NbArbresAffiches = 0 ;

static void	AjouteBranche( BRANCHE * pBranche )
{
	BRANCHE FAR * lpBranche ;
	BRANCHE FAR * lpDerniere ;

	// =============================================================== Allocation de la branche
	lpBranche						= (BRANCHE FAR *)GlobalAllocPtr( GMEM_MOVEABLE, sizeof( BRANCHE )) ;
	if ( ! lpBranche )
		return ;
		
	// ============================================================ Trouver la derniere branche
	if ( lpBranches )				// Y a t il deja des branches ?
		{
		lpDerniere = lpBranches ;
		while ( lpDerniere->lpSuivante )
			lpDerniere = lpDerniere->lpSuivante ;
		}
	else
		{
		lpDerniere = 0 ;
		lpBranches = lpBranche ;
		}
		
	(*lpBranche)					= (*pBranche) ;
	lpBranche->lpSuivante		= 0 ;
	lpBranche->lpPrecedente		= lpDerniere ;
	
	if ( lpDerniere )
		lpDerniere->lpSuivante = lpBranche ;
		
	NbBranches ++ ;
}

static void ModifieCouleur( COLORREF * pCouleur )
	{
	int R	=	GetRValue( *pCouleur ) ;
	int G	=	GetGValue( *pCouleur ) ;
	int B	=	GetBValue( *pCouleur ) ;

	R	=	Alea( R-1, R+1 ) ;
	G	=	Alea( G-1, G+1 ) ;
	B	=	Alea( B-1, B+1 ) ;

	if ( R < 0 )
		R	=	0 ;
	if ( R > 255 )
		R	=	255 ;
	if ( G < 0 )
		G	=	0 ;
	if ( G > 255 )
		G	=	255 ;
	if ( B < 0 )
		B	=	0 ;
	if ( B > 255 )
		B	=	255 ;

	*pCouleur	=	RGB( R, G, B ) ;
	}

static void SupprimeBranche( BRANCHE FAR * pBranche )
{
	BRANCHE FAR * lpPrecedente ;
	BRANCHE FAR * lpSuivante ;
	
	lpPrecedente 	= pBranche->lpPrecedente ;
	lpSuivante		= pBranche->lpSuivante ;
	
	if ( lpPrecedente )
		// Ce n'est pas la premiere branche de la liste
		lpPrecedente->lpSuivante = pBranche->lpSuivante ;
	else
		// C'etait la premiere de la liste
		lpBranches = lpSuivante ;
		
	if ( lpSuivante )
		lpSuivante->lpPrecedente = lpPrecedente ;
		
	// Liberation de la branche
	GlobalFreePtr( pBranche ) ;
	
	NbBranches -- ;
}

// ----------------------------------------------------------------------------
// DessineFeuille
// Dessine une feuille ( ou un fruit ) a l'extremite d'une branche
// ENTREES :	DC
//					Branche
// ----------------------------------------------------------------------------
static void	DessineFeuille( HDC hDC, BRANCHE FAR * pBranche )
{
	POINT	Pt[NB_MAX_SOMMETS_FEUILLE] ;
	int	x, y ;
	HBRUSH	hBrush, hOldBrush ;
	UINT	i ;
	int	LargeurFruit, HauteurFruit ;
	
	x	= pBranche->Depart.x + (int)(pBranche->Longueur*SIN( pBranche->Angle )) ;
	y	= pBranche->Depart.y + (int)(pBranche->Longueur*COS( pBranche->Angle )) ;
		
	if ( UnSur( 50 ))
		{
		// ======================================================= Dessiner un fruit
		LargeurFruit	= Alea( 2, 10 ) ;
		HauteurFruit	= Alea( 2, 10 ) ;
		
		hBrush		=	CreateSolidBrush( CouleurFruit ) ;
		hOldBrush	=	SelectBrush( hDC, hBrush ) ;
		Ellipse( hDC, x - LargeurFruit, y - HauteurFruit, x + HauteurFruit, y + HauteurFruit ) ;
		SelectBrush( hDC, hOldBrush ) ;
		DeleteBrush( hBrush ) ;
		}
	else
		{	
		// ===================================================== Dessiner la feuille
		for ( i = 0; i < NbSommetsFeuille; i++)
			{
			Pt[i].x = x - 10 + Alea( 0, 21 ) ;
			Pt[i].y = y - 10 + Alea( 0, 21 ) ;
			}
		
		hBrush	= CreateSolidBrush( CouleurFeuilles ) ;
		ModifieCouleur( &CouleurFeuilles ) ;
		hOldBrush = SelectBrush( hDC, hBrush ) ;
		Polygon( hDC, Pt, NbSommetsFeuille ) ;
		
		SelectBrush( hDC, hOldBrush ) ;
		DeleteBrush( hBrush ) ;
		}
}


void GenereUneBranche( BRANCHE FAR * pBranche )
{
	BRANCHE	Branche ;
	
	Branche.Depart.x			= pBranche->Depart.x + (int)(pBranche->Longueur*SIN( pBranche->Angle )) ;
	Branche.Depart.y			= pBranche->Depart.y + (int)(pBranche->Longueur*COS( pBranche->Angle )) ;
	Branche.Epaisseur 		= pBranche->Epaisseur/2 + 2 - Alea( 0,2 );
	
	Branche.NbBranchesMax	= pBranche->NbBranchesMax - Alea( 0, 1 ) ;
	Branche.NbBranchesMin	= pBranche->NbBranchesMin ;
	
	if ( Branche.NbBranchesMin >= Branche.NbBranchesMax )
		Branche.NbBranchesMin -- ;
	                            
	Branche.LongueurVoulue	= Alea( pBranche->LongueurVoulue/3, (pBranche->LongueurVoulue/3)*2 ) ;
	Branche.Longueur	= 0 ;
	
	if ( UnSur( 2 ))
		Branche.Angle	=	pBranche->Angle + AngleArbre * Alea( 1, 4 ) ;
	else
		Branche.Angle	=	pBranche->Angle - AngleArbre * Alea( 1, 4 ) ;
		
				
	AjouteBranche( &Branche ) ;
}

void GenereBranchesFilles( BRANCHE FAR * pBranche )
{
	int		i ;
	int		NbBranches = Alea( pBranche->NbBranchesMin, pBranche->NbBranchesMax ) ;
	
	for ( i = 0; i < NbBranches; i++)
			GenereUneBranche(pBranche) ;
}

void __inline PousseBranche( BRANCHE FAR * lpBranche )
{
	if ( PousseeRapide )
		(lpBranche->Longueur) += (lpBranche->LongueurVoulue) ;
	else
		{
		(lpBranche->Longueur) += 3 ;
		(lpBranche->Angle)	 += 1 - Alea( 0, 2 ) ;
		}
}

// ============================================================================
// AfficheBranche
//	Affiche une branche d'un arbre
// 
// ============================================================================
void AfficheBranche( HDC hDC,BRANCHE FAR * lpBranche )
{
	POINT	Dest ;
	HBRUSH	hBrush, hOldBrush ;
	HPEN		hOldPen ;
	POINT	Pt[3] ;
	POINT	DecaleDepart ;
	POINT	DecaleDest ;
	double	Sinus, Cosinus ;
		
	Dest.x	=	lpBranche->Depart.x + (int)(lpBranche->Longueur * SIN( lpBranche->Angle )) ;
	Dest.y	=	lpBranche->Depart.y + (int)(lpBranche->Longueur * COS( lpBranche->Angle )) ;
		
	hBrush		= CreateSolidBrush( CouleurBranches ) ;
	ModifieCouleur( &CouleurBranches ) ;

	hOldBrush	= SelectBrush( hDC, hBrush ) ;

	if ( PousseeRapide )
		{
		hOldPen = SelectPen( hDC, GetStockObject( NULL_PEN )) ;
		
		Sinus		=	SIN( lpBranche->Angle-90) ;
		Cosinus	=	COS( lpBranche->Angle-90) ;
		
		DecaleDepart.x	=	(int)((lpBranche->Epaisseur * Sinus ) / 2);
		DecaleDepart.y	=	(int)((lpBranche->Epaisseur * Cosinus ) /2) ;
		DecaleDest.x	=	(int)((lpBranche->Epaisseur / 2 * Sinus) /2);
		DecaleDest.y	=	(int)((lpBranche->Epaisseur / 2 * Cosinus ) /2) ;
		
		Pt[0].x	=	lpBranche->Depart.x - DecaleDepart.x ;
		Pt[0].y	=	lpBranche->Depart.y - DecaleDepart.y ;
		
		Pt[1].x	=	Dest.x	- DecaleDest.x ;
		Pt[1].y	=	Dest.y	- DecaleDest.y ;
		
		Pt[2].x	=	Dest.x	+ DecaleDest.x ;
		Pt[2].y	=	Dest.y	+ DecaleDest.y ;
		
		Pt[3].x	=	lpBranche->Depart.x + DecaleDepart.x ;
		Pt[3].y	=	lpBranche->Depart.y + DecaleDepart.y ;
		
		Polygon( hDC, Pt, 4 ) ;
		SelectPen( hDC, hOldPen ) ;
		Polyline( hDC, Pt, 4 ) ;
		}
	else
		{
		Ellipse( hDC, Dest.x - lpBranche->Epaisseur/2, Dest.y - lpBranche->Epaisseur/2,
						  Dest.x + lpBranche->Epaisseur/2, Dest.y + lpBranche->Epaisseur/2 ) ;
		}
		
	SelectBrush( hDC, hOldBrush ) ;
	DeleteBrush( hBrush ) ;
}


void	GenereUnArbre( LPRECT lpR )
{
	BRANCHE	Branche ;
	int		Largeur ;
	
	Largeur = lpR->right - lpR->left ;
		
	Branche.Depart.x		=	Alea( 0, Largeur) ;
	Branche.Depart.y		=	Hauteur ;
	Branche.Epaisseur		=	Alea( Largeur/20, Largeur/10 ) ;
	Branche.Angle			=	0 ;
	Branche.Longueur		=	0 ;
	Branche.LongueurVoulue 	=	Alea( Hauteur/4, Hauteur/2 ) ;
	Branche.NbBranchesMin	=	Alea( 3, 4 ) ;
	Branche.NbBranchesMax	=	Alea( Branche.NbBranchesMin+1, Branche.NbBranchesMin + 3 ) ;
	
	AjouteBranche( &Branche ) ;
	
	CouleurBranches			=	RGB( Alea( 32, 192 ), Alea( 32,(255*NbArbresAffiches/NbArbres)), 0 ) ;
	CouleurFeuilles			=	RGB( 0, Alea( 32, 255), 0 ) ;
	CouleurFruit			=	RGB( Alea( 64, 255 ), Alea( 0, 255 ), 0 ) ;
			
	AngleArbre				=	Alea( 10, 60 ) ;
			
	ProbaBranche			= Alea( 800, 2000 ) ;
	
	NbSommetsFeuille		=	Alea( 3, NB_MAX_SOMMETS_FEUILLE ) ;
}
// ==================================================================================================
// ==================================================================================================
void SPECIF_InitEconomiseur( HWND hWnd )
// ==================================================================================================
// ==================================================================================================
{
	RECT R ;
	NoircirEcran = TRUE ;
	SetRect( &R, 0, 0, Largeur, Hauteur ) ;
	//HautePriorite = TRUE ;

	//SetTimer( hWnd, 1, 50, 0 ) ;
	
	lpBranches	= 0 ;
		
	GenereUnArbre(&R) ;
}  

// ============================================================================
DWORD _stdcall SPECIF_Animation( LPVOID lp  )
// ============================================================================
{
	HDC	hDC ;
	static BRANCHE FAR * pBranche = 0 ;
	BRANCHE FAR *	pNext ;
	RECT	R ;

	SetRect( &R, 0, 0, Largeur, Hauteur ) ;
		
	SPECIF_InitEconomiseur( hWndPrincipale ) ;
	hDC	=	GetDC( hWndPrincipale ) ;

	SetEvent( hEventInitFini ) ;

	while ( ! Fini )
		{
			
		if ( ! lpBranches ) // Plus de branches, on fait un nouvel arbre
			{
			NbArbresAffiches ++ ;
			if ( NbArbresAffiches > NbArbres )
				{
				NbArbresAffiches = 0 ;
				InvalidateRect( GetActiveWindow(), NULL, TRUE ) ;
				}
			else
				GenereUnArbre(&R) ;
			}

		if ( pBranche == 0 )
			// Recommencer au debut de la liste
			pBranche = lpBranches ;
			
		if ( pBranche )
			{		
			pNext	=	pBranche->lpSuivante ;
				
			PousseBranche( pBranche ) ;
			AfficheBranche( hDC, pBranche ) ;
				
			if ( pBranche->Longueur >= pBranche->LongueurVoulue )
				{
				if ( (pBranche->Epaisseur > 4 ) /*&&( pBranche->NbBranchesMax > 1 )*/ )
					GenereBranchesFilles( pBranche ) ;
				else
					DessineFeuille( hDC, pBranche ) ;
					
				SupprimeBranche( pBranche ) ;
				}
					
			pBranche = pNext ;
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
}

 
// ============================================================================
// SPECIF_PaintFenetre
// Peindre la fenetre
// ============================================================================
void	SPECIF_PeintFenetre( HDC hDC, LPRECT lpR )
{  
	if ( ! Paysage )
		return ;

	PeintPaysage( hDC, lpR );		
}

// ============================================================================
// SPECIF_LirePreferences
// Lire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_LirePreferences( void )
{
	NoircirEcran	=	TRUE ;
	//HautePriorite	=	LitEntier( "Haute Priorite", TRUE ) ;
	PousseeRapide	=	LitEntier( "Poussee Rapide", PousseeRapide ) ;
	Paysage			=	LitEntier( "Paysage", Paysage ) ;
	NbArbres		=	LitEntier(	"NbArbres", NbArbres ) ;
}

// ============================================================================
// SPECIF_EcrirePreferences
// Ecrire les preferences de l'economiseur a partir du .INI
// ============================================================================
void SPECIF_EcrirePreferences( void )
{
	EcritEntier( "Haute Priorite", TRUE ) ;          
	EcritEntier( "Poussee Rapide", PousseeRapide ) ; 
	EcritEntier( "Paysage", Paysage ) ;              
	EcritEntier( "NbArbres", NbArbres ) ;           
}


// ============================================================================
// SPECIF_ConfCommande
// WM_COMMAND
// ============================================================================
BOOL	SPECIF_PreprocessMessageConfig( HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam )
{
	BOOL	Translated ;
	
	switch( Message )
		{
		case WM_INITDIALOG :
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS,	UDM_SETBUDDY, (WPARAM)GetDlgItem( hDlg, IDC_NBARBRES ), 0 ) ;
			SendDlgItemMessage( hDlg, IDC_PLUSMOINS,	UDM_SETRANGE, 0, MAKELPARAM( 1, 100 ) ) ;
			CheckDlgButton( hDlg, IDC_RAPIDE, PousseeRapide ) ;
			CheckDlgButton( hDlg, IDC_PAYSAGE, Paysage) ;
			//CheckDlgButton( hDlg, IDC_PRIORITE, HautePriorite ) ;

			//HautePriorite	= IsDlgButtonChecked( hDlg, IDC_PRIORITE ) ;
			Paysage			= IsDlgButtonChecked( hDlg, IDC_PAYSAGE ) ;
			SetDlgItemInt( hDlg, IDC_NBARBRES, NbArbres, FALSE ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					PousseeRapide	= IsDlgButtonChecked( hDlg, IDC_RAPIDE ) ;
					//HautePriorite	= IsDlgButtonChecked( hDlg, IDC_PRIORITE ) ;
					Paysage			= IsDlgButtonChecked( hDlg, IDC_PAYSAGE ) ;
					NbArbres			= GetDlgItemInt( hDlg, IDC_NBARBRES, &Translated, FALSE ) ;
					return FALSE ;
			
				default :
					return FALSE ;
				}
		}
	return FALSE ;
}
