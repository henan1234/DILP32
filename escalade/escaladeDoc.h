// escaladeDoc.h : interface of the CEscaladeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ESCALADEDOC_H__662B7A39_13EB_4BFD_9E77_37BDA12AEEA2__INCLUDED_)
#define AFX_ESCALADEDOC_H__662B7A39_13EB_4BFD_9E77_37BDA12AEEA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEscaladeDoc : public CDocument
{
protected: // create from serialization only
	CEscaladeDoc();
	DECLARE_DYNCREATE(CEscaladeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEscaladeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEscaladeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEscaladeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESCALADEDOC_H__662B7A39_13EB_4BFD_9E77_37BDA12AEEA2__INCLUDED_)
