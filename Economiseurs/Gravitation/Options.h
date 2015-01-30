// Options.h: interface for the COptions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONS_H__E5550F81_247E_11D3_A5A4_00A04B04180E__INCLUDED_)
#define AFX_OPTIONS_H__E5550F81_247E_11D3_A5A4_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning( disable : 4711 )
#define FLOTTANT double
#include <afxtempl.h>

#include "optionEntier.h"
#include "optionFlottant.h"
#include "optionChaine.h"

class COptions  
{
public:
	virtual ~COptions();

	// Acces aux valeurs, accelerateurs
	static COptionEntier & Modele3D()			{ return _3D ; }
	static COptionEntier & NbMinCorps()			{ return _NbMinCorps ; }
	//static COptionEntier & NbImages()			{ return _NbImages ; }
	static COptionEntier & NbImagesSeconde()	{ return _NbImagesSeconde ; }
	static COptionEntier & NbMaxCorps()			{ return _NbMaxCorps ; }
	static COptionEntier & NbInitCorps()		{ return _NbInitCorps ; }
	static COptionEntier & NbMaxPoussieres()	{ return _NbMaxPoussiere ; }
	static COptionEntier & BruitPoussieres()	{ return _BruitPoussieres ; }
	static COptionEntier & CoeffLiberation()	{ return _CoeffLiberation ; }
	static COptionEntier & DensiteEtoiles()		{ return _DensiteEtoiles ; }
	static COptionEntier & Depart()				{ return _Depart ; }
	//static COptionEntier & Transparence()		{ return _Transparence ; }
	static COptionEntier & ViePoussieres()		{ return _ViePoussieres ; }
	//static COptionEntier & ImageComete()		{ return _ImageComete ; }
	static COptionEntier & CreationComete()		{ return _CreationComete ; }
	//static COptionEntier & NbElementsDecors()	{ return _NbElementsDecors ; }
	static COptionEntier & TaillePoussieres()	{ return _TaillePoussieres ; }
	static COptionEntier & AfficherInfos()		{ return _AfficherInfos ; }
	static COptionEntier & AfficherRepere()		{ return _AfficherRepere ; }
	static COptionEntier & ChangerResolution()	{ return _ChangerResolution ; }
	//static COptionEntier & CouleurRepere()		{ return _CouleurRepere ; }
	static COptionEntier & DecaleElementsDecors() { return _DecaleElementsDecors ; }
	static COptionEntier & ReInitSiPlusDEtoile() { return _ReinitSiPlusDEtoiles ; }

	static COptionFlottant & CoeffMinMax()		{ return _CoeffMinMax ; }
	static COptionFlottant & VentSolaire()		{ return _VentSolaire ; }
	static COptionFlottant & CoeffRayon()		{ return _CoeffRayon ; }
	static COptionFlottant & DeltaVMax()		{ return _DeltaVMax ; }
	static COptionFlottant & CoeffTraveling()	{ return _CoeffTraveling ; }
	static COptionFlottant & ZoomMax()			{ return _ZoomMax ; }
	static COptionFlottant	& G() { return _G  ;}
	static COptionFlottant & TimeMult() { return _TimeMult ; }
	static COptionFlottant & DistMult() { return _DistMult ; }

	//static COptionChaine & NomPalette() { return _NomPalette ; }
	static COptionChaine & FichierInit()	{ return _FichierInit ; }

	//static COptionChaine & NomDecors( int i ) { return _NomsDecors[i] ; }
	//static COptionChaine & NomImage( int i )	{ return _NomsImages[i] ; }
	static COptionFlottant & MasseMax( int i ) { return _MassesMax[i] ; }
	//static COptionChaine & NomExplosion() { return _NomExplosion ; }

