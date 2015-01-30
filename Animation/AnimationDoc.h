// AnimationDoc.h : interface of the CAnimationDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMATIONDOC_H__2759DB6B_4F85_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_ANIMATIONDOC_H__2759DB6B_4F85_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CAnimationDoc : public CDocument
{
protected: // create from serialization only
	CAnimationDoc();
	DECLARE_DYNCREATE(CAnimationDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnimationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnimationDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_ANIMATIONDOC_H__2759DB6B_4F85_11D1_AEF5_444553540000__INCLUDED_)
