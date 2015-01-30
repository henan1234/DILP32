// Decoupe.h : main header file for the DECOUPE application
//

#if !defined(AFX_DECOUPE_H__0F0BDDAF_B41E_4598_90AC_A9DD2CFC9FDD__INCLUDED_)
#define AFX_DECOUPE_H__0F0BDDAF_B41E_4598_90AC_A9DD2CFC9FDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDecoupeApp:
// See Decoupe.cpp for the implementation of this class
//

class CDecoupeApp : public CWinApp
{
public:
	CDecoupeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoupeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDecoupeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECOUPE_H__0F0BDDAF_B41E_4598_90AC_A9DD2CFC9FDD__INCLUDED_)
