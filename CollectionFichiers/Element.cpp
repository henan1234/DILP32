// Element.cpp: implementation of the CElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "Element.h"
#include "fileservices.h"
#include "cmp3Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CStringArray	CElement::_TousLesAttributs ;

IMPLEMENT_SERIAL( CElement, CObject, 1 ) ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElement::CElement()
{

}

CElement::~CElement()
{

}

CString CElement::GetAttribut(const CString &Nom)
{
	CString Res ;
	_Attributs.Lookup( Nom, Res ) ;
	return Res ;
}

BOOL CElement::Scanne( const CString & path, WIN32_FIND_DATA data, CScanningDlg & dlg,
					   CMapStringToString	& AttributsCommuns )
	{
	POSITION Pos	=	AttributsCommuns.GetStartPosition() ;
	while ( Pos )
		{
		CString Key ;
		CString Value ;
		AttributsCommuns.GetNextAssoc( Pos, Key, Value ) ;

		SetAttribut( Key, Value ) ;
		}

	SetAttribut( REPERTOIRE, CFileServices::GetParentDirectory( path )) ;
	SetAttribut( CHEMIN, path ) ;

	SetAttribut( NOM, data.cFileName ) ;

	_Data	=	data ;
	dlg.m_Fichier.SetWindowText( path ) ;

	if ( data.dwFileAttributes	& FILE_ATTRIBUTE_DIRECTORY )
		{
		SetAttribut( ELEMENT, "Répertoire" ) ;
		}
	else
		{
		SetAttribut( ELEMENT, "Fichier" ) ;
		

		// Taille
		__int64	Taille	=	(data.nFileSizeHigh<<(__int64)32)+data.nFileSizeLow ;
		CString		StTaille	=	CalculeTexteTaille( Taille  ) ;
		SetAttribut( TAILLE, StTaille ) ;

		// Extension
		char	Ext[_MAX_EXT] ;
		_tsplitpath( data.cFileName, NULL, NULL, NULL, Ext ) ;
		SetAttribut( EXTENSION, Ext ) ;

		// Type de fichier

		SHFILEINFO	FileInfo ;
		memset( &FileInfo, 0, sizeof( FileInfo )) ;

		GetSystemInfo( Ext ) ;

		if ( Taille > 0L )
			{
			GetFileCheckSum( path, Taille, dlg) ;

			ExtraitInfosFichier( path, Ext ) ;
			}
		}

	return TRUE ;
	}

	//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
CString CElement::CalculeTexteTaille(__int64 TailleFichier)
{
	CString res ;
	// Go ?
	if ( TailleFichier > ((__int64)1024*(__int64)1024*(__int64)1024))
		{
		TailleFichier /= (__int64)1024*(__int64)1024*(__int64)1024 ;
		res.Format( "%ld Go", TailleFichier ) ;
		}
	else
	// Mo ?
	if ( TailleFichier > ((__int64)1024*(__int64)1024))
		{
		TailleFichier /= (__int64)1024*(__int64)1024 ;
		res.Format( "%ld Mo", TailleFichier ) ;
		}
	else
	// Ko ?
	if ( TailleFichier > (__int64)1024)
		{
		TailleFichier /= (__int64)1024 ;
		res.Format( "%ld Ko", TailleFichier ) ;
		}
	else
	// OCtets ?
		{
		res.Format( "%ld Octets", TailleFichier ) ;
		}

	return res ;
}


///////////////////////////////////////////////////////////////////////////////
// Extrait les informations possible du fichier, dependant du type de fichier
///////////////////////////////////////////////////////////////////////////////
void CElement::ExtraitInfosFichier(const CString &File, const CString &Ext)
{
	if ( Ext.CompareNoCase( ".MP3" ) == 0 )
		ExtraitInfosMP3( File ) ;
}

