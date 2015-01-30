// Tapisserie V2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tapisserie V2.h"
#include "Tapisserie V2Dlg.h"
#include "TapisserieSheet.h"
#include "Page1.h"
#include "Page2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTapisserieV2App

BEGIN_MESSAGE_MAP(CTapisserieV2App, CWinApp)
	//{{AFX_MSG_MAP(CTapisserieV2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTapisserieV2App construction

CTapisserieV2App::CTapisserieV2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTapisserieV2App object

CTapisserieV2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CTapisserieV2App initialization

BOOL CTapisserieV2App::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTapisserieSheet	PropertySheet( IDS_CAPTION ) ;
	CPage1		Page1 ;
	CPage2		Page2 ;

	PropertySheet.AddPage( &Page1 ) ;
	PropertySheet.AddPage( &Page2 ) ;

	PropertySheet.DoModal() ;

	m_pMainWnd	=	0 ;
	return FALSE;
}
