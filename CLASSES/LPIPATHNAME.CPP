///////////////////////////////////////////////////////////////////////////////
// CLPIPathName
//	Facilite beaucoup le maniement des noms de fichiers et chemins
///////////////////////////////////////////////////////////////////////////////
#ifndef __AFXWIN_H__
#include <afxwin.h>
#endif

#include "LpiPathName.h"

IMPLEMENT_SERIAL( CLPIPathName, CObject, 1 ) ;

// Accessible for all
const CString	CLPIPathName::VALID_CHARACTERS		("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_!@#$%&=+אגהיטכךלןמעצפשüû(),") ;
const char		CLPIPathName::PATH_SEPARATOR		( '\\' ) ;
const char		CLPIPathName::EXTENSION_SEPARATOR	( '.' ) ;
const int		CLPIPathName::MAX_FILE_LENGTH		( 8 ) ;
const int		CLPIPathName::MAX_EXTENSION_LENGTH( 3 ) ;

// =============================== Private class, just for this module purpose
class CHPDiskAccessErrorMode
// Instanciate one object of this class when you want to change Windows drive
// checking mode ( SetErrorMode )
{
	public :
		CHPDiskAccessErrorMode( UINT Error ) { _Error = SetErrorMode( Error ) ; } ;
		~CHPDiskAccessErrorMode() { SetErrorMode( _Error ) ; } ;
	private :
		UINT	_Error ;
} ;

//+--------------------------------------------------------------------------
//+ Function   : Constructors
//+ Purpose    : purpose of a constructor !
//+				 Available constructors :
//+					-default :		empty path
//+					-String :		full path name
//+					-CLPIPathName :	copy constructor
//+					- Three strings : path, filename, extension
//+
//+ Parameters : Windows standard
//+
//+ Creation   : 2/6/94 Lucien PILLONI
//+
//+--------------------------------------------------------------------------
CLPIPathName::CLPIPathName()
{
	// Nothing particular to do
}

CLPIPathName::CLPIPathName( const CLPIPathName & PathName )
:_PathFileName( PathName._PathFileName )
{
	ASSERT_VALID( &PathName ) ;
}

CLPIPathName::CLPIPathName( const CString & PathNameString )
{
	_PathFileName	= PathNameString ;
	ASSERT_VALID( this ) ;
}

CLPIPathName::CLPIPathName( LPCSTR PathName )
{
	_PathFileName	= PathName ;
	ASSERT_VALID( this ) ;
}


CLPIPathName::CLPIPathName( const CString & PathName, const CString & FileName, const CString & Ext )
{
	ColleMorceaux( PathName, FileName, Ext ) ;
}

//+--------------------------------------------------------------------------
//+ Function   : Path
//+ Purpose    : return the path without the filename and without the extension
//+ Parameters : none
//+--------------------------------------------------------------------------
CString CLPIPathName::Path( void ) const
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	return	Chemin ;
}

//+--------------------------------------------------------------------------
//+ Function   : Path
//+ Purpose    : sets the path of the pathname object
//+ Parameters : string containing the path
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::Path( const CString & Path )
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	ColleMorceaux( Path, Fichier, Extension );
	ASSERT_VALID( this ) ;
	
	return TRUE ;
}


//+--------------------------------------------------------------------------
//+ Function   : SearchPath
//+ Purpose    : search the file in the PATH defined directories
//+ Parameters : none
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::SearchPath( const CString & EnvVariable )
{  
	char	Buffer[ _MAX_PATH ] ;
	
	_searchenv( GetFileWithExtension(), EnvVariable, Buffer ) ;
	
	if ( Buffer[0] )
		{
		// File found in the PATH directories
		*this = Buffer ;
		}
	return TRUE ;
}

//+--------------------------------------------------------------------------
//+ Function   : FileName
//+ Purpose    : return the filename without the pathname and without the extension
//+ Parameters : none
//+--------------------------------------------------------------------------
const CString CLPIPathName::FileName( void ) const
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	return	Fichier ;
}

//+--------------------------------------------------------------------------
//+ Function   : operators
//+ Purpose    : COnverti le nom de fichier en chaine de caracteres
//+ Parameters : 
//+--------------------------------------------------------------------------
CLPIPathName::operator	CString() const
{
	return _PathFileName ;
}

#ifdef WIN32
CLPIPathName::operator	LPCTSTR() const
{
	return(LPCTSTR)_PathFileName ; 
}
#else
CLPIPathName::operator	LPCSTR() const
{
	return(LPCSTR)_PathFileName ; 
}
#endif

