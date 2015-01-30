///////////////////////////////////////////////////////////////////////////////
// UniverseFile.cpp
//	Economiseur Gravitation, lecture des fichiers Universe
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "..\..\CLASSES\RegistrationKey.h"

// Supprime le warning qui annonce qu'une fonction est mise en inline
#pragma warning( disable : 4711 )

#include "EcoGravitation.h"
extern void _cdecl Error( const TCHAR * pMessage, ... ) ;
#include "options.h"

BOOL ChercheFichier( const TCHAR * pUniverseFile, CString & Fichier )
	{
	UINT Err = SetErrorMode( SEM_NOOPENFILEERRORBOX ) ;
	CFileStatus Status ;

	if ( CFile::GetStatus( Fichier, Status ))
		return TRUE ;

	TCHAR	FName[_MAX_FNAME] ;
	TCHAR	FExt[_MAX_EXT] ;
	_tsplitpath( (const TCHAR *)Fichier, 0, 0, FName, FExt ) ;

	// Essayer dans le meme repertoire que le .UNIVERSE
	TCHAR	Drive[_MAX_DRIVE] ;
	TCHAR	Path[_MAX_PATH] ;

	_tsplitpath( pUniverseFile, Drive, Path, 0, 0 ) ;
	TCHAR	Buffer[MAX_PATH] ;
	_tmakepath( Buffer, Drive, Path, FName, FExt ) ;

	if ( CFile::GetStatus( Buffer, Status ))
		{
		Fichier = Buffer ;
		return TRUE ;
		}

	SetErrorMode( Err ) ;

	return FALSE ;
	}

BOOL	ChercheFichier( const TCHAR * pUniverseFile, COptionChaine & Option )
	{
	CString	Nom( Option ) ;

	if ( ChercheFichier( pUniverseFile, Nom ))
		{
		Option.Set( Nom ) ;
		TRACE( "%s trouvé dans %s\n", pUniverseFile, (const TCHAR *)Nom ) ;
		return TRUE ;
		}

	return FALSE ;
	}
