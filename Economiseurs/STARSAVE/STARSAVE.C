/*  STARSAVE Economiseur d'ecran intergalactique
 */

#include <windows.h>
#include <scrnsave.h>
#include <time.h>
#include <stdlib.h>
#include <commctrl.h>
#include <wing.h>
#include "\dilp\commun\liblpi\liblpi.h"

#include "starsave.h"

#define INLINE	_inline

/* Global used by SCRNSAVE.LIB. Required for all screen savers.
 */
char szAppName[40];


/* Externals defined in SCRNSAVE.LIB. Required for all screen savers.
 */

char _cdecl szIsPassword[22];
char _cdecl szPassword[16];
char _cdecl szDifferentPW[BUFFLEN];
char _cdecl szChangePW[30];
char _cdecl szBadOldPW[BUFFLEN];
HOOKPROC _cdecl fpMessageFilter;

#define NBMAXETOILES	500
#define NBCOULEURS		4
#define LARGEURMAX		100

#define NBMAXPLANETES   5

#define LARGEUR_DEPART  10
#define HAUTEUR_DEPART  10

char    * NomPlanetes[] = {
							"PLANETE1",
							"PLANETE2",
							"PLANETE3",
							"PLANETE4",
							"PLANETE5",
							"PLANETE6",
							"PLANETE7",
							"PLANETE8",
							"PLANETE9",
							"PLANETEA" } ;

#define NBPLANETES	(sizeof(NomPlanetes) / sizeof( NomPlanetes[0]))

typedef struct
    {
    int x ;
    int y ;
    int dx ;
    int dy ;
	int Largeur ;
    int Teinte ;
    }
    T_ETOILES ;

typedef struct
    {
    int x ;
    int y ;
    int dx ;
    int dy ;
    HBITMAP hBitmap ;
    int LargeurBitmap ;
    int HauteurBitmap ;
    int Largeur ;
	}
    T_PLANETE ;


time_t  ltime ;

T_ETOILES   Etoiles[NBMAXETOILES] ;
T_PLANETE   Planete [ NBMAXPLANETES ] ;

HBRUSH		hCouleurs[NBCOULEURS] ;

DWORD       Fond ;
HBRUSH      hFond ;

int         NbEtoiles = NBMAXETOILES ;
int         CentreX ;
int         CentreY ;
int         Droite ;
int         Gauche ;
int         Haut ;
int         Bas ;

extern	HDC	hWinGDC ;
extern	HDC	hMemDC ;
extern	void	InitWinG() ;


INLINE void EffacerPlanete( HDC hDC, T_PLANETE Planete )
{
	int		Largeur, Hauteur ;
	HBRUSH  hABrush ;
	
	Largeur = Planete.LargeurBitmap * Planete.Largeur / 50;
	Hauteur = Planete.HauteurBitmap * Planete.Largeur / 50 ;

    hABrush = SelectObject( hDC, hFond ) ;

    PatBlt( hDC, Planete.x, Planete.y, Largeur, Hauteur, PATCOPY ) ;

    SelectObject( hDC, hABrush ) ;
}

INLINE void AfficherPlanete( HDC hDC, T_PLANETE Planete )
{
//    HDC     hMemDC ;
    HBITMAP hABitmap ;
    int     Largeur, Hauteur ;

//    hMemDC    = CreateCompatibleDC( hDC ) ;
    hABitmap= SelectObject( hMemDC, Planete.hBitmap ) ;

	Largeur = Planete.LargeurBitmap * Planete.Largeur / 50 ;
	Hauteur = Planete.HauteurBitmap * Planete.Largeur / 50 ;

    SetStretchBltMode( hDC, COLORONCOLOR ) ;

//    StretchBlt( hDC, Planete.x, Planete.y, Largeur, Hauteur,
//                hMDC, 0, 0, Planete.LargeurBitmap, Planete.HauteurBitmap,
//                SRCCOPY ) ;
//
    WinGStretchBlt( hDC, Planete.x, Planete.y, Largeur, Hauteur,
                	hMemDC, 0, 0, Planete.LargeurBitmap, Planete.HauteurBitmap ) ;

    SelectObject( hMemDC, hABitmap ) ;
//    DeleteDC( hMemDC ) ;

}

