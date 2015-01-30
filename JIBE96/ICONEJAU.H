///////////////////////////////////////////////////////////////////////////////
// CIconeJauge
///////////////////////////////////////////////////////////////////////////////
#ifndef _ICONEJAUGE_H_
#define _ICONEJAUGE_H_

#include "iconePeriodique.h"

class	CIconeJauge : public CIconePeriodique
	{
	DECLARE_SERIAL( CIconeJauge ) ;

public:
	virtual CWnd* OuvreFenetre( CRect & RectIcone, CWnd * pParent );
	static	CString FormatNumber( double );
	const	UINT & GetPourcentageAlarme( void ) const;
	void	SetPourcentageAlarme( UINT ) ;
	virtual void Update( void ) ;
	~CIconeJauge();
	CIconeJauge();

	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;
	virtual	HRGN		Region( CPoint Decalage ) const ;

	void	Serialize( CArchive & ar ) ;

#ifdef _DEBUG
	virtual	void	AssertValid( void ) const ;
#endif

protected:
	static CString FormatNumber( DWORD );
	virtual CString GetText( UINT Pourcentage );
	virtual	UINT		GetPourcentage( void ) = 0 ;
	virtual	UINT		GetIDBitmap( void ) const = 0 ;
	virtual	COLORREF	GetCouleurBarre( BOOL	Alarme = FALSE ) const = 0 ;	

	void	SetFormatNom( const CString & ) ;
	static UINT ChangeIntervalle( DWORD Valeur, DWORD DepMin, DWORD DepMax, DWORD DstMin, DWORD DstMax );

private:
	BOOL _AlarmeAffichee;
	UINT	_PourcentageAlarme ;
	UINT	_DernierPourcentage ;
	CString	_FormatNom ;
	} ;

#endif
