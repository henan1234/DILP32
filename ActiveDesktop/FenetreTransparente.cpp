// FenetreTransparente.cpp : implementation file
//

#include "stdafx.h"
#include "ActiveDesktop.h"
#include "FenetreTransparente.h"
#include "WorkingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWorkingDlg	Dlg ;

/////////////////////////////////////////////////////////////////////////////
// CFenetreTransparente

CFenetreTransparente::CFenetreTransparente()
{
	_hBitmap	=	0 ;
}

CFenetreTransparente::~CFenetreTransparente()
{
	Dlg.DestroyWindow() ;
}


BEGIN_MESSAGE_MAP(CFenetreTransparente, CWnd)
	//{{AFX_MSG_MAP(CFenetreTransparente)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFenetreTransparente message handlers

void CFenetreTransparente::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect R ;
	GetClientRect( R ) ;

	if ( _hBitmap )
		dc.DrawState( R.TopLeft(), R.Size(), _hBitmap, DSS_NORMAL ) ;
	else
		{
		CString Message ;
		Message.LoadString( IDS_NO_BITMAP ) ;
		dc.DrawText( Message, R, DT_LEFT | DT_TOP ) ;
		}
}


BOOL CFenetreTransparente::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style	=	WS_POPUP ;
	cs.dwExStyle=	WS_EX_TOOLWINDOW ;
	cs.x		=	0 ;
	cs.y		=	0 ;
	cs.cx		=	GetSystemMetrics( SM_CXSCREEN ) ;
	cs.cy		=	GetSystemMetrics( SM_CYSCREEN ) ;

	return CWnd::PreCreateWindow(cs);
}

void CFenetreTransparente::SetBitmap( const char * pBitmapName )
{
	if ( _hBitmap )
		DeleteObject( _hBitmap ) ;

	
	if ( ! pBitmapName || ! (*pBitmapName) )
		{
		_hBitmap	=	NULL ;
		SetWindowRgn( NULL, TRUE  ) ;
		}
	
	_hBitmap	=	(HBITMAP)LoadImage( AfxGetInstanceHandle(), pBitmapName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ) ;

	if ( _hBitmap )
		{
		HRGN	hRegion	=	GetRegionFromBitmap( _hBitmap, RGB(0, 0, 0)) ;
		if ( hRegion == NULL )
			{
			CString	Message ;
			CString Titre ;
			Message.LoadString( IDS_ERREUR_REGION ) ;
			Titre.LoadString( IDS_TITRE_REGION ) ;

			MessageBeep( MB_ICONSTOP ) ;
			MessageBox( Message, Titre, MB_OK | MB_ICONSTOP ) ;
			}
		else
			SetWindowRgn( hRegion, TRUE ) ;

		Invalidate( FALSE ) ;
		ShowWindow( SW_SHOW ) ;
		}
}

