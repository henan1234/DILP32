// ChoixRepertoire.cpp : implementation file
//

#include "stdafx.h"
#include "Instal.h"
#include "ChoixRepertoire.h"
#include "choosfol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChoixRepertoire property page

IMPLEMENT_DYNCREATE(CChoixRepertoire, CPropertyPage)

CChoixRepertoire::CChoixRepertoire() : CPropertyPage(CChoixRepertoire::IDD)
{
	//{{AFX_DATA_INIT(CChoixRepertoire)
	m_Directory = _T("");
	//}}AFX_DATA_INIT
}

CChoixRepertoire::~CChoixRepertoire()
{
}

void CChoixRepertoire::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChoixRepertoire)
	DDX_Text(pDX, IDC_DIRECTORY, m_Directory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChoixRepertoire, CPropertyPage)
	//{{AFX_MSG_MAP(CChoixRepertoire)
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoixRepertoire message handlers

BOOL CChoixRepertoire::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

	m_Directory	=	pApp->GetInstallationDirectory() ;
	UpdateData( FALSE ) ;
	
	DWORD DiskSpaceKo	=	CInstalApp::DiskSpace() ;

	CString Needed	;
	Needed.Format( "%lu K", DiskSpaceKo ) ;

	SetDlgItemText( IDC_SPACE, Needed ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChoixRepertoire::OnCancelMode() 
{
	CPropertyPage::OnCancelMode();
	
}

void CChoixRepertoire::OnChange() 
{
	CChooseFolder	dlg( m_Directory, this ) ;
	if ( dlg.DoModal() == IDOK )
		{
		m_Directory	=	dlg.GetDirName() ;
		CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
		ASSERT_VALID( pApp ) ;

		pApp->ChangeInstallationDirectory(m_Directory) ;
		UpdateData( FALSE ) ;
		}
}

BOOL CChoixRepertoire::OnSetActive() 
{
	CPropertySheet*	pSheet	=		(CPropertySheet*)GetParent() ;

	ASSERT( pSheet ) ;
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT ) ;
	return CPropertyPage::OnSetActive();
}