	//static COptionEntier &	NbCouleursCometes() { return _NbCouleursCometes ; }
	//static COptionEntier &	CouleursCometes( int i ) { return _CouleursCometes[i] ; }
	//static COptionEntier &	NbCouleursEtoiles()	{ return _NbCouleursEtoiles ; }
	//static COptionEntier &	CouleursEtoiles( int i ) { return _CouleursEtoiles[i] ; }

	static	COptionChaine & SkinFile() { return _SkinFile ; }
	static	COptionEntier & UseSkinFile() { return _UseSkinFile ; }

	// Switch entre les categories de valeurs
	void	ValeursShareware() ;
	void	ValeursApercu() ;
	void	ValeursDefaut() ;

	void	EcritRegistry( const TCHAR * pNom, BOOL bShareware ) ;
	void	LitRegistry( const TCHAR * pNom, BOOL bApercu, BOOL bShareware ) ;
	void	EcritFichier( const TCHAR * pNom, const TCHAR * pFichier, BOOL bShareware ) ;
	void	LitFichier( const TCHAR * pNom, const TCHAR * pFichier, BOOL bApercu, BOOL bShareware ) ;

private:
	COptions();
	friend COptions* CEcoGravitation::GetOptions() ;

	void VerifValeurs( void );
	static	COptionEntier	_3D ;
	static	COptionEntier	_NbMinCorps ;
	//static  COptionEntier	_NbImages ;
	static  COptionEntier	_NbImagesSeconde ;
	static	COptionEntier	_NbMaxPoussiere ;
	static	COptionEntier	_NbInitCorps ;
	static	COptionEntier	_NbMaxCorps ;
	static	COptionEntier	_BruitPoussieres ;
	static	COptionEntier	_CoeffLiberation ;
	static	COptionEntier	_DensiteEtoiles ;
	static	COptionEntier	_Depart ;
	//static	COptionEntier	_Transparence ;
	static	COptionEntier	_ViePoussieres ;
	//static	COptionEntier	_ImageComete ;
	static	COptionEntier	_CreationComete ;
	//static	COptionEntier	_NbElementsDecors ;
	static	COptionEntier	_TaillePoussieres ;
	static	COptionEntier	_AfficherRepere ;
	static	COptionEntier	_ChangerResolution ;
	static	COptionEntier	_AfficherInfos ;
	//static	COptionEntier	_CouleurRepere ;
	static	COptionEntier	_DecaleElementsDecors ;
	static	COptionEntier	_ReinitSiPlusDEtoiles ;

	static	COptionFlottant _VentSolaire ;
	static	COptionFlottant _CoeffRayon ;
	static	COptionFlottant	_DeltaVMax ;
	static	COptionFlottant _CoeffTraveling ;
	static	COptionFlottant _ZoomMax ;
	static	COptionFlottant _G ;
	static	COptionFlottant _DistMult ;
	static	COptionFlottant _TimeMult ;
	static	COptionFlottant _CoeffMinMax ;

	//static	COptionChaine	_NomPalette ;
	static	COptionChaine	_FichierInit ;
	//static	COptionChaine	_NomExplosion ;

	//static	COptionChaine	_NomsDecors[ NB_MAX_DECORS ] ;
	//static	COptionChaine	_NomsImages[ NB_MAX_IMAGES ] ;

	static	COptionFlottant	_MassesMax[ NB_MAX_IMAGES ] ;


	//static	COptionEntier	_NbCouleursEtoiles ;
	//static	COptionEntier	_CouleursEtoiles[ NB_MAX_COULEURS_ETOILES ] ;
	//static	COptionEntier	_NbCouleursCometes ;
	//static	COptionEntier	_CouleursCometes[ NB_MAX_COULEURS_COMETES] ;

	static	COptionChaine	_SkinFile ;
	static	COptionEntier	_UseSkinFile ;
	CArray	<COption*, COption*> _Options ;
};

#endif // !defined(AFX_OPTIONS_H__E5550F81_247E_11D3_A5A4_00A04B04180E__INCLUDED_)