HRGN CFenetreTransparente::GetRegionFromBitmap(HBITMAP hBitmap, COLORREF Transparente)
{
	CWaitCursor() ;

	HDC		hMemDC ;
	BITMAP	sBitmap ;
	HGDIOBJ	hOld ;
	RGNDATA	*	lpData ;
	LPRECT	lpR	;
	int		Ligne ;
	int		IndiceFin	;
	int		IndiceDepart;

	Dlg.ShowWindow( SW_SHOW ) ;
	Dlg.UpdateWindow() ;
	Dlg.SetWindowPos( &wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE ) ;

	GetObject( hBitmap, sizeof( sBitmap ), &sBitmap ) ;

	Dlg.m_Progress.SetRange( 0, sBitmap.bmHeight ) ;
	
	hMemDC	=	CreateCompatibleDC( NULL ) ;
	hOld	=	SelectObject( hMemDC, hBitmap ) ;

	///////////////////////////////////////////////////////////////////////////
	// Initialisation de l'entete de la structure
	///////////////////////////////////////////////////////////////////////////
	lpData				=	(RGNDATA*)malloc(sizeof( RGNDATA ) + sizeof( RECT ) * sBitmap.bmHeight ) ;
	ASSERT( lpData ) ;

	lpData->rdh.dwSize	=	sizeof( lpData->rdh.dwSize ) ;
	lpData->rdh.iType	=	RDH_RECTANGLES ;
	lpData->rdh.nCount	=	0 ;
	lpData->rdh.nRgnSize=	0 ;

	// Bounding rectangle : le rectangle de la bitmap
	SetRect( &lpData->rdh.rcBound,0,0,sBitmap.bmWidth,sBitmap.bmHeight ) ;

	lpR	=	(LPRECT)&lpData->Buffer ;			// Pour se faciliter la vie, on pointe directement sur les rectangles

	///////////////////////////////////////////////////////////////////////////
	// Parcourir les lignes pour en deduire les rectangles
	///////////////////////////////////////////////////////////////////////////
	MSG msg ;
	
	for ( Ligne	=	0; Ligne < sBitmap.bmHeight; Ligne ++ )
		{
		if ( Ligne %10 == 0)
			{
			if (PeekMessage( &msg, Dlg, 0, 0, PM_REMOVE ))
				{
				TranslateMessage( &msg ) ;
				DispatchMessage( &msg ) ;
				}
			Dlg.m_Progress.SetPos( Ligne ) ;
			}

		IndiceDepart	=	0 ;

		while ( IndiceDepart < sBitmap.bmWidth-1)
			{
			///////////////////////////////////////////////////////////////////////////
			// Parcourir la ligne et en deduire les bouts de la couleur qui nous interessent
			///////////////////////////////////////////////////////////////////////////
	
			// Trouver le premier pixel d'une autre couleur que celle specifiee
			while ( (IndiceDepart < sBitmap.bmWidth) &&	GetPixel( hMemDC, IndiceDepart, Ligne ) == Transparente )
				IndiceDepart ++ ;

			// Parcourir jusqu'a retrouver la couleur specifiee
			IndiceFin =	IndiceDepart ;
			while ( (IndiceFin < sBitmap.bmWidth ) && GetPixel( hMemDC, IndiceFin, Ligne ) != Transparente )
				IndiceFin ++ ;
			
			BOOL bAjoute	=	FALSE ;
			// Ajouter le rectangle trouve
			if ( IndiceFin > IndiceDepart )
				{
				RECT * pRectangle	=	lpR ;

				while ( pRectangle <= (lpR + (lpData->rdh.nCount)) )
					{
					if ( pRectangle->left == IndiceDepart
						 && pRectangle->right == IndiceFin
						 && pRectangle->bottom == Ligne )
						{
						// Ce rectangle convient, on l'augmente plutot que d'ajouter un rectangle a la liste
						pRectangle->bottom ++ ;
						bAjoute	=	TRUE ;
						break ;
						}
					pRectangle ++ ;
					}

				if ( ! bAjoute )
					{
					// Ajouter le rectangle
					lpData	=	(RGNDATA*)realloc( lpData, sizeof( lpData->rdh ) + ((lpData->rdh.nCount+1)*sizeof( RECT ))) ;
					SetRect( &lpR[lpData->rdh.nCount], IndiceDepart, Ligne, IndiceFin, Ligne+1 ) ;

					lpData->rdh.nRgnSize	+=	sizeof( RECT ) ;
					lpData->rdh.nCount++ ;
					}
				}

			IndiceDepart = IndiceFin ;
			}

		// Ligne suivante
		}

	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;

	HRGN hRegion	=	ExtCreateRegion( NULL, sizeof( lpData->rdh ) + (lpData->rdh.nCount*sizeof( RECT )),	lpData ) ;

	free( lpData ) ;

	Dlg.ShowWindow(SW_HIDE) ;
	return hRegion ;
}

int CFenetreTransparente::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Dlg.Create(IDD_WORKING, this ) ;

	
	return 0;
}
