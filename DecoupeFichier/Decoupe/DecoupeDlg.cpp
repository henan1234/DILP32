// DecoupeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Decoupe.h"
#include "DecoupeDlg.h"
#include "choosfol.h"
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

static const char*	NomsFormats[]	=	
	{
	"nom<x>.ext",
	"nom <x>.ext",
	"nom.ext<x>",
	"nom.ext <x>",
	"nom.ext.<x>"
	} ;

static const char*	Formats[]	=	
	{
	"%1%2>.%3",
	"%1 %2.%3",
	"%1.%3%2",
	"%1.%3 %2",
	"%1.%3.%2"
	} ;

static const char * NomsTailles[]	=	
	{
	"Octets",
	"Kilo-Octets",
	"Mega-Octets",
	"Giga-Octets"
	} ;

static DWORD Tailles[]	=	
	{
	1,
	1024,
	1024L*1024L,
	1024L*1024L*1024L
	} ;

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
// CDecoupeDlg dialog

CDecoupeDlg::CDecoupeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDecoupeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDecoupeDlg)
	m_FichierADecouper = _T("");
	m_TailleFichier = _T("");
	m_RepertoireCible = _T("");
	m_TailleMorceau = 1;
	m_NbMorceaux = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDecoupeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDecoupeDlg)
	DDX_Control(pDX, IDC_TAILLES, m_Tailles);
	DDX_Control(pDX, IDC_FORMAT_NOM_CIBLE, m_FormatsNomsCibles);
	DDX_Text(pDX, IDC_FICHIER_A_DECOUPER, m_FichierADecouper);
	DDX_Text(pDX, IDC_TAILLE_FICHIER, m_TailleFichier);
	DDX_Text(pDX, IDC_REPERTOIRE_CIBLE, m_RepertoireCible);
	DDX_Text(pDX, IDC_TAILLE_MORCEAU, m_TailleMorceau);
	DDV_MinMaxDWord(pDX, m_TailleMorceau, 1, 4294967295);
	DDX_Text(pDX, IDC_NB_PARTIES, m_NbMorceaux);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDecoupeDlg, CDialog)
	//{{AFX_MSG_MAP(CDecoupeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PARCOURS_FICHIERS, OnParcoursFichiers)
	ON_BN_CLICKED(IDC_PARCOURS_REPERTOIRE, OnParcoursRepertoire)
	ON_EN_CHANGE(IDC_FICHIER_A_DECOUPER, OnChangeFichierADecouper)
	ON_CBN_SELCHANGE(IDC_TAILLES, OnSelchangeTailles)
	ON_EN_CHANGE(IDC_TAILLE_MORCEAU, OnChangeTailleMorceau)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDecoupeDlg message handlers

