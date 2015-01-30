/*  Autoscr	: 	Economiseur d'ecran automate
 */

#include <windows.h>
#include <windowsx.h>
#include <scrnsave.h>
#include <commdlg.h>
#include <commctrl.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <io.h>

#define LIFE

#include "resource.h"
#define _cdecl
/* Global used by SCRNSAVE.LIB. Required for all screen savers.
 */
char szAppName[40];
char _cdecl szIsPassword[22];
char _cdecl szPassword[16];
char _cdecl szDifferentPW[BUFFLEN];
char _cdecl szChangePW[30];
char _cdecl szBadOldPW[BUFFLEN];
HOOKPROC _cdecl fpMessageFilter;

#define CHECK_BOUNDS( x, min, max )		{ if ( (x) < (min) ) (x) = (min) ; else if ((x) > (max)) (x) = (max) ; }
#define LARGEUR	GetSystemMetrics(SM_CXSCREEN)
#define HAUTEUR	GetSystemMetrics(SM_CYSCREEN)
#define MAX_DELAI		200
#define MIN_DELAI		50
#define NB_MAX_GOUTTES	10
#define NB_MAX_BITMAP 	20

// ======================================================= Types
typedef BYTE	FAR *	LIGNE ;
typedef LIGNE	FAR	*	LPLIGNE ;
typedef LIGNE	FAR *	TABLEAU ;
typedef TABLEAU FAR *	LPTABLEAU ;


// ========================================== Variables globales
int		NbLignes	= 200 ;
int		NbColonnes  = 200 ;
int		NbEtats		= 8 ;
int		NoLigne		= 0 ;
unsigned long NbChanges	= 0 ;
unsigned long NbCases	= 0 ;

int		Grille ;

TABLEAU Ancien ;
TABLEAU Nouveau ;

COLORREF	Couleurs[16] = {
							RGB(0x00, 0x00, 0x00),
							RGB(0x00, 0xFF, 0x00),
							RGB(0x00, 0x00, 0x20),
							RGB(0x00, 0xFF, 0x20),
							RGB(0x00, 0x00, 0x40),
							RGB(0x00, 0xFF, 0x40),
							RGB(0x00, 0x00, 0x60),
							RGB(0x00, 0xFF, 0x60),
							RGB(0x00, 0x00, 0x80),
							RGB(0x00, 0xFF, 0x80),
							RGB(0x00, 0x00, 0xa0),
							RGB(0x00, 0xFF, 0xa0),
							RGB(0x00, 0x00, 0xc0),
							RGB(0x00, 0xFF, 0xc0),
							RGB(0x00, 0x00, 0xe0),
							RGB(0x00, 0xFF, 0xe0)
						   };     

HBRUSH		hBrushes[16] ;



// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
_inline int Alea( int Min, int Max )
{
	return Min + (rand()+GetCurrentTime()) % ( Max - Min + 1 ) ;
	
}


_inline BYTE Incremente( BYTE Valeur, BYTE Max )
{
	if ( Valeur >= Max )
		return 0 ;
	else
		return Valeur + 1 ;
}


BOOL VerifVersion()
{
	char	Buffer[100] ;
	DWORD	Taille	;

	// Si c'est moi, je vais quand meme pas payer...
	Taille	=	sizeof( Buffer ) ;
	GetUserName( Buffer, &Taille) ;

	CharUpper( Buffer ) ;

	if ( lstrcmp( Buffer, "PILLONI" ) == 0)
		return TRUE ;


	if ( lstrcmp( Buffer, "LUCIEN" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LULU" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LP" ) == 0)
		return TRUE ;

	if ( lstrcmp( Buffer, "LPI" ) == 0)
		return TRUE ;

	// Verification de la date
/*	time( &tim ) ;
	ptm	=	localtime( &tim ) ;

	if ( ptm->tm_year >= 97 && ptm->tm_mon >= 3 && ptm->tm_mday >= 3 )
		{
		exit(0) ;
		}
*/

	return TRUE ;
}


void LitCouleurs()
{
	int	i ;
	char	Rubrique[20] ;
	char	Valeur[20] ;
	char	Defaut[20] ;
	
	for ( i = 0; i < 16; i++)
		{
		wsprintf( Defaut, "%lu", (unsigned long) Couleurs[i] ) ;
		wsprintf( Rubrique, "Couleur%d", i ) ;
		
		GetPrivateProfileString( "AutoScr", Rubrique, Defaut, Valeur, sizeof( Valeur ), "LPI_ISL.INI" ) ;
		Couleurs[i] = atol( Valeur ) ;
		}
}

