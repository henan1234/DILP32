// SoftCatDoc.h : interface of the CSoftCatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFTCATDOC_H__33985F5A_ACCA_4483_B230_13C14FBB3A09__INCLUDED_)
#define AFX_SOFTCATDOC_H__33985F5A_ACCA_4483_B230_13C14FBB3A09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SoftCatSet.h"


class CSoftCatDoc : public CDocument
{
protected: // create from serialization only
	CSoftCatDoc();
	DECLARE_DYNCREATE(CSoftCatDoc)

// Attributes
public:
	CSoftCatSet m_softCatSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCatDoc)
	public:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSoftCatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSoftCatDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTCATDOC_H__33985F5A_ACCA_4483_B230_13C14FBB3A09__INCLUDED_)
