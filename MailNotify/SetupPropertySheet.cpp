// SetupPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "SetupPropertySheet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertySheet

IMPLEMENT_DYNAMIC(CSetupPropertySheet, CPropertySheet)

CSetupPropertySheet::CSetupPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage( & m_Page1 ) ;
}

CSetupPropertySheet::CSetupPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CSetupPropertySheet::~CSetupPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CSetupPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSetupPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupPropertySheet message handlers
