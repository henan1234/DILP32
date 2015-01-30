///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.CPP
//	Implementation de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <string.h>
#include "economiseur.h"
//#include "resource.h"
extern HWND hMainWindow ;
CEconomiseur*	CEconomiseur::_pTheOnlyOne = 0 ;
BOOL			CEconomiseur::_Fini = TRUE ;
HWND			CEconomiseur::_hWnd ;
HANDLE			CEconomiseur::_hThreadFini ;

CString			CShareWare::_Message = "This is a shareware program. You can test it\n"
										"If you decide to use it, you must obtain a registered version\n"
										"Please check the configuration dialog box\n"
										"Lucien PILLONI tanks you for trying this program" ;

CCriticalSection		PeintureFenetre ;
CDC CEconomiseur::DC ;
int		CEconomiseur::Largeur ;
int		CEconomiseur::Hauteur ;

CEconomiseur::CEconomiseur( const CString & Nom, const CString & Enregistre )
{
	ASSERT( _pTheOnlyOne==	0 ) ;
	hPalette			=	0 ;
	_pTheOnlyOne		=	this ;
	_Nom				=	Nom ;
	_ValeurEnregistre	=	Enregistre ;
	NoircirEcran		=	TRUE ;
	_EcriturePreferences=	FALSE ;
	_dwSeed				=	GetCurrentTime() ;
	_ResolutionChangee	=	FALSE ;
	_hThread			=	NULL ;
	_NoCourant			=	0 ;
}

CEconomiseur::~CEconomiseur()
{
	if ( _ResolutionChangee )
		ChangeDisplaySettings( NULL, 0 ) ;
}

void CEconomiseur::InitSave( HWND	hWnd )
{
	LitPreferences() ;

	CRect	R ;
	::GetClientRect( hWnd, R ) ;
	
	Largeur	=	R.Width() ;
	Hauteur	=	R.Height() ;

	//	Un peu de pub, on laisse les gens tranquilles dans le mode apercu
	//
	//
	if ( ! Apercu())
		{
		if ( ShareWare())
			{
			// Creation de la fenetre d'explication SHAREWARE
			const char *	pClass	=	AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW, 0, (HBRUSH)GetStockObject( BLACK_BRUSH )) ;
			CShareWare *	pShareWare	=	new CShareWare ;
			pShareWare->CreateEx( WS_EX_TOPMOST, pClass, "", WS_POPUP | WS_VISIBLE, 0, 0, 100, 100, hWnd, 0 ) ;

			pShareWare->Invalidate( TRUE ) ;
			pShareWare->UpdateWindow() ;

			// Verification de la date
			if ( ! VerifDate())
				{
				MessageBox( 0, "SHAREWARE", "This shareware program is for test only. You had time enough to test it. It is now time for you to obtain the registered version. Please check the configuration box.",
							MB_OK | MB_ICONSTOP ) ;
				exit(0) ;
				}
			}
		}
}

void	CEconomiseur::Configuration( CPropertySheet * )
{
}

void	CEconomiseur::PeintFenetre( CDC &, const CRect& )
{
}

void CEconomiseur::Preferences()
{
}


CEconomiseur*	CEconomiseur::GetEconomiseur()
{
	ASSERT( _pTheOnlyOne ) ;
	return _pTheOnlyOne ;
}

void CEconomiseur::EcritPreferences()
{
	ValidePreferences() ;
	_EcriturePreferences	=	TRUE ;
	Preferences() ;
}

void CEconomiseur::LitPreferences()
{
	_EcriturePreferences	=	FALSE ;
	Preferences() ;
	ValidePreferences() ;
}


void CEconomiseur::ValidePreferences()
{
}

