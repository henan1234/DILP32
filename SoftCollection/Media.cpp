// Media.cpp: implementation of the CMedia class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoftCollection.h"
#include "Media.h"
#include "FileServices.h"
#include "element.h"
#include "repertoire.h"
#include "fichier.h"
#include "mediafile.h"
#include "scanningdlg1.h"

static const CString COPYRIGHT	=	"SoftCollection\r\n(c) Lucien Pilloni 2000" ;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMedia::CMedia()
{
	_Vide	= FALSE ;
}

CMedia::~CMedia()
{
	const int Nb	=	_TableauElements.GetSize() ;
	for ( int i = 0; i < Nb; i++)
		delete _TableauElements[i] ;

	_TableauElements.RemoveAll() ;
}

//////////////////////////////////////////////////////////////////////
// Scanne l'arborescence d'un media
//////////////////////////////////////////////////////////////////////
BOOL CMedia::Scan(const CString &Media)
{
	_MediaName		=	CFileServices::ExtractFileName( Media ) ;
	if ( _MediaName.IsEmpty())
		_MediaName	=	Media ;

	_MediaPath		=	Media ;

	return ScanneFirstDirectory( _MediaPath ) ;
}

BOOL CMedia::AjouteElement(CElement *pElement)
{
	if ( _Vide )
		Charge( _NomFichier ) ;

	try
		{
		_TableauElements.Add( pElement ) ;
		}
	catch( CMemoryException e )
		{
		AfxMessageBox( "Pas assez de memoire", MB_ICONSTOP | MB_OK ) ;
		return FALSE ;
		}

	return TRUE ;
}

void CMedia::Remplit(CTreeCtrl &Tree)
{
	if ( _Vide )
		Charge( _NomFichier ) ;
	
	const int NbElements	=	_TableauElements.GetSize() ;

	for ( int i = 0; i < NbElements; i++)
		{
		CElement * pElement =	_TableauElements[i] ;
		pElement->Remplit( Tree, TVI_ROOT ) ;
		}
}

CElement * CMedia::TrouveElement(HTREEITEM hItem)
{
	if ( _Vide )
		Charge( _NomFichier ) ;

	const int NbElements	=	_TableauElements.GetSize() ;
	for ( int i = 0; i < NbElements; i++)
		{
		CElement * pElement =	_TableauElements[i] ;
		CElement * pTrouve	=	pElement->Trouve( hItem ) ;

		if ( pTrouve )
			return pTrouve ;
		}
	return NULL ;
}

void CMedia::Sauve(const CString &NomFichier)
{
	_NomFichier	=	NomFichier ;
	CMediaFile	file ;
	if ( ! file.Open( NomFichier, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ))
		{
		MessageBox( 0, "Impossible de sauver le media", "Erreur", MB_ICONHAND | MB_OK ) ;
		return ;
		}

	// Copyright
	file.WriteString( COPYRIGHT ) ;

	// MediaName
	file.WriteString( _MediaName ) ;
	
	// MediaPath
	file.WriteString( _MediaPath ) ;
	
	// NbElements
	long nb = _TableauElements.GetSize() ;
	file.Write( &nb, sizeof( nb )) ;

	for ( int i = 0; i < nb; i++)
		_TableauElements[i]->Sauve( file ) ;

	file.Close() ;
}

///////////////////////////////////////////////////////////////////////////////
// Recharge la structure d'un media a partir d'un fichier
///////////////////////////////////////////////////////////////////////////////
BOOL CMedia::Charge(const CString &NomFichier)
{
	_NomFichier	=	NomFichier ;
	CMediaFile	file ;
	if ( ! file.Open( NomFichier, CFile::modeRead | CFile::typeBinary ))
		{
		MessageBox( 0, "Impossible de charger le media", "Erreur", MB_ICONHAND | MB_OK ) ;
		return FALSE ;
		}

	CString Copyright	=	file.ReadString() ;
	if ( Copyright != COPYRIGHT )
		{
		MessageBox( 0, "Format de fichier incorrect", "Erreur", MB_ICONHAND | MB_OK ) ;
		}

	// MediaName
	_MediaName = file.ReadString() ;
	
	// MediaPath
	_MediaPath	=	file.ReadString() ;

	// NbElements
	long	nb ;
	file.Read( &nb, sizeof( nb )) ;
	_TableauElements.RemoveAll() ;

	_TableauElements.SetSize( nb ) ;

	

	for ( int i = 0; i < nb; i++)
		{
		long	Type ;
		file.Read( &Type, sizeof( Type )) ;
		switch( Type )
			{
			case FICHIER :
				{
				CFichier * pFichier	=	new CFichier ;
				if ( ! pFichier )
					return FALSE ;
				pFichier->Charge( file ) ;
				_TableauElements.SetAt( i, pFichier ) ;
				}
				break ;

			case REPERTOIRE :
				{
				CRepertoire * pRepertoire	=	new CRepertoire ;
				if ( ! pRepertoire )
					return FALSE ;

				pRepertoire->Charge( file ) ;
				_TableauElements.SetAt( i, pRepertoire ) ;
				}
				break ;

			default :
				MessageBox( 0, "Format de fichier incorrect", "Erreur", MB_OK | MB_ICONSTOP ) ;
				_TableauElements.RemoveAll() ;
				return FALSE ;
			}
		}

	file.Close() ;
	_Vide	=	FALSE ;
	return TRUE ;
}


