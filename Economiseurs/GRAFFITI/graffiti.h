///////////////////////////////////////////////////////////////////////////////
// Graffiti.H
//	Interface de la classe CGraffiti
///////////////////////////////////////////////////////////////////////////////

#ifndef _ECONOMISEUR_H_
#include "..\economiseur generique\economiseur.h"

class	COutil ;
class	CTrajectoire ;

#define	ECRAN		0
#define BLANC		1
#define NOIR		2

class	CGraffiti : public CEconomiseur
	{
	public :
		CGraffiti( const CString & NomEconomiseur, const CString & ValeurEnregistre ) ;
		virtual	~CGraffiti() ;

		virtual	void InitSave( HWND	hWnd )  ;
//		virtual void InitConfig( HWND hWnd ) ;

		virtual	void Animation( CDC&	Dc ) ;
		virtual	void PeintFenetre( CDC & Dc, const CRect& R ) ;
		virtual void InitDC( CDC & ) {} ;
		virtual void FinDC( CDC & ) {} ;

		virtual	BOOL PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) ;

		virtual	void Preferences() ;

	private :
		COutil	*	_pOutil ;
private:
	BOOL _ChangerResolution;
	static DWORD TechniqueFromIndex( int );
	static int IndexFromTechnique( DWORD );
	DWORD _Technique;
	CTrajectoire* ChoisiTrajectoire( void );
	CBitmap* _pOld;
	CDC _MemDC;
	COutil * ChoisiOutil( void );
	CTrajectoire*	_pTrajectoire ;
public:
	int		_Feuille ;
	} ;

#endif
