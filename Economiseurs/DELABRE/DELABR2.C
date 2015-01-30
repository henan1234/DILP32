/*  STARSAVE Economiseur d'ecran intergalactique
 */

#include <windows.h>
#include <scrnsave.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

#include "resource.h"

#define INLINE	_inline

/* Global used by SCRNSAVE.LIB. Required for all screen savers.
 */
char szAppName[40];
HINSTANCE _cdecl hMainInstance;
HWND _cdecl hMainWindow;
char _cdecl szName[TITLEBARNAMELEN];
char _cdecl szIsPassword[22];
char _cdecl szIniFile[MAXFILELEN];
char _cdecl szScreenSaver[22];
char _cdecl szPassword[16];
char _cdecl szDifferentPW[BUFFLEN];
char _cdecl szChangePW[30];
char _cdecl szBadOldPW[BUFFLEN];
char _cdecl szHelpFile[MAXFILELEN];
char _cdecl szNoHelpMemory[BUFFLEN];
UINT _cdecl MyHelpMessage;
HOOKPROC _cdecl fpMessageFilter;

#define LARGEUR	GetSystemMetrics(SM_CXSCREEN)
#define HAUTEUR	GetSystemMetrics(SM_CYSCREEN)
#define MAX_DELAI	200
#define MIN_DELAI	50
#define PI			3.14159265359
#define NB_MAX_GOUTTES	10
// ======================================================= Types
typedef struct
		{
		POINT	Depart ;
		int		LargeurDepart ;
		POINT	Pos ;
		int		Largeur ;
		int		LongueurReduit ;
		int		LongueurCoule ;
		int		LongueurGoutte ;
		int		LargeurGoutte ;
		DWORD	RasterOp ;
		}
		GOUTTE ;

// Valeurs de parametrage
int		Grosseur, Rapidite ;
GOUTTE	Goutte[NB_MAX_GOUTTES] ;


// 
 
int Alea( int Min, int Max )
{
	return Min + rand() % ( Max - Min + 1 ) ;
}
void CouleurEnHaut( HDC hDC )
{
	HBRUSH hOldBrush ;
	HBRUSH hBrush ;
	static int CompteTours = 0 ;
	
	
	if ( CompteTours ++  )	
		{
		if ( CompteTours > HAUTEUR )
			CompteTours = 0 ;
			
		return ;
		}		
	hBrush = CreateSolidBrush( RGB(Alea( 0, 255 ), Alea( 0, 255 ), Alea( 0, 255 )) ) ;
	
	hOldBrush = SelectObject( hDC, hBrush ) ;
	PatBlt(hDC, 0, 2, LARGEUR, 8, PATCOPY )	;
	SelectObject( hDC, hOldBrush ) ;
	DeleteObject( hBrush ) ;
}

void NouvelleGoutte( GOUTTE * pGoutte )
{
	pGoutte->Largeur	= Alea( 10, Grosseur ) ;
	pGoutte->LargeurDepart = pGoutte->Largeur ;
	pGoutte->Depart.x	= Alea(0, LARGEUR-pGoutte->Largeur) ;
	
	pGoutte->LongueurReduit = (pGoutte->Largeur/2) -Alea(1,4) ;
	pGoutte->LongueurCoule	= Alea( 20, 80 ) ;
	pGoutte->LargeurGoutte	= Alea( 5, pGoutte->Largeur) ;
	pGoutte->LongueurGoutte = 	pGoutte->LargeurGoutte ;
	
	pGoutte->Depart.y = Alea( 0, HAUTEUR-(pGoutte->LongueurReduit + pGoutte->LongueurCoule + pGoutte->LongueurGoutte)) ;
	
	pGoutte->Pos = pGoutte->Depart ;
	
	switch ( Alea(0,10))
		{
		case 0	:
			pGoutte->RasterOp = SRCAND ;
			break ;
		case 1	:
			pGoutte->RasterOp = SRCPAINT ;
			break ;
		default	:
			pGoutte->RasterOp = SRCCOPY ;
			break ;
		}
}

void AvanceGoutte( GOUTTE * pGoutte )
{
	if ( pGoutte->LongueurReduit )
		{
		// Avance dans la phase de reduction de la goutte
		(pGoutte->Pos.y)	++ ;
		
		(pGoutte->Largeur)	=(int)(	(double)(pGoutte->LargeurDepart) 
								* sin(	(double)pGoutte->LongueurReduit
										*PI
										/(double)pGoutte->LargeurDepart )) ;
		pGoutte->Pos.x = pGoutte->Depart.x + (pGoutte->LargeurDepart - pGoutte->Largeur) / 2 ;
		
		(pGoutte->LongueurReduit) -- ;
		return ;
		}
		
	if ( pGoutte->LongueurCoule )
		{
		// Phase d'ecoulement
		(pGoutte->Pos.y) ++ ;
		(pGoutte->LongueurCoule) -- ;
		return ;
		}
	
	// La goutte s'arrondi
	pGoutte->Pos.y ++ ;	
	pGoutte->Largeur =	(int)(sin( (double)pGoutte->LongueurGoutte*PI/(double)pGoutte->LargeurGoutte )
					  * (double)pGoutte->LargeurGoutte) / 2;
		
	pGoutte->Pos.x = pGoutte->Depart.x + (pGoutte->LargeurDepart - pGoutte->Largeur) / 2 ;
	
	pGoutte->LongueurGoutte -- ;
}

