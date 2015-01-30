///////////////////////////////////////////////////////////////////////////////
// CLPISablier
//	Pour mettre temporairement le curseur sablier et l'enlever en une seule
//	ligne
///////////////////////////////////////////////////////////////////////////////
#ifndef __AFXWIN_H__
#include <afxwin.h>
#endif

#include "LpiSablier.h"

CLPISablier::CLPISablier()
{
	_hAncienCurseur	= SetCursor( LoadCursor( NULL, IDC_WAIT )) ;
}

CLPISablier::CLPISablier( HCURSOR hCurseur )
{
	_hAncienCurseur	= SetCursor( hCurseur ) ;
}

CLPISablier::~CLPISablier()
{
	SetCursor( _hAncienCurseur ) ;
}
