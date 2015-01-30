// Racine.h: interface for the CRacine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RACINE_H__8454DC58_0AB3_4D9D_85A8_07680364FDC6__INCLUDED_)
#define AFX_RACINE_H__8454DC58_0AB3_4D9D_85A8_07680364FDC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Repertoire.h"

class CRacine : public CRepertoire  
{
public:
	virtual void RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler & Imh, BOOL NonDuppliques );
	CRacine();
	virtual ~CRacine();

};

#endif // !defined(AFX_RACINE_H__8454DC58_0AB3_4D9D_85A8_07680364FDC6__INCLUDED_)
