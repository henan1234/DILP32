// SoftCollectionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoftCollection.h"
#include "SoftCollectionDlg.h"
#include "DlgProxy.h"
#include "choosfol.h"
#include "element.h"
#include "media.h"
#include "fileservices.h"
#include "repertoire.h"
#include "fichier.h"
#include "recherche.h"

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
// CSoftCollectionDlg dialog

IMPLEMENT_DYNAMIC(CSoftCollectionDlg, CDialog);

CSoftCollectionDlg::CSoftCollectionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoftCollectionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoftCollectionDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CSoftCollectionDlg::~CSoftCollectionDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CSoftCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoftCollectionDlg)
	DDX_Control(pDX, ID_MEDIAS_SUPPRIMER, m_BoutonSupprimerMedia);
	DDX_Control(pDX, IDC_ATTRIBUTS, m_Attributs);
	DDX_Control(pDX, IDC_CONTENUMEDIA, m_ContenuMedia);
	DDX_Control(pDX, IDC_LISTEMEDIAS, m_ListeMedias);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoftCollectionDlg, CDialog)
	//{{AFX_MSG_MAP(CSoftCollectionDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_COMMAND(ID_MEDIAS_AJOUTER, OnMediasAjouter)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTEMEDIAS, OnItemchangedListemedias)
	ON_NOTIFY(TVN_SELCHANGED, IDC_CONTENUMEDIA, OnSelchangedContenumedia)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LISTEMEDIAS, OnEndlabeleditListemedias)
	ON_COMMAND(ID_RECHERCHE_CHERCHER, OnRechercheChercher)
	ON_BN_CLICKED(ID_MEDIAS_SUPPRIMER, OnMediasSupprimer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionDlg message handlers

BOOL CSoftCollectionDlg::OnInitDialog()
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
	
	// Charge le menu
	CMenu	Menu	;
	Menu.LoadMenu( IDR_MENU1 ) ;
	SetMenu( &Menu ) ;
	
	
	// ImageList de la liste des medias
	_ImageListMedias.Create( GetSystemMetrics( SM_CXICON ),
							 GetSystemMetrics( SM_CYICON ),
							 ILC_MASK | ILC_COLOR16,
							 1, 1 ) ;

	_ImageListMedias.Add( AfxGetApp()->LoadIcon( IDI_MEDIA )) ;

	m_ListeMedias.SetImageList( &_ImageListMedias, LVSIL_NORMAL ) ;

	_iSelected		=	-1 ;

	// ImageListe du contenu des medias
	_ImageListContenus.Create(	GetSystemMetrics( SM_CXSMICON ),
								GetSystemMetrics( SM_CYSMICON ),
								ILC_MASK | ILC_COLOR16,
								1, 1 ) ;
	CRepertoire::IndiceImage	=	_ImageListContenus.Add( AfxGetApp()->LoadIcon( IDI_DOSSIER )) ;
	CFichier::IndiceImage		=	_ImageListContenus.Add( AfxGetApp()->LoadIcon( IDI_FICHIER )) ;

	m_ContenuMedia.SetImageList( & _ImageListContenus, TVSIL_NORMAL ) ;

	m_Attributs.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINECOLD ) ;
	m_Attributs.InsertColumn( 0, "Nom", LVCFMT_LEFT, 100 ) ;
	m_Attributs.InsertColumn( 1, "Valeur", LVCFMT_LEFT, 200 ) ;

	m_BoutonSupprimerMedia.EnableWindow( FALSE ) ;

	ChargeCatalogues() ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoftCollectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoftCollectionDlg::OnPaint() 
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
HCURSOR CSoftCollectionDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CSoftCollectionDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnCancel();
}

void CSoftCollectionDlg::OnOK() 
{
/*	if (CanExit())
		CDialog::OnOK();*/
}

void CSoftCollectionDlg::OnCancel() 
{
/*	if (CanExit())
		CDialog::OnCancel();*/
}

BOOL CSoftCollectionDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}


	return TRUE;
}

