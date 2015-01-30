// AnimationView.cpp : implementation of the CAnimationView class
//

#include "stdafx.h"
#include "Animation.h"

#include "AnimationDoc.h"
#include "AnimationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimationView

IMPLEMENT_DYNCREATE(CAnimationView, CFormView)

BEGIN_MESSAGE_MAP(CAnimationView, CFormView)
	//{{AFX_MSG_MAP(CAnimationView)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_COMMAND(ID_EDITION_MONTERLIMAGE, OnEditionMonterlimage)
	ON_COMMAND(ID_EDITION_DESCENDRELIMAGE, OnEditionDescendrelimage)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimationView construction/destruction

CAnimationView::CAnimationView()
	: CFormView(CAnimationView::IDD)
{
	//{{AFX_DATA_INIT(CAnimationView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	_IndiceImageCourante	=	0 ;
}

CAnimationView::~CAnimationView()
{
}

void CAnimationView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimationView)
	DDX_Control(pDX, IDC_LISTE, m_Liste);
	//}}AFX_DATA_MAP
}

BOOL CAnimationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAnimationView printing

BOOL CAnimationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAnimationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAnimationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAnimationView::OnPrint(CDC* pDC, CPrintInfo*)
{
	// TODO: add code to print the controls
}

/////////////////////////////////////////////////////////////////////////////
// CAnimationView diagnostics

#ifdef _DEBUG
void CAnimationView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAnimationView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CAnimationDoc* CAnimationView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimationDoc)));
	return (CAnimationDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimationView message handlers

int CAnimationView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DragAcceptFiles() ;

	return 0;
}

void CAnimationView::OnDropFiles(HDROP hDropInfo) 
{
	CWaitCursor Cr ;

	const int NbFichiers	=	::DragQueryFile( hDropInfo, -1, NULL, -1 ) ;

	for ( int i = 0; i < NbFichiers; i++) 
		{
		char Buffer[MAX_PATH] ;
		::DragQueryFile( hDropInfo, i, Buffer, sizeof( Buffer )) ;

		CString NomFichier( Buffer ) ;

		HBITMAP	hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(),
												NomFichier,
												IMAGE_BITMAP,
												0,0,
												LR_LOADFROMFILE ) ;

		if ( hBitmap )
			{
			CBitmap	*	pBitmap	= new CBitmap ;
			pBitmap->Attach( hBitmap ) ;

			// Image pour la liste
			HBITMAP hBmListe	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(),
												NomFichier,
												IMAGE_BITMAP,
												32,32,
												LR_LOADFROMFILE ) ;
			
			const int Index	= _ListeImages.Add( CBitmap::FromHandle( hBmListe ), RGB(0,0,0)) ;

			m_Liste.InsertItem( i, NomFichier, Index ) ;
			_NomsDeFichiers.Add( NomFichier ) ;
			_Bitmaps.Add( pBitmap ) ;
			}
		}

	SetTimer( 1, 100, NULL ) ;
	CFormView::OnDropFiles(hDropInfo);
}

void CAnimationView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	
	_ListeImages.Create( 32, 32, ILC_COLOR32, 0, 1  ) ;

	m_Liste.SetImageList( &_ListeImages, LVSIL_SMALL ) ;
}

void CAnimationView::OnTimer(UINT nIDEvent) 
{
	if ( _IndiceImageCourante > _Bitmaps.GetUpperBound())
		_IndiceImageCourante = 0 ;

	if ( _Bitmaps.GetSize())
		{
		CRect R ;
		::GetWindowRect( ::GetDlgItem( m_hWnd, IDC_ANIMATION ), R ) ;
		ScreenToClient( R ) ;

		BITMAP sBitmap ;
		CBitmap*	pBitmap	=	(CBitmap*)_Bitmaps[_IndiceImageCourante] ;
		_IndiceImageCourante ++ ;

		pBitmap->GetBitmap( &sBitmap ) ;

		CClientDC	Dc( this ) ;
		Dc.DrawState( CPoint( R.left+(R.Width()-sBitmap.bmWidth)/2, R.top+(R.Height()-sBitmap.bmHeight)/2),
					  CSize( sBitmap.bmWidth, sBitmap.bmHeight ),
					  pBitmap,
					  DSS_NORMAL );
		}


	CFormView::OnTimer(nIDEvent);
}

