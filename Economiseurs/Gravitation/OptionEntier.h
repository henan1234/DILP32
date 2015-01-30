// OptionEntier.h: interface for the COptionEntier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONENTIER_H__ACE39F33_2549_11D3_A5A5_00A04B04180E__INCLUDED_)
#define AFX_OPTIONENTIER_H__ACE39F33_2549_11D3_A5A5_00A04B04180E__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "option.h"

class COptionEntier: public COption
{
public:
	COptionEntier( const TCHAR * pNom, BOOL bModifiableShareware,
				   int	 Min,
				   int   Max,
				   int	 Defaut,
				   int	 Shareware,
				   int	 Apercu
				 );

	COptionEntier() : COption( "", FALSE ) { _Initialise = FALSE ;} ;

	BOOL	Initialisee() const { return _Initialise ; }

	virtual ~COptionEntier();

	virtual BOOL ValeurCorrecte( BOOL bInteractif )  ;

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

	operator int() { return _Courant ; } ;
	void			Set( int v ) ;
	void	SetValues( int Min, int Max, int Courant, int Defaut, int Shareware, int Apercu )
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
	int _Min ;
	int _Max ;
	int _Courant ;
	int _Defaut ;
	int	_Config ;
	int _Apercu ;
	int	_Shareware ;
	BOOL	_Initialise ;
};

#endif // !defined(AFX_OPTIONENTIER_H__ACE39F33_2549_11D3_A5A5_00A04B04180E__INCLUDED_)
