// Element.cpp: implementation of the CElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoftCollection.h"
#include "Element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStringArray	CElement::_TousLesAttributs ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CElement::CElement()
{
}

CElement::~CElement()
{
}

void CElement::Remplit(CTreeCtrl &Tree, HTREEITEM hParent)
{
	HTREEITEM hTreeItem	=	Tree.InsertItem( Nom(),hParent ) ;
	SetHItem( hTreeItem ) ;
}

CElement * CElement::Trouve(HTREEITEM hItem)
{
	if ( hItem == _hTreeItem )
		return this ;

	return NULL ;
}

void CElement::Sauve(CMediaFile &file)
{
	file.WriteFormat( "Element" ) ;

	long	Nb	=	_Noms.GetSize() ;
	file.Write( &Nb, sizeof( Nb )) ;

	for ( int i = 0; i < Nb; i++)
		{
		file.WriteString( _Noms[i] ) ;
		file.WriteString( _Valeurs[i] ) ;
		}

	// Find Data
	file.Write( &_Data, sizeof( _Data )) ;
}

BOOL CElement::Charge( CMediaFile & file )
	{
	if ( ! file.VerifieFormat( "Element" ))
		return FALSE ;

	long Nb ;
	file.Read( &Nb, sizeof( Nb )) ;

	_Noms.RemoveAll() ;
	_Valeurs.RemoveAll() ;

	_Noms.SetSize( Nb ) ;
	_Valeurs.SetSize( Nb ) ;

	for ( int i = 0; i < Nb; i ++ )
		{
		CString Nom	=	file.ReadString() ;
		_Noms.SetAt( i, Nom ) ;
		_Valeurs.SetAt( i, file.ReadString()) ;

		ReferenceAttribut( Nom ) ;
		}


	file.Read( &_Data, sizeof( _Data )) ;

	return TRUE ;
	}


BOOL CElement::Scanne( const CString & Path, const WIN32_FIND_DATA & data, CScanningDlg & )
	{
	SetAttribut( PATH, Path ) ;
	_Data	=	data ;

	return TRUE ;
	}

void CElement::SetAttribut(const CString &Nom, const CString &Valeur)
{
	ASSERT( _Noms.GetSize() == _Valeurs.GetSize()) ;

	const int Nb	=	_Noms.GetSize() ;
	for ( int i = 0; i < Nb; i ++)
		if ( Nom.CompareNoCase( _Noms[i] ) == 0 )
			{
			_Valeurs[i] = Valeur ;
			return ;
			}

	try
		{
		_Noms.SetAtGrow( Nb, Nom ) ;
		_Valeurs.SetAtGrow( Nb, Valeur ) ;

		ReferenceAttribut( Nom ) ;
		}
	catch( CMemoryException e)
		{
		MessageBox( 0, "Pas assez de memoire pour ajouter un attribut", "Erreur", MB_OK | MB_ICONSTOP ) ;
		}
}

CString CElement::GetAttribut(const CString &Nom) const
{
	ASSERT( _Noms.GetSize() == _Valeurs.GetSize()) ;

	const int Nb	=	_Noms.GetSize() ;

	for ( int i = 0; i < Nb; i++)
		if ( Nom.CompareNoCase( _Noms[i] ) == 0 )
			return _Valeurs[i] ;

	return "" ;
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

void CElement::Recherche(const CString &Texte, const CString &Attribut, TABLEAU_ELEMENTS & resultat)
{
	CString	TEXTE( Texte ) ;
	TEXTE.MakeUpper() ;

	if ( Attribut.IsEmpty())
		{
		const int	Nb	=	_Noms.GetSize() ;
		// Recherche dans tous les attributs
		for ( int i  = 0; i < Nb; i++)
			{
			if ( ConvientPourRecherche( TEXTE, _Valeurs[i] ))
				{
				resultat.Add( this ) ;
				return ;
				}
			}

		}
	else
		{
		// Recherche dans un attribut particulier
		CString Valeur	=	GetAttribut( Attribut ) ;
		
		if ( ConvientPourRecherche( TEXTE, Valeur ))
			resultat.Add( this ) ;
		}
}

BOOL CElement::ConvientPourRecherche(const CString &TEXTE, const CString &Valeur)
{
	// TEXTE est deja en majuscule

	CString VALEUR(Valeur) ;
	VALEUR.MakeUpper() ;

	if ( VALEUR.Find( TEXTE ) != -1 )
		return TRUE ;

	return FALSE ;
}

void CElement::AjouteDansListCtrl(CListCtrl &list, int Indice)
{
	static char Buffer[1024] ;

	int NoColonne	=	0 ;
	LVCOLUMN		Colonne ;

	Colonne.mask	=	LVCF_TEXT | LVCF_SUBITEM ;
	Colonne.pszText	=	Buffer ;
	Colonne.cchTextMax	=	sizeof( Buffer ) ;

	while( list.GetColumn( NoColonne, &Colonne ))
		{
		CString NomColonne	=	Colonne.pszText ;

		CString Valeur		=	GetAttribut( NomColonne ) ;
		list.SetItem( Indice, Colonne.iSubItem, LVIF_TEXT, Valeur, 0, 0, 0, 0 ) ;

		NoColonne ++ ;
		}
}

void CElement::SetAttribut(const CString &Nom, int Valeur)
{
	CString Nombre ;
	Nombre.Format( "%d", Valeur ) ;
	SetAttribut( Nom, Nombre ) ;
}
