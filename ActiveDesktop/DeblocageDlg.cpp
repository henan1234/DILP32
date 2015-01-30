// DeblocageDlg.cpp : implementation file
//

#include "stdafx.h"
#include <stdlib.h>
#include "activedesktop.h"
#include "DeblocageDlg.h"
#include "RegistrationKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeblocageDlg dialog


CDeblocageDlg::CDeblocageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeblocageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeblocageDlg)
	m_Deblocage = _T("");
	//}}AFX_DATA_INIT
}


void CDeblocageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeblocageDlg)
	DDX_Text(pDX, IDC_CODE, m_Deblocage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeblocageDlg, CDialog)
	//{{AFX_MSG_MAP(CDeblocageDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeblocageDlg message handlers

void CDeblocageDlg::OnOK() 
{
	UpdateData( TRUE ) ;

	char Buffer[100]	;
	strcpy( Buffer, m_Deblocage ) ;
	char * pEnd ;

	DWORD	wKey	=	strtoul( Buffer, &pEnd, 10 ) ;

	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

	if ( pApp->_pRegistration->TryToUnlock( wKey ))
		{
		CString	Message ;
		CString	Titre ;

		Message.LoadString( IDS_UNLOCKED ) ;
		Titre.LoadString( IDS_TITRE ) ;

		MessageBox( Message, Titre, MB_OK | MB_ICONINFORMATION ) ;
		}
	else
		{
		CString	Message ;
		CString	Titre ;

		Message.LoadString( IDS_NOT_UNLOCKED ) ;
		Titre.LoadString( IDS_TITRE ) ;

		MessageBox( Message, Titre, MB_OK | MB_ICONSTOP ) ;
		}
	
	CDialog::OnOK();
}
