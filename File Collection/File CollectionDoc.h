// File CollectionDoc.h : interface of the CFileCollectionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECOLLECTIONDOC_H__A38F06BF_C00F_44FA_9CDC_FC705256A533__INCLUDED_)
#define AFX_FILECOLLECTIONDOC_H__A38F06BF_C00F_44FA_9CDC_FC705256A533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileCollectionDoc : public CDocument
{
protected: // create from serialization only
	CFileCollectionDoc();
	DECLARE_DYNCREATE(CFileCollectionDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileCollectionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFileCollectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFileCollectionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CFileCollectionDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECOLLECTIONDOC_H__A38F06BF_C00F_44FA_9CDC_FC705256A533__INCLUDED_)
