///////////////////////////////////////////////////////////////////////////////
// Protection.h
//	Fonction de protection de mes logiciels
///////////////////////////////////////////////////////////////////////////////
#ifndef __PROTECTION_H__
#define __PROTECTION_H__

#ifdef __cplusplus
extern "C" {
#endif
BOOL	CEstMoi( void ) ;
BOOL	Enregistree( const char *	Logiciel, const char * Valeur ) ;

#ifdef __cplusplus
}
#endif

#endif

