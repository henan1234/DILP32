// Element.h: interface for the CElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENT_H__24A2ED18_E69A_435B_8CE6_AE00583E33F1__INCLUDED_)
#define AFX_ELEMENT_H__24A2ED18_E69A_435B_8CE6_AE00583E33F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "imageListHandler.h"

class CElement  : public CObject
{
	DECLARE_DYNAMIC(CElement) ;

public:
	virtual void Vide();
	virtual void FiniScan();
	virtual void Ouvre( CWnd * pParent );
	virtual void  AfficheProprietes( CWnd * );
	virtual BOOL ADesDuppliques() = 0 ;
	virtual void SetAttributs( CDC & dc );
	virtual void RemplitListe( CListCtrl & Liste );
	virtual void RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler &, BOOL NonDuppliques ) = 0 ;
	virtual void Scanne( const char * pChemin );
	CElement();
	virtual ~CElement();

	const CString & Nom() const { return _Nom ; }
	const CString & Path() const { return _Path ; }

private:
	CString _Nom;
	CString _Path;
};

#endif // !defined(AFX_ELEMENT_H__24A2ED18_E69A_435B_8CE6_AE00583E33F1__INCLUDED_)
