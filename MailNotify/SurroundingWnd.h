#if !defined(AFX_SURROUNDINGWND_H__69E78343_934D_11D1_9802_444553540000__INCLUDED_)
#define AFX_SURROUNDINGWND_H__69E78343_934D_11D1_9802_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SurroundingWnd.h : header file
//

#include "GraphicWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CSurroundingWnd window

class CSurroundingWnd : public CGraphicWnd
{
// Construction
public:
	CSurroundingWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurroundingWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create( HWND hSurroundedWindow );
	virtual ~CSurroundingWnd();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURROUNDINGWND_H__69E78343_934D_11D1_9802_444553540000__INCLUDED_)
