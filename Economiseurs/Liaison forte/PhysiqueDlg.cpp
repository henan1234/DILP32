// PhysiqueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "liaisonForte.h"
#include "PhysiqueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhysiqueDlg property page

IMPLEMENT_DYNCREATE(CPhysiqueDlg, CPropertyPage)

CPhysiqueDlg::CPhysiqueDlg() : CPropertyPage(CPhysiqueDlg::IDD)
{
	//{{AFX_DATA_INIT(CPhysiqueDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPhysiqueDlg::~CPhysiqueDlg()
{
}

void CPhysiqueDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhysiqueDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPhysiqueDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPhysiqueDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhysiqueDlg message handlers
