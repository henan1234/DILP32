// Repertoire.h: interface for the CRepertoire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPERTOIRE_H__3549B34B_52C7_47B2_B28D_E58C9531D2F5__INCLUDED_)
#define AFX_REPERTOIRE_H__3549B34B_52C7_47B2_B28D_E58C9531D2F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "Element.h"

class CRepertoire : public CElement  
{
public:
	virtual void Recherche( const CString & Texte, const CString & Attribut, TABLEAU_ELEMENTS & resultat );
	virtual void Sauve( CMediaFile & file );
	virtual BOOL Charge( CMediaFile & file ) ;

	virtual void Remplit( CTreeCtrl & Tree, HTREEITEM hParent );

	virtual BOOL Scanne( const CString & Path, const WIN32_FIND_DATA & data, CScanningDlg & dlg );
	CRepertoire();
	virtual ~CRepertoire();

	virtual CElement * Trouve( HTREEITEM hItem );
	static int	IndiceImage ;

private:
	BOOL AjouteElement(CElement *pElement) ;

	CArray<CElement *, CElement *> _TableauElements ;
};

#endif // !defined(AFX_REPERTOIRE_H__3549B34B_52C7_47B2_B28D_E58C9531D2F5__INCLUDED_)
