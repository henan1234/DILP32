// InstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Install.h"
#include "InstallDlg.h"
#include "stdlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char NomFichier[]	=	"Gravitation.scr" ;

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg dialog

CInstallDlg::CInstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstallDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallDlg)
	DDX_Control(pDX, IDC_CONFIGURATION, m_Configuration);
	DDX_Control(pDX, IDC_CHOIX, m_Choix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInstallDlg, CDialog)
	//{{AFX_MSG_MAP(CInstallDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSTALL, OnInstall)
	ON_BN_CLICKED(IDC_README, OnReadme)
	ON_BN_CLICKED(IDC_CONFIGURATION, OnConfiguration)
	ON_BN_CLICKED(IDC_CHOIX, OnChoix)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallDlg message handlers

BOOL CInstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Choix.EnableWindow( FALSE ) ;
	m_Configuration.EnableWindow( FALSE ) ;
	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstallDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInstallDlg::OnInstall() 
{
	// Copier Gravitation.scr dans le repertoire systeme
	char Buffer[_MAX_PATH] ;
	GetSystemDirectory(Buffer, sizeof( Buffer )) ;
	
	if ( Buffer[strlen(Buffer)-1] != '\\' )
		strcat( Buffer, "\\" ) ;

	strcat( Buffer, NomFichier ) ;

	// Lire le nom du fichier
	if ( CopyFile( NomFichier, Buffer, FALSE ))
		{
		m_Choix.EnableWindow( TRUE ) ;
		m_Configuration.EnableWindow( TRUE ) ;
		MessageBox( "The shareware version of Gravitation screen saver has been installed on your PC\n"
					"You may now choose it as your active screen saver",
					"Installation OK",
					MB_OK | MB_ICONINFORMATION ) ;
		}
	else
		MessageBox( "The file could not be copied, your drive may be full", "Error", MB_OK | MB_ICONSTOP ) ;
}

void CInstallDlg::OnReadme() 
{
	char Buffer[_MAX_PATH] ;
	GetCurrentDirectory( sizeof( Buffer ), Buffer ) ;

	ShellExecute( m_hWnd, NULL, "Readme.txt", NULL, Buffer,	SW_SHOW ) ;
}

void CInstallDlg::OnConfiguration() 
{
		// Copier Gravitation.scr dans le repertoire systeme
	char SystemDir[_MAX_PATH] ;
	GetSystemDirectory(SystemDir, sizeof( SystemDir )) ;
	
	char Buffer[_MAX_PATH] ;
	strcpy( Buffer, SystemDir ) ;

	if ( Buffer[strlen(Buffer)-1] != '\\' )
		strcat( Buffer, "\\" ) ;

	strcat( Buffer, NomFichier ) ;


	ShellExecute( m_hWnd, "config", Buffer, NULL, SystemDir,	SW_SHOW ) ;
}

void CInstallDlg::OnChoix() 
{
		// Copier Gravitation.scr dans le repertoire systeme
	char SystemDir[_MAX_PATH] ;
	GetSystemDirectory(SystemDir, sizeof( SystemDir )) ;
	
	char Buffer[_MAX_PATH] ;
	strcpy( Buffer, SystemDir ) ;

	if ( Buffer[strlen(Buffer)-1] != '\\' )
		strcat( Buffer, "\\" ) ;

	strcat( Buffer, NomFichier ) ;


	ShellExecute( m_hWnd, "install", Buffer, NULL, SystemDir,	SW_SHOW ) ;
}
