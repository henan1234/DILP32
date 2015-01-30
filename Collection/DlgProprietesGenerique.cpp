// DlgProprietesGenerique.cpp : implementation file
//

#include "stdafx.h"
#include "Collection.h"
#include "DlgProprietesGenerique.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProprietesGenerique dialog


CDlgProprietesGenerique::CDlgProprietesGenerique( UINT IDDlg, CWnd* pParent /*=NULL*/)
	: CDialog(IDDlg, pParent)
{
	//{{AFX_DATA_INIT(CDlgProprietesGenerique)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProprietesGenerique::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProprietesGenerique)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProprietesGenerique, CDialog)
	//{{AFX_MSG_MAP(CDlgProprietesGenerique)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProprietesGenerique message handlers
