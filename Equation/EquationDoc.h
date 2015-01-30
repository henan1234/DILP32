// EquationDoc.h : interface of the CEquationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUATIONDOC_H__11F7A589_126E_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_EQUATIONDOC_H__11F7A589_126E_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CEquationDoc : public CDocument
{
protected: // create from serialization only
	CEquationDoc();
	DECLARE_DYNCREATE(CEquationDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEquationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEquationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEquationDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_EQUATIONDOC_H__11F7A589_126E_11D1_AEF5_444553540000__INCLUDED_)
