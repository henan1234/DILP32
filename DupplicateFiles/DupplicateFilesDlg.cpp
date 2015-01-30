// DupplicateFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include <io.h>
#include <shellapi.h>
#include <afxtempl.h>
#include "DupplicateFiles.h"
#include "DupplicateFilesDlg.h"
#include <string.h>
#include "RegistryServices.h"
#include "ScanningDlg.h"
#include "MultipleDelete.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




BOOL FileExist( const TCHAR * pFileName )
	{
	return _access( pFileName, 0 ) == 0 ;
	}

///////////////////////////////////////////////////////////////////////////////
// FilterDOSFileNameChars
//	Eliminates all DOS filename incorrect characters from a file name, lower
//	case characters are uppercased
// INPUT :	String
// RETURN:	String with only DOS valid characters
///////////////////////////////////////////////////////////////////////////////
CString FilterFileNameChars(const TCHAR * pFileName)
{
	const CString  VALID_DOS_FILE_CHARS(	TEXT("\"\'")) ;

	CString	FileName( pFileName ) ;
	if ( FileName.IsEmpty())
		return FileName ;
	FileName.MakeUpper() ;

	CString	Result ;

	int	CharIndex	=	0 ;
	
	while ( CharIndex < FileName.GetLength())
		{
		const int Index	=	VALID_DOS_FILE_CHARS.Find( FileName[CharIndex] ) ;

		if ( Index == -1 )
			{
			// Valid char
			Result	+=	FileName[CharIndex] ;
			}

		CharIndex ++ ;
		}

	return Result ;
}

///////////////////////////////////////////////////////////////////////////////
// Concat
//	Concatenates two filename parts, adding "\\" where needed
//	INPUT:	First and second path names
//	RETURN:	New path
///////////////////////////////////////////////////////////////////////////////
CString	Concat( const TCHAR * pPath1, const TCHAR * pPath2 )
	{
	CString	Path1( pPath1 ) ;
	CString Path2( pPath2 ) ;

	if ( ! Path1.IsEmpty())
		if ( Path1.Right(1) == TEXT("\\") )
			Path1	=	Path1.Left( Path1.GetLength() - 1 ) ;

	if ( ! Path2.IsEmpty())
		if ( Path2[0] == TEXT('\\') )
			Path2	=	Path2.Mid( 1 ) ;

	return Path1 + TEXT("\\") + Path2 ;
	}


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
// CDupplicateFilesDlg dialog

CDupplicateFilesDlg::CDupplicateFilesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDupplicateFilesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDupplicateFilesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDupplicateFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDupplicateFilesDlg)
	DDX_Control(pDX, IDC_DELETEFILE, m_DeleteFile);
	DDX_Control(pDX, IDC_SHOW_DUPP, m_ShowDups);
	DDX_Control(pDX, IDC_PREV, m_Prev);
	DDX_Control(pDX, IDC_OPEN, m_Open);
	DDX_Control(pDX, IDC_NEXT, m_Next);
	DDX_Control(pDX, IDC_DELETE_ALL, m_DeleteAll);
	DDX_Control(pDX, IDC_DELETE, m_Delete);
	DDX_Control(pDX, IDC_TREE1, m_FileTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDupplicateFilesDlg, CDialog)
	//{{AFX_MSG_MAP(CDupplicateFilesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SHOW_DUPP, OnShowDupp)
	ON_BN_CLICKED(IDC_DELETE_ALL, OnDeleteAll)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree)
	ON_BN_CLICKED(IDC_DELETEFILE, OnDeletefile)
	ON_BN_CLICKED(IDC_DELETE_MULTIPLE, OnDeleteMultiple)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDupplicateFilesDlg message handlers

