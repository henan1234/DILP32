// UniverseCreationKitDoc.cpp : implementation of the CUniverseCreationKitDoc class
//

#include "stdafx.h"
#include "UniverseCreationKit.h"

#include "UniverseCreationKitDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitDoc

IMPLEMENT_DYNCREATE(CUniverseCreationKitDoc, CDocument)

BEGIN_MESSAGE_MAP(CUniverseCreationKitDoc, CDocument)
	//{{AFX_MSG_MAP(CUniverseCreationKitDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitDoc construction/destruction

CUniverseCreationKitDoc::CUniverseCreationKitDoc()
{
	// TODO: add one-time construction code here

}

CUniverseCreationKitDoc::~CUniverseCreationKitDoc()
{
}

BOOL CUniverseCreationKitDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitDoc serialization

void CUniverseCreationKitDoc::Serialize(CArchive& ar)
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
// CUniverseCreationKitDoc diagnostics

#ifdef _DEBUG
void CUniverseCreationKitDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUniverseCreationKitDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitDoc commands
