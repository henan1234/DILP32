#if !defined(AFX_GRAPHICWND_H__B17251C4_940D_11D1_9802_444553540000__INCLUDED_)
#define AFX_GRAPHICWND_H__B17251C4_940D_11D1_9802_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphicWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphicWnd window

class CGraphicWnd : public CWnd
{
// Construction
public:
	CGraphicWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicWnd)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static CObList _WindowList;
	friend void CALLBACK EXPORT TimerProc(HWND, UINT, UINT, DWORD ) ;
	static int _Origin;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICWND_H__B17251C4_940D_11D1_9802_444553540000__INCLUDED_)