//+--------------------------------------------------------------------------
//+ Function   : FileName
//+ Purpose    : sets the filename of the pathname object, without extension !
//+ Parameters : string containing the path
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::FileName( const CString & FileName )
{   
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	ColleMorceaux( Chemin, FileName, Extension );
	ASSERT_VALID( this ) ;
	
	return TRUE ;
}
    
//+--------------------------------------------------------------------------
//+ Function   : GetExtension
//+ Purpose    : return the extension without the pathname and without the filename
//+				 and without the "."
//+ Parameters : none
//+--------------------------------------------------------------------------
const CString	CLPIPathName::Extension( void ) const
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	return	Extension ;
}

//+--------------------------------------------------------------------------
//+ Function   : Extension
//+ Purpose    : sets the extension of the pathname object
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::Extension( const CString & Ext )
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	ColleMorceaux( Chemin, Fichier, Ext );
	ASSERT_VALID( this ) ;
	
	return TRUE ;
}


//+--------------------------------------------------------------------------
//+ Function   : GetWithFileExtension
//+ Purpose    : return the filename with the "." and the extension
//+ Parameters : none
//+--------------------------------------------------------------------------
CString	 CLPIPathName::GetFileWithExtension( void ) const
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	if ( Extension.IsEmpty())
		return Fichier ;
	else
		return Fichier + EXTENSION_SEPARATOR + Extension ;
}

//+--------------------------------------------------------------------------
//+ Function   : SetEmptyExtension
//+ Purpose    : sets an empty extension of the pathname object
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::SetEmptyExtension( void )
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	ColleMorceaux( Chemin, Fichier, "" );
	ASSERT_VALID( this ) ;
	
	
	return TRUE ;
}

//+--------------------------------------------------------------------------
//+ Function   : GetPathComponents
//+ Purpose    : Divide the pathname in it's components
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
void	CLPIPathName::GetPathComponents( CStringList & ListOfComponents ) const
{
	ASSERT_VALID( this ) ;
	
	CString		PathCopy, Fichier, Extension ;
	SepareChemin( PathCopy, Fichier, Extension ) ;
	
	int BackSlashIndex = PathCopy.Find('\\') ;
		
	while ( BackSlashIndex != -1 )
		{
		
		if ( BackSlashIndex > 1 )
			{
			char *	pChaine = new char[BackSlashIndex] ;
			lstrcpy( pChaine, (const char *)PathCopy.Left( BackSlashIndex -1 ) ) ;
			
			ListOfComponents.AddTail( pChaine ) ;
			}
		
		// Get the next component
		PathCopy = PathCopy.Right(PathCopy.GetLength()-BackSlashIndex) ;
		}
}

//+--------------------------------------------------------------------------
//+ Function   : FileExist
//+ Purpose    : Check file existance
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::FileExist( void ) const
{
	// Avoid the "insert disk..." message box
	CHPDiskAccessErrorMode		ErrMode( SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS ) ;
	
	// Try to open the file
	OFSTRUCT	Of ;
	const HFILE Err = OpenFile( *this, &Of, OF_EXIST ) ;
	// the file is not open, we used OF_EXIST, so don't close it !
	
	return ( Err != HFILE_ERROR ) ;
}

//+--------------------------------------------------------------------------
//+ Function   : DirectoryExist
//+ Purpose    : Check directory existance
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::DirectoryExist( void ) const
{
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	// Avoid the "insert disk..." message box
	CHPDiskAccessErrorMode		ErrMode( SEM_NOOPENFILEERRORBOX | SEM_FAILCRITICALERRORS ) ;
	BOOL	ReturnValue ;
	
	// Check the directory existance 
	char	OldDir[ _MAX_PATH ] ;
	_getcwd( OldDir, sizeof( OldDir)) ;
	
	// try to move to the directory
	if ( chdir( Chemin ) == -1 )
		// failed : the directory isn't accessible
		ReturnValue = FALSE ;
	else
		{
		// ok : the directory exists
		ReturnValue = TRUE ;
		chdir( OldDir ) ;
		}
	
	return ReturnValue ;
}

//+--------------------------------------------------------------------------
//+ Function   : Down
//+ Purpose    : Add a level of sub directory
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL	CLPIPathName::Down( const CString & SubDirectory )
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	Chemin += PATH_SEPARATOR + SubDirectory ;
	ColleMorceaux( Chemin, Fichier, Extension );
	
	ASSERT_VALID( this ) ;
	return TRUE ;
}

