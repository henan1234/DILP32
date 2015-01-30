#if !defined(AFX_DLGPRIORITE_H__CEE7AE61_5846_11D1_AB41_0020AF71E433__INCLUDED_)
#define AFX_DLGPRIORITE_H__CEE7AE61_5846_11D1_AB41_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// dlgpriorite.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPriorite dialog

class CDlgPriorite : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgPriorite)

// Construction
public:
	CDlgPriorite();
	~CDlgPriorite();

// Dialog Data
	//{{AFX_DATA(CDlgPriorite)
	enum { IDD = IDD_PRIORITE };
	CSliderCtrl	m_Priorite;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgPriorite)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPriorite)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRIORITE_H__CEE7AE61_5846_11D1_AB41_0020AF71E433__INCLUDED_)