void EcritCouleurs()
{
	int i ;
	char	Rubrique[20] ;
	char	Valeur[20] ;
	
	for ( i = 0; i < 16; i++)
		{
		wsprintf( Valeur, "%lu", (unsigned long) Couleurs[i] ) ;
		wsprintf( Rubrique, "Couleur%d", i ) ;
		
		WritePrivateProfileString( "AutoScr", Rubrique, Valeur, "LPI_ISL.INI" ) ;
		}
}

void	InitTableau( TABLEAU FAR * pTableau, int NbLignes, int NbColonnes )
{
	int	i ;
	
	(*pTableau) = (TABLEAU)GlobalAllocPtr( GMEM_FIXED, sizeof(LIGNE)*NbLignes) ;
	
	for (i = 0; i < NbLignes; i++)
		// Alloue une ligne
		(*pTableau)[i] = (LIGNE)GlobalAllocPtr(GMEM_FIXED | GMEM_ZEROINIT, sizeof(BYTE)*NbColonnes ) ;
}

void ValeurInitiales( TABLEAU Tableau, int NbLignes, int NbColonnes, int NbEtats )
{
	int i, j ;
	
	for ( j = 0; j < NbColonnes; j++ )
		for ( i = 0; i < NbLignes; i++)
#ifdef LIFE
		Tableau[i][j] = Alea( 0, 1 ) ;
#else
		Tableau[i][j] = Alea( 0, NbEtats-1 ) ;
#endif
}

_inline void AfficheCase(HDC hDC, int x, int y, int Couleur )
{
	SelectObject( hDC, hBrushes[Couleur] ) ;
	
    PatBlt( hDC, x, y, 1, 1, PATCOPY ) ;
}


// retourne vrai si la voisine = case + 1
_inline BOOL Traite( TABLEAU Tableau, int i, int j, int x, int y)
{
    if (x < 0)
        x = NbColonnes - 1 ;
    else
        if ( x >= NbColonnes )
            x = 0 ;

    if (y < 0)
        y = NbLignes - 1 ;
    else
        if (y >= NbLignes)
            y = 0 ;

    if (Tableau[i][j] + 1== Tableau[x][y])
        return TRUE ;
    else
        if ((Tableau[i][j] == NbEtats-1 ) && (Tableau[x][y] == 0))
            return TRUE ;
        else
            return FALSE ;
}

void Copie( TABLEAU Dest, TABLEAU Source )
{
	int i, j ;
	
	for ( i = 0; i < NbLignes; i++)
		for ( j = 0; j < NbColonnes; j++ )
			Dest[i][j] = Source[i][j] ;
}

int	NbVoisines( TABLEAU Tab, int NoLigne, int NoColonne )
	{
	int	XDroite = NoColonne  +1 ;
	int XGauche	= NoColonne	 -1 ;
	int	YHaut	= NoLigne	 -1 ;
	int YBas	= NoLigne	+1 ;

	if ( XDroite >= NbColonnes )
		XDroite = 0 ;

	if ( XGauche < 0 )
		XGauche = NbColonnes - 1 ;

	if ( YHaut < 0 )
		YHaut = NbLignes - 1 ;

	if ( YBas >= NbLignes )
		YBas	=	0 ;

	return	Tab[YHaut][XGauche]
		+	Tab[YHaut][NoColonne]
		+	Tab[YHaut][XDroite]
		+	Tab[YBas][XGauche]
		+	Tab[YBas][NoColonne]
		+	Tab[YBas][XDroite]
		+	Tab[NoLigne][XDroite]
		+	Tab[NoLigne][XGauche] ;
	}

