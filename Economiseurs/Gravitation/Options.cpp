// Options.cpp: implementation of the COptions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ecogravitation.h"
#include "resource.h"
#include "Options.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

COptionEntier	COptions::_3D				("3D Model",				TRUE, FALSE, TRUE, TRUE, TRUE, FALSE ) ;
COptionEntier	COptions::_AfficherInfos	("Display information",		FALSE, FALSE, TRUE, FALSE, FALSE, FALSE ) ;
COptionEntier	COptions::_AfficherRepere	("Display crosshair",		FALSE, FALSE, TRUE, FALSE, FALSE, FALSE ) ;
COptionEntier	COptions::_BruitPoussieres	("Dust scattering",			TRUE, 0, 100, 20, 20, 20 ) ;
COptionEntier	COptions::_ChangerResolution("Change resolution",		FALSE, FALSE, TRUE, FALSE, FALSE, FALSE ) ;
COptionEntier	COptions::_CoeffLiberation	("Escape Velocity %",		TRUE, 0, 99, 10, 2, 10 ) ;
COptionFlottant	COptions::_CoeffMinMax		("Min max coeff",			FALSE,  0.5, 1.5, 1, 1, 1 );
COptionFlottant	COptions::_CoeffRayon		("Radius mult",				FALSE,  0.001, 1, 0.2, 0.05, 0.01 );
COptionFlottant	COptions::_CoeffTraveling	("Panning speed",			FALSE,  0, 1, 0.1, 0.1, 0.99 ) ;
COptionEntier	COptions::_CreationComete	("Comet creation frequency", FALSE, 0, 10000, 2000, 1000, 2000 ) ;
COptionEntier	COptions::_DecaleElementsDecors("Background traveling",	FALSE, -200, 200, 10, 10, 0 ) ;
COptionFlottant	COptions::_DeltaVMax		("Max relative speed",		FALSE,  0, 10000, 100, 100, 100 );
COptionEntier	COptions::_DensiteEtoiles	("Starfield density",		TRUE, 0, NB_MAX_ETOILES, 3000, 3000, 0 ) ;
COptionEntier	COptions::_Depart			("Universe creation method", FALSE, 0, 5, 3, 3, 3 ) ;
COptionFlottant	COptions::_DistMult			("Distance mult",			FALSE,  1, 1000000, 100, 100, 100 ) ;
COptionFlottant	COptions::_G				("G",						TRUE,  1, 100000, 2000, 10000, 2000 );
COptionEntier	COptions::_NbImagesSeconde	("Nb images per second",	FALSE, 10, 40, 25, 25, 25 ) ;
COptionEntier	COptions::_NbInitCorps		("Initial planets number",	TRUE, 1, NB_MAX_CORPS, 10, 10, 4 ) ;
COptionEntier	COptions::_NbMaxCorps		("Max Planet number",		TRUE, 1, NB_MAX_CORPS, 50, 50, 3 ) ;
COptionEntier	COptions::_NbMaxPoussiere	("Dust max number",			FALSE, 0, NB_MAX_POUSSIERES, 200, 200, 10 ) ;
COptionEntier	COptions::_NbMinCorps		("Planets min number",		TRUE, 2, NB_MAX_CORPS, 3, 3, 2 ) ;
COptionFlottant	COptions::_TimeMult			("Time mult",				FALSE,  0.001, 10000, 1, 1, 1 );
COptionEntier	COptions::_TaillePoussieres	("Dust size",				FALSE, 1, 4, 2, 2, 2 ) ;
COptionFlottant	COptions::_VentSolaire		("Solar wind",				FALSE,  0, 10, 0.02, 0.05, 0.01 ) ;
COptionEntier	COptions::_ViePoussieres	("Dust life lenght",		FALSE, 0, 6, 2, 2, 2 ) ;
COptionFlottant	COptions::_ZoomMax			("Max zoom",				FALSE,  0, 10, 2, 1, 2 ) ;
COptionChaine	COptions::_FichierInit		("Universe file",			FALSE, "", "", "", IDS_UNIVERSE_EXTENSION, IDS_UNIVERSE_FILTRE ) ;
COptionFlottant	COptions::_MassesMax[ NB_MAX_IMAGES ] ;
COptionEntier	COptions::_ReinitSiPlusDEtoiles("Reinit if no more star", TRUE, FALSE, TRUE, TRUE, TRUE, TRUE ) ;
COptionChaine	COptions::_SkinFile( "Skin file", TRUE, "", "", "", IDS_SKIN_EXTENSION, IDS_SKIN_FILTRE ) ;
COptionEntier	COptions::_UseSkinFile( "Use skin file", TRUE, 0, 1, 0, 0, 0 ) ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



