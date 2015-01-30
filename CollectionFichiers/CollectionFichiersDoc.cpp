// CollectionFichiersDoc.cpp : implementation of the CCollectionFichiersDoc class
//

#include "stdafx.h"
#include "CollectionFichiers.h"
#include "fileServices.h"

#include "CollectionFichiersDoc.h"
#include "scanningdlg.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersDoc

IMPLEMENT_DYNCREATE(CCollectionFichiersDoc, CDocument)

BEGIN_MESSAGE_MAP(CCollectionFichiersDoc, CDocument)
	//{{AFX_MSG_MAP(CCollectionFichiersDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersDoc construction/destruction

CCollectionFichiersDoc::CCollectionFichiersDoc()
{
	// TODO: add one-time construction code here

}

CCollectionFichiersDoc::~CCollectionFichiersDoc()
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		delete _Elements[i] ;
}

BOOL CCollectionFichiersDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersDoc serialization

void CCollectionFichiersDoc::Serialize(CArchive& ar)
{
	if ( ar.IsLoading())
		{
		ar >> _AttributFiltre ;
		ar >> _TexteFiltre ;
		}
	else
		{
		ar << _AttributFiltre ;
		ar << _TexteFiltre ;
		}

	_TableauLargeurs.Serialize( ar ) ;
	_TableauOrdre.Serialize( ar ) ;
	_Elements.Serialize( ar ) ;

	if ( ar.IsLoading())
		MajToolbars() ;
}

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersDoc diagnostics

#ifdef _DEBUG
void CCollectionFichiersDoc::AssertValid() const
{
	CDocument::AssertValid();

}

void CCollectionFichiersDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCollectionFichiersDoc commands

void CCollectionFichiersDoc::ScanneDirectory(const CString &Path, CMapStringToString &ListeAttributsCommuns, CView *pParent)
{
	CObArray	Temporaire ;
	CScanningDlg		dlg( pParent ) ;
	dlg.Create( IDD_SCANNING ) ;
	dlg.ShowWindow( SW_SHOW ) ;

	// Scrute le premier niveau pour avoir une idee du nombre d'elements
	CString	Mask	=	CFileServices::Concat( Path, "*.*" ) ;

	// Compter les objets de 1er niveau
	WIN32_FIND_DATA	data ;
	HANDLE	hFind	=	FindFirstFile( Mask, &data ) ;
	BOOL	Continue	=	TRUE ;
	int		Nb		=	0 ;
	while( Continue )
		{
		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			Nb ++ ;
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}
	FindClose( hFind ) ;

	// Parcourir
	dlg.m_Progress.SetRange( 0, Nb-1 ) ;
	Nb	=	0 ;
	hFind	=	FindFirstFile( Mask, &data ) ;
	Continue	=	TRUE ;

	// Scrutation de premier niveau avec avancement de la jauge
	while( Continue )
		{
		if ( dlg.Abort())
			{
			Nettoie( Temporaire ) ;
			FindClose( hFind ) ;
			dlg.DestroyWindow() ;
			return ;
			}

		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			CString CompletePath	=	CFileServices::Concat( Path, data.cFileName ) ;
			dlg.m_Fichier.SetWindowText( data.cFileName ) ;

			CElement * pElement = new CElement() ;			
			if ( ! pElement->Scanne( CompletePath, data, dlg, ListeAttributsCommuns ))
				{
				Nettoie( Temporaire ) ;
				FindClose( hFind ) ;
				dlg.DestroyWindow() ;
				return ;
				}

			if ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
				if ( ! ScanneDirectory( CompletePath, ListeAttributsCommuns, dlg, Temporaire ))
					{
					Nettoie( Temporaire ) ;
					FindClose( hFind ) ;
					return ;
					}
				}

			if ( ! AjouteElement( Temporaire, pElement ) )
				{
				Nettoie( Temporaire ) ;
				FindClose( hFind ) ;
				return ;
				}

			Nb ++ ;
			dlg.m_Progress.SetPos( Nb ) ;
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}


	FindClose( hFind ) ;


	dlg.DestroyWindow() ;

	_Elements.Append( Temporaire ) ;
	SetModifiedFlag( TRUE ) ;
	MajToolbars() ;

	UpdateAllViews(0) ;		
}

