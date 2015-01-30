// DlgCouleurs.cpp : implementation file
//

#include "stdafx.h"
#include "liaisonForte.h"
#include "DlgCouleurs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COLORREF	CouleurFond ;
extern COLORREF	CouleurLien ;
extern COLORREF	AtomeLibre ;
extern COLORREF	AtomeSature ;


/////////////////////////////////////////////////////////////////////////////
// CDlgCouleurs property page

IMPLEMENT_DYNCREATE(CDlgCouleurs, CPropertyPage)

CDlgCouleurs::CDlgCouleurs() : CPropertyPage(CDlgCouleurs::IDD)
{
	//{{AFX_DATA_INIT(CDlgCouleurs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDlgCouleurs::~CDlgCouleurs()
{
}

void CDlgCouleurs::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCouleurs)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCouleurs, CPropertyPage)
	//{{AFX_MSG_MAP(CDlgCouleurs)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_FOND, OnFond)
	ON_BN_CLICKED(IDC_LIBRE, OnLibre)
	ON_BN_CLICKED(IDC_LIENS, OnLiens)
	ON_BN_CLICKED(IDC_SATURE, OnSature)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCouleurs message handlers

void CDlgCouleurs::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	PeintRectangle( dc, IDC_LIBRE, AtomeLibre ) ;	
	PeintRectangle( dc, IDC_SATURE, AtomeSature ) ;	
	PeintRectangle( dc, IDC_LIENS, CouleurLien ) ;	
	PeintRectangle( dc, IDC_FOND, CouleurFond ) ;	
}

void CDlgCouleurs::PeintRectangle( CDC & Dc, UINT IdControl, COLORREF Couleur)
{
	CRect R ;
	::GetWindowRect( ::GetDlgItem( m_hWnd, IdControl ), R ) ;

	ScreenToClient( R ) ;

	R.InflateRect( 10, 8 ) ;

	CBrush Brosse( Couleur ) ;
	Dc.FillRect( R, &Brosse ) ;
	Brosse.DeleteObject() ;
}

void CDlgCouleurs::OnFond() 
{
	CColorDialog	Dlg( CouleurFond, CC_SOLIDCOLOR | CC_FULLOPEN ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CouleurFond	=	Dlg.GetColor() ;
		Invalidate( FALSE ) ;
		}	
}

void CDlgCouleurs::OnLibre() 
{
	CColorDialog	Dlg( AtomeLibre, CC_SOLIDCOLOR | CC_FULLOPEN ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		AtomeLibre	=	Dlg.GetColor() ;
		Invalidate( FALSE ) ;
		}
}

void CDlgCouleurs::OnLiens() 
{
	CColorDialog	Dlg( CouleurLien, CC_SOLIDCOLOR | CC_FULLOPEN ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CouleurLien	=	Dlg.GetColor() ;
		Invalidate( FALSE ) ;
		}
}

void CDlgCouleurs::OnSature() 
{
	CColorDialog	Dlg( AtomeSature, CC_SOLIDCOLOR | CC_FULLOPEN ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		AtomeSature	=	Dlg.GetColor() ;
		Invalidate( FALSE ) ;
		}
}

void CDlgCouleurs::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CPropertyPage::OnOK();
}
