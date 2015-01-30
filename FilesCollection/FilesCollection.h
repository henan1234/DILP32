// FilesCollection.h : main header file for the FILESCOLLECTION application
//

#if !defined(AFX_FILESCOLLECTION_H__5635EBA1_52A9_4543_B1C5_59DE25CC7E07__INCLUDED_)
#define AFX_FILESCOLLECTION_H__5635EBA1_52A9_4543_B1C5_59DE25CC7E07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionApp:
// See FilesCollection.cpp for the implementation of this class
//

class CFilesCollectionApp : public CWinApp
{
public:
	CFilesCollectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesCollectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFilesCollectionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESCOLLECTION_H__5635EBA1_52A9_4543_B1C5_59DE25CC7E07__INCLUDED_)
