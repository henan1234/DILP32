// Jibe96.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Jibe96.h"

#include "MainFrm.h"
#include "Jibe96Doc.h"
#include "Jibe96View.h"
#include "Splash.h"
#include <dos.h>
#include <direct.h>
#include "preferences.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define JIBE_DEFAULT_FILE	"Jibe.Jib"

CPreferences	Preferences( "Jibe 96" ) ;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CJibe96App

BEGIN_MESSAGE_MAP(CJibe96App, CWinApp)
	ON_COMMAND(CG_IDS_TIPOFTHEDAY, ShowTipOfTheDay)
	//{{AFX_MSG_MAP(CJibe96App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_APROPOS, OnApropos)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJibe96App construction

CJibe96App::CJibe96App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CJibe96App object

CJibe96App theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {F567F820-12A1-11CF-B124-0800096E0E20}
static const CLSID clsid =
{ 0xf567f820, 0x12a1, 0x11cf, { 0xb1, 0x24, 0x8, 0x0, 0x9, 0x6e, 0xe, 0x20 } };

/////////////////////////////////////////////////////////////////////////////
// CJibe96App initialization

BOOL CJibe96App::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	}

	if ( TropTard() )
		{
		CAboutDlg	Dlg ;
		Dlg.DoModal() ;	
		return FALSE ;
		}

	// Verifier que Jibe n'est pas deja lance

	HWND	hWnd	=	::FindWindow(NULL,"Jibe96") ;
	if ( IsWindow( hWnd))
		{
		SetActiveWindow( hWnd );
		return FALSE ;
		}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CJibe96Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CJibe96View));
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
		COleTemplateServer::RegisterAll();

		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}


	CString	FileName ;
	GetPreferences()->LitPreference( "Nom de fichier", FileName, JIBE_DEFAULT_FILE ) ;
	
	// Creer le fichier jibe.jibe la premiere fois, l'ouvrir sinon
	CFileStatus	Status ;

	if ( CFile::GetStatus( FileName, Status ) == 0 )
		{
		OnFileNew() ;

		}
	else
		{
		OpenDocumentFile( FileName ) ;
		}

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// CG: This line inserted by 'Tip of the Day' component.
	ShowTipAtStartup();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CJibe96App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CJibe96App commands

BOOL CJibe96App::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::PreTranslateAppMessage(pMsg);

	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CAboutDlg::OnInitDialog()
{
	// CG: Folowing code is added by System Info Component
	{
	CDialog::OnInitDialog();
	}

	return TRUE;
}

void CJibe96App::OnApropos() 
{
	CAboutDlg	Dlg ;
	Dlg.DoModal() ;	
}

BOOL CJibe96App::TropTard( void )
{
	CTime	Time( CTime::GetCurrentTime()) ;

	if ( Time.GetYear() < 2010 )
		return FALSE ;

	if ( Time.GetMonth() < 6 )
		return FALSE ;

	return TRUE ;
}

void CJibe96App::ShowTipAtStartup(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if (cmdInfo.m_bShowSplash)
	{
		CTipDlg dlg;
		if (dlg.m_bStartup)
			dlg.DoModal();
	}

}

void CJibe96App::ShowTipOfTheDay(void)
{
	// CG: This function added by 'Tip of the Day' component.

	CTipDlg dlg;
	dlg.DoModal();

}
