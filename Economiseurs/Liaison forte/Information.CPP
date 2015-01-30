// Information.cpp : implementation file
//

#include "..\economiseur generique\stdafx.h"
#include "resource.h"
#include "liaisonforte.h"
#include "Information.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInformation property page

IMPLEMENT_DYNCREATE(CInformation, CPropertyPage)

CInformation::CInformation() : CPropertyPage(CInformation::IDD)
{
	//{{AFX_DATA_INIT(CInformation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CInformation::~CInformation()
{
}

void CInformation::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInformation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInformation, CPropertyPage)
	//{{AFX_MSG_MAP(CInformation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInformation message handlers
