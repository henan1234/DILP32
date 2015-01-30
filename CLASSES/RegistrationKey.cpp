// RegistrationKey.cpp: implementation of the CRegistrationKey class.
//
//	Principe : a l'installation du logiciel, on genere une clef
//			   aleatoire. Cette est stockee codee et cachee dans la
//			   registry.
//	Pour debloquer :
//				On donne une version codee ( deuxieme methode ) de la
//				clef a l'utilisateur.
//				L'utilisateur doit donner la clef initiale pour
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Transparentdesktop.h"
#include "RegistrationKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define HIDDEN_PATH	"System\\CurrentControlSet\\Control\\FileSystem"

#define FILTRE_REGISTRY	0x12354678
#define FILTRE_ECRAN	0x87654391

CRegistrationKey*	CRegistrationKey::_pZeOnlyOuane	=	0 ;

typedef	struct
	{
	DWORD	Clef ;
	char	Bidon ;
	DWORD	Date ;
	DWORD	CheckSum ;
	}
	CLEF_ET_DATE ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistrationKey::CRegistrationKey( const char * SoftwarePathName, const char * HiddenKey )
{
	ASSERT( _pZeOnlyOuane == 0 ) ;
	_pZeOnlyOuane	=	this ;

	_SoftwareName	=	SoftwarePathName ;
	_HiddenKey		=	HiddenKey ;
}

CRegistrationKey::~CRegistrationKey()
{
	ASSERT( _pZeOnlyOuane == this ) ;
	_pZeOnlyOuane = 0 ;
}


///////////////////////////////////////////////////////////////////////////////
// TryToUnlock
//	Tentative de debloquer le logiciel en entrant la clef.
//	La clef est donnee par l'utilisateur, on la compare a celle stockee dans
//	la registry
///////////////////////////////////////////////////////////////////////////////
BOOL	CRegistrationKey::TryToUnlock( DWORD dwKey )
{
	DWORD	Clef	=	ClefCachee() ;

	if ( Clef ==	dwKey )
		{
		///////////////////////////////////////////////////////////////////////
		// C'est debloque
		// On stocke l'information dans la registry, non codee, comme ca
		// l'utilisateur pour aller y regarder a loisir
		///////////////////////////////////////////////////////////////////////
		//		SetRegistryValue( HKEY_LOCAL_MACHINE, _SoftwareName, "Registered", dwKey ) ;
		// Deuxieme methode de stockage : on stocke la clef avec la date de deblocage, pour
		// permettre le controle de la duree de license
		// Stockage dans une clef binaire

		// Date d'aujourdhui
		CTime	Aujourdhui( CTime::GetCurrentTime() ) ;
		DWORD	Annee	=	Aujourdhui.GetYear() ;
		DWORD	Mois	=	Aujourdhui.GetMonth() ;
		DWORD	Jour	=	Aujourdhui.GetDay() ;

		CLEF_ET_DATE	Buffer ;

		Buffer.Clef	=	dwKey ;
		Buffer.Date	=	(Annee * 1000) + (Mois * 50) + Jour ;
		Buffer.CheckSum	=	CheckSum( (const char *)&Buffer, (const char*)&Buffer.CheckSum - (const char *)&Buffer ) ;

		SetRegistryValue( HKEY_LOCAL_MACHINE, _SoftwareName, "Registered", (LPBYTE)&Buffer, sizeof( Buffer )) ;
		return TRUE ;
		}
	else
		return FALSE ;
}

