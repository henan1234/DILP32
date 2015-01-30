// ChangeMotDePasse.cpp : implementation file
//

#include "stdafx.h"
#include "Transparentdesktop.h"
#include "ChangeMotDePasse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChangeMotDePasse dialog


CChangeMotDePasse::CChangeMotDePasse(CWnd* pParent /*=NULL*/)
	: CDialog(CChangeMotDePasse::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeMotDePasse)
	m_Confirm = _T("");
	m_Password = _T("");
	//}}AFX_DATA_INIT
}


void CChangeMotDePasse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeMotDePasse)
	DDX_Text(pDX, IDC_CONFIRM, m_Confirm);
	DDX_Text(pDX, IDC_PWD, m_Password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeMotDePasse, CDialog)
	//{{AFX_MSG_MAP(CChangeMotDePasse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeMotDePasse message handlers

void CChangeMotDePasse::OnOK() 
{
	UpdateData( TRUE ) ;
	if ( m_Password != m_Confirm )
		{
		CString Message ;
		CString Titre ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString( IDS_PASSWORD_DIFFERENT ) ;

		MessageBeep( MB_ICONSTOP ) ;
		MessageBox( Message, Titre, MB_ICONSTOP | MB_OK | MB_SETFOREGROUND ) ;
		return ;
		}
	CDialog::OnOK();
}
