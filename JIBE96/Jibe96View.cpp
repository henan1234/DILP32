// Jibe96View.cpp : implementation of the CJibe96View class
//

#include "stdafx.h"
#include "Jibe96.h"

#include "Jibe96Doc.h"
#include "Jibe96View.h"
#include "mainfrm.h"
#include "lpibitmap.h"

#include "iconeNote.h"
#include "iconehorloge.h"
#include "iconeDisque.h"
#include "iconeRAM.h"
#include "iconemem.h"
#include "iconeSwap.h"
#include "IconeGroupe.h"
#include "iconeSeparateur.h"
#include "preferences.h"
#include "preferencesDlg.h"
#include "iconesurveille.h"
#include "IconeCommande.h"
#include "IconeBouton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	DEPLACE_FENETRE		0
#define DEPLACE_ICONE		1
#define OUVRE_FENETRE		2
#define	ACTIVATION_AUTO		3

CJibe96View * CJibe96View::_thisView = 0 ;


/////////////////////////////////////////////////////////////////////////////
// CJibe96View
int	CalculeComposante( int i, int DepMin, int DepMax, int ArrMin, int ArrMax )
	{
	i	-=	DepMin ;
	i	=	i * (ArrMax-ArrMin) /  (DepMax-DepMin ) ;
	i	+=	ArrMin ;

	return i ;
}

COLORREF	CalculeCouleur( int i, int Min, int Max, COLORREF CouleurMin, COLORREF CouleurMax )
	{
	return	RGB( CalculeComposante( i, Min, Max, GetRValue( CouleurMin ), GetRValue( CouleurMax )),
				 CalculeComposante( i, Min, Max, GetGValue( CouleurMin ), GetGValue( CouleurMax )),
				 CalculeComposante( i, Min, Max, GetBValue( CouleurMin ), GetBValue( CouleurMax ))) ;
	}


IMPLEMENT_DYNCREATE(CJibe96View, CView)

