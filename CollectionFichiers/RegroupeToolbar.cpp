// RegroupeToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "collectionfichiers.h"
#include "RegroupeToolbar.h"
#include "element.h"
#include "mainfrm.h"
#include "collectionFichiersDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegroupeToolbar dialog


CRegroupeToolbar::CRegroupeToolbar(CWnd* pParent /*=NULL*/)
//	: CDialog(CRegroupeToolbar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegroupeToolbar)
	//}}AFX_DATA_INIT
}


void CRegroupeToolbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegroupeToolbar)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegroupeToolbar, CDialogBar)
	//{{AFX_MSG_MAP(CRegroupeToolbar)
	ON_CBN_SELCHANGE(IDC_LISTE_ATTRIBUTS, OnSelchangeListeAttributs)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegroupeToolbar message handlers

void CRegroupeToolbar::OnSelchangeListeAttributs() 
{
	CComboBox	ListeAttributs ;
	ListeAttributs.Attach( ::GetDlgItem( *this, IDC_LISTE_ATTRIBUTS)) ;
	CString AttributSelectionne	;

	int CurSel	=	ListeAttributs.GetCurSel() ;

	if ( CurSel != -1 )
		{
		ListeAttributs.GetLBText( CurSel, AttributSelectionne ) ;
		}

	ListeAttributs.Detach() ;

	CMainFrame	*	pFrame	=	(CMainFrame*)AfxGetMainWnd() ;
	CCollectionFichiersDoc * pDoc	=	(CCollectionFichiersDoc*)pFrame->GetActiveDocument() ;

//	if ( pDoc )
//		pDoc->SetAttributRegroupe( AttributSelectionne ) ;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CRegroupeToolbar::Maj()
{
/*	CComboBox	ListeAttributs ;
	ListeAttributs.Attach( ::GetDlgItem( *this, IDC_LISTE_ATTRIBUTS)) ;

	ListeAttributs.SetRedraw( FALSE ) ;
	ListeAttributs.ResetContent() ;

	CStringArray& Attributs	=	CElement::GetTousAttributs() ;

	for ( int i = 0; i < Attributs.GetSize(); i++)
		ListeAttributs.AddString( Attributs[i] ) ;

	CMainFrame	*	pFrame	=	(CMainFrame*)AfxGetMainWnd() ;
	CCollectionFichiersDoc * pDoc	=	(CCollectionFichiersDoc*)pFrame->GetActiveDocument() ;

	ListeAttributs.SelectString( -1, pDoc->GetAttributRegroupe() ) ;

	ListeAttributs.SetRedraw( TRUE ) ;
	ListeAttributs.Invalidate() ;

	ListeAttributs.Detach() ;
	*/
}

BOOL CRegroupeToolbar::OnInitDialog() 
{
//	CDialogBar::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CRegroupeToolbar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

