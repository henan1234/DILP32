#if !defined(AFX_REGROUPETOOLBAR_H__3C2FAD4E_5B50_4A50_BDDC_6FF94A579D7F__INCLUDED_)
#define AFX_REGROUPETOOLBAR_H__3C2FAD4E_5B50_4A50_BDDC_6FF94A579D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegroupeToolbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegroupeToolbar dialog

class CRegroupeToolbar : public CDialogBar
{
// Construction
public:
	void Maj();
	CRegroupeToolbar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRegroupeToolbar)
	enum { IDD = IDR_REGROUPE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegroupeToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegroupeToolbar)
	afx_msg void OnSelchangeListeAttributs();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFiltrer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGROUPETOOLBAR_H__3C2FAD4E_5B50_4A50_BDDC_6FF94A579D7F__INCLUDED_)
