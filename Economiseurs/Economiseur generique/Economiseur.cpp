///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.CPP
//	Implementation de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <string.h>
#include "resource.h"
#include "economiseur.h"
//#include <RegistrationKey.h>
//#include <PropPageRegistering.h>
//#include <DlgPriorite.h>

extern HWND hMainWindow ;
CEconomiseur*	CEconomiseur::_pTheOnlyOne = 0 ;
BOOL			CEconomiseur::_Fini = TRUE ;
HWND			CEconomiseur::_hWnd ;
HANDLE			CEconomiseur::_hThreadFini ;

static const int	PrioritesThread[NB_PRIORITE] =
		{ THREAD_PRIORITY_HIGHEST,
		  THREAD_PRIORITY_ABOVE_NORMAL,
		  THREAD_PRIORITY_NORMAL,
		  THREAD_PRIORITY_BELOW_NORMAL,
		  THREAD_PRIORITY_LOWEST } ;

CCriticalSection		PeintureFenetre ;
CDC CEconomiseur::DC ;
int		CEconomiseur::Largeur ;
int		CEconomiseur::Hauteur ;

CEconomiseur::CEconomiseur( const CString & Nom )
{
	ASSERT( _pTheOnlyOne==	0 ) ;
	hPalette			=	0 ;
	_pTheOnlyOne		=	this ;
	_PrioriteThread		=	2 ;

	_Nom				=	Nom ;
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

	if ( ! Apercu())
		{
		CRect R ;
		HDC hDC	=	::GetDC( NULL ) ;
		GetClipBox( hDC, R ) ;
		::ReleaseDC( NULL, hDC ) ;

		::SetWindowPos( hWnd,  0, R.left, R.top, R.Width(), R.Height(), SWP_NOACTIVATE | SWP_NOZORDER ) ;
		}

	CRect	R ;
	::GetClientRect( hWnd, R ) ;
	
	Largeur	=	R.Width() ;
	Hauteur	=	R.Height() ;

	//	Un peu de pub, on laisse les gens tranquilles dans le mode apercu
	//
	//
	if ( ! Apercu())
		{
//		CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
/*
		if ( pKey->IsLocked())
			{
			// Creation de la fenetre d'explication SHAREWARE
			const char *	pClass	=	AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW, 0, (HBRUSH)GetStockObject( BLACK_BRUSH )) ;
			CShareWare *	pShareWare	=	new CShareWare ;
			pShareWare->CreateEx( WS_EX_TOPMOST, pClass, "", WS_POPUP | WS_VISIBLE, 0, 0, 100, 100, hWnd, 0 ) ;

			pShareWare->Invalidate( TRUE ) ;
			pShareWare->UpdateWindow() ;
			}
*/
		}
}

void	CEconomiseur::Configuration( CPropertySheet * pPage )
{
//	pPage->AddPage( new CDlgPriorite ) ;

//	CRegistrationKey*	pKey	=	CRegistrationKey::GetKey() ;
	
//	if ( pKey->IsLocked())
//		pPage->AddPage( new CPropPageRegistering( IDD_PROPPAGE_REGISTERING ) ) ;

}

void	CEconomiseur::PeintFenetre( CDC &, const CRect& )
{
}

void CEconomiseur::Preferences()
{
	Preference( "Priorite", _PrioriteThread ) ;
	if ( _PrioriteThread < 0 )
		_PrioriteThread	=	0 ;

	if ( _PrioriteThread >= NB_PRIORITE )
		_PrioriteThread	=	NB_PRIORITE-1 ;
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

		RegCloseKey( hKey ) ;
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

		RegCloseKey( hKey ) ;
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
		RegCloseKey( hKey ) ;
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
		RegCloseKey( hKey ) ;
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
	SetThreadPriority( _hThread, PrioritesThread[ _PrioriteThread ] ) ;

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

/*	CString Message ;
	Message.LoadString( IDS_MESSAGE_SHAREWARE ) ;

	dc.DrawText( Message, R, DT_TOP | DT_LEFT | DT_WORDBREAK ) ;*/
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
	PeintureFenetre.Lock() ;
	PeintFenetre( Dc, R ) ;
	PeintureFenetre.Unlock() ;
	}


