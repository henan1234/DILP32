// Collection.h : main header file for the COLLECTION application
//

#if !defined(AFX_COLLECTION_H__0D303E85_E8FD_42B2_91F9_1521F5615FFC__INCLUDED_)
#define AFX_COLLECTION_H__0D303E85_E8FD_42B2_91F9_1521F5615FFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCollectionApp:
// See Collection.cpp for the implementation of this class
//

class CCollectionApp : public CWinApp
{
public:
	CCollectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCollectionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTION_H__0D303E85_E8FD_42B2_91F9_1521F5615FFC__INCLUDED_)
