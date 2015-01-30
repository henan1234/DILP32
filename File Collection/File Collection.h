// File Collection.h : main header file for the FILE COLLECTION application
//

#if !defined(AFX_FILECOLLECTION_H__E756FDDD_87AD_4E06_9962_C859A2C111A8__INCLUDED_)
#define AFX_FILECOLLECTION_H__E756FDDD_87AD_4E06_9962_C859A2C111A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionApp:
// See File Collection.cpp for the implementation of this class
//

class CFileCollectionApp : public CWinApp
{
public:
	CFileCollectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileCollectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CFileCollectionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILECOLLECTION_H__E756FDDD_87AD_4E06_9962_C859A2C111A8__INCLUDED_)
