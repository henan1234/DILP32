#if !defined(AFX_PHYSIQUEDLG_H__653C3F22_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
#define AFX_PHYSIQUEDLG_H__653C3F22_4C8A_11D1_AB40_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PhysiqueDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhysiqueDlg dialog
#include "resource.h"
class CPhysiqueDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CPhysiqueDlg)

// Construction
public:
	CPhysiqueDlg();
	~CPhysiqueDlg();

// Dialog Data
	//{{AFX_DATA(CPhysiqueDlg)
	enum { IDD = IDD_PHYSIQUE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPhysiqueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPhysiqueDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHYSIQUEDLG_H__653C3F22_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
