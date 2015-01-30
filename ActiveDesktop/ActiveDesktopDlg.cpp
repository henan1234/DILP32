// ActiveDesktopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winreg.h"
#include "winerror.h"
#include "time.h"
#include "io.h"
#include "stdlib.h"
#include "ActiveDesktop.h"
#include "ActiveDesktopDlg.h"
#include "FenetreTransparente.h"
#include "GraphicPropertySheet.h"
#include "Preferences.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define BASE_CActiveDesktopDlg	CPropertyPage


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

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

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopDlg dialog

CActiveDesktopDlg::CActiveDesktopDlg(CWnd* pParent /*=NULL*/)
	: BASE_CActiveDesktopDlg(CActiveDesktopDlg::IDD, IDS_TITRE_PAGE1 ) //, pParent)
{
	_BackupActuel	=	0 ;

	//{{AFX_DATA_INIT(CActiveDesktopDlg)
	m_EditorPath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
}

void CActiveDesktopDlg::DoDataExchange(CDataExchange* pDX)
{
	BASE_CActiveDesktopDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveDesktopDlg)
	DDX_Control(pDX, IDC_DEFAULT_EDITOR, m_DefaultEditor);
	DDX_Control(pDX, IDC_CHANGE_EDITOR, m_ChangeEditor);
	DDX_Text(pDX, IDC_EDITOR, m_EditorPath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CActiveDesktopDlg, BASE_CActiveDesktopDlg)
	//{{AFX_MSG_MAP(CActiveDesktopDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHANGE_EDITOR, OnChangeEditor)
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_DEFAULT_EDITOR, OnDefaultEditor)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopDlg message handlers

BOOL CActiveDesktopDlg::OnInitDialog()
{
	BASE_CActiveDesktopDlg::OnInitDialog();

	m_EditorPath	=	CPreferences::GetImageEditor() ;

	UpdateData( FALSE ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CActiveDesktopDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	BASE_CActiveDesktopDlg::OnDestroy();
}

void CActiveDesktopDlg::OnChangeEditor() 
{
	CFileDialog	Dlg(	TRUE,
						"*.EXE",
						CPreferences::GetImageEditor(),
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ENABLETEMPLATE,
						"Image editors (*.EXE)|*.EXE||",
						this ) ;

	Dlg.m_ofn.lpTemplateName	=	MAKEINTRESOURCE( IDD_CHOOSE_EDITOR_CHILD ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CPreferences::SetImageEditor( Dlg.GetPathName()) ;
		}
}
	

void CActiveDesktopDlg::OnDefaultEditor() 
{
	CPreferences::SetDefaultImageEditor() ;
	m_EditorPath	=	CPreferences::GetImageEditor() ;
	UpdateData( FALSE ) ;
}


BOOL CActiveDesktopDlg::OnSetActive()
{
	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;
	if ( CActiveDesktopApp::IsShareWare())
		{
		m_ChangeEditor.EnableWindow( FALSE ) ;
		m_DefaultEditor.EnableWindow( FALSE ) ;
		}
	else
		{
		m_ChangeEditor.EnableWindow( TRUE ) ;
		m_DefaultEditor.EnableWindow( TRUE ) ;
		}

	return TRUE ;
}
