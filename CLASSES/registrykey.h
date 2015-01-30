////////////////////////////////////////////////////////////////////////////////
// CRegistryKey
// To ease registry manipulation
////////////////////////////////////////////////////////////////////////////////
#ifndef _REGISTRY_KEY_H_
#define _REGISTRY_KEY_H_

#include <winreg.h>

class	CRegistryKey
{
public :
		CRegistryKey( HKEY	hRoot, const char * SubKey, REGSAM	Desired	=	KEY_ALL_ACCESS ) ;
		~CRegistryKey() ;

		BOOL	GetValue( const char * ValueName, DWORD & ) ;
		BOOL	GetValue( const char * ValueName, CString & ) ;
		BOOL	GetValue( const char * ValueName, int & ) ;

		BOOL	SetValue( const char * ValueName, DWORD  ) ;
		BOOL	SetValue( const char * ValueName, const char * ) ;
		BOOL	SetValue( const char * ValueName, int ) ;

		BOOL	DeleteValue( const char * ValueName ) ;

		BOOL	Create() ;
		BOOL	Delete() ;

		CRegistryKey Create( const char * pSubKey ) ;
		BOOL	Delete( const char * pSubKey ) ;

		BOOL	Exist() ;

		operator HKEY ( void ) const { return _hKey ; } ;

private :
		HKEY	_hKey ;		
		HKEY	_hRoot ;
		CString	_Name ;
} ;

#endif
