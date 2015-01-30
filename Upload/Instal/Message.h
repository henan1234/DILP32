#if !defined(AFX_MESSAGE_H__AAB157C2_2DB3_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_MESSAGE_H__AAB157C2_2DB3_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Message.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessage dialog

class CMessage : public CPropertyPage
{
// Construction
public:
	CMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessage)
	enum { IDD = IDD_PROPPAGE_MEDIUM3 };
	CString	m_Status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGE_H__AAB157C2_2DB3_11D1_AEF5_444553540000__INCLUDED_)