///////////////////////////////////////////////////////////////////////////////
// Lecture de tous les parametres dans un fichier
// Le fichier aura un format de .INI
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::LoadFile(const char * pFileName)
{
	CEconomiseur::LoadFile( pFileName ) ;

	// Memoriser les options qui ne doivent pas changer de valeur
	//const int			Depart		=	COptions::Depart() ;
	const CString		FichierIni	=	COptions::FichierInit() ;

	CRegistrationKey*	pKey = CRegistrationKey::GetKey() ;
	GetOptions()->LitFichier( NomEconomiseur(), pFileName, Apercu(), pKey->IsLocked() ) ;

	// Recherche des fichiers references dans le fichier UNIVERSE
//	for ( int i = 0; i < COptions::NbImages(); i++)
//		ChercheFichier( pFileName, COptions::NomImage( i ) ) ;

//	for ( i = 0; i < COptions::NbElementsDecors(); i++)
//		ChercheFichier( pFileName, COptions::NomDecors( i )) ;

//	ChercheFichier( pFileName, COptions::NomExplosion()) ;
//	ChercheFichier( pFileName, COptions::NomPalette()) ;

	// Verification des parametres lus dans le fichier
	ValidePreferences() ;

	//COptions::Depart().Set( Depart ) ;
	COptions::FichierInit().Set( FichierIni ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Lecture des noms de fichiers des images de planetes a partir du fichier
// univers
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::LitImagesPlanetes(const TCHAR * /*pFileName*/ )
{
	// Nombre de planetes
/*	if ( ! ChercheFichier( pFileName, COptions::NomPalette() ))
		Error( "Error in %s universe file, the palette file %s cannot be found",
				pFileName, (const TCHAR *)COptions::NomPalette() ) ;

	if ( COptions::NbImages() < 2 || COptions::NbImages() >= NB_MAX_IMAGES )
		Error( "Error in %s universe file, the number of planet images must be beetwen 2 and %d",
				pFileName,
				NB_MAX_IMAGES ) ;
	
	if ( COptions::ImageComete() < -1 || COptions::ImageComete() >= COptions::NbImages() )
		Error( "Wrong Comete image index=%d in %s universe file",
				COptions::ImageComete(),
				pFileName ) ;

	// Decors
	if ( COptions::NbElementsDecors() < 0 || COptions::NbElementsDecors() > NB_MAX_DECORS )
		Error( "Error in %s universe file, the background images count must be between 0 and %d",
				pFileName, (int)NB_MAX_DECORS ) ;
*/
}

///////////////////////////////////////////////////////////////////////////////
// Generation du systeme a partir d'un fichier
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::GenereDeFichier()
{
	// recuperation des parametres eventuels pour ecraser les valeurs par defaut
	LoadFile( COptions::FichierInit() ) ;
	COptions::Depart().Set( 5 ) ;

	int IndicePlanete	=	0 ;
	BOOL	Continuer = TRUE ;

	do
		{
		if ( IndicePlanete >= COptions::NbMaxCorps() )
			Continuer	=	FALSE ;
		else
			{
			// Lit les infos sur la planete no IndicePlanete
			CString	Format ;
			Format.LoadString( IDS_FORMATPLANET ) ;
			CString NomPlanete ;
			NomPlanete.Format( Format, IndicePlanete ) ;

			// Lecture de la masse de la planete
			CString StMasse ; StMasse.LoadString( IDS_MASSE ) ;
			char	Buffer[10] ;

			if ( GetPrivateProfileString( NomPlanete, StMasse, "", Buffer, sizeof( Buffer ), COptions::FichierInit() ))
				{
				LitInfosPlanetes( NomPlanete, IndicePlanete ) ;
				IndicePlanete	++ ;
				}
			else
				{
				Continuer	=	FALSE ;
				}
			}
		}
	while ( Continuer ) ;

	NbCorps	=	IndicePlanete ;
}

///////////////////////////////////////////////////////////////////////////////
// LitInfosPlanetes
//	Lecture des informations d'une planete dans le fichier de configuration
// Syntaxe :
//	[NomPlanete]
//		Mass=xx
//		Pos=x,y,z		|			|	Orbit=<autre planete>
//		Speed=x,y,z		|	ou		|	Distance=d
//									|
//		Rotation=x
//		Dust scattering=x
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::LitInfosPlanetes(const char * NomPlanete, int IndicePlanete)
{
	if ( IndicePlanete < 0 || IndicePlanete >= COptions::NbMaxCorps() )
		return ;

	memset( &_Corps[IndicePlanete], 0, sizeof( _Corps[IndicePlanete ] )) ;

	FLOTTANT	Masse	=	0 ;
	LitFichier( Masse, COptions::FichierInit(), NomPlanete, IDS_MASSE ) ;
	_Corps[IndicePlanete].Attraction	=	Masse * COptions::G() ;

	CString	StPos ;
	StPos.LoadString( IDS_POSITION ) ;

	char Buffer[10] ;
	if ( GetPrivateProfileString( NomPlanete, StPos, "", Buffer, sizeof( Buffer ), COptions::FichierInit() ))
		{
		// Position absolue donnee
		LitFlottants( _Corps[IndicePlanete].x, _Corps[IndicePlanete].y, _Corps[IndicePlanete].z,
					  NomPlanete,  IDS_POSITION ) ;

		LitFlottants( _Corps[IndicePlanete].vx, _Corps[IndicePlanete].vy, _Corps[IndicePlanete].vz,
					  NomPlanete,  IDS_VITESSE ) ;
		}
	else
		{
		// Calcul d'un orbite circulaire autour d'une autre planete
		CString	Rubrique ;
		Rubrique.LoadString( IDS_ORBITE ) ;

		const int PlaneteMere	=	GetPrivateProfileInt( NomPlanete, Rubrique, 0, COptions::FichierInit() ) ;

		if ( PlaneteMere >= 0 && PlaneteMere < IndicePlanete )
			{
			FLOTTANT	Distance = 0 ;
			LitFichier( Distance, COptions::FichierInit(), NomPlanete, IDS_DISTANCE ) ;
			
			FLOTTANT	Vitesse	=	VitesseOrbiteCirculaire( Distance, _Corps[PlaneteMere].Attraction ) ;


			// Calcul de la position et de la vitesse du satellite
			FLOTTANT	Angle = AngleAleatoire() ;
			_Corps[IndicePlanete].vx		=	Vitesse* sin( Angle + PI/2) + _Corps[PlaneteMere].vx ;
			_Corps[IndicePlanete].vy		=	Vitesse* cos( Angle + PI/2) + _Corps[PlaneteMere].vy ;
			_Corps[IndicePlanete].vz		=	_Corps[PlaneteMere].vz ;

			_Corps[IndicePlanete].x			=	_Corps[PlaneteMere].x + Distance*sin( Angle ) ;
			_Corps[IndicePlanete].y			=	_Corps[PlaneteMere].y + Distance*cos( Angle ) ;
			_Corps[IndicePlanete].z			=	_Corps[PlaneteMere].z ;
			}
		}

	LitFichier( _Corps[IndicePlanete].Rotation, COptions::FichierInit(), NomPlanete, IDS_ROTATION ) ;

	CString Value ; Value.LoadString( IDS_BRUITPOUSSIERE ) ;
	_Corps[IndicePlanete].BruitPoussiere = GetPrivateProfileInt( NomPlanete, Value, COptions::BruitPoussieres(), COptions::FichierInit() ) ;

	// Calcul des informations complementaires
	_Corps[IndicePlanete].Image	=	(int)ImagePourMasse( _Corps[IndicePlanete].Attraction ) ;
	_Corps[IndicePlanete].Phase	=	0 ;
	_Corps[IndicePlanete].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
}

void CEcoGravitation::LitFichier(FLOTTANT & Value, const char * pFichier, const char * pSection, UINT IdsValue)
{
	CString	ValueName ;
	ValueName.LoadString( IdsValue ) ;

	CString Val ;
	Val.Format( "%g", Value ) ;

	char Buffer[100] ;

	::GetPrivateProfileString( pSection, ValueName, Val, Buffer, sizeof( Buffer ), pFichier ) ;

	Value	=	atof( Buffer ) ;
}

///////////////////////////////////////////////////////////////////////////////
// LitFlottants
// Lire 3 flottants sur une ligne :  <valeur>=F1, F2, F3
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::LitFlottants(FLOTTANT & F1, FLOTTANT & F2, FLOTTANT & F3, const char * pSection, UINT Rubrique)
{
	const char * SEPARATEURS	=	" ,\t" ;
	CString	Value ;
	Value.LoadString( Rubrique ) ;

	char Buffer[200] ;
	GetPrivateProfileString( pSection, Value, "0,0,0", Buffer, sizeof( Buffer ), COptions::FichierInit() ) ;


	// 'Casser' la chaine en trois bouts
	char	*	pF1	= strtok( Buffer, SEPARATEURS ) ;
	char	*	pF2	= strtok( NULL, SEPARATEURS ) ;
	char	*	pF3	= strtok( NULL, SEPARATEURS ) ;

	if ( pF1 )
		F1	=	atof( pF1 ) ;

	if ( pF2 )
		F2	=	atof( pF2 ) ;

	if ( pF3 )
		F3	=	atof( pF3 ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Sauvegarde de tous les parametres dans un fichier
// Le fichier aura un format de .INI
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::SaveFile(const char * pFileName)
{
	CWaitCursor	Wait ;
	CEconomiseur::SaveFile( pFileName ) ;

	CRegistrationKey*	pKey = CRegistrationKey::GetKey() ;

	GetOptions()->EcritFichier( NomEconomiseur(), pFileName, pKey->IsLocked()) ;
}