// =========================================================================
// Nouvelle Planete
// =========================================================================
void NouvellePlanete( T_PLANETE * pPlanete )
{
	BITMAP  Bitmap ;
	pPlanete->x        = GetSystemMetrics( SM_CXSCREEN)/2 + rand() % 11 - 5 ;
	pPlanete->y        = GetSystemMetrics( SM_CYSCREEN)/2 + rand() % 11 - 5 ;
	pPlanete->dx       = rand() % 11 - 5 ;
	pPlanete->dy       = rand() % 11 - 5 ;
	pPlanete->Largeur  = rand() % 20 + 1 ;
	pPlanete->hBitmap  = LoadBitmap( hMainInstance,
									 NomPlanetes[ rand() % NBPLANETES ]) ;
		
	GetObject( pPlanete->hBitmap, sizeof( Bitmap), (LPSTR)&Bitmap ) ;
		
	pPlanete->LargeurBitmap = Bitmap.bmWidth ;
	pPlanete->HauteurBitmap = Bitmap.bmHeight ;
}

INLINE void NouvelleEtoile( T_ETOILES * pEtoile )
{
    pEtoile->x = CentreX - ( rand() % (LARGEUR_DEPART * 2)) + LARGEUR_DEPART ;
    pEtoile->y = CentreY - ( rand() % (HAUTEUR_DEPART * 2)) + HAUTEUR_DEPART ;
    
    if ( pEtoile->x < CentreX )
		/* Vers la gauche */
		pEtoile->dx 	  = -(rand() % 10) ;
    else
        /* Vers la droite */
		pEtoile->dx 	  = rand() % 10  ;

    if ( pEtoile->y < CentreY )
        /* Vers le haut */
		pEtoile->dy 	  = -(rand() % 9)  ;
    else
        /* Vers le bas */
		pEtoile->dy 	  = rand() % 9  ;

	pEtoile->Largeur  = 15 ;
    pEtoile->Teinte   = rand() % NBCOULEURS ;
}

void RAZTableau( void )
{
    int i ;

    for ( i = 0; i < NbEtoiles; i++)
        NouvelleEtoile( &Etoiles[i] ) ;
}


INLINE void EffaceEtoile( HDC hDC, int i )
{
	PatBlt( hDC,
			Etoiles[i].x, Etoiles[i].y,
			Etoiles[i].Largeur/10,
			Etoiles[i].Largeur/10,
			BLACKNESS ) ;
}

/* ======================================================================== */
/* Afficher une etoile                                                      */
/* ======================================================================== */
INLINE void AfficheEtoile( HDC hDC, int i )
{
	PatBlt( hDC,
			Etoiles[i].x, Etoiles[i].y,
			Etoiles[i].Largeur/10, 
			Etoiles[i].Largeur/10,
			PATCOPY ) ;
}

/* ======================================================================== */
/* Avance une etoile                                                        */
/* ======================================================================== */
INLINE void Avance( int i )
{
	if (Etoiles[i].Largeur >= LARGEURMAX)
        {
        NouvelleEtoile( &Etoiles[i] ) ;
        return ;
        }
 
    Etoiles[i].x += Etoiles[i].dx ;
    Etoiles[i].y += Etoiles[i].dy ;
	Etoiles[i].Largeur ++ ;
                    
    // Acceleration
	if (Etoiles[i].Largeur % 4 == 0)
        {
		Etoiles[i].dx = Etoiles[i].dx * 5 / 2 ;
		if ( Etoiles[i].dx == 0)
			Etoiles[i].dx = (rand() % 3) - 1 ;

		Etoiles[i].dy = Etoiles[i].dy * 3 / 2 ;
		if ( Etoiles[i].dy == 0)
			Etoiles[i].dy = (rand() % 3) - 1 ;
        }

    if ( Etoiles[i].x < Gauche || Etoiles[i].x > Droite ||
         Etoiles[i].y < Haut   || Etoiles[i].y > Bas )
         NouvelleEtoile( &Etoiles[i] ) ;
}


void AvanceEtoiles( HDC hDC )
{
	int    i, j ;
	HBRUSH hOBrush ;

	for (j = 0; j < NBCOULEURS; j++) // Affichage par teinte pour optimiser
		{
		hOBrush = SelectObject( hDC, hCouleurs[j] ) ;

		for (i = 0; i < NbEtoiles; i++)
			if (Etoiles[i].Teinte == j) 
				{
				EffaceEtoile( hDC, i ) ;

				Avance( i ) ;

				AfficheEtoile( hDC, i ) ;
				}

		SelectObject( hDC, hOBrush ) ;
		}
}


