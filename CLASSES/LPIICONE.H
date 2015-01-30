///////////////////////////////////////////////////////////////////////////////
// CLPIIcone
//	Construction directement a partir des ressources
//	Taille sans s'emmerder avec GetSystemMetrics
///////////////////////////////////////////////////////////////////////////////
#ifndef __LPIICONE_H__
#define __LPIICONE_H__

class	CLPIIcone
{
	public :
		class CLPIPathName ;
		
		CLPIIcone( WORD IdRessource ) ;
		CLPIIcone( LPCSTR	ResourceName ) ;
		CLPIIcone( CWnd * ) ;
		CLPIIcone( LPCSTR, int Indice ) ;
		CLPIIcone( HICON, BOOL = FALSE ) ;
		
		~CLPIIcone() ;
		operator HICON( void ) const ;
		static	CSize	Taille( void ) ;
		static	int		Largeur( void ) ;
		static	int		Hauteur( void ) ;

		HRGN	CreateRegion( BOOL	Exterieur = FALSE ) ;
				
	private :
		HICON	_hIcone ;
		BOOL	_FautDetruire ;
} ;


#endif
