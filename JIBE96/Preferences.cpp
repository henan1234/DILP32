///////////////////////////////////////////////////////////////////////////////
// Interface de la classe CPreferences
//	Un seul objet de cette classe sera instancie.
//	La fonction GetPreferences rendra l'adresse de cet objet
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Preferences.h"

CPreferences*	CPreferences::_pThePreference	=	0 ;

CPreferences::CPreferences( const char	*	AppName, HKEY	RootKey	 )
	{			  
	DWORD		Dispo ;
	CString		KeyName	=	"SOFTWARE\\Lucien Pilloni\\" ;
	KeyName		+= AppName ;
	VERIFY( RegCreateKeyEx( RootKey, KeyName, 0, "Preferences",
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS, NULL, &_hKeyPreferences, &Dispo ) == ERROR_SUCCESS ) ;

	ASSERT( _hKeyPreferences ) ;
	_pThePreference	=	this ;
	}
	
CPreferences::~CPreferences()
	{
	RegCloseKey( _hKeyPreferences ) ;
	}

void	CPreferences::LitPreference( const char * Name, CString & Valeur, const char * Defaut )
	{
	DWORD	Type ;
	DWORD	Taille ;

	// Longueur de la valeur
	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, NULL, &Taille )
		 != ERROR_SUCCESS )
		{
		Valeur	=	Defaut ;
		return ;
		}

	if ( Type != REG_SZ )
		{
		Valeur	=	Defaut ;
		return ;
		}

	char *	pValeur	=	Valeur.GetBuffer( Taille + 1 ) ;

	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, (LPBYTE)pValeur, &Taille ) != ERROR_SUCCESS )
		{
		Valeur.ReleaseBuffer() ;
		Valeur	=	Defaut ;
		return ;
		}

	Valeur.ReleaseBuffer() ;
	}


void	CPreferences::LitPreference( const char * Name, int& Valeur,	const int Defaut )
	{
	DWORD	Type ;
	DWORD	Taille ;

	// Longueur de la valeur
	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, NULL, &Taille )
		 != ERROR_SUCCESS )
		{
		Valeur	=	Defaut ;
		return ;
		}

	if ( Type != REG_DWORD )
		{
		Valeur	=	Defaut ;
		return ;
		}

	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, (LPBYTE)&Valeur, &Taille ) != ERROR_SUCCESS )
		{
		Valeur	=	Defaut ;
		return ;
		}
	}
		
void	CPreferences::LitPreference( const char * Name , double& Valeur,	const double  Defaut )
	{
	CString	ValeurLue ;
	CString	ValDefaut ;

	ValDefaut.Format( "%g", Valeur ) ;
	LitPreference( Name, ValeurLue, ValDefaut ) ;

	Valeur	=	atof( ValeurLue ) ;
	}
		
void	CPreferences::LitPreference( const char * Name, DWORD& Valeur, const DWORD Defaut )
	{
	DWORD	Type ;
	DWORD	Taille ;

	// Longueur de la valeur
	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, NULL, &Taille )
		 != ERROR_SUCCESS )
		{
		Valeur	=	Defaut ;
		return ;
		}

	if ( Type != REG_DWORD )
		{
		Valeur	=	Defaut ;
		return ;
		}

	if ( RegQueryValueEx( _hKeyPreferences, Name, 0, &Type, (LPBYTE)&Valeur, &Taille ) != ERROR_SUCCESS )
		{
		Valeur	=	Defaut ;
		return ;
		}
	}


void	CPreferences::EcritPreference( const char * Name, const char * Valeur )
	{
	VERIFY( RegSetValueEx( _hKeyPreferences, Name, 0, REG_SZ, (CONST BYTE *)Valeur, lstrlen( Valeur + 1 ))
			== ERROR_SUCCESS ) ;
	}
		
void	CPreferences::EcritPreference( const char * Name, int Valeur )
	{
	EcritPreference( Name, (DWORD)Valeur ) ;
	}
		
void	CPreferences::EcritPreference( const char * Name, double Valeur ) 
	{
	CString	Val ;
	Val.Format( "%g", Valeur ) ;
	EcritPreference( Name, Val ) ;
	}
		
void	CPreferences::EcritPreference( const char * Name, DWORD Valeur)
	{
	VERIFY(
			RegSetValueEx( _hKeyPreferences, Name, 0, REG_DWORD, (CONST BYTE *)&Valeur, sizeof( Valeur ))
			== ERROR_SUCCESS ) ;
	}

CPreferences *		GetPreferences( void )
	{
	ASSERT( CPreferences::_pThePreference ) ;
	return CPreferences::_pThePreference ;
	}