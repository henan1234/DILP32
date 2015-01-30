//
// Common utilities for HP CenterWarnIcon and HPFlashIcon
//
//	This file is used by HPFlashIcon and should avoid using M.F.C to preserve
//	memory space.
//

#include "stdafx.h"
#include "tchar.h"
#include <stdlib.h>
#include "common.h"

#pragma data_seg("SHARED_DATA")
LONG	NbInstances	=	0 ;
#pragma data_seg()

TCHAR	ConfigurationFile[_MAX_PATH]	=	"" ;

////////////////////////////////////////////////////////////////////////////
// ToTheExeDirectory
// takes a filename and adds the EXE directory path
// WARNING : The FilePath buffer must be big enough to receive the new
// path ( use _MAX_PATH system constant )
////////////////////////////////////////////////////////////////////////////
void	ToTheExeDirectory( TCHAR * FilePath )
{
	TCHAR	InitialFileName[_MAX_FNAME] ;
	TCHAR	InitialExtension[_MAX_EXT] ;

	_tsplitpath( FilePath, NULL, NULL, InitialFileName, InitialExtension ) ;

	// Get the EXE path name
	TCHAR Dir[_MAX_DIR] ;
	GetModuleFileName( NULL, Dir, sizeof( Dir )) ;

	TCHAR		Drive[_MAX_DRIVE] ;
	TCHAR		Directory[_MAX_DIR] ;
	_tsplitpath( Dir, Drive, Directory, 0, 0 ) ;
	_tmakepath( FilePath, Drive, Directory, InitialFileName, InitialExtension ) ;
}

static void	SetConfigurationFileName()
{
	_tcscpy( ConfigurationFile, INI_FILE_NAME ) ;
	
	ToTheExeDirectory( ConfigurationFile ) ;
}


////////////////////////////////////////////////////////////////////////////
// Get a string from the configuration file
/////////////////////////////////////////////////////////////////////////////
void	GetConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName,
								TCHAR * Value, int Size )
{
	if ( ! ConfigurationFile[0] )
		{
		// Get the configuration name, under the same directory as the EXE file
		SetConfigurationFileName() ;
		}

	::GetPrivateProfileString( pSectionName, pValueName, Value, Value, Size, ConfigurationFile ) ;
}

CString GetConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName, const TCHAR * pDefault )
	{
	TCHAR	Buffer[1024] ;
	_tcscpy( Buffer, pDefault ) ;

	GetConfigurationString( pSectionName, pValueName, Buffer, sizeof( Buffer )) ;
	return Buffer ;
	}

int GetConfigurationInt( const TCHAR * pSectionName, const TCHAR * pValueName, int Default )
{
	TCHAR Buffer[20] ;
	_itot( Default, Buffer, 10 ) ;

	GetConfigurationString( pSectionName, pValueName, Buffer, sizeof( Buffer )) ;

	return _ttoi( Buffer ) ;
}

void WriteConfigurationString( const TCHAR * pSectionName, const TCHAR * pValueName, const TCHAR * pValue )
{
	if ( ! ConfigurationFile[0] )
		{
		// Get the configuration name, under the same directory as the EXE file
		SetConfigurationFileName() ;
		}

	::WritePrivateProfileString( pSectionName, pValueName, pValue, ConfigurationFile ) ;
}

void WriteConfigurationInt( const TCHAR * pSectionName, const TCHAR * pValueName, int Value )
{
	TCHAR Buffer[20] ;	// Should be sufficient to store an int
	_itot( Value, Buffer, 10 ) ;

	WriteConfigurationString( pSectionName, pValueName, Buffer ) ;
}



/////////////////////////////////////////////////////////////////////////////
// Get the timer delai from the configuration file
// /////////////////////////////////////////////////////////////////////////////
UINT GetTimerDelay( T_TIMER_DELAY Delay )
{
	switch ( Delay )
		{
		case DELAY_CHECK :
			return ::GetConfigurationInt( CFG_PARAMETERS, CFG_DELAY_CHECK, 2 * 60 * 1000 ) ;

		case DELAY_BEFORE_HIDE :
			return ::GetConfigurationInt( CFG_PARAMETERS, CFG_DELAY_BEFORE_HIDE, 30 * 1000 ) ;

		case DELAY_FLASH :
			return ::GetConfigurationInt( CFG_PARAMETERS, CFG_DELAY_FLASH, 500) ;
		case DELAY_ANIMATION :
			return ::GetConfigurationInt( CFG_PARAMETERS, CFG_DELAY_ANIMATION, 100 ) ;
		}

	return 0 ;
}

/////////////////////////////////////////////////////////////////////////////
// Set the timer delai from the configuration file
// /////////////////////////////////////////////////////////////////////////////
void SetTimerDelay( T_TIMER_DELAY Type, UINT Delay )
{
	switch ( Type )
		{
		case DELAY_CHECK :
			::WriteConfigurationInt( CFG_PARAMETERS, CFG_DELAY_CHECK, Delay ) ;
			break ;

		case DELAY_BEFORE_HIDE :
			::WriteConfigurationInt( CFG_PARAMETERS, CFG_DELAY_BEFORE_HIDE, Delay ) ;
			break ;

		case DELAY_FLASH :
			::WriteConfigurationInt( CFG_PARAMETERS, CFG_DELAY_FLASH, Delay ) ;
			break ;

		case DELAY_ANIMATION :
			::WriteConfigurationInt( CFG_PARAMETERS, CFG_DELAY_ANIMATION, Delay ) ;
			break ;
		}

}


/////////////////////////////////////////////////////////////////////////////
// MultipleInstances
// Returns TRUE if there are multiple instances of this program
// CAUTION: You should add : in the linkers options
/////////////////////////////////////////////////////////////////////////////
BOOL MultipleInstances( void )
{
	InterlockedIncrement( &NbInstances ) ;

	if ( NbInstances > 1 )
		return TRUE ;

	return FALSE ;
}


/////////////////////////////////////////////////////////////////////////////
// ExitInstance
// Decrements the instance cptr to signal the instance exit
/////////////////////////////////////////////////////////////////////////////
void ExitInstance( void )
{
	InterlockedDecrement( &NbInstances ) ;
}

