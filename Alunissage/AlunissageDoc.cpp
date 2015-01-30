// AlunissageDoc.cpp : implementation of the CAlunissageDoc class
//

#include "stdafx.h"
#include "Alunissage.h"

#include "AlunissageDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAlunissageDoc

IMPLEMENT_DYNCREATE(CAlunissageDoc, CDocument)

BEGIN_MESSAGE_MAP(CAlunissageDoc, CDocument)
	//{{AFX_MSG_MAP(CAlunissageDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAlunissageDoc construction/destruction

CAlunissageDoc::CAlunissageDoc()
{
	// TODO: add one-time construction code here

}

CAlunissageDoc::~CAlunissageDoc()
{
}

BOOL CAlunissageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAlunissageDoc serialization

void CAlunissageDoc::Serialize(CArchive& ar)
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
// CAlunissageDoc diagnostics

#ifdef _DEBUG
void CAlunissageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAlunissageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAlunissageDoc commands
