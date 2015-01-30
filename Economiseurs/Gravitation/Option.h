// Option.h: interface for the COption class.
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COption
{
public:
	COption( const TCHAR * pNom, BOOL bModifiableShareware ) ;
	virtual ~COption();

	// Verif valeur
	virtual BOOL ValeurCorrecte( BOOL bInteractif ) = 0 ;

	// Lecture de configuration
	virtual void LitRegistry( HKEY hRoot ) = 0 ;
	virtual void LitFichier( const TCHAR * pFile, const TCHAR * pSection ) = 0 ;

	// Ecriture configuration
	virtual void EcritRegistry( HKEY hRoot ) = 0 ;
	virtual void EcritFichier( const TCHAR * pFile, const TCHAR * pSection ) = 0 ;

	// Switch entre les valeurs
	virtual void ValeurDefaut( void ) = 0 ;
	virtual void ValeurApercu( void ) = 0 ;
	virtual void ValeurShareware( void ) = 0 ;
	virtual void ValeurEnregistree( void ) = 0 ;

	CString & Nom() { return _Nom ; }

	BOOL	ModifiableShareware() const { return _ModifiableShareware ; } ;

private:
	CString	_Nom ;
	BOOL	_ModifiableShareware ;
};


