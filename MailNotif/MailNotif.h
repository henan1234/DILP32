// MailNotif.h : main header file for the MAILNOTIF application
//

#if !defined(AFX_MAILNOTIF_H__107BA8D8_EFF8_465B_837A_CC0DA8EBDC4F__INCLUDED_)
#define AFX_MAILNOTIF_H__107BA8D8_EFF8_465B_837A_CC0DA8EBDC4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMailNotifApp:
// See MailNotif.cpp for the implementation of this class
//

class CMailNotifApp : public CWinApp
{
public:
	CMailNotifApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailNotifApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMailNotifApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILNOTIF_H__107BA8D8_EFF8_465B_837A_CC0DA8EBDC4F__INCLUDED_)
