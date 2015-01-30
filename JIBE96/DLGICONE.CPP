// DlgIcone.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "DlgIcone.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIcone dialog


CDlgIcone::CDlgIcone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIcone::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIcone)
	m_NomFichier = _T("");
	//}}AFX_DATA_INIT
}


void CDlgIcone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIcone)
	DDX_Control(pDX, IDC_ICONES, m_Liste);
	DDX_Text(pDX, IDC_EDIT1, m_NomFichier);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIcone, CDialog)
	//{{AFX_MSG_MAP(CDlgIcone)
	ON_BN_CLICKED(IDC_PARCOURIR, OnParcourir)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIcone message handlers

void CDlgIcone::OnParcourir() 
{
	CString	FiltreExtensions ;
	FiltreExtensions.LoadString( IDS_FILTRE_ICONES ) ;
	CFileDialog	Dlg(	TRUE,
					 	"ICO",
						m_NomFichier,
						OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_LONGNAMES,
						FiltreExtensions,
						this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		m_NomFichier	=	Dlg.GetPathName() ;
		UpdateData( FALSE ) ;
		RemplitIcones() ;
		}
}

void CDlgIcone::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDraw ) 
{
	if ( lpDraw->itemState & ODS_SELECTED )
		{
		HBRUSH	hBrush = CreateSolidBrush( GetSysColor( COLOR_HIGHLIGHT )) ;
			
		FillRect( lpDraw->hDC, &lpDraw->rcItem, hBrush ) ;
		DeleteObject( hBrush ) ;
		DrawFocusRect( lpDraw->hDC, &lpDraw->rcItem ) ;
		}
	else
		{
		HBRUSH hBrush = CreateSolidBrush( GetSysColor(COLOR_WINDOW)) ;
		FillRect( lpDraw->hDC, &lpDraw->rcItem, hBrush ) ;
		DeleteObject( hBrush ) ;
		}
				
			
	if ( lpDraw->itemID >= 0 )
		{
		HICON	hIcon =	ExtractIcon( AfxGetInstanceHandle(),
										m_NomFichier, lpDraw->itemID ) ;
		if ( ! hIcon )
			{
			WORD	Ind	=	lpDraw->itemID ;

			hIcon = ExtractAssociatedIcon( AfxGetInstanceHandle(),
								   m_NomFichier.GetBuffer(0),
								   &Ind ) ;
			m_NomFichier.ReleaseBuffer() ;
			}

		DrawIcon( lpDraw->hDC, lpDraw->rcItem.left + 2, lpDraw->rcItem.top + 2,
				  hIcon ) ;

		DestroyIcon( hIcon );
		}
}

void CDlgIcone::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemWidth	=	GetSystemMetrics( SM_CXICON ) + 4 ;
	lpMeasureItemStruct->itemHeight	=	GetSystemMetrics( SM_CYICON ) + 4 ;
}

BOOL CDlgIcone::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Liste.SetColumnWidth( GetSystemMetrics( SM_CXICON ) + 4 ) ;
	RemplitIcones() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// RemplitIcones
//	Remplissage de la listbox avec les icones. Comme la list box est owner
//	draw, on se contente d'ajouter un element par icone disponible, on les
//	dessinera directement a partir du nom de fichier et du numero d'element
/////////////////////////////////////////////////////////////////////////////
void CDlgIcone::RemplitIcones( void )
{
	m_Liste.SetRedraw( FALSE ) ;
	m_Liste.ResetContent() ;

	const int NbIcones = (int)ExtractIcon(	AfxGetInstanceHandle(),
											m_NomFichier, (unsigned int)-1 ) ;

	if ( NbIcones )
		for ( int i = 0; i < NbIcones; i++)
			m_Liste.AddString( " " );
	else
		{
		ExtractAssociatedIcon( AfxGetInstanceHandle(),
							   m_NomFichier.GetBuffer(0), (WORD*)&_IndiceIcone ) ;
		m_NomFichier.ReleaseBuffer() ;
		m_Liste.AddString( " " ) ;
		}


	if ( m_Liste.SetCurSel( _IndiceIcone ) == LB_ERR )
		m_Liste.SetCurSel( 0 ) ;

	m_Liste.SetRedraw( TRUE ) ;
	m_Liste.InvalidateRect( NULL, TRUE ) ;
}

void CDlgIcone::OnOK() 
{
	_IndiceIcone	=	m_Liste.GetCurSel() ;
	
	CDialog::OnOK();
}
