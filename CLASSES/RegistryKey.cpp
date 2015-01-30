////////////////////////////////////////////////////////////////////////////////
// CRegistryKey
// To ease registry manipulation
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "RegistryKey.h"


CRegistryKey::CRegistryKey( HKEY	hRoot, const char * SubKey, REGSAM	Desired	 )
{
	_Name	=	SubKey ;

	if ( _Name[_Name.GetLength()-1] == '\\' )
		_Name	=	_Name.Left( _Name.GetLength() - 1) ;

	if ( RegOpenKeyEx( hRoot, _Name, 0, Desired, &_hKey ) != ERROR_SUCCESS )
		_hKey	=	0 ;

	_hRoot	=	hRoot ;
}


CRegistryKey::~CRegistryKey()
{
	if ( _hKey )
		RegCloseKey( _hKey ) ;
}

		
BOOL	CRegistryKey::GetValue( const char * ValueName, DWORD & Value )
{
	if ( ! _hKey )
		return FALSE ;

	DWORD			Val ;
	DWORD			Size	=	sizeof( Val ) ;
	DWORD			Type	=	REG_DWORD ;
	if ( RegQueryValueEx( _hKey, ValueName, NULL, &Type, (LPBYTE)&Val, &Size) != ERROR_SUCCESS )
		return FALSE ;

	if ( Type != REG_DWORD )
		return FALSE ;

	Value	=	Val ;

	return TRUE ;
}

BOOL	CRegistryKey::GetValue( const char * ValueName, CString & Value )
{
	if ( ! _hKey )
		return FALSE ;


	DWORD			Size ;
	DWORD			Type	=	REG_DWORD ;

	// Get the string length
	if ( RegQueryValueEx( _hKey, ValueName, NULL, &Type, NULL, &Size) != ERROR_SUCCESS )
		return FALSE ;

	if ( Type != REG_SZ )
		return FALSE ;

	char	*	pString	=	Value.GetBuffer( Size + 1 ) ;

	if ( RegQueryValueEx( _hKey, ValueName, NULL, &Type, (LPBYTE)pString, &Size) != ERROR_SUCCESS )
		return FALSE ;

	Value.ReleaseBuffer() ;
	return TRUE ;
}

BOOL	CRegistryKey::GetValue( const char * ValueName, int & Value )
{
	DWORD	Val ;

	if ( GetValue( ValueName, Val ))
		{
		Value=(int)Val ;
		return TRUE ;
		}
	else
		return FALSE ;
}


BOOL	CRegistryKey::SetValue( const char * ValueName, DWORD  Value )
{
	if ( ! Exist())
		if ( !Create())
			return FALSE ;

	ASSERT( _hKey ) ;

	if ( RegSetValueEx( _hKey, ValueName, 0, REG_DWORD, (LPBYTE)&Value, sizeof( Value )) != ERROR_SUCCESS )
		return FALSE ;

	return TRUE ;
}

BOOL	CRegistryKey::SetValue( const char * ValueName, const char * Value ) 
{
	if ( ! Exist())
		if ( !Create())
			return FALSE ;
	ASSERT( _hKey ) ;

	if ( RegSetValueEx( _hKey, ValueName, 0, REG_SZ, (LPBYTE)Value, lstrlen( Value ) + 1)
		!= ERROR_SUCCESS )
		return FALSE ;

	return TRUE ;
}


BOOL	CRegistryKey::SetValue( const char * ValueName, int Value )
{
	return SetValue( ValueName,(DWORD)Value ) ;
}

BOOL	CRegistryKey::DeleteValue( const char * ValueName )
{
	if ( ! Exist())
		return FALSE ;

	ASSERT( _hKey ) ;

	return ( ERROR_SUCCESS == RegDeleteValue( _hKey, ValueName )) ;
}


BOOL	CRegistryKey::Create()
{
	if ( Exist() )
		// Key already exist
		return TRUE ;

	if ( ERROR_SUCCESS != RegCreateKey( _hRoot, _Name, &_hKey ))
		{	
		_hKey	=	0 ;
		return FALSE ;
		}

	return TRUE ;
}

BOOL	CRegistryKey::Delete()
{
	if ( ! Exist())
		return TRUE ;

	if ( ERROR_SUCCESS != RegDeleteKey( _hRoot, _Name ))
		return FALSE ;

	_hKey	=	0 ;

	return TRUE ;
}

CRegistryKey CRegistryKey::Create( const char * pSubKey )
{
	if ( ! Exist())
		Create() ;

	CString	Name( _Name ) ;
	Name	+= '\\' ;
	Name	+=	pSubKey ;


	HKEY	hKey ;
	RegCreateKey( _hRoot, Name, &hKey ) ;
	RegCloseKey( hKey ) ;

	return	CRegistryKey( _hRoot, Name ) ;
}
		
BOOL	CRegistryKey::Delete( const char * pSubKey )
{
	if ( ! Exist())
		return TRUE ;

	return RegDeleteKey( _hKey, pSubKey ) == ERROR_SUCCESS ;
}

BOOL	CRegistryKey::Exist()
{
	return _hKey != 0 ;
}
