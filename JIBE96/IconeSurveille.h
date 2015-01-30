////////////////////////////////////////////////////////////////
// CIconeSurveille
// Cette icone surveille un repertoire et averti des qu'il y a
// un changement
////////////////////////////////////////////////////////////////
#ifndef	_ICONSURVEILLE_H_
#define	_ICONSURVEILLE_H_
#include "iconePeriodique.h"

class	CIconeSurveille	:	public	CIconePeriodique
	{
	DECLARE_SERIAL( CIconeSurveille ) ;
	public :
		CIconeSurveille() ;
		~CIconeSurveille() ;

		virtual void	Update( void ) ;
		virtual	void	Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;
		virtual	HRGN	Region( CPoint Decalage ) const ;
		virtual	UINT	GetMenuID( void ) const ;
		virtual CWnd*	OuvreFenetre( CRect & RectFenetre, CWnd* pParent );
		virtual CString GetTip( void );
		
		virtual void	Serialize( CArchive & ) ;
		virtual BOOL ExecuteCommand( UINT NoCommande ) ;
	private :
		CMapStringToOb		_EtatsFichiers ;
		BOOL				_AlarmeEnCours ;
		CString				_Repertoire ;
		BOOL				_Clignote ;
		CStringList			_Evenements ;

private:
	DWORD _Options;
	BOOL _Recursif;
	HANDLE _hThread;
	static DWORD __stdcall ThreadSurveille( LPVOID );
	HANDLE _hFNotif;
	void DepartSurveillance( void );
	void NouveauFichier( const CString &, const WIN32_FIND_DATA & );
	void AjouteEvenement( const CString & );
	BOOL CompareFichier( const char *, const WIN32_FIND_DATA & );
	void SurveilleRepertoire( const char * Repertoire );
public:
	CStringList* Evenements(void);
	} ;


#endif