// FilesCollectionDoc.cpp : implementation of the CFilesCollectionDoc class
//

#include "stdafx.h"
#include "FilesCollection.h"

#include "FilesCollectionDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionDoc

IMPLEMENT_DYNCREATE(CFilesCollectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CFilesCollectionDoc, CDocument)
	//{{AFX_MSG_MAP(CFilesCollectionDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionDoc construction/destruction

CFilesCollectionDoc::CFilesCollectionDoc()
{
	// TODO: add one-time construction code here

}

CFilesCollectionDoc::~CFilesCollectionDoc()
{
}

BOOL CFilesCollectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionDoc diagnostics

#ifdef _DEBUG
void CFilesCollectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFilesCollectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFilesCollectionDoc commands
