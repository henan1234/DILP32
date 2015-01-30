#if !defined(AFX_CONFIRMATION_H__AAB157C1_2DB3_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_CONFIRMATION_H__AAB157C1_2DB3_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Confirmation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfirmation dialog

class CConfirmation : public CPropertyPage
{
	DECLARE_DYNCREATE(CConfirmation)

// Construction
public:
	CConfirmation();
	~CConfirmation();

// Dialog Data
	//{{AFX_DATA(CConfirmation)
	enum { IDD = IDD_PROPPAGE_MEDIUM2 };
	CStatic	m_Infos;
	CString	m_Directory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CConfirmation)
	public:
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConfirmation)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIRMATION_H__AAB157C1_2DB3_11D1_AEF5_444553540000__INCLUDED_)
