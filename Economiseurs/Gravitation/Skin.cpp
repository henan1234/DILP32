// Skin.cpp: implementation of the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ecogravitation.h"
#include "Skin.h"

// Supprime le warning qui annonce qu'une fonction est mise en inline
#pragma warning( disable : 4711 )
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int			CSkin::_NbImages ;
int			CSkin::_CouleurRepere ;
int			CSkin::_ImageComete ;
int			CSkin::_NbElementsDecors ;
BYTE		CSkin::_Transparence ;

int			CSkin::_NbCouleursEtoiles ;
BYTE		CSkin::_CouleursEtoiles[ NB_MAX_COULEURS_ETOILES ] ;
int			CSkin::_NbCouleursCometes ;
BYTE		CSkin::_CouleursCometes[ NB_MAX_COULEURS_COMETES ] ;
CString		CSkin::_SkinFile = "" ;

extern void _cdecl Error( const TCHAR * pMessage, ... );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkin::CSkin()
{
	ValeursDefaut() ;
}

CSkin::~CSkin()
{

}

//////////////////////////////////////////////////////////////////////
//	SetFile
//	Ouverture d'un fichier skin : lire les valeurs a l'interieur
//////////////////////////////////////////////////////////////////////
void	CSkin::SetFile( const char * pFile ) 
{

	_SkinFile	=	pFile ;

	CFileStatus	Status ;

	if ( ! CFile::GetStatus( pFile, Status ))
		Error( "Skin file %s not found", pFile ) ;

	// Lecture
	_NbImages			=	GetInt( "Nb images", _NbImages ) ;
	_CouleurRepere		=	(BYTE)GetInt( "Crosshair color index", _CouleurRepere ) ;
	_ImageComete		=	GetInt( "Comet image", _ImageComete ) ;
	_NbElementsDecors	=	GetInt( "Nb background images", _NbElementsDecors ) ;
	_Transparence		=	(BYTE)GetInt( "Transparency", _Transparence ) ;
	_NbCouleursEtoiles	=	GetInt( "Nb star colors", _NbCouleursEtoiles ) ;
	_NbCouleursCometes	=	GetInt( "Nb comet colors", _NbCouleursCometes ) ;

	Controle( _NbImages, 1, NB_MAX_IMAGES ) ;
	Controle( _ImageComete, -1, _NbImages-1 ) ;
	Controle( _NbCouleursCometes, 0, NB_MAX_COULEURS_COMETES ) ;
	Controle( _NbCouleursEtoiles, 0, NB_MAX_COULEURS_ETOILES ) ;

	for ( int i = 0; i < _NbCouleursCometes; i++)
	{
		CString	Ligne ;
		Ligne.Format( "Comet color %d", i ) ;
		_CouleursCometes[i]	=	(BYTE)GetInt( Ligne, _CouleursCometes[i] ) ;
	}

	for ( i = 0; i < _NbCouleursEtoiles; i++)
	{
		CString	Ligne ;
		Ligne.Format( "Star color %d", i ) ;
		_CouleursEtoiles[i]	=	(BYTE)GetInt( Ligne, _CouleursEtoiles[i] ) ;
	}

}

//////////////////////////////////////////////////////////////////////
// Retour aux valeurs par defaut
//////////////////////////////////////////////////////////////////////
void	CSkin::ValeursDefaut()
{
	_SkinFile = "" ;
	static const int	CouleursEtoiles[NB_MAX_COULEURS_ETOILES]	=	
									{
									246, 245, 244, 243, 242,
									230, 229, 228, 227, 226,
									201, 200, 194
									} ;

	static const int CouleursCometes[NB_MAX_COULEURS_COMETES]	=	
		{
		239, 238, 237, 236, 231, 230, 229,227, 226, 225,
		191, 187, 186, 127
		} ;

	_NbImages			=	8 ;
	_CouleurRepere		=	135 ;
	_ImageComete		=	1 ;
	_NbElementsDecors	=	4 ;
	_Transparence		=	0 ;
	_NbCouleursEtoiles	=	sizeof( CouleursEtoiles ) / sizeof( CouleursEtoiles[0] ) ;
	_NbCouleursCometes	=	sizeof( CouleursCometes ) / sizeof( CouleursCometes[0] ) ;


	for ( int i = 0; i < _NbCouleursCometes; i++)
	{
		_CouleursCometes[i]	=	(BYTE)CouleursCometes[i] ;
	}

	for ( i = 0; i < _NbCouleursEtoiles; i++)
	{
		_CouleursEtoiles[i]	=	(BYTE)CouleursEtoiles[i] ;
	}


}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int CSkin::GetInt(const TCHAR *Val, int Defaut)
{
	return GetPrivateProfileInt( "Skin", Val, Defaut, _SkinFile ) ;
}

