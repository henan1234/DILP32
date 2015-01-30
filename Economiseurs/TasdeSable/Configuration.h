#if !defined(AFX_CONFIGURATION_H__CE3988E2_4ED6_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_CONFIGURATION_H__CE3988E2_4ED6_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Configuration.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CConfiguration dialog

class CConfiguration : public CPropertyPage
{
// Construction
public:
	CConfiguration();   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfiguration)
	enum { IDD = IDD_PROPPAGE_CONFIG };
	CSliderCtrl	m_Vitesse;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfiguration)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfiguration)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATION_H__CE3988E2_4ED6_11D1_AEF5_444553540000__INCLUDED_)
