///////////////////////////////////////////////////////////////////////////////
// CRaccourci
//	Classe d'objets raccourcis vers un fichier, un document ou un programme
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winreg.h>
#include "resource.h"
#include "Raccourci.h"
#include "DlgIcone.h"
#include "sclib.h"

IMPLEMENT_SERIAL( CRaccourci, CObject, 0 ) ;

CRaccourci::CRaccourci()
	{
	_hIcon	=	0 ;
	}


CRaccourci::~CRaccourci()
	{
	if ( _hIcon )
		DestroyIcon( _hIcon ) ;
	}

void	CRaccourci::Serialize( CArchive & ar )
	{	
	CObject::Serialize( ar ) ;

	if ( ar .IsStoring())
		{
		ar << _Texte ;
		ar << _FichierIcone ;
		ar << _IndiceIcone ;
		ar << _NomFichier ;
		}
	else
		{
		ar >> _Texte ;
		ar >> _FichierIcone ;
		ar >> _IndiceIcone ;
		ar >> _NomFichier ;
		_hIcon	=	GetIcone() ;
		}
	}
		

void	CRaccourci::SetText( const CString & Texte )
	{
	_Texte	=	Texte ;
	}

void	CRaccourci::SetIcone( LPCSTR pFichier, WORD Indice )
	{
	_FichierIcone	=	pFichier ;
	_IndiceIcone	=	Indice ;

	if ( _hIcon )
		DestroyIcon( _hIcon ) ;

	_hIcon	=	0 ;

	_hIcon	=	GetIcone() ;
	}

void	CRaccourci::SetCommande( LPCSTR pCommande )
	{
	_NomFichier	=	pCommande ;
	}

HICON	CRaccourci::GetIcone( void )
	{
	if ( _hIcon )
		return _hIcon ;

	if ( ! _FichierIcone )
		_FichierIcone	=	_NomFichier ;

	HICON	hIcone	=	 ExtractIcon( AfxGetInstanceHandle(), _FichierIcone, _IndiceIcone ) ;

	if ( ! hIcone )
		{
		hIcone	=	ExtractAssociatedIcon( AfxGetInstanceHandle(),
										   _FichierIcone.GetBuffer( _MAX_PATH ),
										   &_IndiceIcone ) ;
		_FichierIcone.ReleaseBuffer() ;
		}

	return hIcone ;
	}

/////////////////////////////////////////////////////////////////////////////
// Active
//	Activer le programme ou le document reference par ce raccourci
/////////////////////////////////////////////////////////////////////////////
void	CRaccourci::Active( void )
	{
	AfxGetApp()->LoadStandardCursor( IDC_WAIT ) ;

	char	Directory[_MAX_PATH] ;
	_splitpath( _NomFichier, NULL, Directory, NULL, NULL ) ;
	ShellExecute( NULL, NULL, _NomFichier, NULL, Directory, SW_SHOWDEFAULT ) ;
	}


#ifdef	_DEBUG
void	CRaccourci::AssertValid( void ) const
	{
	CObject::AssertValid() ;
	ASSERT( _IndiceIcone >= 0 ) ;
	}

void	CRaccourci::Dump( CDumpContext & Dc ) const
	{
	CObject::Dump( Dc ) ;
	Dc << "Ligne de commande : " << _NomFichier << "\n" ;
	Dc << "Icone : " << _FichierIcone << ", " << _IndiceIcone << "\n" ;
	}
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropsRaccourci dialog


CPropsRaccourci::CPropsRaccourci(CWnd* pParent /*=NULL*/)
	: CDialog(CPropsRaccourci::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropsRaccourci)
	m_Nom = _T("");
	m_Commande = _T("");
	//}}AFX_DATA_INIT
}


