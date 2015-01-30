///////////////////////////////////////////////////////////////////////////////
// CGraffiti
//	Implementation de l'economiseur Graffiti
// Cet economiseur dessine a l'ecran avec differents outils tels que les plumes,
// les pinceaux, la craie ...
///////////////////////////////////////////////////////////////////////////////
#include "..\stdafx.h"

#include <windowsx.h>
#include <scrnsave.h>
#include "resource.h"

#include "..\..\classes\dib.h"
#include "..\Economiseur Generique\RectAffichage.h"
#include "Graffiti.h"
#include "resource.h"
#include "trajectoire.h"
#include "outil.h"
#include <RegistrationKey.h>

#define	STYLO			0x0001
#define	PLUME			0x0002
#define CRAIE			0x0004
#define	CRAIEGRASSE		0x0008
#define	DOIGT			0x0010
#define	SURLIGNEUR		0x0020
#define PINCEAU			0x0040
#define GROSPINCEAU		0x0080
#define ESTOMPE			0x0100
#define AEROGRAPHE		0x0200
#define HACHURE			0x0400
#define CRAYONGRIS		0x0800
#define NB_OUTILS		12

typedef	struct
	{
	UINT	IdStringTable ;
	DWORD	Outils ;
	} T_TECHNIQUE ;

const T_TECHNIQUE Techniques[] =
	{
		{ IDS_TOUS,			0xFFFFFFFF },
		{ IDS_STYLOS_PLUMES,( PLUME | STYLO ) },
		{ IDS_FEUTRES,		(STYLO | SURLIGNEUR )},
		{ IDS_PASTEL,		(CRAIE | DOIGT | ESTOMPE) },
		{ IDS_CRAIE_GRASSE,	(CRAIEGRASSE | ESTOMPE )},
		{ IDS_AEROGRAPHE,	(AEROGRAPHE | SURLIGNEUR | ESTOMPE )},
		{ IDS_DESSIN,		( STYLO | PLUME | SURLIGNEUR | DOIGT )},
		{ IDS_TAG,			( AEROGRAPHE | PLUME )},
		{ IDS_PINCEAUX,		( PINCEAU | GROSPINCEAU )},
		{ IDS_CRAYONS,		( HACHURE | STYLO )},
		{ IDS_CRAYONSGRIS,	( CRAYONGRIS )}
	} ;

#define NB_TECHNIQUES		(sizeof( Techniques ) / sizeof( Techniques[0]))

CRegistrationKey	Key( GRAF_PATH, GRAF_HIDDEN ) ;
CGraffiti	CeciEstMonEconomiseur( "Graffiti", "slfjti" ) ;

CGraffiti::CGraffiti( const CString & NomEconomiseur, const CString & ValeurEnregistre )
:	CEconomiseur( NomEconomiseur )
	{
	LitPreferences() ;
	_pOutil	=	0 ;
	_pOld	=	0 ;
	_Feuille=	NOIR ;
	_Technique	=	Techniques[0].Outils ;
	}
		
CGraffiti::~CGraffiti()
	{
	delete _pOutil ;
	delete _pTrajectoire ;

	if ( _pOld )
		{
		CBitmap * pBitmap	=	_MemDC.SelectObject( _pOld ) ;
		pBitmap->DeleteObject() ;
		delete	pBitmap ;
		}
	}


///////////////////////////////////////////////////////////////////////////////	
// Initialisation de l'animation
///////////////////////////////////////////////////////////////////////////////	
void CGraffiti::InitSave( HWND	hWnd ) 
	{
	LitPreferences() ;

	// Essayer de changer la resolution de l'ecran
	if ( _ChangerResolution )
		if (  _Feuille	== NOIR || _Feuille == BLANC )
			{
			if ( ! ChangeResolution( 1024, 768, COLOR_TRUE_32 ))
			if ( ! ChangeResolution( 800, 600, COLOR_TRUE_32 ))
			if ( ! ChangeResolution( 1024, 768, COLOR_TRUE_24 ))
			if ( ! ChangeResolution( 800, 600, COLOR_TRUE_24 ))
			if ( ! ChangeResolution( 640, 480, COLOR_TRUE_32 ))
			if ( ! ChangeResolution( 640, 480, COLOR_TRUE_24 ))
			if ( ! ChangeResolution( 1024, 768, COLOR_64K ))
			if ( ! ChangeResolution( 800, 600, COLOR_64K ))
			if ( ! ChangeResolution( 640, 480, COLOR_64K ))
				// Tant pis, on garde la resolution courante
				;
			}

	CEconomiseur::InitSave(hWnd) ;
	HautePriorite	= TRUE ;

	HDC	hDC	=	CreateCompatibleDC( NULL ) ;
	SetPalette( CreateHalftonePalette(hDC)) ;
	DeleteDC( hDC ) ;

	if ( _Feuille	==	ECRAN )
		{
		// Memorisation de l'image de l'ecran
		CBitmap	*	pBitmap	=	MemoriseEcran( Largeur, Hauteur ) ;
		_MemDC.CreateCompatibleDC( 0  ) ;
		}
	else
		_pOld	= 0 ;

	_pOutil			=	ChoisiOutil() ;
	_pTrajectoire	=	ChoisiTrajectoire() ;

	NoircirEcran	=	(_Feuille == NOIR ) ;
	}


