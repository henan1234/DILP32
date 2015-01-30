// GravitationSkinMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GravitationSkinMaker.h"
#include "GravitationSkinMakerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGravitationSkinMakerDlg dialog

CGravitationSkinMakerDlg::CGravitationSkinMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGravitationSkinMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGravitationSkinMakerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_IndiceImageCourante	=	0 ;
}

void CGravitationSkinMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGravitationSkinMakerDlg)
	DDX_Control(pDX, IDC_LIST1, m_Liste);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGravitationSkinMakerDlg, CDialog)
	//{{AFX_MSG_MAP(CGravitationSkinMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MOVEUP, OnMoveup)
	ON_BN_CLICKED(IDC_MOVEDOWN, OnMovedown)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGravitationSkinMakerDlg message handlers

BOOL CGravitationSkinMakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	DragAcceptFiles() ;
	_ListeImages.Create( 32, 32, ILC_COLOR32, 0, 1  ) ;

	m_Liste.SetImageList( &_ListeImages, LVSIL_SMALL ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGravitationSkinMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGravitationSkinMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGravitationSkinMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGravitationSkinMakerDlg::OnDropFiles(HDROP hDropInfo) 
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
		else
			MessageBox( NomFichier, "Could not load image file", MB_ICONSTOP | MB_OK ) ;
		}

	SetTimer( 1, 100, NULL ) ;
	
	CDialog::OnDropFiles(hDropInfo);
}

void CGravitationSkinMakerDlg::OnTimer(UINT nIDEvent) 
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


	
	CDialog::OnTimer(nIDEvent);
}

void CGravitationSkinMakerDlg::OnMoveup() 
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

void CGravitationSkinMakerDlg::OnMovedown() 
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

void CGravitationSkinMakerDlg::OnCopy() 
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
