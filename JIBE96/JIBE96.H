// Jibe96.h : main header file for the JIBE96 application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJibe96App:
// See Jibe96.cpp for the implementation of this class
//

class CJibe96App : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CJibe96App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJibe96App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
//	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CJibe96App)
	afx_msg void OnAppAbout();
	afx_msg void OnApropos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowTipAtStartup(void);
	void ShowTipOfTheDay(void);
	BOOL TropTard( void );
};


/////////////////////////////////////////////////////////////////////////////
