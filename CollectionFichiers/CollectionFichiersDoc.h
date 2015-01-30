// CollectionFichiersDoc.h : interface of the CCollectionFichiersDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLECTIONFICHIERSDOC_H__35F8AB22_063E_477D_B4D9_65DFBFA7EB85__INCLUDED_)
#define AFX_COLLECTIONFICHIERSDOC_H__35F8AB22_063E_477D_B4D9_65DFBFA7EB85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "element.h"

class CCollectionFichiersDoc : public CDocument
{
public:
	//void SetAttributRegroupe( const CString & Att );
	void SetFiltre( const CString & Att, const CString & Texte ) { _AttributFiltre = Att; _TexteFiltre = Texte ; }
	void GetFiltre( CString & Att, CString & Texte ) { Att = _AttributFiltre; Texte = _TexteFiltre ; }
	CObArray & GetListeElements() { return _Elements ; }
	UINT	GetAttributRegroupe() const { if ( _TableauOrdre.GetSize() > 0) return _TableauOrdre[0] ; else return 0 ; }

	CUIntArray	& GetTableauLargeurs() { return _TableauLargeurs ; }
	CUIntArray	& GetTableauOrdre() { return _TableauOrdre ; }

private:
	CString _AttributFiltre ;
	CString _TexteFiltre ;
	CUIntArray	_TableauLargeurs ;
	CUIntArray	_TableauOrdre ;

	void MajToolbars();
	BOOL AjouteElement( CObArray & Tab, CElement * pElement );
	BOOL ScanneDirectory( const CString & Path, CMapStringToString & ListeAttributsCommuns, CScanningDlg & dlg, CObArray & Temporaire );
	void Nettoie( CObArray & Tab );
	CObArray	_Elements ;
protected: // create from serialization only
	CCollectionFichiersDoc();
	DECLARE_DYNCREATE(CCollectionFichiersDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionFichiersDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void MemoriseLargeursColonnes( int * pTableauLargeurs, int NbItems ) ;
	void MemoriseOrdreColonnes( int * pTableauOrdre, int NbItems );
	void GetListeValeurs( const CString & Attribut, const CString & AttributFiltre, const CString & TexteFiltre, CStringArray & ListeValeurs );
	void ScanneDirectory( const CString & Path, CMapStringToString & ListeAttributsCommuns, CView * pParent );
	virtual ~CCollectionFichiersDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollectionFichiersDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTIONFICHIERSDOC_H__35F8AB22_063E_477D_B4D9_65DFBFA7EB85__INCLUDED_)
