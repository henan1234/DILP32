///////////////////////////////////////////////////////////////////////////////
// CLPIString
//	Classe CString amelioree
//	Deux nouveaux services :
//		Construction directement a partir de la STRINGTABLE
//		formatage a l'interieur de la chaine par wsprintf
///////////////////////////////////////////////////////////////////////////////

#ifndef __LPISTRING__
#define __LPISTRING__

class	CLPIString : public CString
{
	public :
		// Fait un LoadString
		CLPIString( WORD	IdString ) ;
} ;

#endif
