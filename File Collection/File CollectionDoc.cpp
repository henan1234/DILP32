// File CollectionDoc.cpp : implementation of the CFileCollectionDoc class
//

#include "stdafx.h"
#include "File Collection.h"

#include "File CollectionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc

IMPLEMENT_DYNCREATE(CFileCollectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileCollectionDoc, CDocument)
	//{{AFX_MSG_MAP(CFileCollectionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFileCollectionDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CFileCollectionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IFileCollection to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {1ABA0DBC-F686-488A-8C01-AC8BB1617AEF}
static const IID IID_IFileCollection =
{ 0x1aba0dbc, 0xf686, 0x488a, { 0x8c, 0x1, 0xac, 0x8b, 0xb1, 0x61, 0x7a, 0xef } };

BEGIN_INTERFACE_MAP(CFileCollectionDoc, CDocument)
	INTERFACE_PART(CFileCollectionDoc, IID_IFileCollection, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc construction/destruction

CFileCollectionDoc::CFileCollectionDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CFileCollectionDoc::~CFileCollectionDoc()
{
	AfxOleUnlockApp();
}

BOOL CFileCollectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc serialization

void CFileCollectionDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc diagnostics

#ifdef _DEBUG
void CFileCollectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileCollectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc commands
