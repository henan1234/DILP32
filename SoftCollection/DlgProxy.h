// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__8525A317_7E3F_46ED_9867_7EA7C7036189__INCLUDED_)
#define AFX_DLGPROXY_H__8525A317_7E3F_46ED_9867_7EA7C7036189__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSoftCollectionDlg;

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionDlgAutoProxy command target

class CSoftCollectionDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CSoftCollectionDlgAutoProxy)

	CSoftCollectionDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CSoftCollectionDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCollectionDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSoftCollectionDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CSoftCollectionDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSoftCollectionDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CSoftCollectionDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__8525A317_7E3F_46ED_9867_7EA7C7036189__INCLUDED_)
