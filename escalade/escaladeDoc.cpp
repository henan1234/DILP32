// escaladeDoc.cpp : implementation of the CEscaladeDoc class
//

#include "stdafx.h"
#include "escalade.h"

#include "escaladeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEscaladeDoc

IMPLEMENT_DYNCREATE(CEscaladeDoc, CDocument)

BEGIN_MESSAGE_MAP(CEscaladeDoc, CDocument)
	//{{AFX_MSG_MAP(CEscaladeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEscaladeDoc construction/destruction

CEscaladeDoc::CEscaladeDoc()
{
	// TODO: add one-time construction code here

}

CEscaladeDoc::~CEscaladeDoc()
{
}

BOOL CEscaladeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEscaladeDoc serialization

void CEscaladeDoc::Serialize(CArchive& ar)
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
// CEscaladeDoc diagnostics

#ifdef _DEBUG
void CEscaladeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEscaladeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEscaladeDoc commands
