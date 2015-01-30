// FichiersDoublesDoc.cpp : implementation of the CFichiersDoublesDoc class
//

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "choosfol.h"
#include "FichiersDoublesDoc.h"
#include "progressdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesDoc

IMPLEMENT_DYNCREATE(CFichiersDoublesDoc, CDocument)

BEGIN_MESSAGE_MAP(CFichiersDoublesDoc, CDocument)
	//{{AFX_MSG_MAP(CFichiersDoublesDoc)
	ON_UPDATE_COMMAND_UI(ID_EDITION_SUPPRIMETOUSLESDUPPLIQUS, OnUpdateEditionSupprimetouslesduppliqus)
	ON_COMMAND(ID_EDITION_SUPPRIMETOUSLESDUPPLIQUS, OnEditionSupprimetouslesduppliqus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesDoc construction/destruction

CFichiersDoublesDoc::CFichiersDoublesDoc()
{
	pElementSelectionne	=	NULL ;
}

CFichiersDoublesDoc::~CFichiersDoublesDoc()
{
	VideRepertoire() ;
}

BOOL CFichiersDoublesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	VideRepertoire() ;
	pElementSelectionne	=	NULL ;

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesDoc serialization

void CFichiersDoublesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesDoc diagnostics

#ifdef _DEBUG
void CFichiersDoublesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFichiersDoublesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFichiersDoublesDoc commands

BOOL CFichiersDoublesDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	_Repertoire.Vide() ;
	UpdateAllViews( 0, HINT_VIDE, 0 ) ;
	pElementSelectionne	=	NULL ;

	// Scanne le repertoire
	_Repertoire.Scanne( lpszPathName ) ;

	ScanneDuppliques() ;

	UpdateAllViews(0) ;
	return TRUE;
}



void CFichiersDoublesDoc::RemplitArbre(CTreeCtrl &Tree, BOOL AfficherNonDuppliques )
{
	_Repertoire.RemplitArbre( Tree, TVI_ROOT, _ImageListHandler, AfficherNonDuppliques ) ;
	Tree.Expand( TVI_ROOT, TVE_EXPAND ) ;
}

void CFichiersDoublesDoc::ScanneDuppliques()
{
	CProgressDlg dlgProgress ;

	dlgProgress.Create( IDD_PROGRESS, AfxGetMainWnd() ) ;
	dlgProgress.ShowWindow( SW_SHOW ) ;
	//AfxGetMainWnd()->EnableWindow(FALSE ) ;
	// Obtient la liste de tous les fichiers
	CArray<CFichier*,CFichier*> _Tous ;

	DWORD	Debut	=	GetCurrentTime() ;

	_Repertoire.ObtientTousFichier( _Tous ) ;

	dlgProgress.m_Progress.SetRange( 0, _Tous.GetSize()) ;
	dlgProgress.m_Progress.SetPos( 0 ) ;
	int Identiques	=	0 ;

	for ( int i =0; i < _Tous.GetSize(); i++)
		{
		CFichier* pFichier1	=	_Tous[i] ;
		dlgProgress.m_Progress.SetPos( i ) ;
		dlgProgress.m_FichierEnCours.SetWindowText( pFichier1->Path()) ;
		CString NoFichier ;
		NoFichier.Format( "Fichier %d/%d", i, _Tous.GetSize() ) ;
		dlgProgress.m_UnSur.SetWindowText( NoFichier ) ;
	
		for ( int j = i+1; j < _Tous.GetSize(); j++)
			{
			CFichier* pFichier2 = _Tous[j] ;
			if ( pFichier1->Compare( pFichier2 ))
				{
				Identiques ++ ;
				CString Message ;
				Message.Format( "%d fichiers identiques trouvés", Identiques ) ;
				dlgProgress.m_DuppliquesTrouves.SetWindowText( Message ) ;
				}
			}

		DWORD Maintenant	=	GetCurrentTime() ;
		DWORD Delai			=	((Maintenant-Debut)/1000) ;
		if ( Delai > 0 )
			{
			int	  TempsMoyen	=	(i+1)/ Delai;
			CString	TpsMoyen ;
			TpsMoyen.Format( "%d fichiers par secondes", TempsMoyen ) ;
			dlgProgress.m_TempsMoyen.SetWindowText( TpsMoyen ) ;
			}
		

		if ( dlgProgress.Aborted())
			{
			_Repertoire.Vide() ;
			break ;
			}


		pFichier1->FiniScan() ;
		}

	_Repertoire.FiniScan() ;

	dlgProgress.DestroyWindow() ;
	//AfxGetMainWnd()->EnableWindow(TRUE ) ;	
}

void CFichiersDoublesDoc::VideRepertoire()
{
	_Repertoire.Vide() ;
	pElementSelectionne	=	NULL ;
}

