///////////////////////////////////////////////////////////////////////////////
// Ajoute deux icones a la fenetre de notification :
//	Une pour activer immediatement le screen saver
//	une autre pour ne jamais l'activer
///////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <winreg.h>
#include "resource.h"

HINSTANCE	hInst ;

#define	WM_NOTIFYICON			WM_USER + 1
BOOL	ScreenSaver				=	TRUE ;


HMENU		hMenu ;
#define DEBUT_COMMANDES_REGISTRY	10000
char	**	pCommandes  ;
int			NbCommandes = 0 ;

BOOL	CALLBACK	AboutDlgProc( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
	switch( Message )
		{
		case WM_INITDIALOG :
			break ;

		case WM_COMMAND :
			EndDialog( hWnd, wParam ) ;
			return TRUE ;

		default :
			return FALSE ;
		}
	return TRUE ;
	}


void	EnregistreIcone( HWND hWnd,UINT Id, WORD	Notify, WORD	Icone, WORD	Tip )
	{
	NOTIFYICONDATA tnd;

	tnd.cbSize				= sizeof(NOTIFYICONDATA);
	tnd.hWnd				= hWnd;
	tnd.uID					= Id;

	tnd.uFlags				= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= Notify ;
	tnd.hIcon				= LoadIcon( hInst, MAKEINTRESOURCE( Icone )) ;
	
	LoadString( hInst, Tip, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon(NIM_ADD, &tnd);
	}


///////////////////////////////////////////////////////////////////////////////
// AfficherMenu
//	Affiche le menu quand on clique avec le bouton droit sur une icone (menu
//	commun aux deux icones )
///////////////////////////////////////////////////////////////////////////////
void	AfficherMenu( HWND hWnd )
	{
	POINT	Pt ;
	GetCursorPos( &Pt );

	HMENU	hSubMenu	=	GetSubMenu( hMenu, 0 ) ;
	TrackPopupMenu( hSubMenu, TPM_RIGHTALIGN | TPM_RIGHTBUTTON,Pt.x, Pt.y, 0, hWnd, NULL ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Notification de l'icone : activer maintenant
///////////////////////////////////////////////////////////////////////////////
void	NotifyIcon( HWND hWnd, WPARAM, LPARAM lParam )
	{
	switch (lParam)
		{
		case WM_RBUTTONDOWN :
			AfficherMenu( hWnd ) ;
			break ;

		case WM_LBUTTONDOWN :
			ScreenSaver	=	TRUE ;
			DefWindowProc( hWnd, WM_SYSCOMMAND, SC_SCREENSAVE, 0 ) ;
			break ;
		}

	return  ;
	}

void	LigneDeCommande( HWND hWnd, int	NoCommande )
	{
	if ( NoCommande < 0 || NoCommande >= NbCommandes )
		return ;

	char	LigneDeCommande[ _MAX_PATH * 2 ] ;
	// Remplacer l'eventuel %1 par le nom du screen saver actif

	char	Buffer[_MAX_PATH] ;
	GetPrivateProfileString( "boot", "SCRNSAVE.EXE", "", Buffer, sizeof( Buffer), "SYSTEM.INI" ) ;

	int	IndiceSrc	=	0 ;
	int	IndiceDst	=	0 ;
	char	*		pCommande	=	pCommandes[NoCommande] ;

	while ( pCommande[IndiceSrc] && IndiceDst < sizeof( LigneDeCommande ))
		{
		if ( (pCommande[IndiceSrc] == '%') && (pCommande[IndiceSrc+1]	==	'1' || pCommande[IndiceSrc+1] == 'l') )
			{
			lstrcpy( &LigneDeCommande[IndiceDst], Buffer ) ;
			IndiceDst +=	lstrlen( Buffer ) ;
			IndiceSrc +=	2 ;
			}
		else
			{
			LigneDeCommande[ IndiceDst ++ ] = pCommande[IndiceSrc ++ ] ;
			}
		}
	

	LigneDeCommande[ IndiceDst ] = 0 ;

	WinExec( LigneDeCommande, SW_SHOWNORMAL ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Parcourir la registry pour ajouter les options de menu specifiques aux
// screen savers
///////////////////////////////////////////////////////////////////////////////
void	ParcoursRegistry( HMENU	hMenu, UINT	Id )
{
	HKEY	hKey ;
	// Acceder a la bonne sous branche
	if ( RegOpenKeyEx( HKEY_CLASSES_ROOT, "SCRFile\\Shell", 0, KEY_ALL_ACCESS, &hKey )
		 == ERROR_SUCCESS )
		{
		// Parcourir les differentes commandes
		DWORD		Indice		=	0 ;
		char		KeyName[ _MAX_PATH ] ;
		DWORD		KeySize		=	sizeof( KeyName ) ;
		FILETIME	Time ;

		while ( RegEnumKeyEx( hKey, Indice, KeyName, &KeySize, NULL, NULL, 0, &Time ) == ERROR_SUCCESS )
			{
			// On a la clef d'un composant du bureau HP, le traiter comme il le merite
			HKEY	hCommande ;
			
 			if ( RegOpenKeyEx( hKey, KeyName, 0, KEY_ALL_ACCESS, &hCommande ) == ERROR_SUCCESS )
				{
				char	NomCommande[ _MAX_PATH ] ;
				LONG	TailleBuffer	=	sizeof( NomCommande ) ;
				// Nom de la commande
				if ( RegQueryValue( hCommande, NULL, NomCommande, &TailleBuffer )== ERROR_SUCCESS )
					{
					char	LigneCommande[ _MAX_PATH ] ;
					TailleBuffer =	sizeof( LigneCommande ) ;
					// Ligne de commande
					if ( RegQueryValue( hCommande, "command", LigneCommande, &TailleBuffer )== ERROR_SUCCESS )
						{
						// Inserer la commande dans le menu
						InsertMenu( hMenu, Id, MF_BYCOMMAND, DEBUT_COMMANDES_REGISTRY+Indice, NomCommande ) ;

						// Memoriser la ligne de commande
						if ( NbCommandes == 0 )
							pCommandes	=	(char**)malloc( sizeof( char * )) ;
						else
							pCommandes	=	(char**)realloc( pCommandes, sizeof( char * ) * (NbCommandes+1)); 

						pCommandes[NbCommandes]	=	(char*)malloc( sizeof( char ) * (lstrlen( LigneCommande)+1)) ;
						lstrcpy( pCommandes[NbCommandes], LigneCommande ) ;
						NbCommandes ++ ;
						}
					}

				RegCloseKey( hCommande ) ;
				}

			Indice ++ ;
			KeySize	=	sizeof( KeyName ) ;
			}

		}

	DeleteMenu( hMenu,  Id, MF_BYCOMMAND) ;
	RegCloseKey( hKey ) ;
}

///////////////////////////////////////////////////////////////////////////////
// WindowProc de la fenetre qui gere les yeux
///////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc( HWND hWnd,
							 unsigned Message,
							 WPARAM wParam,
							 LPARAM lParam )
{
	switch( Message )
		{
		case WM_CREATE :
			{
			EnregistreIcone( hWnd, 1,WM_NOTIFYICON, IDI_MAINTENANT, IDS_TIP_MAINTENANT ) ;
			hMenu	=	LoadMenu( hInst, MAKEINTRESOURCE( IDR_MENU1 ) ) ;
			ParcoursRegistry( hMenu, ID_V_CESTICIQUONINSRELEMENUDELAREGISTRY ) ;
			}
			break ;

		case WM_NOTIFYICON :
			NotifyIcon( hWnd, wParam, lParam ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case ID_V_APROPOS :
					DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUT ), hWnd, (DLGPROC)AboutDlgProc ) ;
					break ;												  


				case ID_QUITTER :
					DestroyWindow( hWnd ) ;
					break ;

				default :
					LigneDeCommande( hWnd, wParam - DEBUT_COMMANDES_REGISTRY ) ;
					break ;
				}
			break ;

		case WM_DESTROY :
			NOTIFYICONDATA tnd;
			tnd.cbSize				= sizeof(NOTIFYICONDATA);
			tnd.hWnd				= hWnd;
			tnd.uID					= 1;
			tnd.uFlags				= NIF_MESSAGE ;
			tnd.uCallbackMessage	= 0;
			tnd.hIcon				= 0 ;
			
			Shell_NotifyIcon(NIM_DELETE , &tnd);
			
			DestroyMenu( hMenu ) ;
			PostQuitMessage(0) ;
			break ;


		case WM_SYSCOMMAND :
			switch( wParam & 0xFFF0 )
				{
				case SC_SCREENSAVE :
					if ( ! ScreenSaver )
						return 0 ;			// Pas de screen saver
				default :
					return DefWindowProc( hWnd, Message, wParam, lParam ) ;
				}
			break ;

		default :
			return DefWindowProc( hWnd, Message, wParam, lParam ) ;
		}

	return 0 ;
}


///////////////////////////////////////////////////////////////////////////////
//	Point d'entree
///////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow )
{
    MSG     msg;
	WNDCLASS	Class ;

	hInst	=	hInstance ;

	Class.hCursor		 =  LoadCursor( NULL, IDC_ARROW ) ;
    Class.hIcon          =	NULL	;
    Class.lpszMenuName	 =	NULL	;
    Class.lpszClassName  =	"MOJ_WNDCLASS";
    Class.hbrBackground  =	(HBRUSH)GetStockObject( BLACK_BRUSH ) ; 
    Class.hInstance      =	hInstance;
    Class.style          =	CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
    Class.lpfnWndProc    =	WindowProc;
    Class.cbClsExtra     =	0 ;
    Class.cbWndExtra     =	0 ;

    if (!RegisterClass( (LPWNDCLASS)&Class ) )
        return FALSE;


    CreateWindowEx(	WS_EX_TOOLWINDOW,
					(LPSTR)"MOJ_WNDCLASS",
					(LPSTR)"Maintenant...",
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT, CW_USEDEFAULT, 10, 10,
					(HWND)NULL,
					(HMENU)NULL,
					(HANDLE)hInstance,
					(LPSTR)NULL
					);

    while (GetMessage(&msg, NULL, 0, 0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

    return (int)msg.wParam;
}