BEGIN_MESSAGE_MAP(CJibe96View, CView)

	//{{AFX_MSG_MAP(CJibe96View)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_COMMAND(ID_FG_NOUVELLEICNE_NOTE, OnFgNouvelleicneNote)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_SUPPRIMER, OnSupprimer)
	ON_COMMAND(ID_PLUSBAS, OnPlusbas)
	ON_UPDATE_COMMAND_UI(ID_PLUSBAS, OnUpdatePlusbas)
	ON_COMMAND(ID_PLUSHAUT, OnPlushaut)
	ON_UPDATE_COMMAND_UI(ID_PLUSHAUT, OnUpdatePlushaut)
	ON_COMMAND(ID_HEURE, OnHeure)
	ON_COMMAND(ID_FG_DATE, OnDate)
	ON_COMMAND(ID_PLACEDISQUE, OnPlacedisque)
	ON_COMMAND(ID_FG_NOUVELLEICNE_PLACERAM, OnFgNouvelleicnePlaceram)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FG_NOUVELLEICNE_PLACEMMOIRE, OnFgNouvelleicnePlacemmoire)
	ON_WM_SETCURSOR()
	ON_COMMAND(ID_FG_FICHIERDCHANGE, OnFgFichierdchange)
	ON_COMMAND(ID_SEPARATEUR, OnSeparateur)
	ON_COMMAND(ID_FG_PRFRENCES, OnFgPrfrences)
	ON_COMMAND(ID_GROUPE, OnGroupe)
	ON_WM_KILLFOCUS()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_COMMAND(ID_SURVEILLE_REP, OnSurveilleRep)
	ON_COMMAND(IDM_COMMANDE, OnCommande)
	ON_NOTIFY(TTN_NEEDTEXT, 0, OnTTNeedText)
	ON_COMMAND(IDM_BOUTON, OnBouton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJibe96View construction/destruction

CJibe96View::CJibe96View()
:_BrushOrg(0,0)
{
//	m_pSelection = NULL;
	// TODO: add construction code here
	ASSERT( ! _thisView ) ;
	_thisView	=	this ;

	_pFenetreIcone	=	0 ;
	_pSelectionnee	=	0 ;
	_hOldRegion		=	0 ;
	_pIconeFenetre	=	0 ;
	}

CJibe96View::~CJibe96View()
{
	if ( _thisView == this )
		_thisView	=	0 ;
}

BOOL CJibe96View::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = WS_CHILD | WS_VISIBLE ;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJibe96View drawing

void CJibe96View::OnDraw(CDC* pDC)
{
	CJibe96Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CPoint	Pt( PosDepart() ) ;	

	const int	EcartY		=	GetSystemMetrics( SM_CYBORDER ) ;
	const int	NbIcones	=	pDoc->NbIcones() ;

	for ( int i = 0; i < NbIcones; i++)
		{
		CIcone * pIcone	=	pDoc->GetIcone( i ) ;
		ASSERT_VALID( pIcone ) ;
		pIcone->Affiche( *pDC, Pt, (_pSelectionnee	== pIcone ) ) ;

		ShiftPos( Pt, pIcone ) ;
		}

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CJibe96CntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

/*	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CJibe96CntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
*/
}

void CJibe96View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CJibe96Doc*	pDoc	=	GetDocument() ;
	
	if ( pDoc->NbIcones()	==	0 )
		{
			MessageBeep( MB_ICONQUESTION ) ;
			CString	Message ;
			Message.LoadString( IDS_CREER_ICONES ) ;

			if ( MessageBox( Message, "Jibe", MB_YESNO | MB_ICONQUESTION ) == IDYES )
				{
				CWaitCursor		Wait ;
				// Creer des icones par defaut
				AjouteIcone( new CIconeDate ) ;
				AjouteIcone( new CIconeHorloge ) ;
				AjouteIcone( new CIconeSeparateur ) ;
				AjouteIcone( new CIconeMem ) ;
				AjouteIcone( new CIconeRAM ) ;
				AjouteIcone( new CIconeSeparateur ) ;
				AjouteIcone( new CIconeDisque ) ;
				
				AjouteIcone( new CIconeSeparateur ) ;

				CIconeGroupe	*	pGroupe =	new	CIconeGroupe ;
				pGroupe->AjouteProgrammes() ;
				AjouteIcone( pGroupe ) ;
				AjouteIcone( new CIconeSeparateur ) ;
				
				CIconeNote*	pNote	=	new CIconeNote ;
				CString		Texte ;		Texte.LoadString( IDS_AIDE ) ;
				pNote->SetTexte( Texte ) ;
				AjouteIcone( pNote ) ;

				AfxMessageBox( IDS_ICONES_CREEES, MB_OK | MB_ICONINFORMATION ) ;
				}
		}

	// TODO: remove this code when final selection model code is written
//	m_pSelection = NULL;    // initialize selection
	
	SetTipsOnIcons() ;
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

/*BOOL CJibe96View::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CJibe96CntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

//	return pDocItem == m_pSelection;
}
*/

/*
void CJibe96View::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CJibe96CntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CJibe96CntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CJibe96Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CJibe96CntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

//		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}
*/


// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CJibe96View::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
/*	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
*/
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CJibe96View::OnSetFocus(CWnd* pOldWnd)
{
/*	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}
  */
	CView::OnSetFocus(pOldWnd);
}

void CJibe96View::OnSize(UINT nType, int cx, int cy)
{
	CRect	R(0,0,0,0) ;

	CView::OnSize(nType, cx, cy);
/*	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
  */
	SetTipsOnIcons() ;
}

/////////////////////////////////////////////////////////////////////////////
// CJibe96View diagnostics

#ifdef _DEBUG
void CJibe96View::AssertValid() const
{
	CView::AssertValid();
}

void CJibe96View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJibe96Doc* CJibe96View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJibe96Doc)));
	return (CJibe96Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJibe96View message handlers

void CJibe96View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu	Menu ;
	
	_pSelectionnee	=	GetIconeFromPoint( point ) ;

	ClientToScreen( &point ) ;

	if ( _pSelectionnee )
		{
		const	UINT IdMenu	=	_pSelectionnee->GetMenuID() ;
		if ( IdMenu != 0)
			{
			VERIFY( Menu.LoadMenu( IdMenu )) ;

			Menu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON,
												 point.x, point.y,
												 this, 0 ) ;
			}
		}
	else
		{
		VERIFY( Menu.LoadMenu( IDR_MENU_DROITE )) ;
		Menu.GetSubMenu(0)->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_LEFTBUTTON,
											 point.x, point.y,
											 AfxGetMainWnd(),
											 0 ) ;
		}
	CView::OnRButtonDown(nFlags, point);
}

