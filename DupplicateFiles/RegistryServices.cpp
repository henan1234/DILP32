// RegistryServices.cpp: implementation of the CRegistryServices class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RegistryServices.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CString CRegistryServices::ReadRegistryKey( HKEY hRoot, const TCHAR * pPath, const TCHAR * pValueName, const TCHAR * pDefault )
	{
	HKEY hkey;
	LONG ret;
	char buf[1024] ;
	DWORD cbData=sizeof( buf ) ;
	DWORD dwType;

	ret=RegOpenKeyEx(hRoot,pPath,0,KEY_READ,&hkey);
	if(ret!=ERROR_SUCCESS)
		return pDefault ;

	ret=RegQueryValueEx(hkey,pValueName, NULL,&dwType,(LPBYTE)buf,&cbData);
	if(ret!=ERROR_SUCCESS)
		{
		RegCloseKey( hkey ) ;
		return pDefault ;
		}

	if ( dwType != REG_SZ )
		{
		RegCloseKey( hkey ) ;
		return pDefault;
		}

	RegCloseKey( hkey ) ;
	return buf ;
}


DWORD	CRegistryServices::ReadRegistryKey( HKEY hRoot, const TCHAR * pPath, const TCHAR * pValueName, DWORD Default )
	{
	HKEY hkey;
	LONG ret;
	DWORD buf  ;
	DWORD cbData=sizeof( buf ) ;
	DWORD dwType;

	ret=RegOpenKeyEx(hRoot,pPath,0,KEY_READ,&hkey);
	if(ret!=ERROR_SUCCESS)
		return Default ;

	ret=RegQueryValueEx(hkey,pValueName, NULL,&dwType,(LPBYTE)&buf,&cbData);
	if(ret!=ERROR_SUCCESS)
		{
		RegCloseKey( hkey ) ;
		return Default ;
		}

	if ( dwType != REG_DWORD )
		{
		RegCloseKey( hkey ) ;
		return Default;
		}

	RegCloseKey( hkey ) ;
	return buf ;
	}

void	CRegistryServices::SetRegistryValue( HKEY hRoot, const TCHAR * pPath, const TCHAR * pValueName, const TCHAR * pValue )
	{
	HKEY	hKey ;
	DWORD	Disp ;

	if ( RegCreateKeyEx(	hRoot, pPath, 0, 0,  REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,	0, &hKey, &Disp ) != ERROR_SUCCESS )
		return ;
 
	RegSetValueEx( hKey, pValueName, 0, REG_SZ, (PBYTE)pValue, _tcslen( pValue ) + 1 ) ;

	RegCloseKey( hKey ) ;
	}

void	CRegistryServices::SetRegistryValue( HKEY hRoot, const TCHAR * pPath, const TCHAR * pValueName, DWORD Value )
	{
	HKEY	hKey ;
	DWORD	Disp ;

	if ( RegCreateKeyEx(	hRoot, pPath, 0, 0,  REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,	0, &hKey, &Disp ) != ERROR_SUCCESS )
		return ;
 
	RegSetValueEx( hKey, pValueName, 0, REG_DWORD, (PBYTE)&Value, sizeof( DWORD ) ) ;

	RegCloseKey( hKey ) ;
	}


//////////////////////////////////////////////////////////////////////
// Returns TRUE if the given key exists in the registry
//////////////////////////////////////////////////////////////////////
BOOL CRegistryServices::KeyExist(HKEY hRoot, const TCHAR * lpSubKey )
{
	HKEY	hKey ;

	if ( RegOpenKeyEx(  hRoot,	lpSubKey, 0, KEY_READ, &hKey )== ERROR_SUCCESS )
		{
		RegCloseKey( hKey );
		return TRUE ;
		}
	else
		return FALSE ;
}
