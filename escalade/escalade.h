// escalade.h : main header file for the ESCALADE application
//

#if !defined(AFX_ESCALADE_H__FEE00A9E_5163_4CF0_B951_40C3BB2D19F1__INCLUDED_)
#define AFX_ESCALADE_H__FEE00A9E_5163_4CF0_B951_40C3BB2D19F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEscaladeApp:
// See escalade.cpp for the implementation of this class
//

class CEscaladeApp : public CWinApp
{
public:
	CEscaladeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEscaladeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEscaladeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESCALADE_H__FEE00A9E_5163_4CF0_B951_40C3BB2D19F1__INCLUDED_)
