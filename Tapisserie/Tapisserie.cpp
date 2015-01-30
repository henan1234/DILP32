///////////////////////////////////////////////////////////////////////////////
// Tapisserie
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <protection.h>
#include "resource.h"
#include "tapisserie.h"
#include "TapisserieDlg.h"

CMonAppli MonApplication ;

void	CMonAppli::LitChaine( const char *	SousClef, const char	*	Rubrique, char	*	Buffer, int 	TailleBuffer )
{
	HKEY	hKey ;
	DWORD	Taille ;
 	DWORD	Type ;
	CString	Clef( CheminIni + "\\" + SousClef ) ;

	if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		return ;

 	Taille	=	TailleBuffer ;
	Type	=	REG_SZ ;

	RegQueryValueEx( hKey, Rubrique, 0, &Type, (LPBYTE)Buffer, &Taille) ;

	ASSERT( Taille <= (DWORD)TailleBuffer ) ;
}

DWORD	CMonAppli::LitEntier( const char *	SousClef, const char *	Rubrique, DWORD Defaut )
{
	DWORD Retour	=	Defaut ;
	HKEY	hKey ;
	DWORD	Taille ;
 	DWORD	Type ;
	CString	Clef( CheminIni + "\\" + SousClef ) ;

	if ( RegOpenKeyEx( HKEY_CURRENT_USER, Clef, 0, KEY_ALL_ACCESS, &hKey  ) != ERROR_SUCCESS )
		return Retour ;

 	Taille	=	sizeof( Retour ) ;
	Type	=	REG_DWORD ;

	if ( RegQueryValueEx( hKey, Rubrique, 0, &Type, (LPBYTE)&Retour, &Taille) != ERROR_SUCCESS )
		Retour	=	Defaut ;

	return Retour ;
}

void	CMonAppli::EcritChaine( const char *	SousClef, const char	*	Rubrique, const char * Buffer )
{
	DWORD	Dispo ;
	HKEY	hKey ;
	CString	Clef( CheminIni + "\\" + SousClef ) ;

	
	if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
		return ;

	RegSetValueEx( hKey, Rubrique, 0, REG_SZ, (LPBYTE)Buffer, lstrlen( Buffer )+1) ;
}

void	CMonAppli::EcritEntier( const char *	SousClef, const char	*	Rubrique, DWORD	Entier )
{
	DWORD	Dispo ;
	HKEY	hKey ;
	CString	Clef( CheminIni + "\\" + SousClef ) ;

	if ( RegCreateKeyEx( HKEY_CURRENT_USER, Clef, 0, "", REG_OPTION_NON_VOLATILE,
						 KEY_ALL_ACCESS, NULL, &hKey, &Dispo ) != ERROR_SUCCESS )
		return ;

	RegSetValueEx( hKey, Rubrique, 0, REG_DWORD, (LPBYTE)&Entier, sizeof( Entier )) ;
}


BOOL	CMonAppli::Enregistree()
{
	return	::Enregistree( "Tapisserie", "Enr-005" ) ;
}

const	CString		CMonAppli::CheminIni	= "Software\\Lucien PILLONI\\Tapisserie" ;

///////////////////////////////////////////////////////////////////////////////
// Initialisation de l'application
///////////////////////////////////////////////////////////////////////////////
BOOL	CMonAppli::InitInstance()
{
	Enable3dControls();

	CTapisserieDlg dlg( IDS_TITRE );

	m_pMainWnd = &dlg;

	dlg.DoModal();

	return FALSE ;
}
