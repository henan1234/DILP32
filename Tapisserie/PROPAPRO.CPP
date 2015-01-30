// propapro.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "tapisserie.h"
#include "propapro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropAPropos property page

IMPLEMENT_DYNCREATE(CPropAPropos, CPropertyPage)

CPropAPropos::CPropAPropos() : CPropertyPage(CMonAppli::Enregistree() ? CPropAPropos::IDD_ENR : CPropAPropos::IDD)
{
	//{{AFX_DATA_INIT(CPropAPropos)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPropAPropos::~CPropAPropos()
{
}

void CPropAPropos::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropAPropos)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropAPropos, CPropertyPage)
	//{{AFX_MSG_MAP(CPropAPropos)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropAPropos message handlers