void CSkin::Controle(int &Val, int Min, int Max)
{
	if ( Val < Min )
		Val	=	Min ;

	if ( Val > Max )
		Val	=	Max ;
}


BOOL CSkin::CreateDecors( int NoDecors, CDIB * pDib )
{
	CString	Nom ;
	Nom.Format( "Background %d", NoDecors ) ;
	return LoadDIB( Nom, IDR_DIB0 + (UINT)NoDecors, pDib ) ;
}

BOOL CSkin::CreateExplosion( CDIB * pDib )
{
	return LoadDIB( "Explosion", IDB_EXPLOSION,  pDib ) ;
}


BOOL CSkin::CreatePalette( CDIBPal * pPal )
{
	CDIB Toutes ;
	if ( ! LoadDIB( "Palette", IDR_PALETTE, &Toutes ))
		return FALSE ;

	if ( ! pPal->Create( &Toutes ))
		return FALSE ;

	return TRUE ;
}

BOOL CSkin::CreatePhasesPlanete( int i, CDIB * pDib )
{
	CString	Nom ;
	Nom.Format( "Planet %d", i ) ;
	return LoadDIB( Nom, IDR_PLANETS0 + i, pDib ) ;
}

BOOL CSkin::LoadDIB(const TCHAR *pNom, WORD IDResource, CDIB *pDIB)
{
	CString NomFichier	=	GetNomFichier( pNom ) ;

	if ( NomFichier.IsEmpty())
		return pDIB->Load( IDResource ) ;
	else
		{
		if (! pDIB->Load( NomFichier ))
			{
			Error( "Failed to load %s image file, may be corrupted", (const TCHAR*)NomFichier ) ;
			return FALSE ;
			}
		return TRUE ;
		}
}

CString CSkin::GetNomFichier(const TCHAR *pNom)
{
	if ( _SkinFile.IsEmpty())
		return "" ;

	TCHAR Buffer[_MAX_PATH] ;
	GetPrivateProfileString( "Skin", pNom, "", Buffer, sizeof( Buffer ), _SkinFile ) ;

	CString	Fichier( Buffer ) ;
	if ( ChercheFichier( Fichier ))
		return Fichier ;

	return "" ;
}

BOOL CSkin::ChercheFichier( CString & Fichier )
	{
	UINT Err = SetErrorMode( SEM_NOOPENFILEERRORBOX ) ;
	CFileStatus Status ;

	// Essai : le nom du fichier texto
	if ( CFile::GetStatus( Fichier, Status ))
		return TRUE ;

	TCHAR	FName[_MAX_FNAME] ;
	TCHAR	FExt[_MAX_EXT] ;
	_tsplitpath( (const TCHAR *)Fichier, 0, 0, FName, FExt ) ;

	// A partir du repertoire du fichier .GravSkin, avec un chemin relatif
	TCHAR	Drive[_MAX_DRIVE] ;
	TCHAR	Path[_MAX_PATH] ;

	_tsplitpath( _SkinFile, Drive, Path, 0, 0 ) ;
	TCHAR	Buffer1[MAX_PATH] ;
	_tmakepath( Buffer1, Drive, Path, 0, 0 ) ;

	if ( Buffer1[strlen(Buffer1)-1] != '\\' )
		_tcscat( Buffer1,"\\" ) ;

	_tcscat( Buffer1, Fichier ) ;

	if ( CFile::GetStatus( Buffer1, Status ))
		{
		Fichier = Buffer1 ;
		return TRUE ;
		}

	// Dans le meme repertoire que le gravskin
	_tsplitpath( Fichier, 0, 0, FName, FExt ) ;
	_tsplitpath( _SkinFile, Drive, Path, 0, 0 ) ;

	TCHAR	Buffer2[MAX_PATH] ;
	_tmakepath( Buffer2, Drive, Path, FName, FExt ) ;
	if ( CFile::GetStatus( Buffer2, Status ))
		{
		Fichier	=	Buffer2 ;
		return TRUE ;
		}

	Error( "Cannot find file %s\r\nAlso tried %s, %s",
			(const TCHAR *)Fichier, Buffer1, Buffer2 ) ;

	SetErrorMode( Err ) ;

	return FALSE ;
	}
