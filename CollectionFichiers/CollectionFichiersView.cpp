// CollectionFichiersView.cpp : implementation of the CCollectionFichiersView class
//

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "mainfrm.h"

#include "CollectionFichiersDoc.h"
#include "CollectionFichiersView.h"
#include "Choosfol.h"
#include "ListeAttributs.h"
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersView

IMPLEMENT_DYNCREATE(CCollectionFichiersView, CFormView)

BEGIN_MESSAGE_MAP(CCollectionFichiersView, CFormView)
	//{{AFX_MSG_MAP(CCollectionFichiersView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FICHIERS_AJOUTER, OnFichiersAjouter)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersView construction/destruction

CCollectionFichiersView::CCollectionFichiersView()
	: CFormView(IDD_COLLECTIONFICHIERS_FORM)
{
	//{{AFX_DATA_INIT(CCollectionFichiersView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CCollectionFichiersView::~CCollectionFichiersView()
{
}

void CCollectionFichiersView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCollectionFichiersView)
	DDX_Control(pDX, IDC_LISTE, m_Liste);
	//}}AFX_DATA_MAP
}

BOOL CCollectionFichiersView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CCollectionFichiersView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	if ( ! IsWindow( _HeaderCtrl ))
		{
		// Remplace le rectangle par un header
		CRect Rect ;
		HWND	hWnd	=	::GetDlgItem( *this, IDC_HEADER ) ;
		::GetWindowRect( hWnd, &Rect ) ;
		::DestroyWindow( hWnd ) ;

		ScreenToClient( Rect ) ;

		// Cree a la place un header Ctrl
		_HeaderCtrl.Create( WS_CHILD | WS_BORDER | WS_VISIBLE | HDS_HOTTRACK | HDS_DRAGDROP | HDS_FULLDRAG | HDS_HORZ,
							Rect,
							this, 
							IDC_HEADER ) ;

		_HeaderCtrl.SetFont( CFont::FromHandle((HFONT)GetStockObject( ANSI_VAR_FONT ))) ;

		_ImageList.Create( 16, 16, ILC_MASK | ILC_COLOR32 , 0, 4 ) ;
		m_IndiceRoot				=	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_ICON2 )) ;
		m_IndiceRootSelectionne		=	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_ICON3 )) ;
		m_IndiceElement				=	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_ICON1 )) ;
		m_IndiceElementSelectionne	=	_ImageList.Add( AfxGetApp()->LoadIcon( IDI_ICON4 )) ;

		m_Liste.SetImageList( &_ImageList, TVSIL_NORMAL ) ;
		m_Liste.SetHeaderCtrl( &_HeaderCtrl ) ;
		}	

	}
/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersView printing

BOOL CCollectionFichiersView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCollectionFichiersView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCollectionFichiersView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCollectionFichiersView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersView diagnostics

#ifdef _DEBUG
void CCollectionFichiersView::AssertValid() const
{
	CFormView::AssertValid();
}

