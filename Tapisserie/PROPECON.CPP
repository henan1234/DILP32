// propecon.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "propecon.h"
#include "eco.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

UINT				CPropEconomiseurs::_NbMinutes = 0 ;
CListeEconomiseurs	CPropEconomiseurs::_Liste ;
HWND				CPropEconomiseurs::_hOldWnd = 0 ;

/////////////////////////////////////////////////////////////////////////////
// CPropEconomiseurs property page

IMPLEMENT_DYNCREATE(CPropEconomiseurs, CPropertyPage)

CPropEconomiseurs::CPropEconomiseurs() : CPropertyPage(CPropEconomiseurs::IDD)
{
	//{{AFX_DATA_INIT(CPropEconomiseurs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	_hOldWnd	=	0 ;
}

CPropEconomiseurs::~CPropEconomiseurs()
{
}

void CPropEconomiseurs::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropEconomiseurs)
	DDX_Control(pDX, IDC_LISTE_ECO, m_LB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropEconomiseurs, CPropertyPage)
	//{{AFX_MSG_MAP(CPropEconomiseurs)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_LBN_SELCHANGE(IDC_LISTE_ECO, OnSelchangeListeEco)
	ON_BN_CLICKED(IDC_CONFIGURER, OnConfigurer)
	ON_BN_CLICKED(IDC_TEST, OnTest)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropEconomiseurs message handlers

BOOL CPropEconomiseurs::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	_Liste.Init() ;

	const int Nb   =  _Liste.NbEconomiseurs() ;

	for ( int i = 0; i < Nb; i++ )
	  {
	  CEconomiseur*  pEco  =  _Liste.GetAt(i) ;
  
	  const int Indice  =  m_LB.AddString( pEco->Chemin() ) ;
	  m_LB.SetItemData( Indice, (DWORD)pEco ) ;
	  }

	m_LB.SetCurSel(0) ;
	OnSelchangeListeEco	() ;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropEconomiseurs::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
   lpMeasureItemStruct->itemHeight  =  ::GetSystemMetrics(SM_CYICON)+4 ;
   CRect R ;
   GetClientRect(R) ;
   lpMeasureItemStruct->itemWidth=  R.Width() ;
}

void CPropEconomiseurs::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDraw) 
{
   if ( lpDraw->itemState & ODS_SELECTED )
      {
      HBRUSH   hBrush = CreateSolidBrush( GetSysColor( COLOR_HIGHLIGHT )) ;
         
      FillRect( lpDraw->hDC, &lpDraw->rcItem, hBrush ) ;
      DeleteObject( hBrush ) ;
      DrawFocusRect( lpDraw->hDC, &lpDraw->rcItem ) ;
      SetTextColor( lpDraw->hDC, GetSysColor( COLOR_HIGHLIGHTTEXT )) ;
      SetBkColor( lpDraw->hDC, GetSysColor( COLOR_HIGHLIGHT )) ;
      SelectObject( lpDraw->hDC, GetStockObject( SYSTEM_FONT )) ;
	  }
   else
      {
      HBRUSH hBrush = CreateSolidBrush( GetSysColor(COLOR_WINDOW)) ;
      FillRect( lpDraw->hDC, &lpDraw->rcItem, hBrush ) ;
      DeleteObject( hBrush ) ;
      SetTextColor( lpDraw->hDC, GetSysColor( COLOR_WINDOWTEXT )) ;
      SetBkColor( lpDraw->hDC, GetSysColor( COLOR_WINDOW )) ;
      SelectObject( lpDraw->hDC, GetStockObject( ANSI_VAR_FONT )) ;
	  }
            
   RECT     R = lpDraw->rcItem ;
   InflateRect( &R, -2, -2 ) ;
   
   if ( lpDraw->itemID >= 0 )
      {
      CEconomiseur*  pEco  =  (CEconomiseur*)
                           (m_LB.GetItemData( lpDraw->itemID )) ;
      ASSERT( pEco->IsKindOf( RUNTIME_CLASS( CEconomiseur))) ;
               
      HICON    hIcone = ExtractIcon(   AfxGetInstanceHandle(),
                                 pEco->Chemin(),
                                 0 ) ;

      if ( hIcone )
      	{
        DrawIcon( lpDraw->hDC,R.left,R.top,hIcone ) ;
        DestroyIcon( hIcone );
        }
      else
      		DrawIcon( lpDraw->hDC, R.left, R.top, LoadIcon(NULL, IDI_QUESTION)) ;
         
      R.left += ::GetSystemMetrics( SM_CXICON ) + 2 ;
      
      CString	Priorite ;
      Priorite.LoadString( 2000 + pEco->Priorite()) ;
      
      char	Texte[200] ;
      wsprintf( Texte, "(%s)", (LPCSTR)Priorite ) ; 
      
      DrawText( lpDraw->hDC, Texte, -1,
               &R, DT_RIGHT| DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX ) ;
               
      wsprintf( Texte, "%s", (LPCSTR)pEco->Nom() ) ; 
      DrawText( lpDraw->hDC, Texte, -1,
               &R, DT_LEFT| DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX ) ;
      }
}

