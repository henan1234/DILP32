///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.CPP
//	Implementation de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <string.h>
#include <ddraw.h>

#include "ddutil.h"

#include "economiseur.h"


extern HWND hMainWindow ;
CEconomiseur*	CEconomiseur::_pTheOnlyOne = 0 ;
BOOL			CEconomiseur::_Fini = TRUE ;
HWND			CEconomiseur::_hWnd ;
HANDLE			CEconomiseur::_hThreadFini ;
LPDIRECTDRAW	CEconomiseur::_lpDD = 0 ;
LPDIRECTDRAWSURFACE CEconomiseur::_lpPrimary = 0 ;
LPDIRECTDRAWSURFACE CEconomiseur::_lpBackBuffer = 0 ;
LPDIRECTDRAWPALETTE CEconomiseur::_lpPalette = 0 ;

CString			CShareWare::_Message = "Ceci est logiciel SHAREWARE, vous avez le droit de le tester.\n"
										"Si vous decidez de l'utiliser régulièrement, vous devez acquérir la version enregistrée\n"
										"Consultez la boîte de configuration pour les modalités\n"
										"Merci d'utiliser ce logiciel\n"
										"Lucien PILLONI" ;

CCriticalSection		PeintureFenetre ;
int	CEconomiseur::Largeur ;
int	CEconomiseur::Hauteur ;
BOOL CEconomiseur::NoircirEcran ;

HANDLE	hThreadCalcul ;
HANDLE	hThreadAffichage ;
CRITICAL_SECTION	Critical ;

CEconomiseur::CEconomiseur( const CString & Nom, const CString & Enregistre )
{
	ASSERT( _pTheOnlyOne==	0 ) ;
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
				MessageBox( hWnd, "Vous avez eu suffisament de temps pour essayer ce logiciel, consultez la boîte de configuration",
								  "SHAREWARE",
							MB_OK | MB_ICONINFORMATION ) ;
				exit(0) ;
				}
			}
		}
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

