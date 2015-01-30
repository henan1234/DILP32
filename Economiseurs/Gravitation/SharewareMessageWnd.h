#if !defined(AFX_SHAREWAREMESSAGEWND_H__59FE2E80_3356_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_SHAREWAREMESSAGEWND_H__59FE2E80_3356_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SharewareMessageWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSharewareMessageWnd window

class CSharewareMessageWnd : public CWnd
{
// Construction
public:
	CSharewareMessageWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSharewareMessageWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSharewareMessageWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSharewareMessageWnd)
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAREWAREMESSAGEWND_H__59FE2E80_3356_11D2_B79A_0000E8D9BF74__INCLUDED_)
