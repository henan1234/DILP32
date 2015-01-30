///////////////////////////////////////////////////////////////////////////////
// CEcoNeige
///////////////////////////////////////////////////////////////////////////////
#include "..\Economiseur Generique\stdafx.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "flocon.h"
#include "neige.h"
#include "resource.h"

CEcoNeige	MonEconomiseur ;


CEcoNeige::CEcoNeige()
:CEconomiseur( "Neige" )
{
	_pImageDeFond	=	0 ;
	_NbMaxFlocons	=	1000 ;
	_TailleMax		=	4 ;
	_VentMax		=	4 ;
	_pPalette		=	0 ;
}


CEcoNeige::~CEcoNeige()
{
	delete	_pImageDeFond ;
	delete	_pPalette ;
}
		
		
void CEcoNeige::InitSave( HWND	hWnd )
{
	NoircirEcran	=	FALSE ;

	CEconomiseur::InitSave(hWnd) ;

	_Affichage.Espace( CRect(0,0,Largeur, Hauteur)) ;

	CDIBSurface	Dib	;

	_pPalette	=	new	CDIBPal ;

	if ( ! _NomImage.IsEmpty())
		{
		// Charger l'image de fond a partir d'un fichier
		Dib.Load( _NomImage ) ;
		_pPalette->Create( &Dib ) ;
		}
	else
		{
		// Image de fond a partir de l'ecran
		_pPalette->CreateWash() ;
	
		Dib.Create( ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ), _pPalette ) ;
		HDC	hDC	=	CreateDC( "display", 0, 0, 0 ) ;
		BitBlt( Dib.GetHDC(), 0, 0, ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ),
				hDC, 0, 0, SRCCOPY ) ;
		DeleteDC( hDC ) ;
		}

	
	_pImageDeFond	=	new CDIBSurface ;
	_pImageDeFond->Create( Largeur, Hauteur, _pPalette ) ;

	Dib.StretchBlt( _pImageDeFond->GetDC(), 0, 0, Largeur, Hauteur,
					0, 0, Dib.GetWidth(), Dib.GetHeight()) ;

	SetPalette( (HPALETTE)_pPalette->m_hObject ) ;
}



void CEcoNeige::InitConfig( HWND hWnd )
{
}

void CEcoNeige::Animation( CDC&	Dc)
{
	//
	// Ajouter de nouveaux flocons, si on peut
	//
	for ( int j = 0; j <  10; j++)
		if ( _ListeFlocons.GetCount() < _NbMaxFlocons )
			{
			// Ajout d'un flocon
			const	NiveauGris	=	Alea( 32, 255 ) ;
			CFlocon	*	pFlocon	=	new CFlocon( Alea( 0, Largeur ),
												 0,
												 RGB( NiveauGris, NiveauGris, NiveauGris ),
												 Alea( 1, _TailleMax )) ;

			_ListeFlocons.AddTail( pFlocon ) ;
			}
		else
			break ;
	
	// Changement global du vent pour tous les flocons
	if ( UnSur( 10 ))
		CFlocon::ChangeVent( Alea( -_VentMax, _VentMax )) ;

	// Deplacer et afficher les flocons
	POSITION Pos	=	_ListeFlocons.GetHeadPosition();
	while (Pos)
		{
		const POSITION	Old	=	Pos ;
		CFlocon*	pFlocon	=	_ListeFlocons.GetNext( Pos ) ;
		CRect	R	=	pFlocon->Rectangle() ;

		if ( R.top > Hauteur )
			{
			// Le flocon est sorti de l'ecran
			delete pFlocon ;
			_ListeFlocons.RemoveAt( Old ) ;
			}
		else
			{
			_pImageDeFond->BitBlt( Dc, R.left,R.top, R.Width(), R.Height(),
								   R.left,R.top ) ;
			pFlocon->Bouge() ;

			pFlocon->Affiche( Dc.m_hDC ) ;
			}
		}
}

