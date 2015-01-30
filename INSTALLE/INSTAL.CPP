// InstalleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Installe.h"
#include "InstalleDlg.h"
#include <direct.h>
#include <winver.h>
#include <lzexpand.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *	Sources[]	=	{
						"Loupes.scr",
						"Brownien.scr",
						"Gravitation.scr",
						"Mouillé.scr",
						"Au feu !!!.scr",
						"Tas de sable.scr",
						"Promenade.scr" } ;


/////////////////////////////////////////////////////////////////////////////
// CInstalleDlg dialog

CInstalleDlg::CInstalleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstalleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstalleDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInstalleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstalleDlg)
	DDX_Control(pDX, IDC_ENCOURS, m_EnCours);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDOK, m_OK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInstalleDlg, CDialog)
	//{{AFX_MSG_MAP(CInstalleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstalleDlg message handlers

BOOL CInstalleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInstalleDlg::OnPaint() 
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
HCURSOR CInstalleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInstalleDlg::OnOK() 
{
	m_OK.EnableWindow( FALSE ) ;
	m_Cancel.EnableWindow( FALSE ) ;

	char	System[_MAX_PATH] ;
	GetSystemDirectory(System, sizeof( System )) ;
	if ( System[lstrlen( System )-1] != '\\' ) 
		lstrcat( System, "\\" ) ;

	char	Dir[ _MAX_PATH] ;
	_getcwd( Dir, _MAX_PATH ) ;
	if ( Dir[lstrlen( Dir )-1] != '\\' ) 
		lstrcat( Dir, "\\" ) ;
	
	BOOL	Erreur	=	FALSE ;

	for ( int	i	=	0; i < sizeof(Sources)/sizeof(Sources[0]); i++)
		{
		char Src[_MAX_PATH] ;
		lstrcpy( Src, Dir ) ;
		lstrcat( Src, Sources[i]) ;

		char Dest[_MAX_PATH] ;
		lstrcpy( Dest, System ) ;
		lstrcat( Dest, Sources[i] ) ;

		m_EnCours.SetWindowText( Sources[i] ) ;

		OFSTRUCT	OfSrc ;
		INT	hSource	=	LZOpenFile( Src, &OfSrc, OF_READ ) ;
		OFSTRUCT	OfDest ;
		LZInit(hSource) ;

		INT	hDest	=	LZOpenFile( Dest, &OfDest, OF_CREATE | OF_WRITE ) ;

		LONG err = LZCopy( hSource, hDest );
		LZClose( hSource ) ;	
		LZClose( hDest ) ;

		if (	err == LZERROR_BADINHANDLE ||
				err == LZERROR_BADOUTHANDLE ||
				err == LZERROR_GLOBALLOC||
				err == LZERROR_GLOBLOCK ||
				err == LZERROR_READ		   ) 
			{
			Erreur	=	TRUE ;
			break ;
			}
		}
	
	CString	Message ;
	if ( Erreur )
		Message.LoadString( IDS_KO ) ;
	else
		Message.LoadString( IDS_OK ) ;

	MessageBeep( MB_ICONEXCLAMATION ) ;
	MessageBox( Message, "Installation", MB_OK | MB_ICONEXCLAMATION ) ;

	CDialog::OnOK();
}
