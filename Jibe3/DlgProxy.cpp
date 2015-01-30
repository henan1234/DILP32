// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe3.h"
#include "DlgProxy.h"
#include "Jibe3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJibe3DlgAutoProxy

IMPLEMENT_DYNCREATE(CJibe3DlgAutoProxy, CCmdTarget)

CJibe3DlgAutoProxy::CJibe3DlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CJibe3Dlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CJibe3Dlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CJibe3DlgAutoProxy::~CJibe3DlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	AfxOleUnlockApp();
}

void CJibe3DlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CJibe3DlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CJibe3DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CJibe3DlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CJibe3DlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IJibe3 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {56718AA3-22BD-11D1-AEF5-444553540000}
static const IID IID_IJibe3 =
{ 0x56718aa3, 0x22bd, 0x11d1, { 0xae, 0xf5, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };

BEGIN_INTERFACE_MAP(CJibe3DlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CJibe3DlgAutoProxy, IID_IJibe3, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {56718AA1-22BD-11D1-AEF5-444553540000}
IMPLEMENT_OLECREATE2(CJibe3DlgAutoProxy, "Jibe3.Application", 0x56718aa1, 0x22bd, 0x11d1, 0xae, 0xf5, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0)

/////////////////////////////////////////////////////////////////////////////
// CJibe3DlgAutoProxy message handlers
