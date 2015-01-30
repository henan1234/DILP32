#if !defined(AFX_PROPPAGES_H__04039F05_2507_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_PROPPAGES_H__04039F05_2507_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropPages.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropPages dialog

class CPropPages : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropPages)

// Construction
public:
	CPropPages();
	~CPropPages();

// Dialog Data
	//{{AFX_DATA(CPropPages)
	enum { IDD = IDD_PROPPAGE_MEDIUM2 };
	CButton	m_ChangePass;
	CButton	m_Ajoute;
	CButton	m_Delete;
	CButton	m_CheckPassword;
	CListCtrl	m_Liste;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropPages)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropPages)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton2();
	afx_msg void OnBeginlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnMdpChange();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPPAGES_H__04039F05_2507_11D1_AEF5_444553540000__INCLUDED_)
