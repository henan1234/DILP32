// SoftCatDoc.cpp : implementation of the CSoftCatDoc class
//

#include "stdafx.h"
#include "SoftCat.h"

#include "SoftCatSet.h"
#include "SoftCatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftCatDoc

IMPLEMENT_DYNCREATE(CSoftCatDoc, CDocument)

BEGIN_MESSAGE_MAP(CSoftCatDoc, CDocument)
	//{{AFX_MSG_MAP(CSoftCatDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoftCatDoc construction/destruction

CSoftCatDoc::CSoftCatDoc()
{
	// TODO: add one-time construction code here

}

CSoftCatDoc::~CSoftCatDoc()
{
}

BOOL CSoftCatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSoftCatDoc diagnostics

#ifdef _DEBUG
void CSoftCatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSoftCatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSoftCatDoc commands
