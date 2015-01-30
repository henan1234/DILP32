// CollectionDoc.h : interface of the CCollectionDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLLECTIONDOC_H__3AD50C09_8C0D_4EE8_9E36_5747247ED8A4__INCLUDED_)
#define AFX_COLLECTIONDOC_H__3AD50C09_8C0D_4EE8_9E36_5747247ED8A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCollectionDoc : public CDocument
{
protected: // create from serialization only
	CCollectionDoc();
	DECLARE_DYNCREATE(CCollectionDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCollectionDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCollectionDoc)
	afx_msg void OnMdiaAjouterunmdia();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTIONDOC_H__3AD50C09_8C0D_4EE8_9E36_5747247ED8A4__INCLUDED_)
