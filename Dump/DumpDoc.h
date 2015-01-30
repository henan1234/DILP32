// DumpDoc.h : interface of the CDumpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUMPDOC_H__3B6AAF8B_1231_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_DUMPDOC_H__3B6AAF8B_1231_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CDumpDoc : public CDocument
{
protected: // create from serialization only
	CDumpDoc();
	DECLARE_DYNCREATE(CDumpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetLigne( int NoLigne );
	int LongueurLigne( void );
	int NbLignes() const;
	virtual ~CDumpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDumpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString RepresentationAnsi( BYTE Octet );
	CString OctetHexa( BYTE );
	LPBYTE _pOctets;
	HANDLE _hMapping;
	HANDLE _hFile;
	DWORD _NbOctetsParLigne;
	DWORD _NbOctets;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_DUMPDOC_H__3B6AAF8B_1231_11D1_AEF5_444553540000__INCLUDED_)
