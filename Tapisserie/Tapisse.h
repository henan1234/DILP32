// Tapisserie.h

class	CMonAppli	: public	CWinApp
{
	public :
		virtual	BOOL	InitInstance( ) ;
		static	void	LitChaine( const char * SousClef, const char	*	Rubrique, char	*	Buffer, int 	TailleBuffer ) ;
		static	DWORD	LitEntier( const char * SousClef, const char *	Rubrique, DWORD Defaut ) ;

		static	void	EcritChaine( const char * SousClef, const char	*	Rubrique, const char * Buffer ) ;
		static	void	EcritEntier( const char * SousClef, const char	*	Rubrique, DWORD	Entier ) ;
		static	const	CString		CheminIni ;

		static	BOOL	Enregistree() ;
} ;
