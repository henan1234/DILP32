///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.H
//	Interface de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////

#ifndef _ECONOMISEUR_H_
#include <afxmt.h>
#include <ddraw.h>

class	CEconomiseur
	{
	public :
		CEconomiseur( const CString & NomEconomiseur, const CString & ValeurEnregistre ) ;
		virtual	~CEconomiseur() ;

		virtual	void InitSave( HWND	hWnd )  ;

		virtual	void Configuration( CPropertySheet * ) ;

		// Animation
		void		UpdateFenetre( CDC &, const CRect & ) ;
		virtual void		Calcul( void ) = 0 ;
		virtual void		Affichage( void ) = 0 ;

		virtual	void Preferences() ;
		virtual void ValidePreferences() ;

		static	CEconomiseur*	GetEconomiseur() ;

		static		BOOL		NoircirEcran ;
		static		int			Largeur ;
		static		int			Hauteur ;

		void		EcritPreferences() ;
		void		LitPreferences() ;

		friend	DWORD __stdcall Economisage( LPVOID  ) ;
		friend	DWORD __stdcall Affichage( LPVOID  ) ;

	protected :
		void	Preference( const char *, CString &, const char * = NULL ) ;
		void	Preference( const char *, DWORD &, const char * = NULL ) ;
		void	Preference( const char *, double &, const char * = NULL ) ;
		void	Preference( const char *, int &, const char * = NULL ) ;

		// Preferences avec saisie automatique
		void	Preference( UINT IdString, int &, int Min, int Max, BOOL bSlider=FALSE ) ;

		void	Etat( const char * Nom, const char *, CString & ) ;
		void	Etat( const char * Nom, const char *, DWORD & ) ;
		void	Etat( const char * Nom, const char *, double & ) ;
		void	Etat( const char * Nom, const char *, int & ) ;
		
		static	HWND	_hWnd ;

		virtual BOOL	ChargeEtat( const char * ) { return FALSE ; } ;
		virtual	BOOL	SauveEtat( const char * ) { return FALSE ; } ;

	private :
		BOOL	_EcriturePreferences ;
		CString	_Nom ;
		CString	_ValeurEnregistre ;

		static	CEconomiseur*	_pTheOnlyOne ;

		BOOL _ResolutionChangee;

		int arand( int x );

		DWORD _dwSeed;
public:
	void Fini( void );
	virtual void CEstParti( HWND hWnd );
	BOOL Apercu( void ) const;
	BOOL UnSur( int x );
	BOOL HautePriorite;
	
	BOOL	ShareWare( void );
	BOOL	VerifDate( void ) ;

	BOOL	RealizePalette(  );
	int Alea( int Min, int Max );
protected:
	virtual void DDErreur( HRESULT ddrval );
	void SetPalette( LPDIRECTDRAWPALETTE );
//	CBitmap * MemoriseEcran( int Largeur, int Hauteur );

	static LPDIRECTDRAW			_lpDD ;
	static LPDIRECTDRAWSURFACE	_lpPrimary ;
	static LPDIRECTDRAWSURFACE	_lpBackBuffer ;
	static LPDIRECTDRAWPALETTE	_lpPalette ;

private:
	void FiniDirectDraw( void );
	virtual void InitDirectDraw( void );

	HANDLE _hThread;
	static HANDLE _hThreadFini;
	static BOOL _Fini;
	int		_NoCourant ;
	} ;

#endif
/////////////////////////////////////////////////////////////////////////////
// CShareWare window

class CShareWare : public CWnd
{
// Construction
public:
	CShareWare();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShareWare)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShareWare();

	// Generated message map functions
protected:
	void OnTimer();
	//{{AFX_MSG(CShareWare)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static CString _Message;
};

/////////////////////////////////////////////////////////////////////////////
