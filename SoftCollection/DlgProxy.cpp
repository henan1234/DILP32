// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "SoftCollection.h"
#include "DlgProxy.h"
#include "SoftCollectionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionDlgAutoProxy

IMPLEMENT_DYNCREATE(CSoftCollectionDlgAutoProxy, CCmdTarget)

CSoftCollectionDlgAutoProxy::CSoftCollectionDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CSoftCollectionDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CSoftCollectionDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CSoftCollectionDlgAutoProxy::~CSoftCollectionDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CSoftCollectionDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CSoftCollectionDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CSoftCollectionDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CSoftCollectionDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CSoftCollectionDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_ISoftCollection to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {299DF0A9-E9B6-4A5C-AD90-0E06799365E8}
static const IID IID_ISoftCollection =
{ 0x299df0a9, 0xe9b6, 0x4a5c, { 0xad, 0x90, 0xe, 0x6, 0x79, 0x93, 0x65, 0xe8 } };

BEGIN_INTERFACE_MAP(CSoftCollectionDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CSoftCollectionDlgAutoProxy, IID_ISoftCollection, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {5B9340D9-2A92-4F82-A501-C366AC0848F7}
IMPLEMENT_OLECREATE2(CSoftCollectionDlgAutoProxy, "SoftCollection.Application", 0x5b9340d9, 0x2a92, 0x4f82, 0xa5, 0x1, 0xc3, 0x66, 0xac, 0x8, 0x48, 0xf7)

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionDlgAutoProxy message handlers
