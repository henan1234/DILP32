// PAEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PAE.h"
#include "PAEDlg.h"

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
// CPAEDlg dialog

CPAEDlg::CPAEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPAEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPAEDlg)
	m_Duree = 0;
	m_Image = _T("");
	m_PAE = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPAEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPAEDlg)
	DDX_Control(pDX, IDC_LISTE, m_Liste);
	DDX_Text(pDX, IDC_DUREE, m_Duree);
	DDX_Text(pDX, IDC_PAE, m_PAE);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPAEDlg, CDialog)
	//{{AFX_MSG_MAP(CPAEDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PARCOURIR_IMAGES, OnParcourirImages)
	ON_BN_CLICKED(IDC_PARCOURIR_PAE, OnParcourirPae)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_DESCENDRE, OnDescendre)
	ON_BN_CLICKED(IDC_MONTER, OnMonter)
	ON_BN_CLICKED(IDC_SUPPRIMER, OnSupprimer)
	ON_BN_CLICKED(IDC_VIDER, OnVider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPAEDlg message handlers

BOOL CPAEDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPAEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPAEDlg::OnPaint() 
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
HCURSOR CPAEDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CPAEDlg::OnParcourirImages() 
{
	UpdateData( TRUE ) ;
	CFileDialog	Dlg( TRUE, "BMP", m_Image,
					 OFN_HIDEREADONLY | OFN_EXPLORER | OFN_ALLOWMULTISELECT,
					 "Fichiers images (*.BMP)|*.BMP|Tous les fichiers (*.*)|*.*||",
					 this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		POSITION	Pos	=	Dlg.GetStartPosition() ;

		while ( Pos )
			m_Liste.AddString( Dlg.GetNextPathName(Pos) );
			
		UpdateData( FALSE ) ;
		}
}

void CPAEDlg::OnParcourirPae() 
{
	UpdateData( TRUE ) ;
	CFileDialog	Dlg( TRUE, "PAE", m_PAE,
					 OFN_HIDEREADONLY | OFN_EXPLORER,
					 "Fichiers PAE (*.PAE)|*.PAE|Tous les fichiers (*.*)|*.*||",
					 this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		m_PAE	=	Dlg.GetPathName() ;
		UpdateData( FALSE ) ;
		}
	
}



void CPAEDlg::OnOK() 
{
	// Generation du fichier
	UpdateData( TRUE ) ;
	CStdioFile	Fichier( m_PAE, CFile::modeCreate | CFile::modeWrite | CFile::typeText ) ; 

	Fichier.WriteString("[PROJECT]\n") ;
	Fichier.WriteString("* Created by Personal AVI Editor v1.X *" ) ;
	Fichier.WriteString("\n" ) ;
	Fichier.WriteString("MAKE VIDEO\n" ) ;
	Fichier.WriteString("SIZE 160x120\n" ) ;
	Fichier.WriteString("FRAMERATE 15 fps\n" ) ;
	Fichier.WriteString("COMPRESSOR cvid\n" ) ;
	Fichier.WriteString("QUALITY 75\n" ) ;
	Fichier.WriteString("DATA RATE 150\n" ) ;
	Fichier.WriteString("OPTIMIZE CD-ROM\n") ;
	Fichier.WriteString("\n" ) ;
	Fichier.WriteString("MAKE AUDIO\n" ) ;
	Fichier.WriteString("SAMPLERATE 11025 Hz\n" ) ;
	Fichier.WriteString("\n" ) ;

	const int	NbFichier	=	m_Liste.GetCount() ;
	for ( int i = 0; i < NbFichier; i++ )
		{
		CString UnFichier;
		m_Liste.GetText( i, UnFichier ) ;

		CFileStatus	Status ;
		if ( ! CFile::GetStatus(UnFichier, Status))
			{
			MessageBox( UnFichier, "Ce fichier n'existe pas", MB_OK | MB_ICONHAND ) ;
			return ;
			}

		CString Ligne ;

		char	Buffer	[_MAX_PATH] ;
		GetShortPathName( UnFichier, Buffer, sizeof( Buffer )) ;

		Ligne.Format( "ADDFILE %s\n", (const char *)Buffer ) ;

		Fichier.WriteString( Ligne ) ;
		}

	Fichier.WriteString("\n[VIDEO 0]\n" ) ;

	int	Temps = 0 ;

	for ( i = 0; i < NbFichier; i++ )
		{
		CString UnFichier;
		m_Liste.GetText( i, UnFichier ) ;

		char	Buffer	[_MAX_PATH] ;
		GetShortPathName( UnFichier, Buffer, sizeof( Buffer )) ;

		CString	Tps ;
		Tps.Format( "USEFILEEX 00:%02d:%02d:%02d 0 %d %s\n", Temps/60000, (Temps/100)%60000, Temps%100, m_Duree, (LPCSTR)Buffer ) ;

		Fichier.WriteString( Tps ) ;

		Temps += m_Duree ;
		}

	Fichier.WriteString( "\n" ) ;
	Fichier.WriteString( "[OPTIONS]\n" ) ;
	Fichier.WriteString( "INSERT AT_END\n" ) ;
	Fichier.WriteString( "STILL DURATION 100\n" ) ;
	Fichier.WriteString( "\n" ) ;
	Fichier.WriteString( "CONSTRUCTWIN 0 0 1024 0\n" ) ;
	Fichier.WriteString( "PROJECTWIN 28 202 300 234\n" ) ;
	Fichier.WriteString( "INFOWIN 378 232 284 270\n" ) ;
	Fichier.WriteString( "PLUGWIN 844 0 180 210\n" ) ;
	
	Fichier.Close() ;

	WinExec( "NOTEPAD " + m_PAE, SW_SHOW ) ;
	
	CDialog::OnOK();
}

void CPAEDlg::OnDropFiles(HDROP hDropInfo) 
{
	const int	Nb	=	DragQueryFile( hDropInfo, 0xFFFFFFFF, 0, 0 ) ;

	for ( int i = 0; i < Nb; i++ )
		{
		char	Buffer[_MAX_PATH] ;
		DragQueryFile( hDropInfo, i, Buffer, sizeof( Buffer )) ;

		m_Liste.AddString( Buffer ) ;
		}
	
	CDialog::OnDropFiles(hDropInfo);
}

void CPAEDlg::OnDescendre() 
{
	const int Sel	=	m_Liste.GetCurSel() ;

	if ( Sel == LB_ERR )
		return ;

	if ( Sel >= m_Liste.GetCount()-1 )
		return ;

	CString	Texte ;
	m_Liste.GetText( Sel, Texte ) ;
	m_Liste.DeleteString( Sel ) ;

	m_Liste.InsertString( Sel+1, Texte ) ;
	m_Liste.SetCurSel( Sel + 1 ) ;
}

void CPAEDlg::OnMonter() 
{
	const int Sel	=	m_Liste.GetCurSel() ;

	if ( Sel == LB_ERR )
		return ;

	if ( Sel < 1 )
		return ;

	CString	Texte ;
	m_Liste.GetText( Sel, Texte ) ;
	m_Liste.DeleteString( Sel ) ;

	m_Liste.InsertString( Sel-1, Texte ) ;
	m_Liste.SetCurSel( Sel - 1 ) ;
}

void CPAEDlg::OnSupprimer() 
{
	const int Sel	=	m_Liste.GetCurSel() ;

	if ( Sel == LB_ERR )
		return ;

	m_Liste.DeleteString( Sel ) ;
}

void CPAEDlg::OnVider() 
{
	m_Liste.ResetContent() ;
}
