///////////////////////////////////////////////////////////////////////////////
// FileServices.h
// Set of common file services functions
///////////////////////////////////////////////////////////////////////////////
#ifndef _FILESERVICES_H_
#define _FILESERVICES_H_
#pragma once

class CFileServices
{
	public:
		static CString GetNonExistingDirectoryName( const TCHAR * pDirectory, const TCHAR * pStartName );
		static BOOL PathHasWildCards( const TCHAR * );
		static CString ToDOSFormat( const TCHAR * pFileName );
		static int TranslateToDOSName( CString &, BOOL );
		static CString ChangeFileName( const TCHAR * pPath, const TCHAR * pNewFileName );
		static CString FilterDOSFileNameChars( const TCHAR * pFileName );
		static BOOL	CreateDirectory( const TCHAR * ) ;
		static BOOL CopyFile( const TCHAR * Source, const TCHAR * Destination, BOOL ReplaceIfExist = FALSE ) ;
		static BOOL CopyFilesWithWildCards( const TCHAR * Source, const TCHAR * pDestDirectory, BOOL ReplaceIfExist = FALSE ) ;

		static BOOL	DeleteFile( const TCHAR * File, BOOL DeleteEvenIfReadOnly = FALSE ) ;
		static BOOL	DeleteDirectory( const TCHAR * RootDirectory ) ;
		static BOOL	FileExist( const TCHAR * pPath ) ;
		static BOOL	DirectoryExist( const TCHAR * pPath ) { return IsDirectory( pPath ) ; } ;
		static BOOL CopyDirectory( const TCHAR * Source, const TCHAR * Dest ) ;

		static CString ExtractLastDir( const TCHAR * pPathName ) ;
		static BOOL	IsDirectory( const TCHAR * pPathName ) ;
		static BOOL	IsDrive( const TCHAR * pPathName ) ;

		static	CString	GetParentDirectory( const TCHAR * pPathName ) ;
		static	CString	ExtractFileName( const TCHAR * pPathName ) ;
		static	CString	Concat( const TCHAR * pPath1, const TCHAR * pPath2 ) ;

		// Make sure the INI file cache is flushed on the disk
		static	void	FlushIniFile( const TCHAR * pIniFileName ) ;

		// Get a unique file name non existing in a given directory
		static CString	GetNonExistingFileName( const TCHAR * pDirectory, const TCHAR * pFileName ) ;
		static CString	GetNonExistingFileName( const TCHAR * pFileName ) ;

		// Add an index to a file name
		static CString	AddIndexToFileName( const TCHAR * FileName, int Index ) ;

		// Change the extension from a file name
		static	CString	ChangeExtension( const TCHAR *, const TCHAR * ) ;

		// Compare file version, if the files do contain version information
		static BOOL	CompareVersions( const TCHAR * pFileName1, const TCHAR * pFileName2, int * pResult ) ;

		// Get The file version information
		static	CString	GetVersion( const TCHAR * pFileName ) ;

		// Get a temporary dir name where we are sure we can write ( GetTempDirectory bug )
		static	CString	GetTempDirectory() ;

		// Check if a directory is writable
		static BOOL		IsWritableDirectory( const TCHAR * pDir ) ;

		// Delete the last character of a path if it is a slash
		static CString DeleteSlashAtEnd( const TCHAR * pPath ) ;

		// Add a line at the end of a text file, create it if doesn't exist
		static void	AddLine( const TCHAR * pPath, const TCHAR * pLine ) ;

		// Convert a file path to DOS format ( using short name if it exists )
		static	CString	DosifyPathName( const TCHAR * pFileName, BOOL UseShortName = TRUE ) ;
} ;

#endif