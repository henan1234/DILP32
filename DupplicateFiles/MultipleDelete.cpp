// MultipleDelete.cpp : implementation file
//

#include "stdafx.h"
#include "dupplicatefiles.h"
#include "MultipleDelete.h"
#include "ChoosFol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultipleDelete dialog


CMultipleDelete::CMultipleDelete(CWnd* pParent /*=NULL*/)
	: CDialog(CMultipleDelete::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultipleDelete)
	m_Directory = _T("");
	m_Choice = -1;
	m_Mask = _T("");
	//}}AFX_DATA_INIT
}


void CMultipleDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultipleDelete)
	DDX_Control(pDX, IDC_TIP, m_Tip);
	DDX_Control(pDX, IDC_BROWSEDIR, m_BrowseBtn);
	DDX_Control(pDX, IDC_MASK, m_MaskCtrl);
	DDX_Control(pDX, IDC_DIR, m_DirCtrl);
	DDX_Text(pDX, IDC_DIR, m_Directory);
	DDX_Radio(pDX, IDC_RADIO1, m_Choice);
	DDX_Text(pDX, IDC_MASK, m_Mask);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultipleDelete, CDialog)
	//{{AFX_MSG_MAP(CMultipleDelete)
	ON_BN_CLICKED(IDC_BROWSEDIR, OnBrowsedir)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultipleDelete message handlers

BOOL CMultipleDelete::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMultipleDelete::OnBrowsedir() 
{
	UpdateData() ;

	CChooseFolder	Dlg( m_Directory, IDS_CHOOSE_DIR, this ) ;
	if ( Dlg.DoModal() == IDOK )
		{
		m_Directory	=	Dlg.GetDirName() ;
		UpdateData( FALSE ) ;
		}
}

void CMultipleDelete::OnRadio1() 
{
	m_MaskCtrl.EnableWindow( FALSE ) ;
	m_DirCtrl.EnableWindow( FALSE ) ;
	m_BrowseBtn.EnableWindow( FALSE ) ;

	CString Tip ;
	Tip.LoadString( IDS_TIP_ALL ) ;
	m_Tip.SetWindowText( Tip ) ;
}

void CMultipleDelete::OnRadio2() 
{
	m_MaskCtrl.EnableWindow( FALSE ) ;
	m_DirCtrl.EnableWindow( TRUE ) ;
	m_BrowseBtn.EnableWindow( TRUE ) ;
	CString Tip ;
	Tip.LoadString( IDS_TIP_DIR ) ;
	m_Tip.SetWindowText( Tip ) ;
}

void CMultipleDelete::OnRadio3() 
{
	m_MaskCtrl.EnableWindow( TRUE ) ;
	m_DirCtrl.EnableWindow( FALSE ) ;
	m_BrowseBtn.EnableWindow( FALSE ) ;

	CString Tip ;
	Tip.LoadString( IDS_TIP_CONTAINING ) ;
	m_Tip.SetWindowText( Tip ) ;

}

HBRUSH CMultipleDelete::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if ( nCtlColor == CTLCOLOR_STATIC  )
		{
		if ( GetWindowLong( *pWnd, GWL_ID ) == IDC_TIP )
			{
			pDC->SetTextColor(RGB(0,0,0)) ;
			pDC->SetBkColor( RGB(255,255,192)) ;
			DeleteObject( hbr ) ;
			hbr	=	CreateSolidBrush( RGB( 255, 255, 192 )) ;
			}
		}
	

	return hbr;
}
