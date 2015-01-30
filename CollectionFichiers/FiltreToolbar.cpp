// FiltreToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "collectionfichiers.h"
#include "collectionfichiersdoc.h"
#include "FiltreToolbar.h"
#include "Element.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char TOUS_ATTRIBUT[]		=	"<N'importe quel attribut>" ;

/////////////////////////////////////////////////////////////////////////////
// CFiltreToolbar dialog


CFiltreToolbar::CFiltreToolbar(CWnd* pParent /*=NULL*/)
//	: CDialogBar(CFiltreToolbar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFiltreToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFiltreToolbar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFiltreToolbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFiltreToolbar, CDialogBar)
	//{{AFX_MSG_MAP(CFiltreToolbar)
	ON_BN_CLICKED(IDC_FILTRER, OnFiltrer)
	ON_EN_CHANGE(IDC_TEXTE, OnChangeTexte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiltreToolbar message handlers

void CFiltreToolbar::Maj()
{
	CComboBox	ListeAttributs ;
	ListeAttributs.Attach( ::GetDlgItem( *this, IDC_LISTE_ATTRIBUTS)) ;
	CString AttributSelectionne	;
	
	ListeAttributs.SetRedraw( FALSE ) ;
	ListeAttributs.ResetContent() ;

	CStringArray& Attributs	=	CElement::GetTousAttributs() ;

	for ( int i = 0; i < Attributs.GetSize(); i++)
		ListeAttributs.AddString( Attributs[i] ) ;

	ListeAttributs.InsertString( 0, TOUS_ATTRIBUT ) ;

	CMainFrame	*	pFrame			=	(CMainFrame*)AfxGetMainWnd() ;
	CCollectionFichiersDoc * pDoc	=	(CCollectionFichiersDoc*)pFrame->GetActiveDocument() ;
	CString Texte ;
	CString Attribut ;
	pDoc->GetFiltre( Attribut, Texte ) ;

	if ( Attribut.IsEmpty())
		Attribut	=	TOUS_ATTRIBUT ;

	ListeAttributs.SelectString( -1, Attribut ) ;

	SetDlgItemText( IDC_TEXTE, Texte ) ;

	ListeAttributs.SetRedraw( TRUE ) ;
	ListeAttributs.Invalidate() ;

	ListeAttributs.Detach() ;

}

void CFiltreToolbar::OnFiltrer() 
{
	CMainFrame	*	pFrame	=	(CMainFrame*)AfxGetMainWnd() ;
	pFrame->GetActiveDocument()->UpdateAllViews(0) ;
}

void CFiltreToolbar::OnChangeTexte() 
{
	CString Texte ;
	CEdit	Edit	;
	Edit.Attach( ::GetDlgItem( *this, IDC_TEXTE )) ;
	Edit.GetWindowText( Texte ) ;
	Edit.Detach() ;

	::EnableWindow( ::GetDlgItem( *this, IDC_FILTRER ), ! Texte.IsEmpty()) ;
}

void CFiltreToolbar::GetFiltre(CString &Attribut, CString &Texte)
{
	CComboBox	ListeAttributs ;
	ListeAttributs.Attach( ::GetDlgItem( *this, IDC_LISTE_ATTRIBUTS)) ;
	CString AttributSelectionne	;
	int Sel	=	ListeAttributs.GetCurSel() ;

	if ( Sel > 0 )	// Rappel: La premiere ligne signifie "N'importe quel attribut"
		ListeAttributs.GetLBText( Sel, Attribut ) ;
	else
		Attribut.Empty() ;
	ListeAttributs.Detach() ;

	CEdit	Edit	;
	Edit.Attach( ::GetDlgItem( *this, IDC_TEXTE )) ;
	Edit.GetWindowText( Texte ) ;
	Edit.Detach() ;
}

BOOL CFiltreToolbar::IsFiltreCorrect()
{
	/*CString Texte ;
	CEdit	Edit	;
	Edit.Attach( ::GetDlgItem( *this, IDC_TEXTE )) ;
	BOOL	Correct	=	Edit.GetWindowTextLength() > 0 ;
	Edit.Detach() ;

	return Correct ;*/
	return TRUE ;
}
