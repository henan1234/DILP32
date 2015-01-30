// SaisieMotDePasse.cpp : implementation file
//

#include "stdafx.h"
#include "Transparentdesktop.h"
#include "SaisieMotDePasse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaisieMotDePasse dialog


CSaisieMotDePasse::CSaisieMotDePasse(CWnd* pParent /*=NULL*/)
	: CDialog(CSaisieMotDePasse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaisieMotDePasse)
	m_Password = _T("");
	//}}AFX_DATA_INIT
}


void CSaisieMotDePasse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaisieMotDePasse)
	DDX_Text(pDX, IDC_PWD, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaisieMotDePasse, CDialog)
	//{{AFX_MSG_MAP(CSaisieMotDePasse)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaisieMotDePasse message handlers
