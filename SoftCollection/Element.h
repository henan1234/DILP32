// Element.h: interface for the CElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENT_H__7FEE99DB_EC37_462A_AFB8_2667A11FC46B__INCLUDED_)
#define AFX_ELEMENT_H__7FEE99DB_EC37_462A_AFB8_2667A11FC46B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mediafile.h"
#include "scanningdlg1.h"
#include <afxtempl.h>

// Classes derivees ( pour la sauvegarde )
const long FICHIER	=	0 ;
const long REPERTOIRE = 1 ;

const char 	NOM	[]			=	"Nom" ;
const char	DESCRIPTION[]	=	"Description" ;
const char	PATH[]			=	"Chemin" ;

class CElement  
{
public:
	void SetAttribut( const CString & Nom, int Valeur );
	virtual void AjouteDansListCtrl( CListCtrl & list, int Indice );
	typedef CArray<CElement*, CElement*> TABLEAU_ELEMENTS ;
	virtual void Recherche( const CString & Texte, const CString & Attribut, TABLEAU_ELEMENTS & resultat );

	// Attributs
	CString GetAttribut( const CString & Nom ) const ;
	void SetAttribut( const CString & Nom, const CString & Valeur );
	int	GetNbAttributs() const { return _Noms.GetSize() ; }

	CString GetNom( int i ) const { return _Noms[i] ; }
	CString GetAttribut( int i ) const { return _Valeurs[i] ; }
	
	// Sauve/Charge
	virtual void Sauve( CMediaFile & file );
	virtual BOOL Charge( CMediaFile & file ) ;

	virtual CElement * Trouve( HTREEITEM hItem );
	virtual void Remplit( CTreeCtrl & Tree, HTREEITEM hParent );

	CElement();
	virtual ~CElement();

	virtual BOOL	Scanne( const CString & Path, const WIN32_FIND_DATA & data, CScanningDlg & dlg ) ;

	const CString Nom() const { return GetAttribut( NOM ) ; } ;
	void Nom( const CString & n ) { SetAttribut( NOM, n ) ; }

	const CString Description () const { return GetAttribut( DESCRIPTION) ; }
	void Description( const CString & d ) { SetAttribut( DESCRIPTION, d  ) ; }

	const CString Path() const { return GetAttribut( PATH ) ; } ;
	void Path( const CString & p ) { SetAttribut( PATH, p ) ; }

	HTREEITEM	GetHItem() { return _hTreeItem ; }
	void		SetHItem( HTREEITEM h ) { _hTreeItem = h ; }

	__int64		GetTaille() { return ((__int64)_Data.nFileSizeHigh << (__int64)32)  + (__int64)_Data.nFileSizeLow ; } 

	static	CStringArray & GetTousAttributs() { return _TousLesAttributs ; }

private:
	virtual BOOL ConvientPourRecherche( const CString & Texte, const CString & Valeur );
	static CStringArray	_TousLesAttributs ;
	static void	ReferenceAttribut( const CString & Nom ) ;

	CStringArray _Noms ;
	CStringArray	_Valeurs ;

	HTREEITEM		_hTreeItem ;
	WIN32_FIND_DATA	_Data ;
};


#endif // !defined(AFX_ELEMENT_H__7FEE99DB_EC37_462A_AFB8_2667A11FC46B__INCLUDED_)
