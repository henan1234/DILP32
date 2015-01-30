// Page5.cpp : implementation file
//

#include "stdafx.h"
#include "econo.h"
#include "Page5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPage5

IMPLEMENT_DYNAMIC(CPage5, CPropertySheet)

CPage5::CPage5(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CPage5::CPage5(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CPage5::~CPage5()
{
}


BEGIN_MESSAGE_MAP(CPage5, CPropertySheet)
	//{{AFX_MSG_MAP(CPage5)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage5 message handlers
