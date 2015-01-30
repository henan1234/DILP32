// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
	//}}AFX_DATA_INIT

	_Aborted	=	FALSE ;
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_FICHIER_SEC, m_TempsMoyen);
	DDX_Control(pDX, IDC_ANIMATE1, m_Animate);
	DDX_Control(pDX, IDC_FICHIER_EN_COURS, m_FichierEnCours);
	DDX_Control(pDX, IDC_FICHIER_1_SUR, m_UnSur);
	DDX_Control(pDX, IDC_DUPLIQUES_TROUVES, m_DuppliquesTrouves);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::Aborted()
{
	if ( _Aborted )
		return TRUE ;

	MSG Msg ;
	while ( PeekMessage( &Msg, NULL, 0, 0, PM_REMOVE ))
		{
		TranslateMessage( &Msg ) ;
		DispatchMessage( & Msg ) ;
		}

	return _Aborted ;
}

void CProgressDlg::OnCancel() 
{
	_Aborted	=	TRUE ;
}

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Animate.Open( IDR_AVI1 ) ;	
	m_Animate.Play( 0, -1, -1 ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
