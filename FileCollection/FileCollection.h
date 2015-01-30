// FileCollection.h : main header file for the FILECOLLECTION application
//

#if !defined(AFX_FILECOLLECTION_H__6A4921A2_029E_4212_8DE6_12F59C19E0D1__INCLUDED_)
#define AFX_FILECOLLECTION_H__6A4921A2_029E_4212_8DE6_12F59C19E0D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionApp:
// See FileCollection.cpp for the implementation of this class
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

#endif // !defined(AFX_FILECOLLECTION_H__6A4921A2_029E_4212_8DE6_12F59C19E0D1__INCLUDED_)
