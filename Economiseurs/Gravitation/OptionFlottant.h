// OptionFlottant.h: FLOTTANTerface for the COptionFlottant class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONFLOTTANT_H__AAA77313_27B3_11D3_A5A9_00A04B04180E__INCLUDED_)
#define AFX_OPTIONFLOTTANT_H__AAA77313_27B3_11D3_A5A9_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Option.h"

#define FLOTTANT double

class COptionFlottant : public COption  
{
	public :
	COptionFlottant( const TCHAR * pNom, BOOL bModifiableShareware,
				   FLOTTANT	 Min,
				   FLOTTANT   Max,
				   FLOTTANT	 Defaut,
				   FLOTTANT	 Shareware,
				   FLOTTANT	 Apercu
				 );

	COptionFlottant() : COption( "", TRUE ) { _Initialise = FALSE ; } ;

	BOOL	Initialisee() const { return _Initialise ; }

	virtual ~COptionFlottant();

	virtual BOOL ValeurCorrecte( BOOL bFLOTTANTeractif )  ;

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

	operator FLOTTANT () { return _Courant ; } ;
	void	Set( FLOTTANT f ) { _Courant = f ; ValeurCorrecte( FALSE ) ; }

	void	SetValues( FLOTTANT Min, FLOTTANT Max, FLOTTANT Courant, FLOTTANT Defaut, FLOTTANT Shareware, FLOTTANT Apercu )
		{
		_Shareware	=	Shareware ;
		_Min		=	Min ;
		_Max		=	Max ;
		_Courant	=	Courant ;
		_Defaut		=	Defaut ;
		_Apercu		=	Apercu ;
		_Initialise	=	TRUE ;
		}


private:
	FLOTTANT	_Min ;
	FLOTTANT	_Max ;
	FLOTTANT	_Courant ;
	FLOTTANT	_Defaut ;
	FLOTTANT	_Config ;
	FLOTTANT	_Apercu ;
	FLOTTANT	_Shareware ;
	BOOL		_Initialise ;
};

#endif // !defined(AFX_OPTIONFLOTTANT_H__AAA77313_27B3_11D3_A5A9_00A04B04180E__INCLUDED_)
