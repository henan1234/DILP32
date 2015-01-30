// FileCollectionDoc.cpp : implementation of the CFileCollectionDoc class
//

#include "stdafx.h"
#include "FileCollection.h"

#include "FileCollectionDoc.h"

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

/////////////////////////////////////////////////////////////////////////////
// CFileCollectionDoc construction/destruction

CFileCollectionDoc::CFileCollectionDoc()
{
	// TODO: add one-time construction code here

}

CFileCollectionDoc::~CFileCollectionDoc()
{
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
