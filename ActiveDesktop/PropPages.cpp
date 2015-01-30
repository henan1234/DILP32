// PropPages.cpp : implementation file
//

#include "stdafx.h"
#include "activedesktop.h"
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropPages message handlers

BOOL CPropPages::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
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
		
		m_Liste.SetItem( i, 1, LVIF_TEXT, CPreferences::PassWordProtected(i) ? Oui : Non, 0, 0, 0, 0 ) ;
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
			
		m_Liste.SetItem( i, 1, LVIF_TEXT, CPreferences::PassWordProtected(i) ? Oui : Non, 0, 0, 0, 0 ) ;
		}
}

BOOL CPropPages::OnSetActive() 
{
	CActiveDesktopApp*	pApp	=	(CActiveDesktopApp*)AfxGetApp() ;
	ASSERT_VALID( pApp ) ;

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
		m_ChangePass.EnableWindow( TRUE ) ;
		m_CheckPassword.EnableWindow( TRUE ) ;
		m_Delete.EnableWindow( TRUE ) ;
		}
	
	return CPropertyPage::OnSetActive();
}

void CPropPages::OnBeginlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CPropPages::OnEndlabeleditList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM	* pItem	=	&pDispInfo->item ;
	CPreferences::RenommeImage( pItem->iItem, pItem->pszText ) ;

	*pResult = 0;

	m_Liste.SetItem(  pItem ) ;
}

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
		MessageBox( Message, Titre, MB_OK | MB_ICONSTOP ) ;
		}
	else
		{
		// Confirmation
		CString Titre, Message ;
		Titre.LoadString( IDS_TITRE ) ;
		Message.LoadString( IDS_CONFIRM_SUPP_IMAGE ) ;

		MessageBeep( MB_ICONQUESTION ) ;
		if ( MessageBox( Message, Titre, MB_ICONQUESTION | MB_YESNO ) == IDYES )
			{
			CPreferences::SupprimeImage( ItemSelected ) ;
			m_Liste.DeleteItem( ItemSelected ) ;
			}
		}
}

void CPropPages::OnMdpChange() 
{
	// Suppression de numero de page
	const int ItemSelected = m_Liste.GetNextItem( -1,  LVNI_SELECTED ) ;

	if ( ItemSelected == -1 )
		return ;

	CChangeMotDePasse	Dlg( this ) ;

	if ( Dlg.DoModal() == IDOK )
		{
		CPreferences::ChangeMotDePasse( ItemSelected, Dlg.m_Password ) ;
		}
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
}
