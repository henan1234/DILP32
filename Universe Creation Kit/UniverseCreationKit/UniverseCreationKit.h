// UniverseCreationKit.h : main header file for the UNIVERSECREATIONKIT application
//

#if !defined(AFX_UNIVERSECREATIONKIT_H__634F8E46_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_UNIVERSECREATIONKIT_H__634F8E46_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitApp:
// See UniverseCreationKit.cpp for the implementation of this class
//

class CUniverseCreationKitApp : public CWinApp
{
public:
	CUniverseCreationKitApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUniverseCreationKitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUniverseCreationKitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNIVERSECREATIONKIT_H__634F8E46_06AE_11D2_B79A_0000E8D9BF74__INCLUDED_)
