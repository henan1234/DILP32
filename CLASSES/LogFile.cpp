///////////////////////////////////////////////////////////////////////////////
// CLogFile
//	Log file management object
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <winnls.h>
#include "io.h"

#include "LogFile.h"

CLogFile::CLogFile( const char * PathName, LONG	MaxSize )
	{
	_Indentation	=	0 ;
	_NewLine		=	0 ;
	_WriteToFile	=	TRUE ;

	OpenFile( PathName, MaxSize ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// Constructor for conditionnal log file : if the specified registry key is
// found, nothing is written on the disk
///////////////////////////////////////////////////////////////////////////////
CLogFile::CLogFile( HKEY hRoot,
					const char * pRegistryKeyPath,
					const char * pRegistryKey,
					const char * pRegistryKeyValue,
					const char * PathName, LONG MaxSize )
	{
	if ( ! RegistryKeyFound( hRoot, pRegistryKeyPath, pRegistryKey, pRegistryKeyValue ))
		{
		_Indentation	=	0 ;
		_NewLine		=	0 ;
		_WriteToFile	=	TRUE ;
		
		OpenFile( PathName, MaxSize ) ;
		}
	else
		_WriteToFile	=	FALSE ;
	}



///////////////////////////////////////////////////////////////////////////////
// Open the log file for writing after creating a correct file name
///////////////////////////////////////////////////////////////////////////////
void	CLogFile::OpenFile( const char * PathName, LONG MaxSize )
{
	if ( TryToOpen( PathName, MaxSize ) )
		{
		_FileName	=	PathName ;
		}
	else
		{
		// Let's try to find a usable filename
		char Drive[_MAX_DRIVE] ;
		char Path[_MAX_DIR] ;
		char Name[_MAX_FNAME] ;
		char Ext[_MAX_EXT] ;

		_splitpath( PathName, Drive, Path, Name, Ext ) ;
		int	Indice = 1 ;

		char	TriedPathName[ _MAX_PATH ] ;
		do
			{
			CString	FileName ;
			FileName.Format( "%s (%d)", Name, Indice ) ;


			_makepath( TriedPathName, Drive, Path, FileName, Ext ) ;
			}
		while ( ! TryToOpen( TriedPathName, MaxSize )) ;

		_FileName	=	TriedPathName ;
		}

	CTime	Time	=	CTime::GetCurrentTime() ;
	SYSTEMTIME	SystemTime ;
	GetLocalTime( &SystemTime ) ;

	char	TxtTime[ 255 ] ;
	char	TxtDate[ 255 ] ;
	GetTimeFormat( LOCALE_USER_DEFAULT, 0, &SystemTime, NULL, TxtTime, sizeof( TxtTime )) ;
	GetDateFormat( LOCALE_USER_DEFAULT, 0, &SystemTime, NULL, TxtDate, sizeof( TxtDate )) ;

	CString	Message ;
	Message.Format( "Log file %s, opened on %s %s", (LPCSTR)PathName, (LPCSTR)TxtDate, (LPCSTR)TxtTime ) ;

	Write( "************************************************************************" ) ;
	Write( "************************************************************************" ) ;
	Write( Message ) ;
	Write( "************************************************************************" ) ;
	Write( "************************************************************************" ) ;
	Write( "" ) ;
}

CLogFile::~CLogFile()
	{
	if ( _WriteToFile )
		{
		CTime	Time	=	CTime::GetCurrentTime() ;
		SYSTEMTIME	SystemTime ;
		GetLocalTime( &SystemTime ) ;

		char	TxtTime[ 255 ] ;
		char	TxtDate[ 255 ] ;
		GetTimeFormat( LOCALE_USER_DEFAULT, 0, &SystemTime, NULL, TxtTime, sizeof( TxtTime )) ;
		GetDateFormat( LOCALE_USER_DEFAULT, 0, &SystemTime, NULL, TxtDate, sizeof( TxtDate )) ;

		CString	Message ;
		Message.Format( "Log file closed on %s %s", (LPCSTR)TxtDate, (LPCSTR)TxtTime ) ;

		Write( "----------------------------------------------------------------------" ) ;
		Write( Message ) ;
		Write( "----------------------------------------------------------------------\n\n" ) ;
		}
	}


void	CLogFile::Write( const char * pString )
	{
	if ( _WriteToFile )
		{
		TRY
			{
			if ( _File.m_hFile != CFile::hFileNull )
				{
				///////////////////////////////////////////////////////////////////
				// Write indentation
				///////////////////////////////////////////////////////////////////
				for ( int i = 0; i < _Indentation; i++)
					_File.Write( "\t", 1 ) ;

				///////////////////////////////////////////////////////////////////
				// Write the string
				///////////////////////////////////////////////////////////////////
				_File.WriteString( pString ) ;
				_File.WriteString( "\n" ) ;
				_File.Flush() ;
				}
			}
		CATCH ( CFileException, e )
			{
			// Do nothing to not interrupt the program
			}
		END_CATCH ;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Write two string on the same line
// For backward compatibility, use operator <<
///////////////////////////////////////////////////////////////////////////////
void	CLogFile::Write( const char * pString1, const char * pString2 )
	{
	(*this) << pString1 << pString2 << newline ;
	}

///////////////////////////////////////////////////////////////////////////////
// Write one string and one integer on the same line
// For backward compatibility, use operator <<
///////////////////////////////////////////////////////////////////////////////
void	CLogFile::Write( const char * pString, int Int )
	{
	(*this) << pString << Int << newline ;
	}

///////////////////////////////////////////////////////////////////////////////
// Helper object to indent a logfile within a function
///////////////////////////////////////////////////////////////////////////////
CLogIndent::CLogIndent( CLogFile & LogFile )
	{
	_pLogFile	=	&LogFile ;
	_pLogFile->FunctionEnter() ;
	}

CLogIndent::~CLogIndent()
	{
	ASSERT( _pLogFile ) ;
	_pLogFile->FunctionExit() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Try to open a file. If the file already exists, concatenate only if its size
// is less than MaxSize, else reset it
///////////////////////////////////////////////////////////////////////////////
BOOL CLogFile::TryToOpen( const char * FileName, LONG MaxSize )
{
	CString	FullPath	=	GetFullPath( FileName ) ;

	CFileException	Exception ;

	if ( access( FullPath, 0 ) == 0)
		{
		CFileStatus	Status ;
		CFile::GetStatus( FullPath, Status ) ;

		///////////////////////////////////////////////////////////////////////
		// The file exists, what's its size ?
		///////////////////////////////////////////////////////////////////////
		if ( Status.m_size < MaxSize )
			{
			if (  _File.Open( FullPath, CFile::modeReadWrite | CFile::typeText | CFile::shareExclusive, &Exception ))
				{
				_File.SeekToEnd() ;
				return TRUE ;
				}
			else
				return FALSE ;
			}
		else
			// The file is
			return _File.Open(	FullPath,
								CFile::modeCreate | CFile::modeWrite | CFile::typeText  | CFile::shareExclusive, &Exception ) ;
		}
	else
		///////////////////////////////////////////////////////////////////////
		// The log file doesn't exist, create it
		///////////////////////////////////////////////////////////////////////
		return _File.Open(	FullPath,
							CFile::modeCreate | CFile::modeWrite | CFile::typeText  | CFile::shareExclusive,
							&Exception ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Log a function entering.
// Increments the indentation counter
// Write a function beginning string
///////////////////////////////////////////////////////////////////////////////
void CLogFile::FunctionEnter( void )
	{
	_Indentation ++ ;
	Write( "{" ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Log a function exit
// Increments the indentation counter
// Write a function beginning string
///////////////////////////////////////////////////////////////////////////////
void CLogFile::FunctionExit( void )
	{
	ASSERT( _Indentation > 0 ) ;
	Write ( "}" ) ;
	_Indentation --  ;
	} 


///////////////////////////////////////////////////////////////////////////////
// Overloaded << operator
///////////////////////////////////////////////////////////////////////////////
CLogFile & CLogFile::operator << ( const char * pValue )
	{
	if ( _WriteToFile )
		{
		if ( _File.m_hFile != CFile::hFileNull )
			{
			if ( pValue)
				{
				///////////////////////////////////////////////////////////////////
				// Write the indentation at the beginning of the line
				///////////////////////////////////////////////////////////////////
				if ( _NewLine )
					for ( int i = 0; i < _Indentation; i++)
						_File.Write( "\t", 1 ) ;
			
				///////////////////////////////////////////////////////////////////
				// Write the string
				///////////////////////////////////////////////////////////////////
				_File.WriteString( pValue ) ;
				_NewLine	=	FALSE ;
				}
			}
		}		

	return *this ;
	}


///////////////////////////////////////////////////////////////////////////////
// Write an integer value
///////////////////////////////////////////////////////////////////////////////
CLogFile & CLogFile::operator << ( int Value )
	{
	if ( _WriteToFile )
		{
		CString Line ;
		Line.Format( "%d", Value ) ;
		(*this) << Line ;
		}

	return *this ;
	}

///////////////////////////////////////////////////////////////////////////////
//	Write an end of line and flush, the used keyword doesn't matter, it is just used
//	to call this function
///////////////////////////////////////////////////////////////////////////////
CLogFile & CLogFile::operator << ( T_NEWLINE )
	{
	if ( _WriteToFile )
		{
		if ( _File.m_hFile != CFile::hFileNull )
			{
			(*this) << "\n" ;
			_File.Flush() ;
			}
		
		_NewLine	=	TRUE ;		// Next write will add an indentation
		}

	return * this ;
	}

// Get the full path name if non is given in the path
// because this f..... windows set the current path to the desktop when you
// drop a file on an exe
CString CLogFile::GetFullPath(const char * FilePath)
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


///////////////////////////////////////////////////////////////////////////////
// RegistryKeyFound
// Returns TRUE if the specified registry key is found
// Used for the conditionnal log files
///////////////////////////////////////////////////////////////////////////////
BOOL CLogFile::RegistryKeyFound( HKEY hKey, const char * pPath, const char * pValueName,
								 const char * pValue )
{
	HKEY	hSubKey ;

	// open the key
	if ( ERROR_SUCCESS != RegOpenKey( hKey, pPath, &hSubKey ))
		return FALSE ;

	// read the value
	char Buffer[1024] ;
	DWORD	Type	=	REG_SZ ;
	DWORD	Taille	=	sizeof( Buffer ) ;

	if ( ERROR_SUCCESS != RegQueryValueEx( hSubKey, pValueName,0, &Type, (LPBYTE)Buffer, &Taille ))
		{
		RegCloseKey( hSubKey ) ;
		return FALSE ;
		}

	RegCloseKey( hSubKey ) ;

	// compare the value
	if ( strcmp( pValue, Buffer ))
		return FALSE ;

	return TRUE ;
}