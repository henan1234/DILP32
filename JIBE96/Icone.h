///////////////////////////////////////////////////////////////////////////////
// CIcone : classe generique
///////////////////////////////////////////////////////////////////////////////

#ifndef __ICONE_H__
#define __ICONE_H__

class	CIcone	:	public	CObject
	{
	DECLARE_DYNAMIC( CIcone ) ;

	public :
		CIcone() ;
		virtual	~CIcone() ;

		// Affichage
		virtual	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) = 0 ;

		// Modifiee, oui/non
		BOOL				Modifiee( void ) const { return _Modifiee ; } ;
		virtual	void		Modifiee( BOOL ) ;

		virtual	HRGN		Region( CPoint Decalage ) const =	0 ;

		virtual	UINT		GetMenuID( void ) const ;
		virtual	BOOL		ExecuteCommand( UINT NoCommande ) ;
		virtual	BOOL		ExecuteCommand( void ) ;

		// Archivage
		void	Serialize( CArchive& ar ) ;

		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

	private :
		BOOL	_Modifiee ;

public:
	virtual void Assombri( CDC &, CPoint Pt );
	virtual void AccepteFichiers( HDROP );
	virtual BOOL ConfirmeSuppression( void ) const;
	const CSize& GetTailleFenetre( void ) const { return _TailleFenetre ; } ;
	void TailleFenetre( const CSize & );
	virtual CWnd* OuvreFenetre( CRect & RectFenetre, CWnd* pParent );
	static BOOL Colors64K( void );
	virtual CString GetTip( void );
	virtual BOOL PtInIcon( CPoint PtTest, CPoint PosIcon ) const;
	virtual int Largeur( void ) const;
	virtual int Hauteur( void ) const;
	virtual CRect Rect( void ) const;
	static UINT GetSide( void );
	void Update( BOOL = FALSE );

protected:
	void DerouleFenetre( CWnd *, const CRect & R ) const;
	static CSize GetMainSize( void ) ;
private:
	CSize _TailleFenetre;
	static	CView * _pView;
	} ;
#endif
