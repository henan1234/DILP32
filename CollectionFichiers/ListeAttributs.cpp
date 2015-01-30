// ListeAttributs.cpp : implementation file
//

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "ListeAttributs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListeAttributs dialog


CListeAttributs::CListeAttributs(CWnd* pParent, CMapStringToString & ListeAttributs )
	: CDialog(CListeAttributs::IDD, pParent),
	_ListeAttributs( ListeAttributs )
{
	//{{AFX_DATA_INIT(CListeAttributs)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CListeAttributs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListeAttributs)
	DDX_Control(pDX, IDC_LISTE_ATTRIBUTS, m_Liste);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListeAttributs, CDialog)
	//{{AFX_MSG_MAP(CListeAttributs)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTE_ATTRIBUTS, OnItemchangedListeAttributs)
	ON_NOTIFY(HDN_ENDDRAG, IDC_LISTE_ATTRIBUTS, OnEnddragListeAttributs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListeAttributs message handlers

BOOL CListeAttributs::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Liste.InsertColumn( 0, "Nom", LVCFMT_LEFT, 200, 0 ) ;
	m_Liste.InsertColumn( 0, "Valeur", LVCFMT_LEFT, 200, 1 ) ;

	POSITION Pos	=	_ListeAttributs.GetStartPosition() ;
	while ( Pos )
		{
		CString Key ;
		CString Value ;
		_ListeAttributs.GetNextAssoc( Pos, Key, Value ) ;

		const int Indice = m_Liste.InsertItem( m_Liste.GetItemCount(), Key ) ;
		m_Liste.SetItem( Indice, 1, LVIF_TEXT, Value, 0,0,0,0 ) ;
		}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListeAttributs::OnItemchangedListeAttributs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CListeAttributs::OnEnddragListeAttributs(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY * phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
