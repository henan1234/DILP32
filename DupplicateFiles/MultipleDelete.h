#if !defined(AFX_MULTIPLEDELETE_H__49919AE2_53B9_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_MULTIPLEDELETE_H__49919AE2_53B9_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MultipleDelete.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultipleDelete dialog

class CMultipleDelete : public CDialog
{
// Construction
public:
	CMultipleDelete(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMultipleDelete)
	enum { IDD = IDD_MULTIPLE };
	CEdit	m_Tip;
	CButton	m_BrowseBtn;
	CEdit	m_MaskCtrl;
	CEdit	m_DirCtrl;
	CString	m_Directory;
	int		m_Choice;
	CString	m_Mask;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultipleDelete)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMultipleDelete)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowsedir();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLEDELETE_H__49919AE2_53B9_11D2_B79A_0000E8D9BF74__INCLUDED_)
