// ImageListHandler.cpp: implementation of the CImageListHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "ImageListHandler.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageListHandler::CImageListHandler()
{
_ImageList.Create( 16,16,
					ILC_COLOR32 | ILC_MASK, 0, 1 ) ;
}

CImageListHandler::~CImageListHandler()
{

}


int CImageListHandler::GetIconIndex( const char * Path )
	{
	void * pObject ;
	char	Extension[ _MAX_EXT ] ;

	_splitpath( Path, NULL, NULL, NULL, Extension ) ;

	// D'abord regarder si on a deja cette extension
	if ( _Extensions.Lookup( Extension, pObject ))
		{
		return (int)pObject ;
		}

	SHFILEINFO FI ;

	SHGetFileInfo( Path, 0, &FI, sizeof( FI ), SHGFI_SMALLICON | SHGFI_ICON  ) ;

	HICON hIcon = FI.hIcon ;
	
	const int Indice	=	_ImageList.Add( hIcon ) ;

	_Extensions.SetAt( Extension, (CObject*)Indice ) ;
	return Indice ;
	}