///////////////////////////////////////////////////////////////////////////////
// Supprime les versions duppliques d'un fichier
///////////////////////////////////////////////////////////////////////////////
void CFichiersDoublesDoc::SupprimeDuppliques(CFichier *pElement)
{
	// Envoi le fichier dans la poubelle
	CArray<CFichier*, CFichier*> & Duppliques	=	pElement->GetDuppliques() ;

	if ( ! DeleteListOfFiles( Duppliques ))
		return ;

	// Supprime les duppliques dans l'arbre
	for ( int i = 0; i < Duppliques.GetSize(); i++)
		{
		if ( _Repertoire.Supprime( Duppliques[i] ))
			delete Duppliques[i] ;
		}


	// Vider la liste des duppliques du fichier, un raccourci pas tres "objet" ;-)
	Duppliques.RemoveAll() ;
	
	UpdateAllViews(0) ;
}

///////////////////////////////////////////////////////////////////////////////
// DeleteFiles
//	Supprimer des fichiers en les transerfant dans la poubelle
//	La liste de fichiers est donnee dans une Chaine, chaque nom etant separe
//	par un |
///////////////////////////////////////////////////////////////////////////////
BOOL CFichiersDoublesDoc::DeleteFiles(CString &Files)
{
	const int	NbChars	=	Files.GetLength() ;

	char	*		pFrom	=	new char[NbChars + 1 ] ;
	strcpy( pFrom, Files ) ;
	for ( int i = 0; i < NbChars; i++)
		if ( pFrom[i] == '|' )
			pFrom[i] = 0 ;

	SHFILEOPSTRUCT	St ;
	St.hwnd			=	AfxGetMainWnd()->GetSafeHwnd();
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

///////////////////////////////////////////////////////////////////////////////
// Supprime la liste des fichiers donnee en parametres
///////////////////////////////////////////////////////////////////////////////
BOOL CFichiersDoublesDoc::DeleteListOfFiles(CArray<CFichier *, CFichier *>&Fichiers)
{
	// Count length of all file names
	int	Len	=	0 ;
	for ( int i = 0; i < Fichiers.GetSize(); i++)
		Len	+=	Fichiers[i]->Path().GetLength() + 1 ;

	// Remplissage de la structure SHFILEOPSTRUCT
	char	*		pFrom	=	new char[Len + 1 ] ;
	memset( pFrom, 0, Len+1 ) ;

	char	*		pFile	=	pFrom ;

	for ( i = 0; i < Fichiers.GetSize(); i++)
		{
		CString	File	=	Fichiers[i]->Path() ;

		ASSERT( AfxIsValidAddress( pFile, File.GetLength() + 1, TRUE )) ;

		strcpy( pFile, File ) ;
		pFile	+=	File.GetLength() + 1 ;
		}

	pFile[0] = 0 ;

	SHFILEOPSTRUCT	St ;
	St.hwnd			=	AfxGetMainWnd()->GetSafeHwnd();
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

void CFichiersDoublesDoc::OnUpdateEditionSupprimetouslesduppliqus(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( _Repertoire.ADesDuppliques()) ;
}

void CFichiersDoublesDoc::OnEditionSupprimetouslesduppliqus() 
{
	if ( MessageBox( *AfxGetMainWnd(), "Cette opération va supprimer tous les fichiers duppliqués, voulez-vous continuer ?\n(Une seule occurence de chaque dupplication sera gardée",
										"Suppression de tous les duppliqués", MB_ICONQUESTION | MB_OKCANCEL ) == IDCANCEL )
		return ;

	//Récupere la liste de tous les fichiers
	CArray<CFichier*,CFichier*> Tous ;
	_Repertoire.ObtientTousFichier( Tous ) ;

	CArray<CFichier*, CFichier*> FichiersASupprimer ;

	// Construit la liste des fichiers a supprimer
	for ( int i = 0; i < Tous.GetSize(); i++)
		{
		CFichier* pFichier	=	Tous[i] ;

		if ( pFichier->ADesDuppliques())
			{
			// Ajoute les fichiers duppliques dans la liste a supprimer
			CArray<CFichier*, CFichier*> & Duppliques = pFichier->GetDuppliques() ;

			for ( int j = 0; j < Duppliques.GetSize(); j++)
				{
				CFichier * pFichier =	Duppliques[j] ;
				FichiersASupprimer.Add( pFichier ) ;

				// Supprime le fichier de la liste globale pour ne pas le mettre deux fois
				for ( int k = i+1; k < Tous.GetSize(); k ++ )
					{
					if ( pFichier == Tous[k] )
						{
						Tous.RemoveAt( k ) ;
						break ;
						}
					}
				}

			}
		}

	if ( DeleteListOfFiles( FichiersASupprimer ))
		{
		for ( int i = 0; i < FichiersASupprimer.GetSize(); i++)
			{
			// Supprime ce fichier de l'arbre
			_Repertoire.Supprime( FichiersASupprimer[i] ) ;
			}
		UpdateAllViews(0) ;
		}
}
