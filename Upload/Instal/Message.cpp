// Message.cpp : implementation file
//

#include "stdafx.h"
#include "Instal.h"
#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessage dialog


CMessage::CMessage(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CMessage::IDD)
{
	//{{AFX_DATA_INIT(CMessage)
	m_Status = _T("");
	//}}AFX_DATA_INIT
}


void CMessage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessage)
	DDX_Text(pDX, IDC_STATUS, m_Status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessage, CPropertyPage)
	//{{AFX_MSG_MAP(CMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessage message handlers

BOOL CMessage::OnSetActive() 
{
	CPropertySheet*	pSheet	=		(CPropertySheet*)GetParent() ;

	ASSERT( pSheet ) ;
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_FINISH ) ;
	return CPropertyPage::OnSetActive();
}

BOOL CMessage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	m_Status	=	CInstalApp::MessageTermine() ;

	UpdateData( FALSE ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