BOOL CDupplicateFilesDlg::OnInitDialog()
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
	
	
	m_Prev.ModifyStyle( 0, BS_BITMAP ) ;
	m_Prev.SetBitmap( (HBITMAP)LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDB_PREV ), IMAGE_BITMAP, 0,0, LR_LOADMAP3DCOLORS|LR_DEFAULTSIZE )) ;
	m_Next.ModifyStyle( 0, BS_BITMAP ) ;
	m_Next.SetBitmap( (HBITMAP)LoadImage( AfxGetResourceHandle(), MAKEINTRESOURCE( IDB_NEXT ), IMAGE_BITMAP, 0,0, LR_LOADMAP3DCOLORS|LR_DEFAULTSIZE )) ;

	_IconList.Create( 16, 16,
					  ILC_COLORDDB|ILC_MASK, 0, 1 ) ;
	_IconList.Add( LoadIcon( AfxGetResourceHandle(),
							  MAKEINTRESOURCE(	IDI_ICON1 ))) ;
	m_FileTree.SetImageList( &_IconList, TVSIL_NORMAL ) ;

	if ( _CommandLine.IsEmpty())
		{
		TCHAR	ExeFileName[_MAX_PATH] ;
		GetModuleFileName(NULL, ExeFileName, sizeof( ExeFileName ) ) ;

		CRegistryServices::SetRegistryValue( HKEY_CLASSES_ROOT, "Folder\\Shell\\Scan for duplicated files...\\Command",
											 CString( ExeFileName ) + " \"%1\"" ) ;
		//DragAcceptFiles();
		}
	else
		{
		if ( ! TraiteCommandLine())
			EndDialog(0) ;
		}

	CRect	R ;
	m_Open.GetWindowRect(R) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDupplicateFilesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDupplicateFilesDlg::OnPaint() 
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
HCURSOR CDupplicateFilesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDupplicateFilesDlg::FillFiles()
{

}

void CDupplicateFilesDlg::OnDropFiles(HDROP hDropInfo) 
{
	CWaitCursor w ;
	const int	NbFiles	=	(int)::DragQueryFile( hDropInfo, 0xFFFFFFFF, 0,0 ) ;
	CScanningDlg	Dlg ;
	Dlg.Create( IDD_DIALOG1 ) ;
	Dlg.ShowWindow(SW_SHOW) ;

	T_FILES_ATTRIBUTE	*	pFiles	=	new T_FILES_ATTRIBUTE[NbFiles] ;
	if ( ! pFiles )
		{
		::MessageBox( *this, "Not enough memory to handle so many files, please quit some application and retry.\r\nOr select less files.",
					  "Too many files",
					  MB_ICONSTOP | MB_OK ) ;

		ExitProcess(0) ;
		}
	int						NbFichiers	=	0;
	
	for ( int i = 0; i < NbFiles; i++)
		{
		TCHAR	File[_MAX_PATH] ;
		::DragQueryFile( hDropInfo, i, File, sizeof( File )) ;

		_int64 FileSize = 0 ;
		HTREEITEM	hItem	=	GetDupplicate( File, pFiles, NbFichiers, &FileSize, &Dlg ) ;
		if ( hItem )
			AddDupplicate( hItem, File, &Dlg ) ;
		else
			AddFile( File, pFiles, &NbFichiers, FileSize );
		}

	delete []	pFiles ;


	DragAcceptFiles(FALSE) ;
	CDialog::OnDropFiles(hDropInfo);

	Dlg.DestroyWindow() ;
}


HTREEITEM CDupplicateFilesDlg::GetDupplicate(const TCHAR * pFileName, T_FILES_ATTRIBUTE * pFiles, int NbFiles, _int64 * pFileSize, CScanningDlg * pDlg )
{
	CStdioFile	File( pFileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary ) ;
	DWORD	SizeHigh  = 0;
	DWORD	SizeLow	=	File.GetLength() ;
	
	*pFileSize	=	(_int64)SizeHigh ;
	(*pFileSize) <<= 32 ;
	(*pFileSize) += SizeLow ;

	for ( int i = 0; i < NbFiles && !pDlg->Abort() ; i++)
		{
		if ( *pFileSize != pFiles[i].Size )
			continue ;

		if ( MemeContenu( pFiles[i].Name, File ))
			{
			File.Close() ;
			return pFiles[i].hItem ;
			}
		}
	
	File.Close() ;
	return 0 ;
}