void CEconomiseur::Preference( const char * Nom, CString & Chaine, const char * pSousCle )
{
	CString	Clef	= "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" + _Nom ;
	if ( pSousCle )
		{
		Clef		+=	'\\' ;
		Clef		+=	pSousCle ;
		}

	if ( _EcriturePreferences )
		{
		///////////////////////////////////////////////////////////////////////
		// Ecrire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		DWORD	Dispo ;
		HKEY	hKey ;
		if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
							 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
			return ;

		RegSetValueEx( hKey, Nom, 0, REG_SZ, (LPBYTE)(LPCSTR)Chaine, Chaine.GetLength()+1 ) ;
		}
	else
		{
		///////////////////////////////////////////////////////////////////////
		// Lire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		HKEY	hKey ;
		DWORD	Taille ;
 		DWORD	Type ;

		if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
			return ;

		char	*	pValeur =	new char[ 1024 ] ;
		Taille	=	1024 ;
		Type	=	REG_SZ ;

		if ( RegQueryValueEx( hKey, Nom, 0, &Type, (LPBYTE)pValeur, &Taille) == ERROR_SUCCESS )
			Chaine = pValeur  ;
	
		delete [] pValeur ;
		}
}


void CEconomiseur::Preference( const char * Nom, DWORD & Valeur, const char * pSousCle )
{
	CString	Clef	= "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" + _Nom ;
	if ( pSousCle )
		{
		Clef		+=	'\\' ;
		Clef		+=	pSousCle ;
		}

	HKEY	hKey ;

	if ( _EcriturePreferences )
		{
		DWORD	Dispo ;
		///////////////////////////////////////////////////////////////////////
		// Ecrire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
			return ;

		RegSetValueEx( hKey, Nom, 0, REG_DWORD, (LPBYTE)&Valeur, sizeof( Valeur )) ;
		}
	else
		{
		///////////////////////////////////////////////////////////////////////
		// Lire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
			return ;

 		DWORD Taille	=	sizeof( Valeur ) ;
		DWORD Type	=	REG_DWORD ;
		RegQueryValueEx( hKey, Nom, 0, &Type, (LPBYTE)&Valeur, &Taille) ;
		}
}

void CEconomiseur::Preference( const char * Nom, double & Valeur, const char * pSousCle )
{
	if ( _EcriturePreferences )
		{
		///////////////////////////////////////////////////////////////////////
		// Ecrire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		char	Buffer[50] ;

		gcvt( Valeur, 45, Buffer ) ;
		CString	Chaine( Buffer ) ;

		Preference( Nom, Chaine, pSousCle ) ;
		}
	else
		{
		///////////////////////////////////////////////////////////////////////
		// Lire la valeur dans la registry
		///////////////////////////////////////////////////////////////////////
		char	Buffer[50] ;
		gcvt( Valeur, 45, Buffer ) ;

		CString	Chaine( Buffer ) ;
		Preference( Nom, Chaine, pSousCle ) ;
		Valeur	=	atof( Chaine ) ;
		}
}


void CEconomiseur::Preference( const char * Nom, int & Valeur, const char * pSousCle )
{
	DWORD	dw	=	Valeur ;
	Preference( Nom, dw, pSousCle ) ;
	Valeur	=	(int)dw ;
}

int CEconomiseur::Alea( int Min, int Max )
{
	return Min + arand( Max - Min + 1 ) ;
}

int CEconomiseur::arand( int x )
{
	_dwSeed = _dwSeed * 0x343fd + 0x269ec3;
	return( (int)(((_dwSeed >> 16) & 0x7fff) * x >> 15) );
}

BOOL CEconomiseur::RealizePalette( CDC & Dc)
{
	if ( hPalette )
		{
		CPalette	Palette ;
		Palette.Attach( hPalette ) ;
		Dc.SelectPalette( &Palette, FALSE ) ;
		Dc.RealizePalette() ;
		Palette.Detach() ;
		return TRUE ;
		}
	return FALSE ;
}

///////////////////////////////////////////////////////////////////////////////
// ShareWare
// Retourne VRAI si ce logiciel a ete enregistre comme ShareWare
///////////////////////////////////////////////////////////////////////////////
BOOL CEconomiseur::ShareWare( void )
{
/*	char	Buffer[100] ;
	DWORD	Taille	;

	// Si c'est moi, je vais quand meme pas payer...
	Taille	=	sizeof( Buffer ) ;
	GetUserName( Buffer, &Taille) ;

	CharUpper( Buffer ) ;
	const int Nb	= lstrlen( Buffer ) ; 

	for ( int i = 0; i < Nb; i++)
		Buffer[i] = Buffer[i]+1 ;
	

	if ( (Buffer[0] == 'M') || (Buffer[0] == 'Q') || Buffer[0] == 'C' )
	{
		if ((Buffer[1] == 'V') || (Buffer[1] == 'Q') || (Buffer[1] == 'J') || (Buffer[1] == 'P') )
		{
		if ( (Buffer[2] == 'M') || (Buffer[2] == 'J') || (Buffer[2] == 'D') || (Buffer[2] == 0) || (Buffer[2] == 'O'))
			return FALSE ;
		}
	}
*/
	const BOOL	Memo	=	_EcriturePreferences ;
	_EcriturePreferences	=	FALSE ;
	CString	Valeur ;
	Preference( "Enregistrement", Valeur ) ;
	_EcriturePreferences	=	Memo ;

	return Valeur != _ValeurEnregistre ;
}