void CCollectionFichiersView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CCollectionFichiersDoc* CCollectionFichiersView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCollectionFichiersDoc)));
	return (CCollectionFichiersDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersView message handlers

void CCollectionFichiersView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	CRect	RClient ;
	GetClientRect( RClient ) ;
	
	if ( IsWindow( m_Liste ))
		{
		CRect R	;
		m_Liste.GetWindowRect( R ) ;
		ScreenToClient( R ) ;

		int EcartX	=	( R.left - RClient.left ) ;
		int	EcartY	=	( RClient.bottom - R.bottom ) ;
		
		m_Liste.MoveWindow( R.left, R.top, RClient.Width() - (EcartX*2), 
							RClient.Height() - R.top- EcartY,
							TRUE ) ;
		}

	if ( IsWindow( _HeaderCtrl ))
		{
		CRect R	;
		_HeaderCtrl.GetWindowRect( R ) ;
		ScreenToClient( R ) ;

		int EcartX	=	( R.left - RClient.left ) ;
		
		_HeaderCtrl.MoveWindow( R.left, R.top, RClient.Width() - (EcartX*2), 
								R.Height(),
								TRUE ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute une liste de fichiers
///////////////////////////////////////////////////////////////////////////////
void CCollectionFichiersView::OnFichiersAjouter() 
{
	// Choisi le chemin de depart
	CChooseFolder dlg( NULL, IDS_AJOUT_FICHIERS, this ) ;

	if ( dlg.DoModal() == IDCANCEL )
		return ;

	CMapStringToString	ListeAttributsCommuns ;
	ListeAttributsCommuns.SetAt( RACINE, dlg.GetDirName() ) ;

	// Choisi la liste d'attributs communs
	CListeAttributs	dlgAttributs( this,  ListeAttributsCommuns) ;
	if ( dlgAttributs.DoModal() == IDCANCEL )
		return ;

	CCollectionFichiersDoc	* pDoc	=	GetDocument() ;

	pDoc->ScanneDirectory( dlg.GetDirName(), ListeAttributsCommuns, this ) ;
}	

void CCollectionFichiersView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CWaitCursor w ;

	if (! IsWindow( _HeaderCtrl ))
		return ;

	SetHeaderCtrl() ;
	m_Liste.DeleteAllItems() ;
	CCollectionFichiersDoc *pDoc	=	GetDocument() ;

	// Filtre
	CString	AttributFiltre ;
	CString TexteFiltre ;
	pDoc->GetFiltre( AttributFiltre, TexteFiltre ) ;

	
	// Retrouve sur quel attribut les elements sont regroupes
	CString	Tri		=	GetNomAttributTri() ;
	
	// Retrouve la liste de toutes les valeurs de l'attribut de tri
	CStringArray ListeAttributs	;
	pDoc->GetListeValeurs( Tri , AttributFiltre, TexteFiltre,ListeAttributs ) ;
		
	if ( ListeAttributs.GetSize() == 0 )
		return ;

	CArray<HTREEITEM, HTREEITEM>	HItems ;
	HItems.SetSize( ListeAttributs.GetSize()) ;

	m_Liste.SetRedraw( FALSE ) ;
	

	// Ajoute les elements racines
	for ( int i = 0; i < ListeAttributs.GetSize(); i++)
		HItems[i]	=	m_Liste.InsertItem( LVIF_TEXT | LVIF_IMAGE,
											ListeAttributs[i], m_IndiceRoot, m_IndiceRootSelectionne, 0, 0, 0, TVI_ROOT, TVI_LAST ) ;


	// Ajoute les elements un par un, dans la racine correspondante
	CObArray & TableauElements	=	pDoc->GetListeElements() ;

	for ( i = 0; i < TableauElements.GetSize(); i++)
		{
		CElement * pElement =	(CElement*)TableauElements[i] ;
		if ( pElement->ConvientPourFiltre( AttributFiltre, TexteFiltre ))
			{
			CString	ValeurAttribut	=	pElement->GetAttribut( Tri ) ;

			int Indice	= -1;
			// Recherche dans le tableau
			for ( int j = 0; j < ListeAttributs.GetSize(); j++)
				{
				if ( ListeAttributs[j] == ValeurAttribut )
					{
					Indice	=	j ;
					break ;
					}
				}

			if (Indice != -1 )
				{
				HTREEITEM hItem =m_Liste.InsertItem( TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM, 
									ValeurAttribut, 
									m_IndiceElement, m_IndiceElementSelectionne, 
									0, 0, (LPARAM)pElement, HItems[Indice], TVI_LAST ) ;
				// Retrouve l'adresse de l'item
				TV_ITEM Item ;
				Item.mask	=	TVIF_PARAM ;
				Item.hItem	=	hItem;
				Item.lParam	=	0 ;
				m_Liste.GetItem( &Item ) ;
				}	
			}
		}

	m_Liste.SetRedraw( TRUE  ) ;
	m_Liste.Invalidate() ;
}


///////////////////////////////////////////////////////////////////////////////
// Construit la liste des header a partir de tous les attributs references
///////////////////////////////////////////////////////////////////////////////
void CCollectionFichiersView::SetHeaderCtrl()
{
	CCollectionFichiersDoc *pDoc	=	GetDocument() ;
	
	if ( ! IsWindow( _HeaderCtrl))
		return ;

	CStringArray & Attributs	=	CElement::GetTousAttributs() ;
	CUIntArray	 & Largeurs		=	pDoc->GetTableauLargeurs() ;
	CUIntArray	 & Ordre		=	pDoc->GetTableauOrdre() ;

	const int NB	=	_HeaderCtrl.GetItemCount() ;
	for ( int i = 0; i< NB; i++)
		_HeaderCtrl.DeleteItem(0) ;

	// Ajoute les nouveaux attributs
	for ( i = 0; i < Attributs.GetSize(); i++)
		{
		HDITEM	item ;
		item.mask		=	HDI_TEXT  | HDI_WIDTH | HDI_FORMAT /*| HDI_ORDER */;
		item.pszText	=	(char*)(const char*)Attributs[i] ;
		item.fmt		=	HDF_LEFT ;
		item.cxy		=	i < Largeurs.GetSize() ? (int)Largeurs[i] : 200 ;
		item.iOrder		=	i < Ordre.GetSize() ? (int)Ordre[i] : i + Ordre.GetSize() ;
		_HeaderCtrl.InsertItem( i, &item ) ;
		}
}

BOOL CCollectionFichiersView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	*pResult	=	0 ;
	if ( wParam == IDC_HEADER )
		{
		NMHEADER * pNotif	=	(NMHEADER*)lParam ;
		NotificationHeader( pNotif ) ;
		}

	return CFormView::OnNotify(wParam, lParam, pResult);
}




///////////////////////////////////////////////////////////////////////////////
// Gestion de la notification du header
///////////////////////////////////////////////////////////////////////////////
void CCollectionFichiersView::NotificationHeader(NMHEADER *pNotif)
{
	switch( pNotif->hdr.code )
		{
		case HDN_ENDTRACK :
		case HDN_ENDDRAG :
			{
			CCollectionFichiersDoc *pDoc	=	GetDocument() ;
			
			m_Liste.Invalidate() ;

			// Retrouve l'ordre des colonnes
			const int NbItems	=	_HeaderCtrl.GetItemCount() ;

			int	*	pOrder		=	new int[NbItems] ;
			if ( ! pOrder )
				return ;

			_HeaderCtrl.GetOrderArray( pOrder, NbItems ) ;
			pDoc->MemoriseOrdreColonnes( pOrder, NbItems ) ;
			delete [] pOrder ;
			
			// Memorise les tailles de colonnes
			int * pLargeurs		=	new int[NbItems] ;
			if ( ! pLargeurs )
				return ;

			for ( int i = 0;i < NbItems; i++)
				{
				HDITEM	Item ;
				Item.mask		=	HDI_WIDTH ;
				_HeaderCtrl.GetItem( i, &Item ) ;
				pLargeurs[i]	=	Item.cxy ;
				}

			pDoc->MemoriseLargeursColonnes( pLargeurs, NbItems ) ;
			delete[]	pLargeurs ;

			pDoc->UpdateAllViews(0) ;
//			m_Liste.Invalidate() ;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////
// Retrouve le nom de l'attribut sur lequel se fait le tri
///////////////////////////////////////////////////////////////////////////////
CString CCollectionFichiersView::GetNomAttributTri()
{
	CCollectionFichiersDoc *pDoc	=	GetDocument() ;
	const int iTri					=	pDoc->GetAttributRegroupe() ;

	const int NB	=	_HeaderCtrl.GetItemCount() ;
	char Buffer[1024] ;
	Buffer[0]		=	0 ;

	for ( int i = 0; i < NB; i++ )
		{
		HDITEM	Item ;
		Item.mask		=	HDI_TEXT | HDI_ORDER ;
		Item.pszText	=	Buffer ;
		Item.cchTextMax	=	sizeof( Buffer ) ;
		_HeaderCtrl.GetItem( i, &Item ) ;
		char *c = Buffer ;
		}

	HDITEM	Item ;
	Item.mask		=	HDI_TEXT | HDI_ORDER ;
	Item.pszText	=	Buffer ;
	Item.cchTextMax	=	sizeof( Buffer ) ;
	_HeaderCtrl.GetItem( 0, &Item ) ;
	
	return Buffer ;
}
