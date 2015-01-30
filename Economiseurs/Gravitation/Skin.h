// Skin.h: interface for the CSkin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKIN_H__A2CDFCC1_6794_11D3_A601_00A04B04180E__INCLUDED_)
#define AFX_SKIN_H__A2CDFCC1_6794_11D3_A601_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkin  
{
public:
	CSkin();
	virtual ~CSkin();
	void	SetFile( const char * ) ;
	void	ValeursDefaut() ;

	static int		NbImages()			{ return _NbImages ; }
	static int		ImageComete()		{ return _ImageComete ; }
	static int		NbElementsDecors()	{ return _NbElementsDecors ; }
	static int		CouleurRepere()		{ return _CouleurRepere ; }
	static int		NbCouleursCometes()	{ return _NbCouleursCometes ; }
	static BYTE		CouleursCometes( int i ) { return _CouleursCometes[i] ; }
	static int		NbCouleursEtoiles()	{ return _NbCouleursEtoiles ; }
	static BYTE		CouleursEtoiles( int i ) { return _CouleursEtoiles[i] ; } 

	static BOOL		CreatePalette( CDIBPal * ) ;
	static BOOL		CreatePhasesPlanete( int i, CDIB * ) ;
	static BOOL		CreateExplosion( CDIB * ) ;
	static BOOL		CreateDecors( int i, CDIB * ) ;


	static BYTE		Transparence()		{ return _Transparence ; }

private:
	static CString GetNomFichier( const TCHAR * pNom );
	static BOOL LoadDIB( const TCHAR * pNom, WORD IDResource, CDIB * pDIB );
	static	CString		_SkinFile ;
	static void Controle( int & Val, int Min, int Max );
	static int GetInt( const TCHAR * Val, int Defaut );
	static BOOL ChercheFichier( CString & Fichier ) ;
	
	static int			_NbImages ;
	static int			_CouleurRepere ;
	static int			_ImageComete ;
	static int			_NbElementsDecors ;
	static BYTE			_Transparence ;
	
	static int			_NbCouleursEtoiles ;
	static BYTE			_CouleursEtoiles[ NB_MAX_COULEURS_ETOILES ] ;
	static int			_NbCouleursCometes ;
	static BYTE			_CouleursCometes[ NB_MAX_COULEURS_COMETES ] ;

	// Cometes

};

#endif // !defined(AFX_SKIN_H__A2CDFCC1_6794_11D3_A601_00A04B04180E__INCLUDED_)