// Retourne VRAI si la date de peremption de ce logiciel n'est pas depassee
BOOL	CEconomiseur::VerifDate()
	{
	time_t	tim ;
	struct	tm *	ptm ;
	// Verification de la date
	time( &tim ) ;
	ptm	=	localtime( &tim ) ;

	// Valable jusqu'au 1/1/97
	if ( ptm->tm_year < 98 )
		return TRUE ;
	
	return FALSE ;
}

BOOL CEconomiseur::UnSur( int x )
{
	return (Alea( 1, x ) == 1) ;
}

BOOL CEconomiseur::Apercu( void ) const
{
	return fChildPreview ;
}

///////////////////////////////////////////////////////////////////////////////
// retourne une bitmap qui memorise l'ecran
///////////////////////////////////////////////////////////////////////////////
CBitmap * CEconomiseur::MemoriseEcran( int Largeur, int Hauteur )
{
	CDC	Dc	;
	Dc.CreateDC( "display", 0,0,0 ) ;

	CDC	MemDC ;
	MemDC.CreateCompatibleDC( &Dc ) ;

	CBitmap	*	pBitmap	=	new CBitmap ;
	ASSERT( pBitmap ) ;

	VERIFY( pBitmap->CreateCompatibleBitmap( &Dc, Largeur, Hauteur )) ;

	CBitmap*	pOld	=	MemDC.SelectObject( pBitmap ) ;

	MemDC.StretchBlt( 0, 0, Largeur, Hauteur,
					&Dc, 0, 0, ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ),
					SRCCOPY ) ;

	MemDC.SelectObject( pOld ) ;

	return pBitmap ;
}



///////////////////////////////////////////////////////////////////////////////
// Essayer de changer la resolution de l'ecran
//	ENTREES :	Largeur, hauteur en pixel
//				Nombre de couleurs :	-1
//										COLOR_16
//										COLOR_256
//										COLOR_64K
//				Si on parametre vaut -1, c'est qu'on ne desire pas changer cette
//				valeur
//	SORTIES :	rien
//	RETOUR :	VRAI si on a reussi a changer de resolution
///////////////////////////////////////////////////////////////////////////////
BOOL CEconomiseur::ChangeResolution( int LargeurDem, int HauteurDem, int NbCouleursDem )
{
	if ( Apercu())
		return FALSE ;

#ifndef _DEBUG
	DEVMODE DevMode ;

	memset( &DevMode, 0, sizeof( DevMode )) ;

	DevMode.dmSize		=	sizeof( DevMode ) ;
	DevMode.dmFields	=	0 ;

	if ( LargeurDem != -1 )
		{
		DevMode.dmFields	|= DM_PELSWIDTH ;
		DevMode.dmPelsWidth	=	LargeurDem ;
		}

	if ( HauteurDem != -1 )
		{
		DevMode.dmFields	|=	DM_PELSHEIGHT ;
		DevMode.dmPelsHeight=	HauteurDem ;
		}

	if ( NbCouleursDem != -1 )
		{
		DevMode.dmFields	|=	DM_BITSPERPEL ;
		DevMode.dmBitsPerPel=	NbCouleursDem ;
		}


	const int Res = ChangeDisplaySettings(&DevMode, 0 ) ;
	
	if ( Res != DISP_CHANGE_SUCCESSFUL )
		return FALSE ;

	Largeur	=	GetSystemMetrics( SM_CXSCREEN ) ;
	Hauteur	=	GetSystemMetrics( SM_CYSCREEN ) ;
		
	if ( IsWindow( hMainWindow ))
		{ 
		SetWindowPos( hMainWindow, HWND_TOPMOST, 0, 0, Largeur, Hauteur,
					  SWP_NOACTIVATE ) ;
		}

	// Cette fois c'est pour de bon
	_ResolutionChangee	=	TRUE ;
#endif
	return TRUE ;
}