///////////////////////////////////////////////////////////////////////////////
// IsLocked
// Le logiciel est il bloque ?
// On se contente de comparer la clef cachee a la clef de debloquage
// eventuellement rentree prealablement par l'utilisateur
//	29/11/97: La clef saisie a ete stockee avec la date de saisie pour verifier
//			  que l'utilisateur enregistre a droit a cette version du logiciel
//			  Si la clef n'est pas stockee en binaire, il s'agit d'une ancienne
//			  license anterieure au 01/01/98
// Rappel, la clef de deblocage n'est pas stockee codee dans la registry
///////////////////////////////////////////////////////////////////////////////
BOOL CRegistrationKey::IsLocked( void ) 
{
return FALSE ;
/*
	DWORD	Cachee	=	ClefCachee() ;

	HKEY	hKey	;
	if ( RegOpenKey( HKEY_LOCAL_MACHINE, _SoftwareName, &hKey ) != ERROR_SUCCESS )
		// Pas de clef stockee
		return TRUE ;

	DWORD		Clef ;
	DWORD		Date ;

	CLEF_ET_DATE	ClefEtDate ;
	DWORD			Taille		=	sizeof( ClefEtDate ) ;
	DWORD			Type		=	REG_BINARY ;
	
	LONG Result =  RegQueryValueEx( hKey, "Registered", 0, &Type, (LPBYTE)&ClefEtDate, &Taille ) ;

	if ( Result != ERROR_SUCCESS ||
		 Type	!= REG_BINARY ||
		 Taille != sizeof( ClefEtDate ) ||
		 ClefEtDate.CheckSum != CheckSum( (const char *)&ClefEtDate,(const char*)&ClefEtDate.CheckSum - (const char *)&ClefEtDate ))
		{
		Type		=	REG_DWORD ;
		Taille		=	sizeof( Clef ) ;
		// Pas de clef binaire stockee, peut etre une ancienne license ?
		if ( ERROR_SUCCESS != RegQueryValueEx( hKey, "Registered", 0, &Type, (LPBYTE)&Clef, &Taille ))
			{
			RegCloseKey( hKey ) ;
			return TRUE ;
			}

		// Les anciennes licenses sont consideree comme etant acquises au 01/01/98
		CTime	License( 1998, 1, 1, 0, 0, 0 ) ;
		Date	=	1000 * License.GetYear() + 50 * License.GetMonth() + License.GetDay() ;
		}
	else
		{
		Clef	=	ClefEtDate.Clef ;
		Date	=	ClefEtDate.Date ;
		}

	RegCloseKey( hKey ) ;

	// Si clef != clef cache -> pas deverouillee
	if ( Clef != Cachee )
		return TRUE ;

	// Si clef saisie + 1 an < date logiciel : l'utilisateur est enregistre mais il n'a pas droit a
	// cette version

	CTime		DateLogiciel( ANNEE_VERSION, MOIS_VERSION, JOUR_VERSION, 0, 0, 0 ) ;

	int			Annee	=	Date / 1000 ;
	Date		-=		Annee	* 1000 ;
	int			Mois	=	Date / 50 ;
	int			Jour	=	Date % 50 ;

	CTime		DateSaisie( Annee+1, Mois, Jour, 0, 0, 0 ) ;

	if ( DateSaisie < DateLogiciel )
		return TRUE ;
	
	// La clef "enregistree" n'est pas codee
	//DWORD	Unlocked=	GetRegistryValue( HKEY_LOCAL_MACHINE, _SoftwareName, "Registered" ) ;
	return FALSE ;
	*/
}



///////////////////////////////////////////////////////////////////////////////
// GenerateLock
// Generation d'une clef aleatoire pour bloquer un logiciel. Cette clef est
// calculee a partir du nom de la machine, du nom d'utilisateur, de l'heure...
// Elle est ensuite stockee de facon codee dans la registry
///////////////////////////////////////////////////////////////////////////////
BOOL CRegistrationKey::GenerateLock( void )
	{
	DWORD	ClefEnregistrement = 0 ;
	char	Buffer[1024] ;
	DWORD	Taille	=	sizeof( Buffer ) ;

	// Coder sur le nom de la machine
	if ( GetComputerName( Buffer, &Taille ))
		ClefEnregistrement +=	CheckSum( Buffer ) ;

	// Coder sur le nom de l'utilisateur
	Taille	=	sizeof( Buffer ) ;
	if ( GetUserName( Buffer, &Taille ))
		ClefEnregistrement +=	CheckSum( Buffer ) ;

	// Coder sur la date courante
	CTime	Time	=	CTime::GetCurrentTime() ;
	ClefEnregistrement +=	CheckSum( Time.Format("%c %H%M%S")) ;

	ClefEnregistrement += GetTickCount() ;

	SetRegistryValue( HKEY_LOCAL_MACHINE, HIDDEN_PATH, _HiddenKey, CodePourRegistry( ClefEnregistrement )) ;

	return TRUE ;
	}

DWORD CRegistrationKey::GetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName )
	{
	HKEY hKey ;
	if ( ERROR_SUCCESS != RegOpenKey( hRoot, Path, &hKey ))
		return 0 ;

	DWORD	Dword	;

	DWORD	Taille	=	sizeof( Dword) ;
	DWORD	Type	=	REG_DWORD ;

	if ( ERROR_SUCCESS != RegQueryValueEx( hKey, ValueName, 0, &Type, (BYTE *)&Dword, &Taille ))
		return 0 ;

	RegCloseKey( hKey ) ;

	return Dword ;
	}

