// ============================================================================
// ECO.H
// Interface de la classe CEconomiseur qui gere un economiseur d'ecran
// ============================================================================
#ifndef _ECO_H_
#define _ECO_H_

#define JAMAIS             -1
#define PRIORITE_MIN       0
#define PRIORITE_BASSE     2
#define PRIORITE_NORMALE   5
#define PRIORITE_HAUTE     8
#define PRIORITE_MAX       10 
                  
class CEconomiseur : public   CObject
{
   public :
	DECLARE_DYNAMIC( CEconomiseur ) ;
	typedef  int   PRIORITE ;
                
	CEconomiseur( const CString   & ) ;

	// Sauver l'economiseur dans la registry
	void	SauveConfiguration() ;

	// Activer l'economiseur (test)  
	void     Active( void ) ;
	// Configurer l'economiseur
	void     Configure( void ) ;
    
	// Priorite courante
	CEconomiseur & operator ++( void ) ;
	int         operator >( const CEconomiseur & ) ;

	void     PrioriteInitiale( void ) { _PrioriteCourante=_Priorite ; } ;
	int      PrioriteCourante( void ) const { return _Priorite ; } ;
	void		PrioriteCourante( PRIORITE P ) { _Priorite = P ; } ;
    
	// Priorite initiale
	int      Priorite( void ) { return _Priorite ; } ;
	void     Priorite( PRIORITE P ) ;

	const CString & Chemin( void ) const { return _Chemin ; } ;
	const CString & Nom( void ) const { return _Nom ; } ;
      
   private :
      void CalculeNom() ;
   
      CString     _Chemin ;
      CString     _Nom ;
      
      PRIORITE _Priorite ;
      PRIORITE _PrioriteCourante ;
} ;

#endif
