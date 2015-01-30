#if !defined(AFX_WARNINGWND_H__CEB81DC3_917C_11D1_9802_444553540000__INCLUDED_)
#define AFX_WARNINGWND_H__CEB81DC3_917C_11D1_9802_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WarningWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarningWnd window


class CSurroundingWnd ;
class CLinkWindow ;

class CWarningWnd : public CWnd
{
// Construction
public:
	CWarningWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarningWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWarningWnd();
	void DisplayMessageWindow( void );

	// Generated message map functions
protected:
	//{{AFX_MSG(CWarningWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CRect GetRectangleFromConfigurationFile( const TCHAR * pSection, const TCHAR * pValue );
	CBitmap * _pBitmap;
	CString _Text;
	const CString & GetText();
	CRect GetLinkRect( const CRect & Tray, const CRect & Message, int Edge );
	CLinkWindow* _pLinkWnd;
	HWND GetIconTrayWnd();
	void HideMessageWindow( void );
	UINT GetTaskBarPosition( HWND hTaskBar );
	static void MoveIntTo( LONG & Moving, LONG Target );
	void MoveRect( CRect & Moving, const CRect  & Target );
	void GetInitialAndFinalWindowRect( CRect &, CRect & ) ;

	CSurroundingWnd * _pSurroundingWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNINGWND_H__CEB81DC3_917C_11D1_9802_444553540000__INCLUDED_)
