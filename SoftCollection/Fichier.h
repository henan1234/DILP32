// Fichier.h: interface for the CFichier class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHIER_H__228E2D47_69E2_48E4_A9B2_1619C92192D5__INCLUDED_)
#define AFX_FICHIER_H__228E2D47_69E2_48E4_A9B2_1619C92192D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"

class CFichier : public CElement  
{
public:
	virtual void Sauve( CMediaFile & file );
	virtual BOOL Charge( CMediaFile & file );

	virtual BOOL Scanne( const CString & Path, const WIN32_FIND_DATA & data, CScanningDlg & );
	CFichier();
	virtual ~CFichier();
	void Remplit(CTreeCtrl &Tree, HTREEITEM hParent) ;

	static int	IndiceImage ;
private:
	void GetSystemInfo( const CString & Path );
	void ExtraitInfosMP3( const CString & File );
	void ExtraitInfosFichier( const CString & File, const CString & Ext );
	CString CalculeTexteTaille( __int64 TailleFichier );
	void GetFileCheckSum( const CString & NomFichier, __int64 Taille, CScanningDlg & dlg );
	
};

#endif // !defined(AFX_FICHIER_H__228E2D47_69E2_48E4_A9B2_1619C92192D5__INCLUDED_)
