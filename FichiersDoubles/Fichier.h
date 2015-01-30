// Fichier.h: interface for the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHIER_H__39C37B97_7F32_466D_A428_1C0281046F78__INCLUDED_)
#define AFX_FICHIER_H__39C37B97_7F32_466D_A428_1C0281046F78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>

#include "Element.h"


class CFichier : public CElement  
{
DECLARE_DYNAMIC( CFichier ) ;
public:
	virtual void Vide();
	virtual void FiniScan();
	virtual BOOL ADesDuppliques();
	virtual void SetAttributs( CDC & dc );
	virtual void RemplitListe( CListCtrl & Liste );

	BOOL Compare( CFichier * );
	void Scanne( const char * pPath );
	CFichier();
	virtual ~CFichier();
	virtual void RemplitArbre( CTreeCtrl & Tree, HTREEITEM hParent, CImageListHandler &, BOOL NonDuppliques );

	CArray<CFichier*, CFichier*> & GetDuppliques() { return _Identiques ; }
private:
	void LitDebutFichier();
	static DWORD CheckSum( char * pBuffer, int Taille );
	void FichiersIdentiques( CFichier * );
	BOOL CompareDebut( CFichier * );
	BOOL _TailleCalculee;
	BOOL CompareContenu( CFichier * );
	BOOL CompareCheckSum( CFichier * );
	BOOL CompareTaille( CFichier * );
	DWORD	_Taille ;
	DWORD	_CheckSum ;
	BOOL	_CheckSumCalculee ;

	BYTE*	_pBuffer ;
	
	CArray<CFichier*, CFichier*> _Identiques ;
};

#endif // !defined(AFX_FICHIER_H__39C37B97_7F32_466D_A428_1C0281046F78__INCLUDED_)
