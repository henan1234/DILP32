// SoftCollection.h : main header file for the SOFTCOLLECTION application
//

#if !defined(AFX_SOFTCOLLECTION_H__872844FF_0816_4073_B360_1D4554B12483__INCLUDED_)
#define AFX_SOFTCOLLECTION_H__872844FF_0816_4073_B360_1D4554B12483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionApp:
// See SoftCollection.cpp for the implementation of this class
//

class CSoftCollectionApp : public CWinApp
{
public:
	CSoftCollectionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCollectionApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSoftCollectionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTCOLLECTION_H__872844FF_0816_4073_B360_1D4554B12483__INCLUDED_)
