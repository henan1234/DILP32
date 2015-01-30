// OptionEntier.cpp: implementation of the COptionEntier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ecogravitation.h"
#include "OptionEntier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
COptionEntier::COptionEntier( const TCHAR * pNom, BOOL bModifiableShareware,
				   int	 Min,
				   int   Max,
				   int	 Defaut,
				   int	 Shareware,
				   int	 Apercu
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

COptionEntier::~COptionEntier()
	{
	}

BOOL COptionEntier::ValeurCorrecte( BOOL bInteractif )
	{
	bInteractif ;

	if ( _Courant < _Min )
		_Courant	=	_Min ;

	if ( _Courant > _Max )
		_Courant = _Max ;

	return (_Courant >= _Min && _Courant <= _Max ) ;
	}

// Lecture de configuration
void COptionEntier::LitRegistry( HKEY hRoot )
	{
	DWORD	Data ;
	DWORD	Taille	=	sizeof( Taille ) ;
	DWORD	Type	=	REG_DWORD ;

	if ( ERROR_SUCCESS == RegQueryValueEx( hRoot, Nom(), NULL, &Type,(LPBYTE)&Data, &Taille))
		_Config	= (int)Data ;
	else
		_Config	=	_Defaut ;

	_Courant = _Config ;
	TRACE( "%s lu de la registry = %d\n", (const char*)Nom(), _Courant ) ;
	}

void COptionEntier::LitFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	_Config	=	GetPrivateProfileInt( pSection, Nom(), _Defaut, pFile ) ;
	_Courant	=	_Config ;
	TRACE( "%s lu du fichier = %d\n", (const char*)Nom(), _Courant ) ;
	}



	// Ecriture configuration
void COptionEntier::EcritRegistry( HKEY hRoot )
	{
	DWORD	Data	=	_Courant ;
	DWORD	Taille	=	sizeof( Data ) ;

	RegSetValueEx( hRoot, Nom(), NULL, REG_DWORD, (LPBYTE)&Data, Taille ) ;
	TRACE( "%s ecrit ds registry = %d\n", (const char*)Nom(), _Courant ) ;
	}

///////////////////////////////////////////////////////////////////////////////
//	EcritFichier
//	Ecriture de l'option dans le fichier donne en parametre
//
///////////////////////////////////////////////////////////////////////////////
void COptionEntier::EcritFichier( const TCHAR * pFile, const TCHAR * pSection )
	{
	CString	Valeur ;
	Valeur.Format( "%d", _Courant ) ;
	WritePrivateProfileString( pSection, Nom(), Valeur, pFile ) ;
	TRACE( "%s ecrit ds fichier = %d\n", (const char*)Nom(), _Courant ) ;
	}

// Switch entre les valeurs
void COptionEntier::ValeurDefaut( void )
	{
	_Courant	=	_Defaut ;
	}

void COptionEntier::ValeurApercu( void )
	{
	_Courant	=	_Apercu ;
	}
	

void COptionEntier::ValeurShareware( void )
	{
	_Courant	=	_Shareware ;
	}

void COptionEntier::ValeurEnregistree( void )
	{
	_Courant	=	_Config ;
	}


void COptionEntier::Set( int v )
	{ 
	_Courant = v; 
	ValeurCorrecte( FALSE ) ; 
	} 
