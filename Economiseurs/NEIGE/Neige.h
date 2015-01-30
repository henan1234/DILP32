///////////////////////////////////////////////////////////////////////////////
// CEcoNeige
///////////////////////////////////////////////////////////////////////////////
#ifndef _ECONEIGE_H_
#define _ECONEIGE_H_
#include "..\..\classes\dibpal.h"
#include "..\..\classes\dibsurface.h"

#ifndef _ECONOMISEUR_H_
#include "..\Economiseur Generique\Economiseur.h"
#endif

#ifndef _FLOCON_H_
#include "flocon.h"
#endif

class	CEcoNeige : public	CEconomiseur
	{
	public	:	
		CEcoNeige() ;
		~CEcoNeige() ;
		
		virtual	void InitSave( HWND	hWnd )  ;
		virtual void InitConfig( HWND hWnd ) ;

		virtual	void Animation( CDC&	Dc )  ;
		virtual	void PeintFenetre( CDC & Dc, const CRect& R ) ;
		virtual	void InitDC( CDC & ) {} ;
		virtual void FinDC( CDC & ) {} ;

		virtual	BOOL PreprocessConfigDlgMessage( HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam ) ;
		virtual	void Preferences() ;

	private :
		CList<CFlocon*, CFlocon*>	_ListeFlocons ;
		CDIBSurface*				_pImageDeFond ;
		CDIBPal*					_pPalette ;

		CRectAffichage				_Affichage ;
		CString						_NomImage ;
		int							_NbMaxFlocons ;
private:
	int _VentMax;
	int _TailleMax;
	} ;

#endif