void CRegistrationKey::SetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName, DWORD dwKey )
	{
	HKEY	hKey ;
	DWORD Disp ;

	if ( ERROR_SUCCESS == RegCreateKeyEx( hRoot,  Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &Disp ))
		{
		RegSetValueEx( hKey, ValueName, 0, REG_DWORD, (CONST BYTE *)&dwKey, sizeof( dwKey )) ;
		RegCloseKey( hKey ) ;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Recuperation de la clef cachee dans la registry. Comme elle est stockee
// de facon codee, il faut evidemment la decoder
// S'il n'y a pas de clef dans la registry, c'est la premiere execution du
// programme, on genere la clef cachee
///////////////////////////////////////////////////////////////////////////////
DWORD	CRegistrationKey::ClefCachee()
	{
	HKEY	hKey ;
	if ( ERROR_SUCCESS != RegOpenKey( HKEY_LOCAL_MACHINE, HIDDEN_PATH, &hKey ))
		GenerateLock() ;
	else
		{
		DWORD Type	=	REG_DWORD ;
		BYTE	Buffer[10] ;
		DWORD Taille	=	sizeof( Buffer ) ;

		if ( ERROR_SUCCESS != RegQueryValueEx( hKey, _HiddenKey, 0, &Type, Buffer, &Taille ))
			GenerateLock() ;

		RegCloseKey(hKey) ;
		}
	return DecodePourRegistry( GetRegistryValue( HKEY_LOCAL_MACHINE, HIDDEN_PATH, _HiddenKey )) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Codage d'une clef pour la stocker dans la registry
// Un petit codage bidon :
//		- Ou exclusif avec la valeur FILTRE_REGISTRY
//		- Rotation de n bit vers la gauche
///////////////////////////////////////////////////////////////////////////////
DWORD	CRegistrationKey::CodePourRegistry( DWORD dw )
	{
	dw ^= FILTRE_REGISTRY ;
	dw	= _lrotl( dw, 2 ) ;

	return dw ;
	}

///////////////////////////////////////////////////////////////////////////////
// Decodage d'une clef codee dans la registry
// Decodage en fonction du codage precedent :
//		- Rotation de 1 bit vers la droite
///////////////////////////////////////////////////////////////////////////////
DWORD	CRegistrationKey::DecodePourRegistry( DWORD dw )
	{
	dw	=	_lrotr( dw, 2 ) ;
	dw ^=	FILTRE_REGISTRY ;

	return dw ;
	}

///////////////////////////////////////////////////////////////////////////////
// Codage d'une clef pour la stocker dans la registry
///////////////////////////////////////////////////////////////////////////////
DWORD	CRegistrationKey::CodePourEcran( DWORD dw )
	{
	dw	=	_lrotr( dw, 3 ) ;
	return dw ^ FILTRE_ECRAN ;
	}

///////////////////////////////////////////////////////////////////////////////
// Decodage d'une clef codee dans la registry
///////////////////////////////////////////////////////////////////////////////
DWORD	CRegistrationKey::DecodePourEcran( DWORD dw )
	{
	dw	^=  FILTRE_ECRAN ;
	return _lrotl( dw, 3 ) ;
	}


DWORD	CRegistrationKey::CheckSum( const char * pChar)
{
	DWORD	Cde	=	0 ;
	while (	*pChar )
		{
		Cde += (*pChar ) ;
		pChar ++ ;
		}

	return Cde ;
}

DWORD	CRegistrationKey::CheckSum( const char * pChar, DWORD Taille )
	{
	DWORD i = 0 ;
	DWORD	Cde	=	0 ;
	while ( i < Taille )
		{
		Cde += (*pChar ) ;
		pChar ++ ;
		i ++ ;
		}

	return Cde ;
	}

#ifdef DEBLOQUE
DWORD CRegistrationKey::GetUnlockKey( const char * LockKey )
{
	CString Lock( LockKey ) ;

	// Extraire eventuellement la sous chaine representative du logiciel
	const int Debut	=	Lock.Find( '[' ) ;
	const int Fin	=	Lock.Find( ']' ) ;

	if ( Debut != -1 && Debut != -1 && Debut < Fin )
		Lock	=	Lock.Mid( Fin + 1 ) ;

	int i = 0 ;
	while ( i < Lock.GetLength() )
		if( strchr( "0123456789abcdefABCDEF", Lock[i] ))
			i ++ ;
		else
			Lock	=	Lock.Left( i ) + Lock.Right( Lock.GetLength() - i - 1 ) ;

	Lock	=	"0x" + Lock ;

	char * pEnd ;
	const DWORD	dwVal	=	strtoul( Lock, &pEnd, 16 ) ;

	const DWORD	Clef	=	DecodePourEcran( dwVal ) ;
	return Clef ;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// GetDisplayableLockKey
// Obtenir une version "affichable" de la clef cachee.
// On applique le codage special ecran a la clef cachee.
// Puis on transforme en chaine de caracteres
///////////////////////////////////////////////////////////////////////////////
CString CRegistrationKey::GetDisplayableLockKey( void )
{
	DWORD	Cachee				=	CodePourEcran( ClefCachee() ) ;
	DWORD	CheckSumLogiciel	=	CheckSum( _SoftwareName ) ;

	CString Res ;
	Res.Format( "[%04X]-{%04X}-(%04X)",
				(int)LOWORD( CheckSumLogiciel ),
				(int)HIWORD(Cachee),
				(int)LOWORD(Cachee) ) ;

	return Res ;
}

CRegistrationKey* CRegistrationKey::GetKey()
{
	return _pZeOnlyOuane ;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CRegistrationKey::SetRegistryValue(HKEY hRoot, const char * pPath, const char * pValueName, LPBYTE lpData, int Taille)
{
	HKEY	hKey ;
	DWORD Disp ;

	if ( ERROR_SUCCESS == RegCreateKeyEx( hRoot,  pPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &Disp ))
		{
		RegSetValueEx( hKey, pValueName, 0, REG_BINARY, lpData, Taille) ;
		RegCloseKey( hKey ) ;
		}
}
