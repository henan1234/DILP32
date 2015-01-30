#if !defined(AFX_PAGEINFORMATION_H__04039F02_2507_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_PAGEINFORMATION_H__04039F02_2507_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageInformation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageInformation dialog

class CPageInformation : public CPropertyPage
{
// Construction
public:
	CPageInformation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPageInformation)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageInformation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageInformation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINFORMATION_H__04039F02_2507_11D1_AEF5_444553540000__INCLUDED_)
