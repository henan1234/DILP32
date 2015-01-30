///////////////////////////////////////////////////////////////////////////////
// CRaccourci
//	Classe d'objets raccourcis vers un fichier, un document ou un programme
///////////////////////////////////////////////////////////////////////////////
#ifndef __RACCOURCI_H_
#define __RACCOURCI_H_

class	CRaccourci	:	public CObject
	{
	public :
		CRaccourci() ;
		~CRaccourci() ;
		DECLARE_SERIAL( CRaccourci ) ;
		virtual	void	Serialize( CArchive & ) ;

		///////////////////////////////////////////////////////////////////////
		//	
		///////////////////////////////////////////////////////////////////////
		void	SetText( const CString & ) ;
		void	SetIcone( LPCSTR, WORD ) ;
		void	SetCommande( LPCSTR ) ;

		///////////////////////////////////////////////////////////////////////
		//	Lecture des infos
		///////////////////////////////////////////////////////////////////////
		HICON	GetIcone( void ) ;
		const	CString &	GetText( void ) const { return _Texte ; } ;
		const	CString &	GetCommande( void ) const { return _NomFichier ; } ;
		void	Active( void ) ;
		const	CString &	GetFichierIcone( void ) const { return _FichierIcone ; } ;
		WORD	GetIndiceIcone( void ) const { return _IndiceIcone ; } ;

#ifdef	_DEBUG
		virtual void	AssertValid( void ) const ;
		virtual void	Dump( CDumpContext & ) const ;
#endif
	private :
		CString	_Texte ;
		CString	_FichierIcone ;
		WORD	_IndiceIcone ;
		CString	_NomFichier ;
private:
	CString GetFileType( void ) const;
	HICON _hIcon;
public:
	static void ResoudShortCut( LPSTR );
	static void ResoudShortCut( CString & );
	static BOOL IsDrive( const char * );
	static BOOL IsFolder( const char * );
	void Menu( UINT );
	void ModifMenu( CMenu *, UINT PremiereCommande );
	} ;


/////////////////////////////////////////////////////////////////////////////
// CPropsRaccourci dialog

class CPropsRaccourci : public CDialog
{
// Construction
public:
	int _IndiceIcone;
	CString _NomFichierIcone;
	CPropsRaccourci(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropsRaccourci)
	enum { IDD = IDD_PROPS_RACCOURCI };
	CString	m_Nom;
	CString	m_Commande;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropsRaccourci)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropsRaccourci)
	afx_msg void OnIcone();
	afx_msg void OnParcourir();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