void CEconomiseur::SetPalette( HPALETTE hPal )
{
	if ( hPalette )
		DeleteObject( hPalette ) ;

	hPalette	=	hPal ;
	if ( hPalette )
		SendMessage( hMainWindow, WM_QUERYNEWPALETTE, 0, 0 ) ;
}

//	===========================================================================
//	Initialisation deroulement et fin du screen saver dans un thread separe
//	===========================================================================
void CEconomiseur::CEstParti( HWND hWnd )
{
	if ( _hThread )
		return ;

	_Fini	=	FALSE ;
	_hWnd	=	hWnd ;

	InitSave( hWnd ) ;

	DWORD	Id ;
	_hThread	=	CreateThread( NULL, 0, Economisage, 0, CREATE_SUSPENDED, &Id ) ;
	//SetThreadPriority( _hThread, THREAD_PRIORITY_ABOVE_NORMAL ) ;

	ShowWindow( hWnd, SW_MAXIMIZE ) ;
	ResumeThread( _hThread ) ;
}	

//	===========================================================================
//	Economisage
//	Fait la boucle de l'economiseur dans un thread separe
//	===========================================================================
DWORD __stdcall Economisage( LPVOID  )
	{
	HDC hDC	=	GetDC( CEconomiseur::_hWnd ) ;
	CEconomiseur::DC.Attach( hDC ) ;

	CEconomiseur::_pTheOnlyOne->InitDC( CEconomiseur::DC ) ;

	// ------------------------------------------------------------------------
	//	Ceci est la boucle principale de l'economiseur
	// ------------------------------------------------------------------------
	while	( ! CEconomiseur::_Fini )
		{
		PeintureFenetre.Lock() ;
		CEconomiseur::_pTheOnlyOne->Animation( CEconomiseur::DC ) ;
		PeintureFenetre.Unlock() ;
		}

	CEconomiseur::_pTheOnlyOne->FinDC( CEconomiseur::DC ) ;

	CEconomiseur::DC.Detach() ;
	ReleaseDC( CEconomiseur::_hWnd, hDC ) ;

	return 0 ;
	}

//	===========================================================================
//	Fonction appelee par SaverWndProc pour demander la fin du screen saver
//	===========================================================================
void CEconomiseur::Fini( void )
{
	_Fini			=	TRUE ;
	WaitForSingleObject( _hThread, 2000 ) ;
}
/////////////////////////////////////////////////////////////////////////////
// CShareWare

CShareWare::CShareWare()
{
}

CShareWare::~CShareWare()
{
}


BEGIN_MESSAGE_MAP(CShareWare, CWnd)
	//{{AFX_MSG_MAP(CShareWare)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShareWare message handlers

int CShareWare::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect	Rect ;
	GetClientRect( Rect );
	const int	LargeurEcran	= GetSystemMetrics( SM_CXSCREEN ) ;
	const int	HauteurEcran	= GetSystemMetrics( SM_CYSCREEN ) ;
	int		PosX = Rect.top ;
	int		PosY = Rect.left ;

	switch( rand() % 4 )
		{
		case 0 :
			// En haut a gauche
			PosX	=	0 ;
			PosY	=	0 ;
			break ;

		case 1 :
			// En haut a droite
			PosX	=	LargeurEcran	-	Rect.Width() ;
			PosY	=	0 ;
			break ;

		case 2 :
			// En bas a gauche
			PosX	=	0 ;
			PosY	=	HauteurEcran - Rect.Height() ;
			break ;

		case 3 :
			// En bas a droite
			PosX	=	LargeurEcran - Rect.Width() ;
			PosY	=	HauteurEcran - Rect.Height() ;
			break ;
		}

	SetWindowPos( &CWnd::wndTopMost, PosX, PosY, 0,0,
				  SWP_NOSIZE | SWP_NOACTIVATE ) ;
	return 0;
}

