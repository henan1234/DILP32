// Fichier.cpp: implementation of the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "Fichier.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CFichier, CElement ) ;
#define TAILLE_BUFFER	4096

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFichier::CFichier()
{
	_CheckSumCalculee	=	FALSE ;
	_pBuffer			=	NULL ;
}

CFichier::~CFichier()
{
	delete _pBuffer ;
}



void CFichier::Scanne(const char *pPath)
{
	CElement::Scanne( pPath ) ;


	SHFILEINFO FI ;

	SHGetFileInfo( Path, 0, &FI, sizeof( FI ), SHGFI_SMALLICON | SHGFI_ICON  ) ;

}


void CFichier::RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler& Imh, BOOL NonDuppliques )
	{
	if ( ! NonDuppliques && ! ADesDuppliques())
		return ;

	const int IndiceIcone	=	Imh.GetIconIndex( Path()) ;
	
	HTREEITEM	hitem = Tree.InsertItem( Nom(), IndiceIcone, IndiceIcone, hParent, TVI_LAST ) ;
	Tree.SetItemData( hitem, (DWORD)this ) ;
	}

BOOL CFichier::Compare(CFichier * pFichier )
{
	if ( pFichier == this )
		return FALSE ;

	BOOL	Identiques	=	FALSE ;

	if ( CompareTaille( pFichier ))
		{
		if ( CompareCheckSum( pFichier ))
			{
			if ( CompareDebut( pFichier ))
				if ( CompareContenu( pFichier ))
					{
					FichiersIdentiques( pFichier ) ;
					Identiques	=	TRUE ;
					}
			}
		}

	return Identiques ;
}

///////////////////////////////////////////////////////////////////////////////
// Compare la taille de deux fichiers
// Retourne TRUE si:
//	- Les tailles sont identiques
//	OU
//	- On n'a pas a comparer, parce qu'une des tailles n'a pas ete calculee
///////////////////////////////////////////////////////////////////////////////
BOOL CFichier::CompareTaille(CFichier * pFichier )
{
	if ( ! _pBuffer )
		// La taille n'a pas ete lue
		return TRUE ;

	return ( _Taille == pFichier->_Taille ) ;
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
BOOL CFichier::CompareCheckSum(CFichier * pFichier )
{
	if (this == pFichier )
		return FALSE ;

	if ( _CheckSumCalculee )
		{
		if ( pFichier->_CheckSumCalculee )
			return ( _CheckSum == pFichier->_CheckSum ) ;
		}

	return TRUE ;
}

BOOL CFichier::CompareDebut(CFichier * pFichier )
{
	LitDebutFichier() ;
	pFichier->LitDebutFichier() ;

	if ( _pBuffer && pFichier->_pBuffer )
		return memcmp( _pBuffer, pFichier->_pBuffer, sizeof( TAILLE_BUFFER ))
				== 0 ;

	return TRUE ;
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
BOOL CFichier::CompareContenu(CFichier * pFichier )
{
	if ( this == pFichier )
		return FALSE ;

	// Ouvre les deux fichiers pour lecture
	CStdioFile File1, File2 ;

	if ( ! File1.Open( Path(), CFile::modeRead | CFile::typeBinary ))
		return FALSE ;

	if ( ! File2.Open( pFichier->Path(), CFile::modeRead | CFile::typeBinary ))
		return FALSE ;

	DWORD	CheckSum1	=	0 ;
	DWORD	CheckSum2	=	0 ;

	BOOL	Identique	=	TRUE ;
	BOOL	Continue	=	TRUE ;

	char	Buffer1[4096] ;
	char	Buffer2[4096] ;

	int	NbLus1 ;
	int	NbLus2 ;

	while ( Continue && Identique )
		{
		NbLus1	=	File1.Read( Buffer1, sizeof( Buffer1 )) ;
		NbLus2	=	File2.Read( Buffer2, sizeof( Buffer2 )) ;

		if ( NbLus1 != NbLus2 )
			Identique = FALSE ;
		else
			Identique = 0 == memcmp( Buffer1, Buffer2, NbLus1 ) ;

		CheckSum1	+=	CheckSum( Buffer1, sizeof( Buffer1 )) ;
		CheckSum2	+=	CheckSum( Buffer2, sizeof( Buffer2 )) ;


		if ( NbLus1 == 0 || NbLus2 == 0 )
			Continue = FALSE ;
		}

	if ( Identique )
		{
		_CheckSum	=	CheckSum1 ;
		_CheckSumCalculee = TRUE ;
		pFichier->_CheckSum	=	CheckSum2 ;
		pFichier->_CheckSumCalculee = TRUE ;
		}

	File1.Close() ;
	File2.Close() ;

	return Identique ;
}



void CFichier::FichiersIdentiques(CFichier * pFichier )
{
	_Identiques.Add( pFichier ) ;
	pFichier->_Identiques.Add( this ) ;
}

DWORD CFichier::CheckSum(char *pBuffer, int Taille)
{
	DWORD	dw = 0 ;
	for ( int i = 0; i < Taille; i++ )
		{
		dw	+=	(DWORD)(*pBuffer) ;

		pBuffer ++ ;
		}

	return dw ;
}

void CFichier::RemplitListe( CListCtrl & Liste )
	{
	int	nItem	=	Liste.GetItemCount() ;

	for ( int i = 0; i < _Identiques.GetSize(); i++)
		Liste.InsertItem( nItem + i, _Identiques[i]->Path() ) ;
	}

void CFichier::SetAttributs(CDC &dc)
{
	if ( _Identiques.GetSize() > 0 )
		{
		dc.SetTextColor( RGB( 255, 0, 0 )) ;
		}
	else
		CElement::SetAttributs( dc ) ;
}

BOOL CFichier::ADesDuppliques()
{
	return ( _Identiques.GetSize() > 0 ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Memorise le debut d'un fichier, permettra de comparer le contenu de deux
// fichier sans avoir a relire depuis le disque
///////////////////////////////////////////////////////////////////////////////
void CFichier::LitDebutFichier()
{
	if ( _pBuffer )
		// Deja lu
		return ;

	CStdioFile file	;
	if ( file.Open( Path(), CFile::modeRead|CFile::typeBinary ))
		{
		_pBuffer	=	new BYTE[TAILLE_BUFFER] ;
		if ( _pBuffer )
			{
			memset( _pBuffer, 0, TAILLE_BUFFER ) ;
			file.Read( _pBuffer, TAILLE_BUFFER ) ;
			file.Close() ;
			}
		}
}

void CFichier::FiniScan()
{
	delete _pBuffer ;
	_pBuffer	=	NULL ;
}

void CFichier::Vide()
{
	delete _pBuffer ;
	_pBuffer	=	NULL ;
}
