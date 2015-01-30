// OptionChaine.cpp: implementation of the COptionChaine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ecoGravitation.h"
#include "OptionChaine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
COptionChaine::COptionChaine( const TCHAR * pNom, BOOL bModifiableShareware,
							   CString Defaut,
							   CString Shareware,
							   CString Apercu,
							   UINT	   Extension,
							   UINT	   Filtre
							 )
				 :COption( pNom, bModifiableShareware )
	{
	_Defaut		=	Defaut ;
	_Shareware	=	Shareware ;
	_Apercu		=	Apercu ;
	_Courant	=	Defaut ;
	_IdExtension=	Extension ;
	_IdFiltre	=	Filtre ;
	}

COptionChaine::~COptionChaine()
	{
	}

BOOL COptionChaine::ValeurCorrecte( BOOL bInteractif )
	{
	bInteractif ;
	return TRUE ;
	}

// Lecture de configuration
void COptionChaine::LitRegistry( HKEY hRoot )
	{
	char	Valeur [ 1024 ] ;
	DWORD	Taille	=	sizeof( Valeur ) ;
	DWORD Type	=	REG_SZ ;

	if ( RegQueryValueEx( hRoot, Nom(), 0, &Type, (LPBYTE)Valeur, &Taille) == ERROR_SUCCESS )
		_Config	=	Valeur ;
	else
		_Config	=	_Defaut ;

	_Courant = _Config ;
	TRACE( "%s lue dans la registry = %s\n", (const char *)Nom(), (const char *)_Courant ) ;
}

void COptionChaine::LitFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	char Valeur[1024] ;
	if ( GetPrivateProfileString( pSection, Nom(), "", Valeur, sizeof( Valeur ), pFile ) )
		_Config	=	Valeur ;
	else
		_Config	=	_Defaut ;

	_Courant = _Config ;
	TRACE( "%s lue depuis le fichier = %s\n", (const char *)Nom(), (const char *)_Courant ) ;
	}



	// Ecriture configuration
void COptionChaine::EcritRegistry( HKEY hRoot )
	{
	RegSetValueEx( hRoot, Nom(), 0, REG_SZ, (LPBYTE)(LPCSTR)_Courant, _Courant.GetLength()+1 ) ;
	TRACE( "%s ecrite dans la registry = %s\n", (const char *)Nom(), (const char *)_Courant ) ;
	}

void COptionChaine::EcritFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	WritePrivateProfileString( pSection, Nom(), _Courant, pFile ) ;
	TRACE( "%s ecrite dans le fichier = %s\n", (const char *)Nom(), (const char *)_Courant ) ;
	}

// Switch entre les valeurs
void COptionChaine::ValeurDefaut( void )
	{
	_Courant	=	_Defaut ;
	}

void COptionChaine::ValeurApercu( void )
	{
	_Courant	=	_Apercu ;
	}
	

void COptionChaine::ValeurShareware( void )
	{
	_Courant	=	_Shareware ;
	}

void COptionChaine::ValeurEnregistree( void )
	{
	_Courant	=	_Config ;
	}

