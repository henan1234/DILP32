// RegistrationKey.h: interface for the CRegistrationKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Transparent desktop
#define WAD_NAME	"Transparent Desktop"
#define WAD_PATH	"Software\\Lucien PILLONI\\TransparentDestop"
#define WAD_HIDDEN "FileVersion01"

// Economiseur d'ecran Gravitation
#define GRAV_NAME	"Gravitation"
#define GRAV_PATH	"Software\\Lucien PILLONI\\Gravitation"
#define GRAV_HIDDEN	"FileVersion02"
	

// Economiseur d'ecran Liaison forte
#define LIF_NAME	"Molecules"
#define LIF_PATH	"Software\\Lucien PILLONI\\Molecules"
#define LIF_HIDDEN	"FileVersion03"


// Economiseur d'ecran Loupes
#define LOP_NAME	"Loupes"
#define LOP_PATH	"Software\\Lucien PILLONI\\Loupes"
#define LOP_HIDDEN	"FileVersion04"

// Economiseur d'ecran Graffiti
#define GRAF_NAME	"Graffiti"
#define GRAF_PATH	"Software\\Lucien PILLONI\\Graffiti"
#define GRAF_HIDDEN	"Sys version 01"

// Economiseur d'ecran Tas de sable
#define TDS_NAME	"SandBox"
#define TDS_PATH	"Software\\Lucien PILLONI\\SandBox"
#define TDS_HIDDEN "Sys version 02"


class CRegistrationKey  
{
public:
	static CRegistrationKey* GetKey( void );
	DWORD GetUnlockKey( const char * );
	CRegistrationKey( const char * SoftwarePathName, const char * HiddenKey );
	virtual ~CRegistrationKey();

	BOOL	TryToUnlock( DWORD	dwKey ) ;
	BOOL	IsLocked( void ) ;

	CString	GetDisplayableLockKey( void ) ;
	BOOL	GenerateLock( void ) ;

private :
	static CRegistrationKey * _pZeOnlyOuane;
	CString	_SoftwareName ;
	CString _HiddenKey ;

	DWORD	GetRegistryValue( HKEY, const char *, const char * ) ;
	void	SetRegistryValue( HKEY, const char *, const char *, DWORD ) ;

	
	DWORD	ClefCachee() ;
	DWORD	CodePourRegistry( DWORD ) ;
	DWORD	DecodePourRegistry( DWORD ) ;

	DWORD	CodePourEcran( DWORD ) ;
	DWORD	DecodePourEcran( DWORD ) ;

	DWORD	CheckSum( const char * ) ;

	friend class	CDebloqueDlg ;
};

#endif // !defined(AFX_REGISTRATIONKEY_H__F7393981_2DDD_11D1_AEF5_444553540000__INCLUDED_)