void CDupplicateFilesDlg::AddDupplicate(HTREEITEM hParent, const TCHAR * pFileName, CScanningDlg * pDlg)
{
	_DuplicatedFound ++ ;
	CString Message ;

	Message.Format( IDS_FOUND, _DuplicatedFound ) ;
	pDlg->m_Found.SetWindowText( Message ) ;

	m_FileTree.InsertItem( TVIF_TEXT,  pFileName, 0,0, 0, 0, 0, hParent, TVI_LAST ) ;
	m_FileTree.Expand( hParent, TVE_EXPAND ) ;
}

void CDupplicateFilesDlg::AddFile( const TCHAR * pFileName, T_FILES_ATTRIBUTE* pFiles, int * pFile, _int64 FileSize )
{
	const int IconIndex		=	GetIconIndex( pFileName ) ;

	pFiles[*pFile].hItem=	m_FileTree.InsertItem( TVIF_TEXT |TVIF_IMAGE|TVIF_SELECTEDIMAGE,
												   pFileName, IconIndex, IconIndex, 0, 0, 0, TVI_ROOT, TVI_LAST ) ;

	CStdioFile	File( pFileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary ) ;
	pFiles[*pFile].Size			=	FileSize ;
	File.Close() ;

	strcpy( pFiles[*pFile].Name, pFileName ) ;
	
	CString Taille ;
	(*pFile) ++ ;
}

BOOL CDupplicateFilesDlg::MemeContenu(const TCHAR * pFileName1, CStdioFile & File2 )
{
	BOOL Idem	= FALSE ;
	char	Buffer1[32768] ;
	char	Buffer2[32768] ;

	CStdioFile	File1( pFileName1, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary ) ;
	File2.SeekToBegin() ;
	
	UINT Nb1, Nb2 ;

	do
		{
		Nb1	=	File1.Read( Buffer1, sizeof( Buffer1 ) ) ;
		Nb2	=	File2.Read( Buffer2, sizeof( Buffer2 ) ) ;

		if ( Nb1 != Nb2 )
			break ;

		if ( memcmp( Buffer1, Buffer2, Nb1 ))
			break ;
		}
	while ( (Nb1 != 0) && (Nb2 != 0) ) ;

	File1.Close() ;
	//File2.Close() ;

	if ( Nb1 != 0 || Nb2 != 0)
		return FALSE ;

	return TRUE ;
}

void CDupplicateFilesDlg::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOpen() ;
	*pResult = 1;
}

void CDupplicateFilesDlg::OnNext() 
{
	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;
	if ( ! hItem )
		return ;

	// if this item is a dupplicate, get its parent get the parent item of this item
	const HTREEITEM	hRoot	=	m_FileTree.GetRootItem() ;

	HTREEITEM hParent =	m_FileTree.GetParentItem( hItem ) ;

	while ( hParent && hParent != hRoot )
		{
		hItem	=	hParent ;
		hParent	=	m_FileTree.GetParentItem(hParent) ;
		}

	if ( ! hItem )
		return ;

	HTREEITEM hSibling	=	m_FileTree.GetNextItem( hItem, TVGN_NEXT ) ;
	
	
	while ( hSibling )
		{
		if ( m_FileTree.ItemHasChildren( hSibling ))
			{
			// This is the one we want
			m_FileTree.EnsureVisible( hSibling ) ;
			m_FileTree.Select( hSibling, TVGN_CARET  ) ;
			return ;
			}

		hSibling	=	m_FileTree.GetPrevSiblingItem( hSibling ) ;
		}
}