BOOL CJibe96View::OnEraseBkgnd(CDC* pDC) 
{
	int	Fond ;

	GetPreferences()->LitPreference( "Fond", Fond, 0 ) ;

	CRect	R ;
	GetClientRect( R ) ;

	{
	CLPIBitmap	Bitmap( CIcone::Colors64K() ? MAKEINTRESOURCE(IDB_TITRE) : MAKEINTRESOURCE( IDB_TITRE16 )) ;
	Bitmap.Affiche( pDC, R.left, R.top ) ;
	R.top +=	Bitmap.Hauteur() ;
	}


	switch( Fond )
		{
		case 0 :
			{
			// Texture
			CLPIBitmap Bitmap( CIcone::Colors64K() ? IDB_FOND : IDB_FOND16 ) ;
			Bitmap.Mosaique( pDC, R ) ;
			}
			break ;

		case 1 :
			{
			// Degrade
			const COLORREF	Debut	=	::GetSysColor( COLOR_3DLIGHT ) ;
			const COLORREF	Fin		=	::GetSysColor( COLOR_3DSHADOW ) ;
			const int	LargeurBande	=	8 ;

			if ( R.Width() < R.Height())
				{
					for (	int i = R.left; i < R.right; i+= LargeurBande )
						{
						CBrush	Brosse( CalculeCouleur( i, R.left, R.right, Debut, Fin )) ;

						CBrush	*	pOld	=	pDC->SelectObject( &Brosse ) ;
						pDC->PatBlt( i, R.top, LargeurBande, R.Height(), PATCOPY ) ;
						pDC->SelectObject( pOld ) ;
						Brosse.DeleteObject() ;
						}
				}
			else
				{
					for (	int i = R.top; i < R.bottom; i+= LargeurBande )
						{
						CBrush	Brosse( CalculeCouleur( i, R.top, R.bottom, Debut, Fin )) ;

						CBrush	*	pOld	=	pDC->SelectObject( &Brosse ) ;
						pDC->PatBlt( R.left, i, R.Width(), LargeurBande, PATCOPY ) ;
						pDC->SelectObject( pOld ) ;
						Brosse.DeleteObject() ;
						}
				}
			}
			break ;

		default :
			return CView::OnEraseBkgnd( pDC ) ;
		}	



	return TRUE ;

}

int CJibe96View::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	DragAcceptFiles( TRUE ) ;
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect	R ;
	GetClientRect(R) ;

	return 0;
}

void CJibe96View::SetSide( UINT Side )
{
	SetTipsOnIcons() ;
}