BOOL CEconomiseur::RealizePalette( )
{
	if ( ! _lpPrimary )
		return FALSE ;

	if ( ! _lpPalette ) 
		return FALSE ;

	_lpPrimary->SetPalette( _lpPalette ) ;
	if ( _lpBackBuffer )
		_lpBackBuffer->SetPalette( _lpPalette ) ;

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// ShareWare
// Retourne VRAI si ce logiciel a ete enregistre comme ShareWare
///////////////////////////////////////////////////////////////////////////////
BOOL CEconomiseur::ShareWare( void )
{
	char	Buffer[100] ;
	DWORD	Taille	;

	// Si c'est moi, je vais quand meme pas payer...
	Taille	=	sizeof( Buffer ) ;
	GetUserName( Buffer, &Taille) ;

	CharUpper( Buffer ) ;
	const int Nb	= lstrlen( Buffer ) ; 

	for ( int i = 0; i < Nb; i++)
		Buffer[i] = Buffer[i]+1 ;
	

	if ( (Buffer[0] == 'M') || (Buffer[0] == 'Q') )
	{
		if ((Buffer[1] == 'V') || (Buffer[1] == 'Q') || (Buffer[1] == 'J') )
		{
		if ( (Buffer[2] == 'M') || (Buffer[2] == 'J') || (Buffer[2] == 'D') || (Buffer[2] == 0))
			return FALSE ;
		}
	}

	const BOOL	Memo	=	_EcriturePreferences ;
	_EcriturePreferences	=	FALSE ;
	CString	Valeur ;
	Preference( "Total", Valeur ) ;
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

/*
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
*/



DWORD __stdcall Affichage( LPVOID  )
	{
	CEconomiseur * pEco	= CEconomiseur::GetEconomiseur() ;

	while ( ! CEconomiseur::_Fini )
		{
		pEco->_lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, 0) ;

		//SuspendThread( hThreadCalcul ) ;
		EnterCriticalSection( &Critical ) ;
		pEco->Affichage() ;
		LeaveCriticalSection( &Critical ) ;
		
		pEco->_lpPrimary->Flip(0,DDFLIP_WAIT) ;
		//ResumeThread( hThreadCalcul ) ;
		}

	return 0 ;
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

	InitDirectDraw() ;

	InitSave( hWnd ) ;


	InitializeCriticalSection( &Critical ) ;

	DWORD	Id ;
	hThreadCalcul		=	CreateThread( NULL, 0, Economisage, 0, CREATE_SUSPENDED, &Id ) ;
	SetThreadPriority( _hThread, THREAD_PRIORITY_HIGHEST ) ;

	hThreadAffichage	=	CreateThread( NULL, 0, ::Affichage, 0, CREATE_SUSPENDED, &Id ) ;
	//SetThreadPriority( _hThread, THREAD_PRIORITY_ABOVE_NORMAL ) ;

#ifdef _DEBUG
	ShowWindow( hWnd, SW_SHOW ) ;
#else
	ShowWindow( hWnd, SW_MAXIMIZE ) ;
#endif
	ResumeThread( hThreadCalcul ) ;
	ResumeThread( hThreadAffichage ) ;
}	

//	===========================================================================
//	Economisage
//	Fait la boucle de l'economiseur dans un thread separe
//	===========================================================================
DWORD __stdcall Economisage( LPVOID  )
	{
	CEconomiseur * pEco	= CEconomiseur::GetEconomiseur() ;
	// ------------------------------------------------------------------------
	//	Ceci est la boucle principale de l'economiseur
	// ------------------------------------------------------------------------
/*	BOOL	BlankOccuring ;

	while	( ! CEconomiseur::_Fini )
		{
		if( CEconomiseur::_lpPrimary->IsLost() != DD_OK )
			CEconomiseur::_lpPrimary->Restore() ;

		if ( CEconomiseur::_lpBackBuffer->IsLost() != DD_OK )
			CEconomiseur::_lpBackBuffer->Restore() ;

		while ( (!CEconomiseur::_Fini) && (!BlankOccuring )) ;
			{
			pEco->Calcul() ;
			pEco->_lpDD->GetVerticalBlankStatus( & BlankOccuring ) ;
			}
		
		pEco->Affichage() ;
		CEconomiseur::_lpPrimary->Flip(0, 0) ;
		}
*/
	while ( ! CEconomiseur::_Fini )
		{
		pEco->Calcul() ;
		}

	return 0 ;
	}
//	===========================================================================
//	Fonction appelee par SaverWndProc pour demander la fin du screen saver
//	===========================================================================
void CEconomiseur::Fini( void )
{
	_Fini			=	TRUE ;

	WaitForSingleObject( hThreadCalcul, 1000 ) ;
	WaitForSingleObject( hThreadAffichage, 1000 ) ;

	FiniDirectDraw() ;
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
	cs.cx	=	250 ;
	cs.cy	=	120 ;
	cs.x	=	GetSystemMetrics( SM_CXSCREEN ) - cs.cx - 2 ;
	cs.y	=	GetSystemMetrics( SM_CYSCREEN ) - cs.cy - 2 ;
	cs.style=	WS_POPUP | WS_VISIBLE | WS_DLGFRAME ;
	cs.dwExStyle=	WS_EX_TOPMOST | WS_EX_WINDOWEDGE ;
	return CWnd::PreCreateWindow(cs);
}

void CEconomiseur::UpdateFenetre( CDC & Dc, const CRect & R )
	{
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


void CEconomiseur::Configuration( CPropertySheet *  )
	{
	}


void CEconomiseur::InitDirectDraw( void )
{
	HRESULT ddrval =	DirectDrawCreate( NULL, &_lpDD, NULL ) ;
	if ( ddrval != DD_OK )
		DDErreur( ddrval ) ;

	_lpDD->SetCooperativeLevel( _hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN ) ;

	DDSURFACEDESC	ddsd ;
	ddsd.dwSize	=	sizeof( ddsd ) ;
	ddsd.dwFlags=	DDSD_CAPS | DDSD_BACKBUFFERCOUNT ;
	ddsd.ddsCaps.dwCaps	=	DDSCAPS_PRIMARYSURFACE | DDSCAPS_COMPLEX | DDSCAPS_FLIP ;
	ddsd.dwBackBufferCount	=	1 ;

	ddrval	=	_lpDD->CreateSurface( &ddsd, &_lpPrimary, NULL ) ;
	if ( ddrval != DD_OK )
		DDErreur( ddrval ) ;

	DDSCAPS	ddscaps ;
	ddscaps.dwCaps	=	DDSCAPS_BACKBUFFER ;
	ddrval	=	_lpPrimary->GetAttachedSurface( &ddscaps, &_lpBackBuffer ) ;
	if ( ddrval != DD_OK )
		DDErreur( ddrval ) ;
}


void CEconomiseur::DDErreur( HRESULT ddrval )
{
const char * pMessage =
	"Cette erreur est due a l'utilisation de DirectDraw\nVérifiez qu'il est bien installé" ;
#define MESSAGE( e )	case e : MessageBox( NULL, pMessage, #e, MB_OK | MB_ICONEXCLAMATION ) ; break ;

	switch( ddrval )
		{
		MESSAGE ( DDLOCK_SURFACEMEMORYPTR		)
		MESSAGE ( DDERR_ALREADYINITIALIZED		)
		MESSAGE ( DDERR_CANNOTATTACHSURFACE		)
		MESSAGE ( DDERR_CANNOTDETACHSURFACE		)
		MESSAGE ( DDERR_CURRENTLYNOTAVAIL		)
		MESSAGE ( DDERR_EXCEPTION				)
		MESSAGE ( DDERR_GENERIC				) 
		MESSAGE ( DDERR_HEIGHTALIGN			)
		MESSAGE ( DDERR_INCOMPATIBLEPRIMARY		)
		MESSAGE ( DDERR_INVALIDCAPS			)
		MESSAGE ( DDERR_INVALIDCLIPLIST			)
		MESSAGE ( DDERR_INVALIDMODE			)
		MESSAGE ( DDERR_INVALIDOBJECT			)
		MESSAGE ( DDERR_INVALIDPARAMS			)
		MESSAGE ( DDERR_INVALIDPIXELFORMAT		)
		MESSAGE ( DDERR_INVALIDRECT			)
		MESSAGE ( DDERR_LOCKEDSURFACES			)
		MESSAGE ( DDERR_NO3D				)
		MESSAGE ( DDERR_NOALPHAHW				)
		MESSAGE ( DDERR_NOCLIPLIST			)
		MESSAGE ( DDERR_NOCOLORCONVHW			)
		MESSAGE ( DDERR_NOCOOPERATIVELEVELSET		)
		MESSAGE ( DDERR_NOCOLORKEY			)
		MESSAGE ( DDERR_NOCOLORKEYHW			)
		MESSAGE ( DDERR_NODIRECTDRAWSUPPORT		)
		MESSAGE ( DDERR_NOEXCLUSIVEMODE			)
		MESSAGE ( DDERR_NOFLIPHW				)
		MESSAGE ( DDERR_NOGDI				)
		MESSAGE ( DDERR_NOMIRRORHW			)
		MESSAGE ( DDERR_NOTFOUND				)
		MESSAGE ( DDERR_NOOVERLAYHW			)
		MESSAGE ( DDERR_NORASTEROPHW			)
		MESSAGE ( DDERR_NOROTATIONHW			)
		MESSAGE ( DDERR_NOSTRETCHHW			)
		MESSAGE ( DDERR_NOT4BITCOLOR			)
		MESSAGE ( DDERR_NOT4BITCOLORINDEX			)
		MESSAGE ( DDERR_NOT8BITCOLOR			)
		MESSAGE ( DDERR_NOTEXTUREHW			)
		MESSAGE ( DDERR_NOVSYNCHW				)
		MESSAGE ( DDERR_NOZBUFFERHW			)
		MESSAGE ( DDERR_NOZOVERLAYHW			)
		MESSAGE ( DDERR_OUTOFCAPS				)
		MESSAGE ( DDERR_OUTOFMEMORY			)
		MESSAGE ( DDERR_OUTOFVIDEOMEMORY			)
		MESSAGE ( DDERR_OVERLAYCANTCLIP			)
		MESSAGE ( DDERR_OVERLAYCOLORKEYONLYONEACTIVE	)
		MESSAGE ( DDERR_PALETTEBUSY			)
		MESSAGE ( DDERR_COLORKEYNOTSET			)
		MESSAGE ( DDERR_SURFACEALREADYATTACHED		)
		MESSAGE ( DDERR_SURFACEALREADYDEPENDENT		)
		MESSAGE ( DDERR_SURFACEBUSY			)
		MESSAGE ( DDERR_CANTLOCKSURFACE                   )
		MESSAGE ( DDERR_SURFACEISOBSCURED			)
		MESSAGE ( DDERR_SURFACELOST			)
		MESSAGE ( DDERR_SURFACENOTATTACHED		)
		MESSAGE ( DDERR_TOOBIGHEIGHT			)
		MESSAGE ( DDERR_TOOBIGSIZE			)
		MESSAGE ( DDERR_TOOBIGWIDTH			)
		MESSAGE ( DDERR_UNSUPPORTED			)
		MESSAGE ( DDERR_UNSUPPORTEDFORMAT			)
		MESSAGE ( DDERR_UNSUPPORTEDMASK			)
		MESSAGE ( DDERR_VERTICALBLANKINPROGRESS		)
		MESSAGE ( DDERR_WASSTILLDRAWING			)
		MESSAGE ( DDERR_XALIGN				)
		MESSAGE ( DDERR_INVALIDDIRECTDRAWGUID		)
		MESSAGE ( DDERR_DIRECTDRAWALREADYCREATED		)
		MESSAGE ( DDERR_NODIRECTDRAWHW			)
		MESSAGE ( DDERR_PRIMARYSURFACEALREADYEXISTS	)
		MESSAGE ( DDERR_NOEMULATION			)
		MESSAGE ( DDERR_REGIONTOOSMALL			)
		MESSAGE ( DDERR_CLIPPERISUSINGHWND		)
		MESSAGE ( DDERR_NOCLIPPERATTACHED			)
		MESSAGE ( DDERR_NOHWND				)
		MESSAGE ( DDERR_HWNDSUBCLASSED			)
		MESSAGE ( DDERR_HWNDALREADYSET			)
		MESSAGE ( DDERR_NOPALETTEATTACHED			)
		MESSAGE ( DDERR_NOPALETTEHW			)
		MESSAGE ( DDERR_BLTFASTCANTCLIP			)
		MESSAGE ( DDERR_NOBLTHW				)
		MESSAGE ( DDERR_NODDROPSHW			)
		MESSAGE ( DDERR_OVERLAYNOTVISIBLE			)
		MESSAGE ( DDERR_NOOVERLAYDEST			)
		MESSAGE ( DDERR_INVALIDPOSITION			)
		MESSAGE ( DDERR_NOTAOVERLAYSURFACE		)
		MESSAGE ( DDERR_EXCLUSIVEMODEALREADYSET		)
		MESSAGE ( DDERR_NOTFLIPPABLE			)
		MESSAGE ( DDERR_CANTDUPLICATE			)
		MESSAGE ( DDERR_NOTLOCKED				)
		MESSAGE ( DDERR_CANTCREATEDC			)
		MESSAGE ( DDERR_NODC				)
		MESSAGE ( DDERR_WRONGMODE				)
		MESSAGE ( DDERR_IMPLICITLYCREATED			)
		MESSAGE ( DDERR_NOTPALETTIZED			)
		MESSAGE ( DDERR_UNSUPPORTEDMODE			)
		MESSAGE ( DDERR_NOMIPMAPHW			)
		MESSAGE ( DDERR_INVALIDSURFACETYPE                )
		MESSAGE ( DDERR_DCALREADYCREATED			)
		MESSAGE ( DDERR_CANTPAGELOCK			)
		MESSAGE ( DDERR_CANTPAGEUNLOCK			)
		MESSAGE ( DDERR_NOTPAGELOCKED			)
		default :
			MessageBox( 0, "DirectDraw", "????", MB_OK ) ;
		}

	ExitProcess(0) ;
}

void CEconomiseur::FiniDirectDraw( void )
{
	_lpDD->RestoreDisplayMode() ;

	if ( _lpPrimary )
		_lpPrimary->Release() ;

	_lpPrimary = 0 ;

	if ( _lpDD )
		_lpDD->Release() ;

	_lpDD = 0 ;
}

void CEconomiseur::SetPalette( LPDIRECTDRAWPALETTE	lpPalette )
	{
	_lpPalette = lpPalette ;
	}