/* ScreenSaverProc - Main entry point for screen saver messages.
 *  This function is required for all screen savers.
 *
 * Params:  Standard window message handler parameters.
 *
 * Return:  The return value depends on the message.
 *
 *  Note that all messages go to the DefScreenSaverProc(), except
 *  for ones we process.
 */
LRESULT FAR PASCAL ScreenSaverProc( HWND hWnd, UINT message, WPARAM wParam,
                                    LPARAM lParam )
{
    int i ;

    switch (message)
    {
    case WM_CREATE :
		InitWinG() ;


        /* Initialisations */
        srand( (unsigned) time(&ltime))  ;

        NbEtoiles = min( NBMAXETOILES,
                         GetPrivateProfileInt((LPSTR)"Etoiles",
                           (LPSTR)"NbEtoiles",
                           NbEtoiles,
                           "LPI_ISL.INI"));

        Droite = GetSystemMetrics( SM_CXSCREEN ) ;
        Gauche = 0 ;
        Bas    = GetSystemMetrics( SM_CYSCREEN ) ;
        Haut   = 0 ;

        CentreX = (Droite - Gauche) / 2 ;
        CentreY = (Bas - Haut) / 2 ;

        RAZTableau(  ) ;

        hFond      = CreateSolidBrush( Fond ) ;

		hCouleurs[0]	= CreateSolidBrush( LPI_RGB_BLANC ) ;
		hCouleurs[1]	= CreateSolidBrush( LPI_RGB_JAUNE ) ;
		hCouleurs[2]	= CreateSolidBrush( LPI_RGB_CYAN ) ;
		hCouleurs[3]	= CreateSolidBrush( LPI_RGB_ROUGE ) ;

        /* =========================================== Timers pour les bitmaps */
        for ( i = 0; i < NBMAXPLANETES; i++)
        	{
        	Planete[i].hBitmap = NULL ;
//        	SetTimer( hWnd, i, rand()%10000, (TIMERPROC)NULL ) ;
        	}
        	
        // Timer pour les etoiles
		SetTimer( hWnd, 20, 50, (TIMERPROC)NULL ) ;
        break ;


    case WM_TIMER :
  		{
		HDC	hDC	;
		hDC	=	GetDC( hWnd ) ;
		//PatBlt( hWinGDC, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ), BLACKNESS ) ;

  		AvanceEtoiles( hDC ) ; 
  		
  		for ( i = 0; i < NBMAXPLANETES; i++)
			{
	        if (Planete[i].hBitmap == NULL )
		            NouvellePlanete( &Planete[i] ) ;
	
	        EffacerPlanete( hDC, Planete[i]) ;

	        if (Planete[i].Largeur < 180)
	            {
	            Planete[i].x += Planete[i].dx ;
	            Planete[i].y += Planete[i].dy ;
	            Planete[i].Largeur ++ ;
	            }
	        else
	            {
	            //SetTimer( hWnd, wParam, rand(), (TIMERPROC)NULL ) ;
	            DeleteObject( Planete[i].hBitmap ) ;
	            Planete[i].hBitmap = NULL ;
	            }

	        AfficherPlanete( hDC, Planete[i]) ;
        	}

		//WinGBitBlt( hDC, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ),
		//			hWinGDC, 0, 0 ) ;

  		ReleaseDC( hWnd,  hDC ) ;
		}
  		break ; 	
/*        if (wParam == 20)
            AvanceEtoiles() ;
        else
        	{
	        if (Planete[wParam].hBitmap == NULL )
	            NouvellePlanete( &Planete[wParam], hWnd, wParam ) ;
	
	        EffacerPlanete( Planete[wParam]) ;
	
	        if (Planete[wParam].Largeur < 80)
	            {
	            Planete[wParam].x += Planete[wParam].dx ;
	            Planete[wParam].y += Planete[wParam].dy ;
	            Planete[wParam].Largeur ++ ;
	            }
	        else
	            {
	            SetTimer( hWnd, wParam, rand(), (TIMERPROC)NULL ) ;
	            DeleteObject( Planete[wParam].hBitmap ) ;
	            Planete[wParam].hBitmap = NULL ;
	            }
	
	        AfficherPlanete( Planete[wParam]) ;
        	}
        break ;
*/

    case WM_DESTROY:
        for ( i = 0; i < NBMAXPLANETES; i++)
            if (Planete[i].hBitmap)
                DeleteObject( Planete[i].hBitmap) ;

		DeleteObject( hCouleurs[0]) ;
		DeleteObject( hCouleurs[1]) ;
		DeleteObject( hCouleurs[2]) ;
		DeleteObject( hCouleurs[3]) ;

        PostQuitMessage( 0 );
        break;

    case WM_WININICHANGE :
        InvalidateRect( hWnd, (LPRECT)NULL, TRUE ) ;
        break ;

    case WM_QUERYOPEN :
        return FALSE ;

    default :
        return DefScreenSaverProc( hWnd, message, wParam, lParam );
        break;
    }
    return(0L);
}





