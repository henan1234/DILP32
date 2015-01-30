// PropPages.cpp : implementation file
//

#include "stdafx.h"
#include "Transparentdesktop.h"
#include "PropPages.h"
#include "preferences.h"
#include "ChangeMotDePasse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropPages property page

IMPLEMENT_DYNCREATE(CPropPages, CPropertyPage)

CPropPages::CPropPages() : CPropertyPage(CPropPages::IDD)
{
	//{{AFX_DATA_INIT(CPropPages)
	//}}AFX_DATA_INIT
}

CPropPages::~CPropPages()
{
}

void CPropPages::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropPages)
	DDX_Control(pDX, IDC_IMPORT, m_Import);
	DDX_Control(pDX, IDC_MDP_CHANGE, m_ChangePass);
	DDX_Control(pDX, IDC_BUTTON2, m_Ajoute);
	DDX_Control(pDX, IDC_DELETE, m_Delete);
	DDX_Control(pDX, IDC_PROTEGE, m_CheckPassword);
	DDX_Control(pDX, IDC_LIST1, m_Liste);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPropPages, CPropertyPage)
	//{{AFX_MSG_MAP(CPropPages)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST1, OnBeginlabeleditList1)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST1, OnEndlabeleditList1)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_MDP_CHANGE, OnMdpChange)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_PROTEGE, OnProtege)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPages message handlers

/////////////////////////////////////////////////////////////////////////////
// Initialisationd de la page
/////////////////////////////////////////////////////////////////////////////
BOOL CPropPages::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	///////////////////////////////////////////////////////////////////////////
	// Creation des colonnes dans la liste
	///////////////////////////////////////////////////////////////////////////
	CString	Message ;
	Message.LoadString( IDS_COLONNE_NOM ) ;
	m_Liste.InsertColumn(0, Message, LVCFMT_LEFT, 200 ) ;

	Message.LoadString( IDS_COLONNE_PASSWORD ) ;
	m_Liste.InsertColumn(1, Message, LVCFMT_LEFT, 100 ) ;

	const int NbPages	=	CPreferences::NbPages() ;
	CString	Oui, Non ;
	Oui.LoadString( IDS_OUI ) ;
	Non.LoadString( IDS_NON ) ;

	for ( int i = 0; i < NbPages; i++)
		{
		m_Liste.InsertItem( i, CPreferences::NomImage(i) ) ;
		
		m_Liste.SetItem( i, 1, LVIF_TEXT, CPreferences::Protege(i) ? Oui : Non, 0, 0, 0, 0 ) ;
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CPropPages::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.dwExStyle |= 	WS_EX_TOPMOST ;
	return CPropertyPage::PreCreateWindow(cs);
}

