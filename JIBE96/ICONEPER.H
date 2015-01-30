///////////////////////////////////////////////////////////////////////////////
// CIconePeriodique
///////////////////////////////////////////////////////////////////////////////
#ifndef _ICONEPERIODIQUE_H_
#define _ICONEPERIODIQUE_H_

#include "icone.h"

class	CIconePeriodique : public CIcone
	{
	DECLARE_SERIAL( CIconePeriodique ) ;

public:
	virtual void Update( void ) = 0;
	~CIconePeriodique();
	CIconePeriodique();
private:
	static void CALLBACK TimerProc( HWND, UINT, UINT, DWORD );
	static UINT _uiTimer;
	static CObList  _ListeIconesPeriodiques;
	} ;

#endif
