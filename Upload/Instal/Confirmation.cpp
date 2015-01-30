// Confirmation.cpp : implementation file
//

#include "stdafx.h"
#include "Instal.h"
#include "Confirmation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfirmation property page

IMPLEMENT_DYNCREATE(CConfirmation, CPropertyPage)

CConfirmation::CConfirmation() : CPropertyPage(CConfirmation::IDD)
{
	//{{AFX_DATA_INIT(CConfirmation)
	m_Directory = _T("");
	//}}AFX_DATA_INIT
}

CConfirmation::~CConfirmation()
{
}

void CConfirmation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfirmation)
	DDX_Control(pDX, IDC_INFOS, m_Infos);
	DDX_Text(pDX, IDC_EDIT1, m_Directory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfirmation, CPropertyPage)
	//{{AFX_MSG_MAP(CConfirmation)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfirmation message handlers

BOOL CConfirmation::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

	m_Directory	=	pApp->GetInstallationDirectory() ;
	UpdateData( FALSE ) ;

	const CString	ProgramName	=	 pApp->ProgramName() ;

	CString Format ;
	m_Infos.GetWindowText( Format ) ;

	CString Titre ;
	Titre.Format( Format, (const char*)ProgramName ) ;

	m_Infos.SetWindowText(  Titre ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfirmation::OnCancelMode() 
{
	CPropertyPage::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

LRESULT CConfirmation::OnWizardNext() 
{
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;
	pApp->Install() ;
	
	return CPropertyPage::OnWizardNext();
}