void CJibe96View::OnFgNouvelleicneNote() 
{
	AjouteIcone( new CIconeNote ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Ajoute une icone dans la vue
///////////////////////////////////////////////////////////////////////////////
void CJibe96View::AjouteIcone( CIcone * pIcone )
{	
	CJibe96Doc*	pDoc	=	GetDocument() ;

	// Calculer la position de l'icone
	const int	NbIcones		=	pDoc->NbIcones() ;
	const int	EcartY			=	GetSystemMetrics( SM_CYBORDER ) ;
	CPoint		Pos(PosDepart()) ;
	
	for ( int i = 0; i < NbIcones; i++)
		ShiftPos( Pos, pIcone ) ;
		
	pDoc->AjouteIcone( pIcone ) ;
	_pSelectionnee	=	pIcone ;
	SetTipsOnIcons() ;

	InvalidateRect( NULL, FALSE ) ;
}

void CJibe96View::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CIcone*			pIcone	=	GetIconeFromPoint( point ) ;

	if ( pIcone )
		{
		if ( pIcone->ExecuteCommand())
			{
			InvalidateRect( NULL, TRUE ) ;
			GetDocument()->SetModifiedFlag() ;
			SetTipsOnIcons() ;
			}
		}
	
	CView::OnLButtonDblClk(nFlags, point);
}

///////////////////////////////////////////////////////////////////////////////
// GetIconeFromPoint :
//	Obtient l'adresse d'une icone qui recouvre un point de la vue
//	ENTREES	:	Coordonnees du point
//	RETOUR :	@ de l'icone (ou NULL si pas d'icone a cet endroit )
///////////////////////////////////////////////////////////////////////////////
CIcone* CJibe96View::GetIconeFromPoint( CPoint Pt )
{
	CJibe96Doc*	pDoc		=	GetDocument() ;
	const int	NbIcones	=	pDoc->NbIcones() ;
	const int	EcartY		=	GetSystemMetrics( SM_CYBORDER ) ;
	CPoint		PosIcone( PosDepart() ) ;
	
	for ( int i = 0; i < NbIcones; i++)
		{
		CIcone	*	pIcone	=	pDoc->GetIcone( i ) ;

		if ( pIcone->PtInIcon( Pt, PosIcone ) )
			return pIcone ;

		ShiftPos( PosIcone, pIcone ) ;
		}

	return 0 ;
}

void CJibe96View::ShiftPos( CPoint & Pt, CIcone * pIcone )
{
	ASSERT_VALID( pIcone ) ;

	switch( GetDocument()->GetSide())
		{
		case ABE_LEFT :
		case ABE_RIGHT :
			Pt.y	+=	pIcone->Hauteur() + GetSystemMetrics( SM_CYFRAME ) ;
			break ;
		case ABE_TOP :
		case ABE_BOTTOM :
			Pt.x	+=	pIcone->Largeur() + GetSystemMetrics( SM_CXFRAME ) ;
			break ;

		default :
			TRACE( "Bug dans shiftpos\n" ) ;
		}
}

CPoint CJibe96View::PosDepart( void )
{
	CLPIBitmap	Bitmap( CIcone::Colors64K() ? MAKEINTRESOURCE(IDB_TITRE) : MAKEINTRESOURCE( IDB_TITRE16 )) ;
	return CPoint( 0, Bitmap.Hauteur() + GetSystemMetrics( SM_CYFRAME ) ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Suppression d'une icone
///////////////////////////////////////////////////////////////////////////////
void CJibe96View::OnSupprimer() 
{
	if (!_pSelectionnee)
		return ;

	ASSERT_VALID( _pSelectionnee ) ;
	if ( ! _pSelectionnee->ConfirmeSuppression())
		return ;

	// Supprimer la fenetre associee si elle est ouverte
	CacheFenetreIcone() ;

	// Supprimer l'icone
	CJibe96Doc*	pDoc	=	GetDocument() ;
	pDoc->SupprimeIcone( _pSelectionnee ) ;
	_pSelectionnee	=	0 ;
	SetTipsOnIcons() ;
}

BOOL CJibe96View::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ( _pSelectionnee )
		{
		ASSERT_VALID( _pSelectionnee ) ;
		if ( _pSelectionnee->ExecuteCommand( wParam ))
			return TRUE ;
		}

	return CView::OnCommand(wParam, lParam);
}

BOOL CJibe96View::PreTranslateMessage(MSG* pMsg) 
{
	_ToolTip.RelayEvent( pMsg ) ;
	
	return CView::PreTranslateMessage(pMsg);
}

void CJibe96View::OnPlusbas() 
{
	CJibe96Doc*	pDoc	=	GetDocument() ;
	ASSERT_VALID( _pSelectionnee ) ;
	const	int	IndiceIcone	=	pDoc->IndiceIcone( _pSelectionnee ) ;

	ASSERT( IndiceIcone < pDoc->NbIcones()-1 ) ;

	pDoc->Echange( IndiceIcone, IndiceIcone+1 ) ;

	InvalidateRect( NULL, TRUE ) ;
	SetTipsOnIcons() ;
}

void CJibe96View::OnUpdatePlusbas(CCmdUI* pCmdUI) 
{
	BOOL	Enabled	=	FALSE ;
	if ( _pSelectionnee )
		{
		CJibe96Doc*	pDoc	=	GetDocument() ;

		const int	IndiceIcone	=	pDoc->IndiceIcone( _pSelectionnee ) ;
		const int	NbIcones	=	pDoc->NbIcones() ;
		if ( IndiceIcone < NbIcones-1 )
			Enabled	=	TRUE ;
		}
	pCmdUI->Enable( Enabled ) ;
}

void CJibe96View::OnPlushaut() 
{
	CJibe96Doc*	pDoc	=	GetDocument() ;
	ASSERT_VALID( _pSelectionnee ) ;
	const	int	IndiceIcone	=	pDoc->IndiceIcone( _pSelectionnee ) ;

	ASSERT( IndiceIcone > 0 ) ;

	pDoc->Echange( IndiceIcone, IndiceIcone-1 ) ;

	InvalidateRect( NULL, TRUE ) ;
	SetTipsOnIcons() ;
}

void CJibe96View::OnUpdatePlushaut(CCmdUI* pCmdUI) 
{
	BOOL	Enabled	=	FALSE ;
	if ( _pSelectionnee )
		{
		const int	IndiceIcone	=	GetDocument()->IndiceIcone( _pSelectionnee ) ;
		if ( IndiceIcone > 0 )
			Enabled	=	TRUE ;
		}
	pCmdUI->Enable( Enabled ) ;
}

void CJibe96View::OnHeure() 
{
	AjouteIcone( new CIconeHorloge ) ;
	
}

void CJibe96View::UpdateIcon( CIcone * pIcone, BOOL Efface )
{
	if ( ! _thisView )
		return ;
	ASSERT_VALID( _thisView ) ;

	CJibe96Doc*	pDoc	=	_thisView->GetDocument() ;
	
	if ( pIcone )
		{
		const int Indice	=	pDoc->IndiceIcone( pIcone ) ;
		if ( Indice < 0)
			return ;

		CPoint	Pt( _thisView->GetPosIcon( Indice )) ;
		CRect	Rect( pIcone->Rect()) ;
		Rect.OffsetRect( Pt ) ;

		_thisView->InvalidateRect( Rect, Efface ) ;
//		_thisView->UpdateWindow() ;
		}
	else
		_thisView->InvalidateRect( NULL, Efface ) ;
}

///////////////////////////////////////////////////////////////////////////////
// GetPosIcon
//	Obtient la position de départ d'une icone a partir de son indice
///////////////////////////////////////////////////////////////////////////////
CPoint CJibe96View::GetPosIcon( int Indice )
{
	CJibe96Doc*	pDoc	=	GetDocument() ;

	ASSERT( Indice >= 0 && Indice < pDoc->NbIcones()) ;

	CPoint		PosIcone( PosDepart() ) ;
	
	for ( int i = 0; i < Indice; i++)
		{
		CIcone	*	pIcone	=	pDoc->GetIcone( i ) ;
		ShiftPos( PosIcone, pIcone ) ;
		}

	return PosIcone;
}

CPoint CJibe96View::GetPosIcon( CIcone * pIcone )
{
	CJibe96Doc*	pDoc	=	GetDocument() ;

	const int	Indice	=	pDoc->IndiceIcone( pIcone ) ;

	return GetPosIcon( Indice ) ;
}


void CJibe96View::OnDate() 
{
	AjouteIcone( new CIconeDate()) ;
	
}

void CJibe96View::OnPlacedisque() 
{
		AjouteIcone( new CIconeDisque ) ;
}

void CJibe96View::SetTipsOnIcons( void )
{
	if ( IsWindow( _ToolTip.m_hWnd ))
		_ToolTip.DestroyWindow() ;

	_ToolTip.Create( this ) ;

	// Ajoute un tooltip pour chaque icone
	CJibe96Doc	*	pDoc	=	GetDocument() ;
	const	int	Nb	=	pDoc->NbIcones() ;

	CPoint		PosIcone( PosDepart() ) ;

	for ( int i = 0; i < Nb; i++)
		{
		CIcone*	pIcone	=	pDoc->GetIcone( i ) ;
		CRect	R		=	pIcone->Rect()  ;
		R.OffsetRect( PosIcone ) ;

		_ToolTip.AddTool( this, LPSTR_TEXTCALLBACK, R, i+1 ) ;

		ShiftPos( PosIcone, pIcone ) ;
		}
}

void CJibe96View::OnTTNeedText(NMHDR* pNMHDR, LRESULT* pResult) 
	{
	LPTOOLTIPTEXT	lpTT	=	(LPTOOLTIPTEXT)pNMHDR ;
	
	if ( lpTT->uFlags	== TTF_IDISHWND )
		{
		lstrcpy( lpTT->szText, "IDISHWND" ) ;
		return ;
		}

	const int	IndiceIcone	=	pNMHDR->idFrom-1 ;

	CJibe96Doc*	pDoc	=	GetDocument() ;
	if ( IndiceIcone < 0 || IndiceIcone > pDoc->NbIcones()) 
		{
		lstrcpy( lpTT->szText, "!" ) ;
		return ;
		}

	CIcone	*	pIcone = pDoc->GetIcone(IndiceIcone) ;
	ASSERT_VALID( pIcone ) ;

	CString	Chaine	=	pIcone->GetTip() ;
	lstrcpy( lpTT->szText, Chaine.Left( 79 )) ;
	}

void CJibe96View::PreTranslateToolTipMsg( MSG * pMsg )
{
	if ( ! _thisView )
		return ;

	_thisView->_ToolTip.RelayEvent( pMsg ) ;
}

void CJibe96View::OnFgNouvelleicnePlaceram() 
{
	AjouteIcone( new CIconeRAM ) ;
	
}

void CJibe96View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CIcone *	pIcone	=	GetIconeFromPoint( point ) ;

	CacheFenetreIcone() ;

	if ( ! pIcone ) 
		{
		// Entrer dans le mode deplacement de la toolbar
		SetCapture() ;
		_ChoixAppui		=	DEPLACE_FENETRE ;
		}
	else
		{
		if ( _pIconeFenetre	!= pIcone )
			{
			SetCapture() ;
			Selectionne( pIcone ) ;
			_PointDepart	=	point ;

			// Calcule la position de cette icone
			_ChoixAppui		=	OUVRE_FENETRE ;
			_pIconeFenetre	=	pIcone ;
			}
		else
			_pIconeFenetre	=	0 ;
		}
	
	CView::OnLButtonDown(nFlags, point);
}

void CJibe96View::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if ( GetCapture()==this)
		{
		ReleaseCapture() ;

		// Sortie du mode de deplacement de la fenetre
		switch( _ChoixAppui )
			{
			case DEPLACE_FENETRE :
				SetWindowPosFromPoint() ;
				InvalidateRect( NULL, TRUE ) ;
				break ;

			case OUVRE_FENETRE :
				{
				///////////////////////////////////////////////////////////////
				// Simple clic sur une icone, on lui demande d'ouvrir sa fenetre
				// contextuelle
				///////////////////////////////////////////////////////////////
				ASSERT_VALID( _pSelectionnee ) ;
				CRect	R( GetIconeRect( _pSelectionnee )) ;
				_pFenetreIcone	=	_pSelectionnee->OuvreFenetre( R, this ) ;
				if ( _pFenetreIcone )
					{
					UpdateWindow() ;
					CClientDC	Dc( this ) ;
					_pSelectionnee->Assombri( Dc, R.TopLeft()) ;
					}
				}
				break ;

			case DEPLACE_ICONE :
				{
				if ( _hOldRegion )
					{
					CClientDC	Dc( this ) ;
					DessineFantome( Dc, _hOldRegion ) ;
					DeleteObject( _hOldRegion ) ;
					_hOldRegion	=	0 ;
					KillTimer( 1 ) ;

					CJibe96Doc*	pDoc	=	GetDocument() ;
					const int	Indice1	=	pDoc->IndiceIcone( _pSelectionnee ) ;
					// Trouver l'icone la plus proche
					CPoint		Pt( 0, point.y ) ;
					CIcone*		pIcone	=	IconePlusProche( Pt - _Decalage ) ;
					const int	Indice2	=	pDoc->IndiceIcone( pIcone ) ;

					TRACE("Echange icone %d et %d\n", Indice1, Indice2 ) ;

					pDoc->Insere( Indice1, Indice2 ) ;
					}
				}
				break ;

			default :
				ASSERT( FALSE ) ;
			}
		}

	CView::OnLButtonUp(nFlags, point);
}

