// PreferencesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "PreferencesDlg.h"
#include "preferences.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDlg dialog


CPreferencesDlg::CPreferencesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreferencesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreferencesDlg)
	m_Sauvegarde = _T("");
	m_Fond = -1;
	//}}AFX_DATA_INIT
}


void CPreferencesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreferencesDlg)
	DDX_Text(pDX, IDC_SAUVEGARDE, m_Sauvegarde );
	DDX_Radio(pDX, IDC_RADIO1, m_Fond);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreferencesDlg, CDialog)
	//{{AFX_MSG_MAP(CPreferencesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreferencesDlg message handlers

BOOL CPreferencesDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CPreferences	*	pPref	=	GetPreferences() ;

	pPref->LitPreference( "Nom de fichier", m_Sauvegarde, "JIBE.JIB" ) ;
	pPref->LitPreference( "Fond", m_Fond, 0 ) ;
											   
	UpdateData( FALSE ) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPreferencesDlg::OnOK() 
{
	UpdateData( TRUE ) ;
	CPreferences	*	pPref	=	GetPreferences() ;

	pPref->EcritPreference( "Nom de fichier", m_Sauvegarde ) ;
	pPref->EcritPreference( "Fond", m_Fond ) ;
											   
	
	CDialog::OnOK();
}