void CDupplicateFilesDlg::OnPrev() 
{
	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;
	if ( ! hItem )
		return ;

	// if this item is a dupplicate, get its parent get the parent item of this item
	const HTREEITEM	hRoot	=	m_FileTree.GetRootItem() ;

	HTREEITEM hParent =	m_FileTree.GetParentItem( hItem ) ;

	while ( hParent && hParent != hRoot )
		{
		hItem	=	hParent ;
		hParent	=	m_FileTree.GetParentItem(hParent) ;
		}

	if ( ! hItem )
		return ;

	HTREEITEM hSibling	=	m_FileTree.GetNextItem( hItem, TVGN_PREVIOUS ) ;
	
	
	while ( hSibling )
		{
		if ( m_FileTree.ItemHasChildren( hSibling ))
			{
			// This is the one we want
			m_FileTree.EnsureVisible( hSibling ) ;
			m_FileTree.Select( hSibling, TVGN_CARET  ) ;
			return ;
			}

		hSibling	=	m_FileTree.GetPrevSiblingItem( hSibling ) ;
		};
}

void CDupplicateFilesDlg::OnDelete() 
{
	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;
	if ( ! hItem )
		return ;

	CString File	=	m_FileTree.GetItemText( hItem ) ;
	//	Delete all the dupplicate files, leaving only the one selected
	CString	Message ;
	Message.Format( IDS_CONFIRM_DELETE, File, File ) ;
	CString Title ;
	Title.LoadString( IDS_TITRE_DELETE ) ;

	MessageBeep( MB_ICONQUESTION ) ;
	if ( MessageBox( Message, Title, MB_ICONQUESTION | MB_OKCANCEL ) == IDCANCEL )
		return ;

	const HTREEITEM	hRoot	=	m_FileTree.GetRootItem() ;

	HTREEITEM hParent =	m_FileTree.GetParentItem( hItem ) ;

	while ( hParent && hParent != hRoot )
		{
		hItem	=	hParent ;
		hParent	=	m_FileTree.GetParentItem(hParent) ;
		}

	CString	FileText	=	m_FileTree.GetItemText( hItem ) ;
	DeleteFile( FileText ) ;

	HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
	CString	FilesToDelete	;

	while ( hChildItem )
		{
		CString	ChildText	=	m_FileTree.GetItemText( hChildItem ) ;
		if ( ChildText != File )
			FilesToDelete += ChildText + "|" ;

		hChildItem			=	m_FileTree.GetNextSiblingItem( hChildItem ) ;
		}

	if ( ! FilesToDelete.IsEmpty())
		{
		FilesToDelete += "|" ;
		if ( DeleteFiles( FilesToDelete ))
			{
			hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
			while ( hChildItem )
				{
				m_FileTree.DeleteItem( hChildItem ) ;
				hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
				}
			}
		}

	m_FileTree.SetItemText( hItem, File ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Ouverture du fichier selectionne
///////////////////////////////////////////////////////////////////////////////
void CDupplicateFilesDlg::OnOpen() 
{
	
	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;

	CString File	=	m_FileTree.GetItemText( hItem ) ;

	TCHAR	CurrentDirectory[_MAX_PATH] ;
	GetCurrentDirectory( sizeof( CurrentDirectory ), CurrentDirectory ) ;
	ShellExecute(    *this,     "open",    File, 
					NULL,   
					CurrentDirectory,
					SW_SHOW ) ;	
}

///////////////////////////////////////////////////////////////////////////////
// Scrutation ligne de commande, traite tous les fichiers dans le repertoire
// courant et les sous repertoires
///////////////////////////////////////////////////////////////////////////////
BOOL CDupplicateFilesDlg::TraiteCommandLine()
{
	CWaitCursor	w ;
	_CommandLine	=	FilterFileNameChars( _CommandLine ) ;
	CScanningDlg	Dlg ;

	Dlg.Create( IDD_DIALOG1 ) ;
	Dlg.ShowWindow(SW_SHOW) ;

	int	NbAlloues	=	100 ;
	int	NbFichiers	=	0 ;
	_ProcessedFiles	=	0 ;
	_DuplicatedFound=	0 ;

	T_FILES_ATTRIBUTE	*	pFiles	= (T_FILES_ATTRIBUTE*)malloc( sizeof( T_FILES_ATTRIBUTE ) * NbAlloues ) ;
	
	ParcoursRepertoire( _CommandLine, pFiles, &NbAlloues, &NbFichiers, &Dlg ) ;
	free( pFiles ) ;


	const BOOL Return	=	 ! Dlg.Abort() ;
	Dlg.DestroyWindow() ;

	return	Return ;
}

void CDupplicateFilesDlg::ParcoursRepertoire(const TCHAR * Path, T_FILES_ATTRIBUTE * & pFiles, int * pNbAlloues, int * pNbFiles, CScanningDlg * pDlg )
{
	WIN32_FIND_DATA		FindData ;
	HANDLE hFind		=	FindFirstFile( Concat( Path, "*.*" ), & FindData ) ;

	BOOL			Continue=	hFind != INVALID_HANDLE_VALUE ;

	while ( Continue && ! pDlg->Abort() )
		{
		// Ignore . and ..
		if ( _tcscmp( FindData.cFileName, TEXT(".") ) && _tcscmp( FindData.cFileName, TEXT("..") ))
			{
			// Reconstruct the complete file path
			const CString	CompleteSource	=	Concat(	Path, FindData.cFileName ) ;

			// Is the entry a file or a directory ?
			if ( FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
				{
				// copy the directory and its content, recursive call
				ParcoursRepertoire( CompleteSource, pFiles, pNbAlloues, pNbFiles, pDlg  ) ;
				}
			else
				{
				pDlg->m_File.SetWindowText( CompleteSource ) ;

				_ProcessedFiles	++ ;
				CString Message ;

				Message.Format( IDS_PROCESSED, _ProcessedFiles ) ;
				pDlg->m_Processed.SetWindowText( Message ) ;

				//Traiter le fichier
				_int64 FileSize = 0 ;
				HTREEITEM	hItem	=	GetDupplicate( CompleteSource, pFiles, *pNbFiles, &FileSize, pDlg ) ;
				if ( hItem )
					AddDupplicate( hItem, CompleteSource, pDlg ) ;
				else
					{
					if ( *pNbFiles >= *pNbAlloues )
						{
						(*pNbAlloues) += 100 ;
						pFiles	=	(T_FILES_ATTRIBUTE*)realloc( pFiles, sizeof( *pFiles ) * (*pNbAlloues) ) ;
						}

					AddFile( CompleteSource, pFiles, pNbFiles, FileSize );
					}
				}
			}

		Continue	=	FindNextFile( hFind, &FindData ) ;
		}

		FindClose(&FindData ) ;
}

///////////////////////////////////////////////////////////////////////////////
// OnShowDup
//	Show only the duplicated files
///////////////////////////////////////////////////////////////////////////////
void CDupplicateFilesDlg::OnShowDupp() 
{
	CWaitCursor	w ;

	HTREEITEM	hChild	=	m_FileTree.GetRootItem() ;

	while ( hChild )
		{
		HTREEITEM	hNext	=	m_FileTree.GetNextItem( hChild, TVGN_NEXT ) ;

		if ( ! m_FileTree.ItemHasChildren(hChild))
			m_FileTree.DeleteItem( hChild ) ;

		hChild	=	hNext ;
		}

	m_ShowDups.EnableWindow( FALSE ) ;
}

void CDupplicateFilesDlg::OnDeleteAll() 
{
	//	Delete all the dupplicate files, leaving only the one selected
	CString	Message ;
	Message.LoadString( IDS_CONFIRM_ALL ) ;
	CString Title ;
	Title.LoadString( IDS_TITRE_DELETE ) ;

	MessageBeep( MB_ICONQUESTION ) ;
	if ( ::MessageBox( *this, Message, Title, MB_ICONQUESTION | MB_OKCANCEL ) == IDCANCEL )
		return ;

	CWaitCursor	w ;
	HTREEITEM	hParent	=	m_FileTree.GetRootItem() ;
	CString		ListeSuppression ;

	while ( hParent )
		{
		HTREEITEM	hNext	=	m_FileTree.GetNextItem( hParent, TVGN_NEXT ) ;

		if ( m_FileTree.ItemHasChildren(hParent))
			{
			// Ajouter tous les fils de ce fichier a la liste de fichiers a supprimer
			HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hParent ) ;
			while ( hChildItem )
				{
				CString	ChildText	=	m_FileTree.GetItemText( hChildItem ) ;
				ListeSuppression += ChildText + "|" ;
				hChildItem			=	m_FileTree.GetNextSiblingItem( hChildItem ) ;
				}
			}

		hParent	=	hNext ;
		}

	if ( ListeSuppression.IsEmpty())
		return ;

	ListeSuppression += '|' ;
	
	if ( DeleteFiles( ListeSuppression ))
		{
		HTREEITEM	hParent	=	m_FileTree.GetRootItem() ;
		while ( hParent )
			{
			HTREEITEM	hNext	=	m_FileTree.GetNextItem( hParent, TVGN_NEXT ) ;

			if ( m_FileTree.ItemHasChildren(hParent))
				{
				// Ajouter tous les fils de ce fichier a la liste de fichiers a supprimer
				HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hParent ) ;
				while ( hChildItem )
					{
					HTREEITEM	hNext	=	m_FileTree.GetNextSiblingItem( hChildItem ) ;
					m_FileTree.DeleteItem( hChildItem ) ;
					hChildItem	=	hNext ;
					}
				}

			hParent	=	hNext ;
			}
		}

	m_ShowDups.EnableWindow( FALSE ) ;
	m_Delete.EnableWindow( FALSE ) ;
	m_DeleteAll.EnableWindow( FALSE ) ;
}


void CDupplicateFilesDlg::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;

	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;
	if ( ! hItem )
		{
		m_Open.EnableWindow( FALSE ) ;
		m_Delete.EnableWindow( FALSE ) ;
		m_DeleteFile.EnableWindow( FALSE ) ;
		}
	else
		{
		m_Open.EnableWindow( TRUE ) ;
		m_Delete.EnableWindow( TRUE ) ;
		m_DeleteFile.EnableWindow( TRUE ) ;
		}
}

