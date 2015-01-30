///////////////////////////////////////////////////////////////////////////////
// FileServices.cpp
//	Implementation file of the CFileServices class
//	This class must be considered as a module rather than a class because all
//	its methods are static
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <direct.h>
#include "FileServices.h"
//#include "MakeDOSFileName.h"


#ifndef VS_VERSION
typedef struct tagVS_VERSION
  {
    WORD wTotLen;
    WORD wValLen;
    char szSig[16];
    VS_FIXEDFILEINFO vffInfo;
  } VS_VERSION;
#endif

///////////////////////////////////////////////////////////////////////////////
// DeleteDirectory, public , static
//	Delete a directory and everything lying under it, use with care !
//	INPUT :	Root path
//	RETURNS:	TRUE if all has been deleted
///////////////////////////////////////////////////////////////////////////////
BOOL CFileServices::DeleteDirectory( const TCHAR * RootPath )
	{
	CString	Mask( CFileServices::Concat( RootPath , TEXT("*.*"))) ;

	WIN32_FIND_DATA	FindData ;
	HANDLE			hFind	=	FindFirstFile( Mask, &FindData ) ;
	BOOL			Continue=	hFind != INVALID_HANDLE_VALUE ;

	while ( Continue )
		{
		// Ignore . and ..
		if ( _tcscmp( FindData.cFileName, TEXT(".") ) && _tcscmp( FindData.cFileName, TEXT("..") ))
			{
			// Reconstruct the complete file path
			CString	CompletePath( RootPath ) ;
			if ( CompletePath.Right(1) != TEXT('\\') )
					CompletePath += TEXT('\\') ;
			CompletePath	+=	FindData.cFileName ;

			// Is the entry a file or a directory ?
			if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
				{
				// Delete the directory and its content, recursive call
				if ( ! DeleteDirectory( CompletePath ))
					{
					// Something wrong happened
					FindClose( hFind ) ;
					return FALSE ;
					}
				}
			else
				{
				// Delete the file
				if ( ! DeleteFile( CompletePath, TRUE ))
					{
					// Something wrong happened
					FindClose( hFind ) ;
					return FALSE ;
					}
				}
			}

		Continue	=	FindNextFile( hFind, &FindData ) ;
		}

	// All the content has been deleted, remove the directory
	RemoveDirectory( RootPath ) ;

	FindClose( hFind ) ;
	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// DeleteFile, public , static
//	Delete a file, eventually delete read-only file
//	INPUT :	File path
//	RETURNS:	TRUE if file has been deleted
///////////////////////////////////////////////////////////////////////////////
BOOL CFileServices::DeleteFile( const TCHAR * FilePath, BOOL DeleteEvenReadOnly )
	{
	if ( DeleteEvenReadOnly )
		{
		::SetFileAttributes( FilePath, ::GetFileAttributes( FilePath ) & ~FILE_ATTRIBUTE_READONLY ) ;
		}

	return ::DeleteFile( FilePath ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// ExtractLastDir, static, public
// Extract the last directory part of a complete directory path:
//	C;\XXX\YYY\ZZZ -> ZZZ
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::ExtractLastDir( const TCHAR * pPath )
	{
	TCHAR	Name[_MAX_FNAME] ;
	_tsplitpath( pPath, 0, 0, Name, 0 ) ;

	return Name ;
	}

///////////////////////////////////////////////////////////////////////////////
// IsDirectory, static, public
// Returns TRUE if the given path is a directory path
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::IsDirectory( const TCHAR * pPath )
	{
	CFileStatus	Status ;

	if ( ! CFile::GetStatus( pPath, Status ))
		return FALSE ;

	if ( ! (Status.m_attribute & CFile::directory ))
		return FALSE ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// IsDirectory, static, public
// Returns TRUE if the given path is a drive X:
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::IsDrive( const TCHAR * pPath )
	{
	CString Path( pPath ) ;
	if ( Path.GetLength() != 2 )
		return FALSE ;

	if ( Path[1] != ':' )
		return FALSE ;

	Path.MakeUpper() ;

	if ( Path[0] < 'A' )
		return FALSE ;

	if ( Path[0] > 'Z' )
		return FALSE ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// GetParentDirectory
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::GetParentDirectory( const TCHAR * pPath )
	{
	TCHAR	Drive[_MAX_DRIVE] ;
	TCHAR	Dir[_MAX_DIR] ;

	_tsplitpath( pPath, Drive, Dir, 0, 0 ) ;

	TCHAR Parent[_MAX_PATH] ;
	_tmakepath( Parent, Drive, Dir, 0, 0 ) ;

	return Parent ;
	}


///////////////////////////////////////////////////////////////////////////////
// ExtractFileName
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::ExtractFileName( const TCHAR * pPath )
	{
	TCHAR FName[_MAX_FNAME] ;
	TCHAR Ext[_MAX_EXT] ;

	_tsplitpath( pPath, 0,0,FName,Ext ) ;

	TCHAR Buffer[_MAX_PATH] ;
	_tmakepath( Buffer, 0,0, FName, Ext ) ;

	return Buffer ;
	}


///////////////////////////////////////////////////////////////////////////////
// CopyFile
//	Copy a file to a given location, returning TRUE if OK
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::CopyFile( const TCHAR * pSource, const TCHAR * pDest, BOOL bReplaceIfExist )
	{
	const UINT	Err	=	SetErrorMode( SEM_NOOPENFILEERRORBOX   ) ;


	// FXL -- 980505
	// check if target directory exists
	CString strTargetDir(GetParentDirectory(pDest));
	CreateDirectory(strTargetDir);

	const BOOL Res	=	::CopyFile( pSource, pDest, bReplaceIfExist ) ;

	SetErrorMode( Err ) ;

	return Res ;
	}

///////////////////////////////////////////////////////////////////////////////
// CreateDirectory
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::CreateDirectory( const TCHAR * pDirectory )
	{
	if ( ! ::CreateDirectory( pDirectory, NULL ))
		{
		// May be we'll have to create multiple levels of directory
		CString	Dir( pDirectory ) ;
		if ( Dir.Right(1) == "\\" )
			Dir =	Dir.Left( Dir.GetLength() - 1 ) ;

		const int BackSlashIndex	=	Dir.ReverseFind( '\\' ) ;

		// Directory path was not composite
		if ( BackSlashIndex <= 0 )
			return FALSE ;

		if ( ! CreateDirectory( Dir.Left( BackSlashIndex ) ))
			return FALSE ;
			
		return ::CreateDirectory( pDirectory, NULL ) ;
		}
		
	return TRUE ;
	}


///////////////////////////////////////////////////////////////////////////////
// Concat
//	Concatenates two filename parts, adding "\\" where needed
//	INPUT:	First and second path names
//	RETURN:	New path
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::Concat( const TCHAR * pPath1, const TCHAR * pPath2 )
	{
	CString	Path1( pPath1 ) ;
	CString Path2( pPath2 ) ;

	if ( ! Path1.IsEmpty())
		if ( Path1.Right(1) == TEXT("\\") )
			Path1	=	Path1.Left( Path1.GetLength() - 1 ) ;

	if ( ! Path2.IsEmpty())
		if ( Path2[0] == TEXT('\\') )
			Path2	=	Path2.Mid( 1 ) ;

	return Path1 + TEXT("\\") + Path2 ;
	}

///////////////////////////////////////////////////////////////////////////////
// FileExist
//	INPUT:	File name
//	Returns TRUE if the given file exist
///////////////////////////////////////////////////////////////////////////////
BOOL CFileServices::FileExist( const TCHAR * pPath )
	{
	CFileStatus Status ;

	return CFile::GetStatus( pPath, Status ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// FlushIniFile
// INPUT:	Ini File Name
// Makes sure the information of an INI file is stored on the disk
///////////////////////////////////////////////////////////////////////////////
void	CFileServices::FlushIniFile( const TCHAR * pIniFileName )
{
	WritePrivateProfileString( NULL, NULL, NULL, pIniFileName ) ;
}

///////////////////////////////////////////////////////////////////////////////
//	GetNonExistingFileName, public, static
//	Get a file name that doesn't exist in the given directory. The filename
//	will be preferably the one given as function input
//	INPUT :	Directory path
//			Starting path name
//	RETURNS:	filename
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::GetNonExistingFileName( const TCHAR * pDirectory, const TCHAR * pFileName )
{
	CString	FileName	=	ExtractFileName( pFileName ) ;
	CString	TriedName	=	FileName ;
	int		TryIndex	=	0 ;

	do
		{
			const CString FullPath	=	Concat( pDirectory, TriedName ) ;
			if ( ! FileExist( FullPath ))
				return TriedName ;

			// The file existed, let's try another
			TryIndex ++ ;
			TriedName	=	AddIndexToFileName( FileName, TryIndex ) ;
		}
	while ( TRUE ) ;
}

///////////////////////////////////////////////////////////////////////////////
//	GetNonExistingFileName, public, static
//	Get a file name that doesn't exist in the given directory. The filename
//	will be preferably the one given as function input
//	INPUT :	Starting path name
//	RETURNS:	filename
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::GetNonExistingFileName( const TCHAR * pFileName )
{
	CString	TriedName	=	pFileName ;
	int		TryIndex	=	0 ;

	do
		{
			if ( ! FileExist( TriedName ))
				return TriedName ;

			// The file existed, let's try another
			TryIndex ++ ;
			TriedName	=	AddIndexToFileName( pFileName, TryIndex ) ;
		}
	while ( TRUE ) ;
}


///////////////////////////////////////////////////////////////////////////////
//	AddIndex
//	Add an index to a file name :
//  XXXX\YYYY.ZZZ + n will become XXXX\YYYYn.ZZZ
//	YYYY could be truncated to follow the _MAX_FNAME limitation
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::AddIndexToFileName( const TCHAR * FileName, int Index )
{
	TCHAR Drive[_MAX_DRIVE] ;
	TCHAR Dir[_MAX_DIR] ;
	TCHAR FName[_MAX_FNAME] ;
	TCHAR Ext[_MAX_EXT] ;

	_tsplitpath( FileName, Drive, Dir, FName, Ext ) ;

	CString	SIndex ;
	SIndex.Format( TEXT( "%d" ), Index ) ;

	// Is 255 character enough to write an integer :-) ?
	ASSERT( SIndex.GetLength() < _MAX_FNAME ) ;

	if ( _tcslen( FName ) + SIndex.GetLength() >= _MAX_FNAME )
		{
		// Truncate the file name
		const int FNameLength	=	max( 0, _MAX_FNAME - SIndex.GetLength() - 1 ) ;
		ASSERT( FNameLength >= 0 ) ;
		ASSERT( FNameLength < _MAX_FNAME ) ;

		FName[FNameLength] = 0 ;
		}

	_tcscat( FName, SIndex ) ;

	TCHAR	Buffer[_MAX_PATH] ;
	_tmakepath( Buffer, Drive, Dir, FName, Ext ) ;

	return Buffer ;
}

///////////////////////////////////////////////////////////////////////////////
// CopyDirectory
//	Copy a directory all recursively all its content into another directory
// INPUT :	Source directory
//			Destination directory
///////////////////////////////////////////////////////////////////////////////
BOOL CFileServices::CopyDirectory( const TCHAR * pSource, const TCHAR * pDest )
	{
	CreateDirectory( pDest ) ;

	//	"All files" wildcard
	CString	Mask( CFileServices::Concat( pSource , TEXT("*.*"))) ;

	WIN32_FIND_DATA	FindData ;
	HANDLE			hFind	=	FindFirstFile( Mask, &FindData ) ;
	BOOL			Continue=	hFind != INVALID_HANDLE_VALUE ;

	while ( Continue )
		{
		// Ignore . and ..
		if ( _tcscmp( FindData.cFileName, TEXT(".") ) && _tcscmp( FindData.cFileName, TEXT("..") ))
			{
			// Reconstruct the complete file path
			const CString	CompleteSource	=	Concat(	pSource, FindData.cFileName ) ;
			const CString	CompleteDestination	=	Concat( pDest, FindData.cFileName ) ;

			// Is the entry a file or a directory ?
			if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
				{
				// copy the directory and its content, recursive call
				if ( ! CopyDirectory( CompleteSource, CompleteDestination ))
					{
					// Something wrong happened
					FindClose( hFind ) ;
					return FALSE ;
					}
				}
			else
				{
				// copy the file
				if ( ! CopyFile( CompleteSource, CompleteDestination ))
					{
					// Something wrong happened
					FindClose( hFind ) ;
					return FALSE ;
					}
				}
			}

		Continue	=	FindNextFile( hFind, &FindData ) ;
		}
	FindClose( hFind ) ;
	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// FilterDOSFileNameChars
//	Eliminates all DOS filename incorrect characters from a file name, lower
//	case characters are uppercased
// INPUT :	String
// RETURN:	String with only DOS valid characters
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::FilterDOSFileNameChars(const TCHAR * pFileName)
{
	const CString  VALID_DOS_FILE_CHARS(	TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-=()~$%&")) ;

	CString	FileName( pFileName ) ;
	if ( FileName.IsEmpty())
		return FileName ;
	FileName.MakeUpper() ;

	CString	Result ;

	int	CharIndex	=	0 ;
	
	while ( CharIndex < FileName.GetLength())
		{
		const int Index	=	VALID_DOS_FILE_CHARS.Find( FileName[CharIndex] ) ;

		if ( Index != -1 )
			{
			// Valid char
			Result	+=	FileName[CharIndex] ;
			}

		CharIndex ++ ;
		}

	return Result ;
}

///////////////////////////////////////////////////////////////////////////////
// Change a file extension
// INPUT :	File path
//			new extension
// RETURN :	File path with new extension
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::ChangeExtension( const TCHAR * pFilePath, const TCHAR * pNewExtension )
	{
	TCHAR Drive[_MAX_DRIVE] ;
	TCHAR Dir[_MAX_DIR] ;
	TCHAR FName[_MAX_FNAME] ;
	TCHAR Ext[_MAX_EXT] ;

	_tsplitpath( pFilePath, Drive, Dir, FName, Ext ) ;

	TCHAR	Buffer[_MAX_PATH] ;
	_tmakepath( Buffer, Drive, Dir, FName, pNewExtension ) ;

	return Buffer ;
	}

///////////////////////////////////////////////////////////////////////////////
// GetVersion
//	The a file version information, empty string if the file doesn't have any
//	version information
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::GetVersion( const TCHAR * szFullPath )
	{
	DWORD dwVerHnd;

   // You must find the file size first before getting any file info
	DWORD dwVerInfoSize = GetFileVersionInfoSize((TCHAR*)szFullPath, &dwVerHnd);
	if (! dwVerInfoSize)
		return "" ;

	LPSTR lpstrVffInfo;             // Pointer to block to hold info
	HANDLE hMem;                     // handle to mem alloc'ed

	// Get a block big enough to hold version info

	hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
	lpstrVffInfo = (LPTSTR)GlobalLock(hMem);

	CString Result ;

	// Get the info
	if (GetFileVersionInfo((TCHAR*)szFullPath, 0L, dwVerInfoSize, lpstrVffInfo))
		{
		VS_VERSION * pVerInfo	=	(VS_VERSION *)lpstrVffInfo ;
		Result.Format("%d.%d.%d.%d",	HIWORD(pVerInfo->vffInfo.dwFileVersionMS),
										LOWORD(pVerInfo->vffInfo.dwFileVersionMS),
										HIWORD(pVerInfo->vffInfo.dwFileVersionLS),
										LOWORD(pVerInfo->vffInfo.dwFileVersionLS));

		}


	// Let go of the memory
	GlobalUnlock(hMem);
	GlobalFree(hMem);

	return Result ;
	}

///////////////////////////////////////////////////////////////////////////////
// CompareVersion
//	Compares two files version information, if they include version
//	INPUT :	Two files names
//	OUTPUT: Result, same as strcmp :
//					<0 :	version 1 < version 2
//					0		version 1 == version 2
//					>0		version 1 > version 2
//	RETURN :	TRUE if both file 1 and file 2 have version information
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::CompareVersions( const TCHAR * pFile1, const TCHAR * pFile2, int * pResult ) 
	{
	ASSERT( AfxIsValidAddress( pResult, sizeof( *pResult )));

	const CString	Version1	=	GetVersion( pFile1 ) ;

	if ( Version1.IsEmpty())
		{
		*pResult	=	0 ;
		return FALSE ;
		}

	const CString	Version2	=	GetVersion( pFile2 ) ;

	if ( Version2.IsEmpty())
		{
		*pResult	=	0 ;
		return FALSE ;
		}


	*pResult	=	Version1.Compare( Version2 ) ;
	return TRUE ;
	}


///////////////////////////////////////////////////////////////////////////////
// GetTempDirectory
//	Get a directory where we are sure we can write
//	RETURN :	Temp directory name
///////////////////////////////////////////////////////////////////////////////
CString	CFileServices::GetTempDirectory()
	{
	TCHAR	Path[_MAX_PATH] ;
	::GetTempPath( sizeof( Path ), Path ) ;

	// If dir not exits
	CreateDirectory( Path ) ;

	if ( IsWritableDirectory( Path ))
		{
		return Path ;
		}

	// The bugged GetTempPath gave us a bad directory name, try another one
	GetWindowsDirectory( Path, sizeof( Path ) ) ;
	CString		TempUnderWin	=	Concat( Path, "TEMP" ) ;

	CreateDirectory( TempUnderWin ) ;

	if ( IsWritableDirectory( TempUnderWin ))
		{
		return TempUnderWin ;
		}

	// If nothing else works, take a hardcoded dir which should be on the hard drive,
	// better than nothing
	_tcscpy( Path, TEXT( "C:\\TEMP" )) ;
	CreateDirectory( Path ) ;

	return Path ;
	}

///////////////////////////////////////////////////////////////////////////////
// WritableDirectory
//	Returns TRUE if the program can write under this directory
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::IsWritableDirectory( const TCHAR * pDir )
	{
	CString	Dir	=	DeleteSlashAtEnd( pDir ) ;
	CreateDirectory( Dir ) ;

	if ( ! IsDirectory( Dir ))
		return FALSE ;

	CString	 FileName	=	GetNonExistingFileName( Dir, TEXT( "Only For Test.File") ) ;
	FileName	=	Concat( Dir, FileName ) ;

	HANDLE hFile = CreateFile(	FileName,
								GENERIC_WRITE,
								0,
								NULL,
								CREATE_NEW,
								0,
								NULL
							  ) ;

	if ( hFile == INVALID_HANDLE_VALUE )
		return FALSE ;

	CloseHandle( hFile ) ;
	DeleteFile( FileName ) ;

	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// DeleteSlashAtEnd
//	Suppress the final slash of a dir name, if exist
//	INPUT : Path name
//	RETURN:	Path without ending slash
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::DeleteSlashAtEnd( const TCHAR * pPath )
	{
	CString Result	=	pPath ;

	if ( Result.Right(1) == "\\" )
		Result	=	Result.Left( Result.GetLength() - 1 ) ;

	return Result ;
	}

///////////////////////////////////////////////////////////////////////////////
// ChangeFileName
//	Change a file name, keeping the path
//	INPUT:	Path
//			New file name
//	RETURN:	Path with changed path
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::ChangeFileName(const TCHAR * pPath, const TCHAR * pNewFileName)
{
	TCHAR Drive[_MAX_DRIVE] ;
	TCHAR Dir[_MAX_DIR] ;
	TCHAR FName[_MAX_FNAME] ;
	TCHAR Ext[_MAX_EXT] ;

	_tsplitpath( pPath, Drive, Dir, FName, Ext ) ;

	TCHAR	Buffer[_MAX_PATH] ;
	_tmakepath( Buffer, Drive, Dir, pNewFileName, NULL ) ;

	return Buffer ;

}

///////////////////////////////////////////////////////////////////////////////
//	TranslateToDOSName
//	Takes a file name and tries to translate it in the DOS 8.3 format
//	Ask  for the user confirmation if needed
//
//	INPUT :	Filename
//			TRUE if the modified 8.3 name is proposed to the user
//	OUTPUT:	Modified file name
//	RETURN:	IDOK if the output file name is OK
//			IDRETRY to reopen a file dialog
//			IDCANCEL operation abortion
///////////////////////////////////////////////////////////////////////////////
/*
int CFileServices::TranslateToDOSName(CString & FileName, BOOL Dialog )
{
	BOOL	Continue	=	TRUE ;

	do
		{
		CString	DOSFileName	= ToDOSFormat( FileName ) ;

		if ( FileName.CompareNoCase( DOSFileName ) == 0 )
			Continue	=	FALSE ;
		else
			if ( Dialog )
				{
				// Dos File name is different from the original file name,
				// ask the user for confirmation
				CMakeDOSFileName	Dlg ;
				Dlg.m_DOSName		=	DOSFileName ;
				Dlg.m_LongName		=	FileName ;

				switch( Dlg.DoModal())
					{
					case IDOK :
						Continue	=	FALSE ;
						DOSFileName	=	Dlg.m_DOSName ;
						break ;

					case IDCANCEL :
						return IDCANCEL ;

					case IDRETRY :
						return IDRETRY ;
					}
				}

		FileName	=	DOSFileName ;
		}
	while ( Continue ) ;

	return IDOK ;
}
*/
///////////////////////////////////////////////////////////////////////////////
// ToDOSFormat
//	Translate a long file name to DOS format
//	INPUT :	File name
//	RETURN:	File name, DOS formatted
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::ToDOSFormat(const TCHAR * pFileName)
{
	// Limit to valid chars
	CString Result	( pFileName ) ;

	// Limit to 8.3
	const int	DotIndex	=	Result.Find( '.' ) ;

	CString Name ;
	CString Extension ;

	if ( DotIndex != -1 )
		{
		Name	=	Result.Left( DotIndex ) ;
		Extension=	Result.Mid( DotIndex + 1 ) ;
		}
	else
		Name	=	Result ;

	Name	=	FilterDOSFileNameChars( Name ) ;
	Extension=	FilterDOSFileNameChars( Extension ) ;

	if ( Name.GetLength() > 8 )
		Name	=	Name.Left( 8 ) ;

	if ( Extension.GetLength() > 3 )
		Extension	=	Extension.Left( 3 ) ;

	Result	=	Name ;
	if ( ! Extension.IsEmpty())
		Result +=	'.' + Extension ;

	return Result ;
}


///////////////////////////////////////////////////////////////////////////////
// CopyFilesWithWildCards
// INPUT :	Source path with wildcards ( * or ? )
//			Destination path
//	RETURN:	TRUE if no problem
///////////////////////////////////////////////////////////////////////////////
BOOL	CFileServices::CopyFilesWithWildCards( const TCHAR * pSource, const TCHAR * pDestDir, BOOL ReplaceIfExist )
	{
	WIN32_FIND_DATA	FindData ;
	HANDLE			hFind	=	FindFirstFile( pSource, &FindData ) ;
	BOOL			Continue=	hFind != INVALID_HANDLE_VALUE ;

	const CString	ParentDirectory	=	GetParentDirectory( pSource ) ;

	while ( Continue )
		{
		// Ignore . and ..
		if ( _tcscmp( FindData.cFileName, TEXT(".") ) && _tcscmp( FindData.cFileName, TEXT("..") ))
			{
			// Is the entry a file or a directory ?
			if ( !(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  ))
				{
				// Reconstruct the complete file path
				const CString	SourcePath	=	Concat( ParentDirectory, FindData.cFileName ) ;
				const CString	DestPath	=	Concat( pDestDir, FindData.cFileName ) ;

				if ( ! CopyFile( SourcePath, DestPath, ReplaceIfExist ))
					{
					FindClose( hFind ) ;
					return FALSE ;
					}
				}
			}
		Continue	=	FindNextFile( hFind, &FindData ) ;
		}

	FindClose( hFind ) ;
	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// PathHasWildCards
//	Returns TRUE if the given path contains wildcards ( * or ? )
///////////////////////////////////////////////////////////////////////////////
BOOL CFileServices::PathHasWildCards(const TCHAR * pPath)
{
	const CString	Path(pPath ) ;

	return (Path.FindOneOf( TEXT( "*?" )) != -1) ;
}

///////////////////////////////////////////////////////////////////////////////
// GetNonExistingDirectoryName
//	Creates a non existing directory name under a given directory
//	INPUT:	Parent directory
//			Base directory name
//	RETURN:	Directory name that doesn't exist under the parent directory
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::GetNonExistingDirectoryName(const TCHAR * pDirectory, const TCHAR * pStartName)
{
	CString	FileName	=	ExtractFileName( pStartName ) ;
	CString	TriedName	=	FileName ;
	int		TryIndex	=	0 ;

	do
		{
		const CString FullPath	=	Concat( pDirectory, TriedName ) ;
		if ( ! DirectoryExist( FullPath ) && !FileExist( FullPath ))
			return TriedName ;

		// The directory existed, let's try another
		TryIndex ++ ;
		TriedName	=	AddIndexToFileName( FileName, TryIndex ) ;
		}
	while ( TRUE ) ;
}

///////////////////////////////////////////////////////////////////////////////
// AddLine
//	Add a line at the end of a text file
//	INPUT	:	File name
//				Line(s) to add
///////////////////////////////////////////////////////////////////////////////
void	CFileServices::AddLine( const TCHAR * pFileName, const TCHAR * pLine )
	{
	CStdioFile	File ;

	if ( ! File.Open( pFileName, 
		CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::typeText ))
		{
		return ;
		}

	File.SeekToEnd() ;
	File.WriteString( pLine ) ;

	File.Close() ;
	}

///////////////////////////////////////////////////////////////////////////////
// DosifyPathName
//	Convert a path name to DOS format
//	INPUT :	File name ( Windows format )
//			Boolean : use short path name if exist ?
//	RETURN :
//			Path name, DOS format ( 8.3 )
///////////////////////////////////////////////////////////////////////////////
CString CFileServices::DosifyPathName( const TCHAR * pFileName, BOOL bUseShortName )
	{
	if ( bUseShortName )
		{
		if ( FileExist( pFileName ))
			{
			TCHAR	ShortPathName[_MAX_PATH] ;

			if ( GetShortPathName( pFileName, ShortPathName, sizeof( ShortPathName )))
				{
				if ( FileExist( ShortPathName ))
					return ShortPathName ;
				}
			}
		}

	// Parse the comple file name into pieces and convert each piece into 8.3 format
	TCHAR Drive[_MAX_DRIVE] ;
	TCHAR Dir[_MAX_DIR] ;
	TCHAR FName[_MAX_FNAME] ;
	TCHAR Ext[_MAX_EXT] ;

	_tsplitpath( pFileName, Drive, Dir, FName, Ext ) ;

	// Convert path to 8.3
	CString	NewPath ;
	CString	Path(Dir) ;
	
	while ( ! Path.IsEmpty())
		{
		CString	Component	=	Path.SpanExcluding( "\\" ) ;
		NewPath	+=	ToDOSFormat( Component ) + '\\' ;

		Path	=	Path.Mid( Component.GetLength() + 1 ) ;
		}

	// Convert filename to 8.3
	CString	NewFileName	=	ToDOSFormat( CString( FName ) + Ext ) ;


	// Reconstruct the new path name
	TCHAR	ShortPath[_MAX_PATH] ;
	_makepath( ShortPath, Drive, NewPath, NewFileName, 0 ) ;

	return ShortPath ;
	}
