#if !defined(AFX_ECONOMISEURPROPERTYSHEET_H__03835701_5D24_11D1_AB41_0020AF71E433__INCLUDED_)
#define AFX_ECONOMISEURPROPERTYSHEET_H__03835701_5D24_11D1_AB41_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// economiseurpropertysheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEconomiseurPropertySheet

class CEconomiseurPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CEconomiseurPropertySheet)

// Construction
public:
	CEconomiseurPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CEconomiseurPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEconomiseurPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEconomiseurPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEconomiseurPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECONOMISEURPROPERTYSHEET_H__03835701_5D24_11D1_AB41_0020AF71E433__INCLUDED_)
