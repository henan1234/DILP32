///////////////////////////////////////////////////////////////////////////////
// Interface de la classe CPreferences
//	Un seul objet de cette classe sera instancie.
//	La fonction GetPreferences rendra l'adresse de cet objet
///////////////////////////////////////////////////////////////////////////////

#ifndef __PREFERENCES__
#define	__PREFERENCES__

#ifndef HKEY_CURRENT_USER
#include <winreg.h>
#endif

class	CPreferences
	{
	public	:
		CPreferences( const char	*	AppName, HKEY	RootKey	=	HKEY_CURRENT_USER ) ;
		~CPreferences() ;

		void	LitPreference( const char * , CString &,	const char * Defaut	=	"" ) ;
		void	LitPreference( const char * , int&,			const int Defaut	=	0 ) ;
		void	LitPreference( const char * , double&,		const double  Defaut	=	0 ) ;
		void	LitPreference( const char * , DWORD&,		const DWORD Defaut	=	0 ) ;

		void	EcritPreference( const char *, const char * ) ;
		void	EcritPreference( const char *, int ) ;
		void	EcritPreference( const char *, double ) ;
		void	EcritPreference( const char *, DWORD ) ;

	private :
		static	CPreferences	*	_pThePreference ;
		HKEY						_hKeyPreferences ;
		friend	CPreferences*		GetPreferences(void) ;
	} ;

CPreferences *		GetPreferences( void ) ;

#endif
