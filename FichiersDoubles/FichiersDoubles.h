// FichiersDoubles.h : main header file for the FICHIERSDOUBLES application
//

#if !defined(AFX_FICHIERSDOUBLES_H__ED277BCF_CAFF_439B_BC69_C549178B8151__INCLUDED_)
#define AFX_FICHIERSDOUBLES_H__ED277BCF_CAFF_439B_BC69_C549178B8151__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesApp:
// See FichiersDoubles.cpp for the implementation of this class
//

class CFichiersDoublesApp : public CWinApp
{
public:
	CFichiersDoublesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFichiersDoublesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFichiersDoublesApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FICHIERSDOUBLES_H__ED277BCF_CAFF_439B_BC69_C549178B8151__INCLUDED_)
