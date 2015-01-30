// Repertoire.h: interface for the CRepertoire class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPERTOIRE_H__DE0B87F4_C0E4_4264_959E_232E6C0066A3__INCLUDED_)
#define AFX_REPERTOIRE_H__DE0B87F4_C0E4_4264_959E_232E6C0066A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"
#include "fichier.h"
#include <afxtempl.h>
class CRepertoire : public CElement  
{
DECLARE_DYNAMIC( CRepertoire ) ;

public:
	BOOL Supprime( CElement * pElement );
	virtual void FiniScan();
	virtual BOOL ADesDuppliques();
	virtual void Vide();
	virtual void RemplitListe( CListCtrl & Liste );

	CRepertoire();
	virtual ~CRepertoire();

	virtual void Scanne( const char * Path ) ;
	virtual void RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler &, BOOL NonDuppliques  );


	void	ObtientTousFichier( CArray<CFichier*, CFichier*> & Tableau ) ;
protected:

	CArray	<CElement*, CElement*>	_Elements ;
};

#endif // !defined(AFX_REPERTOIRE_H__DE0B87F4_C0E4_4264_959E_232E6C0066A3__INCLUDED_)