COptions::COptions()
{
	for ( int i = 0; i < NB_MAX_IMAGES; i++)
		{
		// Pour remplacer le constructeur dans les tableaux
		if ( ! _MassesMax[i].Initialisee() )
			{
			_MassesMax[i].Nom().Format( "Mass %d", i ) ;
			_MassesMax[i].SetValues( 0, 1000000000, pow( 2, i ), pow( 2, i ), pow( 2, i ), pow( 2, i )) ;
			}

		_Options.Add( &_MassesMax[i] ) ;
		}

	_Options.Add( &	_3D				) ;
	_Options.Add( &	_AfficherInfos	) ;
	_Options.Add( &	_AfficherRepere	) ;
	_Options.Add( & _BruitPoussieres ) ;
	_Options.Add( & _ChangerResolution ) ;
	_Options.Add( & _CoeffLiberation ) ;
	_Options.Add( & _CoeffMinMax) ;
	_Options.Add( &	_CoeffRayon		) ;
	_Options.Add( &	_CoeffTraveling	) ;
	_Options.Add( & _CreationComete ) ;
	_Options.Add( & _DecaleElementsDecors ) ;
	_Options.Add( &	_DeltaVMax		) ;
	_Options.Add( & _DensiteEtoiles ) ;
	_Options.Add( & _Depart ) ;
	_Options.Add( &	_DistMult			) ;
	_Options.Add( &	_G				) ;
	_Options.Add( & _NbImagesSeconde ) ;
	_Options.Add( & _NbInitCorps ) ;
	_Options.Add( & _NbMaxCorps ) ;
	_Options.Add( & _NbMaxPoussiere ) ;
	_Options.Add( & _NbMinCorps ) ;
	_Options.Add( & _TaillePoussieres ) ;
	_Options.Add( &	_TimeMult			) ;
	_Options.Add( &	_VentSolaire		) ;
	_Options.Add( & _ViePoussieres ) ;
	_Options.Add( &	_ZoomMax			) ;
	_Options.Add( & _ReinitSiPlusDEtoiles ) ;

	_Options.Add( & _FichierInit ) ;

	_Options.Add( &_SkinFile ) ;
	_Options.Add( &_UseSkinFile ) ;

}

COptions::~COptions()
{

}

///////////////////////////////////////////////////////////////////////////////
// Lit les options dans la registry
//	ATTENTION ! Si on est en mode apercu, on utilise les valeurs apercu
//				Sin on est en shareware, ca depend de l'option
///////////////////////////////////////////////////////////////////////////////
void	COptions::LitRegistry( const TCHAR * pNom, BOOL bApercu, BOOL bShareware )
	{
	HKEY	hKey ;
	if ( ERROR_SUCCESS != RegOpenKeyEx( HKEY_CURRENT_USER, pNom, 0, KEY_READ, &hKey ))
		return ;

	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption =	_Options[i] ;
		if ( bApercu )
			pOption->ValeurApercu() ;
		else
			if ( ! bShareware )
				pOption->LitRegistry( hKey ) ;
			else
				if ( pOption->ModifiableShareware())
					pOption->LitRegistry( hKey ) ;
				else
					pOption->ValeurShareware() ;
		}

	RegCloseKey( hKey ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Lit les options dans un fichier
//	ATTENTION ! Si on est en mode apercu, on utilise les valeurs apercu
//				Sin on est en shareware, ca depend de l'option
///////////////////////////////////////////////////////////////////////////////
void	COptions::LitFichier( const TCHAR * pNom, const TCHAR * pFichier, BOOL bApercu, BOOL bShareware )
	{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption =	_Options[i] ;
		if ( bApercu )
			pOption->ValeurApercu() ;
		else
			if ( ! bShareware )
				pOption->LitFichier( pFichier, pNom ) ;
			else
				if ( pOption->ModifiableShareware())
					pOption->LitFichier( pFichier, pNom ) ;
				else
					pOption->ValeurShareware() ;
		}

	VerifValeurs() ;
	}


///////////////////////////////////////////////////////////////////////////////
// Lit les options dans la registry
//	ATTENTION ! Si on est en mode apercu, on utilise les valeurs apercu
//				Sin on est en shareware, ca depend de l'option
///////////////////////////////////////////////////////////////////////////////
void	COptions::EcritRegistry( const TCHAR * pNom, BOOL bShareware )
	{
	HKEY	hKey ;
	DWORD	Disp ;

	if ( ERROR_SUCCESS != RegCreateKeyEx( HKEY_CURRENT_USER, pNom, 0, NULL, REG_OPTION_NON_VOLATILE, 
										  KEY_ALL_ACCESS, NULL, &hKey, &Disp ))
		return ;

	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption =	_Options[i] ;
		if ( !bShareware || pOption->ModifiableShareware() )
			pOption->EcritRegistry( hKey ) ;
		}

	RegCloseKey( hKey ) ;
	VerifValeurs() ;
	}


///////////////////////////////////////////////////////////////////////////////
// Lit les options dans un fichier
//	ATTENTION ! Si on est en mode apercu, on utilise les valeurs apercu
//				Sin on est en shareware, ca depend de l'option
///////////////////////////////////////////////////////////////////////////////
void	COptions::EcritFichier( const TCHAR * pNom, const TCHAR * pFichier, BOOL bShareware )
	{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption =	_Options[i] ;
		if ( !bShareware || pOption->ModifiableShareware() )
			pOption->EcritFichier( pFichier, pNom ) ;
		}
	}



///////////////////////////////////////////////////////////////////////////////
// Prend les valeurs shareware de chaque option
//	ATTENTION ! Si on est en mode apercu, on utilise les valeurs apercu
//				Sin on est en shareware, ca depend de l'option
///////////////////////////////////////////////////////////////////////////////
void	COptions::ValeursShareware(  )
	{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption = _Options[i] ;
		if ( ! pOption->ModifiableShareware())
			pOption->ValeurShareware() ;
		}

	VerifValeurs() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Prend les valeurs apercu de chaque option
///////////////////////////////////////////////////////////////////////////////
void	COptions::ValeursApercu(  )
	{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption = _Options[i] ;
		pOption->ValeurApercu() ;
		}
	VerifValeurs() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Prend les valeurs par defaut de chaque option
///////////////////////////////////////////////////////////////////////////////
void	COptions::ValeursDefaut(  )
	{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption = _Options[i] ;
		pOption->ValeurDefaut() ;
		}

	VerifValeurs() ;
	}


void COptions::VerifValeurs()
{
	for ( int i = 0; i < _Options.GetSize(); i++)
		{
		COption * pOption	=	_Options[i] ;
		pOption->ValeurCorrecte( FALSE ) ;
		}	
}