void CAnimationView::OnEditionMonterlimage() 
{
	const int IndiceImage	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;

	if ( IndiceImage > 0 )
		{
		KillTimer(1) ;

		CObject * pObject	=	_Bitmaps[IndiceImage] ;
		CObject * pObject2	=	_Bitmaps[IndiceImage-1] ;

		_Bitmaps[IndiceImage]	=	pObject2 ;
		_Bitmaps[IndiceImage-1]	=	pObject ;

		CString Chaine1		=	_NomsDeFichiers[IndiceImage] ;
		CString Chaine2		=	_NomsDeFichiers[IndiceImage-1] ;

		_NomsDeFichiers[IndiceImage]	=	Chaine2 ;
		_NomsDeFichiers[IndiceImage-1]	=	Chaine1 ;

		char Buffer1[_MAX_PATH] ;
		char Buffer2[_MAX_PATH] ;

		LV_ITEM		Item1, Item2 ;

		memset( &Item1, 0, sizeof( Item1 )) ;
		Item1.mask	=	LVIF_TEXT | LVIF_IMAGE ;
		Item1.iItem	=	IndiceImage ;
		Item1.iSubItem=	0 ;
		Item1.pszText=	Buffer1 ;
		Item1.cchTextMax= sizeof( Buffer1 ) ;
		

		m_Liste.GetItem(&Item1) ;


		memset( &Item2, 0, sizeof( Item2 )) ;
		Item2.mask	=	LVIF_TEXT | LVIF_IMAGE ;
		Item2.iItem	=	IndiceImage-1 ;
		Item2.iSubItem= 0 ;
		Item2.pszText=	Buffer2 ;
		Item2.cchTextMax= sizeof( Buffer2 ) ;
		
		m_Liste.GetItem(&Item2) ;

		Item1.iItem	=	IndiceImage-1 ;
		Item2.iItem	=	IndiceImage ;

		Item1.mask |= LVIF_STATE ;
		Item1.state	=	LVIS_FOCUSED | LVIS_SELECTED ;
		Item1.stateMask=LVIS_FOCUSED | LVIS_SELECTED ;	
		m_Liste.SetItem( &Item1 ) ;
		m_Liste.SetItem( &Item2 ) ;

		m_Liste.EnsureVisible( IndiceImage-1, FALSE ) ;
		SetTimer( 1, 100, NULL ) ;
		}
}

void CAnimationView::OnEditionDescendrelimage() 
{
	const int IndiceImage	=	m_Liste.GetNextItem( -1, LVNI_SELECTED ) ;

	if ( IndiceImage >= 0 && IndiceImage < _Bitmaps.GetUpperBound() )
		{
		KillTimer(1) ;

		CObject * pObject	=	_Bitmaps[IndiceImage] ;
		CObject * pObject2	=	_Bitmaps[IndiceImage+1] ;

		_Bitmaps[IndiceImage]	=	pObject2 ;
		_Bitmaps[IndiceImage+1]	=	pObject ;

		CString Chaine1		=	_NomsDeFichiers[IndiceImage] ;
		CString Chaine2		=	_NomsDeFichiers[IndiceImage+1] ;

		_NomsDeFichiers[IndiceImage]	=	Chaine2 ;
		_NomsDeFichiers[IndiceImage+1]	=	Chaine1 ;

		char Buffer1[_MAX_PATH] ;
		char Buffer2[_MAX_PATH] ;

		LV_ITEM		Item1, Item2 ;

		memset( &Item1, 0, sizeof( Item1 )) ;
		Item1.mask	=	LVIF_TEXT | LVIF_IMAGE ;
		Item1.iItem	=	IndiceImage ;
		Item1.iSubItem=	0 ;
		Item1.pszText=	Buffer1 ;
		Item1.cchTextMax= sizeof( Buffer1 ) ;
		

		m_Liste.GetItem(&Item1) ;


		memset( &Item2, 0, sizeof( Item2 )) ;
		Item2.mask	=	LVIF_TEXT | LVIF_IMAGE ;
		Item2.iItem	=	IndiceImage+1 ;
		Item2.iSubItem= 0 ;
		Item2.pszText=	Buffer2 ;
		Item2.cchTextMax= sizeof( Buffer2 ) ;
		
		m_Liste.GetItem(&Item2) ;

		Item1.iItem	=	IndiceImage+1 ;
		Item2.iItem	=	IndiceImage ;

		Item1.mask |= LVIF_STATE ;
		Item1.state	=	LVIS_FOCUSED | LVIS_SELECTED ;
		Item1.stateMask=LVIS_FOCUSED | LVIS_SELECTED ;	
		m_Liste.SetItem( &Item1 ) ;
		m_Liste.SetItem( &Item2 ) ;

		m_Liste.EnsureVisible( IndiceImage+1, FALSE ) ;
		SetTimer( 1, 100, NULL ) ;
		}
}

