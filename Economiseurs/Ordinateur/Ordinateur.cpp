///////////////////////////////////////////////////////////////////////////////
//	Ordinateur
//	Simule un bon vieil ordinateur des '80s
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <mmsystem.h>
#include "resource.h"
#include "..\Economiseur Generique\economiseur.h"
#include "ordinateur.h"

COrdinateur MonEconomiseur ;


COrdinateur::COrdinateur(  )
:CEconomiseur( "Ordinateur" ) //,"BMI" )
	{
	_FichierScript	=	"ORDINATEUR.SCRIPT" ;
	_hFont			=	0 ;
	_Delai			=	100 ;
	_hThreadClignote=0 ;
	}
		
	
COrdinateur::~COrdinateur()
	{
	if ( _hFont )
		DeleteObject( _hFont ) ;
	}

void COrdinateur::InitSave( HWND	hWnd )
	{
	if ( ! Apercu() && _ChangeResolution )
		{
		// Prendre la resolution la plus pourrie possible
		if ( ! ChangeResolution( 320, 200, -1 ))
		if ( ! ChangeResolution( 640, 480, -1 ))
			ChangeResolution( 800, 600, -1 );
		}
	CEconomiseur::InitSave( hWnd ) ;

	// Lire le fichier de lignes
	CStdioFile	Fichier ;
	if ( Fichier.Open( _FichierScript, CFile::modeRead ))
		{
		CString		Ligne ;
		while ( Fichier.ReadString( Ligne ))
			{
			Ligne.TrimLeft() ;
			Ligne.TrimRight() ;
			if ( ! Ligne.IsEmpty() && Ligne[0] != ';' )
				_Lignes.AddTail( Ligne ) ;
			}
		Fichier.Close() ;
		}
	else
		{
		_Lignes.AddTail( "BIP CLIGNOTE \"Le fichier de script pour cet economiseur d'écran est\"" ) ;
		_Lignes.AddTail( "\"incorrect ou n'existe pas\" CLIGNOTE " ) ;
		_Lignes.AddTail( "\"\"" ) ;
		_Lignes.AddTail( "\"Utilisez la fenêtre de configuration pour choisir un fichier .SCRIPT\"" ) ;
		_Lignes.AddTail( "\"\"" ) ;
		}

	_LigneCourante	=	"" ;
	_Pos			=	0 ;
	_IndiceSurLigne	=	0 ;
	_XCurseur		=	0 ;
	_YCurseur		=	0 ;
	_PauseEnCours	=	0 ;

	_Clignote		=	FALSE ;

	_LargeurCase	=	Largeur / NB_COLONNES ;
	_HauteurCase	=	Hauteur / NB_LIGNES ;

	_CouleurFond	=	0 ;
	_CouleurCar		=	RGB( 0, 255, 0 ) ;

	NoircirEcran	=	TRUE ;

	LOGFONT LogFont ;
	LogFont.lfHeight		=	_HauteurCase ;
	LogFont.lfWidth			=	_LargeurCase ;
	LogFont.lfEscapement	=	0 ;
	LogFont.lfOrientation	=	0 ;
	LogFont.lfWeight		=	FW_NORMAL ;
	LogFont.lfItalic		=	FALSE ;
	LogFont.lfUnderline		=	FALSE ;
	LogFont.lfStrikeOut		=	FALSE ;
	LogFont.lfCharSet		=	ANSI_CHARSET;
	LogFont.lfOutPrecision	=	OUT_DEFAULT_PRECIS ;
	LogFont.lfClipPrecision=	CLIP_CHARACTER_PRECIS ;
	LogFont.lfQuality		=	DRAFT_QUALITY ;
	LogFont.lfPitchAndFamily=	FIXED_PITCH | FF_DONTCARE ;
	lstrcpy( LogFont.lfFaceName, "FixedSys" ) ;

	_hFont					=	CreateFontIndirect( &LogFont ) ;

	_DernierTps			=	GetCurrentTime() ;

	}