void SequenceAnimation( HDC hDC )
{
	int		Colonne ;
#ifdef LIFE
	BOOL Reinitialiser = FALSE ;
	static DWORD	DeltaM1 = 0 ;
	static DWORD	DeltaM2 = 0 ;
	static DWORD	DeltaM3 = 0 ;

#else
	BOOL	Change ;
#endif
	
	for ( NoLigne = 0; NoLigne < NbLignes; NoLigne ++ )
    for (Colonne = 0; Colonne < NbColonnes; Colonne++)
        {
#ifdef LIFE
		Nouveau[NoLigne][Colonne] = Ancien[NoLigne][Colonne] ;
		switch( NbVoisines( Ancien, NoLigne, Colonne) )
			{
			case 0:
			case 1:
				if  (Ancien[NoLigne][Colonne] != 0 )
					{
					Nouveau[NoLigne][Colonne]	=	0 ;
					AfficheCase( hDC, Colonne, NoLigne, Nouveau[NoLigne][Colonne] ) ;
					NbChanges ++ ;
					}
				break ;

			case 2:
				break ;

			case 3:
				if ( Ancien[NoLigne][Colonne] != 1 )
					{
					Nouveau[NoLigne][Colonne]	=	1 ;
					AfficheCase( hDC, Colonne, NoLigne, Nouveau[NoLigne][Colonne] ) ;
					NbChanges ++ ;
					}
				break ;

			default:
				if ( Ancien[NoLigne][Colonne] != 0 )
					{
					Nouveau[NoLigne][Colonne]	=	0 ;
					AfficheCase( hDC, Colonne, NoLigne, Nouveau[NoLigne][Colonne] ) ;
					NbChanges ++ ;
					}
				break ;
			}

#else
        Change =     Traite( Ancien, NoLigne, Colonne, NoLigne, Colonne+1) ;

        if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne, Colonne-1) ;

        if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne+1, Colonne) ;

        if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne-1, Colonne) ;

		// En diagonal
		if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne-1, Colonne-1) ;
		if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne-1, Colonne+1) ;
		if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne+1, Colonne-1) ;
		if (! Change)
            Change = Traite( Ancien, NoLigne, Colonne, NoLigne+1, Colonne+1) ;

        if (Change)
            {
            Nouveau[NoLigne][Colonne] = Incremente( Ancien[NoLigne][Colonne], LOBYTE(NbEtats-1) ) ;
            AfficheCase( hDC, Colonne, NoLigne, Nouveau[NoLigne][Colonne] ) ;          	
            NbChanges ++ ;
            }
        else
			if ( Ancien[NoLigne][Colonne] != Nouveau[NoLigne][Colonne] )
	        	{
	        	Nouveau[NoLigne][Colonne] = Ancien[NoLigne][Colonne] ;
	            AfficheCase( hDC, Colonne, NoLigne, Nouveau[NoLigne][Colonne] ) ;
	            }  	
#endif
		}

        
//    if (NoLigne < NbLignes-1)
  //      NoLigne ++ ;
    //else
        {
        TABLEAU	Memo ;
        char Buffer[1000] ;
		
        Memo = Ancien ;
        Ancien = Nouveau ;
        Nouveau = Memo ;
        NoLigne = 0 ;
#ifdef LIFE
		if ( NbChanges == 0 )
			Reinitialiser = TRUE ;
		else
			{
			if ( NbChanges == DeltaM2 && DeltaM1==DeltaM3 )
				Reinitialiser = TRUE ;
			}

		DeltaM3 = DeltaM2 ;
		DeltaM2	= DeltaM1 ;
		DeltaM1	= NbChanges ;

		if (Reinitialiser )
#else        
        if ((NbChanges == 0) ||		// Situation bloquee
        	(NbChanges >= NbCases))	// Des spirales partout
#endif
        	{	
	        ValeurInitiales( Ancien, NbLignes, NbColonnes, NbEtats ) ;
	    	Copie( Nouveau, Ancien ) ;
	    	}
	    	
	    SelectObject( hDC, GetStockObject( ANSI_VAR_FONT )) ;
		wsprintf( Buffer, "%ld/%ld", (long)NbChanges, (long)NbCases ) ;
		TextOut( hDC, 10, 10, Buffer, strlen( Buffer) ) ;
    	
		NbChanges = 0 ;

		}
}

void CreerBrosses()
{
	int i ;
	
	for ( i = 0; i < 16; i++)
		hBrushes[i] = CreateSolidBrush( Couleurs[i] ) ;
}

void DetruitBrosses()
{
	int i ;
	
	for ( i = 0; i < 16; i++)
		DeleteObject(hBrushes[i]) ;
}


