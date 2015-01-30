// DebloqueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Debloque.h"
#include "DebloqueDlg.h"
#include <RegistrationKey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct
	{
	char*	Name ;
	char*	Path ;
	char*	Hidden ;
	}
	T_LOGICIEL ;

T_LOGICIEL	Logiciels[]
	=
	{
		{WAD_NAME,		WAD_PATH, WAD_HIDDEN },
		{GRAV_NAME,		GRAV_PATH, GRAV_HIDDEN},
		{LIF_NAME,		LIF_PATH, LIF_HIDDEN},
		{LOP_NAME,		LOP_PATH, LOP_HIDDEN},
		{GRAF_NAME,		GRAF_PATH, GRAF_HIDDEN},
		{TDS_NAME,		TDS_PATH, TDS_HIDDEN}

	} ;

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
// CDebloqueDlg dialog

CDebloqueDlg::CDebloqueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDebloqueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDebloqueDlg)
	m_Entree = _T("");
	m_Sortie = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDebloqueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebloqueDlg)
	DDX_Control(pDX, IDC_LISTE, m_Liste);
	DDX_Text(pDX, IDC_ENTREE, m_Entree);
	DDX_Text(pDX, IDC_SORTIE, m_Sortie);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDebloqueDlg, CDialog)
	//{{AFX_MSG_MAP(CDebloqueDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LISTE, OnSelchangeListe)
	ON_EN_CHANGE(IDC_ENTREE, OnChangeEntree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebloqueDlg message handlers

BOOL CDebloqueDlg::OnInitDialog()
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

	for ( int i = 0; i < sizeof( Logiciels ) / sizeof( Logiciels[0] ); i++ )
		m_Liste.AddString( Logiciels[i].Name ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDebloqueDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDebloqueDlg::OnPaint() 
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
HCURSOR CDebloqueDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDebloqueDlg::OnSelchangeListe() 
{
	int	Sel	=	m_Liste.GetCurSel() ;

	m_Sortie.Empty() ;

	UpdateData( FALSE ) ;
}

void CDebloqueDlg::OnChangeEntree() 
{
	UpdateData( TRUE ) ;
	m_Sortie.Empty() ;
			
	if (	m_Entree.Find( ')' ) != -1
		 && m_Entree.Find( '(' ) != -1
		 && m_Entree.Find( '}' ) != -1
		 && m_Entree.Find( '{' ) != -1 )
		{
		if ( VerifieLogiciel())
			{
			int	Sel	=	m_Liste.GetCurSel() ;
			if ( Sel == LB_ERR )
				return ;

			ASSERT ( Sel >= 0 && Sel < sizeof(Logiciels)/sizeof(Logiciels[0]) );

			CRegistrationKey	Key( Logiciels[Sel].Path, Logiciels[Sel].Hidden ) ;

			DWORD wKey	=	Key.GetUnlockKey(m_Entree) ;
			m_Sortie.Format( "%lu", wKey ) ;
			}
		}

		UpdateData( FALSE ) ;

}

// Verifier que la partie entre crochets correspond au logiciel attendu
BOOL CDebloqueDlg::VerifieLogiciel()
{
	const int IndiceDebut	=	m_Entree.Find( '[' ) ;
	const int IndiceFin		=	m_Entree.Find( ']' ) ;

	if ( IndiceDebut == -1 || IndiceFin == -1 )
		return TRUE ;	// Ancienne version : pas de clef pour le logiciel

	if ( IndiceDebut + 1 >= IndiceFin -1 )
		return FALSE ;

	CString	SousChaine	=	m_Entree.Mid( IndiceDebut + 1, IndiceFin - IndiceDebut - 1 ) ;
	SousChaine	=	"0x" + SousChaine ;

	char * Fin ;
	WORD	CS	=	(WORD)strtoul( SousChaine, &Fin, 0 ) ;

	int	Sel	=	m_Liste.GetCurSel() ;
	if ( Sel == LB_ERR )
		return FALSE ;

	ASSERT ( Sel >= 0 && Sel < sizeof(Logiciels)/sizeof(Logiciels[0]) );
	CRegistrationKey	Key( Logiciels[Sel].Path, Logiciels[Sel].Hidden ) ;
	
	WORD	CheckSum	=	LOWORD(Key.CheckSum( Key._SoftwareName )) ;

	if ( CheckSum != CS )
		{
		MessageBeep( MB_ICONSTOP ) ;
		MessageBox( "La clef ne correspond pas au logiciel", "Erreur", MB_OK | MB_ICONSTOP ) ;
		return FALSE ;
		}

	return TRUE ;
}
