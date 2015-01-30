#if !defined(AFX_SAISIEMOTDEPASSE_H__FB766761_3356_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_SAISIEMOTDEPASSE_H__FB766761_3356_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SaisieMotDePasse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaisieMotDePasse dialog

class CSaisieMotDePasse : public CDialog
{
// Construction
public:
	CSaisieMotDePasse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaisieMotDePasse)
	enum { IDD = IDD_PWD };
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaisieMotDePasse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaisieMotDePasse)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAISIEMOTDEPASSE_H__FB766761_3356_11D1_AEF5_444553540000__INCLUDED_)