BOOL CDecoupeDlg::OnInitDialog()
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
	
	for ( int i = 0; i < sizeof( NomsFormats ) / sizeof( NomsFormats[0]); i++)
		m_FormatsNomsCibles.AddString( NomsFormats[i] ) ;
	m_FormatsNomsCibles.SetCurSel(0 ) ;

	for ( i = 0; i < sizeof( NomsTailles ) / sizeof( NomsTailles[0]); i++)
		m_Tailles.AddString( NomsTailles[i] ) ;

	m_Tailles.SetCurSel(0 ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDecoupeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDecoupeDlg::OnPaint() 
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
HCURSOR CDecoupeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDecoupeDlg::OnParcoursFichiers() 
{
	UpdateData( TRUE ) ;
	CFileDialog	dlg( TRUE, "*", m_FichierADecouper, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_ENABLESIZING, "*.*|*.*|", this ) ;
	if ( dlg.DoModal() == IDOK )
		{
		m_FichierADecouper	=	dlg.GetPathName() ;
		CalculeTailleFichier() ;
		UpdateData( FALSE ) ;
		OnChangeTailleMorceau() ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Calcule la taille du fichier a decouper et met a jour les champs adequats
///////////////////////////////////////////////////////////////////////////////
void CDecoupeDlg::CalculeTailleFichier()
{
	if ( m_FichierADecouper.IsEmpty() )
		m_TailleFichier.Empty() ;

	try
		{
		CStdioFile	file( m_FichierADecouper, CFile::modeRead | CFile::typeBinary );

		DWORD	taille	=	file.GetLength() ;
		file.Close() ;
		m_TailleFichier	=	FormatteTailleFichier( taille ) ;
		}
	catch( CException e)
		{
		return ;
		}

}

///////////////////////////////////////////////////////////////////////////////
// Formatte une taille de fichiers de maniere lisible
///////////////////////////////////////////////////////////////////////////////
CString CDecoupeDlg::FormatteTailleFichier(DWORD Taille)
{
	CString Result ;

	if ( Taille > (1024L * 1024L * 1024L ))
		{
		// Taille en Go
		Result.Format( "%ld Go", Taille/(1024L*1024L*1024L) ) ;
		}
	if ( Taille > (1024L * 1024L))
		{
		// Taille en Mo
		Result.Format( "%ld Mo", Taille/(1024L*1024L) ) ;
		}
	if (Taille > 1024L )
		{
		// Taille en Ko
		Result.Format( "%ld Ko", Taille/1024L ) ;
		}
	else
		{
		// Taille en Octets
		Result.Format( "%ld Octets", Taille ) ;
		}

	return Result ;
}

void CDecoupeDlg::OnParcoursRepertoire() 
{
	UpdateData( TRUE ) ;
	CChooseFolder	fld( m_RepertoireCible, NULL, this ) ;
	if ( fld.DoModal() == IDOK )
		{
		m_RepertoireCible	=	fld.GetDirName() ;

		UpdateData( FALSE ) ;
		OnChangeTailleMorceau() ;
		}
}

void CDecoupeDlg::OnChangeFichierADecouper() 
{
	OnChangeTailleMorceau() ;
	
}

void CDecoupeDlg::OnSelchangeTailles() 
{
	OnChangeTailleMorceau() ;
	
}

void CDecoupeDlg::OnChangeTailleMorceau() 
{
	UpdateData( TRUE ) ;

	// Si un fichier est choisi, qu'une taille est connue, on peut calculer
	// le nombre de morceaux qui seront necessaires 
	if ( m_FichierADecouper.IsEmpty() )
		return ;

	const int UniteTaille	=	m_Tailles.GetCurSel() ;
	if ( UniteTaille == -1 )
		return ;

	DWORD	taille	;

	try
		{
		CStdioFile	file( m_FichierADecouper, CFile::modeRead | CFile::typeBinary );

		taille=	file.GetLength() ;
		file.Close() ;
		m_TailleFichier	=	FormatteTailleFichier( taille ) ;
		}
	catch( CException e)
		{
		return ;
		}

	const DWORD TailleMorceau	=	m_TailleMorceau * Tailles[UniteTaille] ;
	const DWORD NbMorceaux		=	( taille + TailleMorceau - 1L ) / TailleMorceau ;
	
	m_NbMorceaux.Format( "%ld", (DWORD)NbMorceaux ) ;

	UpdateData( FALSE ) ;
}

void CDecoupeDlg::OnOK() 
{
	UpdateData() ;

	if ( m_FichierADecouper.IsEmpty())
		{
		MessageBox( "Choisissez d'abord un fichier à decouper", "Erreur", MB_ICONSTOP | MB_OK ) ;
		return ;
		}

	if ( m_TailleMorceau <= 0 )
		{
		MessageBox( "Saississez une taille de morceau supérieure à 0", "Erreur", MB_ICONSTOP | MB_OK ) ;
		return ;
		}

	const int UniteTaille	=	m_Tailles.GetCurSel() ;
	if ( UniteTaille == -1 )
		{
		MessageBox( "Choisissez une unité pour la taille des morceaux", "Erreur", MB_ICONSTOP | MB_OK ) ;
		return ;
		}

	const int FormatNom		=	m_FormatsNomsCibles.GetCurSel() ;
	if ( FormatNom == -1 )
		{
		MessageBox( "Choisissez un format pour le nom des morceaux", "Erreur", MB_ICONSTOP | MB_OK ) ;
		return ;
		}

	if ( m_RepertoireCible.IsEmpty())
		{
		MessageBox( "Choisissez d'abord un répertoire cible", "Erreur", MB_ICONSTOP | MB_OK ) ;
		return ;
		}

	CDlgDecoupeEnCours dlg ;
	dlg.Create( IDD_DECOUPE_EN_COURS, this ) ;
	dlg.ShowWindow( SW_SHOW ) ;
	
	dlg.m_TailleMorceau.Format( "%lu %s", (DWORD)m_TailleMorceau, (char *)NomsTailles[UniteTaille] ) ;
	dlg.UpdateData( FALSE ) ;

	DecoupeFichier( dlg, m_FichierADecouper, m_RepertoireCible, m_TailleMorceau * Tailles[UniteTaille], Formats[FormatNom] ) ;
	dlg.DestroyWindow() ;

	CDialog::OnOK();
}

void CDecoupeDlg::DecoupeFichier( CDlgDecoupeEnCours & dlg, const char *pNomFichier, const char *pRepertoireCible, DWORD TailleMorceaux, const char *pFormatNom)
{
	CStdioFile	Fichier ;
	if ( ! Fichier.Open( pNomFichier, CFile::modeRead | CFile::typeBinary ))
		return ;

	


	Fichier.Close() ;
}
