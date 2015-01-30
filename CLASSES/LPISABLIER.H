///////////////////////////////////////////////////////////////////////////////
// CLPISablier
//	Pour mettre temporairement le curseur sablier et l'enlever en une seule
//	ligne
///////////////////////////////////////////////////////////////////////////////

#ifndef __LPISABLIER__
#define __LPISABLIER__

class	CLPISablier
{
	public :
		CLPISablier() ;
		CLPISablier( HCURSOR ) ;		// Force le curseur d'un certain type
		~CLPISablier() ;
	private :
		HCURSOR	_hAncienCurseur ;
} ;

#endif
