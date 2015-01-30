// ActiveDesktop.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Transparentdesktop.h"
#include "TransparentopDlg.h"
#include "GraphicPropertySheet.h"
#include "PageInformation.h"
#include "PropPages.h"
#include <RegistrationKey.h>
#include <PropPageRegistering.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopApp

BEGIN_MESSAGE_MAP(CActiveDesktopApp, CWinApp)
	//{{AFX_MSG_MAP(CActiveDesktopApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopApp construction

CActiveDesktopApp::CActiveDesktopApp()
{
	_pRegistration	=	new CRegistrationKey( WAD_PATH, WAD_HIDDEN ) ;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CActiveDesktopApp object

CActiveDesktopApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopApp initialization

BOOL CActiveDesktopApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//CTime	Aujourdhui	=	CTime::GetCurrentTime() ;

	//if ( Aujourdhui.GetYear() > 1997 )
	//	{
	//	MessageBeep( MB_ICONINFORMATION ) ;
	//	MessageBox( NULL, "Expired beta version", "Transparent Desktop", MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND | MB_SETFOREGROUND) ;
	//	return FALSE ;
	//	}

	CGraphicPropertySheet	Prop( IDS_TITRE ) ;
	CPageInformation		Page1 ;
		
	if ( _pRegistration->IsLocked())
		Prop.AddPage( &Page1 ) ;
	
	CActiveDesktopDlg		Page2 ;
	CPropPages				Page3 ;

	Prop.AddPage( &Page2 ) ;
	Prop.AddPage( &Page3 ) ;

	CPropPageRegistering	Page4(  IDD_PROPPAGE_REGISTERING );

	if ( _pRegistration->IsLocked())
		Prop.AddPage( &Page4 ) ;

	CString	Titre ;
	Titre.LoadString( IDS_TITRE_FENETRE ) ;
	Prop.SetTitle( Titre ) ;

	m_pMainWnd	=	&Prop ;

	int nResponse	=	Prop.DoModal() ;


	/*CActiveDesktopDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();*/

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

BOOL	CActiveDesktopApp::IsShareWare()
	{
	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;

	ASSERT_VALID( pApp ) ;
	ASSERT( pApp->_pRegistration ) ;

	return pApp->_pRegistration->IsLocked() ;
	}
