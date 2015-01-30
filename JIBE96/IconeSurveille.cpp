////////////////////////////////////////////////////////////////
// CIconeSurveille
// Cette icone surveille un repertoire et averti des qu'il y a
// un changement
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <afxmt.h>
#include <winnls.h>
#include <winbase.h>
#include "resource.h"
#include "iconesurveille.h"
#include "surveilledlg.h"
#include "choosfol.h"
#include "DlgOptionsSurveillance.h"

#define new	DEBUG_NEW

CCriticalSection	Section ;
IMPLEMENT_SERIAL( CIconeSurveille, CIconePeriodique,0 ) ;

class	CEtatFichier : public	CObject
	{
	public :
		DECLARE_SERIAL( CEtatFichier ) ;
		CEtatFichier( const WIN32_FIND_DATA & ) ;
		virtual	void	Serialize( CArchive & ) ;
		CString		Compare( const WIN32_FIND_DATA &, DWORD ) ;
		const char *	Nom( void ) const { return _Status.cFileName ; } ;

	private :
		CEtatFichier(){} ;
		WIN32_FIND_DATA	_Status ;
	} ;

IMPLEMENT_SERIAL( CEtatFichier, CObject, 0 ) ;

CEtatFichier::CEtatFichier( const WIN32_FIND_DATA & S )
	{
	_Status	=	S ;
	}

void	CEtatFichier::Serialize( CArchive & ar )
	{
	CObject::Serialize( ar ) ;
	if ( ar.IsStoring())
		ar.Write( &_Status, sizeof( _Status )) ;
	else
		ar.Read( &_Status, sizeof( _Status )) ;
	}

////////////////////////////////////////////////////////////////
// Comparaison de deux status de fichiers
////////////////////////////////////////////////////////////////
CString	CEtatFichier::Compare( const WIN32_FIND_DATA & S, DWORD Options )
{
	ASSERT( lstrcmp( S.cFileName, _Status.cFileName) == 0 ) ;

	CString	Return ;

	if ( Options & FILE_NOTIFY_CHANGE_ATTRIBUTES ) 
		{
		// Comparer attributs
		if ( _Status.dwFileAttributes!= S.dwFileAttributes )
			{
			Return.Format( IDS_CHANGE_ATTR, _Status.cFileName ) ;
			_Status	=	S ;
			return Return ;
			}
		}

	if ( Options & FILE_NOTIFY_CHANGE_SIZE ) 
	// Comparer taille
	if ( _Status.nFileSizeLow != S.nFileSizeLow ||
		 _Status.nFileSizeHigh != S.nFileSizeHigh )
		{
		Return.Format( IDS_CHANGE_SIZE, _Status.cFileName ) ;
		_Status	=	S ;
		return Return ;
		}

	// Comparer	date
	if ( Options & FILE_NOTIFY_CHANGE_LAST_WRITE ) 
	if ( CompareFileTime( &_Status.ftLastWriteTime, &S.ftLastWriteTime ))
		{
		Return.Format( IDS_CHANGE_TIME, _Status.cFileName ) ;
		_Status	=	S ;
		return Return ;
		}

	// Comparer	date
	if ( Options & FILE_NOTIFY_CHANGE_LAST_WRITE ) 
	if ( CompareFileTime( &_Status.ftCreationTime, &S.ftCreationTime ))
		{
		Return.Format( IDS_CHANGE_CTIME, _Status.cFileName ) ;
		_Status	=	S ;
		return Return ;
		}

	// Comparer	date
	if ( Options & FILE_NOTIFY_CHANGE_LAST_WRITE ) 
	if ( CompareFileTime( &_Status.ftLastAccessTime, &S.ftLastAccessTime ))
		{
		Return.Format( IDS_CHANGE_ATIME, _Status.cFileName ) ;
		_Status	=	S ;
		return Return ;
		}

	return "" ;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
CIconeSurveille::CIconeSurveille()
	{
	_AlarmeEnCours	=	TRUE ;
	_Clignote		=	FALSE ;
	_hThread		=	0 ;
	_Recursif		=	FALSE ;
	_Options		=	FILE_NOTIFY_CHANGE_FILE_NAME |
						FILE_NOTIFY_CHANGE_DIR_NAME	|
						FILE_NOTIFY_CHANGE_ATTRIBUTES |
						FILE_NOTIFY_CHANGE_SIZE	|
						FILE_NOTIFY_CHANGE_LAST_WRITE ;
	_hFNotif		=	INVALID_HANDLE_VALUE ;
	}

CIconeSurveille::~CIconeSurveille()
	{
	if ( _hThread )
		{
		SuspendThread( _hThread ) ;
		CloseHandle( _hThread ) ;
		}

	_Evenements.RemoveAll() ;

	POSITION	Pos	=	_EtatsFichiers.GetStartPosition() ;
	CObject	*	pObject ;
	CString		Str ;

	while ( Pos )
		{
		_EtatsFichiers.GetNextAssoc( Pos, Str, pObject ) ;
		delete pObject ;
		}

	if ( _hFNotif != INVALID_HANDLE_VALUE )
		FindCloseChangeNotification(_hFNotif) ;
	}

void	CIconeSurveille::Update( void )
	{
//	SurveilleRepertoire() ;
	if ( _AlarmeEnCours || _Clignote )
		{
		_Clignote = ! _Clignote ;
		CIcone::Update() ;
		}

	}
void	CIconeSurveille::Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee )
	{
	HICON	hIcone	=	AfxGetApp()->LoadIcon( _Clignote ? IDI_SURVEILLE_REP1 : IDI_SURVEILLE_REP ) ;
	HRGN	hRegion =	Region( Pt ) ;
	CRect	R ;
	GetRgnBox( hRegion, R ) ;
	DeleteObject( hRegion ) ;

	Dc.DrawIcon( R.left + ( R.Width() - GetSystemMetrics( SM_CXICON ))/2,
				 R.top,
				 hIcone ) ;
	DestroyIcon( hIcone ) ;

	Dc.SetBkMode( OPAQUE ) ;
	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetBkColor( GetSysColor( Selectionnee ? COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION )) ;
	Dc.SetTextColor( GetSysColor( Selectionnee ? COLOR_CAPTIONTEXT : COLOR_INACTIVECAPTIONTEXT )) ;

	Dc.DrawText( _Repertoire, -1, R, DT_BOTTOM | DT_SINGLELINE | DT_CENTER | DT_WORDBREAK ) ;
	}

