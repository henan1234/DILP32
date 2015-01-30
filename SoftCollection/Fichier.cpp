// Fichier.cpp: implementation of the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoftCollection.h"
#include "Fichier.h"
#include "fileservices.h"
#include "CMP3Info.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int CFichier::IndiceImage = 0 ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFichier::CFichier()
{

}

CFichier::~CFichier()
{

}

BOOL CFichier::Scanne(const CString &path, const WIN32_FIND_DATA &data, CScanningDlg & dlg )
{
	if ( dlg.Abort())
		return FALSE ;
	

	dlg.m_Fichier.SetWindowText( path ) ;

	CElement::Scanne( path, data, dlg ) ;
	Nom( data.cFileName ) ;
	Path( path ) ;


	// Repertoire parent
	SetAttribut( "Répertoire parent", CFileServices::GetParentDirectory( path ) ) ;

	// Taille
	CString		Taille	=	CalculeTexteTaille( GetTaille() ) ;
	SetAttribut( "Taille", Taille ) ;

	// Extension
	char	Ext[_MAX_EXT] ;
	_tsplitpath( data.cFileName, NULL, NULL, NULL, Ext ) ;
	SetAttribut( "Extension", Ext ) ;

	// Type de fichier

	SHFILEINFO	FileInfo ;
	memset( &FileInfo, 0, sizeof( FileInfo )) ;

	GetSystemInfo( Ext ) ;

	if ( GetTaille() > 0 )
		{
		GetFileCheckSum( path, GetTaille(), dlg) ;

		ExtraitInfosFichier( path, Ext ) ;
		}

	return TRUE ;
}

void CFichier::Remplit(CTreeCtrl &Tree, HTREEITEM hParent)
{
	HTREEITEM hTreeItem	=	Tree.InsertItem( Nom(),
											 IndiceImage, IndiceImage,
											 hParent ) ;
	SetHItem( hTreeItem ) ;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
CString CFichier::CalculeTexteTaille(__int64 TailleFichier)
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

void CFichier::Sauve(CMediaFile &file)
{
	// Devra etre lu par l'objet contenant
	file.Write( &FICHIER, sizeof( long )) ;

	file.WriteFormat( "Fichier" ) ;
	CElement::Sauve( file ) ;

}


BOOL	CFichier::Charge( CMediaFile & file )
	{
	if ( ! file.VerifieFormat( "Fichier" ))
		return FALSE ;

	return CElement::Charge( file ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// Extrait les informations possible du fichier, dependant du type de fichier
///////////////////////////////////////////////////////////////////////////////
void CFichier::ExtraitInfosFichier(const CString &File, const CString &Ext)
{
	if ( Ext.CompareNoCase( ".MP3" ) == 0 )
		ExtraitInfosMP3( File ) ;
}

void CFichier::ExtraitInfosMP3(const CString &File)
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
void CFichier::GetFileCheckSum(const CString &NomFichier, __int64 Taille, CScanningDlg & dlg )
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

	while ( Grandeur > (__int64)1000 )
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
void CFichier::GetSystemInfo(const CString &Ext)
{
	HKEY	hKey ;
	if ( RegOpenKey( HKEY_CLASSES_ROOT, "Ext", &Key ) != ERROR_SUCESS )
		return ;

	char	Buffer[1024] ;
	DWORD	Taille	=	sizeof( Buffer ) ;
	DWORD	Type	=	REG_SZ ;

	if ( RegQueryValueEx( hKey, NULL, 0, &Type, (LPBYTE)Buffer, &Taille ) == ERROR_SUCCESS )
		{
		}
	RegCloseKey( hKey ) ;
}
