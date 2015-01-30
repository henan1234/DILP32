///////////////////////////////////////////////////////////////////////////////
// ListeEconomiseurs.H
// Interface de la classe CListeEconomiseur
///////////////////////////////////////////////////////////////////////////////
#ifndef _LISTECO_H_
#define _LISTECO_H_

class	CEconomiseur ;

class	CListeEconomiseurs : private	CObArray
{
	public :
		CListeEconomiseurs() ;
		~CListeEconomiseurs() ;
		
		void	Init() ;
		
		CEconomiseur *	PlusPrioritaire( void ) ;
	    
	    int		NbEconomiseurs( void ) { return GetSize() ; } ;
	    CEconomiseur*	GetAt( int I ) { return (CEconomiseur*)CObArray::GetAt(I) ; } ;
	    
	    UINT	PrioriteMax( void ) ;
	    
		void	SauveConfiguration( void ) ;

	private :
		void	ParcoursSCR( LPCSTR Dir ) ;
} ;

#endif
