// MosaiqueView.cpp : implementation of the CMosaiqueView class
//

#include "stdafx.h"
#include "Mosaique.h"
#include "image.h"
#include "MosaiqueDoc.h"
#include "MosaiqueView.h"
#include "BitmapWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueView

IMPLEMENT_DYNCREATE(CMosaiqueView, CFormView)

BEGIN_MESSAGE_MAP(CMosaiqueView, CFormView)
	//{{AFX_MSG_MAP(CMosaiqueView)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_CREATE()
	ON_LBN_DBLCLK(IDC_LISTE, OnDblclkListe)
	ON_EN_CHANGE(IDC_NBCOLONNES, OnChangeNbcolonnes)
	ON_EN_CHANGE(IDC_NBLIGNES, OnChangeNblignes)
	ON_BN_CLICKED(IDC_PLUSHAUT, OnPlushaut)
	ON_BN_CLICKED(IDC_PLUSBAS, OnPlusbas)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_NOTIFY( DL_BEGINDRAG, IDC_LISTE, OnBeginDrag ) 
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueView construction/destruction

CMosaiqueView::CMosaiqueView()
	: CFormView(CMosaiqueView::IDD)
{
	//{{AFX_DATA_INIT(CMosaiqueView)
	m_Bordure = FALSE;
	m_NbLignes = 0;
	m_NbColonnes = 0;
	m_NomDeFichier = FALSE;
	m_Memo = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	_IndiceMemo	=	-1 ;
	_pBitmapWnd	=	0 ;
}

CMosaiqueView::~CMosaiqueView()
{
}

void CMosaiqueView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMosaiqueView)
	DDX_Control(pDX, IDC_LISTE, m_Liste);
//	DDX_Check(pDX, IDC_BORDURE, m_Bordure);
	DDX_Text(pDX, IDC_NBLIGNES, m_NbLignes);
	DDV_MinMaxInt(pDX, m_NbLignes, 1, 100);
	DDX_Text(pDX, IDC_NBCOLONNES, m_NbColonnes);
	DDV_MinMaxInt(pDX, m_NbColonnes, 1, 100);
	DDX_Check(pDX, IDC_NOMDEFICHIER, m_NomDeFichier);
	DDX_Text(pDX, IDC_MEMO, m_Memo);
	//}}AFX_DATA_MAP
}

BOOL CMosaiqueView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueView printing

BOOL CMosaiqueView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage( CalculNbPages()) ;
	return DoPreparePrinting(pInfo);
}

void CMosaiqueView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMosaiqueView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMosaiqueView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CMosaiqueDoc* pDoc	=	GetDocument() ;

	int Debut, Fin ;
	CalculDebutFin( pInfo->m_nCurPage, &Debut, &Fin ) ;

	int NoColonne	=	0 ;
	int NoLigne		=	0 ;

	const int LargeurPage	=	pDC->GetDeviceCaps( HORZRES ) ;
	const int HauteurPage	=	pDC->GetDeviceCaps( VERTRES ) ;

	const int LargeurColonne=	LargeurPage / pDoc->NbColonnes() ;
	const int HauteurLigne	=	HauteurPage / pDoc->NbLignes() ;

	for ( int i = Debut; i < Fin; i++)
		{
		CImage * pImage	=	pDoc->GetImage( i ) ;
		if ( ! pImage )
			continue ;


		CRect	R( NoColonne*LargeurColonne, NoLigne*HauteurLigne,
				 (NoColonne+1)*LargeurColonne, (NoLigne+1)*HauteurLigne) ;

		R.DeflateRect( 4, 4 );

		pImage->Dessine( *pDC,
						  R.left, R.top, R.Width(), R.Height() ) ;
		
		if ( NoColonne >= pDoc->NbColonnes()-1 )
			{
			NoColonne = 0 ;
			NoLigne ++ ;
			}
		else
			NoColonne ++ ;
		}
		
	CScrollView::OnPrint(pDC, pInfo);}

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueView diagnostics

