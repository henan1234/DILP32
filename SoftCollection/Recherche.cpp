// Recherche.cpp : implementation file
//

#include "stdafx.h"
#include "SoftCollection.h"
#include "Recherche.h"
#include "element.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecherche dialog


CRecherche::CRecherche(CWnd* pParent, CArray<CMedia*, CMedia*> & Medias )
	: CDialog(CRecherche::IDD, pParent),
	_TableauMedias( Medias )
{
	//{{AFX_DATA_INIT(CRecherche)
	m_Texte = _T("");
	m_TousAttributs = -1;
	//}}AFX_DATA_INIT
}


void CRecherche::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecherche)
	DDX_Control(pDX, IDC_TEXTE, m_TexteCtrl);
	DDX_Control(pDX, IDC_CHERCHER, m_Chercher);
	DDX_Control(pDX, IDC_RESULTAT, m_ResultatRecherche);
	DDX_Control(pDX, IDC_LISTE_ATTRIBUTS, m_ListeAttributs);
	DDX_Text(pDX, IDC_TEXTE, m_Texte);
	DDX_Radio(pDX, IDC_TOUS_ATTRIBUTS, m_TousAttributs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecherche, CDialog)
	//{{AFX_MSG_MAP(CRecherche)
	ON_BN_CLICKED(IDC_TOUS_ATTRIBUTS, OnTousAttributs)
	ON_BN_CLICKED(IDC_UN_ATTRIBUT, OnUnAttribut)
	ON_EN_CHANGE(IDC_TEXTE, OnChangeTexte)
	ON_BN_CLICKED(IDC_CHERCHER, OnChercher)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_RESULTAT, OnItemclickResultat)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_RESULTAT, OnColumnclickResultat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecherche message handlers

BOOL CRecherche::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Remplissage de la liste des attributs
	CStringArray&	Attributs	=	CElement::GetTousAttributs() ;
	m_ListeAttributs.ResetContent() ;

	m_ResultatRecherche.SetExtendedStyle( LVS_EX_FLATSB | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_TRACKSELECT | LVS_EX_UNDERLINECOLD ) ;
	
	const int NbAttributs	=	Attributs.GetSize() ;
	m_ResultatRecherche.InsertColumn( 0, "Media", LVCFMT_LEFT, 100 ) ;

	for ( int i = 0; i < NbAttributs; i++)
		{
		m_ListeAttributs.AddString( Attributs[i] ) ;
		m_ResultatRecherche.InsertColumn( i+1, Attributs[i], LVCFMT_LEFT, 100, i+1 ) ;
		}


	m_ListeAttributs.SetCurSel( 0 ) ;
	m_TousAttributs	=	0 ;
	m_ListeAttributs.EnableWindow( FALSE ) ;
	m_Chercher.EnableWindow( FALSE ) ;

	
	UpdateData(FALSE) ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecherche::OnTousAttributs() 
{
	m_ListeAttributs.EnableWindow( FALSE ) ;	
}

void CRecherche::OnUnAttribut() 
{
	m_ListeAttributs.EnableWindow( TRUE ) ;	
}

void CRecherche::OnChangeTexte() 
{
	CString Texte ;

	m_TexteCtrl.GetWindowText( Texte ) ;

	m_Chercher.EnableWindow( ! Texte.IsEmpty()) ;	
}

void CRecherche::OnChercher() 
{
	CWaitCursor w ;
	UpdateData( TRUE ) ;

	CString	Attribut ;

	if ( m_TousAttributs ==  1)
		{
		int Sel	=	m_ListeAttributs.GetCurSel() ;
		if ( Sel != CB_ERR )
			m_ListeAttributs.GetLBText( Sel, Attribut ) ;
		}

	m_ResultatRecherche.DeleteAllItems() ;

	for (int i = 0; i < _TableauMedias.GetSize(); i++)
		{
		// Fait la recherche
		CElement::TABLEAU_ELEMENTS TableauElements ;
		_TableauMedias[i]->Recherche( m_Texte, Attribut, TableauElements ) ;

		CString MediaName	=	_TableauMedias[i]->MediaName() ;

		// Ajoute les elements trouves dans la liste
		for ( int j = 0; j < TableauElements.GetSize(); j++)
			{
			const int No		=	m_ResultatRecherche.GetItemCount() ;
			const int indice	=	m_ResultatRecherche.InsertItem( LVIF_TEXT | LVIF_PARAM, No, MediaName, 0, 0, 0, No ) ;

			TableauElements[j]->AjouteDansListCtrl( m_ResultatRecherche, indice ) ;
			}

		_TableauMedias[i]->Vide() ;
		}
}

void CRecherche::OnOK() 
{
	OnChercher() ;
}

///////////////////////////////////////////////////////////////////////////////
// Tri des items
///////////////////////////////////////////////////////////////////////////////
void CRecherche::OnItemclickResultat(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	*pResult = 0;

	// Numero de la colonne
	int NoColonne	=	phdn->iItem ;

	// SubItem associe a la colonne
	LVCOLUMN		Colonne ;
	Colonne.mask	=	LVCF_SUBITEM ;
	m_ResultatRecherche.GetColumn( NoColonne, &Colonne ) ;

	m_iSubItemSort	=	Colonne.iSubItem ;
	m_ResultatRecherche.SortItems( fctCompare, (unsigned long)this ) ;
}

int CALLBACK CRecherche::fctCompare(LPARAM Param1, LPARAM Param2, LPARAM ParamSort)
{
	CRecherche*	pRecherche	=	(CRecherche*)ParamSort ;

   CString    strItem1 = pRecherche->m_ResultatRecherche.GetItemText(Param1, pRecherche->m_iSubItemSort);
   CString    strItem2 = pRecherche->m_ResultatRecherche.GetItemText(Param2, pRecherche->m_iSubItemSort);

   return strcmp(strItem2, strItem1);

}

void CRecherche::OnColumnclickResultat(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	if ( pNMListView->iItem != -1 )
		return ;

	m_iSubItemSort	=	pNMListView->iSubItem ;
	m_ResultatRecherche.SortItems( fctCompare, (unsigned long)this ) ;

	m_ResultatRecherche.GetHeaderCtrl()->SetHotDivider( m_iSubItemSort ) ;
}
