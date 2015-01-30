// GraphicPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "Transparentdesktop.h"
#include "GraphicPropertySheet.h"
#include "FenetreTransparente.h"
#include "Preferences.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL	Attente			=	FALSE ;

#define PLAGE_IMAGES 10000
#define FICHIER_AIDE	"help\\WADHelp.htm"

CGraphicPropertySheet * CGraphicPropertySheet::_pZeOnlyOuane = 0 ;
/////////////////////////////////////////////////////////////////////////////
// CGraphicPropertySheet

IMPLEMENT_DYNAMIC(CGraphicPropertySheet, CPropertySheet)
const UINT	CGraphicPropertySheet::_wTaskBarNotify	=	RegisterWindowMessage( "Message from Taskbar to ActiveDesktop, Lucien PILLONI") ;
const UINT	CGraphicPropertySheet::_wFinEdition	=	RegisterWindowMessage( "End of image edition to ActiveDesktop, Lucien PILLONI") ;

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
// AttenteEdition
//	Cette fonction est lancee dans un thread separe
//	Elle attend que l'editeur graphique soit termine. Si l'editeur n'est pas
//	termine au bout de 10 minutes, on fait savoir a l'utilisateur que c'est
//	inquietant
/////////////////////////////////////////////////////////////////////////////
DWORD	WINAPI	AttenteEdition( LPVOID	lp )
	{
	CGraphicPropertySheet*	pDlg	=	(CGraphicPropertySheet*)lp ;
	ASSERT_VALID( pDlg ) ;	

	BOOL Continue	=	TRUE ;
	do
		{
		if ( WaitForSingleObject( pDlg->_hProcessEdition, 1000*60*10 ) == WAIT_TIMEOUT )
			{
			// Verifier si le process est toujours la
			DWORD ExitCode ;

			GetExitCodeProcess( pDlg->_hProcessEdition, &ExitCode) ;

			if ( ExitCode	== STILL_ACTIVE )
				{
				CString Message, Titre ;
				Message.LoadString( IDS_TIMEOUT_EDIT ) ;
				Titre.LoadString( IDS_TITRE ) ;

				MessageBeep( MB_ICONQUESTION ) ;
				switch( MessageBox( AfxGetMainWnd()->m_hWnd, Message, Titre,
									MB_ICONQUESTION|MB_YESNOCANCEL | MB_SETFOREGROUND | MB_TOPMOST ))
					{
					case IDYES :
						break ;

					case IDNO :
						Continue	= FALSE ;
						break ;

					case IDCANCEL :
						Continue	=	FALSE ;
						TerminateProcess( pDlg->_hProcessEdition, 0 ) ;
						break ;
					}
				}
			}
		else
			Continue = FALSE ;
		}
	while ( Continue ) ;

	// On passe par un PostMessage pour se replacer dans le bon thread
	pDlg->PostMessage( CGraphicPropertySheet::_wFinEdition, 0, 0 ) ;
	return 0 ;
	}


CGraphicPropertySheet::CGraphicPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	ASSERT( _pZeOnlyOuane == 0 ) ;
	_pZeOnlyOuane	=	this ;
	_bPermissionMenu=	TRUE ;
	_NoIcone	=	IDR_MAINFRAME ;
}

CGraphicPropertySheet::CGraphicPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	ASSERT( _pZeOnlyOuane == 0 ) ;
	_pZeOnlyOuane	=	this ;
	_bPermissionMenu=	TRUE ;
	_NoIcone	=	IDR_MAINFRAME ;
}

CGraphicPropertySheet::~CGraphicPropertySheet()
{
}


BEGIN_MESSAGE_MAP(CGraphicPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGraphicPropertySheet)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_REGISTERED_MESSAGE(_wTaskBarNotify, OnTaskBarNotify )
	ON_REGISTERED_MESSAGE(_wFinEdition, OnFinEdition )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicPropertySheet message handlers

int CGraphicPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Ajouter une icone dans la barre de tache
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	tnd.hIcon		= LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE( IDR_MAINFRAME )) ;
	
	LoadString( AfxGetResourceHandle(), IDS_TIP, tnd.szTip, sizeof(tnd.szTip));
	
	Shell_NotifyIcon( NIM_ADD, &tnd);

	_pFenetreTransparente	=	new CFenetreTransparente() ;
	ASSERT_VALID( _pFenetreTransparente ) ;

	_pFenetreTransparente->CreateEx( 0,
									 AfxRegisterWndClass( CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
														  LoadCursor( NULL, IDC_ARROW),
														  (HBRUSH)GetStockObject( NULL_BRUSH ) ),
									 "Transparent desktop",
									 WS_POPUP | WS_VISIBLE,
									 0, 0, 100,100,
									 NULL,
									 NULL,
									 NULL
									 ) ;

	CString ImageCourante	=	CPreferences::FichierImageCourante() ;

	if ( ! ImageCourante.IsEmpty() )
		_pFenetreTransparente->SetBitmap(ImageCourante) ;

	_pFenetreTransparente->SetWindowPos( &wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE ) ;

	// On va cacher la fenetre
	SetTimer( 2, 50, NULL ) ;
	
	return 0;
}


void CGraphicPropertySheet::OnDestroy() 
{
	CPropertySheet::OnDestroy();
	
	// Ajouter une icone dans la barre de tache
	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_MESSAGE;
	tnd.uCallbackMessage	= _wTaskBarNotify ;
	
	Shell_NotifyIcon( NIM_DELETE, &tnd);
}


///////////////////////////////////////////////////////////////////////////////
// Reception des evenements sur la petite icone dans la barre de taches
///////////////////////////////////////////////////////////////////////////////
LONG CGraphicPropertySheet::OnTaskBarNotify(UINT wParam, LONG lParam)
{
	switch( lParam )
		{
		case WM_LBUTTONDOWN :
			///////////////////////////////////////////////////////////////////
			// Passer les notes en premier plan
			///////////////////////////////////////////////////////////////////
			{
			ASSERT_VALID( _pFenetreTransparente ) ;

			// Y'en a bien un qui va marcher !
			_pFenetreTransparente->SetWindowPos( &wndTop, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE ) ;
			_pFenetreTransparente->BringWindowToTop() ;
			_pFenetreTransparente->SetForegroundWindow() ;
			}
			break ;

		case WM_LBUTTONDBLCLK :
			if ( ! Attente )
				EditBackGroundImage() ;
			break ;

		case WM_RBUTTONDOWN :
			AfficheMenu() ;
			break ;
		}

	return 0 ;
}

