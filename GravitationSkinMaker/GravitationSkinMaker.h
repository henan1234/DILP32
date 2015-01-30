// GravitationSkinMaker.h : main header file for the GRAVITATIONSKINMAKER application
//

#if !defined(AFX_GRAVITATIONSKINMAKER_H__9D213526_817B_11D3_A60F_00A04B04180E__INCLUDED_)
#define AFX_GRAVITATIONSKINMAKER_H__9D213526_817B_11D3_A60F_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGravitationSkinMakerApp:
// See GravitationSkinMaker.cpp for the implementation of this class
//

class CGravitationSkinMakerApp : public CWinApp
{
public:
	CGravitationSkinMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravitationSkinMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGravitationSkinMakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVITATIONSKINMAKER_H__9D213526_817B_11D3_A60F_00A04B04180E__INCLUDED_)
