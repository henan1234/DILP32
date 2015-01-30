// MediaFile.cpp: implementation of the CMediaFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SoftCollection.h"
#include "MediaFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMediaFile::CMediaFile()
{

}

CMediaFile::~CMediaFile()
{

}


//////////////////////////////////////////////////////////////////////
// Ecrit une chaine de caracteres dans le fichier
//////////////////////////////////////////////////////////////////////
void CMediaFile::WriteString( const CString & String )
	{
	long	longueur	=	String.GetLength() ;

	Write( &longueur, sizeof( longueur )) ;
	Write( (const char*)String, longueur ) ;
	}

//////////////////////////////////////////////////////////////////////
// Lit une chaine de caracteres
//////////////////////////////////////////////////////////////////////
CString CMediaFile::ReadString()
	{
	long longueur ;
	Read( &longueur, sizeof( longueur )) ;

	CString Result ;
	char * pBuffer	=	Result.GetBufferSetLength( longueur ) ;
	Read( pBuffer, longueur ) ;

	Result.ReleaseBuffer( longueur ) ;
	return Result ;
	}

void CMediaFile::WriteFormat(const CString &formatname)
{
	WriteString( "@FORMAT@" + formatname ) ;
}

BOOL CMediaFile::VerifieFormat(const CString &formatname)
{
	CString	lecture	=	ReadString() ;

	if ( lecture != ( "@FORMAT@" + formatname ))
		{
		CString Message ;
		Message =	formatname + " attendu dans le fichier, format incorrect" ;
		MessageBox( 0, Message, "Erreur", MB_OK | MB_ICONSTOP ) ;
		return FALSE ;
		}

	return TRUE ;
}
