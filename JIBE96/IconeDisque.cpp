///////////////////////////////////////////////////////////////////////////////
// CIconeDisque
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"
#include "iconedisque.h"
#include "propsdisque.h"
#include "jibe96view.h"

#define new DEBUG_NEW

IMPLEMENT_SERIAL( CIconeDisque,CIconeJauge, 0 ) ;

CIconeDisque::CIconeDisque()
:_NomDisque( "C:\\" )
	{
	}

CIconeDisque::~CIconeDisque()
	{
	}

void	CIconeDisque::Serialize( CArchive & ar )
	{
	CIconeJauge::Serialize(ar);
	if ( ar.IsStoring())
		ar << _NomDisque ;
	else
		ar >> _NomDisque ;
	}

UINT	CIconeDisque::GetPourcentage( void )
	{
	DWORD	SectorsPerCluster, BytesPerSector, FreeClusters, Clusters ;
	if ( GetDiskFreeSpace( _NomDisque ,&SectorsPerCluster, &BytesPerSector, & FreeClusters, &Clusters ))
		return ChangeIntervalle( FreeClusters, 0, Clusters, 0, 100 ) ;
	
	return 0 ;
}

UINT	CIconeDisque::GetIDBitmap( void ) const
	{
	return (Colors64K() ? IDB_DISQUE : IDB_DISQUE16 ) ;
	}

COLORREF	CIconeDisque::GetCouleurBarre( BOOL	Alarme ) const
	{
	if ( Alarme )
		return RGB( 128, 0, 0 ) ;
	else
		return RGB( 64,128,64) ;
	}


	
UINT		CIconeDisque::GetMenuID( void ) const
	{
	return IDR_MENU_DISQUE ;
	}


CString CIconeDisque::GetText( UINT Pourcentage )
{
	return _NomDisque ;
}

BOOL	CIconeDisque::ExecuteCommand( UINT NoCommande )
	{
	switch( NoCommande )
		{
		case ID_PROPRIETES :
			ExecuteCommand() ;
			break ;

		case ID_DISQUE_EXPLORER :
			WinExec( "EXPLORER " + _NomDisque, SW_SHOW ) ;
			break ;

		default :
			return FALSE ;
		}
	return TRUE ;
	}

BOOL	CIconeDisque::ExecuteCommand( void )
	{
	CPropsDisque	Dlg(this) ;

	Dlg.m_PourcentageAlarme	=	(int)GetPourcentageAlarme() ;
	Dlg.m_Disque			=	_NomDisque ;

	if ( Dlg.DoModal() != IDOK )
		return FALSE ;

	SetPourcentageAlarme( (UINT)Dlg.m_PourcentageAlarme ) ;
	_NomDisque			=	Dlg.m_Disque ;

	return TRUE ;
	}

CString CIconeDisque::GetTip( void )
{
	CString	Nom	=	CPropsDisque::GetDriveName( _NomDisque );
	DWORD	SectorsPerCluster, BytesPerSector, FreeClusters, Clusters ;
	if ( ! GetDiskFreeSpace( _NomDisque ,&SectorsPerCluster, &BytesPerSector, & FreeClusters, &Clusters ))
		return Nom ;
	
	DWORD	Ko	=	(DWORD)((double)BytesPerSector * SectorsPerCluster * Clusters / 1024.0 ) ;
	DWORD	KoLibres	=	(DWORD)((double)BytesPerSector * SectorsPerCluster * FreeClusters / 1024.0 ) ;

	CString Libre ;
	CString	Total ;

	if ( Ko > 1024L )
		// en Mo
		Total = FormatNumber( Ko / 1024.0  ) + " Mo"  ;
	else
		Total  = FormatNumber( Ko ) + " Ko" ;

	if ( KoLibres > 1024L )
		// en Mo
		Libre = FormatNumber( KoLibres / 1024.0  ) + " Mo" ;
	else
		Libre = FormatNumber( KoLibres ) + " Ko" ;

	CString	Texte ;
	Texte.Format( IDS_TIP_DISQUE,
					(LPCSTR)Nom,
					(LPCSTR)Libre,
					(LPCSTR)Total) ;
	return Texte ;
}

CWnd* CIconeDisque::OuvreFenetre( CRect & RectIcone, CWnd * pParent )
{
	CPropsDisque*	pDlg =	new CPropsDisque( this ) ;

	pDlg->m_PourcentageAlarme	=	(int)GetPourcentageAlarme() ;
	pDlg->m_Disque				=	_NomDisque ;

	pDlg->Create( IDD_DIALOG1, pParent ) ;

	pParent->ClientToScreen( RectIcone ) ;
	pDlg->AjusteRectangle( RectIcone ) ;

	//DerouleFenetre( pDlg, RectIcone ) ;
	return pDlg ;
}


void CIconeDisque::SetNomDisque( const CString & Nom )
{
	if ( Nom != _NomDisque )
		{
		_NomDisque	=	Nom ;
		Modifiee( TRUE ) ;
		CJibe96View::UpdateIcon( this ) ;
		}
}