void CSoftCollectionDlg::OnMediasAjouter() 
{
	CChooseFolder dlg(	NULL, this ) ;

	if ( dlg.DoModal() == IDCANCEL )
		return ;

	AjouteMedia( dlg.GetDirName()) ;
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute un nouveau media
///////////////////////////////////////////////////////////////////////////////
void CSoftCollectionDlg::AjouteMedia(const CString &Media)
{
	CWaitCursor wait ;

	CMedia	*media	=	new CMedia ;
	if ( ! media->Scan( Media ))
		{
		delete media ;
		return ;
		}

	// Ajoute le media dans le tableau
	if ( AjouteMedia( media ))
		{
		// Ajoute le media dans la liste des medias
		int n = m_ListeMedias.GetItemCount() ;
		m_ListeMedias.InsertItem( n, media->MediaName(), 0 ) ;
		m_ListeMedias.EnsureVisible( n, FALSE ) ;
		m_ListeMedias.SetItemState( n, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED ) ;

		//SelectionneMedia( media->MediaName() ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// Ajoute un media dans le tableau des medias
///////////////////////////////////////////////////////////////////////////////
BOOL CSoftCollectionDlg::AjouteMedia(CMedia *pMedia)
{
	ASSERT( _TableauMedias.GetSize() == _NomsFichiers.GetSize()) ;
	try
		{
		_TableauMedias.Add( pMedia ) ;

		CString Fichier	=	NomFichierUnique() ;
		_NomsFichiers.Add( Fichier ) ;
		pMedia->Sauve( Fichier );
		}
	catch( CMemoryException e )
		{
		const int Min	=	min( _TableauMedias.GetSize(), _NomsFichiers.GetSize()) ;
		_TableauMedias.SetSize( Min ) ;
		_NomsFichiers.SetSize( Min ) ;
		MessageBox( "Pas assez de memoire", "Erreur", MB_OK | MB_ICONSTOP ) ;
		return FALSE ;
		}

	return TRUE ;
}

int CSoftCollectionDlg::GetIndiceMedia(const CString &MediaName)
{
	const int NbMedias	=	_TableauMedias.GetSize() ;
	for ( int i = 0; i < NbMedias; i++)
		{
		if ( _TableauMedias[i]->MediaName() == MediaName )
			return i ;
		}
	return -1 ;
}

CMedia* CSoftCollectionDlg::TrouveMedia(const CString &MediaName)
{
	const int NbMedias	=	_TableauMedias.GetSize() ;
	for ( int i = 0; i < NbMedias; i++)
		{
		if ( _TableauMedias[i]->MediaName() == MediaName )
			return _TableauMedias[i] ;
		}
	return NULL ;
}


void CSoftCollectionDlg::OnItemchangedListemedias(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;
	
	if ( pNMListView->uNewState == pNMListView->uOldState )
		return ;

	if ( pNMListView->uNewState & LVIS_SELECTED )
		SelectionneMedia( pNMListView->iItem ) ;

	m_BoutonSupprimerMedia.EnableWindow( pNMListView->iItem != -1 ) ;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CSoftCollectionDlg::SelectionneMedia(const CString &MediaName)
{
	// Selection dans le controle
	int indiceItem	=	GetIndiceMedia( MediaName ) ;
	if ( indiceItem == -1 )
		return ;

	SelectionneMedia( indiceItem ) ;
}


void CSoftCollectionDlg::SelectionneMedia(int indiceItem)
{
	const int NbMedias	=	_TableauMedias.GetSize() ;

	if ( indiceItem < 0 || indiceItem>= NbMedias )
		return ;

	m_ListeMedias.EnsureVisible( indiceItem, FALSE ) ;
	m_ListeMedias.SetItemState( indiceItem, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED ) ;

	if ( _iSelected != -1 )
		{
		CMedia * pMedia	=	_TableauMedias[_iSelected] ;
		pMedia->Sauve( _NomsFichiers[_iSelected] ) ;
		pMedia->Vide() ;
		}

	_iSelected		=	indiceItem ;

	// Trouve le media dont on a donne le nom
	CMedia * pMedia	=	_TableauMedias[indiceItem] ;
	if ( pMedia == NULL )
		return ;

	// Remplit l'arbre avec le contenu du media
	CWaitCursor w ;
	m_ContenuMedia.DeleteAllItems() ;
	m_ContenuMedia.SetRedraw( FALSE ) ;
	pMedia->Remplit( m_ContenuMedia ) ;
	m_ContenuMedia.Expand( m_ContenuMedia.GetRootItem(), TVE_EXPAND ) ;
	m_ContenuMedia.SetRedraw( TRUE ) ;
	m_ContenuMedia.Invalidate() ;
}

void CSoftCollectionDlg::OnSelchangedContenumedia(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	HTREEITEM	hItem	=	pNMTreeView->itemNew.hItem ;
	// Retrouve le media selectionne

	const int NbMedias		=	_TableauMedias.GetSize() ;
	const int IndiceMedia	=	m_ListeMedias.GetNextItem( -1, LVNI_SELECTED ) ;

	if ( IndiceMedia	< 0 || IndiceMedia > NbMedias )
		return ;

	CMedia	* pMedia	=	_TableauMedias[IndiceMedia] ;
	
	// Retrouve l'objet dans le media
	CElement	* pElement	=	pMedia->TrouveElement( hItem ) ;
	if ( ! pElement )
		return ;

	// Remplit le panel description
	m_Attributs.DeleteAllItems() ;

	const int Nb	=	pElement->GetNbAttributs() ;
	int	Indice		=	0 ;
	for ( int i = 0; i < Nb; i ++)
		{
		CString	Nom	=	pElement->GetNom(i) ;
		CString Valeur=	pElement->GetAttribut(i) ;

		if ( ! Nom.IsEmpty() && ! Valeur.IsEmpty())
			{
			Indice	=	m_Attributs.InsertItem( Indice, Nom, 0 ) ;
			m_Attributs.SetItem( Indice, 1, LVIF_TEXT, Valeur, 0, 0, 0, 0 ) ;
			}
		}

	UpdateData( FALSE ) ;
}

CString CSoftCollectionDlg::NomFichierUnique()
{
	char Path[_MAX_PATH ] ;
	GetModuleFileName( NULL, Path, sizeof( Path )) ;

	CString FileName	=	CFileServices::ChangeExtension( Path, "MEDIA" ) ;
	return CFileServices::GetNonExistingFileName( FileName ) ;
}


///////////////////////////////////////////////////////////////////////////////
// Fin de l'edition du label d'un media, prendre en compte le nouveau nom

///////////////////////////////////////////////////////////////////////////////
void CSoftCollectionDlg::OnEndlabeleditListemedias(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	*pResult = 0;

	// Recuperer no d'item selectionne
	const int Indice	=	pDispInfo->item.iItem ;
	const int NbMedias		=	_TableauMedias.GetSize() ;

	if ( Indice < 0 || Indice > NbMedias )
		return ;

	// Recuperer nouveau texte
	CString	Texte		=	pDispInfo->item.pszText ;
	if ( Texte.IsEmpty())
		{
		MessageBox( "Veuillez saisir un nom de média", "Erreur", MB_ICONWARNING | MB_OK ) ;
		return ;
		}
	

	CMedia*	pMedia	=	_TableauMedias[Indice] ;
	if ( Texte == pMedia->MediaName())
		{
		// Meme texte, rien a faire
		return ;
		}

	// Verifier unicite du texte
	for ( int i = 0; i < NbMedias; i++)
		if ( Texte	==	pMedia->MediaName())
			{
			MessageBox( "Ce nom existe déjà dans la liste des médias", "Erreur", MB_ICONWARNING | MB_OK ) ;
			return ;
			}

	// Stocker nouveau texte
	pMedia->MediaName( Texte ) ;
	pMedia->Sauve( _NomsFichiers[Indice] ) ;

	m_ListeMedias.SetItem( Indice, 0, LVIF_TEXT, Texte, 0, 0, 0, 0 ) ;
}

void CSoftCollectionDlg::ChargeCatalogues()
{
	char Path[_MAX_PATH ] ;
	GetModuleFileName( NULL, Path, sizeof( Path )) ;

	CString Repertoire	=	CFileServices::GetParentDirectory( Path ) ;
	CString Mask		=	CFileServices::Concat( Repertoire, "*.MEDIA" ) ;

	WIN32_FIND_DATA	data ;
	HANDLE	hFind	=	FindFirstFile( Mask, &data ) ;
	BOOL	Continue	=	TRUE ;
	while( Continue )
		{
		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			CString CompletePath	=	CFileServices::Concat( Repertoire, data.cFileName ) ;

			CElement * pElement = NULL ;

			if( ! (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ))
				{
				CMedia	* pMedia	=	new CMedia() ;
				if ( pMedia->Charge( CompletePath ))
					{
					_TableauMedias.Add( pMedia ) ;
					_NomsFichiers.Add( CompletePath ) ;

					int n = m_ListeMedias.GetItemCount() ;
					m_ListeMedias.InsertItem( n, pMedia->MediaName(), 0 ) ;
					pMedia->Vide() ;
					}
				else
					delete pMedia ;

				}
			}
		Continue	=	FindNextFile( hFind, &data ) ;
		}

	FindClose( hFind ) ;

}

void CSoftCollectionDlg::OnRechercheChercher() 
{
	CRecherche dlg( this, _TableauMedias ) ;
	
	dlg.DoModal() ;
}

void CSoftCollectionDlg::OnMediasSupprimer() 
{
	const int	IndiceMedia	=	m_ListeMedias.GetNextItem( -1, LVNI_SELECTED ) ;
	if ( IndiceMedia < 0 || IndiceMedia >= _TableauMedias.GetSize() )
		return ;

	CMedia*	pMedia	=	_TableauMedias[IndiceMedia] ;

	CString Message ;
	Message.Format( "Voulez-vous vraiment supprimer le média %s ?", (const char*)pMedia->MediaName()) ;

	if ( MessageBox( Message, "Suppression", MB_OKCANCEL | MB_ICONQUESTION ) == IDCANCEL )
		return ;

	// Supprime le media du tableau
	_TableauMedias.RemoveAt( IndiceMedia, 1 ) ;

	// Supprime le fichier du media
	DeleteFile( _NomsFichiers[IndiceMedia] ) ;
	_NomsFichiers.RemoveAt( IndiceMedia, 1 ) ;

	// Supprime de la liste des medias
	_iSelected	=	-1 ;
	m_ListeMedias.DeleteItem( IndiceMedia ) ;
	delete pMedia ;
}