///////////////////////////////////////////////////////////////////////////////
// Editer l'image
// On lance l'editeur d'image choisi, puis on se place en attente jusqu'a ce que
// celui ci soit fini
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::EditBackGroundImage()
{
	ASSERT_VALID( _pZeOnlyOuane ) ;
	if (! _pZeOnlyOuane )
		return ;

	_pZeOnlyOuane->ShowWindow( SW_HIDE ) ;

	const CString FichierImage	=	CPreferences::FichierImageCourante() ;

	if ( FichierImage.IsEmpty())
		return ;

	CString	LigneCommande( CPreferences::GetImageEditor() ) ;
	LigneCommande += " \"" ;
	LigneCommande += FichierImage ;
	LigneCommande += "\"" ;

	///////////////////////////////////////////////////////////////////////////
	// Recuperer la date courante du fichier a editer pour verifier s'il a
	// ete modifie
	///////////////////////////////////////////////////////////////////////////
	CFileStatus	Status ;
	CFile::GetStatus( FichierImage, Status ) ;
	_pZeOnlyOuane->_DateAvantEdition	=	Status.m_mtime ;

	///////////////////////////////////////////////////////////////////////////
	// Lancer l'editeur
	///////////////////////////////////////////////////////////////////////////
	STARTUPINFO Startup ;
	memset( &Startup, 0, sizeof( Startup )) ;
	Startup.cb	=	sizeof( Startup ) ;

	if ( ! CPreferences::DejaEdite())
		{
		CString Message, Titre ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString(IDS_FIRST_TIME_EDIT) ;

		_pZeOnlyOuane->MessageBox( Message, Titre, MB_OK | MB_ICONINFORMATION | MB_SETFOREGROUND | MB_TOPMOST ) ;

		CPreferences::DejaEdite( TRUE ) ;
		}

	PROCESS_INFORMATION Process ;
	if ( !CreateProcess(	NULL,	(char*)(const char *)LigneCommande, 
							NULL, NULL,	TRUE, CREATE_DEFAULT_ERROR_MODE,
							NULL, NULL,	&Startup, &Process ))
		{
		CString Message, Titre ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString( IDS_CANNOT_LAUNCH ) ;
		_pZeOnlyOuane->MessageBox( Message, Titre, MB_OK | MB_SETFOREGROUND );
		}
	else
		{
		///////////////////////////////////////////////////////////////////////
		// Lancement reussi, mise en attente du programme
		///////////////////////////////////////////////////////////////////////
		_pZeOnlyOuane->SetTimer( 3, 200, 0 ) ;
		Attente	=	TRUE ;
		_pZeOnlyOuane->_hProcessEdition	=	Process.hProcess ;
		DWORD Id ;

		PermetMenu( FALSE ) ;
		CreateThread( NULL, 0, AttenteEdition, (LPDWORD)_pZeOnlyOuane, 0, &Id ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// FinEdition
// Traitement de la fin de l'edition de l'image
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::FinEdition()
{
	PermetMenu() ;

	KillTimer( 3 ) ;

	// Noter la fin de l'attente
	Attente	=	FALSE ;

	CString Tip ;
	Tip.LoadString( IDS_TIP ) ;

	ChangeTrayIcone( IDR_MAINFRAME, Tip ) ;

	if ( ImageModifiee())
		ChangeImageDeFond() ;
}


void CGraphicPropertySheet::OnTimer(UINT nIDEvent) 
{
	switch( nIDEvent )
		{
		case 2 :
			ShowWindow( SW_HIDE ) ;
			KillTimer( 2 ) ;	
			break ;

		case 3 :
			{
			switch( _NoIcone )
				{
				case IDR_MAINFRAME :
					_NoIcone	=	IDR_MAINFRAME1 ;
					break ;
				case IDR_MAINFRAME1 :
					_NoIcone	=	IDR_MAINFRAME2 ;
					break ;
				case IDR_MAINFRAME2 :
					_NoIcone	=	IDR_MAINFRAME3 ;
					break ;
				default :
					_NoIcone	=	IDR_MAINFRAME ;
					break ;
				}

			CString Tip ;
			Tip.LoadString( IDS_TIP_WAIT_EDITOR ) ;
			ChangeTrayIcone( _NoIcone, Tip ) ;
			}
			break ;
		}
				
	CPropertySheet::OnTimer(nIDEvent);
}

///////////////////////////////////////////////////////////////////////////////
// OnCommand
// REception des commandes du menu
///////////////////////////////////////////////////////////////////////////////
BOOL CGraphicPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch( wParam )
		{
		case ID_CONFIGURE :
			// Ouverture de la boite de configuration
			PermetMenu( FALSE ) ;
			ShowWindow( SW_SHOW ) ;
			break ;

		case ID_EDITERLIM :
			// Edition de l'image
			EditBackGroundImage() ;
			break ;

		case IDOK :
			// Cacher la boite de configuration
			PermetMenu( TRUE ) ;
			ShowWindow( SW_HIDE ) ;
			break ;

		case IDCANCEL :
		case ID_APPLY_NOW :
			// Ignorer ces commandes
			break ;


		case ID_EXIT :
			// Fin
			EndDialog( TRUE ) ;
			break ;

		case ID_ABOUT :
			// Boite a propos de
			{
			PermetMenu( FALSE ) ;
			CAboutDlg	Dlg ;
			Dlg.DoModal() ;
			PermetMenu( TRUE ) ;
			}
			break ;

		case IDHELP :
			AfficheAide("Configuration") ;
			break ;

		case ID_F_HELP :
			AfficheAide() ;
			break ;

		default :
			if ( (int)wParam >= PLAGE_IMAGES  && (int)wParam < PLAGE_IMAGES +CPreferences::NbPages())
				{
				if ( CPreferences::SetImageCourante( (int)wParam-PLAGE_IMAGES ))
					_pFenetreTransparente->SetBitmap(CPreferences::FichierImageCourante()) ;
				}
			return CPropertySheet::OnCommand(wParam, lParam);
		}

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// Changer l'image de fond
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::ChangeImageDeFond()
{
	ASSERT_VALID( _pFenetreTransparente ) ;

	CString Image	=	CPreferences::FichierImageCourante() ;

	if ( !Image.IsEmpty() && _pFenetreTransparente )
		_pFenetreTransparente->SetBitmap(Image) ;
}


///////////////////////////////////////////////////////////////////////////////
// INitialisation de la fenetre
///////////////////////////////////////////////////////////////////////////////
BOOL CGraphicPropertySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	::DestroyWindow	( ::GetDlgItem( m_hWnd, IDCANCEL )) ;
	::DestroyWindow	( ::GetDlgItem( m_hWnd, ID_APPLY_NOW )) ;

	// Changer le texte du bouton OK
	CString	Button ;
	Button.LoadString( IDS_BUTTON ) ;
	::SetWindowText( ::GetDlgItem( m_hWnd, IDOK ), Button ) ;
	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// ImageModifiee
//	Determiner si l'image a ete modifiee par l'editeur graphique
//	On a memorise la date de modif du fichier avant edition et on la compare a
//	la nouvelle
///////////////////////////////////////////////////////////////////////////////
BOOL CGraphicPropertySheet::ImageModifiee()
{
	CFileStatus	Status ;
	CFile::GetStatus( CPreferences::FichierImageCourante(), Status ) ;

	if (  Status.m_mtime == _DateAvantEdition )
		{
		///////////////////////////////////////////////////////////////////////
		// Le fichier n'a pas change, on demande a l'utilisateur s'il veut
		// quand meme rescruter l'image
		///////////////////////////////////////////////////////////////////////
		CString Message ;
		CString Titre ;

		Message.LoadString( IDS_IMAGE_NON_MODIFIEE ) ;
		Titre.LoadString( IDS_TITRE ) ;

		MessageBeep( MB_ICONQUESTION ) ;
		if ( MessageBox( Message, Titre,
						 MB_ICONQUESTION | MB_YESNO | MB_SETFOREGROUND | MB_TOPMOST | MB_DEFBUTTON2 )
			== IDNO )
			return FALSE ;
		}

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// CompleteSousMenu
//	Complete le sous menu avec les noms des pages
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::CompleteSousMenu(CMenu * pMenu)
{
	ASSERT_VALID( pMenu ) ;

	if ( ! pMenu )
		return ;
	CMenu * pSousMenu	= pMenu->GetSubMenu( 0 ) ;

	if ( ! pSousMenu )
		return ;

	ASSERT_VALID( pSousMenu ) ;

	pSousMenu->DeleteMenu( ID_F_DISPLAY_XXX, MF_BYCOMMAND ) ;

	const int NbImages	= CPreferences::NbPages() ;

	for ( int i = 0; i < NbImages; i++)
		pSousMenu->AppendMenu( MF_STRING, PLAGE_IMAGES+i, CPreferences::NomImage(i) ) ;

	pSousMenu->CheckMenuRadioItem(	PLAGE_IMAGES, PLAGE_IMAGES + NbImages -1,
									CPreferences::GetNoImageCourante() + PLAGE_IMAGES,
									MF_BYCOMMAND ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Permettre ou non l'acces au menu
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::PermetMenu(BOOL bPermission)
{
	ASSERT_VALID( _pZeOnlyOuane ) ;

	if ( ! _pZeOnlyOuane )
		return ;
	
	_pZeOnlyOuane->_bPermissionMenu 	=	bPermission ;

	if ( bPermission )
		ChangeTrayIcone( IDR_MAINFRAME ) ;
	else
		ChangeTrayIcone( IDR_WAITING ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Reception du message en provenance du thread qui attendait la fin de
// l'editeur d'images
///////////////////////////////////////////////////////////////////////////////
UINT CGraphicPropertySheet::OnFinEdition(UINT wParam, LONG lParam)
{
	FinEdition() ;
	return 0 ;
}

///////////////////////////////////////////////////////////////////////
// Affichage de l'aide
// Actuellement, on utilise un fichier d'aide au format HTML, parce que
// c'est a la mode et que c'est plus simple a ecrire.
// ENTREES :	NULL ou Nom de la rubrique a l'interieur du fichier d'aide
///////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::AfficheAide( const char * pRubrique  )
{
	STARTUPINFO	Startup ;
	Startup.cb	=	sizeof( Startup ) ;

	char Dir[_MAX_PATH] ;
	GetCurrentDirectory( sizeof( Dir ) , Dir ) ;

	///////////////////////////////////////////////////////////////////////////
	// Aller eventuellement directement vers une rubrique
	///////////////////////////////////////////////////////////////////////////
	if ( ShellExecute( m_hWnd, "open", FICHIER_AIDE, pRubrique, Dir, SW_SHOW ) <= (HINSTANCE)32 )
		{
		CString Message, Titre ;
		Message.LoadString( IDS_CANNOT_HELP ) ;
		Titre.LoadString( IDS_TITRE ) ;

		MessageBeep( MB_ICONSTOP ) ;
		MessageBox( Message, Titre, MB_ICONSTOP | MB_OK | MB_SETFOREGROUND ) ;
		}
}

///////////////////////////////////////////////////////////////////////
// Affichage du menu
///////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::AfficheMenu()
{
	ASSERT_VALID( _pZeOnlyOuane ) ;
	if (! _pZeOnlyOuane )
		return ;

	if ( _pZeOnlyOuane->_bPermissionMenu && ! Attente )
		{
		// Afficher le menu 
		CMenu Menu ;
		if ( ! Menu.LoadMenu( IDR_MENU ))
			return ;
		ASSERT_VALID( &Menu ) ;

		CMenu * pSousMenu	=	Menu.GetSubMenu(0 ) ;

		if ( pSousMenu )
			{
			ASSERT_VALID( pSousMenu ) ;

			_pZeOnlyOuane->CompleteSousMenu( pSousMenu ) ;

			CPoint	Pt ;
			GetCursorPos( &Pt );

			pSousMenu->TrackPopupMenu(	TPM_RIGHTALIGN | TPM_RIGHTBUTTON,
										Pt.x, Pt.y,
										_pZeOnlyOuane ) ;
			}
		}
}


///////////////////////////////////////////////////////////////////////////////
// ChangeTrayIcone, publique, statique
// Change l'icone dans la tray bar et eventuellement le tip
// ENTREES	:	No d'icone dans les ressources
//				Nouveau tip ou NULL si pas de changement
///////////////////////////////////////////////////////////////////////////////
void CGraphicPropertySheet::ChangeTrayIcone(UINT NoIcone, const char * pTip )
{
	NOTIFYICONDATA tnd;
	ASSERT_VALID( _pZeOnlyOuane ) ;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= _pZeOnlyOuane->m_hWnd;
	tnd.uID			= 1;

	tnd.uFlags		= NIF_ICON ;

	if ( pTip )
		{
		tnd.uFlags	|=	NIF_TIP ;
		strcpy( tnd.szTip, pTip );
		}

	tnd.hIcon		= LoadIcon( AfxGetResourceHandle(), MAKEINTRESOURCE( NoIcone )) ;
	
	Shell_NotifyIcon( NIM_MODIFY, &tnd);
}