void CDupplicateFilesDlg::OnDeletefile() 
{
	HTREEITEM hItem	=	m_FileTree.GetNextItem(m_FileTree.GetRootItem(), TVGN_CARET ) ;
	if ( ! hItem )
		return ;

	CString File	=	m_FileTree.GetItemText( hItem ) ;
	if ( File.IsEmpty())
		return ;

	CString	FileToDelete	=	File + "|" ;

	if ( DeleteFiles( FileToDelete ) && ! FileExist( FileToDelete ))
		{
		// Si le fichier selectionne a des fils dans l'arbre, remplacer le texte par le
		// premier fils et enlever celui ci
		// Sinon, enlever ce fichier
		HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
		
		if ( hChildItem )
			{
			CString	ChildText	=	m_FileTree.GetItemText( hChildItem ) ;
			m_FileTree.SetItemText( hItem, ChildText ) ;
			m_FileTree.DeleteItem( hChildItem ) ;
			}
		else
			{
			m_FileTree.DeleteItem( hItem ) ;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////
// DeleteFiles
//	Supprimer des fichiers en les transerfant dans la poubelle
//	La liste de fichiers est donnee dans une Chaine, chaque nom etant separe
//	par un |
///////////////////////////////////////////////////////////////////////////////
BOOL CDupplicateFilesDlg::DeleteFiles(const CString & Files )
{
	const int	NbChars	=	Files.GetLength() ;

	char	*		pFrom	=	new char[NbChars + 1 ] ;
	strcpy( pFrom, Files ) ;
	for ( int i = 0; i < NbChars; i++)
		if ( pFrom[i] == '|' )
			pFrom[i] = 0 ;

	SHFILEOPSTRUCT	St ;
	St.hwnd			=	GetSafeHwnd();
	St.wFunc		=	FO_DELETE  ;
	St.pFrom		=	pFrom ;
	St.pTo			=	NULL ;
	St.fFlags		=	FOF_ALLOWUNDO | FOF_FILESONLY ;	 
	St.fAnyOperationsAborted = FALSE ;    
	St.hNameMappings=	0 ; 
    St.lpszProgressTitle = 0 ;

	const BOOL Res	=	 ! SHFileOperation(&St) ;
	delete []pFrom ;
	return Res ;
}

void CDupplicateFilesDlg::OnDeleteMultiple() 
{
	CMultipleDelete		Dlg ;
	Dlg.m_Directory	=	_CommandLine ;
	if (  Dlg.DoModal() == IDOK )
		{
		switch( Dlg.m_Choice )
			{
			case 0 :
				DeleteAllDuplicated() ;
				break ;

			case 1 :
				DeleteDuplicatedUnderDir( Dlg.m_Directory ) ;
				break ;

			case 2 :
				DeleteDuplicatedContaining( Dlg.m_Mask ) ;
				break ;
			}
		}
}

void CDupplicateFilesDlg::DeleteAllDuplicated()
{

}

void CDupplicateFilesDlg::DeleteDuplicatedUnderDir(const TCHAR * pDir )
{
	CWaitCursor	W ;

	// Browse all item on the list
	CStringArray	FilesToDelete ;
	CDWordArray		ItemList ;
	
	BrowseDuplicatedFilesUnderDir( FilesToDelete, ItemList, pDir ) ;

	DeleteListOfFiles( FilesToDelete, ItemList ) ;
}

void CDupplicateFilesDlg::DeleteDuplicatedContaining(const TCHAR *)
{

}

void CDupplicateFilesDlg::BrowseDuplicatedFilesUnderDir(CStringArray & ListOfFiles, CDWordArray & ItemList, const TCHAR * pDirectory )
{
	// Browse all the items from the list
	HTREEITEM	hParent	=	m_FileTree.GetRootItem() ;
	
	while ( hParent )
		{
		HTREEITEM	hNext	=	m_FileTree.GetNextItem( hParent, TVGN_NEXT ) ;

		if ( m_FileTree.ItemHasChildren(hParent))
			AddFilesFromItemDirectory( hNext, pDirectory, ListOfFiles, ItemList ) ;

		hParent	=	hNext ;
		}	
}

void CDupplicateFilesDlg::DeleteListOfFiles(CStringArray & FilesToDelete, CDWordArray & ItemList)
{
	// Count length of all file names

	int	Len	=	0 ;
	for ( int i = 0; i < FilesToDelete.GetSize(); i++)
		Len	+=	FilesToDelete[i].GetLength() + 1 ;

	char	*		pFrom	=	new char[Len + 1 ] ;
	char	*		pFile	=	pFrom ;

	for ( i = 0; i < FilesToDelete.GetSize(); i++)
		{
		CString	File	=	FilesToDelete[i] ;

		ASSERT( AfxIsValidAddress( pFile, File.GetLength() + 1, TRUE )) ;

		strcpy( pFile, File ) ;
		pFile	+=	File.GetLength() + 1 ;
		}

	pFile[strlen(pFile) + 1] = 0 ;

	SHFILEOPSTRUCT	St ;
	St.hwnd			=	GetSafeHwnd();
	St.wFunc		=	FO_DELETE  ;
	St.pFrom		=	pFrom ;
	St.pTo			=	NULL ;
	St.fFlags		=	FOF_ALLOWUNDO | FOF_FILESONLY ;	 
	St.fAnyOperationsAborted = FALSE ;    
	St.hNameMappings=	0 ; 
    St.lpszProgressTitle = 0 ;

	const BOOL Res	=	 ! SHFileOperation(&St) ;
	delete []pFrom ;

	DeleteFilesFromTree( FilesToDelete, ItemList ) ;
}

void CDupplicateFilesDlg::AddFilesFromItemDirectory(HTREEITEM hItem, const TCHAR * pDir, CStringArray & ListOfFiles, CDWordArray & ItemList )
{
	CStringArray	LocalList ;
	CDWordArray LocalItems ;
	int			NbLeft	=	0 ;

	// Get all the files into a local list

	CString File			=	m_FileTree.GetItemText( hItem ) ;
	if ( FileUnderPath( pDir, File ))
		{
		LocalList.Add( File ) ;
		LocalItems.Add( (DWORD)hItem ) ;
		}
	else
		NbLeft	++ ;

	// Child items
	HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
	while ( hChildItem )
		{
		CString File	=	m_FileTree.GetItemText( hChildItem ) ;
		if ( FileUnderPath( pDir, File ))
			{
			LocalList.Add( File ) ;
			LocalItems.Add( (DWORD)hChildItem ) ;
			}
		else
			NbLeft ++ ;

		hChildItem	=	m_FileTree.GetNextSiblingItem( hChildItem ) ;
		}

	// Check we keep at least one file
	if ( NbLeft == 0 )
		if ( ItemList.GetSize() != 0 )
			{
			LocalList.RemoveAt(0) ;
			LocalItems.RemoveAt(0) ;
			}

	ASSERT( LocalList.GetSize() == LocalList.GetSize()) ;

	// Add the list to the global list
	ListOfFiles.InsertAt( ListOfFiles.GetSize(), &LocalList ) ;
	ItemList.InsertAt( ItemList.GetSize(), &LocalItems ) ;

	ASSERT( ListOfFiles.GetSize() == ItemList.GetSize()) ;
}

BOOL CDupplicateFilesDlg::FileUnderPath(const TCHAR * Dir, const TCHAR * File)
{
	if ( _tcslen( Dir ) >= _tcslen( File ))
		return FALSE ;

	return 0 == _tcsnicmp( Dir, File, _tcslen( Dir )) ;
}

void CDupplicateFilesDlg::DeleteFilesFromTree(CStringArray & ListOfFiles, CDWordArray & ListOfHandles )
{
	ASSERT( ListOfFiles.GetSize() == ListOfHandles.GetSize()) ;


	for ( int i = ListOfFiles.GetUpperBound(); i >= 0; i--)
		{
		CString		File		=	ListOfFiles[i] ;
		HTREEITEM	hItem		=	(HTREEITEM)ListOfHandles[i] ;

#ifdef DEBUG
		CString	Text=	m_FileTree.GetItemText( hItem ) ;
		ASSERT( Text == File ) ;
#endif

		if ( ! FileExist( File ))
			{
			HTREEITEM hChildItem	=	m_FileTree.GetChildItem( hItem ) ;
		
			if ( hChildItem )
				{
				CString	ChildText	=	m_FileTree.GetItemText( hChildItem ) ;
				m_FileTree.SetItemText( hItem, ChildText ) ;
				m_FileTree.DeleteItem( hChildItem ) ;
				}
			else
				{
				m_FileTree.DeleteItem( hItem ) ;
				}
			}
		}
}

int CDupplicateFilesDlg::GetIconIndex(const TCHAR *pFileName)
{
	char	Extension[_MAX_EXT] ;
	_tsplitpath( pFileName, NULL, NULL, NULL, Extension ) ;

	void * ptr	;
	
	if ( m_Extensions.Lookup( Extension, ptr ))
		{
		return  (int)ptr ;
		}
	

	// Ajoute la nouvelle icone

	char Path[_MAX_PATH] ;
	strcpy( Path, pFileName ) ;
	WORD		Index ;
	
	HICON	hIcon	=	ExtractAssociatedIcon( AfxGetInstanceHandle(),	Path, &Index ) ;
	const int	IconIndex	=	_IconList.Add( hIcon ) ;

	m_Extensions.SetAt( Extension, (void*)IconIndex ) ;
	return IconIndex ;
}
