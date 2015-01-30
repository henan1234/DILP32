#if !defined(AFX_FILTRETOOLBAR_H__A2C68984_E8BA_4DE7_B03F_3028DBD498E2__INCLUDED_)
#define AFX_FILTRETOOLBAR_H__A2C68984_E8BA_4DE7_B03F_3028DBD498E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FiltreToolbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFiltreToolbar dialog

class CFiltreToolbar : public CDialogBar
{
// Construction
public:
	BOOL IsFiltreCorrect();
	void GetFiltre( CString & Attribut, CString & Texte );
	void Maj();
	CFiltreToolbar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFiltreToolbar)
	enum { IDD = IDR_MAINFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiltreToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFiltreToolbar)
	afx_msg void OnFiltrer();
	afx_msg void OnChangeTexte();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILTRETOOLBAR_H__A2C68984_E8BA_4DE7_B03F_3028DBD498E2__INCLUDED_)
