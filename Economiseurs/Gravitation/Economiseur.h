///////////////////////////////////////////////////////////////////////////////
// ECONOMISEUR.H
//	Interface de la classe CEconomiseur
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <scrnsave.h>
#include <afxmt.h>

#define NB_PRIORITE	5

class	CEconomiseur
	{
	public :
		CEconomiseur( const CString & NomEconomiseur ) ;
		virtual	~CEconomiseur() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Configuration( CPropertySheet * )  ;

		// Animation
		void		UpdateFenetre( CDC &, const CRect & ) ;
		virtual	void Animation( CDC&	Dc ) = 0 ;
		virtual void InitDC( CDC & ) = 0 ;
		virtual void FinDC( CDC & ) = 0 ;

		virtual	void Preferences() ;
		virtual void ValidePreferences() ;

		static	CEconomiseur*	GetEconomiseur() ;

		BOOL		NoircirEcran ;
		static	int	Largeur ;
		static	int	Hauteur ;

		void		EcritPreferences() ;
		void		LitPreferences() ;

		friend	DWORD __stdcall Economisage( LPVOID  ) ;

		virtual	void	OnTimer( UINT ) {} ;

		friend class	CDlgPriorite ;

	protected :
		void	Preference( const char *, CString &, const char * = NULL ) ;
		void	Preference( const char *, DWORD &, const char * = NULL ) ;
		void	Preference( const char *, double &, const char * = NULL ) ;
		void	Preference( const char *, int &, const char * = NULL ) ;

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

		static	CEconomiseur*	_pTheOnlyOne ;

		BOOL _ResolutionChangee;

		int arand( int x );

		DWORD _dwSeed;
public:
		virtual void LoadFile( const char * pFileName );
		virtual void SaveFile( const char * pFileName );
		virtual void Configure( void );
	void Fini( void );
	virtual void CEstParti( HWND hWnd );
	BOOL Apercu( void ) const;
	BOOL UnSur( int x );
	BOOL HautePriorite;
	
	BOOL	VerifDate( void ) ;

	BOOL	RealizePalette( CDC & );
	int Alea( int Min, int Max );
protected:
	CDC & GetDC( void ) const;
	void SetPalette( HPALETTE );
	CBitmap * MemoriseEcran( int Largeur, int Hauteur );

	#define COLOR_MONO		1
	#define	COLOR_16		4
	#define COLOR_256		8
	#define COLOR_64K		16
	#define	COLOR_TRUE_24	24
	#define	COLOR_TRUE_32	32

	BOOL	ChangeResolution( int Largeur, int Hauteur, int NbCouleurs );

	HANDLE _hThread;

	static void EcritFichier( const char * pFileName, UINT IdStrSection, UINT IdsValueName, int Value );
	static void EcritFichier( const char * pFileName, UINT IdStrSection, UINT IdsValueName, double Value );

	static void LitFichier( const char * pFileName, UINT IdStrSection, UINT IdsValueName, int & Value );
	static void LitFichier( const char * pFileName, UINT IdStrSection, UINT IdsValueName, double & Value );
	HPALETTE hPalette ;

private:
	static HANDLE _hThreadFini;
	static BOOL _Fini;
	virtual	void PeintFenetre( CDC & Dc, const CRect& R ) ;
	int		_NoCourant ;
	static CDC DC;
	int		_PrioriteThread ;
	} ;

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
};

/////////////////////////////////////////////////////////////////////////////
