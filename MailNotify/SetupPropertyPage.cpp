// SetupPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "SetupPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertyPage property page

IMPLEMENT_DYNCREATE(CSetupPropertyPage, CPropertyPage)

CSetupPropertyPage::CSetupPropertyPage() : CPropertyPage(CSetupPropertyPage::IDD)
{
	//{{AFX_DATA_INIT(CSetupPropertyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSetupPropertyPage::~CSetupPropertyPage()
{
}

void CSetupPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPropertyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPropertyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertyPage message handlers