void COrdinateur::InitConfig( HWND hWnd )
	{
	}

void COrdinateur::Animation( CDC&	Dc )
	{
	DWORD	CurrentTime	=	GetCurrentTime() ;
	DWORD	Delta		=	CurrentTime - _DernierTps ;
	if ( Delta < _Delai )
		Sleep( _Delai - Delta ) ;

	_DernierTps	=	CurrentTime ;
	
	TEXTMETRIC	Tm ;
	Dc.GetTextMetrics( &Tm ) ;
	_LargeurCase	=	Tm.tmAveCharWidth ;	// On utilise une fonte fixe
	_HauteurCase	=	Tm.tmHeight + Tm.tmExternalLeading ;

	if ( _PauseEnCours > 0 )
		_PauseEnCours -- ;
	else
		{
		if ( _IndiceSurLigne >= _LigneCourante.GetLength())
			LigneSuivante(Dc) ;
		
		AjouteCaractere( Dc, _LigneCourante[_IndiceSurLigne] ) ;
		_IndiceSurLigne ++ ;
		}
	}

void COrdinateur::PeintFenetre( CDC & Dc, const CRect& R )
	{
	}

BOOL COrdinateur::PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
	{
	switch( Message )
		{
		case WM_INITDIALOG :
			LitPreferences() ;
			SetDlgItemText( hWnd, IDC_FICHIER, _FichierScript ) ;
			CheckDlgButton( hWnd, IDC_CHECK1, _ChangeResolution ) ;
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					GetDlgItemText( hWnd, IDC_FICHIER, _FichierScript.GetBuffer( _MAX_PATH ), _MAX_PATH ) ;
					_FichierScript.ReleaseBuffer() ;
					_ChangeResolution = IsDlgButtonChecked( hWnd, IDC_CHECK1 ) ;
					EcritPreferences() ;
					EndDialog( hWnd, TRUE ) ;
					break ;

				case IDCANCEL :
					EndDialog( hWnd, FALSE ) ;
					break ;

				case IDC_PARCOURIR :
					{
					CFileDialog	Dlg( TRUE, "Script", NULL, OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_LONGNAMES,
									 "Fichiers script|*.script|Fichiers texte|*.txt|Tous les fichiers|*.*||" ) ;
					if ( Dlg.DoModal() == IDOK )
						{
						_FichierScript	=	Dlg.GetPathName() ;
						SetDlgItemText( hWnd, IDC_FICHIER, _FichierScript ) ;
						}
					}
					break ;

				default :
					return FALSE ;
				}
			break ;

		default :
			return FALSE ;
		}
	return TRUE ;
	}

///////////////////////////////////////////////////////////////////////////////
// Lecture ET ecriture des preferences dans la registry
///////////////////////////////////////////////////////////////////////////////
void COrdinateur::Preferences()
	{
//	Preference( "Fichier Script", _FichierScript ) ;
//	Preference( "Changer resolution", _ChangeResolution ) ;

//	if ( ! ShareWare())
//		Preference( "Delai", _Delai ) ;
	}


void COrdinateur::LigneSuivante( CDC & Dc )
{
	_IndiceSurLigne	=	0 ;

	// Efface le curseur
	do
		{
		Dc.SetBkColor( 0 ) ;
		Dc.TextOut( _XCurseur*_LargeurCase, _YCurseur*_HauteurCase, " ", 1 ) ;

		_LigneCourante =	ProchainMorceau(Dc) ;
		}
	while ( _LigneCourante.IsEmpty()) ;
}

