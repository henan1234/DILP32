#if !defined(AFX_CHANGEMOTDEPASSE_H__FB766762_3356_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_CHANGEMOTDEPASSE_H__FB766762_3356_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChangeMotDePasse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeMotDePasse dialog

class CChangeMotDePasse : public CDialog
{
// Construction
public:
	CChangeMotDePasse(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeMotDePasse)
	enum { IDD = IDD_CHANGE_PWD };
	CString	m_Confirm;
	CString	m_Password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeMotDePasse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeMotDePasse)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEMOTDEPASSE_H__FB766762_3356_11D1_AEF5_444553540000__INCLUDED_)
