#if !defined(AFX_INFORMATION_H__57D6A0CD_2DB1_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_INFORMATION_H__57D6A0CD_2DB1_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// information.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cinformation dialog

class Cinformation : public CPropertyPage
{
	DECLARE_DYNCREATE(Cinformation)

// Construction
public:
	Cinformation();
	~Cinformation();

// Dialog Data
	//{{AFX_DATA(Cinformation)
	enum { IDD = IDD_PROPPAGE_MEDIUM };
	CStatic	m_Infos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(Cinformation)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(Cinformation)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFORMATION_H__57D6A0CD_2DB1_11D1_AEF5_444553540000__INCLUDED_)