void CJibe96View::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( GetCapture() == this )
		{
		switch( _ChoixAppui )
			{
			case	DEPLACE_FENETRE :
				SetWindowPosFromPoint() ;
				break ;

			case DEPLACE_ICONE :
				{
				// Deplacement de l'icone
				ASSERT_VALID( _pSelectionnee ) ;
				CPoint		Pt( 0, point.y ) ;
				HRGN	hRgn	=	_pSelectionnee->Region( Pt - _Decalage ) ;
				
				CClientDC	Dc( this ) ;
				if ( _hOldRegion )
					{
					DessineFantome( Dc, _hOldRegion ) ;
					DeleteObject( _hOldRegion ) ;
					}

				DessineFantome( Dc, hRgn ) ;

				_hOldRegion	=	hRgn ;
				}
				break ;

			case OUVRE_FENETRE :
				if ( CurseurTropLoing( _PointDepart, point ))
					{
					_ChoixAppui	=	DEPLACE_ICONE ;
					// Calcul du decalage entre l'icone et le curseur
					ASSERT_VALID( _pSelectionnee );
					const	CPoint	Pt	=	GetPosIcon( _pSelectionnee ) ;
					_Decalage			=	_PointDepart - Pt;
					_Decalage.cx		=	0 ;
					SetTimer( 1, 100, 0 ) ;
					}
			   break ;

			case ACTIVATION_AUTO :
				{
				// La fenetre a ete activee automatiquement, retourner
				// a l'ancienne application si le curseur est hors de la
				// fenetre
				CRect R ;
				GetClientRect( R ) ;
				R.InflateRect( 4, 4 ) ;

				if ( ! R.PtInRect( point ))
					{
					::SetForegroundWindow( _hApplicationActive ) ;
					ReleaseCapture() ;
					CMainFrame*	pMainFrame	=	(CMainFrame*)AfxGetMainWnd();
					pMainFrame->FermeFenetre() ;
					}
				}

			default :
				//ASSERT( FALSE ) ;
				break ;
			}
		}
	else
		// Le curseur se balade sur notre fenetre, on active
		// automatiquement la barre
		{
		_hApplicationActive	=	::GetForegroundWindow() ;
		SetForegroundWindow() ;
		SetCapture() ;
		_ChoixAppui	=	ACTIVATION_AUTO ;
		CMainFrame*	pMainFrame	=	(CMainFrame*)AfxGetMainWnd();
		pMainFrame->OuvreFenetre() ;
		}
	CView::OnMouseMove(nFlags, point);
}