void COrdinateur::AjouteCaractere( CDC & Dc, char c )
{
	_Cases[_XCurseur][_YCurseur]._Car		    =	c ;
	_Cases[_XCurseur][_YCurseur]._CouleurCar	=	_CouleurCar ;
	_Cases[_XCurseur][_YCurseur]._CouleurFond	=	_CouleurFond ;
	_Cases[_XCurseur][_YCurseur]._Clignote		=	_Clignote ;

	if ( _Clignote )
		_Cases[_XCurseur][_YCurseur].Clignote( Dc, _XCurseur * _LargeurCase, _YCurseur*_HauteurCase,
											   _ClignoteAllume ) ;
	else
		_Cases[_XCurseur][_YCurseur].Affiche( Dc, _XCurseur * _LargeurCase, _YCurseur*_HauteurCase ) ;

	if ( _XCurseur <= NB_COLONNES - 1)
		_XCurseur ++ ;
	else
		{
		_XCurseur =	0 ;
		_YCurseur ++ ;
		}

	if ( _YCurseur >= NB_LIGNES-1 )
		{
		Scroll( Dc ) ;
		_YCurseur= NB_LIGNES -2 ;
		}
}

void COrdinateur::Scroll( CDC & Dc )
{
	_Clignotant.Lock() ;
	int i, j ;

	for ( i = 0; i < NB_LIGNES-1; i++)
		for ( j = 0; j < NB_COLONNES; j++)
			{
			_Cases[j][i] = _Cases[j][i+1] ;
			_Cases[j][i].Affiche( Dc, j * _LargeurCase, i * _HauteurCase ) ;
			}

	for ( j = 0; j < NB_COLONNES; j++)
		{
		_Cases[j][i]._Car = ' ' ;
		_Cases[j][i]._CouleurFond = 0 ;
		_Cases[j][i]._CouleurCar = 0 ;
		_Cases[j][i]._Clignote	=	0 ;

		_Cases[j][i].Affiche( Dc, j * _LargeurCase, i * _HauteurCase ) ;
		}
	_YCurseur	=	NB_LIGNES - 2 ;
	_Clignotant.Unlock() ;
}

void COrdinateur::InverseCurseur( CDC & Dc )
{
	if ( _CurseurInverse )
		{
		Dc.SetTextColor( 0 ) ;
		Dc.SetBkColor( RGB( 0, 255, 0 )) ;
		}
	else
		{
		Dc.SetBkColor( 0 ) ;
		Dc.SetTextColor( RGB( 0, 255, 0 )) ;
		}

	Dc.TextOut( _XCurseur*_LargeurCase, _YCurseur*_HauteurCase, "_", 1 ) ;

	_CurseurInverse	=	! _CurseurInverse ;
}