void CShareWare::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect	R	;
	GetClientRect( R ) ;
	
	CBrush	Brosse( RGB( 0,0,0 )) ;
	dc.FillRect( R, &Brosse ) ;
	Brosse.DeleteObject() ;

	dc.SetTextColor( RGB( 255, 0, 0 )) ;
	dc.SetBkColor( RGB( 0,0,0 )) ;
	dc.SelectStockObject( ANSI_VAR_FONT ) ;

	dc.DrawText( _Message, R, DT_TOP | DT_LEFT | DT_WORDBREAK ) ;
}

BOOL CShareWare::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.cx	=	280 ;
	cs.cy	=	110 ;
	cs.x	=	GetSystemMetrics( SM_CXSCREEN ) - cs.cx - 2 ;
	cs.y	=	GetSystemMetrics( SM_CYSCREEN ) - cs.cy - 2 ;
	cs.style=	WS_POPUP | WS_VISIBLE | WS_DLGFRAME ;
	cs.dwExStyle=	WS_EX_TOPMOST | WS_EX_WINDOWEDGE ;
	return CWnd::PreCreateWindow(cs);
}

void CEconomiseur::UpdateFenetre( CDC & Dc, const CRect & R )
	{
	PeintureFenetre.Lock() ;
	PeintFenetre( Dc, R ) ;
	PeintureFenetre.Unlock() ;
	}

BOOL	CEconomiseur::Save( void )
	{
	PeintureFenetre.Lock() ;
	SuspendThread( _hThread ) ;

	// Trouver une branche de registry non utilisee
	const CString	Clef	=	"Software\\Lucien PILLONI\\Economiseurs d'écrans\\" + _Nom ;

	int	No	=	0 ;
	HKEY	hKey ;

	CString	SousClef ;

	do
		{
		No ++ ;

		SousClef.Format( "%s\\Etats\\%d", (const char *)Clef, No ) ;
		// Essayer d'ouvrir cette clef
		}
	while ( RegOpenKeyEx( HKEY_CURRENT_USER, SousClef, 0, KEY_ALL_ACCESS, &hKey  ) == ERROR_SUCCESS ) ;

	RegCloseKey( hKey ) ;

	_EcriturePreferences	=	TRUE ;


	CString	NomEtat ;
	NomEtat.Format( "Etats\\%d", No ) ;
	const BOOL b = SauveEtat( NomEtat ) ;

	ResumeThread( _hThread ) ;
	PeintureFenetre.Unlock() ;

	return b ;
	}

BOOL	CEconomiseur::Load( void )
	{
	PeintureFenetre.Lock() ;
	SuspendThread( _hThread ) ;
	const CString	Clef	=	"Software\\Lucien PILLONI\\Economiseurs d'écrans\\" + _Nom ;
	_NoCourant	++ ;

	CString	SousClef ;
	SousClef.Format( "%s\\Etats\\%d", (const char *)Clef, _NoCourant ) ;

	BOOL	Ok	=	TRUE ;
	HKEY	hKey ;
	if ( RegOpenKeyEx( HKEY_CURRENT_USER, SousClef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		{
		_NoCourant	=	1 ;
		SousClef.Format( "%s\\Etats\\%d", (const char *)Clef, _NoCourant ) ;

		if ( RegOpenKeyEx( HKEY_CURRENT_USER, SousClef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
			Ok = FALSE ;
		}

	if ( Ok )
		{
		RegCloseKey( hKey ) ;

		_EcriturePreferences	=	FALSE ;

		CString	NomEtat ;
		NomEtat.Format( "Etats\\%d", _NoCourant ) ;

		Ok	=	ChargeEtat( NomEtat ) ;
		}

	PeintureFenetre.Unlock() ;
	ResumeThread( _hThread ) ;

	return Ok ;
	}

void	CEconomiseur::Etat( const char * No, const char * Val,  CString & i )
	{
	Preference( Val, i, No ) ;
	}

void	CEconomiseur::Etat( const char *  No, const char * Val,  DWORD & i )
	{
	Preference( Val, i, No ) ;
	}

void	CEconomiseur::Etat( const char *  No, const char * Val,  int & i )
	{
	Preference( Val, i, No ) ;
	}

void	CEconomiseur::Etat( const char *  No, const char * Val,  double  & i )
	{
	Preference( Val, i, No ) ;
	}

CDC & CEconomiseur::GetDC( void ) const
{
	return DC ;
}
