// Script.cpp: implementation of the CScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Instal.h"
#include "Script.h"
#include "sclib.h"
#include <logfile.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define PROGRAM_NAME "PROGRAMNAME"
#define INSTALLATION "INSTALLATION"
#define CREATE_DIR	"CREATEDIR"
#define COPY_FILE	"COPYFILE"
#define COPY_DIR	"COPYDIR"
#define CREATE_SHORTCUT	"CREATESHORTCUT"
#define DELETE_FILE	"DELETEFILE"
#define DELETE_DIR	"DELETEDIR"
#define MESSAGE_OK	"MESSAGEOK"
#define MESSAGE_KO	"MESSAGEKO"

#define OPEN		"OPEN"

CLogFile	LogFile( "\\LPInstall.log" ) ;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScript::CScript( const char * pFileName )
{
	_Ok	=	FALSE ;
	if ( pFileName == 0 )
		pFileName	= "Install.script" ;

	CString FullName	=	GetFullPath( pFileName ) ;

	LogFile.Write( "Using script file : ", FullName ) ;

	CStdioFile	File ;
	if ( File.Open( FullName, CFile::modeRead | CFile::typeText ))
		{
		ReadScript( File ) ;
		}
	else
		{
		LogFile.Write( "Error, script file not found" ) ;
		}

	GetDefaultInstallDir() ;
	_Filter.Add( "$AppInstallDir", _InstallDir ) ;

	char CurrentDir[_MAX_PATH] ;
	GetCurrentDirectory(sizeof( CurrentDir ), CurrentDir ) ;

	_Filter.Add("$SourceDir", CurrentDir ) ;
}

CScript::~CScript()
{

}

///////////////////////////////////////////////////////////////////////////////
// Lecture du fichier script pour memoriser les lignes
///////////////////////////////////////////////////////////////////////////////
void CScript::ReadScript(CStdioFile & File)
{
	CString	Line ;
	while ( File.ReadString( Line ))
		{
		LogFile.Write( Line ) ;
		if ( CorrectLine( Line ))
			_ScriptLines.AddTail( Line ) ;
		}
}



///////////////////////////////////////////////////////////////////////////////
// Corrige eventuellement la ligne et dit si on peut l'ajouter au script
///////////////////////////////////////////////////////////////////////////////
BOOL CScript::CorrectLine(CString & Line)
{
	Line.TrimLeft() ;
	Line.TrimRight() ;

	if( Line.IsEmpty())
		return FALSE ;

	if ( Line[0]	== ';' )		// Commentaire
		return FALSE ;

	CString	FirstPart	=	Line.SpanExcluding( ";,=/\\.+)([] \t" ) ;
	FirstPart.MakeUpper() ;

	if ( FirstPart	==	PROGRAM_NAME )
		return TRUE ;
	if ( FirstPart	==	INSTALLATION )
		return TRUE ;
	if ( FirstPart	==	CREATE_DIR )
		return TRUE ;
	if ( FirstPart	==	COPY_FILE )
		return TRUE ;
	if ( FirstPart	==	COPY_DIR )
		return TRUE ;
	if ( FirstPart	==	CREATE_SHORTCUT )
		return TRUE ;
	if ( FirstPart	==	DELETE_FILE )
		return TRUE ;
	if ( FirstPart	==	DELETE_DIR )
		return TRUE ;
	if ( FirstPart	==	MESSAGE_OK )
		return TRUE ;
	if ( FirstPart	==	MESSAGE_KO )
		return TRUE ;
	if ( FirstPart	==	OPEN )
		return TRUE ;
	return FALSE ;
}


///////////////////////////////////////////////////////////////////////////////
// Retourne le n ieme mot de la chaine. Les chaines entre cotes sont considerees
// comme des mots uniques, meme s'il contiennent des separateurs
///////////////////////////////////////////////////////////////////////////////
CString CScript::GetPart(const CString & String, int NoPart)
{
	int IndiceDebut	=	0 ;
	int IndiceFin	=	0 ;
	CString Morceau ;

	for ( int i = 0; i <= NoPart; i++ )
		{
		IndiceDebut	=	IndiceFin ;
		Morceau	= ProchainMorceau( String, IndiceDebut, IndiceFin ) ;

		if ( Morceau.IsEmpty())
			return "" ;
		}

	return Morceau ;
}