void CJibe96View::SetWindowPosFromPoint( void )
{
	// Obtenir la position du curseur
	CPoint	Pt ;
	GetCursorPos( &Pt ) ;

	// Determiner le bord le plus proche
	const int	DistTop		=	Pt.y ;
	const int	DistLeft	=	Pt.x ;
	const int	DistBottom	=	GetSystemMetrics( SM_CYSCREEN ) - Pt.y ;
	const int	DistRight	=	GetSystemMetrics( SM_CXSCREEN ) - Pt.x ;
//	const int	DistMin		=	min( DistTop, min( DistBottom, min( DistLeft, DistRight ))) ;
	const int	DistMin		=	min( DistLeft, DistRight ) ;
	UINT	Side ;
/*	if ( DistMin == DistTop )
		Side = ABE_TOP  ;
	else
	if ( DistMin == DistBottom )
		Side = ABE_BOTTOM  ;
	else
*/
	if ( DistMin == DistRight )
		Side = ABE_RIGHT  ;
	else
		Side = ABE_LEFT  ;

	CMainFrame	*	pFrame	=	STATIC_DOWNCAST( CMainFrame, AfxGetMainWnd()) ;
	ASSERT_VALID( pFrame ) ;
	pFrame->SetPos( Side ) ;
}

void CJibe96View::OnFgNouvelleicnePlacemmoire() 
{
	AjouteIcone( new CIconeMem ) ;
	
}