HRGN	CIconeSurveille::Region( CPoint Decalage ) const
	{
	// Largeur de la fenetre ?
	CSize	Taille( GetMainSize()) ;


	switch( GetSide())
		{
		case ABE_LEFT :
		case ABE_RIGHT :
			Taille.cy	=	GetSystemMetrics( SM_CYICON ) + GetSystemMetrics( SM_CYCAPTION ) ;
			break ;

		case ABE_TOP :
		case ABE_BOTTOM :
			Taille.cx	=	GetSystemMetrics( SM_CXICON ) * 2 ;
			break ;

		default :
			ASSERT( FALSE ) ;
		}

	return CreateRectRgn( Decalage.x, Decalage.y,
						  Decalage.x+Taille.cx,
						  Decalage.y+Taille.cy ) ;
	}

UINT	CIconeSurveille::GetMenuID( void ) const
	{
	return IDR_MENU_REP ;
	}

CWnd*	CIconeSurveille::OuvreFenetre( CRect & RectIcone, CWnd* pParent )
	{
	ASSERT_VALID( this ) ;
	CSurveilleDlg	*	pWnd =	new	CSurveilleDlg( this ) ;
	ASSERT( pWnd ) ;

	const int LargeurVoulue	=	GetSystemMetrics( SM_CXICONSPACING ) * 8 ;
	const int HauteurVoulue	=	GetSystemMetrics( SM_CYICONSPACING ) * 4 ;
	const DWORD	StyleEx	=	WS_EX_TOOLWINDOW ;
	const DWORD	Style	=	WS_POPUP | WS_VISIBLE | WS_BORDER | WS_THICKFRAME ;

	pWnd->Create( IDD_SURVEILLE, pParent ) ;

	pParent->ClientToScreen( RectIcone ) ;
	CRect	R( pWnd->AjusteRectangle( RectIcone, LargeurVoulue, HauteurVoulue, Style, StyleEx )) ;

	pWnd->SetWindowPos( pWnd, R.left, R.top, R.Width(), R.Height(),
						SWP_NOZORDER ) ;
	
	pWnd->ShowWindow( SW_SHOW ) ;
	return pWnd ;
	}

CString CIconeSurveille::GetTip( void )
	{
	return _Repertoire ;
	}

void CIconeSurveille::Serialize( CArchive & ar )
	{
	CIconePeriodique::Serialize( ar ) ;

	_EtatsFichiers.Serialize( ar ) ;
	_Evenements.Serialize( ar ) ;

	if ( ar.IsStoring())
		{
		ar << _Repertoire ;
		ar << _AlarmeEnCours ;
		ar << _Recursif ;
		ar << _Options ;
		}
	else
		{
		ar >> _Repertoire ;
		ar >> _AlarmeEnCours ;
		ar >> _Recursif ;
		ar >> _Options ;
		}
	}