///////////////////////////////////////////////////////////////////////////////	
// Animation, VIRTUELLE
// Une etape de l'animation
///////////////////////////////////////////////////////////////////////////////
void CGraffiti::Animation( CDC&	Dc )
	{
	ASSERT_VALID( _pOutil ) ;
	ASSERT_VALID( _pTrajectoire ) ;

	if ( _pTrajectoire->Fini())
		{
		delete _pTrajectoire ;
		delete _pOutil ;

		_pOutil			=	ChoisiOutil() ;
		_pTrajectoire	=	ChoisiTrajectoire() ;
		}

	_pTrajectoire->PromeneOutil( Dc, _pOutil ) ;
	}
	

void CGraffiti::PeintFenetre( CDC & Dc, const CRect& R )
	{
	switch( _Feuille )
		{
		case ECRAN :
			ASSERT_VALID( &_MemDC ) ;

			Dc.BitBlt( R.left, R.top, R.Width(), R.Height(),
					   &_MemDC, 0, 0, SRCCOPY ) ;
			break ;

		case NOIR :
			ASSERT_VALID( &Dc ) ;
			Dc.PatBlt( R.left, R.top, R.Width(), R.Height(), BLACKNESS ) ;
 			break ;

		case BLANC :
			ASSERT_VALID( &Dc ) ;
			Dc.PatBlt( R.left, R.top, R.Width(), R.Height(), WHITENESS ) ;
			break ;
		}
	}


BOOL CGraffiti::PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam )
	{
	switch( Message )
		{
		case WM_INITDIALOG :
			{
			LitPreferences() ;
			CheckRadioButton( hWnd, IDC_ECRAN, IDC_NOIRE, IDC_ECRAN + _Feuille ) ;
			CheckDlgButton( hWnd, IDC_CHECK1, _ChangerResolution ) ;

			char	 Technique[100] ; ;

			for ( int i = 0; i < NB_TECHNIQUES; i++)
				{
				LoadString( (HINSTANCE)hMainInstance, Techniques[i].IdStringTable, Technique, sizeof( Technique )) ;
				ComboBox_AddString( GetDlgItem( hWnd, IDC_TECHNIQUE ), Technique ) ;
				}

			ComboBox_SetCurSel( GetDlgItem( hWnd, IDC_TECHNIQUE ), IndexFromTechnique( _Technique )) ;
			}
			break ;

		case WM_COMMAND :
			switch( wParam )
				{
				case IDOK :
					if  (IsDlgButtonChecked( hWnd, IDC_ECRAN ))
						_Feuille	=	ECRAN ;
					else
						if  (IsDlgButtonChecked( hWnd, IDC_BLANC ))
							_Feuille	=	BLANC ;
						else
							_Feuille	=	NOIR ;
					_Technique	=	Techniques[ ComboBox_GetCurSel( GetDlgItem(hWnd, IDC_TECHNIQUE ))].Outils ;

					_ChangerResolution	=	IsDlgButtonChecked( hWnd, IDC_CHECK1 ) ;
					EcritPreferences() ;
					EndDialog( hWnd, IDOK ) ;
					return TRUE ;
				default :
					return FALSE ;
				}
		}

	return FALSE ;

	}


COutil * CGraffiti::ChoisiOutil( void )
{
	do 
		{
		switch( Alea( 0, NB_OUTILS-1 ))
			{
			case 0 :
				if ( _Technique & STYLO )
					return new CStylo ;
				break ;

			case 1 :
				if ( _Technique & PLUME )
					return new CPlume ;
				break ;

			case 2 :
				if ( _Technique & CRAIE )
					return new CCraie ;
				break ;

			case 3 :
				if ( _Technique & AEROGRAPHE )
					return new CAerographe ;
				break ;

			case 4 :
				if ( _Technique & ESTOMPE )
					return new CEstompe ;
				break ;

			case 5 :
				if ( _Technique & CRAIEGRASSE )
					return new CCraieGrasse ;
				break ;

			case 6 :
				if ( _Technique & DOIGT )
					return new CDoigt ;
				break ;

			case 7 :
				if ( _Technique & SURLIGNEUR )
					return new CSurligneur ;
				break ;

			case 8 :
				if ( _Technique & PINCEAU )
					return new CPinceau ;
				break ;

			case 9 :
				if ( _Technique & GROSPINCEAU )
					return new	CGrosPinceau ;
				break ;

			case 10 :
				if ( _Technique & HACHURE )
					return new CHachures ;
				break ;

			case 11 :
				if ( _Technique & CRAYONGRIS )
					return new CCrayonGris ;
				break ;

			default :
				ASSERT( FALSE ) ;
			}
		}
	while( 1 ) ;

	return 0 ;
}

void	CGraffiti::Preferences()
	{
	Preference( "Feuille", _Feuille ) ;
	Preference( "Technique", _Technique ) ;
	Preference( "Résolution", _ChangerResolution ) ;
	}

CTrajectoire* CGraffiti::ChoisiTrajectoire( void )
{
	switch( Alea( 0, 1 ))
		{
		case 0 :
			return new CTrajectoireCourbe( Largeur, Hauteur ) ;

		default :
			return new CTrajectoireRectiligne( Largeur, Hauteur ) ;
		}
}

int CGraffiti::IndexFromTechnique( DWORD Technique )
{
	for ( int i = 0; i < NB_TECHNIQUES; i++)
		if ( Techniques[i].Outils	== Technique )
			return i ;

	return 0 ;
}
