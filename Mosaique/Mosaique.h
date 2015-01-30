// Mosaique.h : main header file for the MOSAIQUE application
//

#if !defined(AFX_MOSAIQUE_H__89876644_40B7_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_MOSAIQUE_H__89876644_40B7_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueApp:
// See Mosaique.cpp for the implementation of this class
//

class CMosaiqueApp : public CWinApp
{
public:
	CMosaiqueApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMosaiqueApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMosaiqueApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_MOSAIQUE_H__89876644_40B7_11D1_AEF5_444553540000__INCLUDED_)
