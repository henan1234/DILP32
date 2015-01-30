/*  Yeux.c
	Lucien PILLONI
	Version 32 Bits
*/
#define STRICT
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "resource.h"

#define RAYONOEIL  		12			// Il vaut mieux que RAYONOEIL soit multiple de 4 
#define ECARTYEUX  		4
#define DELAI_CLIN		5000		
#define DELAI_SOMMEIL	400			// en millisecondes

char		NomOeil[]="LPI Oeil" ;
int 		xOeil		=	100 ;
int			yOeil		=	20 ;
HBITMAP		hBitmap ;
int 		RayonOeil ;
POINT		AncienPoint ;
POINT		NouveauPoint ;
DWORD		CompteurTemps ;
int			HauteurPaupiere ;
HWND		hWndPrincipale ;
BOOL		ClinEnCours = FALSE ;
BOOL		ClinPossible = TRUE ;
HINSTANCE	hInst ;
HANDLE		hThread ;
DWORD		ThreadId ;
DWORD		DernierClinDOeil ;

#define		APPLI_KEY		"SOFTWARE\\Lucien PILLONI\\Yeux"
#define		X_KEY			"PosX"
#define		Y_KEY			"PosY"

void	WriteRegistryInt( HKEY	hClef, const char * Key, const char * Value, int v )
	{
	DWORD	Dispo ;
	HKEY	hKey ;

	if ( RegCreateKeyEx( hClef, Key, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
		return ;

	Dispo	=	v ;
	RegSetValueEx( hKey, Value, 0, REG_DWORD, (LPBYTE)&Dispo, sizeof( Dispo)) ;
	}


void ReadRegistryInt( HKEY hClef, const char * Key,const char * Value, int * pI )
{
	DWORD	Retour	;
	HKEY	hKey ;
	DWORD	Taille ;
 	DWORD	Type ;

	if ( RegOpenKeyEx( hClef, Key, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		return ;

 	Taille	=	sizeof( Retour ) ;
	Type	=	REG_DWORD ;

	if ( RegQueryValueEx( hKey, Value, 0, &Type, (LPBYTE)&Retour, &Taille) == ERROR_SUCCESS )
		(*pI)	=	Retour ;
}


///////////////////////////////////////////////////////////////////////////////
// WritePosition
///////////////////////////////////////////////////////////////////////////////
void	WritePosition( int x, int y )
	{
	WriteRegistryInt( HKEY_CURRENT_USER, APPLI_KEY, X_KEY, x ) ;
	WriteRegistryInt( HKEY_CURRENT_USER, APPLI_KEY, Y_KEY, y ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// ReadPosition
///////////////////////////////////////////////////////////////////////////////
void	ReadPosition( int * px, int * py )
	{
	ReadRegistryInt( HKEY_CURRENT_USER, APPLI_KEY, X_KEY, px ) ;
	ReadRegistryInt( HKEY_CURRENT_USER, APPLI_KEY, Y_KEY, py ) ;
	}

void GestionOeil( void ) ;

BOOL	Delai( int Delai, DWORD	*	pDelai )
	{
	const DWORD	Maintenant	=	GetCurrentTime() ;

	if ( (*pDelai)+Delai > Maintenant )
		return FALSE ;

	(*pDelai)	=	Maintenant ;
	return TRUE ;
	}

void	SetFenetreNonRect()
	{
	HRGN	hOeil1	=	CreateEllipticRgn( 0, 0, RayonOeil * 2 + 1, RayonOeil * 2 + 1 ) ;
	HRGN	hOeil2	=	CreateEllipticRgn( 0, 0, RayonOeil * 2 + 1, RayonOeil * 2 + 1 ) ;
	HRGN	hRegion	=	CreateRectRgn(0,0,0,0) ;
	OffsetRgn( hOeil1, 1, 1 ) ;
	OffsetRgn( hOeil2, 1+ ECARTYEUX + RayonOeil * 2, 1 ) ;


	CombineRgn( hRegion, hOeil1, hOeil2, RGN_OR ) ;
	DeleteObject( hOeil1 ) ;
	DeleteObject( hOeil2 ) ;


	OffsetRgn(hOeil2, ECARTYEUX + RayonOeil, 0 ) ;
	SetWindowRgn( hWndPrincipale, hRegion, TRUE ) ;
	}

// ----------------------------------------------------------------------------
// DrawFocus
// Inverse un curseur pour suivre le deplacement de la fenetre
// ----------------------------------------------------------------------------
void DrawFocus( HDC hDC,LPRECT lpR )                                           

{
	HBITMAP	hOldBitmap ;
	HBITMAP	hBitmap ;
	BITMAP	Bitmap ;
	HDC		hMemDC ;
	
	hMemDC = CreateCompatibleDC( hDC ) ;
	hBitmap= LoadBitmap( hInst, "DEPLACE" ) ;
	GetObject( hBitmap, sizeof( Bitmap ), &Bitmap ) ;
	
	hOldBitmap = SelectObject( hMemDC, hBitmap ) ;
	
	BitBlt(	hDC, lpR->left, lpR->top, Bitmap.bmWidth, Bitmap.bmHeight,
				hMemDC, 0, 0, SRCINVERT ) ;
	BitBlt(	hDC, lpR->right-Bitmap.bmWidth, lpR->top, Bitmap.bmWidth, Bitmap.bmHeight,
				hMemDC, 0, 0, SRCINVERT ) ;
	SelectObject( hMemDC, hOldBitmap ) ;
	
	DeleteObject( hBitmap ) ;
	DeleteDC( hMemDC ) ;
}

// ---------------------------------------------------------------------------
// CalculePosPupille
// Calcule la position de la pupille depuis les positions relatives de l'oeil
// et du curseur
// ENTREES :	Position de l'oeil
//					Position du curseur
// SORTIES :	Position de la pupille
// RETOUR :		Rien
// ---------------------------------------------------------------------------
static void CalculePosPupille( int x, int y, POINT Point, int * pxPupille, int * pyPupille )
{
	POINT	CentreOeil ;
	int	DistMax ;

	// Position du centre de l'oeil par rapport a l'ecran	
	CentreOeil.x = x ;
	CentreOeil.y = y ;
	ClientToScreen( hWndPrincipale, &CentreOeil ) ;
	
	if (abs(Point.x - CentreOeil.x) < RayonOeil + ECARTYEUX)
		DistMax = RayonOeil + ECARTYEUX ;
	else
		if (Point.x > CentreOeil.x)
			DistMax = GetSystemMetrics( SM_CXSCREEN ) - CentreOeil.x ;
		else
			DistMax = CentreOeil.x ;

    *pxPupille = (int)((double)(Point.x - CentreOeil.x) * (double)RayonOeil / 2.0 / (double)DistMax) ;

	if (abs(Point.y - CentreOeil.y) < RayonOeil )
		DistMax = RayonOeil  ;
	else
		if (Point.y > CentreOeil.y)
			DistMax = GetSystemMetrics( SM_CYSCREEN ) - CentreOeil.y ;
		else
			DistMax = CentreOeil.y ;

    *pyPupille = (int)((double)(Point.y - CentreOeil.y)
		   * (double)RayonOeil / 2.0 / (double)DistMax) ;

    (*pxPupille) += RayonOeil / 2 + 1 ;
    (*pyPupille) += RayonOeil / 2 + 1 ;
    
}

///////////////////////////////////////////////////////////////////////////////
//	Dessiner un oeil
//	ENTREES :	DC de la fenetre
//				Coordonnees du centre de l'oeil
//				Hauteur actuelle de la paupiere
///////////////////////////////////////////////////////////////////////////////
void DessineOeil( HDC hDC, int x, int y, int HauteurPaupiere )
{
    HBRUSH  hOBrush ;
    HPEN    hOPen ;
    HBRUSH  hBrush ;
    int     xPupille ;
    int     yPupille ;
    POINT   Point ;
    HBITMAP hMemBitmap ;
    HBITMAP hOBitmap ;
    HDC     hMemDC ;
    HDC     hPupilleDC ;
    HBITMAP hOPupilleBitmap ;
	BITMAP	sBitmap ;

    // ------------------------------------------------------------------------
	// Memorisation du fond de l'ecran
    // ------------------------------------------------------------------------
	hMemDC		= CreateCompatibleDC( hDC ) ;
    hMemBitmap	= CreateCompatibleBitmap( hDC, RayonOeil * 2 + 2, RayonOeil * 2 + 2) ;
    hOBitmap	= SelectObject( hMemDC, hMemBitmap ) ;
    BitBlt( hMemDC, 0, 0, RayonOeil * 2 + 2, RayonOeil * 2 + 2,
			hDC, x - RayonOeil - 2, y - RayonOeil - 2, SRCCOPY ) ;


	// ------------------------------------------------------------------------
	// Nouvelle position du curseur
    // ------------------------------------------------------------------------
	GetCursorPos( & Point ) ;
    
    // ------------------------------------------------------------------------
	// Calcul de la direction du regard
    // ------------------------------------------------------------------------
	CalculePosPupille( x, y, Point, &xPupille, &yPupille ) ;

    /* ************ Affiche le fond de l'oeil ************ */
    GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;

    hPupilleDC = CreateCompatibleDC( hDC ) ;
    hOPupilleBitmap = SelectObject( hPupilleDC, hBitmap ) ;
    BitBlt( hMemDC, 0, 0,
			sBitmap.bmHeight, sBitmap.bmHeight,
			hPupilleDC, 
			(sBitmap.bmWidth- RayonOeil)/2  - xPupille,
			(sBitmap.bmHeight- RayonOeil)/2  - yPupille, SRCCOPY ) ;

    SelectObject( hPupilleDC, hOPupilleBitmap ) ;
    DeleteDC( hPupilleDC ) ;

    /* ************ Affiche la paupiere  ************ */
    if ( HauteurPaupiere > 0 )
		{
		hBrush = CreateSolidBrush( RGB( 255, 127, 72) ) ;
		hOBrush = SelectObject( hMemDC, hBrush ) ;
		hOPen = SelectObject( hMemDC, GetStockObject( BLACK_PEN )) ;
		Ellipse( hMemDC, 0, 0, RayonOeil * 2 + 1, HauteurPaupiere + 1 ) ;
		    	
		SelectObject( hMemDC, hOBrush ) ;
		SelectObject( hMemDC, hOPen) ;
		DeleteObject( hBrush ) ;
		}
    
	// Dessine le tour de l'oeil
	hOBrush	= SelectObject( hMemDC, GetStockObject( NULL_BRUSH )) ;
	hOPen	= SelectObject( hMemDC, CreatePen( PS_SOLID, 2, 0 )) ; //GetStockObject( BLACK_PEN )) ;
			
	Ellipse( hMemDC, 0, 0, RayonOeil * 2+1, RayonOeil * 2+1) ;
	
	// Affiche l'oeil a l'ecran
	BitBlt( hDC, x - RayonOeil - 2, y - RayonOeil - 2, RayonOeil * 2 + 2, RayonOeil * 2 + 2,
			hMemDC, 0, 0, SRCCOPY ) ;

    DeleteObject( SelectObject( hMemDC, hOPen )) ;
    SelectObject( hMemDC, hOBrush ) ;
    SelectObject( hMemDC, hOBitmap ) ;

    DeleteObject( hMemBitmap ) ;
    DeleteDC(	  hMemDC ) ;
}


/* ==================================================================== */
// Boite de dialogue qui affiche des infos sur l'appli, quitte l'appli
// si on presse Fermer
/* ==================================================================== */
BOOL CALLBACK DlgAbout(HWND hDlg, unsigned Message, WPARAM wParam, LPARAM lParam )
{
	switch(Message)
		{
		case WM_INITDIALOG :
			break ;
			
		case WM_COMMAND :
			switch(wParam)
				{
				case IDOK :
				case IDC_FERMER :
					EndDialog( hDlg, wParam ) ;
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


// ----------------------------------------------------------------------------
// FONCTION DessineYeux
// Dessiner les yeux comme il le faut 
// ----------------------------------------------------------------------------
void DessineYeux( HDC hDC, int HauteurPaupiere )
{  
	DessineOeil( hDC, RayonOeil + 2, RayonOeil + 2, HauteurPaupiere ) ;
	DessineOeil( hDC, RayonOeil * 3 + ECARTYEUX + 2, RayonOeil + 2, HauteurPaupiere ) ;
}


// ----------------------------------------------------------------------------
// ClinDOeil
// Cligne des paupiere
// ENTREES :	HDC
// SORTIES :	rien
// RETOUR :		rien
// ----------------------------------------------------------------------------
static void ClinDOeil( HDC hDC )
{
	int i ;
	
	if ( (! ClinPossible) || (ClinEnCours))
		return ;
		
	ClinEnCours = TRUE ;	// Pour eviter les problemes de reentrance dus au Yield
	EnableWindow( hWndPrincipale, FALSE ) ;
	
	/********** Clin d'oeil **************************/
	// Baisser les paupieres
	for (i = 0 ; i < RayonOeil * 2; i++ )
		{
		DessineYeux( hDC, i ) ;
		Yield() ;
	   }
	
	// Remonter les paupieres
	for (i = RayonOeil * 2; i >= 0; i-- )
		{
		DessineYeux( hDC, i ) ;
		Yield() ;
		}
		
	ClinEnCours = FALSE ;
	EnableWindow( hWndPrincipale, TRUE ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Dessin des deux yeux
///////////////////////////////////////////////////////////////////////////////
void GestionOeil( void )
{
	HDC     hDC ;
	RECT	R ;

	if ( ClinEnCours )
		// Pb de reentrance dus au hook
		return ;
		
	hDC = GetDC( hWndPrincipale ) ; ;
	GetWindowRect( hWndPrincipale, &R) ;
	GetCursorPos( & NouveauPoint ) ;

	if ((NouveauPoint.x != AncienPoint.x) || (NouveauPoint.y != NouveauPoint.y))
		{
		/************** Suivre le curseur de la souris ******************/
		if (HauteurPaupiere > -RayonOeil * 2 )
			HauteurPaupiere -- ;

		DessineYeux( hDC, HauteurPaupiere ) ;

		AncienPoint = NouveauPoint ;
		CompteurTemps = GetCurrentTime() ;
		}
    else
		{
		if (HauteurPaupiere <= 0)
		// Clignotement aleatoire des paupieres
		    if ( Delai( DELAI_CLIN, &DernierClinDOeil ) )
		    ClinDOeil( hDC ) ;

		// ==================== Si le curseur ne bouge pas, on s'endort progressivement
		if (HauteurPaupiere <= RayonOeil * 2 )
			{
			if ( GetCurrentTime() - CompteurTemps > DELAI_SOMMEIL )
				{
				/******** Endormissement progressif *******************/
				HauteurPaupiere ++ ;
				DessineYeux( hDC, HauteurPaupiere ) ;
	
				CompteurTemps = GetCurrentTime() ;
				}
			}
	}
	
	ReleaseDC( hWndPrincipale, hDC ) ;
}



///////////////////////////////////////////////////////////////////////////////
// WindowProc de la fenetre qui gere les yeux
///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc( HWND hWnd,
							 unsigned Message,
							 WPARAM wParam,
							 LPARAM lParam )
{
	static BOOL		BoutonEnfonce = FALSE ;
	static int		EcartX, EcartY ;
	static POINT	Point ;
	static RECT		R ;
	static RECT		RectDepart ;
	static WORD		wMessageFixe ;
	
	switch( Message )
		{
		case WM_LBUTTONDOWN :
			{
			HDC				hDC ;

			// Empeche les yeux de se redessiner pendant qu'on les deplace
			ClinPossible	=	FALSE ;			
			BoutonEnfonce	=	TRUE ;
			SetCapture( hWnd ) ;
			EcartX			=	LOWORD( lParam ) ;
			EcartY			=	HIWORD( lParam ) ;
			SuspendThread( hThread ) ;

			GetWindowRect( hWnd, &R ) ;
			hDC = CreateDC( "display", NULL, NULL, NULL ) ;
			DrawFocus( hDC, &R ) ;
			DeleteDC( hDC ) ; 
			GetWindowRect( hWnd, &RectDepart ) ;
			}
			break ;
			
		case WM_MOUSEMOVE :
			if (BoutonEnfonce)
				{
				HDC				hDC ;

				hDC			=	CreateDC( "display", NULL, NULL, NULL ) ;
				DrawFocus( hDC, &R ) ;

				Point.x		=	LOWORD( lParam ) ;
				Point.y		=	HIWORD( lParam ) ;
				ClientToScreen( hWnd, &Point ) ;
				Point.x -= EcartX ;
				Point.y -= EcartY ;
				
				OffsetRect( &R, -R.left, -R.top ) ;
				OffsetRect( &R, Point.x, Point.y ) ;
				DrawFocus( hDC, &R ) ;
								
				DeleteDC( hDC ) ;
				}
			break ;
			
		case WM_LBUTTONUP:
			if ( BoutonEnfonce )
				{
				HDC	hDC  ;
				HDC hDispDC ;
				
				hDispDC		= CreateDC( "display", NULL, NULL, NULL ) ;
				Point.x		=	LOWORD( lParam ) ;
				Point.y		=	HIWORD( lParam ) ;
				ClientToScreen( hWnd, &Point ) ;
				Point.x		-= EcartX ;
				Point.y		-= EcartY ;
				
				hDC			= GetDC( hWnd ) ;

				OffsetRect( &R, -R.left, -R.top ) ;
				OffsetRect( &R, Point.x, Point.y ) ;
				DrawFocus( hDispDC, &R ) ;
				
				BitBlt( hDC, 0, 0, R.right - R.left, R.bottom-R.top,
						hDispDC, Point.x, Point.y, SRCCOPY ) ;

				DeleteDC( hDispDC ) ;
				ReleaseDC( hWnd, hDC ) ;
				
				ReleaseCapture() ;                                            
				SetWindowPos( hWnd, HWND_TOPMOST, Point.x, Point.y, 0, 0, SWP_NOSIZE ) ;
				
				BoutonEnfonce = FALSE ;
				InvalidateRect( hWnd, NULL, TRUE ) ;

				WritePosition( Point.x, Point.y ) ;

				// Relance la machine
				ResumeThread( hThread ) ;

				AncienPoint.x = -1 ;
				ClinPossible = TRUE ;
				GestionOeil() ;
				}
			break ;

	case WM_RBUTTONDOWN :	
	case WM_LBUTTONDBLCLK :
			{
			if ( DialogBox( hInst, MAKEINTRESOURCE(IDD_ABOUT), hWnd, DlgAbout ) == IDC_FERMER )
				DestroyWindow(hWnd) ;
				
			}
			break ;
			
		case WM_DESTROY :
			PostQuitMessage( 0 ) ;
			break ;

		case WM_PAINT :
			{
			PAINTSTRUCT Ps ;
			RECT			R ;
			
			BeginPaint( hWnd, &Ps ) ;
			
			GetWindowRect( hWndPrincipale, &R) ;
			DessineYeux(Ps.hdc,HauteurPaupiere) ;
			
			EndPaint( hWnd, &Ps ) ;
			}
			break ;
			
		default :
			if ( Message == wMessageFixe )
				return TRUE ;
			else
				return DefWindowProc( hWnd, Message, wParam, lParam ) ;
		}
		
	return 0L ;
}

/////////////////////////////////////////////////////////////////////////////// 
// Enregistrement de la classe de la fenetre
/////////////////////////////////////////////////////////////////////////////// 
BOOL Init( HANDLE hInstance )
{
    WNDCLASS   Class;

	Class.hCursor		 =  LoadCursor( hInstance, "CURSEUR" ) ;
    Class.hIcon          =	NULL	;
    Class.lpszMenuName	 =	NULL	;
    Class.lpszClassName  =	(LPSTR)NomOeil;
    Class.hbrBackground  =	(HBRUSH)GetStockObject( BLACK_BRUSH ) ; //(HBRUSH)NULL ;
    Class.hInstance      =	hInstance;
    Class.style          =	CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    Class.lpfnWndProc    =	WindowProc;
    Class.cbClsExtra     =	0 ;
    Class.cbWndExtra     =	0 ;

    if (!RegisterClass( (LPWNDCLASS)&Class ) )
        return FALSE;

    return TRUE;
}


DWORD	WINAPI ThreadYeux( LPVOID p )
	{
	while ( IsWindow( hWndPrincipale ))
		{
		if ( ! FindWindow("WindowsScreenSaverClass", NULL ))
			GestionOeil() ;
		}

	return 0 ;
	}

///////////////////////////////////////////////////////////////////////////////
//	Point d'entree
///////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow )
{
    MSG     msg;
    char    Titre[50] ;
	BITMAP	Bitmap ;

	hInst	=	hInstance ;

    srand( (unsigned)GetCurrentTime()) ;

    hBitmap		= LoadBitmap( hInstance, (LPSTR)"OEIL") ;
    GetObject( hBitmap, sizeof(Bitmap), (LPSTR)&Bitmap) ;

    RayonOeil	= Bitmap.bmHeight / 3 ;

	if (!Init( hInstance ))
    	return FALSE;

    if (! FindWindow( (LPSTR)NomOeil, (LPSTR)NULL ))
		ReadPosition( &xOeil, &yOeil ) ;
    else
		{
		xOeil = RayonOeil + (rand() % (GetSystemMetrics( SM_CXSCREEN)- RayonOeil * 3)) ;
		yOeil = RayonOeil + (rand() % (GetSystemMetrics( SM_CYSCREEN)- RayonOeil * 3)) ;
		}

	DernierClinDOeil	=	GetCurrentTime() ;

    sprintf( Titre, "%s %dx%d", NomOeil, xOeil, yOeil ) ;

    hWndPrincipale = CreateWindowEx(	WS_EX_TOOLWINDOW,
										(LPSTR)NomOeil,
										(LPSTR)Titre,
										WS_POPUP | WS_VISIBLE | WS_BORDER,
										xOeil,
										yOeil,
										RayonOeil * 4 + ECARTYEUX + 2,
										RayonOeil *2 + 2,
										(HWND)NULL,
										(HMENU)NULL,
										(HANDLE)hInstance,
										(LPSTR)NULL
										);

	SetWindowPos( hWndPrincipale, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE ) ;
	
	SetFenetreNonRect() ;
	
    HauteurPaupiere = RayonOeil + 1 ;
    CompteurTemps   = 0 ;
    
	hThread	=	CreateThread( NULL, 0,ThreadYeux, NULL, CREATE_SUSPENDED, &ThreadId ) ;
	SetThreadPriority( hThread, THREAD_PRIORITY_BELOW_NORMAL ) ;
	ResumeThread( hThread ) ;

    while (GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

    DeleteObject( hBitmap ) ;

	TerminateThread( hThread, 0 ) ;

    return (int)msg.wParam;
}
