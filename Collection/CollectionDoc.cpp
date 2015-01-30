// CollectionDoc.cpp : implementation of the CCollectionDoc class
//

#include "stdafx.h"
#include "Collection.h"

#include "CollectionDoc.h"
#include "DlgAjouteMedia.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollectionDoc

IMPLEMENT_DYNCREATE(CCollectionDoc, CDocument)

BEGIN_MESSAGE_MAP(CCollectionDoc, CDocument)
	//{{AFX_MSG_MAP(CCollectionDoc)
	ON_COMMAND(ID_MDIA_AJOUTERUNMDIA, OnMdiaAjouterunmdia)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollectionDoc construction/destruction

CCollectionDoc::CCollectionDoc()
{
	// TODO: add one-time construction code here

}

CCollectionDoc::~CCollectionDoc()
{
}

BOOL CCollectionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCollectionDoc serialization

void CCollectionDoc::Serialize(CArchive& ar)
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
// CCollectionDoc diagnostics

#ifdef _DEBUG
void CCollectionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCollectionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCollectionDoc commands

void CCollectionDoc::OnMdiaAjouterunmdia() 
{
		CDlgAjouteMedia	dlg ;
		if ( dlg.DoModal() == IDOK )
			{
			}
}
