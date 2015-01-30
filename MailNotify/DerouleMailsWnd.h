#if !defined(AFX_DEROULEMAILSWND_H__5D734632_FE6C_4156_81AA_ACCA9EDB1FC7__INCLUDED_)
#define AFX_DEROULEMAILSWND_H__5D734632_FE6C_4156_81AA_ACCA9EDB1FC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DerouleMailsWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDerouleMailsWnd window

class CDerouleMailsWnd : public CWnd
{
// Construction
public:
	CDerouleMailsWnd();
	int	_Decalage ;
	int	_Texte ;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDerouleMailsWnd)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDerouleMailsWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDerouleMailsWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void Dessine( CDC & Dc );
	CBitmap _Gauche ;
	CBitmap _Droite ;
	CBitmap _Centre ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEROULEMAILSWND_H__5D734632_FE6C_4156_81AA_ACCA9EDB1FC7__INCLUDED_)
