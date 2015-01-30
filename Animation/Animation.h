// Animation.h : main header file for the ANIMATION application
//

#if !defined(AFX_ANIMATION_H__2759DB63_4F85_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_ANIMATION_H__2759DB63_4F85_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnimationApp:
// See Animation.cpp for the implementation of this class
//

class CAnimationApp : public CWinApp
{
public:
	CAnimationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnimationApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_ANIMATION_H__2759DB63_4F85_11D1_AEF5_444553540000__INCLUDED_)
