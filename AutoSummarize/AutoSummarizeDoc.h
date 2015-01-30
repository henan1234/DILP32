// AutoSummarizeDoc.h : interface of the CAutoSummarizeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOSUMMARIZEDOC_H__4887529F_9738_45C1_9DF5_1B3A99958C37__INCLUDED_)
#define AFX_AUTOSUMMARIZEDOC_H__4887529F_9738_45C1_9DF5_1B3A99958C37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoSummarizeDoc : public CDocument
{
protected: // create from serialization only
	CAutoSummarizeDoc();
	DECLARE_DYNCREATE(CAutoSummarizeDoc)

// Attributes
public:
	CStringArray _Mots ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoSummarizeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoSummarizeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoSummarizeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL QueAccentuees();
	BOOL UneVoyelle( const CString & Mot );
	BOOL LonguesSequences( const CString & Mot );
	BOOL AuMoinsUnSansAccent( const CString & Mot );
	void ExtraitMots( LPSTR Mots, DWORD Taille );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSUMMARIZEDOC_H__4887529F_9738_45C1_9DF5_1B3A99958C37__INCLUDED_)