//+--------------------------------------------------------------------------
//+ Function   : Up
//+ Purpose    : Move one level up
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
BOOL CLPIPathName::Up( void )
{
	ASSERT_VALID( this ) ;
	CString		Chemin, Fichier, Extension ;
	SepareChemin( Chemin, Fichier, Extension ) ;
	
	const int	BackSlashIndex = Chemin.ReverseFind( '\\' ) ;
	
	if ( BackSlashIndex < 1 )
		// No parent directory
		return FALSE ;
		
	Chemin	= Chemin.Left(BackSlashIndex) ;
		
	ColleMorceaux( Chemin, Fichier, Extension );
	
	ASSERT_VALID( this ) ;return TRUE ;
}

//+--------------------------------------------------------------------------
//+ Function   : affectation operator ( = )
//+ Purpose    : affects the object
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
const CLPIPathName &	CLPIPathName::operator = ( const CLPIPathName & PathName )
{
	ASSERT_VALID( &PathName ) ;
	
	_PathFileName	=	PathName._PathFileName ;
	
	ASSERT_VALID( this ) ;
	
	return *this ;
}

const CLPIPathName &	CLPIPathName::operator = ( const CString & PathNameString )
{
	_PathFileName	= PathNameString ;
	ASSERT_VALID( this ) ;
		
	return *this ;
}

const CLPIPathName &	CLPIPathName::operator = ( LPCSTR PathName )
{
	_PathFileName	= PathName ;
	ASSERT_VALID( this ) ;
		
	return *this ;
}

//+--------------------------------------------------------------------------
//+ Function   : comparison operator ( == )
//+ Purpose    : affects the object
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
int CLPIPathName::operator == ( const CLPIPathName & PathName ) const
{
	if ( _PathFileName != PathName._PathFileName )
		return FALSE ;
		
	return TRUE ;
}

//+--------------------------------------------------------------------------
//+ Function   : comparison operator ( != )
//+ Purpose    : affects the object
//+ Parameters : Windows standard
//+--------------------------------------------------------------------------
int CLPIPathName::operator != ( const CLPIPathName & PathName ) const
{
	ASSERT_VALID( this ) ;
	
	if ( _PathFileName != PathName._PathFileName )
		return TRUE;
		
	return FALSE ;
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!    PRIVATE METHODS, YOU DON'T HAVE TO LOOK IF YOU ARE A USER    !!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



// ----------------------------------------------------------------------------
// SepareChemin
// Separe le chemin en : 	Chemin
//									Nom de fichier
//									Extension
// ENTREES :					rien
//	SORTIES :					Composants du chemin
// ----------------------------------------------------------------------------
void	CLPIPathName::SepareChemin( CString & Chemin, CString & Fichier, CString & Extension ) const
{
	char	Path[ _MAX_PATH ] ;
	char	Drive[ _MAX_DRIVE ] ;
	char	Dir[ _MAX_DIR ] ;
	char	Fich[ _MAX_FNAME ] ;
	char	Ext[ _MAX_EXT ] ;
	
	lstrcpy( Path, _PathFileName ) ;
	_splitpath( Path, Drive, Dir, Fich, Ext ) ;
	
	Chemin.Empty() ;
	if ( Drive[0])
		{
		Chemin += Drive ;
		}
	Chemin += Dir ;
	
	Fichier = Fich ;
	
	if ( Ext[0] == '.' )
		Extension = &Ext[1] ;
	else
		Extension = Ext ;
}
	   
// ----------------------------------------------------------------------------
// ColleMorceaux
// Recolle les bouts d'un chemin
// ----------------------------------------------------------------------------
void CLPIPathName::ColleMorceaux(	const CString & Chemin, 
								const CString & Fichier,
								const CString & Extension,
								BOOL  ForcePoint )
{
	_makepath( _PathFileName.GetBuffer( _MAX_PATH ), NULL, Chemin, Fichier, Extension ) ;
	
	_PathFileName.ReleaseBuffer() ;
	
	if ( ForcePoint && Extension.IsEmpty())
		_PathFileName += '.' ;
}

void CLPIPathName::Serialize( CArchive & Ar )
{
	CObject::Serialize( Ar ) ;
	
	if ( Ar.IsStoring())
		{
		Ar << _PathFileName ;
		}
	else
		{
		Ar >> _PathFileName ;
		}
}

#ifdef _DEBUG
void CLPIPathName::Dump( CDumpContext & DC) const
{
	DC << _PathFileName << "\n" ;
	if ( FileExist() )
		DC << "The file exists...\n" ;
	else
		DC << "The file doens't exst...\n" ;
		
	if ( DirectoryExist() )
		DC << "The directory exists...\n" ;
	else
		DC << "The directory doesn't exists..." ;
}

void CLPIPathName::AssertValid() const
{
	CObject::AssertValid() ;
	
	
}

#endif

