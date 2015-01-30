#if !defined(AFX_LINKWINDOW_H__B17251C3_940D_11D1_9802_444553540000__INCLUDED_)
#define AFX_LINKWINDOW_H__B17251C3_940D_11D1_9802_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// LinkWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkWindow window
#include "GraphicWnd.h"

class CLinkWindow : public CGraphicWnd
{
// Construction
public:
	CLinkWindow();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Create( void );
	virtual ~CLinkWindow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLinkWindow)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINKWINDOW_H__B17251C3_940D_11D1_9802_444553540000__INCLUDED_)