BOOL CJibe96View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor( AfxGetApp()->LoadCursor( IDC_CURSOR )) ;
	
	return TRUE ;
}

void CJibe96View::OnFgFichierdchange() 
{
	AjouteIcone( new CIconeSwap ) ;
	
}

void CJibe96View::OnSeparateur() 
{
	AjouteIcone( new CIconeSeparateur ) ;
}


// statique
CSize	CJibe96View::GetSize( void )
	{
	ASSERT_VALID( _thisView ) ;

	CSize	Size( CMainFrame::GetSize()) ;
	CJibe96Doc*	pDoc	=	_thisView->GetDocument() ;
	CRect	R ;
	_thisView->GetClientRect( R ) ;

	switch( pDoc->GetSide())
		{
		case ABE_LEFT :
		case ABE_RIGHT :
			Size.cx	=	min( Size.cx, R.Width()) ;
			break ;

		case ABE_TOP :
		case ABE_BOTTOM :
			Size.cy	=	min( Size.cy, R.Height()) ;
			break ;
		}

	return Size ;
	}

void CJibe96View::OnFgPrfrences() 
{
	CPreferencesDlg	Dlg ;
	if ( Dlg.DoModal() == IDOK )
		InvalidateRect( NULL, TRUE ) ;	
}

///////////////////////////////////////////////////////////////////////////////
// GetIconeRect
//	Obtient le rectangle occupe par une icone
///////////////////////////////////////////////////////////////////////////////
CRect CJibe96View::GetIconeRect( CIcone * pIconeRect )
{
	CJibe96Doc*	pDoc	=	GetDocument() ;

	const int	NbIcones	=	pDoc->NbIcones() ;
	CPoint		PosIcone( PosDepart() ) ;
	
	for ( int i = 0; i < NbIcones; i++)
		{
		CIcone	*	pIcone	=	pDoc->GetIcone( i ) ;

		if ( pIconeRect	==	pIcone )
			{
			CRect	R(pIcone->Rect()) ;
			R.OffsetRect( PosIcone ) ;
			return R ;
			}

		ShiftPos( PosIcone, pIcone ) ;
		}

	return CRect( 0,0,0,0 ) ;	
}

void CJibe96View::OnGroupe() 
{
	AjouteIcone( new CIconeGroupe()) ;
}