void CElement::ExtraitInfosMP3(const CString &File)
{
	char Buffer[10240] ;
	strcpy( Buffer, File ) ;

	CString Format	;
	
	CMP3Info	infos ;
	if ( infos.loadInfo( Buffer ) != 0 )
		return ;

	if ( infos.isTagged())
		{
		infos.getAlbum( Buffer ) ;
		SetAttribut( "MP3 Album", Buffer ) ;

		infos.getArtist( Buffer ) ;
		SetAttribut( "MP3 Artiste", Buffer ) ;

		infos.getComment( Buffer ) ;
		SetAttribut( "MP3 Commentaire", Buffer ) ;

		infos.getGenre( Buffer ) ;
		SetAttribut( "MP3 Genre", Buffer ) ;
		
		infos.getTitle( Buffer ) ;
		SetAttribut( "MP3 Titre", Buffer ) ;

		int val	=	infos.getTrackNumber() ;
		Format.Format( "%d", val ) ;
		SetAttribut( "MP3 N° de piste", Format ) ;

		val	=	infos.getYear() ;
		Format.Format( "%d", val ) ;
		SetAttribut( "MP3 Année", Format ) ;
		
		}

	infos.getVersion( Buffer ) ;
	SetAttribut( "MP3 Version", Buffer ) ;


	int BitRate	=	infos.getBitrate() ;
	Format.Format( "%d b/s", BitRate ) ;
	SetAttribut( "MP3 BitRate", Format ) ;

	infos.getFormattedLength( Buffer ) ;
	SetAttribut( "MP3 Longueur", Buffer ) ;

	int Frequency	=	infos.getFrequency() ;
	Format.Format( "%d Hz", Frequency ) ;
	SetAttribut( "MP3 Frequence", Format ) ;

	infos.getMode( Buffer ) ;
	SetAttribut( "MP3 Mode", Buffer ) ;


}


