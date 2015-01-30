// Repertoire.cpp: implementation of the CRepertoire class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "Repertoire.h"
#include "fileservices.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CRepertoire, CElement ) ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRepertoire::CRepertoire()
{

}

CRepertoire::~CRepertoire()
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		delete _Elements[i] ;

	_Elements.RemoveAll() ;
}

//////////////////////////////////////////////////////////////////////
// Parcours un repertoire et memorise son contenu//
//////////////////////////////////////////////////////////////////////
void CRepertoire::Scanne(const char *Path)
{
	CElement::Scanne( Path ) ;
	WIN32_FIND_DATA		FindData ;
	HANDLE hFind		=	FindFirstFile( CFileServices::Concat( Path, "*.*" ), & FindData ) ;

	BOOL			Continue=	hFind != INVALID_HANDLE_VALUE ;

	while ( Continue )
		{
		// Ignore . and ..
		if ( _tcscmp( FindData.cFileName, TEXT(".") ) && _tcscmp( FindData.cFileName, TEXT("..") ))
			{
			// Reconstruct the complete file path
			const CString	CompleteSource	=	CFileServices::Concat(	Path, FindData.cFileName ) ;
			CElement * pElement ;

			// Is the entry a file or a directory ?
			if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
				pElement	=	new CRepertoire() ;
				
			else
				pElement	=	new CFichier() ;

			pElement->Scanne( CompleteSource ) ;
			_Elements.Add( pElement ) ;
			}

		Continue	=	FindNextFile( hFind, &FindData ) ;
		}

		FindClose(&FindData ) ;

}

void CRepertoire::RemplitListe( CListCtrl & Liste )
	{
	int nItem	=	Liste.GetItemCount() ;
	Liste.InsertItem( nItem, Nom()) ;
	}

void CRepertoire::RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler & Imh, BOOL NonDuppliques )
	{
	if ( ! NonDuppliques && ! ADesDuppliques())
		return ;


	const int IndiceIcone	=	Imh.GetIconIndex( Path()) ;
	HTREEITEM	hRep =	Tree.InsertItem( Nom(), IndiceIcone, IndiceIcone, hParent, TVI_LAST ) ;
	Tree.SetItemData( hRep, (DWORD)this ) ;
	
	for ( int i = 0; i < _Elements.GetSize(); i++)
		{
		_Elements[i]->RemplitArbre( Tree, hRep, Imh, NonDuppliques ) ;
		}

	Tree.Expand( hRep, TVE_EXPAND ) ;
	}


void CRepertoire::ObtientTousFichier( CArray<CFichier*, CFichier*> & Tableau )
	{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		{
		CElement * pElement	=	_Elements[i] ;

		if ( pElement->IsKindOf( RUNTIME_CLASS( CRepertoire )))
			{
			CRepertoire* pRepertoire	=	(CRepertoire*)pElement ;
			pRepertoire->ObtientTousFichier( Tableau ) ;
			}
		else
		if ( pElement->IsKindOf( RUNTIME_CLASS( CFichier )))
			{
			CFichier * pFichier	=	(CFichier*)pElement ;
			Tableau.Add( pFichier ) ;
			}
		}
	}

void CRepertoire::Vide()
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		delete _Elements[i] ;

	_Elements.RemoveAll() ;
}

BOOL CRepertoire::ADesDuppliques()
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		if ( _Elements[i]->ADesDuppliques())
			return TRUE ;

	return FALSE ;
}


void CRepertoire::FiniScan()
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		_Elements[i]->FiniScan() ;
}

///////////////////////////////////////////////////////////////////////////////
// Supprime un objet CElement dans l'arbre
///////////////////////////////////////////////////////////////////////////////
BOOL CRepertoire::Supprime(CElement *pElement)
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		{
		CElement * pCourant	=	_Elements[i] ;

		if ( pElement == pCourant )
			{
			delete pElement ;
			_Elements.RemoveAt(i);
			}
		else
			{
			if ( pCourant->IsKindOf( RUNTIME_CLASS( CRepertoire )))
				{
				CRepertoire * pRep = (CRepertoire*)pCourant ;
				if ( pRep->Supprime( pElement ))
					return FALSE ;
				}
			}
		}

	return FALSE ;
}
