// FichiersDoublesDoc.h : interface of the CFichiersDoublesDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FICHIERSDOUBLESDOC_H__711DA481_A2CF_4E34_818C_5D039A68FC31__INCLUDED_)
#define AFX_FICHIERSDOUBLESDOC_H__711DA481_A2CF_4E34_818C_5D039A68FC31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "racine.h"
#include "repertoire.h"
#include "fichier.h"
#include "imageListHandler.h"

#define HINT_VIDE	1
#define HINT_NEW	2

class CFichiersDoublesDoc : public CDocument
{
protected: // create from serialization only
	CFichiersDoublesDoc();
	DECLARE_DYNCREATE(CFichiersDoublesDoc)

	CImageList	&	GetImageList() { return _ImageListHandler.GetImageList() ; }

	CElement *	GetSelectionne() { return pElementSelectionne ; }
	void		Selectionne( CElement * pElement ) { pElementSelectionne = pElement ; UpdateAllViews(0) ; }

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFichiersDoublesDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SupprimeDuppliques( CFichier * pElement );
	void RemplitArbre( CTreeCtrl & Tree, BOOL AfficherNonDuppliques );
	virtual ~CFichiersDoublesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFichiersDoublesDoc)
	afx_msg void OnUpdateEditionSupprimetouslesduppliqus(CCmdUI* pCmdUI);
	afx_msg void OnEditionSupprimetouslesduppliqus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL DeleteListOfFiles( CArray<CFichier*, CFichier*> & Fichiers );
	BOOL DeleteFiles( CString & Files );
	void VideRepertoire();
	void ScanneDuppliques();
	CRacine _Repertoire ;
	CImageListHandler _ImageListHandler ;

	CElement *	pElementSelectionne ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FICHIERSDOUBLESDOC_H__711DA481_A2CF_4E34_818C_5D039A68FC31__INCLUDED_)