//////////////////////////////////////////////////////////////////////////////
// Enchaine la surveillance des repertoires
//////////////////////////////////////////////////////////////////////////////
void CIconeSurveille::SurveilleRepertoire( const char * Repertoire )
{
	// Nouveaux fichiers ou fichiers ayant change
	CString	Chemin(Repertoire) ;
	Chemin += "\\*.*" ;

	WIN32_FIND_DATA	FData ;
	HANDLE	hFF	=	FindFirstFile( Chemin, &FData ) ;
	BOOL	Continuer	=	(hFF != INVALID_HANDLE_VALUE ) ;

	while ( Continuer )
		{
		if ( lstrcmp( ".", FData.cFileName ) && lstrcmp( "..", FData.cFileName ))
			{
			CString NomFichier(Repertoire) ;
			NomFichier += "\\" ;
			NomFichier +=	FData.cFileName ;
			lstrcpy( FData.cFileName, NomFichier ) ;

			if ( CompareFichier( NomFichier, FData ))
				_AlarmeEnCours	=	TRUE ;

			if ( (FData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (_Recursif))
				 SurveilleRepertoire( NomFichier ) ;
			}

		Continuer	=	FindNextFile( hFF, &FData ) ;
		}

	FindClose( hFF ) ;

	// Fichiers ayant disparus
	POSITION	Pos	=	_EtatsFichiers.GetStartPosition() ;
	CObject	*	pObject ;
	CString		Str ;

	while ( Pos )
		{
		_EtatsFichiers.GetNextAssoc( Pos, Str, pObject ) ;
		CEtatFichier*	pFichier	=	STATIC_DOWNCAST( CEtatFichier, pObject ) ;
		CFileStatus	S ;

		if ( ! CFile::GetStatus( pFichier->Nom(), S ))
			{
			// Le fichier a disparu !!!!!
			CString S ;
			S.Format( IDS_FICHIER_DISPARU, pFichier->Nom()) ;
			AjouteEvenement( S ) ;

			_EtatsFichiers.RemoveKey( pFichier->Nom() ) ;
			delete pFichier ;
			}
		}
}

BOOL CIconeSurveille::ExecuteCommand( UINT NoCommande )
{
	switch( NoCommande )
		{
		case ID_SURVEILLE_REP :
			{
			CChooseFolder	Dlg( _Repertoire ) ;
			if ( Dlg.DoModal()==IDOK)
				{
				_Repertoire	=	Dlg.GetDirName() ;
				//SurveilleRepertoire() ;
				_AlarmeEnCours	=	0 ;
				_Evenements.RemoveAll() ;
				Modifiee( TRUE ) ;
				CIcone::Update() ;
				DepartSurveillance() ;
				}
			}
			break ;

		case ID_ARRETE_ALARME :
			_AlarmeEnCours	=	FALSE ;
			break ;

		case ID_VIDE_MESSAGES :
			_Evenements.RemoveAll() ;
			Modifiee( TRUE ) ;
			break ;
		case ID_REP_OPTIONS :
			{
			CDlgOptionsSurveillance	Dlg ;

			Dlg.m_SousRep	=	_Recursif ;
			Dlg.m_Attributs	=	(_Options & FILE_NOTIFY_CHANGE_ATTRIBUTES) != 0  ;
			Dlg.m_DateModif	=	(_Options & FILE_NOTIFY_CHANGE_LAST_WRITE) != 0  ;
			Dlg.m_Fichiers	=	(_Options & FILE_NOTIFY_CHANGE_FILE_NAME) != 0  ;
			Dlg.m_Repertoires=	(_Options & FILE_NOTIFY_CHANGE_DIR_NAME) != 0 ;
			Dlg.m_Taille	=	(_Options & FILE_NOTIFY_CHANGE_SIZE) != 0 ;

			if ( Dlg.DoModal() == IDOK )
				{
				_Recursif	=	Dlg.m_SousRep ;
				_Options	=	0 ;
				if ( Dlg.m_Attributs )
					_Options |=	FILE_NOTIFY_CHANGE_ATTRIBUTES ;

				if ( Dlg.m_DateModif )
					_Options |= FILE_NOTIFY_CHANGE_LAST_WRITE ;

				if ( Dlg.m_Fichiers )
					_Options |=  FILE_NOTIFY_CHANGE_FILE_NAME ;

				if ( Dlg.m_Repertoires )
					_Options |= FILE_NOTIFY_CHANGE_DIR_NAME ;

				if ( Dlg.m_Taille )
					_Options |= FILE_NOTIFY_CHANGE_SIZE ;

				DepartSurveillance();
				}
			}
			break ;
		default :
			return FALSE ;
		}

	return TRUE ;
}

//////////////////////////////////////////////////////////////////////////////
// Comparaison du nouvel etat d'un fichier
//////////////////////////////////////////////////////////////////////////////
BOOL CIconeSurveille::CompareFichier( const char * NomFichier, const WIN32_FIND_DATA & Status )
{
	CObject	*	pObject ;
	if ( _EtatsFichiers.Lookup( NomFichier, pObject ))
		{
		// Le fichier existait deja, comparer ces caracteristiques
		CEtatFichier*	pFichier	=	STATIC_DOWNCAST( CEtatFichier, pObject ) ;

		CString	Evenement( pFichier->Compare( Status, _Options ) ) ;

		if ( ! Evenement.IsEmpty())
			// Le fichier a change !!!
			AjouteEvenement( Evenement ) ;
		}
	else
		{
		// Le fichiers n'etait pas dans la liste, c'est un nouveau !!!
		NouveauFichier( NomFichier, Status ) ;
		}					   

	return FALSE ;
}

//////////////////////////////////////////////////////////////////////////////
// Ajout d'un nouvel evenement dans la liste
//////////////////////////////////////////////////////////////////////////////
void CIconeSurveille::AjouteEvenement( const CString & Evenement )
{
	// Date
	SYSTEMTIME	SystemTime ;
	GetLocalTime( &SystemTime ) ;

	char	Date[100] ;
	GetDateFormat( LOCALE_USER_DEFAULT,DATE_SHORTDATE,&SystemTime,NULL,Date,sizeof( Date )) ;

	// Heure
	char	Heure[100] ;
	GetTimeFormat( LOCALE_USER_DEFAULT,0,&SystemTime,NULL,Heure, sizeof( Heure )) ;

	CString	Message ;

	Message.Format( IDS_EVENEMENT, (LPCSTR)Date, (LPCSTR)Heure, (LPCSTR)Evenement ) ;

	TRACE( Message ) ;
	TRACE( "\n"  ) ;

	_Evenements.AddTail( Message ) ;
	_AlarmeEnCours	=	TRUE ;
}

//////////////////////////////////////////////////////////////////////////////
// Un nouveau fichier est apparu
//////////////////////////////////////////////////////////////////////////////
void CIconeSurveille::NouveauFichier( const CString & NomFichier, const WIN32_FIND_DATA & Status )
{
	CString	Evenement	;
	Evenement.Format( IDS_NOUVEAU_FICHIER, (LPCSTR)NomFichier ) ;
	AjouteEvenement( Evenement ) ;

	CEtatFichier	*	p	=	new CEtatFichier( Status ) ;
	_EtatsFichiers.SetAt( NomFichier, p ) ;
}

CStringList* CIconeSurveille::Evenements(void)
{
	return &_Evenements ;
}

//////////////////////////////////////////////////////////////////////////////
// Mise en place de la surveillance de repertoire, on attend une notification
// par le systeme dans un thread secondaire
//////////////////////////////////////////////////////////////////////////////
void CIconeSurveille::DepartSurveillance( void )
{
	Section.Lock() ;
	if ( _hThread )
		{
		SuspendThread( _hThread ) ;
		CloseHandle( _hThread ) ;
		}

	if ( _hFNotif != INVALID_HANDLE_VALUE )
		FindCloseChangeNotification( _hFNotif ) ;

	_hFNotif	=	FindFirstChangeNotification( _Repertoire, _Recursif, _Options ) ;

	if ( _hFNotif == INVALID_HANDLE_VALUE )
		{
		TRACE( "Erreur : %ld", GetLastError()) ;
		return ;
		}

	DWORD	Id ;
	_hThread	=	CreateThread( NULL, 0, ThreadSurveille, (LPVOID)this, 
								  CREATE_SUSPENDED, &Id ) ;
	SetThreadPriority( _hThread, THREAD_PRIORITY_LOWEST ) ;
	ResumeThread( _hThread ) ;

	Section.Unlock() ;
}

///////////////////////////////////////////////////////////////////////////////
// Fonction de qui attend en tache de fond une notification de changement dans
// le repertoire
// Ce thread attend une notification du systeme, balaie le repertoire puis
// ce remet en attente
///////////////////////////////////////////////////////////////////////////////
DWORD __stdcall CIconeSurveille::ThreadSurveille( LPVOID p )
{
	ASSERT( p ) ;
	CIconeSurveille	*	pIcone	=	(CIconeSurveille*)p ;

	do
		{
		WaitForSingleObject( pIcone->_hFNotif, INFINITE ) ;
		pIcone->_AlarmeEnCours	=	TRUE ;
		Section.Lock() ;
		pIcone->SurveilleRepertoire( pIcone->_Repertoire ) ;
		Section.Unlock() ;
		FindNextChangeNotification( pIcone->_hFNotif ) ;
		}
	while ( 1 ) ;

	return 0 ;
}
