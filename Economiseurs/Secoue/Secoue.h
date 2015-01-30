#pragma once

#include "..\Economiseur generique\economiseur.h"

class	CSecoue : public CEconomiseur
	{
	public :
		CSecoue( const CString & NomEconomiseur, const CString & ValeurEnregistre ) ;
		virtual	~CSecoue() ;

		virtual	void InitSave( HWND	hWnd )  ;
		virtual	void Configuration( CPropertySheet * )  ;

		// Animation
		virtual	void Animation( CDC&	Dc ) ;
		virtual void InitDC( CDC & ) ;
		virtual void FinDC( CDC & ) ;

		virtual	void Preferences() ;
		virtual void ValidePreferences() ;
		virtual	void PeintFenetre( CDC & Dc, const CRect& R) ;
		virtual void OnTimer( UINT IdTimer ) ;

	} ;