void PrepareDC( HDC hDC, RECT R )
{   
	SetMapMode( hDC, MM_ANISOTROPIC ) ;

    //SetBkMode( hDC, TRANSPARENT ) ;
    //SetTextColor( hDC, RGB(0xFF, 0xFF, 0xFF)) ;
        
	SetViewportExtEx( hDC, R.right - R.left, R.top - R.bottom, NULL ) ;
	SetViewportOrgEx( hDC, R.left, R.top, NULL ) ;
	
	SetWindowExtEx( hDC, NbColonnes , NbLignes, NULL ) ;
	SetWindowOrgEx( hDC, 0, NbLignes, NULL ) ;
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
	HDC 			hDC ;
	RECT			R ;
	HBRUSH			hOldBrush ;
	
    switch (message)
    {
    case WM_CREATE :
    	SetTimer( hWnd, 1, 1, NULL ) ;
    	
    	LitCouleurs() ;
    	CreerBrosses() ;
    	NbEtats = GetPrivateProfileInt("AutoScr", "Etats", 8, "LPI_ISL.INI") ;
    	Grille	= GetPrivateProfileInt("AutoScr", "Grille", 200, "LPI_ISL.INI") ;
    	CHECK_BOUNDS( Grille, 10, min(LARGEUR, HAUTEUR)) ;
		NbLignes = Grille ;
	
		NbColonnes = Grille ;
		
		NbCases = ((unsigned long)NbLignes) * ((unsigned long)NbColonnes) ;
		NbChanges = 0 ;
    	InitTableau( &Ancien, NbLignes, NbColonnes ) ;
    	InitTableau( &Nouveau, NbLignes, NbColonnes ) ;

		VerifVersion() ;
    	
    	srand((unsigned int)GetCurrentTime()) ;
    	ValeurInitiales( Ancien, NbLignes, NbColonnes, NbEtats ) ;
    	break ;

    case WM_TIMER :
    	hDC = GetDC( hWnd ) ;
    	hOldBrush = SelectObject( hDC, hBrushes[0]) ;
    	GetClientRect( hWnd, &R ) ;
        PrepareDC( hDC, R ) ;
        
    	SequenceAnimation( hDC ) ;
		SelectObject( hDC, hOldBrush ) ;
        ReleaseDC( hWnd, hDC ) ;
        break ;

	case WM_ERASEBKGND :
		GetClientRect(hWnd, &R) ;
		FillRect((HDC)wParam, &R, hBrushes[0] ) ;
		return TRUE ;
		
    case WM_DESTROY:
    	DetruitBrosses() ;
    	PostQuitMessage( 0 );
        break;

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



void CentreFenetre( HWND hFenetre )
{
	RECT R ;
	int	LargeurEcran = GetSystemMetrics( SM_CXSCREEN ) ;
	int	HauteurEcran = GetSystemMetrics( SM_CYSCREEN ) ;
	int	LargeurFenetre, HauteurFenetre ;
	
	GetWindowRect( hFenetre, &R ) ;
	
	LargeurFenetre = R.right - R.left ;
	HauteurFenetre = R.bottom - R.top ;
	
	R.left = (LargeurEcran - LargeurFenetre) / 2 ;
	R.top = (HauteurEcran - HauteurFenetre) / 2 ;
	
	SetWindowPos( hFenetre, HWND_TOP, R.left, R.top, LargeurFenetre, HauteurFenetre,
				  SWP_NOSIZE ) ;
}


BOOL CALLBACK DlgAbout( HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	RECT		R ;
	PAINTSTRUCT	Ps ;
	HDC			hMemDC ;
	HBITMAP		hBitmap ;
	HBITMAP		hOldBitmap ;
	BITMAP		sBitmap ;
	
	switch( Message )
		{
		case WM_INITDIALOG :
			CentreFenetre( hDlg ) ;
			return TRUE ;
			
		case WM_COMMAND :
			switch( wParam)
				{
				case IDOK :
					EndDialog( hDlg, TRUE ) ;
					break ;
				default :
					return FALSE ;
				}
			break ;
		case WM_PAINT :
			BeginPaint( hDlg, &Ps ) ;
			GetClientRect( hDlg, &R ) ;
			hBitmap		= LoadBitmap( hMainInstance, MAKEINTRESOURCE( IDB_APROPOS )) ;
			hMemDC		= CreateCompatibleDC( Ps.hdc ) ;
			hOldBitmap	= SelectObject( hMemDC, hBitmap ) ;
			GetObject( hBitmap, sizeof( sBitmap ), (LPSTR)&sBitmap ) ;
			
			BitBlt(Ps.hdc, (R.right-R.left-sBitmap.bmWidth) / 2, (R.bottom-R.top-sBitmap.bmHeight)/2,
				   sBitmap.bmWidth, sBitmap.bmHeight,
				   hMemDC, 0, 0, SRCCOPY ) ;
				   
			SelectObject( hMemDC, hOldBitmap ) ;
			DeleteDC( hMemDC ) ;
			DeleteObject( hBitmap ) ;
			EndPaint( hDlg, &Ps ) ;
			break ;
			
		default :
			return FALSE ;
		}
		
	return TRUE ;
}

void BoiteAPropos( HWND hDlg )
{
	FARPROC	lProc = MakeProcInstance( DlgAbout, hMainInstance ) ;
	
	DialogBox( hMainInstance, MAKEINTRESOURCE( IDD_APROPOS ), hDlg, lProc ) ;
	FreeProcInstance( lProc ) ;
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
	char	Texte[30] ;
	int		Pos ;
	CHOOSECOLOR CouleursStruct ;
	
    switch( Message )
        {
        case WM_INITDIALOG :
        	CentreFenetre(hDlg) ;
            NbEtats = GetPrivateProfileInt("AutoScr", "Etats", 8, "LPI_ISL.INI") ;
            CHECK_BOUNDS( NbEtats, 2, 16 ) ;

			SendDlgItemMessage( hDlg, IDC_ETATS, TBM_SETRANGE, TRUE, MAKELPARAM( 2, 16 )) ;
			SendDlgItemMessage( hDlg, IDC_ETATS, TBM_SETPOS, TRUE, (LPARAM)( NbEtats )) ;
			SetDlgItemInt( hDlg, IDC_NB_ETAT, NbEtats, FALSE ) ;
			
            Grille = GetPrivateProfileInt("AutoScr", "Grille", HAUTEUR/2, "LPI_ISL.INI") ;
            CHECK_BOUNDS(Grille, 50, min(LARGEUR, HAUTEUR)) ;
			SendDlgItemMessage( hDlg, IDC_GRILLE, TBM_SETRANGE, TRUE, MAKELPARAM( 10, min(LARGEUR, HAUTEUR) )) ;
			SendDlgItemMessage( hDlg, IDC_GRILLE, TBM_SETPOS, TRUE, (LPARAM)( Grille )) ;
			SetDlgItemInt( hDlg, IDC_NB_GRILLE, Grille, FALSE ) ;
            
            LitCouleurs() ;
			break ;

		case WM_HSCROLL :
			Pos = SendMessage( (HWND)lParam, TBM_GETPOS, 0, 0 ) ;
			SetDlgItemInt( hDlg, GetWindowLong((HWND)lParam, GWL_ID)+1, Pos, FALSE ) ;
			break ;
        
        case WM_COMMAND :
            switch( wParam )
                {
                case IDCANCEL :
                    EndDialog( hDlg, FALSE ) ;
                    break ;

                case IDOK :
                	NbEtats		= SendDlgItemMessage( hDlg, IDC_ETATS, TBM_GETPOS, 0, 0  ) ;
                	Grille		= SendDlgItemMessage( hDlg, IDC_GRILLE, TBM_GETPOS, 0, 0  ) ;
                	
                	itoa( NbEtats, Texte, 10 ) ;
					WritePrivateProfileString("AutoScr", "Etats", Texte, "LPI_ISL.INI") ;
                    
                    itoa( Grille, Texte, 10 ) ;
					WritePrivateProfileString("AutoScr", "Grille", Texte, "LPI_ISL.INI")  ;
					
					EndDialog( hDlg, TRUE ) ;
                    break ;
                    
                case IDC_COULEURS :
                	memset( &CouleursStruct, 0, sizeof( CouleursStruct )) ;
                	
                	CouleursStruct.lStructSize	= sizeof( CouleursStruct ) ;
                	CouleursStruct.hwndOwner	= hDlg ;
                	CouleursStruct.hInstance	= hMainInstance ;
                	CouleursStruct.rgbResult	= Couleurs[0] ;
                	CouleursStruct.lpCustColors	= Couleurs ;
                	CouleursStruct.Flags		= CC_FULLOPEN |  CC_RGBINIT ;
                	if ( ChooseColor(& CouleursStruct))
                		EcritCouleurs() ;
                	break ;
                	
                case IDC_APROPOS :
                	BoiteAPropos( hDlg ) ;
                	break ;
                }
                break;

        default :
            return FALSE ;
        }

    return TRUE ;
}
