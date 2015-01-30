// information.cpp : implementation file
//

#include "stdafx.h"
#include "Instal.h"
#include "information.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cinformation property page

IMPLEMENT_DYNCREATE(Cinformation, CPropertyPage)

Cinformation::Cinformation() : CPropertyPage(Cinformation::IDD)
{
	//{{AFX_DATA_INIT(Cinformation)
	//}}AFX_DATA_INIT
}

Cinformation::~Cinformation()
{
}

void Cinformation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cinformation)
	DDX_Control(pDX, IDC_INFOS, m_Infos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cinformation, CPropertyPage)
	//{{AFX_MSG_MAP(Cinformation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cinformation message handlers

BOOL Cinformation::OnSetActive() 
{
	CPropertySheet*	pSheet	=		(CPropertySheet*)GetParent() ;

	ASSERT( pSheet ) ;
	pSheet->SetWizardButtons( PSWIZB_NEXT ) ;
	
	return CPropertyPage::OnSetActive();
}

BOOL Cinformation::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CInstalApp*	pApp	=	(CInstalApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

/*	const CString	ProgramName	=	 pApp->ProgramName() ;

	CString Format ;
	m_Infos.GetWindowText( Format ) ;

	CString Titre ;
	Titre.Format( Format, (const char*)ProgramName ) ;

	m_Infos.SetWindowText(  Titre ) ;*/
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
