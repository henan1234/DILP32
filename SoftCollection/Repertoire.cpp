// Repertoire.cpp: implementation of the CRepertoire class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoftCollection.h"
#include "Repertoire.h"
#include "fileservices.h"
#include "fichier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int	CRepertoire::IndiceImage = 0 ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepertoire::CRepertoire()
{
}

CRepertoire::~CRepertoire()
{
	const int NbElements	=	_TableauElements.GetSize() ;

	for ( int i = 0; i < NbElements; i++)
		delete _TableauElements[i] ;

	_TableauElements.RemoveAll() ;
}

BOOL CRepertoire::Scanne(const CString &path, const WIN32_FIND_DATA & thisdata, CScanningDlg & dlg)
{
	CElement::Scanne( path, thisdata, dlg ) ;
	Nom( thisdata.cFileName ) ;
	Path( path ) ;
	
	CString	Mask	=	CFileServices::Concat( path, "*.*" ) ;

	WIN32_FIND_DATA	data ;
	HANDLE	hFind	=	FindFirstFile( Mask, &data ) ;
	BOOL	Continue	=	TRUE ;
	while( Continue )
		{
		if ( dlg.Abort())
			{
			const int NbElements	=	_TableauElements.GetSize() ;

			for ( int i = 0; i < NbElements; i++)
				delete _TableauElements[i] ;

			_TableauElements.RemoveAll() ;
			return FALSE ;
			}

		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			CString CompletePath	=	CFileServices::Concat( path, data.cFileName ) ;
			dlg.m_Fichier.SetWindowText( CompletePath ) ;

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
				return FALSE ;
				}

			if ( ! AjouteElement( pElement ) )
				{
				FindClose( hFind ) ;
				return FALSE ;
				}
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}

	SetAttribut( "Nb de fichiers", _TableauElements.GetSize()) ;
	FindClose( hFind ) ;

	return TRUE ;
}

BOOL CRepertoire::AjouteElement(CElement *pElement)
{
	try
		{
		_TableauElements.Add( pElement ) ;
		}
	catch( CMemoryException e )
		{
		MessageBox( 0, "Pas assez de memoire", "Erreur", MB_OK | MB_ICONHAND ) ;
		return FALSE ;
		}
	return TRUE ;
}

void CRepertoire::Remplit(CTreeCtrl &Tree, HTREEITEM hParent)
{
	// Ajoute le repertoire
	HTREEITEM hRep	= Tree.InsertItem( Nom(), IndiceImage, IndiceImage, hParent ) ;
	SetHItem( hRep ) ;

	const int NbElements	=	_TableauElements.GetSize() ;
	for ( int i = 0; i < NbElements; i++)
		{
		CElement * pElement =	_TableauElements[i] ;
		pElement->Remplit( Tree, hRep ) ;
		}
}


CElement * CRepertoire::Trouve( HTREEITEM hItem )
	{
	CElement * pTrouve	=	CElement::Trouve( hItem ) ;
	if ( pTrouve )
		return pTrouve ;

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

void CRepertoire::Sauve(CMediaFile &file)
{
	file.Write( &REPERTOIRE, sizeof( long )) ;
	
	CElement::Sauve( file ) ;
	file.WriteFormat( "Repertoire" ) ;

	const int NbElements	=	_TableauElements.GetSize() ;
	long nb	 = NbElements ;
	file.Write( &nb, sizeof( nb )) ;

	for ( int i = 0; i < NbElements; i++ )
		{
		_TableauElements[i]->Sauve( file ) ;
		}
}

BOOL CRepertoire::Charge( CMediaFile & file )
	{
	CElement::Charge( file ) ;
	if ( ! file.VerifieFormat( "Repertoire" ))
		return FALSE ;

	long	nb ;
	file.Read( &nb, sizeof( nb )) ;

	_TableauElements.SetSize( nb ) ;

	for ( int i = 0; i < nb; i++)
		{
		long	Type ;
		file.Read( &Type, sizeof( Type )) ;

		CElement * pElement	=	NULL ;
		if ( Type == FICHIER )
			pElement	=	new CFichier ;
		else
		if ( Type == REPERTOIRE )
			pElement	=	new CRepertoire ;
		else
			{
			MessageBox( 0, "Format de fichier incorrect", "Erreur", MB_OK | MB_ICONSTOP ) ;
			const int NbElements	=	_TableauElements.GetSize() ;

			for ( int i = 0; i < NbElements; i++)
			delete _TableauElements[i] ;

			_TableauElements.RemoveAll() ;
			return FALSE ;
			}

		if (! pElement )
			{
			MessageBox( 0, "Pas assez de memoire", "Erreur", MB_OK | MB_ICONSTOP ) ;
			const int NbElements	=	_TableauElements.GetSize() ;

			for ( int i = 0; i < NbElements; i++)
				delete _TableauElements[i] ;

			_TableauElements.RemoveAll() ;
			return FALSE ;
			}

		if ( ! pElement->Charge( file ))
			{
			const int NbElements	=	_TableauElements.GetSize() ;

			for ( int i = 0; i < NbElements; i++)
				delete _TableauElements[i] ;

			_TableauElements.RemoveAll() ;
			return FALSE ;
			}

		_TableauElements.SetAt( i,  pElement ) ;
		}

	return TRUE ;
	}


void CRepertoire::Recherche( const CString & Texte, const CString & Attribut, TABLEAU_ELEMENTS & resultat )
	{
	CElement::Recherche( Texte, Attribut, resultat ) ;

	for ( int i = 0; i < _TableauElements.GetSize(); i++ )
		_TableauElements[i]->Recherche( Texte, Attribut, resultat ) ;
	}
