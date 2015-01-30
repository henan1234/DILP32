///////////////////////////////////////////////////////////////////////////////
// CIconeDisque
///////////////////////////////////////////////////////////////////////////////
#ifndef _ICONEDISQUE_H_
#define _ICONEDISQUE_H_

#include "iconeJauge.h"

class	CIconeDisque : public CIconeJauge
	{
	DECLARE_SERIAL( CIconeDisque ) ;

public:
	void SetNomDisque( const CString & );
	virtual CWnd* OuvreFenetre( CRect &, CWnd * );
	virtual CString GetTip( void );
	~CIconeDisque();
	CIconeDisque();

	void	Serialize( CArchive & ar ) ;
	virtual UINT		GetMenuID( void ) const ;
	virtual	BOOL		ExecuteCommand( UINT NoCommande ) ;
	virtual	BOOL		ExecuteCommand( void ) ;

protected:
	virtual CString GetText( UINT Pourcentage );
	virtual	UINT		GetPourcentage( void ) ;
	virtual	UINT		GetIDBitmap( void ) const  ;
	virtual	COLORREF	GetCouleurBarre( BOOL	Alarme = FALSE ) const ;	

	
private:
	CString	_NomDisque ;
	} ;

#endif