void CMedia::Vide()
{
	const int NbElements	=	_TableauElements.GetSize() ;
	for ( int i = 0; i < NbElements; i++)
		delete _TableauElements[i] ;

	_TableauElements.RemoveAll() ;
	_Vide	=	TRUE ;
}



BOOL CMedia::ScanneFirstDirectory(const CString &Path)
{
	CScanningDlg	dlg ;
	dlg.Create( IDD_SCANNING, AfxGetMainWnd()) ;
	dlg.ShowWindow( SW_SHOW ) ;

	CString	Mask	=	CFileServices::Concat( Path, "*.*" ) ;

	// Compter les objets de 1er niveau
	WIN32_FIND_DATA	data ;
	HANDLE	hFind	=	FindFirstFile( Mask, &data ) ;
	BOOL	Continue	=	TRUE ;
	int		Nb		=	0 ;
	while( Continue )
		{
		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			Nb ++ ;
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}
	FindClose( hFind ) ;

	// Parcourir
	dlg.m_Progress.SetRange( 0, Nb-1 ) ;
	hFind	=	FindFirstFile( Mask, &data ) ;
	Continue	=	TRUE ;
	
	while( Continue )
		{
		if ( dlg.Abort())
			{
			FindClose( hFind ) ;
			dlg.DestroyWindow() ;
			return FALSE ;
			}

		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			CString CompletePath	=	CFileServices::Concat( Path, data.cFileName ) ;
			dlg.m_Fichier.SetWindowText( data.cFileName ) ;

			CElement * pElement = NULL ;
			if( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				pElement	=	new CRepertoire ;
			else
				pElement	=	new CFichier ;

			if ( pElement == NULL )
				{
				FindClose( hFind ) ;
				return FALSE ;
				}

			
			if ( ! pElement->Scanne( CompletePath, data, dlg ))
				{
				FindClose( hFind ) ;
				dlg.DestroyWindow() ;
				return FALSE ;
				}
			if ( ! AjouteElement( pElement ) )
				{
				FindClose( hFind ) ;
				return FALSE ;
				}
			dlg.m_Progress.SetPos( _TableauElements.GetSize() ) ;
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}


	FindClose( hFind ) ;

	dlg.DestroyWindow();
	_Vide	=	FALSE ;
	return TRUE ;
	
}

BOOL CMedia::ChargeInfos(const CString &NomFichier)
{
	_NomFichier	=	NomFichier ;
	CMediaFile	file ;
	if ( ! file.Open( NomFichier, CFile::modeRead | CFile::typeBinary ))
		{
		MessageBox( 0, "Impossible de charger le media", "Erreur", MB_ICONHAND | MB_OK ) ;
		return FALSE ;
		}

	CString Copyright	=	file.ReadString() ;
	if ( Copyright != COPYRIGHT )
		{
		MessageBox( 0, "Format de fichier incorrect", "Erreur", MB_ICONHAND | MB_OK ) ;
		}

	// MediaName
	_MediaName = file.ReadString() ;
	
	// MediaPath
	_MediaPath	=	file.ReadString() ;
	file.Close() ;

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// Fait une recherche, met tous les elements qui conviennent dans le tableau
// ENTREE: Texte a chercher
//		   Nom de l'attribut sur lequel joue la recherche ou vide pour tous
//			les attributs
///////////////////////////////////////////////////////////////////////////////
void CMedia::Recherche(const CString &Texte, const CString &Attribut, CArray<CElement*, CElement*> & resultat)
{
	if ( _Vide )
		Charge( _NomFichier ) ;

	for ( int i = 0; i < _TableauElements.GetSize(); i++ )
		_TableauElements[i]->Recherche( Texte, Attribut, resultat ) ;
}