void CCollectionFichiersDoc::GetListeValeurs(const CString &Attribut, const CString & AttributFiltre, const CString & TexteFiltre, CStringArray &ListeValeurs)
{
	for ( int i = 0; i < _Elements.GetSize(); i++)
		{
		CElement * pElement	=	(CElement*)_Elements[i] ;
		if ( pElement->ConvientPourFiltre( AttributFiltre, TexteFiltre ))
			{
			CString	Valeur	=	pElement->GetAttribut( Attribut ) ;

			// Cherche la valeur de l'attribut dans le tableau des valeurs differentes
			int Indice = -1 ;
			for ( int j = 0; j < ListeValeurs.GetSize(); j++)
				if  (Valeur == ListeValeurs[j] )
					{
					Indice = j ;
					break ;
					}

			if ( Indice == -1 )
				ListeValeurs.Add( Valeur ) ;
			}
		}
}

void CCollectionFichiersDoc::Nettoie(CObArray &Tab)
{
	for ( int i = 0; i < Tab.GetSize(); i++)
		delete Tab[i] ;
}

BOOL CCollectionFichiersDoc::ScanneDirectory(const CString &Path, CMapStringToString &ListeAttributsCommuns, CScanningDlg &dlg, CObArray &Temporaire)
{
	// Scrute le premier niveau pour avoir une idee du nombre d'elements
	CString	Mask	=	CFileServices::Concat( Path, "*.*" ) ;

	// Compter les objets de 1er niveau
	WIN32_FIND_DATA	data ;
	HANDLE	hFind	=	FindFirstFile( Mask, &data ) ;
	BOOL	Continue	=	TRUE ;
	
	while( Continue )
		{
		if ( dlg.Abort())
			{
			FindClose( hFind ) ;
			dlg.DestroyWindow() ;
			return FALSE ;
			}

		if ( strcmp( data.cFileName, "." ) && strcmp( data.cFileName, ".." ))
			{
			CString CompletePath	=	CFileServices::Concat( Path, data.cFileName ) ;
			dlg.m_Fichier.SetWindowText( data.cFileName ) ;

			CElement * pElement = new CElement() ;			
			if ( ! pElement->Scanne( CompletePath, data, dlg, ListeAttributsCommuns ))
				{
				FindClose( hFind ) ;
				dlg.DestroyWindow() ;
				return FALSE ;
				}

			if ( data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
				{
				if ( ! ScanneDirectory( CompletePath, ListeAttributsCommuns, dlg, Temporaire ))
					{
					FindClose( hFind ) ;
					return FALSE ;
					}
				}

			if ( ! AjouteElement( Temporaire, pElement ) )
				{
				FindClose( hFind ) ;
				return FALSE ;
				}
			}

		Continue	=	FindNextFile( hFind, &data ) ;
		}


	FindClose( hFind ) ;
	return TRUE ;
}

BOOL CCollectionFichiersDoc::AjouteElement(CObArray &Tab, CElement *pElement)
{
	try
		{
		Tab.Add( pElement ) ;
		return TRUE ;
		}
	catch( CMemoryException e)
		{
		return FALSE ;
		}
}

void CCollectionFichiersDoc::MajToolbars()
{
	CMainFrame	*	pFrame	=	(CMainFrame*)AfxGetMainWnd() ;
	
	//pFrame->m_wndRegroupeToolBar.Maj() ;
	pFrame->m_wndFiltreToolBar.Maj() ;
}


void CCollectionFichiersDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( IsModified()) ;
}


///////////////////////////////////////////////////////////////////////////////
// Memorise l'ordre des colonnes
// ENTREES:	Tableau d'Ordre des colonnes
//			Nombre d'elements dans le tableau
///////////////////////////////////////////////////////////////////////////////
void CCollectionFichiersDoc::MemoriseOrdreColonnes(int *pTableauOrdre, int NbItems)
{
	_TableauOrdre.SetSize( NbItems ) ;
	for (int i = 0; i < NbItems; i++)
		_TableauOrdre[i]	=	pTableauOrdre[i] ;

	UpdateAllViews(0) ;
}


///////////////////////////////////////////////////////////////////////////////
// Memorise les largeurs de colonnes
// ENTREES: Tableau de largeurs
//			Nombre d'elements
///////////////////////////////////////////////////////////////////////////////
void	CCollectionFichiersDoc::MemoriseLargeursColonnes( int * pTableauLargeurs, int NbItems )
{
	_TableauLargeurs.SetSize( NbItems ) ;
	for (int i = 0; i< NbItems; i++)
		_TableauLargeurs[i]	=	pTableauLargeurs[i] ;

	UpdateAllViews(0) ;
}

