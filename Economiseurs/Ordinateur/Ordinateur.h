///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
#ifndef	_ORDINATEUR_H_
#define	_ORDINATEUR_H_

#include "Case.h"

#define	NB_LIGNES	20
#define	NB_COLONNES	80

class	COrdinateur : public	CEconomiseur
	{
	public :
		COrdinateur(  ) ;
		virtual	~COrdinateur() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual void InitConfig( HWND hWnd ) ;

		virtual	void Animation( CDC&	Dc ) ;
		virtual	void PeintFenetre( CDC & Dc, const CRect& R ) ;

		virtual	BOOL PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) ;

		virtual	void Preferences() ;

	private :
		CString		_LigneCourante ;
		CString		_LigneATraiter ;
		CCase		_Cases[NB_COLONNES][NB_LIGNES] ;	
		CStringList	_Lignes ;
		POSITION	_Pos ;
		int			_IndiceSurLigne	;
		CString		_FichierScript ;
		HFONT		_hFont ;
		int			_LargeurCase ;
		int			_HauteurCase ;
		int			_XCurseur ;
		int			_YCurseur ;
		int			_PauseEnCours ;
		BOOL		_CurseurInverse ;
		CCriticalSection	_Clignotant ;	// Pour eviter la gestion du clignotement pendant le scroll
		HANDLE		_hThreadClignote ;

private:
	BOOL _ClignoteAllume;
	static DWORD _stdcall FctThreadClignote( LPVOID ) ;
	DWORD _Delai;
	DWORD _DernierTps;
	BOOL _ChangeResolution;
	HFONT _hOldFont;
	void ClignoteCaracteres( CDC & );
	BOOL _Clignote;
	COLORREF _CouleurFond;
	COLORREF _CouleurCar;
	CString ProchainMorceau( CDC & );
	void InverseCurseur( CDC & );
	void Scroll( CDC & );
	void AjouteCaractere( CDC &, char );
	void LigneSuivante( CDC & );
public:
	virtual void FinDC( CDC & Dc );
	virtual void InitDC( CDC & Dc );
	} ;

#endif