///////////////////////////////////////////////////////////////////////////////
// Trouver le morceau de chaine qui commence a debut.
// 
///////////////////////////////////////////////////////////////////////////////
CString CScript::ProchainMorceau(const CString & Chaine, int & Debut, int & Fin)
{
#define SEPARATEURS	" ;,/\\()[]'\t"
#define SEPARATEUR(x)	(strchr( SEPARATEURS, x ) != NULL )

	const int LongueurChaine	=	Chaine.GetLength() ;
	if ( Debut >= LongueurChaine )
		return "" ;

	///////////////////////////////////////////////////////////////////////////
	// Passer les separateurs eventuels
	///////////////////////////////////////////////////////////////////////////
	while ( (Debut <= LongueurChaine) && SEPARATEUR( Chaine[Debut] ) )
		Debut ++ ;

	///////////////////////////////////////////////////////////////////////////
	// On est soit sur la fin de la chaine, soit sur le debut du morceau
	///////////////////////////////////////////////////////////////////////////
	if ( Debut >= LongueurChaine )
		// On est sur la fin de la chaine
		return "" ;


	///////////////////////////////////////////////////////////////////////////
	// A partir d'ici, deux cas possibles :
	// On est sur le debut d'une chaine, le morceau, c'est tout, jusqu'a
	// la prochaine cote
	// On est par sur le debut d'une chaine, le morceau, c'est tout
	// jusqu'au prochain separateur
	///////////////////////////////////////////////////////////////////////////

	if ( Chaine[Debut] == '\"' )
		{
		// Passer la premiere cote
		Debut ++ ;
		if ( Debut >= LongueurChaine )
			// On est sur la fin de la chaine
			return "" ;

		// Chaine, trouver la cote de fin
		CString C( Chaine.Right( LongueurChaine - Debut )) ;

		Fin	=	C.Find( '\"' ) ;

		if ( Fin == -1 )
			return "" ;


		Fin += Debut + 1 ;
		return C.Left( Fin - Debut - 1 ) ;
		}
	else
		{
		// Mot, chercher le prochain sepatateur
		CString	C( Chaine.Right( LongueurChaine - Debut )) ;

		Fin	=	C.FindOneOf( SEPARATEURS ) ;

		if ( Fin == -1 )
			return "" ;

		Fin += Debut ;

		return C.Left(  Fin - Debut ) ;
		}
}


const CString &	CScript::GetInstallDir( void ) const
	{
	return _InstallDir ;
	}



void CScript::GetDefaultInstallDir()
{
	// recherche du mot cle INSTALLATION
	POSITION	Pos	=	_ScriptLines.GetHeadPosition() ;

	while ( Pos )
		{
		CString	ScriptLine	=	_ScriptLines.GetNext( Pos ) ;

		CString	Morceau	=	GetPart( ScriptLine, 0 ) ;
		Morceau.MakeUpper() ;

		if ( Morceau == INSTALLATION )
			{
			// Repertoire d'installation par defaut = deuxieme mot de la ligne
			_InstallDir	=	_Filter.Decode(GetPart( ScriptLine, 1 )) ;
			}
		}

	LogFile << "Script default installation directory : " << _InstallDir << CLogFile::endline ;
	}


void CScript::SetInstallDir( const char * pDir )
	{
	ASSERT( pDir ) ;

	_InstallDir	=	pDir ;
	_Filter.Change( "$AppInstallDir", pDir ) ;

	LogFile << "Installation directory changed to " << pDir << CLogFile::endline ;
	}

