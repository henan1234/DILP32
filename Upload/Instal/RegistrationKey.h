// RegistrationKey.h: interface for the CRegistrationKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRegistrationKey  
{
public:
	CRegistrationKey( const char * SoftwarePathName, const char * HiddenKey );
	virtual ~CRegistrationKey();

	BOOL	TryToUnlock( DWORD	dwKey ) ;
	BOOL	IsLocked( void ) const ;

	CString	GetDisplayableLockKey( void ) ;
	BOOL	GenerateLock( void ) ;

private :
	CString	_SoftwareName ;
	CString _HiddenKey ;

	DWORD	GetRegistryValue( HKEY, const char * ) ;
	void	SetRegistryValue( HKEY, const char *, DWORD ) ;
};

#endif // !defined(AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_)
