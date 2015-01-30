// AutoSummarize.h : main header file for the AUTOSUMMARIZE application
//

#if !defined(AFX_AUTOSUMMARIZE_H__06878FEE_0B90_4F41_9B23_C02B039FE27B__INCLUDED_)
#define AFX_AUTOSUMMARIZE_H__06878FEE_0B90_4F41_9B23_C02B039FE27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeApp:
// See AutoSummarize.cpp for the implementation of this class
//

class CAutoSummarizeApp : public CWinApp
{
public:
	CAutoSummarizeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoSummarizeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAutoSummarizeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSUMMARIZE_H__06878FEE_0B90_4F41_9B23_C02B039FE27B__INCLUDED_)