CDC & CEconomiseur::GetDC( void ) const
{
	return DC ;
}

///////////////////////////////////////////////////////////////////////////////
// Configure
// Ouvre la boite de dialogue de configuration
///////////////////////////////////////////////////////////////////////////////
void CEconomiseur::Configure()
{
	CPropertySheet	Prop ;

	LitPreferences() ;
	Configuration(  &Prop ) ;

	if ( Prop.DoModal() == IDOK )
			EcritPreferences() ;
}

void CEconomiseur::SaveFile(const char * pFileName)
{
//	EcritFichier( pFileName, IDS_MAIN_SECTION, IDS_PRIORITE_THREAD, _PrioriteThread ) ;
//	EcritFichier( pFileName, IDS_MAIN_SECTION, IDS_NOIRCIR_ECRAN, NoircirEcran ) ;
}

void CEconomiseur::LoadFile(const char * pFileName)
{
//	LitFichier( pFileName, IDS_MAIN_SECTION, IDS_PRIORITE_THREAD, _PrioriteThread ) ;
//	LitFichier( pFileName, IDS_MAIN_SECTION, IDS_NOIRCIR_ECRAN, NoircirEcran ) ;
}

void CEconomiseur::EcritFichier(const char * pFileName, UINT IdStrSection, UINT IdsValueName, int Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;

	CString	ValueName ;
	ValueName.LoadString( IdsValueName ) ;

	CString Val ;
	Val.Format( "%d", Value ) ;

	::WritePrivateProfileString( SectionName, ValueName, Val, pFileName ) ;
}

void CEconomiseur::EcritFichier(const char * pFileName, UINT IdStrSection, UINT IdsValueName, double Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;

	CString	ValueName ;
	ValueName.LoadString( IdsValueName ) ;

	CString Val ;
	Val.Format( "%g", Value ) ;

	::WritePrivateProfileString( SectionName, ValueName, Val, pFileName ) ;
}

void CEconomiseur::LitFichier(const char * pFileName, UINT IdStrSection, UINT IdsValueName, int & Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;

	CString	ValueName ;
	ValueName.LoadString( IdsValueName ) ;

	Value = ::GetPrivateProfileInt( SectionName, ValueName, Value, pFileName ) ;
}

void CEconomiseur::LitFichier(const char * pFileName, UINT IdStrSection, UINT IdsValueName, double & Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;

	CString	ValueName ;
	ValueName.LoadString( IdsValueName ) ;

	CString Val ;
	Val.Format( "%g", Value ) ;

	char Buffer[100] ;

	::GetPrivateProfileString( SectionName, ValueName, Val, Buffer, sizeof( Buffer ), pFileName ) ;

	Value	=	atof( Buffer ) ;
}

void CEconomiseur::LitFichier(const char * pFileName, UINT IdStrSection, const TCHAR * ValueName, double & Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;

	CString Val ;
	Val.Format( "%g", Value ) ;

	char Buffer[100] ;

	::GetPrivateProfileString( SectionName, ValueName, Val, Buffer, sizeof( Buffer ), pFileName ) ;

	Value	=	atof( Buffer ) ;
}


void CEconomiseur::LitFichier(const char * pFileName, UINT IdStrSection, const TCHAR * ValueName, CString & Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;
	
	char Buffer[1000] ;
	
	::GetPrivateProfileString( SectionName, ValueName, Value, Buffer, sizeof( Buffer ), pFileName ) ;

	Value	=	Buffer  ;
}



void CEconomiseur::LitFichier(const char * pFileName, UINT IdStrSection, UINT IdsValueName, CString & Value)
{
	CString	SectionName ;
	SectionName.LoadString( IdStrSection ) ;
	
	char Buffer[1000] ;

	CString	ValueName ;
	ValueName.LoadString( IdsValueName ) ;

	::GetPrivateProfileString( SectionName, ValueName, Value, Buffer, sizeof( Buffer ), pFileName ) ;

	Value	=	Buffer  ;
}
