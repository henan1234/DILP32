// Instal.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Instal.h"
#include "InstalDlg.h"
#include "ChoixRepertoire.h"
#include "Information.h"
#include "Confirmation.h"
#include "Message.h"
#include "script.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define SHELL_FOLDERS	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell folders"
#define PROGRAM_FILES_FOLDERS_KEY	"Software\\Microsoft\\Windows\\CurrentVersion"
#define PROGRAM_FILES_FOLDERS_ENTRY	"ProgramFilesDir"
#define SETUP			"Software\\Microsoft\\Windows\\CurrentVersion\\Setup"


CString	CInstalApp::InstallationDirectory	=	GetProgramsFileDirectory()  ;

/////////////////////////////////////////////////////////////////////////////
// CInstalApp

BEGIN_MESSAGE_MAP(CInstalApp, CWinApp)
	//{{AFX_MSG_MAP(CInstalApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstalApp construction

CInstalApp::CInstalApp()
{
	_pScript = 0 ;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInstalApp object

CInstalApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CInstalApp initialization

BOOL CInstalApp::InitInstance()
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

	_pScript	=	new CScript() ;


	//CInstalDlg dlg;
	CPropertySheet	dlg ;
	Cinformation	Page1 ;
	CChoixRepertoire Page2 ;
	CConfirmation	Page3 ;
	CMessage		Page4 ;

	dlg.AddPage( &Page1 ) ;
	dlg.AddPage( &Page2 ) ;
	dlg.AddPage( &Page3 ) ;
	dlg.AddPage( &Page4 ) ;

	dlg.SetWizardMode() ;

	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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

CString CInstalApp::GetInstallationDirectory()
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT( pApp->_pScript ) ;
	return pApp->_pScript->GetInstallDir() ;
}

void CInstalApp::ChangeInstallationDirectory( const char * pDir )
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT( pApp->_pScript ) ;
	pApp->_pScript->SetInstallDir(pDir) ;
}

BOOL CInstalApp::Install()
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT( pApp->_pScript ) ;

	pApp->_pScript->ExecuteScript( NULL ) ;
	return TRUE ;
}


CString CInstalApp::GetProgramsFileDirectory()
{
	char	buf[_MAX_PATH ] ;

    HKEY hkey;
    LONG ret;
    DWORD cbData=sizeof( buf ) ;
    DWORD dwType;

    ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,PROGRAM_FILES_FOLDERS_KEY,0,KEY_READ,&hkey);

    if(ret==ERROR_SUCCESS)
	    {
        ret=RegQueryValueEx(hkey,PROGRAM_FILES_FOLDERS_ENTRY, NULL,&dwType,(unsigned char*)buf,&cbData);
        if (ret!=ERROR_SUCCESS)
            return "" ;
		}

    else return "" ;
    return buf ;
}



CString CInstalApp::MessageTermine()
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT( pApp->_pScript ) ;
	return pApp->_pScript->MessageTermine() ;
}

DWORD CInstalApp::DiskSpace()
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT( pApp->_pScript ) ;
	return pApp->_pScript->DiskSpace() ;
}

CString CInstalApp::ProgramName()
{
	return _pScript->GetApplicationName() ;
}
