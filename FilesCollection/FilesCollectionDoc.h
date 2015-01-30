// FilesCollectionDoc.h : interface of the CFilesCollectionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILESCOLLECTIONDOC_H__4605DAE9_E8E6_409F_BBAC_04343F9A6312__INCLUDED_)
#define AFX_FILESCOLLECTIONDOC_H__4605DAE9_E8E6_409F_BBAC_04343F9A6312__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFilesCollectionDoc : public CDocument
{
protected: // create from serialization only
	CFilesCollectionDoc();
	DECLARE_DYNCREATE(CFilesCollectionDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesCollectionDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFilesCollectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFilesCollectionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESCOLLECTIONDOC_H__4605DAE9_E8E6_409F_BBAC_04343F9A6312__INCLUDED_)