CString COrdinateur::ProchainMorceau( CDC & Dc )
{
	_LigneATraiter.TrimLeft() ;

	if ( _LigneATraiter.IsEmpty())
		{
		_XCurseur	=	0 ;
		_YCurseur	++ ;

		if ( _YCurseur >= NB_LIGNES-1 )
			Scroll( Dc ) ;

		// Chercher la ligne suivante dans la liste
		if ( ! _Pos )
			_Pos	=	_Lignes.GetHeadPosition() ;

		_LigneATraiter	=	_Lignes.GetNext( _Pos ) ;
		}

	switch( _LigneATraiter[0])
		{
		case '\"' :
			// Affichage de la machine :
		case '\'' :
			// Saisie :
			{
			const char	C	=	_LigneATraiter[0] ;
			_LigneATraiter	=	_LigneATraiter.Mid(1) ;
			int	IndiceFin	=	_LigneATraiter.Find( C ) ;
			if ( IndiceFin == -1 )
				IndiceFin	=	_LigneATraiter.GetLength() ;

			const CString	Result	=	_LigneATraiter.Left( IndiceFin ) ;
			_LigneATraiter			=	_LigneATraiter.Mid( IndiceFin + 1 ) ;

			if ( C == '\"' ) // Surbrillance
				{
				if ( _CouleurFond != 0)
					_CouleurFond	=	RGB( 0, 255, 0 ) ;
				else
					_CouleurCar	=	RGB( 0, 255, 0 ) ;
				}
			else
				{
				if ( _CouleurFond != 0)
					_CouleurFond	=	RGB( 0, 128, 0 ) ;
				else
					_CouleurCar	=	RGB( 0, 128, 0 ) ;
				}
			return Result ;
			}

		default :
			{
			// Isole le mot clef
			int		Indice	=	_LigneATraiter.FindOneOf( " \t," ) ;
			if ( Indice == -1)
				Indice	=	_LigneATraiter.GetLength() ;

			CString	MotCle	=	_LigneATraiter.Left( Indice ) ;
			_LigneATraiter	=	_LigneATraiter.Mid( Indice ) ;
			_LigneATraiter.TrimLeft() ;

			MotCle.MakeUpper() ;

			if ( MotCle	==	"PAUSE" )
				{
				// Nb de cycles de pause ?
				int Indice	=	_LigneATraiter.FindOneOf( " \t," ) ;
				if ( Indice == -1 ) // Separateur non trouve -> Fin de la ligne
					Indice	=	_LigneATraiter.GetLength() ;

				_PauseEnCours	=	atoi( _LigneATraiter.Left( Indice )) ;
				_LigneATraiter	=	_LigneATraiter.Mid( Indice ) ;
				}
			else 
			if  ( MotCle	== "BIP" )
				{
				if ( ! PlaySound( MAKEINTRESOURCE( IDR_BIP ), AfxGetResourceHandle(), 
									SND_RESOURCE | SND_SYNC ))
					MessageBeep(0xFFFFFFFF) ;
				}
			if ( MotCle	== "INVERSE" )
				{
 				COLORREF	Sos	=	_CouleurFond ;
				_CouleurFond	=	_CouleurCar ;
				_CouleurCar		=	Sos ;
				}
			else
			if ( MotCle == "CLIGNOTE" )
				{
				_Clignote	=	! _Clignote ;
				_CouleurFond	=	0 ;
				_CouleurCar		=	RGB( 0, 255, 0 ) ;
				}
			}
			return "" ; // Pour l'instant
		}

	return "" ;
}

void COrdinateur::ClignoteCaracteres( CDC & Dc )
{
	int i, j ;

	_ClignoteAllume	= ! _ClignoteAllume ;

	for ( i = 0; i < NB_LIGNES; i++)
		for ( j = 0; j < NB_COLONNES; j++)
			_Cases[j][i].Clignote( Dc, j * _LargeurCase, i * _HauteurCase, _ClignoteAllume ) ;
}

void COrdinateur::InitDC( CDC & Dc )
{
	_hOldFont	=	(HFONT)SelectObject( Dc, _hFont ) ;
	DWORD	ThreadId ;
	_hThreadClignote	=	CreateThread( NULL, 0, FctThreadClignote, (LPVOID)this, CREATE_SUSPENDED, &ThreadId ) ;
//	SetThreadPriority( _hThreadClignote, THREAD_PRIORITY_BELOW_NORMAL ) ;
	ResumeThread( _hThreadClignote ) ;
}

void COrdinateur::FinDC( CDC & Dc )
{
	TerminateThread( _hThreadClignote, 0 ) ;
	_hThreadClignote=0 ;
	SelectObject( Dc, _hOldFont ) ;
}


DWORD _stdcall COrdinateur::FctThreadClignote( LPVOID p )
{
	/*COrdinateur*	pOrdinateur =(COrdinateur*)p ;

	while ( TRUE )
		{
		Sleep( 500 ) ;
		pOrdinateur->_Clignotant.Lock() ;
		pOrdinateur->ClignoteCaracteres( pOrdinateur->GetDC()) ;
		pOrdinateur->InverseCurseur( pOrdinateur->GetDC()) ;
		pOrdinateur->_Clignotant.Unlock() ;
		}	*/
	return 0 ;
}
