///////////////////////////////////////////////////////////////////////////////
// LPICLASSES
// Ces classes derivees des MFC me facilitent la vie
///////////////////////////////////////////////////////////////////////////////
#include <afxwin.h>
#include <direct.h>
#include <math.h>

#include "lpiclasses.h"

///////////////////////////////////////////////////////////////////////////////
// CLPIString
//	Classe CString amelioree
//	Deux nouveaux services :
//		Construction directement a partir de la STRINGTABLE
//		formatage a l'interieur de la chaine par wsprintf
///////////////////////////////////////////////////////////////////////////////
CLPIString::CLPIString( WORD	IdString )
{
	LoadString( IdString ) ;
}

///////////////////////////////////////////////////////////////////////////////
//	CLPIRect
//	Un CRect construit directement avec les dimension d'une zone client
///////////////////////////////////////////////////////////////////////////////
CLPIRect::CLPIRect( CWnd * pWnd )
{
	pWnd->GetClientRect( this ) ;
}

CLPIRect::operator CRect( void ) const
{
	return * (CRect*)this ;
}

void CLPIRect::Serialize( CArchive & ar )
{
	if ( ar.IsStoring())
		{
		ar << left ;
		ar << right ;
		ar << top ;
		ar << bottom ;
		}
	else
		{
		ar >> left ;
		ar >> right ;
		ar >> top ;
		ar >> bottom ;
		}
}


#include "LpiSablier.cpp"
#include "LpiBitmap.cpp"
#include "LpiDC.cpp"
#include "LpiIcone.cpp"
#include "LpiPathName.cpp"
#include "LpiCouleur.cpp"

