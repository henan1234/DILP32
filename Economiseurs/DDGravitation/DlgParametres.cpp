// DlgParametres.cpp : implementation file
//

#include "..\stdafx.h"
#include "resource.h"
#include "DlgParametres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParametres dialog


CDlgParametres::CDlgParametres(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParametres::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParametres)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgParametres::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParametres)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParametres, CDialog)
	//{{AFX_MSG_MAP(CDlgParametres)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParametres message handlers
