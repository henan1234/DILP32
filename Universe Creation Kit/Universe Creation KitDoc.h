// Universe Creation KitDoc.h : interface of the CUniverseCreationKitDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIVERSECREATIONKITDOC_H__069CCDAD_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
#define AFX_UNIVERSECREATIONKITDOC_H__069CCDAD_5F35_11D1_98A4_080009F8FCDD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CUniverseCreationKitDoc : public CDocument
{
protected: // create from serialization only
	CUniverseCreationKitDoc();
	DECLARE_DYNCREATE(CUniverseCreationKitDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniverseCreationKitDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUniverseCreationKitDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUniverseCreationKitDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIVERSECREATIONKITDOC_H__069CCDAD_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
