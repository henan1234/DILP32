// OptionChaine.h: CStringerface for the COptionChaine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONCHAINE_H__1F1B8EA3_27D2_11D3_A5A9_00A04B04180E__INCLUDED_)
#define AFX_OPTIONCHAINE_H__1F1B8EA3_27D2_11D3_A5A9_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Option.h"

class COptionChaine : public COption  
{
public:
public:
	COptionChaine( const TCHAR * pNom, BOOL bModifiableShareware,
				   CString	 Defaut,
				   CString	 Shareware,
				   CString	 Apercu,
				   UINT		 ExtensionFichier = 0 ,
				   UINT		 FiltreFichier = 0
				 );

	COptionChaine() : COption( "", TRUE ) {} ;
	virtual ~COptionChaine();

	virtual BOOL ValeurCorrecte( BOOL bCStringeractif )  ;

	// Lecture de configuration
	virtual void LitRegistry( HKEY hRoot ) ;
	virtual void LitFichier( const TCHAR * pFile, const TCHAR * pSection ) ;

	// Ecriture configuration
	virtual void EcritRegistry( HKEY hRoot ) ;
	virtual void EcritFichier( const TCHAR * pFile, const TCHAR * pSection ) ;

	// Switch entre les valeurs
	virtual void ValeurDefaut( void ) ;
	virtual void ValeurApercu( void ) ;
	virtual void ValeurShareware( void )  ;
	virtual void ValeurEnregistree( void ) ;

	CString & ValeurCourante() { return _Courant ; } ;
	operator const CString &() { return _Courant ; } ;
	operator const TCHAR *() { return _Courant ; } ;
	void	Set( const CString & c ) { _Courant = c ; }

	BOOL	IsEmpty( void ) const { return _Courant.IsEmpty() ; }

	CString	Filtre( void ) const { CString s ; s.LoadString( _IdFiltre ) ; return s ; }
	CString	Extension( void ) const { CString s ; s.LoadString( _IdExtension ); return s ; }

private:
	CString _Courant ;
	CString _Defaut ;
	CString	_Config ;
	CString _Apercu ;
	CString	_Shareware ;
	UINT	_IdExtension ;
	UINT	_IdFiltre ;
};

#endif // !defined(AFX_OPTIONCHAINE_H__1F1B8EA3_27D2_11D3_A5A9_00A04B04180E__INCLUDED_)
