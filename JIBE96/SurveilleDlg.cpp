// SurveilleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "SurveilleDlg.h"
#include "IconeSurveille.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSurveilleDlg dialog


CSurveilleDlg::CSurveilleDlg(CIcone * pIcone, CWnd* pParent /*=NULL*/)
	: CWndIcone(pIcone)
{
	//{{AFX_DATA_INIT(CSurveilleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSurveilleDlg::DoDataExchange(CDataExchange* pDX)
{
	CWndIcone::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSurveilleDlg)
	DDX_Control(pDX, IDC_EVENEMENTS, m_Evenements);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSurveilleDlg, CWndIcone)
	//{{AFX_MSG_MAP(CSurveilleDlg)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSurveilleDlg message handlers

void CSurveilleDlg::OnSize(UINT nType, int cx, int cy) 
{
	CWndIcone::OnSize(nType, cx, cy);
	
	if ( IsWindow( m_Evenements ))
		m_Evenements.MoveWindow( 0,0, cx, cy, TRUE ) ;	
}

BOOL CSurveilleDlg::OnInitDialog() 
{
	CWndIcone::OnInitDialog();
	
	CIconeSurveille*	pIcone	=	STATIC_DOWNCAST( CIconeSurveille, _pIconeAssociee ) ;
	CStringList*	pListe		=	pIcone->Evenements() ;

	POSITION	Pos	=	pListe->GetHeadPosition( ) ;
	while (Pos )
		{
		CString	S	=	pListe->GetNext( Pos ) ;
		m_Evenements.AddString( S ) ;
		}

	m_Evenements.SetCurSel( m_Evenements.GetCount() -1 ) ;
	m_Evenements.SendMessage( WM_VSCROLL, SB_BOTTOM, 0 ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
