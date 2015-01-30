#if !defined(AFX_BITMAPWND_H__40170023_B2BC_11D1_9802_444553540000__INCLUDED_)
#define AFX_BITMAPWND_H__40170023_B2BC_11D1_9802_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BitmapWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBitmapWnd window

class	CImage ;

class CBitmapWnd : public CWnd
{
// Construction
public:
	CBitmapWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetImage( CImage * pImage );
	virtual ~CBitmapWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBitmapWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CImage*	_pImage ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPWND_H__40170023_B2BC_11D1_9802_444553540000__INCLUDED_)
