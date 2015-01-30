#include "stdafx.h"
#include "tapisserie.h"

#include <stdlib.h>
#include "eco.h"

static const char	*	SousClef	=	"Economiseurs" ;


IMPLEMENT_DYNAMIC( CEconomiseur, CObject ) ;                       

CEconomiseur::CEconomiseur( const CString & Ligne )
{
   _Chemin  =  Ligne ;
   
   char  Buffer[500] ;
   lstrcpy( Buffer, "5,5" ) ;

   CMonAppli::LitChaine( SousClef, _Chemin, Buffer, sizeof( Buffer ) ) ;

   char  *  pMax  =  strtok( Buffer, "," );
   char  *  pCour =  strtok( NULL,  "," ) ;
   
   if ( pMax )
      _Priorite         =  (PRIORITE)atoi( pMax ) ;
   else
      _Priorite         =  PRIORITE_NORMALE ;
      
   if ( pCour )
      _PrioriteCourante =  (PRIORITE)atoi( pCour ) ;
   else
      _PrioriteCourante =  _Priorite ;
      
   CalculeNom() ;
}

void  CEconomiseur::Active( void )
{
   CString  LigneCommande( _Chemin + " /s" ) ;
   SetCursorPos( ::GetSystemMetrics( SM_CXSCREEN ),
   				 ::GetSystemMetrics( SM_CYSCREEN )) ;
   WinExec( LigneCommande,SW_SHOWMAXIMIZED ) ;
}

void  CEconomiseur::Configure( void )
{
   WinExec( _Chemin, SW_SHOW ) ;
}

CEconomiseur & CEconomiseur::operator ++ ( void )
{
   if ( _PrioriteCourante != JAMAIS )
      _PrioriteCourante = _PrioriteCourante + 1 ;
      
   return *this ;
}

int   CEconomiseur::operator > ( const CEconomiseur & E )
{
   return _PrioriteCourante >  E._PrioriteCourante ;
}

void CEconomiseur::Priorite( int P )
{
   _Priorite   =  P ;
   _PrioriteCourante =  P ;
}

void  CEconomiseur::CalculeNom()
{
	char  Fichier[_MAX_FNAME] ;
	_splitpath( _Chemin, NULL, NULL, Fichier, NULL ) ;
			   
	_Nom  =  Fichier ;
}

void	CEconomiseur::SauveConfiguration()
{
   char  Buffer[500] ;
   
   wsprintf( Buffer, "%d,%d", (int)_Priorite, (int)_PrioriteCourante ) ;
   CMonAppli::EcritChaine( SousClef, _Chemin, Buffer ) ;
}