///////////////////////////////////////////////////////////////////////////////
// Trouve la checksum d'un fichier
///////////////////////////////////////////////////////////////////////////////
void CElement::GetFileCheckSum(const CString &NomFichier, __int64 Taille, CScanningDlg & dlg )
{
	HANDLE	hFile		=	CreateFile( NomFichier,
										GENERIC_READ,
										FILE_SHARE_READ,
										NULL, 
										OPEN_EXISTING, 
										FILE_FLAG_SEQUENTIAL_SCAN,
										NULL ) ;

	if ( hFile == INVALID_HANDLE_VALUE )
		return ;

	HANDLE	hMapping	=	CreateFileMapping(hFile, NULL, PAGE_READONLY, (DWORD)(Taille >> (_int64)32), (DWORD)Taille,
											  NULL ) ;
	if ( ! hMapping )
		{
		CloseHandle( hFile ) ;
		return ;
		}

	LPVOID pFile = MapViewOfFile( hMapping, FILE_MAP_READ, 0, 0, 0 ) ;
	if ( ! pFile )
		{
		CloseHandle( hMapping ) ;
		CloseHandle( hFile ) ;
		return ;
		}

	__int64 Step = 1 ;
	__int64 Grandeur	=	Taille ;

	while ( Grandeur > (__int64)100 )
		{
		Grandeur /= (__int64)2 ;
		Step *= (__int64)2 ;
		}

	dlg.m_CheckSum.SetRange( 0, (int)(Taille/Step) ) ;
	dlg.m_CheckSum.SetStep(1) ;
	dlg.m_CheckSum.SetPos(0) ;

	__int64 Nb = Taille ;
	PBYTE	pByte	=	(PBYTE)pFile ;
	__int64	Result = 0 ;
	__int64	ThisStep	=	0 ;
	while( Nb > 0 )
		{
		Result += (__int64)*pByte ;
		pByte ++ ;
		Nb -= (__int64)sizeof( *pByte ) ;

		ThisStep ++ ;
		if ( ThisStep == Step )
			{
			dlg.m_CheckSum.StepIt() ;
			dlg.m_CheckSum.UpdateWindow() ;
			ThisStep	=	0 ;
			}
		}

	UnmapViewOfFile( pFile ) ;
	CloseHandle( hMapping ) ;
	CloseHandle( hFile ) ;

	CString CRC ;
	CRC.Format( "%ld", Result ) ;
	SetAttribut( "CRC64", CRC ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Retrouve les informations relatives au type de fichier
// ENTREE: Extension du fichier
///////////////////////////////////////////////////////////////////////////////
void CElement::GetSystemInfo(const CString &Ext)
{
	HKEY	hKey ;
	if ( RegOpenKey( HKEY_CLASSES_ROOT, "Ext", &hKey ) != ERROR_SUCCESS )
		return ;

	char	Buffer[1024] ;
	DWORD	Taille	=	sizeof( Buffer ) ;
	DWORD	Type	=	REG_SZ ;

	if ( RegQueryValueEx( hKey, NULL, 0, &Type, (LPBYTE)Buffer, &Taille ) == ERROR_SUCCESS )
		{
		SetAttribut( "Type de fichier", Buffer ) ;
		}
	RegCloseKey( hKey ) ;
}


void CElement::SetAttribut(const CString &Nom, const CString &Valeur)
{
	try
		{
		_Attributs.SetAt( Nom, Valeur ) ;
		}
	catch( CMemoryException e )
		{
		}

	
	ReferenceAttribut( Nom ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute un nom d'attribut dans la liste de tous les attributs existants
// ENTREE:	Nom d'un attribut
///////////////////////////////////////////////////////////////////////////////
void	CElement::ReferenceAttribut( const CString & NomAttribut )
	{
	const int Nb	=	_TousLesAttributs.GetSize() ;

	for ( int i = 0; i < Nb; i++)
		if ( NomAttribut == _TousLesAttributs[i] )
			// Existant
			return ;

	_TousLesAttributs.Add( NomAttribut ) ;
	}


void CElement::SetAttribut(const CString &Nom, int Valeur)
{
	CString Nombre ;
	Nombre.Format( "%d", Valeur ) ;
	SetAttribut( Nom, Nombre ) ;
}


void CElement::Serialize( CArchive & ar )
	{
	CObject::Serialize( ar ) ;
	_Attributs.Serialize( ar ) ;


	if ( ar.IsLoading())
		{
		ar.Read( &_Data, sizeof( _Data )) ;
		CStringList	Noms ;
		Noms.Serialize( ar ) ;
		CStringList Valeurs ;
		Valeurs.Serialize( ar ) ;

		ASSERT( Noms.GetCount() == Valeurs.GetCount()) ;

		POSITION PosNoms	=	Noms.GetHeadPosition() ;
		POSITION PosValeurs	=	Valeurs.GetHeadPosition() ;

		while (PosNoms && PosValeurs )
			{
			CString Nom	=	Noms.GetNext( PosNoms ) ;
			CString Valeur=	Noms.GetNext( PosValeurs ) ;

			SetAttribut( Nom, Valeur ) ;
			}
		}
	else
		{
		ar.Write(&_Data, sizeof( _Data )) ;

		CStringList Noms ;
		CStringList Valeurs ;

		POSITION Pos	=	_Attributs.GetStartPosition() ;
		while ( Pos )
			{
			CString Nom ;
			CString Valeur ;
			_Attributs.GetNextAssoc( Pos, Nom, Valeur ) ;

			Noms.AddTail( Nom ) ;
			Valeurs.AddTail( Valeur ) ;
			}

		Noms.Serialize( ar ) ;
		Valeurs.Serialize( ar ) ;
		}

	}

///////////////////////////////////////////////////////////////////////////////
// Retourne VRAI si cet element convient au filtre donne en parametre
// ENTREES:	Attribut sur lequel porte le filtre
//			Texte du filtre
// RETOUR:	VRAI si cet element convient
///////////////////////////////////////////////////////////////////////////////
BOOL CElement::ConvientPourFiltre(const CString &AttributFiltre, const CString &TexteFiltre)
{
	if ( TexteFiltre.IsEmpty())
		return TRUE ;

	CString TEXTE( TexteFiltre ) ;
	TEXTE.MakeUpper() ;

	if ( AttributFiltre.IsEmpty() )
		{
		POSITION Pos	=	_Attributs.GetStartPosition() ;
		
		while ( Pos  )
			{
			CString Nom ;
			CString Valeur ;
			_Attributs.GetNextAssoc( Pos, Nom, Valeur ) ;
			
			Valeur.MakeUpper() ;
			if ( ValeurConvient( TEXTE, Valeur ))
				return TRUE ;
			}
		}
	else
		{
		CString Valeur	=	GetAttribut( AttributFiltre ) ;
		Valeur.MakeUpper() ;

		if ( ValeurConvient( TEXTE, Valeur ))
			return TRUE ;
		}

	return FALSE ;
}

///////////////////////////////////////////////////////////////////////////////
// Retourne VRAI si la valeur donnee contient le texte
// ENTREES:	Texte a rechercher
//			Valeur
///////////////////////////////////////////////////////////////////////////////
BOOL CElement::ValeurConvient(const CString &Texte, const CString &Valeur)
{
	return ( -1 != Valeur.Find( Texte ) ) ;
}
