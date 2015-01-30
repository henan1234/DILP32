#if !defined(AFX_FENETRETRANSPARENTE_H__D365587E_2446_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_FENETRETRANSPARENTE_H__D365587E_2446_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FenetreTransparente.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFenetreTransparente window

class CFenetreTransparente : public CWnd
{
// Construction
public:
	CFenetreTransparente();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFenetreTransparente)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetBitmap(const char * pBitmapName);
	virtual ~CFenetreTransparente();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFenetreTransparente)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HRGN GetRegionFromBitmap( HBITMAP hBitmap, COLORREF Transparent );
	HBITMAP _hBitmap;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FENETRETRANSPARENTE_H__D365587E_2446_11D1_AEF5_444553540000__INCLUDED_)