/* RegisterDialogClasses -- Entry point for registering window
 * classes required by configuration dialog box.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL WINAPI RegisterDialogClasses(HINSTANCE hInst)
{
	InitCommonControls() ;
    return TRUE;
}


/* ScreenSaverConfigureDialog -- Dialog box function for configuration
 * dialog.
 *
 * Params:  hWnd -- Handle to window
 *
 * Return:  None
 */
BOOL CALLBACK ScreenSaverConfigureDialog( HWND hDlg, UINT Message,
                                          WPARAM wParam, LPARAM lParam)
{
    int     PosScroll ;
    char    Texte[20] ;

    switch( Message )
        {
        case WM_INITDIALOG :
			NbEtoiles = min( NBMAXETOILES,
							 GetPrivateProfileInt((LPSTR)"Etoiles",
							   (LPSTR)"NbEtoiles",
							   NbEtoiles,
							   "LPI_ISL.INI"));
				 SetDlgItemInt( hDlg, IDB_TEXTE, NbEtoiles, FALSE ) ;
            SetScrollRange( GetDlgItem( hDlg, IDB_SCROLL), SB_CTL, 0, NBMAXETOILES,
                            TRUE  ) ;
            SetScrollPos( GetDlgItem( hDlg, IDB_SCROLL), SB_CTL, NbEtoiles,
                          TRUE) ;
            break ;

        case WM_HSCROLL :
            PosScroll = GetScrollPos( GetDlgItem( hDlg, IDB_SCROLL), SB_CTL ) ;

            switch ( wParam )
                {
                case SB_LINEUP :
                    PosScroll -- ;
                    break ;

                case SB_LINEDOWN :
                    PosScroll ++ ;
                    break ;

                case SB_PAGEDOWN :
                    PosScroll += 10 ;
                    break ;

                case SB_PAGEUP :
                    PosScroll -= 11 ;
                    break ;

                case SB_THUMBPOSITION :
                case SB_THUMBTRACK :
                    PosScroll = LOWORD( lParam ) ;
                    break ;
                }

            if (PosScroll < 0)
                PosScroll = 0 ;

            if (PosScroll >= NBMAXETOILES)
                PosScroll = NBMAXETOILES - 1 ;

            SetDlgItemInt( hDlg, IDB_TEXTE, PosScroll, FALSE ) ;

            SetScrollPos( GetDlgItem( hDlg, IDB_SCROLL), SB_CTL,
                          PosScroll, TRUE ) ;
            break ;

        case WM_COMMAND :
            switch( wParam )
                {
                case IDCANCEL :
                    EndDialog( hDlg, FALSE ) ;
                    break ;

                case IDOK :
                    NbEtoiles = GetScrollPos( GetDlgItem( hDlg, IDB_SCROLL),
                                              SB_CTL ) ;

                    wsprintf( Texte, "%d", NbEtoiles ) ;

                    WritePrivateProfileString((LPSTR)"Etoiles",
                                              (LPSTR)"NbEtoiles",
                                              Texte,
                                             "LPI_ISL.INI");

                    PostMessage( hMainWindow, WM_WININICHANGE, 0, 0L ) ;
                    EndDialog( hDlg, TRUE ) ;
                    break ;
                }
                break;

        default :
            return FALSE ;
        }

    return TRUE ;
}
