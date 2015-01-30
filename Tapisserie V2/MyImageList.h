#if !defined(AFX_MYIMAGELIST_H__D582C947_8D1F_11D3_A616_00A04B04180E__INCLUDED_)
#define AFX_MYIMAGELIST_H__D582C947_8D1F_11D3_A616_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyImageList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyImageList window

class CMyImageList : public CListCtrl
{
// Construction
public:
	CMyImageList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyImageList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyImageList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyImageList)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGELIST_H__D582C947_8D1F_11D3_A616_00A04B04180E__INCLUDED_)