void DelabreEcran( HDC hDC, GOUTTE * pGoutte )
{	
	// Controles
	if ( (pGoutte->LongueurReduit + pGoutte->LongueurCoule + pGoutte->LongueurGoutte) == 0 )
		// Nouvelle goutte
		NouvelleGoutte( pGoutte ) ;

	StretchBlt( hDC,
				pGoutte->Pos.x, pGoutte->Pos.y,
				pGoutte->Largeur, 3,
				hDC, pGoutte->Depart.x, pGoutte->Depart.y,
			    pGoutte->LargeurDepart, 2,
			    pGoutte->RasterOp ) ;


	// Avance la goutte
	AvanceGoutte( pGoutte ) ;

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
	time_t		ltime ;
	PAINTSTRUCT	Ps ;
	HDC 		hDC ;
	int			i ;

    switch (message)
    {
    case WM_ERASEBKGND :
    	return TRUE ;
    
    case WM_CREATE :
    	Rapidite	= GetPrivateProfileInt("Degouline", "Rapidite", 60, "LPI_ISL.INI") ;
		Grosseur	= GetPrivateProfileInt("Degouline", "Grosseur", 50, "LPI_ISL.INI") ;
		
        srand( (unsigned) time(&ltime))  ;
        
        for ( i = 0; i < NB_MAX_GOUTTES; i++)
        	NouvelleGoutte( &Goutte[i] ) ;
        
        SetTimer( hWnd, 1, (MAX_DELAI+MIN_DELAI)-Rapidite, (TIMERPROC)NULL ) ;
        break ;

    case WM_PAINT :
    	BeginPaint( hWnd, &Ps ) ;
		PatBlt( Ps.hdc, 0, 0, LARGEUR, 10, BLACKNESS ) ;
		PatBlt( Ps.hdc, 0, 0, 1, HAUTEUR, BLACKNESS ) ;
		PatBlt( Ps.hdc, LARGEUR-1, 0, 1, HAUTEUR, BLACKNESS ) ;
    	EndPaint( hWnd, &Ps ) ;
    	break ;
    	
    case WM_TIMER :
    	hDC =GetDC( hWnd ) ;
		CouleurEnHaut(hDC) ;
		for ( i = 0; i < NB_MAX_GOUTTES; i++)
        	DelabreEcran( hDC, &Goutte[i] ) ;
		ReleaseDC( hWnd, hDC ) ;
        break ;

    case WM_DESTROY:
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
BOOL RegisterDialogClasses(HINSTANCE hInst)
{
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
	int	Rapidite ;
	int	Grosseur ;
	int Min, Max, Pos ;
	char Texte[10] ;
	
    switch( Message )
        {
        case WM_INITDIALOG :
            Rapidite	= GetPrivateProfileInt("Degouline", "Rapidite", MAX_DELAI, "LPI_ISL.INI") ;
			Grosseur	= GetPrivateProfileInt("Degouline", "Grosseur", 50, "LPI_ISL.INI") ;
			
			SetScrollRange( GetDlgItem( hDlg, IDC_RAPIDITE ), SB_CTL, MIN_DELAI, MAX_DELAI, TRUE ) ;
			SetScrollPos( GetDlgItem( hDlg, IDC_RAPIDITE ), SB_CTL, Rapidite, TRUE ) ;
			
			SetScrollRange( GetDlgItem( hDlg, IDC_GROSSEUR ), SB_CTL, 10, 100, TRUE ) ;
			SetScrollPos( GetDlgItem( hDlg, IDC_GROSSEUR), SB_CTL, Grosseur, TRUE ) ;
			break ;


		case WM_HSCROLL :
			GetScrollRange( HIWORD( lParam ), SB_CTL, &Min, &Max ) ;
			Pos = GetScrollPos( HIWORD( lParam ), SB_CTL ) ;
			switch( wParam )
				{
				case SB_LINEUP :
					Pos -- ;
					break ;
				case SB_LINEDOWN :
					Pos ++ ;
					break ;
				case SB_PAGEUP :
					Pos += ( Max - Min ) / 10 ;
					break ;
				case SB_PAGEDOWN :
					Pos -= ( Max - Min ) / 10 ;
					break ;
				case SB_THUMBTRACK :
					Pos = LOWORD( lParam ) ;
					break ;				
				}
				
			if ( Pos < Min )
				Pos = Min ;
			else
				if ( Pos > Max )
					Pos = Max ;
					
			SetScrollPos( HIWORD( lParam ), SB_CTL, Pos, TRUE ) ;
			break ;
        
        case WM_COMMAND :
            switch( wParam )
                {
                case IDCANCEL :
                    EndDialog( hDlg, FALSE ) ;
                    break ;

                case IDOK :
                	Rapidite = GetScrollPos( GetDlgItem( hDlg, IDC_RAPIDITE ), SB_CTL ) ;
                	Grosseur = GetScrollPos( GetDlgItem( hDlg, IDC_GROSSEUR ), SB_CTL ) ;
                	
                	itoa( Rapidite, Texte, 10 ) ;
					WritePrivateProfileString("Degouline", "Rapidite", Texte, "LPI_ISL.INI") ;
                    
                    itoa( Grosseur, Texte, 10 ) ;
					WritePrivateProfileString("Degouline", "Grosseur", Texte, "LPI_ISL.INI")  ;
					EndDialog( hDlg, TRUE ) ;
                    break ;
                }
                break;

        default :
            return FALSE ;
        }

    return TRUE ;
}
