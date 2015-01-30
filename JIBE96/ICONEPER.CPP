///////////////////////////////////////////////////////////////////////////////
// CIconePeriodique
// Classe generique de toute icone periodique
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "iconeperiodique.h"

CObList		CIconePeriodique::_ListeIconesPeriodiques ;
UINT		CIconePeriodique::_uiTimer ;
IMPLEMENT_DYNAMIC( CIconePeriodique, CIcone ) ;

///////////////////////////////////////////////////////////////////////////////
// Constructeur
///////////////////////////////////////////////////////////////////////////////
CIconePeriodique::CIconePeriodique()
{
	if ( _ListeIconesPeriodiques.IsEmpty())
		{
		// Mettre en route le timer
		_uiTimer = SetTimer( NULL, 1, 1000, TimerProc ) ;
		}
	_ListeIconesPeriodiques.AddTail( this ) ;
}


CIconePeriodique::~CIconePeriodique()
{
	POSITION	Pos	=	_ListeIconesPeriodiques.Find( this ) ;
	ASSERT( Pos ) ;
	_ListeIconesPeriodiques.RemoveAt( Pos ) ;

	if ( _ListeIconesPeriodiques.IsEmpty() )
		{
		// Arreter le timer
		KillTimer( NULL, _uiTimer ) ;
		}
}

///////////////////////////////////////////////////////////////////////////////
// CIconePeriodique::TimerProc
// Fonction appelee toutes les secondes.
// On parcours la liste des icones periodiques pour les mettre a jour
// On detecte un eventuel economiseur d'ecran pour ne pas le perturber
///////////////////////////////////////////////////////////////////////////////
void CALLBACK CIconePeriodique::TimerProc( HWND, UINT, UINT, DWORD )
{
	if ( ! FindWindow("WindowsScreenSaverClass", NULL ))
		{
		POSITION	Pos	=	_ListeIconesPeriodiques.GetHeadPosition() ;

		while ( Pos )
			{
			CIconePeriodique*	pIcone	=	(CIconePeriodique*)_ListeIconesPeriodiques.GetNext( Pos ) ;

			pIcone->Update() ;
			}
		}
}
