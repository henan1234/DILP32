// ActiveDesktopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winreg.h"
#include "winerror.h"
#include "time.h"
#include "io.h"
#include "stdlib.h"
#include "TransparentDesktop.h"
#include "TransparentopDlg.h"
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
// CActiveDesktopDlg dialog

CActiveDesktopDlg::CActiveDesktopDlg(CWnd* pParent /*=NULL*/)
	: BASE_CActiveDesktopDlg(CActiveDesktopDlg::IDD, IDS_TITRE_PAGE1 ) //, pParent)
{
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
	BASE_CActiveDesktopDlg::OnDestroy();
}


///////////////////////////////////////////////////////////////////////////////
// Changement de l'editeur d'image
// On ouvre une boite de dialogue pour choisir un exe
// On ajoute un petit message a la boite pour avertir que l'exe doit etre
// capable d'editer une bitmap
///////////////////////////////////////////////////////////////////////////////
void CActiveDesktopDlg::OnChangeEditor() 
{
	CString		Filter ;
	Filter.LoadString( IDS_FILTRE_IMAGE_EDITOR ) ;
	CFileDialog	Dlg(	TRUE,
						"*.EXE",
						CPreferences::GetImageEditor(),
						OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ENABLETEMPLATE,
						Filter,
						this ) ;

	Dlg.m_ofn.lpTemplateName	=	MAKEINTRESOURCE( IDD_CHOOSE_EDITOR_CHILD ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CPreferences::SetImageEditor( Dlg.GetPathName()) ;

		m_EditorPath	=	CPreferences::GetImageEditor() ;
		UpdateData( FALSE ) ;
		}
}
	

///////////////////////////////////////////////////////////////////////////////
// Retour a l'editeur d'images par defaut
///////////////////////////////////////////////////////////////////////////////
void CActiveDesktopDlg::OnDefaultEditor() 
{
	CPreferences::SetDefaultImageEditor() ;
	m_EditorPath	=	CPreferences::GetImageEditor() ;
	UpdateData( FALSE ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Activation de la page, on grise certains boutons en mode shareware
///////////////////////////////////////////////////////////////////////////////
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
