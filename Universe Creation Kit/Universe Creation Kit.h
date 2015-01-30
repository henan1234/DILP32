// Universe Creation Kit.h : main header file for the UNIVERSE CREATION KIT application
//

#if !defined(AFX_UNIVERSECREATIONKIT_H__069CCDA5_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
#define AFX_UNIVERSECREATIONKIT_H__069CCDA5_5F35_11D1_98A4_080009F8FCDD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitApp:
// See Universe Creation Kit.cpp for the implementation of this class
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

#endif // !defined(AFX_UNIVERSECREATIONKIT_H__069CCDA5_5F35_11D1_98A4_080009F8FCDD__INCLUDED_)
