// Page2.cpp : implementation file
//

#include "stdafx.h"


#include "resource.h"

#include "Page2.h"
#include "RectAffichage.h"
#include "EcoGravitation.h"


/////////////////////////////////////////////////////////////////////////////
// CPage2 property page

IMPLEMENT_DYNCREATE(CPage2, CPropertyPage)

CPage2::CPage2() : CPropertyPage(CPage2::IDD)
{
	//{{AFX_DATA_INIT(CPage2)
	//}}AFX_DATA_INIT
}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage2)
	DDX_Control(pDX, IDC_MAXIMAL_NOMBRE, m_MaximalNombre);
	DDX_Control(pDX, IDC_MINIMAL_NOMBRE, m_MinimalNombre);
	DDX_Control(pDX, IDC_INITIAL_NOMBRE, m_InitialNombre);
	DDX_Control(pDX, IDC_MINIMAL, m_Minimal);
	DDX_Control(pDX, IDC_MAXIMAL, m_Maximal);
	DDX_Control(pDX, IDC_INITIAL, m_Initial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CPage2)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPage2 message handlers

BOOL CPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	ConfSliders() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPage2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl	*	pSlider	=	(CSliderCtrl*) pScrollBar ;
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	switch( nSBCode )
		{
		case TB_BOTTOM :
		case TB_ENDTRACK :
		case TB_LINEDOWN :
		case TB_LINEUP :
		case TB_PAGEDOWN :
		case TB_PAGEUP :
		case TB_THUMBPOSITION :
		case TB_TOP :
			pEco->NbInitCorps	=	m_Initial.GetPos() ;
			pEco->NbMinCorps	=	m_Minimal.GetPos() ;
			pEco->NbMaxCorps	=	m_Maximal.GetPos() ;
			break ;

		case TB_THUMBTRACK :
			{
			int	Valeur	=	pSlider->GetPos() ;
			
			// Modifier la valeur en temps reel
			switch( GetWindowWord( (HWND)pScrollBar->m_hWnd, GWL_ID ))
				{
				case IDC_INITIAL :
					if( Valeur > pEco->NbMaxCorps )
						Valeur = pEco->NbMaxCorps ;
					if (Valeur < pEco->NbMinCorps )
						Valeur = pEco->NbMinCorps ;

					pEco->NbInitCorps	=	Valeur ;
					break ;
				case IDC_MINIMAL :
					if ( Valeur > pEco->NbMaxCorps )
						Valeur	=	pEco->NbMaxCorps ;
					if (Valeur > pEco->NbInitCorps )
						Valeur = pEco->NbInitCorps ;
					if ( Valeur < 2 )
						Valeur = 2 ;

					pEco->NbMinCorps	=	Valeur ;
					break ;

				case IDC_MAXIMAL :
					if ( Valeur < pEco->NbInitCorps )
						Valeur	=	pEco->NbInitCorps ;

					if ( Valeur < pEco->NbMinCorps )
						Valeur	=	pEco->NbMinCorps ;

					if ( Valeur > NB_MAX_CORPS )
						Valeur = NB_MAX_CORPS ;

					pEco->NbMaxCorps	=	Valeur ;
					break ;

				default :
					return ;
				}

			pSlider->SetPos( Valeur) ;
			}
		}

	ConfSliders() ;
	CPropertyPage::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPage2::ConfSliders()
{
	CEcoGravitation*	pEco	=	(CEcoGravitation*)CEconomiseur::GetEconomiseur() ;

	CString	Chaine ;
	m_Initial.SetRange( 2, NB_MAX_CORPS ) ;
	m_Initial.SetSelection( pEco->NbMinCorps, pEco->NbMaxCorps ) ;
	m_Initial.SetPageSize( 10 ) ;
	m_Initial.SetLineSize( 1 ) ;
	m_Initial.SetPos( pEco->NbInitCorps ) ;
	Chaine.Format( "%d", pEco->NbInitCorps ) ;
	m_InitialNombre.SetWindowText( Chaine ) ;
	m_Initial.Invalidate() ;
	

	m_Minimal.SetRange( 2, NB_MAX_CORPS ) ;
	m_Minimal.SetSelection( 2, pEco->NbMaxCorps ) ;
	m_Minimal.SetPageSize( 10 ) ;
	m_Minimal.SetLineSize( 1 ) ;
	m_Minimal.SetPos( pEco->NbMinCorps ) ;
	Chaine.Format( "%d", pEco->NbMinCorps ) ;
	m_MinimalNombre.SetWindowText( Chaine ) ;
	m_Minimal.Invalidate() ;
	

	m_Maximal.SetRange( 2, NB_MAX_CORPS ) ;
	m_Maximal.SetSelection( pEco->NbMinCorps, NB_MAX_CORPS ) ;
	m_Maximal.SetPageSize( 10 ) ;
	m_Maximal.SetLineSize( 1 ) ;
	m_Maximal.SetPos( pEco->NbMaxCorps ) ;
	Chaine.Format( "%d", pEco->NbMaxCorps ) ;
	m_MaximalNombre.SetWindowText( Chaine ) ;
	m_Maximal.Invalidate() ;
}