void CPropsRaccourci::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropsRaccourci)
	DDX_Text(pDX, IDC_NOM, m_Nom);
	DDX_Text(pDX, IDC_LGCOMM, m_Commande);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropsRaccourci, CDialog)
	//{{AFX_MSG_MAP(CPropsRaccourci)
	ON_BN_CLICKED(IDC_ICONE, OnIcone)
	ON_BN_CLICKED(IDC_PARCOURIR, OnParcourir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropsRaccourci message handlers

void CPropsRaccourci::OnIcone() 
{
	UpdateData( TRUE ) ;

	if ( _NomFichierIcone.IsEmpty())
		_NomFichierIcone	=	m_Commande ;	

	CDlgIcone	Dlg ;

	Dlg.m_NomFichier	=	_NomFichierIcone ;
	Dlg._IndiceIcone	=	_IndiceIcone ;

	if ( Dlg.DoModal() == IDOK )
		{
		_NomFichierIcone 	=	Dlg.m_NomFichier ;
		_IndiceIcone		=	Dlg._IndiceIcone ;
		UpdateData( FALSE ) ;
		}
}

//////////////////////////////////////////////////////////////////////////////
// OnParcourir
//	Ouvre une boite de dialogue pour rechercher un fichier sur le disque
//////////////////////////////////////////////////////////////////////////////
void CPropsRaccourci::OnParcourir() 
{
	CString	FiltreExtensions ;
	FiltreExtensions.LoadString( IDS_FILTRE_RACCOURCI ) ;
	CFileDialog	Dlg(	TRUE,
					 	"EXE",
						m_Commande,
						OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_LONGNAMES,
						FiltreExtensions,
						this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		m_Commande	=	Dlg.GetPathName() ;
		UpdateData( FALSE ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Modifie le menu du raccourci avec les commandes enregistrees dans la registry
///////////////////////////////////////////////////////////////////////////////
void CRaccourci::ModifMenu( CMenu * pMenu, UINT PremiereCommande )
{
	ASSERT_VALID( pMenu ) ;

	char	Extension[ _MAX_EXT ] ;
	_splitpath( _NomFichier, NULL, NULL, NULL, Extension ) ;

	///////////////////////////////////////////////////////////////////////////
	// Chercher le type de fichier concerne
	///////////////////////////////////////////////////////////////////////////
	char	TypeFichier[ 255 ] ;

	lstrcpy( TypeFichier, GetFileType() ) ;

	if ( ! TypeFichier[0] )
		// Pas trouve le type de fichier
		return ;

	lstrcat( TypeFichier, "\\shell" ) ;

	HKEY	hKey ;

	// Acceder a la bonne sous branche
	if ( RegOpenKeyEx( HKEY_CLASSES_ROOT, TypeFichier, 0, KEY_ALL_ACCESS, &hKey )
		 == ERROR_SUCCESS )
		{
		// Parcourir les differentes commandes
		DWORD		Indice		=	0 ;
		char		KeyName[ _MAX_PATH ] ;
		DWORD		KeySize		=	sizeof( KeyName ) ;
		FILETIME	Time ;

		while ( RegEnumKeyEx( hKey, Indice, KeyName, &KeySize, NULL, NULL, 0, &Time ) == ERROR_SUCCESS )
			{
			HKEY	hCommande ;
			
 			// Type d'operation
			if ( RegOpenKeyEx( hKey, KeyName, 0, KEY_ALL_ACCESS, &hCommande ) == ERROR_SUCCESS )
				{
				char	NomCommande[ _MAX_PATH ] ;
				LONG	TailleBuffer	=	sizeof( NomCommande ) ;
				// Nom de la commande
				if ( RegQueryValue( hCommande, NULL, NomCommande, &TailleBuffer )!= ERROR_SUCCESS )
					NomCommande[0] = 0 ;

				if ( NomCommande[0] == 0 )
					lstrcpy( NomCommande, KeyName ) ;

				pMenu->InsertMenu( Indice, MF_BYPOSITION, PremiereCommande+Indice, NomCommande ) ;
				
				RegCloseKey( hCommande ) ;
				}

			Indice ++ ;
			KeySize	=	sizeof( KeyName ) ;
			}

		}

	RegCloseKey( hKey ) ;
}

void CRaccourci::Menu( UINT NoCommande )
{
	char	Extension[ _MAX_EXT ] ;
	_splitpath( _NomFichier, NULL, NULL, NULL, Extension ) ;

	// Type de fichier
	char	TypeFichier[ 255 ] ;

	lstrcpy( TypeFichier, GetFileType() ) ;

	if ( ! TypeFichier[0] )
		// Pas trouve le type de fichier
		return ;

	lstrcat( TypeFichier, "\\shell" ) ;

	HKEY	hKey ;

	// Acceder a la bonne sous branche
	if ( RegOpenKeyEx( HKEY_CLASSES_ROOT, TypeFichier, 0, KEY_ALL_ACCESS, &hKey )!= ERROR_SUCCESS )
		return ;

	char		KeyName[ _MAX_PATH ] ;
	DWORD		KeySize		=	sizeof( KeyName ) ;
	FILETIME	Time ;

	if ( RegEnumKeyEx( hKey, NoCommande, KeyName, &KeySize, NULL, NULL, 0, &Time ) != ERROR_SUCCESS )
		return ;

	HKEY	hCommande ;
			
 	// Type d'operation
	if ( RegOpenKeyEx( hKey, KeyName, 0, KEY_ALL_ACCESS, &hCommande ) != ERROR_SUCCESS )
		return ;

	char	LigneCommande[ _MAX_PATH ] ;
	LONG	TailleBuffer	=	sizeof( LigneCommande ) ;
	if ( RegQueryValue( hCommande, "command", LigneCommande, &TailleBuffer )!= ERROR_SUCCESS )
		return ;

	char	LigneDeCommande[ _MAX_PATH * 2 ] ;
	// Remplacer l'eventuel %1 par le nom du screen saver actif

	int	IndiceSrc	=	0 ;
	int	IndiceDst	=	0 ;
	char	*		pCommande	=	LigneCommande ;

	while ( pCommande[IndiceSrc] && IndiceDst < sizeof( LigneDeCommande ))
		{
		if ( (pCommande[IndiceSrc] == '%') && (pCommande[IndiceSrc+1]	==	'1' || pCommande[IndiceSrc+1] == 'l') )
			{
			lstrcpy( &LigneDeCommande[IndiceDst], _NomFichier ) ;
			IndiceDst +=	_NomFichier.GetLength() ;
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
// IsFolder, statique
// Retourne VRAI si le nom est le nom d'un repertoire
///////////////////////////////////////////////////////////////////////////////
BOOL CRaccourci::IsFolder( const char * Nom )
{
	// Est-ce un fichier ou un repertoire ?
	CFileStatus	Status ;
	CFile::GetStatus( Nom, Status ) ;

	if ( Status.m_attribute & CFile::directory )
		return TRUE ;
	else
		return FALSE ;
}


BOOL CRaccourci::IsDrive( const char * Nom )
{
	// Est-ce un fichier ou un repertoire ?
	CFileStatus	Status ;
	CFile::GetStatus( Nom, Status ) ;

	if ( Status.m_attribute & CFile::volume )
		return TRUE ;
	else
		return FALSE ;
}

///////////////////////////////////////////////////////////////////////////////
// Obtenir par tout moyen le type du fichier en regardant dans la registry
//	RETOUR :	Type du fichier
///////////////////////////////////////////////////////////////////////////////
CString CRaccourci::GetFileType( void ) const
{
	char	Extension[ _MAX_EXT ] ;
	_splitpath( _NomFichier, NULL, NULL, NULL, Extension ) ;

	///////////////////////////////////////////////////////////////////////////
	// Chercher le type de fichier concerne
	///////////////////////////////////////////////////////////////////////////
	if ( Extension[0] )
		{
		char	TypeFichier[ _MAX_PATH ] ;
		LONG	TailleTypeFichier	=	sizeof( TypeFichier ) ;
		
		if	( RegQueryValue( HKEY_CLASSES_ROOT, Extension, TypeFichier,
							   &TailleTypeFichier ) != ERROR_SUCCESS )
			return TypeFichier ;
		}

	
	///////////////////////////////////////////////////////////////////////////
	// Pas pu trouver l'extension, peut etre est-ce un repertoire ?
	///////////////////////////////////////////////////////////////////////////
	if ( IsFolder( _NomFichier ))
		return "Folder" ;

	///////////////////////////////////////////////////////////////////////////
	// Peut etre un disque ?
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	// Pas pu trouver l'extension, peut etre est-ce un repertoire ?
	///////////////////////////////////////////////////////////////////////////
	if ( IsDrive( _NomFichier ))
		return "Drive" ;

	return "" ;
}

///////////////////////////////////////////////////////////////////////////////
// Resoud un shortcut (.LNK) du shell
///////////////////////////////////////////////////////////////////////////////
void CRaccourci::ResoudShortCut( CString & PathName )
{
	InitializeSCLib() ;
	SHORTCUTSTRUCT	Sc ;

	lstrcpy( Sc.szLink, PathName ) ;

	if( ResolveShortcut(NULL, &Sc ) == SC_NoError )
		{
		PathName	=	Sc.szTargetFile ;
		}

	UnInitializeSCLib() ;
}

void CRaccourci::ResoudShortCut( LPSTR lpName )
{
	CString	Pn	=	lpName ;
	ResoudShortCut( Pn ) ;

	ASSERT( AfxIsValidAddress( lpName, Pn.GetLength()+1, TRUE )) ;
	lstrcpy( lpName, Pn ) ;
}