BOOL CScript::ExecuteScript( CProgressWnd * )
	{
	_Ok = FALSE ;
	POSITION Pos	=	_ScriptLines.GetHeadPosition() ;

	while ( Pos )
		{
		CString ScriptLine	=	_ScriptLines.GetNext( Pos ) ;

		LogFile << "Executing script line " << ScriptLine << CLogFile::endline ;

		if ( ! ExecuteLine( ScriptLine ))
			return FALSE ;
		}

	_Ok = TRUE ;
	return TRUE ;
	}

BOOL CScript::ExecuteLine(const CString & CodedLine)
{
	CString	Line	=	_Filter.Decode( CodedLine ) ;

	CString FirstPart	=	GetPart( Line, 0 ) ;
	FirstPart.MakeUpper() ;

	if ( FirstPart	==	CREATE_DIR )
		return CreateDir( Line ) ;

	if ( FirstPart	==	COPY_FILE )
		return CopyFile( Line ) ;

	if ( FirstPart	==	COPY_DIR )
		return CopyDir( Line ) ;

	if ( FirstPart	==	CREATE_SHORTCUT )
		return CreateShortcut( Line ) ;

	if ( FirstPart	==	DELETE_FILE )
		return DeleteFile( Line ) ;

	if ( FirstPart	==	DELETE_DIR )
		return DeleteDir( Line ) ;

	if ( FirstPart	==	OPEN )
		return Open( Line ) ;

	LogFile.Write( "Unknown script line, not executed" ) ;
	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// CreateDir
// Creation d'un repertoire
// Syntaxe de la ligne :
//	CreateDir "<repertoire>"
///////////////////////////////////////////////////////////////////////////////
BOOL	CScript::CreateDir( const CString &Line )
	{
	CString	Dir	=	GetPart( Line, 1 );
	LogFile << "Creating directory " << Dir << CLogFile::endline ;

	if ( CreateDirectory(Dir, NULL))
		return TRUE ;

	LogLastError() ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// CopyFile
// Copie d'un fichier
// Syntaxe de la ligne :
//	CopyFile	"<fichier source>", "<fichier destination>"
///////////////////////////////////////////////////////////////////////////////
BOOL	CScript::CopyFile( const CString &Line )
	{
	CString	Source	=	GetPart( Line, 1 ) ;
	CString	Destination	=	GetPart( Line, 2 ) ;

	LogFile << "Copying file " << Source << " to " << Destination << CLogFile::endline ;

	if ( Source.IsEmpty() || Destination.IsEmpty())
		return FALSE ;

	if ( ::CopyFile(Source, Destination, FALSE))
		return TRUE ;

	LogLastError() ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// CopyDir
// Copie d'un repertoire
// Syntaxe de la ligne
//	CopyDir	"<repertoire source>", "<repertoire destination>"
///////////////////////////////////////////////////////////////////////////////
BOOL	CScript::CopyDir( const CString &Line )
	{
	const CString	RepertoireSource	=	GetPart( Line, 1 ) ;
	const CString	RepertoireDestination	=	GetPart( Line, 2 ) ;

	LogFile << "Copying directory " << RepertoireSource ;
	LogFile << " to " << RepertoireDestination << CLogFile::endline ;

	return CopieRepertoire( RepertoireSource, RepertoireDestination ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Effacement recursif d'un repertoire
///////////////////////////////////////////////////////////////////////////////
BOOL	CScript::DeleteDir( const CString &Line )
	{
	const CString Rep	=	GetPart( Line, 1 ) ;
	return EffaceRepertoire( Rep ) ;
	}

BOOL	CScript::DeleteFile( const CString &Line )
	{
	CString Fichier	=	GetPart( Line, 1 ) ;
	if  ( ::DeleteFile( Fichier ))
		return TRUE ;

	LogLastError() ;
	return TRUE ;
	}

BOOL	CScript::CreateShortcut( const CString &Line )
	{
	SHORTCUTSTRUCT ShortCut ;

	strcpy( ShortCut.szLink,		GetPart( Line, 1)) ;
	strcpy( ShortCut.szTargetFile,	GetPart( Line, 2)) ;
	strcpy( ShortCut.szDescription, GetPart( Line, 3)); ;
	strcpy( ShortCut.szIconFile, ShortCut.szTargetFile ) ;
	ShortCut.IconIndex	= atoi( GetPart( Line, 4)) ;
	strcpy( ShortCut.szWDirectory, _InstallDir ) ;
	ShortCut.ShowCmd	=	SW_SHOW ;
	strcpy( ShortCut.szArguments, "" ) ;

	LogFile << "Creating shortcut " << ShortCut.szLink << " to " << ShortCut.szTargetFile << CLogFile::endline ;

	InitializeSCLib() ;
	::CreateShortcut( &ShortCut ) ;
	UnInitializeSCLib() ;
	return TRUE ;
	}

BOOL CScript::CopieRepertoire(const char * RepertoireSource, const char * RepertoireDestination )
{
	CreateDirectory( RepertoireDestination, NULL ) ;
	SetCurrentDirectory( RepertoireSource ) ;

	WIN32_FIND_DATA fData ;

	CString	Rep( RepertoireSource ) ;
	Rep += "\\*.*" ;

	HANDLE h	=	FindFirstFile( Rep, &fData) ;
	BOOL Continue	=	(h != INVALID_HANDLE_VALUE) ;
	while ( Continue )
		{
		if ( strcmp( fData.cFileName, "." ) && strcmp( fData.cFileName, ".." ))
			{
			// Reconstitution des noms absolus a partir des noms relatifs obtenus
			CString	Source(RepertoireSource ) ;
			Source += '\\' ;
			Source += fData.cFileName ;
			CString Destination(	RepertoireDestination ) ;
			Destination += '\\' ;
			Destination += fData.cFileName ;

			if ( fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
				// Copie recursive
				CopieRepertoire( Source, Destination ) ;
				}
			else
				{
				if ( ! ::CopyFile( Source, Destination, FALSE ))
					{
					LogLastError() ;
					return FALSE;
					}
				}
			}

		Continue	=	FindNextFile( h, &fData ) ;
		}

	FindClose( h ) ;
	return TRUE ;
}


BOOL CScript::EffaceRepertoire(const char * Repertoire )
{
	WIN32_FIND_DATA fData ;

	CString	Rep( Repertoire ) ;
	Rep += "\\*.*" ;

	HANDLE h	=	FindFirstFile( Rep, &fData) ;
	BOOL Continue	=	(h != INVALID_HANDLE_VALUE) ;
	while ( Continue )
		{
		if ( strcmp( fData.cFileName, "." ) && strcmp( fData.cFileName, ".." ))
			{
			// Reconstitution des noms absolus a partir des noms relatifs obtenus
			CString	Source( Repertoire ) ;
			Source += '\\' ;
			Source += fData.cFileName ;
	
			if ( fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
				// Destruction recursive
				if ( !EffaceRepertoire( Source ))
					{
					LogLastError() ;
					return FALSE ;
					}
				}
			else
				{
				if ( ! ::DeleteFile( Source ))
					return FALSE;
				}
			}

		Continue	=	FindNextFile( h, &fData ) ;
		}

	RemoveDirectory( Repertoire ) ;

	FindClose( h ) ;
	return TRUE ;
}

BOOL CScript::Open(const CString & Line)
{
	CString	CmdLine	=	GetPart( Line, 1 ) ;
	
	return (int)ShellExecute( NULL, "open", CmdLine, NULL, _InstallDir,  SW_SHOW )> 31 ;
}

DWORD CScript::DiskSpace()
{
	DWORD	Taille	=	0 ;
	POSITION Pos	=	_ScriptLines.GetHeadPosition() ;

	while ( Pos )
		{
		CString ScriptLine	=	_ScriptLines.GetNext( Pos ) ;
		CString	Part	=	GetPart( ScriptLine, 0 ) ;
		Part.MakeUpper() ;

		if ( Part == COPY_FILE )
			{
			CString Source	=	GetPart( ScriptLine, 1 ) ;

			Taille += TailleFichier( _Filter.Decode( Source) ) ;
			}
		else
			if ( Part	== COPY_DIR )
				{
				CString Source	=	GetPart( ScriptLine, 1 ) ;

				Taille += TailleRepertoire( _Filter.Decode( Source) ) ;
				}
		}

	return Taille ;
}

DWORD CScript::TailleFichier(const char * NomFichier)
{
	CFileStatus Status ;

	if ( CFile::GetStatus(NomFichier, Status))
		return (DWORD)(Status.m_size+1023)/1024 ;
	else
		return 0 ;
}

DWORD CScript::TailleRepertoire(const char * Repertoire)
{
	DWORD Taille	=	0 ;
	WIN32_FIND_DATA fData ;

	CString	Rep( Repertoire ) ;
	Rep += "\\*.*" ;

	HANDLE h	=	FindFirstFile( Rep, &fData) ;
	BOOL Continue	=	(h != INVALID_HANDLE_VALUE) ;
	while ( Continue )
		{
		if ( strcmp( fData.cFileName, "." ) && strcmp( fData.cFileName, ".." ))
			{
			// Reconstitution des noms absolus a partir des noms relatifs obtenus
			CString	Source(Repertoire) ;
			Source += '\\' ;
			Source += fData.cFileName ;
		
			if ( fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
				// Copie recursive
				Taille += TailleRepertoire( Source ) ;
				}
			else
				{
				Taille += TailleFichier( Source ) ;
				}
			}

		Continue	=	FindNextFile( h, &fData ) ;
		}

	FindClose( h ) ;

	return Taille ;
}

BOOL CScript::ScriptOk() const
{
	return _Ok ;
}

///////////////////////////////////////////////////////////////////////////////
// Chercher le nom de l'application dans le script
///////////////////////////////////////////////////////////////////////////////
CString	CScript::GetApplicationName( void )
	{
		// recherche du mot cle INSTALLATION
	POSITION	Pos	=	_ScriptLines.GetHeadPosition() ;

	while ( Pos )
		{
		CString	ScriptLine	=	_ScriptLines.GetNext( Pos ) ;

		CString	Morceau	=	GetPart( ScriptLine, 0 ) ;
		Morceau.MakeUpper() ;

		if ( Morceau == PROGRAM_NAME )
			{
			CString	ProgramName	=	GetPart( ScriptLine, 1 ) ;
			return ProgramName ;
			}
		}

	return "" ;
	}

///////////////////////////////////////////////////////////////////////////////
// Retourne le message de fin de l'installation, en fonction du success ou de
// l'echec
///////////////////////////////////////////////////////////////////////////////
CString CScript::MessageTermine()
{
	CString	Message ;
	if ( _Ok )
		Message.LoadString( IDS_OK ) ;
	else
		Message.LoadString( IDS_KO ) ;

	return Message ;
}

void CScript::LogLastError()
{
	LPVOID lpMsgBuf;

	FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
					(LPTSTR) &lpMsgBuf,
					0,
					NULL );


	LogFile << "System error : " << (const char *)lpMsgBuf << CLogFile::endline ;

	// Free the buffer.
	LocalFree( lpMsgBuf );
}



// Get the full path name if non is given in the path
// because this f..... windows set the current path to the desktop when you
// drop a file on an exe
CString CScript::GetFullPath(const char * FilePath)
{
	char	CurrentDirectory[_MAX_PATH] ;
	GetCurrentDirectory( sizeof( CurrentDirectory ), CurrentDirectory ) ;

	// Set the path to the exe path
	char	ExePath[_MAX_PATH] ;
	GetModuleFileName( GetModuleHandle(NULL), ExePath, sizeof( ExePath )) ;

	char Drive[ _MAX_DRIVE ] ;
	char Path[ _MAX_PATH ] ;
	_splitpath(ExePath, Drive, Path, 0, 0 ) ;
	_makepath(  ExePath, Drive, Path, NULL, NULL ) ;

	SetCurrentDirectory( ExePath ) ;

	char Result[_MAX_PATH] ;
	char * P ;
	GetFullPathName( FilePath, sizeof( Result ), Result, &P ) ;

	SetCurrentDirectory( CurrentDirectory ) ;
	return Result ;
}
