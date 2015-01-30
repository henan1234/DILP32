// EquationDoc.cpp : implementation of the CEquationDoc class
//

#include "stdafx.h"
#include "Equation.h"

#include "EquationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEquationDoc

IMPLEMENT_DYNCREATE(CEquationDoc, CDocument)

BEGIN_MESSAGE_MAP(CEquationDoc, CDocument)
	//{{AFX_MSG_MAP(CEquationDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEquationDoc construction/destruction

CEquationDoc::CEquationDoc()
{
	// TODO: add one-time construction code here

}

CEquationDoc::~CEquationDoc()
{
}

BOOL CEquationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CEquationDoc serialization

void CEquationDoc::Serialize(CArchive& ar)
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
// CEquationDoc diagnostics

#ifdef _DEBUG
void CEquationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEquationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEquationDoc commands