#ifdef _DEBUG
void CMosaiqueView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMosaiqueView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMosaiqueDoc* CMosaiqueView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMosaiqueDoc)));
	return (CMosaiqueDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueView message handlers

void CMosaiqueView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	const int Indice	=	lpDrawItemStruct->itemID ;
	CMosaiqueDoc* pDoc	=	GetDocument() ;


	CDC	Dc ;
	Dc.Attach( lpDrawItemStruct->hDC ) ;

	CBrush	Brosse ;
	if ( lpDrawItemStruct->itemState & (ODS_SELECTED|ODS_FOCUS|ODS_CHECKED) )
		{
		Brosse.CreateSolidBrush( GetSysColor( COLOR_HIGHLIGHT )) ;
		Dc.SetTextColor( GetSysColor( COLOR_HIGHLIGHTTEXT )) ;
		Dc.SetBkColor( GetSysColor( COLOR_HIGHLIGHT )) ;
		}
	else
		{
		Brosse.CreateSolidBrush( GetSysColor( COLOR_WINDOW )) ;
		Dc.SetBkColor( GetSysColor( COLOR_WINDOW )) ;
		Dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT )) ;
		}

	Brosse.DeleteObject() ;
	
	if ( Indice >= 0)
		{
		CImage *	pImage	=	pDoc->GetImage( Indice ) ;
		if (! pImage )
			return ;


		if ( lpDrawItemStruct->itemAction & ODA_DRAWENTIRE )
			pImage->Dessine( Dc, lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top,
							  lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left,
							  lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top,
							  CENTREV ) ;

		Dc.SelectStockObject( ANSI_VAR_FONT ) ;
		Dc.DrawText( pImage->Nom(), &lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_RIGHT | DT_VCENTER ) ;
		}

	Dc.Detach() ;
}

void CMosaiqueView::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	CRect  R ;
	GetClientRect( R ) ;
	lpMeasureItemStruct->itemHeight	=	64 ;
	lpMeasureItemStruct->itemWidth	=	R.Width() ;

	//CFormView::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CMosaiqueView::OnDropFiles( HDROP hDrop ) 
{
	CMosaiqueDoc* pDoc	=	GetDocument() ;
	const int NbFichiers	=	DragQueryFile(hDrop, (UINT)-1, NULL, NULL ) ;

	for ( int i = 0; i < NbFichiers; i++)
		{
		char NomFichier[ _MAX_PATH ] ;

		DragQueryFile( hDrop, i, NomFichier, sizeof( NomFichier )) ;

		if ( pDoc->AjouteImage( NomFichier ))
			{
			// AJouter le fichier dans la liste
			m_Liste.AddString( "" ) ;
			}
		}

	DragFinish( hDrop ) ;
}




int CMosaiqueView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DragAcceptFiles( TRUE ) ;	
	return 0;
}

void CMosaiqueView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	MakeDragList( m_Liste.m_hWnd ) ;
	}

void CMosaiqueView::OnDblclkListe() 
{
	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	CMosaiqueDoc* pDoc	=	GetDocument() ;
	CImage*	pImage	=	pDoc->GetImage(Selectionnee) ;

	if ( ! pImage )
		return ;
	
	if ( ! _pBitmapWnd )
		_pBitmapWnd	=	new CBitmapWnd ;

	if ( ! IsWindow( *_pBitmapWnd ))
		{
		const char * pClass	=	AfxRegisterWndClass( CS_VREDRAW | CS_HREDRAW,
													  LoadCursor( NULL, IDC_ARROW ),
													  (HBRUSH)(COLOR_WINDOW + 1)
													) ;

		_pBitmapWnd->CreateEx( WS_EX_TOOLWINDOW, pClass, "", WS_CAPTION | WS_SYSMENU |  WS_VISIBLE | WS_POPUP | WS_THICKFRAME,
							   0, 0, 500, 500, *this, NULL, NULL	
							 ) ;
		}

	_pBitmapWnd->SetImage( pImage ) ;
}


afx_msg void CMosaiqueView::OnBeginDrag( NMHDR * pNotifyStruct, LRESULT * result )
	{
	}

void CMosaiqueView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CMosaiqueDoc* pDoc	=	GetDocument() ;
	m_Liste.ResetContent() ;	

	const int NbImages = pDoc->NbImages() ;

	for ( int i = 0; i < NbImages; i++)
		m_Liste.AddString( "" ) ;
	
	m_NbLignes	=	pDoc->NbLignes() ;
	m_NbColonnes=	pDoc->NbColonnes() ;

	UpdateData( FALSE ) ;
}

void CMosaiqueView::CalculDebutFin(int NoPage, int * pDebut, int * pFin)
{
	CMosaiqueDoc* pDoc = GetDocument();
	const int NbImages	=	pDoc->NbImages() ;
	const int NbImagesParPage	=	pDoc->NbLignes() * pDoc->NbColonnes() ;

	*pDebut	=	(NoPage-1) * NbImagesParPage ;
	if ( *pDebut >= NbImages )
		*pDebut	=	NbImages - 1 ;

	*pFin	=	*pDebut + NbImagesParPage ;

	if ( *pFin >= NbImages )
		*pFin	=	NbImages - 1 ;
}

int CMosaiqueView::CalculNbPages()
{
	CMosaiqueDoc* pDoc = GetDocument();
	const int NbImages	=	pDoc->NbImages() ;

	const int NbImagesParPage	=	pDoc->NbLignes() * pDoc->NbColonnes() ;

	return ( NbImages + NbImagesParPage - 1 ) / NbImagesParPage ;
}

