// UniverseCreationKitView.cpp : implementation of the CUniverseCreationKitView class
//

#include "stdafx.h"
#include "UniverseCreationKit.h"

#include "UniverseCreationKitDoc.h"
#include "UniverseCreationKitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TAILLE_TABLEAU(t)		(sizeof(t)/sizeof(t[0]))

typedef enum	T_TYPE {	T_STRING, T_INT, T_BOOL, T_FLOTTANT } ;

typedef struct
	{
	UINT	IdsString ;
	T_TYPE	TypeParametre ;
	LPVOID	Adresse ;
	HTREEITEM	hItem ;
	}
	T_PARAMETRE ;

T_PARAMETRE	ParametresUnivers[]=
	{
		{ IDS_3D, T_BOOL, 0, 0 },
		{ IDS_DISPLAY_LINES, T_BOOL, 0, 0 },
		{ IDS_DUST_SCATTERING, T_INT, 0, 0 },
		{ IDS_CHANGE_RESOLUTION, T_BOOL, 0, 0 },
		{ IDS_ESCAPE_VELOCITY, T_INT, 0, 0 },
		{ IDS_COMET_CREATION, T_INT, 0, 0 },
		{ IDS_COLLISION_SPEED, T_FLOTTANT, 0, 0 }
	} ;

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView

IMPLEMENT_DYNCREATE(CUniverseCreationKitView, CFormView)

BEGIN_MESSAGE_MAP(CUniverseCreationKitView, CFormView)
	//{{AFX_MSG_MAP(CUniverseCreationKitView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView construction/destruction

CUniverseCreationKitView::CUniverseCreationKitView()
	: CFormView(CUniverseCreationKitView::IDD)
{
	//{{AFX_DATA_INIT(CUniverseCreationKitView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CUniverseCreationKitView::~CUniverseCreationKitView()
{
}

void CUniverseCreationKitView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUniverseCreationKitView)
	DDX_Control(pDX, IDC_UNIVERSE, m_Display);
	DDX_Control(pDX, IDC_TREE1, m_Tree);
	//}}AFX_DATA_MAP
}

BOOL CUniverseCreationKitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView diagnostics

#ifdef _DEBUG
void CUniverseCreationKitView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUniverseCreationKitView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CUniverseCreationKitDoc* CUniverseCreationKitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUniverseCreationKitDoc)));
	return (CUniverseCreationKitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUniverseCreationKitView message handlers

void CUniverseCreationKitView::OnSize(UINT nType, int cx, int cy) 
{
	//CFormView::OnSize(nType, cx, cy);

	SetScrollRange( SB_VERT, 0, 0, TRUE ) ;
	SetScrollRange( SB_HORZ, 0, 0, TRUE ) ;

	if ( IsWindow( m_Tree ) && IsWindow( m_Display ))
		{
		CRect	R ;
		GetClientRect( R ) ;

		CRect	RectTree ;
		m_Tree.GetWindowRect( RectTree ) ;

		CRect RectDisplay ;
		m_Display.GetWindowRect( RectDisplay ) ;
		
		m_Tree.SetWindowPos( &wndTop, 0, 0, RectTree.Width(), R.Height() - 32, SWP_NOZORDER | SWP_NOMOVE ) ;

		m_Display.SetWindowPos( &wndTop, 0, 0, R.Width() - RectTree.Width() - 32, R.Height() - 32, SWP_NOZORDER | SWP_NOMOVE ) ;
		}
}

void CUniverseCreationKitView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	CRect	R ;
	GetClientRect( R ) ;

	OnSize( SIZE_RESTORED, R.Width(), R.Height()) ;

	RemplitListe() ;
}

void CUniverseCreationKitView::RemplitListe()
{
	m_Tree.DeleteAllItems() ;

	HTREEITEM	hRoot	=	m_Tree.GetRootItem() ;
	CString		String ;

	// Ajoute les parametres de l'univers
	String.LoadString( IDS_PARAMETRES_UNIVERS ) ;
	_hUniverseParameters = m_Tree.InsertItem( String ) ;

	for ( int i = 0; i < TAILLE_TABLEAU( ParametresUnivers ); i++)
		{
		String.LoadString( ParametresUnivers[i].IdsString ) ;

		ParametresUnivers[i].hItem	=	m_Tree.InsertItem( String, _hUniverseParameters ) ;

		switch( ParametresUnivers[i].Type )
			{
			case T_STRING :
				break ;

			case T_BOOL :
				break ;

			case T_INT :
				break ;

			case T_FLOTTANT :
				break ;
			}
		}

	m_Tree.Expand( _hUniverseParameters, TVE_EXPAND ) ;

	// Ajoute les planetes
	String.LoadString( IDS_PLANETS ) ;
	_hPlanets	=	m_Tree.InsertItem( String ) ;
}