void CAnimationView::OnEditCopy() 
{
	const int	NbImages	=	_Bitmaps.GetSize() ;


	// Calcul de la taille de la nouvelle bitmap
	int	Hauteur	=	0 ;
	int	Largeur	=	0 ;

	for ( int i = 0; i < NbImages; i++)
		{
		BITMAP	sBitmap ;

		CBitmap*	pBitmap	=	(CBitmap*)_Bitmaps[i] ;

		pBitmap->GetBitmap( &sBitmap ) ;

		if ( sBitmap.bmHeight	> Hauteur )
			Hauteur = sBitmap.bmHeight ;

		Largeur += sBitmap.bmWidth ;
		}

	// Creation de la bitmap pour mettre dans le presse papier
	HDC	hDisplayDC	= CreateDC( "display", 0, 0, 0 ) ;
	HDC	hMemDC		=	CreateCompatibleDC( hDisplayDC ) ;
	HBITMAP	 hMemBitmap	=	CreateCompatibleBitmap( hDisplayDC, Largeur, Hauteur ) ;
	DeleteDC( hDisplayDC ) ;

	HBITMAP	hOldBitmap	=	(HBITMAP)SelectObject( hMemDC, hMemBitmap ) ;
	int x = 0 ;

	for ( i = 0; i < NbImages; i++)
		{
		HDC hMemDC2	=	CreateCompatibleDC( hMemDC ) ;
		CBitmap	*	pBitmap	=	(CBitmap*)_Bitmaps[i] ;
		BITMAP		sBitmap ;
		pBitmap->GetBitmap( &sBitmap ) ;

		HBITMAP	hOld	= (HBITMAP)SelectObject( hMemDC2, pBitmap->m_hObject ) ;

		BitBlt( hMemDC, x, 0, sBitmap.bmWidth, sBitmap.bmHeight,
				hMemDC2, 0, 0, SRCCOPY ) ;

		SelectObject( hMemDC2, hOld ) ;
		DeleteDC( hMemDC2 ) ;

		x += sBitmap.bmWidth ;
		}

	SelectObject( hMemDC, hOldBitmap );
	DeleteDC( hMemDC ) ;

	OpenClipboard() ;
	EmptyClipboard() ;
	SetClipboardData( CF_BITMAP, hMemBitmap ) ;
	CloseClipboard() ;
}

void CAnimationView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	

	// retailler la liste
	if ( IsWindow( m_Liste.m_hWnd ))
		m_Liste.MoveWindow( 0, 0, cx/2, cy, TRUE ) ;

	// retailler le rectangle d'affichage
	::MoveWindow( ::GetDlgItem( m_hWnd, IDC_ANIMATION ), cx/2, 0, cx/2, cy, TRUE ) ;
	
}
