// PageInformation.cpp : implementation file
//

#include "stdafx.h"
#include "Transparentdesktop.h"
#include "PageInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageInformation dialog


CPageInformation::CPageInformation(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CPageInformation::IDD ) //, pParent)
{
	//{{AFX_DATA_INIT(CPageInformation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInformation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageInformation, CPropertyPage)
	//{{AFX_MSG_MAP(CPageInformation)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageInformation message handlers
