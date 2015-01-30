// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__56718AAA_22BD_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_DLGPROXY_H__56718AAA_22BD_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CJibe3Dlg;

/////////////////////////////////////////////////////////////////////////////
// CJibe3DlgAutoProxy command target

class CJibe3DlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CJibe3DlgAutoProxy)

	CJibe3DlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CJibe3Dlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJibe3DlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CJibe3DlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CJibe3DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CJibe3DlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CJibe3DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_DLGPROXY_H__56718AAA_22BD_11D1_AEF5_444553540000__INCLUDED_)