void CMosaiqueView::OnChangeNbcolonnes() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	UpdateData( TRUE ) ;
	pDoc->NbColonnes( m_NbColonnes ) ;
}

void CMosaiqueView::OnChangeNblignes() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	UpdateData( TRUE ) ;
	pDoc->NbLignes( m_NbLignes ) ;
}

BOOL CMosaiqueView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	if ( wParam == IDC_LISTE )
		{
		DRAGLISTINFO * pDragInfo	=	(DRAGLISTINFO *)lParam ;

		switch( pDragInfo->uNotification )
			{
			case DL_BEGINDRAG :
				return TRUE ;

			case DL_CANCELDRAG :
				break ;

			case DL_DRAGGING :
				break ;

			case DL_DROPPED :
				break ;
			}
		}
	return CFormView::OnNotify(wParam, lParam, pResult);
}

BOOL CMosaiqueView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( wParam == IDC_LISTE )
		{
		DRAGLISTINFO * pDragInfo	=	(DRAGLISTINFO *)lParam ;

		switch( pDragInfo->uNotification )
			{
			case DL_BEGINDRAG :
				return TRUE ;

			case DL_CANCELDRAG :
				break ;

			case DL_DRAGGING :
				break ;

			case DL_DROPPED :
				break ;
			}
		}

	return CFormView::OnCommand(wParam, lParam);
}

void CMosaiqueView::OnPlushaut() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	if ( pDoc->PlusHaut( Selectionnee ))
		{
		CRect R ;
		m_Liste.GetItemRect( Selectionnee, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.GetItemRect( Selectionnee-1, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.SetCurSel( Selectionnee - 1 ) ;
		}
}

void CMosaiqueView::OnPlusbas() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	if ( pDoc->PlusBas( Selectionnee ))
		{
		CRect R ;
		m_Liste.GetItemRect( Selectionnee, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.GetItemRect( Selectionnee+1, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.SetCurSel( Selectionnee + 1 ) ;
		}
}

void CMosaiqueView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	

	if ( IsWindow( m_Liste ))
		{
		CRect R ;
		m_Liste.GetClientRect(R) ;

		R.bottom	=	R.top + cy - 8 ;

		m_Liste.SetWindowPos( 0, 0, 0, R.Width(), R.Height(), SWP_NOMOVE ) ;
		}
}

void CMosaiqueView::OnButton3() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	if ( pDoc->Deplace( _IndiceMemo, Selectionnee ))
		{
		CRect R ;
		m_Liste.GetItemRect( Selectionnee, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.GetItemRect( Selectionnee+1, R ) ;
		m_Liste.InvalidateRect( R, TRUE ) ;

		m_Liste.SetCurSel( Selectionnee ) ;
		_IndiceMemo	=	Selectionnee ;
		}
}

void CMosaiqueView::OnEditCopy() 
{
	CMosaiqueDoc* pDoc = GetDocument();

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	if ( ! OpenClipboard())
		return ;

	CString Texte	=	pDoc->GetImage( Selectionnee )->Nom() ;

	HANDLE	hText	=	GlobalAlloc( GMEM_ZEROINIT, Texte.GetLength() + 1 ) ;
	LPSTR	lpText	=	(LPSTR)GlobalLock( hText ) ;
	strcpy( lpText,   Texte ) ;
	GlobalUnlock( hText ) ;
	
	SetClipboardData( CF_TEXT, hText) ;

	CloseClipboard() ;
}

void CMosaiqueView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		pCmdUI->Enable( FALSE ) ;
	else
		pCmdUI->Enable( TRUE ) ;	
}

void CMosaiqueView::OnEditCut() 
{
	OnEditCopy() ;

	CMosaiqueDoc* pDoc = GetDocument();

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( Selectionnee == LB_ERR )
		return ;

	pDoc->SupprimeImage( Selectionnee ) ;
	m_Liste.DeleteString( Selectionnee ) ;
}

void CMosaiqueView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	OnUpdateEditCopy( pCmdUI ) ;
	
}

void CMosaiqueView::OnEditPaste() 
{
	if ( ! OpenClipboard())
		return ;

	HANDLE	hText	=	GetClipboardData( CF_TEXT ) ;

	const int 	Selectionnee	=	 m_Liste.GetCurSel() ;

	if ( hText )
		{
		CMosaiqueDoc* pDoc = GetDocument();
		LPSTR lpTexte	=	(LPSTR)GlobalLock(hText) ;
		pDoc->AjouteImage( Selectionnee, lpTexte) ;

		GlobalUnlock( hText ) ;
		m_Liste.InsertString( Selectionnee, "" ) ;
		m_Liste.Invalidate() ;
		}

	CloseClipboard() ;
}

void CMosaiqueView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