void CJibe96View::CacheFenetreIcone( void )
{
	if ( _pFenetreIcone )
		{
		// Pointeur toujours valide ?
		if ( AfxIsValidAddress( _pFenetreIcone, sizeof( CWnd )))
			{
			if ( IsWindow( _pFenetreIcone->m_hWnd ))
				{

				_pFenetreIcone->DestroyWindow() ;
				}

			delete _pFenetreIcone ;
			}

		_pFenetreIcone	=	0 ;

		if ( _pSelectionnee )
			_pSelectionnee->Update() ;
		}

}

void CJibe96View::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	CacheFenetreIcone() ;	
}

void CJibe96View::OnDropFiles(HDROP hDropInfo) 
{
	POINT	Pt ;
	DragQueryPoint( hDropInfo, &Pt ) ;

	CIcone	*	pIcone	=	GetIconeFromPoint( Pt ) ;

	if ( pIcone )
		pIcone->AccepteFichiers( hDropInfo ) ;
	
	CView::OnDropFiles(hDropInfo);
}

BOOL CJibe96View::CurseurTropLoing( const CPoint & Pt1, const CPoint & Pt2 )
{
	const int	XMin	=	GetSystemMetrics( SM_CXDRAG ) ;
	const int	YMin	=	GetSystemMetrics( SM_CYDRAG ) ;
	const int	DeltaX	=	Pt1.x - Pt2.x ;
	const int	DeltaY	=	Pt1.y - Pt2.y ;

	if ( abs( DeltaX ) > XMin )
		return TRUE ;

	if ( abs( DeltaY ) > YMin )
		return TRUE ;
	
	return FALSE ;
}


void CJibe96View::DessineFantome( CDC & Dc, HRGN hRgn )
{
	Dc.SetROP2( R2_XORPEN ) ;
	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( IDB_FANTOME ) ;
	CBrush	Brush( &Bitmap ) ;

	Dc.SetBrushOrg( _BrushOrg ) ;
	Brush.UnrealizeObject() ;

	FillRgn( Dc.m_hDC, hRgn, Brush ) ;
	Brush.DeleteObject() ;
	Bitmap.DeleteObject() ;
}

void CJibe96View::OnTimer(UINT nIDEvent) 
{
	CClientDC	Dc( this ) ;

	if ( _hOldRegion )
		DessineFantome( Dc, _hOldRegion ) ;

	_BrushOrg.x	++ ;
	_BrushOrg.y ++ ;
	
	if ( _hOldRegion )
		DessineFantome( Dc, _hOldRegion ) ;

	CView::OnTimer(nIDEvent);
}

CIcone* CJibe96View::IconePlusProche( CPoint Pt )
{
	TRACE("Point : %d\n", Pt.y ) ;
	CJibe96Doc*	pDoc	=	GetDocument() ;

	const int	NbIcones	=	pDoc->NbIcones() ;
	CPoint		PosIcone( PosDepart() ) ;
	
	for ( int i = 0; i < NbIcones; i++)
		{
		CIcone	*	pIcone	=	pDoc->GetIcone( i ) ;

		CRect	R(pIcone->Rect()) ;
		R.OffsetRect( PosIcone ) ;

		TRACE("Bas de l'icone %d : %d\n", i, R.bottom ) ;

		if ( R.bottom > Pt.y )
			return pIcone ;

		ShiftPos( PosIcone, pIcone ) ;
		}

	return pDoc->GetIcone( NbIcones-1 ) ;
}

void CJibe96View::Selectionne( CIcone * pIcone )
{
	ASSERT( _thisView	== this ) ;
	if ( _pSelectionnee	==	pIcone )
		return ;

	if ( _pSelectionnee )
		{
		// Enlever l'ancienne selection
		ASSERT_VALID( _pSelectionnee ) ;
		CIcone*		pIcone	= _pSelectionnee ;
		_pSelectionnee		=	0 ;
		UpdateIcon(  pIcone, TRUE ) ;
		}

	_pSelectionnee	=	pIcone ;
	if ( _pSelectionnee )
		{
		ASSERT_VALID( _pSelectionnee ) ;
		UpdateIcon( _pSelectionnee, TRUE ) ;
		}
}

void CJibe96View::OnSurveilleRep()
	{
	AjouteIcone( new CIconeSurveille ) ;
	}
void CJibe96View::OnCommande() 
{
	AjouteIcone( new CIconeCommande ) ;
}

void CJibe96View::OnBouton() 
{
	AjouteIcone( new CIconeBouton ) ;	
}
