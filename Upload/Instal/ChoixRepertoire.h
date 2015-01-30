#if !defined(AFX_CHOIXREPERTOIRE_H__57D6A0CE_2DB1_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_CHOIXREPERTOIRE_H__57D6A0CE_2DB1_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChoixRepertoire.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChoixRepertoire dialog

class CChoixRepertoire : public CPropertyPage
{
	DECLARE_DYNCREATE(CChoixRepertoire)

// Construction
public:
	CChoixRepertoire();
	~CChoixRepertoire();

// Dialog Data
	//{{AFX_DATA(CChoixRepertoire)
	enum { IDD = IDD_PROPPAGE_MEDIUM1 };
	CString	m_Directory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CChoixRepertoire)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CChoixRepertoire)
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOIXREPERTOIRE_H__57D6A0CE_2DB1_11D1_AEF5_444553540000__INCLUDED_)