void CEcoNeige::PeintFenetre( CDC & Dc, const CRect& R )
{
	if ( _pImageDeFond )
		{
		_pImageDeFond->BitBlt( &Dc, R.left,R.top, R.Width(), R.Height(), 0, 0 ) ;
		}
}

BOOL CEcoNeige::PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
	{
	switch( Message )
		{
		case WM_INITDIALOG :
			LitPreferences() ;
			SendDlgItemMessage( hWnd, IDC_SPIN1, UDM_SETBUDDY, (WPARAM)GetDlgItem( hWnd, IDC_NBFLOCONS ), 0 ) ;
			SendDlgItemMessage( hWnd, IDC_SPIN1, UDM_SETRANGE, 0, (LPARAM)MAKELONG( 5000, 1) ) ;
			SendDlgItemMessage( hWnd, IDC_SPIN1, UDM_SETPOS, 0, (LPARAM)MAKELONG( _NbMaxFlocons, 0 ) ) ;
			SetDlgItemInt	  ( hWnd, IDC_NBFLOCONS, _NbMaxFlocons, TRUE ) ;
			SetDlgItemText( hWnd, IDC_NOM, _NomImage ) ;

			if ( _NomImage.IsEmpty())
				{
				CheckRadioButton( hWnd, IDC_ECRAN, IDC_FICHIER, IDC_ECRAN ) ;
				EnableWindow( GetDlgItem( hWnd, IDC_NOM), FALSE ) ;
				EnableWindow( GetDlgItem( hWnd, IDC_PARCOURIR ), FALSE ) ;
				}
			else
				{
				CheckRadioButton( hWnd, IDC_ECRAN, IDC_FICHIER, IDC_FICHIER ) ;
				}
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDC_PARCOURIR :
					{
					static	char	Filtre[]	=	"Bitmaps|*.BMP;*.DIB||" ;
					CWnd	Wnd ;
					Wnd.Attach( hWnd ) ;
					CFileDialog	 Dlg( TRUE, "BMP", _NomImage, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NONETWORKBUTTON,
									  Filtre, &Wnd ) ;

					if ( Dlg.DoModal() == IDOK )
						{
						_NomImage	=	Dlg.GetPathName() ;
						SetDlgItemText( hWnd, IDC_NOM, _NomImage ) ;
						}

					Wnd.Detach() ;
					
					}
					break ;

				case IDC_ECRAN :
					{
					CheckRadioButton( hWnd, IDC_ECRAN, IDC_FICHIER, IDC_ECRAN ) ;
					EnableWindow( GetDlgItem( hWnd, IDC_NOM), FALSE ) ;
					EnableWindow( GetDlgItem( hWnd, IDC_PARCOURIR ), FALSE ) ;
					}
					break ;

				case IDC_FICHIER :
					{
					CheckRadioButton( hWnd, IDC_ECRAN, IDC_FICHIER, IDC_FICHIER ) ;
					EnableWindow( GetDlgItem( hWnd, IDC_NOM), TRUE ) ;
					EnableWindow( GetDlgItem( hWnd, IDC_PARCOURIR ), TRUE ) ;
					}
					break ;


				case IDOK :
					{
					BOOL Tr ;
					_NbMaxFlocons	=	GetDlgItemInt( hWnd, IDC_NBFLOCONS, &Tr, FALSE ) ;

					if ( IsDlgButtonChecked( hWnd, IDC_ECRAN ))
						_NomImage.Empty() ; 

					EcritPreferences() ;
					}
					break ;
				}
			break ;
		}
	return FALSE ;
	}

///////////////////////////////////////////////////////////////////////////////
// Lecture/Ecriture des preferences
///////////////////////////////////////////////////////////////////////////////
void CEcoNeige::Preferences()
	{
	Preference( "Nb. max flocons", _NbMaxFlocons ) ;
	Preference( "Image de fond", _NomImage ) ;

//	if ( ! ShareWare())
		{
		Preference( "Vent Max", _VentMax ) ;
		Preference( "Taille Max", _TailleMax ) ;
		}
	}

