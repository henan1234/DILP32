// Install.h : main header file for the INSTALL application
//

#if !defined(AFX_INSTALL_H__FA8AA783_1EC0_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_INSTALL_H__FA8AA783_1EC0_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInstallApp:
// See Install.cpp for the implementation of this class
//

class CInstallApp : public CWinApp
{
public:
	CInstallApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInstallApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio ins�re des d�clarations suppl�mentaires juste au-dessus de la ligne pr�c�dente.

#endif // !defined(AFX_INSTALL_H__FA8AA783_1EC0_11D1_AEF5_444553540000__INCLUDED_)
