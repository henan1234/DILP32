///////////////////////////////////////////////////////////////////////////////
// CIconeHorloge
//	Derivee de CIconePeriodique
///////////////////////////////////////////////////////////////////////////////
#ifndef _IconeHorloge_H_
#define _IconeHorloge_H_
#include "IconePeriodique.h"

class	CIconeHorloge	:	public	CIconePeriodique
	{ 
	DECLARE_SERIAL( CIconeHorloge ) ;


public:
	virtual BOOL ExecuteCommand( UINT );
	virtual CString GetTip( void );
	virtual BOOL ExecuteCommand( void );
	virtual UINT GetMenuID( void ) const;
	CIconeHorloge();
	virtual void  Update( void );

	virtual	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;
	virtual	HRGN	Region( CPoint Decalage ) const ;
	
	void	Serialize( CArchive & ar ) ;

private:
	UINT _Mode;
	CTime _DerniereHeure;
	} ;

class	CIconeDate :	public	CIconePeriodique
	{ 
	DECLARE_SERIAL( CIconeDate ) ;


public:
	virtual BOOL ExecuteCommand( UINT );
	virtual CString GetTip( void );
	virtual BOOL ExecuteCommand( void );
	virtual UINT GetMenuID( void ) const;
	CIconeDate();
	virtual void  Update( void );

	virtual	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;
	virtual	HRGN	Region( CPoint Decalage ) const ;
	
	void	Serialize( CArchive & ar ) ;

private:
	BOOL _FormatLong;
	CTime _DerniereDate;
	} ;

#endif