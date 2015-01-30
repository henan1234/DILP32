// Mail.cpp: implementation of the CMail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mail.h"
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
char Hex( char c )
	{
	static const CString	Hexa( "0123456789ABCDEF" ) ;
	
	c	=	toupper( c ) ;

	return Hexa.Find( c ) ;
	}

CMail::CMail( const CString &  MsgContent )
{
	_From	=	Extract( MsgContent, "From") ;
	_Subject=	Extract( MsgContent, "Subject" ) ;
	_Content=	ExtractContent( MsgContent ) ;
	_MessageId=	Extract( MsgContent, "Message-ID" ) ;
	_Acknowledged = FALSE ;

	// Essaie d'isoler le nom dans l'expediteur s'il est fourni avec l'@
	_Subject=	ExtraitFrom( _Subject ) ;
	_From	=	ExtraitFrom( _From ) ;

	int Indice = _From.Find( '\"' ) ;
	if ( Indice != -1 )
		{
		CString Travail ;
		Indice ++ ;
		while ( Indice < _From.GetLength() && _From[Indice] != '\"' )
			{
			Travail += _From[Indice] ;
			Indice ++ ;
			}
		_From = Travail ;
		}
}

CMail::~CMail()
{

}


CString CMail::Extract( const CString & Content, const CString & Keyword )
	{
	const CString	Search	=	"\r\n" + Keyword + ": " ;

	int	Indice	=	Content.Find( Search ) ;
	if ( Indice == -1 )
		return "not found" ;
	
	Indice += Search.GetLength() ;

	// Extraire jusqu'a la fin de ligne
	CString Result ;
	while ( Indice < Content.GetLength() && Content[Indice] != '\r' )
		{
		Result += Content[Indice] ;
		Indice ++ ;
		}

	Result.TrimLeft() ;
	Result.TrimRight() ;

	return Result ;
	}

///////////////////////////////////////////////////////////////////////////////
// Extrait le nom, si possible du champ 'From'
///////////////////////////////////////////////////////////////////////////////
CString CMail::ExtraitFrom(const CString &From)
{
	CString Travail( From ) ;
	// ISO ?
	if ( Travail.Find("iso") != -1 )
		Iso( Travail ) ;

	int Indice	=	Travail.Find( '<' ) ;
	if ( Indice > 2 ) // Y'a quelque chose avant -> Le nom
		Travail	=	Travail.Left( Indice -1 ) ;

	return Travail ;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void CMail::Iso(CString & Chaine )
{
	int Indice ;

	while (Chaine.Replace( "=?iso-8859-1?Q?", "" )) ;
	while (Chaine.Replace( "iso", "" )) ;
	while (Chaine.Replace( "?", "" )) ;
	while (Chaine.Replace( "= ", " " )) ;

	do
		{
		Indice	=	Chaine.Find( '=' ) ;
		if ( Indice != -1 )
			{
			if ( Indice < Chaine.GetLength()-2 )
				{
				char	C1	=	Hex( Chaine[Indice+1] ) ;

				char	C2	=	Hex( Chaine[Indice+2] ) ;

				char	C	=	C1 * 16 + C2 ;

				const CString	Left	=	Chaine.Left( Indice ) ;
				const CString	Right	=	Chaine.Mid( Indice + 3 ) ;

				Chaine	=	Left + C + Right ;
				}
			else
				break ;
			}
		}
	while ( Indice != -1 ) ;
}

CString CMail::ExtractContent(const CString &MsgContent)
{
	int Indice	=	MsgContent.Find( "Content-Type: text/plain" ) ;

	if ( Indice == -1 )
		return "" ;
	
	// Se deplacer jusqu'a la fin de la ligne
	Indice		=	MsgContent.Find( "\r\n\r\n", Indice ) ;

	if ( Indice == -1 )
		return "" ;

	CString	Travail	=	MsgContent.Mid( Indice + 4 ) ;

	CString	Texte	=	ChercheLigneNonVide( Travail ) ;
	Iso( Texte ) ;
	return Texte ;
}

CString CMail::ChercheLigneNonVide(const CString &Chaine)
{
	int	DebutDeLigne	=	0 ;
	int	FinDeLigne		=	Chaine.Find( "\r\n" ) ;

	while ( FinDeLigne != -1 )
		{
		if ( FinDeLigne > DebutDeLigne )
			return Chaine.Mid( DebutDeLigne, FinDeLigne-DebutDeLigne ) ;

		DebutDeLigne	=	FinDeLigne + 2 ;
		FinDeLigne		=	Chaine.Find( "\r\n", DebutDeLigne ) ;
		}

	return "" ;
}

CString CMail::DecodeBody(const CString &Body)
{
	CString Travail( Body ) ;

	CString sCooked = "";
	LPTSTR szBad = "\r\n..\r\n";
	LPTSTR szGood = "\r\n.\r\n";
	int nPos;
	int nBadLength = strlen( szBad );
	if( Travail.Left( 4 ) == "..\r\n" )
		Travail = Travail.Mid(1);
	//
	// This is a little inefficient because it beings a search
	// at the beginning of the string each time. This was
	// the only thing I could think of that handled ALL variations.
	// In particular, the sequence "\r\n.\r\n.\r\n" is troublesome. 
	// (Even CStringEx's FindReplace wouldn't handle that situation
	// with the global flag set.)
	//
	while( (nPos = Travail.Find( szBad )) > -1 )
	{
		sCooked = Travail.Mid( 0, nPos );
		sCooked += szGood;
		Travail = sCooked + Travail.Right( Travail.GetLength() - (nPos + nBadLength) );
	}

	return Travail.Left( 200 ) ;
}