void CPropPages::OnButton2() 
{
	if ( CPreferences::AjoutePage())
		{
		const int NbPages	=	CPreferences::NbPages() ;
		const int i = NbPages-1 ;

		CString	Oui, Non ;
		Oui.LoadString( IDS_OUI ) ;
		Non.LoadString( IDS_NON ) ;

		m_Liste.InsertItem( i, CPreferences::NomImage(i) ) ;
			
		m_Liste.SetItem( i, 1, LVIF_TEXT, CPreferences::Protege(i) ? Oui : Non, 0, 0, 0, 0 ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// La page devient active
// En mode shareware, griser certains boutons
///////////////////////////////////////////////////////////////////////////////
BOOL CPropPages::OnSetActive() 
{
	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;
	
	///////////////////////////////////////////////////////////////////////////
	// Protection SHAREWARE
	///////////////////////////////////////////////////////////////////////////
	if ( CActiveDesktopApp::IsShareWare())
		{
		m_Ajoute.EnableWindow( FALSE ) ;
		m_ChangePass.EnableWindow( FALSE ) ;
		m_CheckPassword.EnableWindow( FALSE ) ;
		m_Delete.EnableWindow( FALSE ) ;
		}
	else
		{
		m_Ajoute.EnableWindow( TRUE ) ;
		m_ChangePass.EnableWindow( ItemSelected != -1  ) ;
		m_CheckPassword.EnableWindow( ItemSelected != -1 ) ;
		m_Delete.EnableWindow( ItemSelected != -1
							   && ItemSelected != CPreferences::GetNoImageCourante() ) ;
		}

	
	return CPropertyPage::OnSetActive();
}

///////////////////////////////////////////////////////////////////////////////
// Debut d'edition d'un nom de page.
// Signaler au systeme qu'on est d'accord pour commencer l'edition
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnBeginlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Fin de l'edition d'un nom de page
// Memoriser le nouveau nom
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM	* pItem	=	&pDispInfo->item ;
	CPreferences::RenommeImage( pItem->iItem, pItem->pszText ) ;

	*pResult = 0;

	m_Liste.SetItem(  pItem ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Suppression d'une page
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnDelete() 
{
	// Suppression de numero de page
	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;

	if ( ItemSelected == -1 )
		return ;

	if ( ItemSelected == CPreferences::GetNoImageCourante())
		{
		// Impossible de supprimer l'image courante
		CString Titre, Message ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString( IDS_SUPP_IMAGE_COURANTE ) ;

		MessageBeep( MB_ICONSTOP ) ;
		MessageBox( Message, Titre, MB_OK | MB_ICONSTOP | MB_SETFOREGROUND ) ;
		}
	else
		{
		// Confirmation
		CString Titre, Message ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString( IDS_CONFIRM_SUPP_IMAGE ) ;

		MessageBeep( MB_ICONQUESTION ) ;
		if ( MessageBox( Message, Titre, MB_ICONQUESTION | MB_YESNO | MB_SETFOREGROUND ) == IDYES )
			{
			CPreferences::SupprimeImage( ItemSelected ) ;
			m_Liste.DeleteItem( ItemSelected ) ;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////
// OnMdpChange
// Changement du mot de passe, on appelle la boite de dialogue de saisie du
// nouveau mot de passe
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnMdpChange() 
{
	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;
	if ( ItemSelected == -1 )
		return ;

	CChangeMotDePasse	Dlg( this ) ;

	if ( Dlg.DoModal() == IDOK )
		CPreferences::ChangeMotDePasse( ItemSelected, Dlg.m_Password ) ;
}



///////////////////////////////////////////////////////////////////////////////
// Selection d'une nouvelle page dans la liste, mettre a jour la checkbox du
// mot de passe
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	*pResult = 0;

		// Suppression de numero de page
	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;
	if ( ItemSelected == -1 )
		return ;

	m_CheckPassword.SetCheck( CPreferences::Protege( ItemSelected ) ? 1 : 0 ) ;

	if ( ! CActiveDesktopApp::IsShareWare())
		{
		m_ChangePass.EnableWindow( ItemSelected != -1  ) ;
		m_CheckPassword.EnableWindow( ItemSelected != -1 ) ;
		m_Delete.EnableWindow( ItemSelected != -1
							   && ItemSelected != CPreferences::GetNoImageCourante() ) ;
		}

}

///////////////////////////////////////////////////////////////////////////////
// Clic sur la check box de protection par mot de passe
///////////////////////////////////////////////////////////////////////////////
void CPropPages::OnProtege() 
{
	// Recuperation de la page selectionnee
	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;
	if ( ItemSelected == -1 )
		return ;

	// Mise a jour de la protection
	BOOL	Protege	=	! CPreferences::Protege( ItemSelected ) ;

	// Changement de protection, avec eventuellement saisie du mot de passe actuel
	CPreferences::Protege( ItemSelected, Protege ) ;

	// Mise a jour de la checkbox
	Protege	=	CPreferences::Protege( ItemSelected ) ;
	m_CheckPassword.SetCheck( Protege ? 1 : 0 ) ;

	// Mise a jour du texte dans la liste
	CString	Texte ;
	Texte.LoadString( Protege ? IDS_OUI : IDS_NON ) ;
	m_Liste.SetItem( ItemSelected, 1, LVIF_TEXT, Texte, 0, 0, 0, 0 ) ;
}

void CPropPages::OnImport() 
{
	CFileDialog	Dlg( TRUE, "*.BMP", NULL,
					 OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
					 "Bitmap files (*.BMP)|*.BMP||",
					 this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		if ( CPreferences::ImportPage( Dlg.GetPathName()))
			{
			const int NoPage	=	CPreferences::NbPages() - 1 ;

			m_Liste.InsertItem( NoPage, CPreferences::NomImage(NoPage) ) ;
		
			CString	Oui, Non ;
			Oui.LoadString( IDS_OUI ) ;
			Non.LoadString( IDS_NON ) ;
			m_Liste.SetItem( NoPage, 1, LVIF_TEXT, CPreferences::Protege(NoPage) ? Oui : Non, 0, 0, 0, 0 ) ;
			}
		}
}
