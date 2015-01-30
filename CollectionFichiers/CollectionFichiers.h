// CollectionFichiers.h : main header file for the COLLECTIONFICHIERS application
//

#if !defined(AFX_COLLECTIONFICHIERS_H__48AAB222_B5B0_4DF1_B442_D52619113C4A__INCLUDED_)
#define AFX_COLLECTIONFICHIERS_H__48AAB222_B5B0_4DF1_B442_D52619113C4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "CollectionFichiers_i.h"

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersApp:
// See CollectionFichiers.cpp for the implementation of this class
//

class CCollectionFichiersApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CCollectionFichiersApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCollectionFichiersApp)
	public:
	virtual BOOL InitInstance();
		virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCollectionFichiersApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bATLInited;
private:
	void ShowTipAtStartup(void);
	void ShowTipOfTheDay(void);
	BOOL InitATL();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLLECTIONFICHIERS_H__48AAB222_B5B0_4DF1_B442_D52619113C4A__INCLUDED_)
