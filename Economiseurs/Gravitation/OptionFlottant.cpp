// OptionFlottant.cpp: implementation of the COptionFlottant class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionFlottant.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
COptionFlottant::COptionFlottant( const TCHAR * pNom, BOOL bModifiableShareware,
				   double	 Min,
				   double   Max,
				   double	 Defaut,
				   double	 Shareware,
				   double	 Apercu
				 )
				 :COption( pNom, bModifiableShareware )
	{
	_Min	=	Min ;
	_Max	=	Max ;
	_Defaut	=	Defaut ;
	_Shareware= Shareware ;
	_Apercu	=	Apercu ;
	_Courant=	Defaut ;
	_Initialise	=	TRUE ;
	}

COptionFlottant::~COptionFlottant()
	{
	}

BOOL COptionFlottant::ValeurCorrecte( BOOL bInteractif )
	{
	bInteractif ;

	if ( _Courant < _Min )
		_Courant	=	_Min ;

	if ( _Courant > _Max )
		_Courant	=	_Max ;

	return (_Courant >= _Min && _Courant <= _Max ) ;
	}

// Lecture de configuration
void COptionFlottant::LitRegistry( HKEY hRoot )
	{
	char	Valeur [ 1024 ] ;
	DWORD	Taille	=	sizeof( Valeur ) ;
	DWORD Type	=	REG_SZ ;

	if ( RegQueryValueEx( hRoot, Nom(), 0, &Type, (LPBYTE)Valeur, &Taille) == ERROR_SUCCESS )
		_Config	=	atof( Valeur ) ;
	else
		_Config	=	_Defaut ;


	_Courant = _Config ;
	TRACE( "%s lu ds la registry = %g\n", (const char *)Nom(), (double)_Courant ) ;
}

///////////////////////////////////////////////////////////////////////////////
// LitFichier
//	Lit l'option dans le fichier donne en parametre
///////////////////////////////////////////////////////////////////////////////
void COptionFlottant::LitFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	char Valeur[1024] ;
	if ( GetPrivateProfileString( pSection, Nom(), "", Valeur, sizeof( Valeur ), pFile ) )
		_Config	=	atof( Valeur ) ;
	else
		_Config	=	_Defaut ;

	_Courant = _Config ;
	TRACE( "%s lu du fichier = %g\n", (const char *)Nom(), (double)_Courant ) ;
	}



	// Ecriture configuration
void COptionFlottant::EcritRegistry( HKEY hRoot )
	{
	char	Buffer[50] ;

	gcvt( _Courant, 45, Buffer ) ;
	CString	Chaine( Buffer ) ;

	RegSetValueEx( hRoot, Nom(), 0, REG_SZ, (LPBYTE)(LPCSTR)Chaine, Chaine.GetLength()+1 ) ;
	TRACE( "%s ecrit ds la registry = %g\n", (const char *)Nom(), (double)_Courant ) ;
	}

void COptionFlottant::EcritFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	CString	Valeur ;
	Valeur.Format( "%g", _Courant ) ;
	WritePrivateProfileString( pSection, Nom(), Valeur, pFile ) ;
	TRACE( "%s ecrit ds fichier = %g\n", (const char *)Nom(), (double)_Courant ) ;
	}

// Switch entre les valeurs
void COptionFlottant::ValeurDefaut( void )
	{
	_Courant	=	_Defaut ;
	}

void COptionFlottant::ValeurApercu( void )
	{
	_Courant	=	_Apercu ;
	}
	

void COptionFlottant::ValeurShareware( void )
	{
	_Courant	=	_Shareware ;
	}

void COptionFlottant::ValeurEnregistree( void )
	{
	_Courant	=	_Config ;
	}

