// economiseurpropertysheet.cpp : implementation file
//

#include "stdafx.h"
#include "..\Gravitation\econo.h"
#include "economiseurpropertysheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEconomiseurPropertySheet

IMPLEMENT_DYNAMIC(CEconomiseurPropertySheet, CPropertySheet)

CEconomiseurPropertySheet::CEconomiseurPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CEconomiseurPropertySheet::CEconomiseurPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CEconomiseurPropertySheet::~CEconomiseurPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CEconomiseurPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CEconomiseurPropertySheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEconomiseurPropertySheet message handlers
