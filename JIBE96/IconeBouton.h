///////////////////////////////////////////////////////////////////////////////
// CIcone : classe generique
///////////////////////////////////////////////////////////////////////////////

#ifndef __ICONEBOUTON_H__
#define __ICONEBOUTON_H__
#include "Raccourci.h"

class	CIconeBouton	:	public	CIcone
	{
	DECLARE_SERIAL( CIconeBouton ) ;

	public :
		CIconeBouton() ;
		virtual	~CIconeBouton() ;

		// Affichage
		virtual	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;

		virtual	UINT		GetMenuID( void ) const ;
		virtual	BOOL		ExecuteCommand( UINT NoCommande ) ;
		virtual	BOOL		ExecuteCommand( void ) ;
		virtual HRGN		Region( CPoint ) const ;

		// Archivage
		void	Serialize( CArchive& ar ) ;

		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

public:
	virtual void AccepteFichiers( HDROP );
	virtual BOOL ConfirmeSuppression( void ) const;
	virtual CRect Rect( void ) const;
	virtual CString GetTip( void );
	
private :
	CRaccourci		_Raccourci ;
} ;
#endif