void CPropEconomiseurs::OnSelchangeListeEco() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		switch( pEco->Priorite())
			{
			case JAMAIS             :
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO7 ) ;
				break ;

			case PRIORITE_MIN       :
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO6 ) ;
				break ;
			case PRIORITE_BASSE   	:
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO5 ) ;
				break ;
			case PRIORITE_HAUTE   	:
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO3 ) ;
				break ;
			case PRIORITE_MAX     	:
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO2 ) ;
				break ;
			case PRIORITE_NORMALE 	:
			default :			
				CheckRadioButton( IDC_RADIO2, IDC_RADIO7, IDC_RADIO4 ) ;
				break ;
			}
	    }
}

void CPropEconomiseurs::OnConfigurer() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Configure() ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}		
}

void CPropEconomiseurs::OnTest() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Active() ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio2() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( PRIORITE_MAX ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio3() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( PRIORITE_HAUTE ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio4() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( PRIORITE_NORMALE ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio5() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( PRIORITE_BASSE ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio6() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( PRIORITE_MIN ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

void CPropEconomiseurs::OnRadio7() 
{
	const	Indice	=	m_LB.GetCurSel() ;

	if( Indice != LB_ERR )
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)(m_LB.GetItemData( Indice )) ;
		pEco->Priorite( JAMAIS ) ;
		m_LB.InvalidateRect( NULL, TRUE ) ;
		SetModified() ;
		}
}

int CPropEconomiseurs::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer( 1, 1000, NULL ) ;
	return 0;
}

void	CPropEconomiseurs::OnTimer()
{
	_NbMinutes	++ ;

	// Rechercher la fenetre d'economiseur
	HWND hWnd	=	::FindWindow( "WindowsScreenSaverClass", NULL ) ;

	// Essayer de detecter si on a lance un nouveau screen-saver
	if ( ! hWnd )
		{
		_hOldWnd	=	0 ;
		return ;
		}

	if ( hWnd != _hOldWnd )
		{
		_hOldWnd	=	hWnd ;
	
		if ( _Liste.NbEconomiseurs() == 0 )
			_Liste.Init() ;

		// Verifier qu'il existe toujours
		CEconomiseur*	pEco	=	_Liste.PlusPrioritaire() ;

		CFileStatus	Status ;
		memset( &Status, 0, sizeof( Status )) ;

		if ( CFile::GetStatus( (LPCSTR)pEco->Chemin(),Status ) == 0 )
			{
			_Liste.Init() ;
			pEco	=	_Liste.PlusPrioritaire() ;
			}

		// Changer l'economiseur
		WritePrivateProfileString( "boot", "SCRNSAVE.EXE", pEco->Chemin(), "SYSTEM.INI" ) ;

		_NbMinutes	=	0 ;
		_Liste.SauveConfiguration() ;	
		}
}

void	CPropEconomiseurs::OnOK()
{
	_Liste.SauveConfiguration() ;	
}

			 
