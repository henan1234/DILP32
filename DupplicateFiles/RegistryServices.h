// RegistryServices.h: interface for the CRegistryServices class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRYSERVICES_H__87D5C942_C3CA_11D1_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_REGISTRYSERVICES_H__87D5C942_C3CA_11D1_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRegistryServices  
{
public:
	static BOOL KeyExist( HKEY, const TCHAR * );
	static	CString ReadRegistryKey( HKEY, const TCHAR * pPath, const TCHAR * pValueName, const TCHAR * pDefault ) ;
	static	DWORD	ReadRegistryKey( HKEY, const TCHAR * pPath, const TCHAR * pValueName, DWORD Default ) ;

	static	void	SetRegistryValue( HKEY, const TCHAR * pPath, const TCHAR * pValueName, const TCHAR * pValue ) ;
	static	void	SetRegistryValue( HKEY, const TCHAR * pPath, const TCHAR * pValueName, DWORD Value ) ;
	static	void	SetRegistryValue( HKEY hKey, const TCHAR * pPath, const TCHAR * pValue ) { SetRegistryValue( hKey, pPath, NULL, pValue ) ; } 
	static	void	SetRegistryValue( HKEY hKey, const TCHAR * pPath, DWORD Value ) { SetRegistryValue( hKey, pPath, NULL, Value ) ; } ;
};

#endif // !defined(AFX_REGISTRYSERVICES_H__87D5C942_C3CA_11D1_B79A_0000E8D9BF74__INCLUDED_)
