///////////////////////////////////////////////////////////////////////////////
// LISTECO.CPP
// Implementation de la classe qui gere la liste des economiseurs
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <dos.h>

#include "ListeEconomiseurs.h"
#include "eco.h"

void  CListeEconomiseurs::ParcoursSCR( LPCSTR   Dir )
{
	CString  MasqueRecherche( CString(Dir) + "*.SCR" ) ;

	WIN32_FIND_DATA	FInfo ;
	HANDLE	res =	FindFirstFile( MasqueRecherche, &FInfo ) ;
	
	if ( res != INVALID_HANDLE_VALUE )
		{
		int		Indice = 0 ;

		do
			{
			CString  NomFichier( CString(Dir) + FInfo.cFileName ) ;

			CEconomiseur * pEco  =  new CEconomiseur( NomFichier ) ;

			SetAtGrow( Indice, pEco ) ;
			Indice ++ ;
			}
		while ( FindNextFile( res, &FInfo) ) ;
		}

	FindClose( res ) ;
}

CListeEconomiseurs::CListeEconomiseurs()
{
}

void  CListeEconomiseurs::Init()
{
   const int Nb   =  GetSize() ;
   
   for ( int i = 0; i < Nb; i++ )
      {
      CEconomiseur   *  pEco  =  (CEconomiseur*)GetAt( i ) ;
      ASSERT( pEco->IsKindOf( RUNTIME_CLASS( CEconomiseur ))) ;
      delete   pEco ;
      }
      
   RemoveAll() ;

   char  WDir[_MAX_PATH] ;
   
   // Trouver le repertoire de windows
   GetWindowsDirectory(WDir, sizeof( WDir )) ;
   if ( WDir[ lstrlen(WDir)-1 ] != '\\' )
      lstrcat( WDir, "\\" ) ; 
   // Chercher les fichiers .SCR dans ce repertoire
   ParcoursSCR( WDir ) ;

   // Trouver le repertoire system
   GetSystemDirectory(WDir, sizeof( WDir )) ;
   if ( WDir[ lstrlen(WDir)-1 ] != '\\' )
      lstrcat( WDir, "\\" ) ; 
   // Chercher les fichiers .SCR dans ce repertoire
   ParcoursSCR( WDir ) ;
}

CListeEconomiseurs::~CListeEconomiseurs()
{
   const int Nb   =  GetSize() ;
   
   for ( int i = 0; i < Nb; i++ )
      {
      CEconomiseur   *  pEco  =  (CEconomiseur*)GetAt( i ) ;
      ASSERT( pEco->IsKindOf( RUNTIME_CLASS( CEconomiseur ))) ;
      delete   pEco ;
      }
      
   RemoveAll() ;
}

CEconomiseur*  CListeEconomiseurs::PlusPrioritaire( void )
{
   CEconomiseur   *  pChoisi = 0 ;
      
   const int   Nb = GetSize() ;
   
   if ( Nb )
      {
      pChoisi  =  GetAt(0) ;
      CEconomiseur::PRIORITE  PrioriteMax =  pChoisi->PrioriteCourante() ;
      
      for( int i = 1; i < Nb; i++)
         {
         CEconomiseur*  pEco  =  (CEconomiseur*)GetAt(i) ;
         
         // Comparaison des priorites courantes
         if ( (*pEco) > (*pChoisi) )
            pChoisi  = pEco ;
         }
         
      // Avancement des priorites
      for ( i  =  0; i < Nb; i++)
         {
         CEconomiseur*pEco =  GetAt(i) ;
         ++(*pEco) ;
         }
         
       pChoisi->PrioriteInitiale() ;
      }
      
   return pChoisi ;
}


UINT	CListeEconomiseurs::PrioriteMax( void )
{
	const int   Nb = GetSize() ;
	CEconomiseur::PRIORITE  	Pri	=	PRIORITE_MIN ;
    
	for( int i = 0; i < Nb; i++)
		{
		CEconomiseur*  pEco  =  (CEconomiseur*)GetAt(i) ;
		ASSERT_VALID (pEco ) ;
		if ( pEco->PrioriteCourante() > Pri )	
			Pri	=	pEco->PrioriteCourante() ;
		}
		
	return (UINT)Pri ;
}

void	CListeEconomiseurs::SauveConfiguration()
{
   const int Nb   =  GetSize() ;
   
   for ( int i = 0; i < Nb; i++ )
      {
      CEconomiseur   *  pEco  =  (CEconomiseur*)GetAt( i ) ;
      ASSERT( pEco->IsKindOf( RUNTIME_CLASS( CEconomiseur ))) ;
      pEco->SauveConfiguration() ;
      }
}
