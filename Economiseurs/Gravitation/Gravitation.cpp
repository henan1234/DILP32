///////////////////////////////////////////////////////////////////////////////
// CEcoGravitation
//	Implementation de l'economiseur Gravitation
// Cet economiseur simule un bout d'espace et les forces de gravites entre
// les differents corps
// 4/4/97 : optimisation : on calcule une fois pour toute l'attraction qu'exerce
//			un corps en stockant Attraction = Masse * G
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <signal.h>
#include "resource.h"
#include "EcoGravitation.h"
#include "options.h"


// Supprime le warning qui annonce qu'une fonction est mise en inline
#pragma warning( disable : 4711 )

#include "..\..\CLASSES\RegistrationKey.h"
#include "..\..\CLASSES\DIB.h"
#include "..\..\CLASSES\DIBSurface.h"

#include "..\Economiseur Generique\RectAffichage.h"
#include "Page1.h"
#include "PagesParametres.h"

#define ABS(x)	(x > 0 ? x : -x)


int			CEcoGravitation::NbCorps ;
DWORD		CEcoGravitation::_DebutSysteme ;
FLOTTANT	CEcoGravitation::DeltaT ;
DWORD		CEcoGravitation::DernierTemps ;
FLOTTANT	CEcoGravitation::_DecalageX ;
FLOTTANT	CEcoGravitation::_DecalageY ;
FLOTTANT	CEcoGravitation::_DecalageVx ;
FLOTTANT	CEcoGravitation::_DecalageVy ;
int			CEcoGravitation::_IndicePlusGros ;
int			CEcoGravitation::_DelaiImages ;
DWORD		CEcoGravitation::_DerniereImage ;
CEcoGravitation::T_POUSSIERE	CEcoGravitation::_Poussieres[ NB_MAX_POUSSIERES ] ;
int			CEcoGravitation::_NbPoussieres	;
FLOTTANT	CEcoGravitation::_MaxZ ;
FLOTTANT	CEcoGravitation::_MinZ ;
int			CEcoGravitation::_NbAffiches ;
CEcoGravitation::T_CORPS		CEcoGravitation::_Corps[NB_MAX_CORPS] ;
CEcoGravitation::T_IMAGE		CEcoGravitation::_Bitmap[NB_MAX_IMAGES] ;
CRectAffichage	CEcoGravitation::_NouveauxRectangles ;
CRectAffichage	CEcoGravitation::_DerniersRectangles ;
CDIBSurface*	CEcoGravitation::pDCIntermediaire ;
FLOTTANT		CEcoGravitation::_ZoomInitial ;
POINTS			CEcoGravitation::_Explosions[100] ;
int				CEcoGravitation::_NbExplosions	=	0 ;
FLOTTANT		CEcoGravitation::_RapportTailleBitmaps = 1.5 ;
int				CEcoGravitation::_NbBoucles = 0 ;

CEcoGravitation::T_ELEMENT_DECOR	CEcoGravitation::_ElementsDecors[NB_MAX_DECORS] ;
int				CEcoGravitation::_MaxHauteurDecor ;
int				CEcoGravitation::_MaxLargeurDecor ;

CSkin*			CEcoGravitation::_pSkin = NULL ;
CString			CEcoGravitation::_DernierEvenement ;

///////////////////////////////////////////////////////////////////////////////
// Important ! Il doit exister un et un seul objet CEcoGravitation
///////////////////////////////////////////////////////////////////////////////
CRegistrationKey	CeciEstMaClefCodee( GRAV_PATH, GRAV_HIDDEN ) ;
CEcoGravitation CeciEstMonEconomiseur ;

CDIB			CEcoGravitation::_Explosion ;


int Steps ;
int Step = 0 ;


///////////////////////////////////////////////////////////////////////////////
// Affiche la jauge de progression pendant l'initialisation du programme
///////////////////////////////////////////////////////////////////////////////
void	JaugeStep()
	{
	if ( CeciEstMonEconomiseur.Apercu())
		return ;

	Step ++ ;

	const int	L	=	GetSystemMetrics( SM_CXSCREEN ) ;
	const int	H	=	GetSystemMetrics( SM_CYSCREEN ) ;
	CDC	Dc ;
	Dc.CreateDC( "display", 0, 0, 0 ) ;

	const int	RL	=	250 ;
	const int	RH	=	75 ;
	CRect	R ;
	R.left	= ( L - RL ) / 2 ;
	R.top   = ( H - RH ) / 2 ;
	R.right	= R.left + RL ;
	R.bottom= R.top + RH ;

	CBrush Fond( GetSysColor( COLOR_3DFACE )) ;
	Dc.FillRect( R, &Fond) ;
	Fond.DeleteObject() ;

	Dc.DrawEdge( R, BDR_RAISEDINNER | BDR_RAISEDOUTER, BF_RECT ) ;

	Dc.SelectStockObject( ANSI_VAR_FONT ) ;
	Dc.SetBkMode( TRANSPARENT ) ;
	
	R.DeflateRect( 4, 4 ) ;
	Dc.DrawEdge( R, BDR_SUNKENINNER | BDR_SUNKENOUTER, BF_RECT ) ;

	R.DeflateRect( 2, 2 ) ;
	Dc.DrawText( "Gravitation initializing...", R, DT_TOP | DT_CENTER | DT_WORDBREAK ) ;

	R.DeflateRect( 4, 4 ) ;

	R.top += 20 ;

	R.right = R.left + R.Width() * Step / (Steps+1) ;
	R.bottom= R.top + 24 ;

	CBitmap	Bitmap ;
	Bitmap.LoadBitmap( IDB_JAUGE ) ;
	Dc.DrawState( R.TopLeft(), R.Size(), &Bitmap, DSS_NORMAL, NULL );
	Bitmap.DeleteObject() ;

	Dc.DrawEdge( R, BDR_RAISEDINNER | BDR_RAISEDOUTER, BF_RECT ) ;

	Dc.DeleteDC() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Error
//	Affiche un message d'erreur et termine le process
///////////////////////////////////////////////////////////////////////////////
void _cdecl Error( const TCHAR * pMessage, ... )
	{
	char Message[2048] ;
    va_list va;
    va_start( va, pMessage );
    wvsprintf( Message, pMessage, va );
    va_end( va );

	strcat( Message, "\nProgram will abort" ) ;

	MessageBeep( MB_ICONHAND ) ;
	MessageBox( 0, Message, "Gravitation: Detected error",
				MB_ICONHAND | MB_OK | MB_SYSTEMMODAL ) ;

	ExitProcess(0) ;
	}

// Juste pour eviter les divide by zero
void _cdecl ErreurFlottant( int )
{
	//Error( "Floating point error" ) ;
}


void _cdecl ErreurAbort( int )
	{
	Error( "Abortion requested" ) ;
	}

void _cdecl ErreurIll( int )
	{
	//Error( "Illegal instruction" ) ;
	}

void _cdecl ErreurInt( int )
	{
	Error( "Interrupt requested" ) ;
	}

void _cdecl ErreurSegV( int )
	{
	//Error( "Illegal storage access" ) ;
	}

void _cdecl ErreurSigTerm( int )
	{
	Error( "Termination request" ) ;
	}


CEcoGravitation::CEcoGravitation (  )
:CEconomiseur( "Gravitation" )
	{
	_DecalageX	=	0 ;
	NbCorps		=	0 ;				// Nombre actuel de corps
	_DecalageY	=	0 ;
	_DecalageVx	=	0 ;
	_DecalageVy	=	0 ;
	_pOptions	=	NULL ;
	}


CEcoGravitation::~CEcoGravitation ()
{
}



///////////////////////////////////////////////////////////////////////////////
// RecherchePlusGros
//	Recherche l'indice du corps le plus massif du systeme, celui sur lequel est
//	fixe la camera
//	Indice stocke dans _IndicePlusGros
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::RecherchePlusGros( void )
{
	_IndicePlusGros	=	0 ;

	for ( register int i = 1; i < NbCorps; i++)
		if ( _Corps[i].Attraction > _Corps[_IndicePlusGros].Attraction )
			_IndicePlusGros	=	i ;
}

///////////////////////////////////////////////////////////////////////////////
// Suppression d'un corps en retassant la fin du tableau
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::SupprimeCorps( int Indice )
{
	memmove( &_Corps[Indice], &_Corps[Indice+1], sizeof( T_CORPS ) * (NbCorps-Indice-1)) ;
	NbCorps -- ;

	RecherchePlusGros() ;
}

// ==================================================================================================
// Generation des corps
// ==================================================================================================
void	CEcoGravitation::GenereCorps( void )
{   
	_DebutSysteme	=	GetCurrentTime() ;

/*	if ( ! Apercu())
		if ( CeciEstMaClefCodee.IsLocked())
			{
			GenereCorpsShareware() ;
			return ;
			}
*/
	if ( COptions::Depart() == 5 )
		{
		// Verifier que le fichier existe
		CFileStatus	Status ;

		if ( ! CFile::GetStatus( COptions::FichierInit(), Status ))
			COptions::Depart().Set( 0 ) ;
		}

	if ( Apercu())
		{
		///////////////////////////////////////////////////////////////////////
		// En mode apercu, on fait le minimum
		///////////////////////////////////////////////////////////////////////
 		NbCorps	=	_pSkin->NbImages() ;
		COptions::Depart().Set( 3 ) ;
		}
	else
		NbCorps	=	COptions::NbInitCorps() ;

	switch( COptions::Depart() )
		{
		case 0 :
			{
			// Position aleatoire, vitesse nulle
			FLOTTANT	Angles[NB_MAX_CORPS] ;
			FLOTTANT	AttractionTotale=0 ;
			FLOTTANT	CentreX = 0 ;
			FLOTTANT	CentreY	= 0 ;
			FLOTTANT	CentreZ	= 0 ;
			GenerePositionsAleatoires( CentreX, CentreY, CentreZ, AttractionTotale, Angles ) ;
			}
			break ;

		case 1 :
			// Orbite circulaire autour du centre de gravite
		case 2 :
			// Orbite circulaire approximative autour du centre de gravite
			{
			FLOTTANT	Angles[NB_MAX_CORPS] ;
			FLOTTANT	AttractionTotale=0 ;
			FLOTTANT	CentreX = 0 ;
			FLOTTANT	CentreY	= 0 ;
			FLOTTANT	CentreZ	= 0 ;
			GenerePositionsAleatoires( CentreX, CentreY, CentreZ, AttractionTotale, Angles ) ;
			GenereVitessesOrbites( CentreX, CentreY, CentreZ, AttractionTotale, Angles ) ;
			}
			break ;

		case 3 :
			// Orbite autour d'un soleil
			GenereCorpsOrbites() ;			
			break ;

		case 4 :
			// Orbite autour d'un soleil, sens de rotation aleatoire
			GenereCorpsOrbites() ;			
			break ;

		case 5 :
			GenereDeFichier() ;
			if ( COptions::Depart() != 5 )
				{
				// Methode de depart changee dans le fichier
				GenereCorps() ;
				return ;
				}
			break ;

		default :
			Error( "Invalid creation method detected: %d, please check configuration",
				COptions::Depart()) ;					
		}

	for ( int i = 0; i < NbCorps; i++)
		if ( _Corps[i].Image == _pSkin->ImageComete() )
			{
			// Coefficient de dispersion des poussieres propre a chaque comete
			_Corps[NbCorps].BruitPoussiere	=	(int)((FLOTTANT)(COptions::BruitPoussieres() *  Alea( 70, 130 )) / 100.0 ) ;
			if ( _Corps[NbCorps].BruitPoussiere < 0 )
				_Corps[NbCorps].BruitPoussiere = 0 ;
			else
				if ( _Corps[NbCorps].BruitPoussiere > 100 )
					_Corps[NbCorps].BruitPoussiere	=	100 ;
			}

	RecherchePlusGros() ;

	_MinZ	=	_Corps[_IndicePlusGros].z ;
	_MaxZ	=	_Corps[_IndicePlusGros].z ;
	PlaceDecors() ;

	_DernierEvenement	=	"Universe creation" ;
}


///////////////////////////////////////////////////////////////////////////////
// Initialisation du screen saver en mode animation
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::InitSave( HWND	hWnd )
	{
	if ( ! Apercu())
		{
		if ( COptions::ChangerResolution() )
			{
			if ( ! ChangeResolution( 1280, 1024, COLOR_256 ))
				if ( ! ChangeResolution( 1152, 864, COLOR_256 ))
					if ( ! ChangeResolution( 1024, 768, COLOR_256 ))
						if ( ! ChangeResolution( 800, 600, COLOR_256 ))
							if ( ! ChangeResolution( 1280, 1023, -1 ))
								if ( ! ChangeResolution( 1152, 864, -1 ))
									if ( ! ChangeResolution( 1024, 768, -1 ))
										ChangeResolution( 800, 600, -1 ) ;
			}
		}
	
	signal( SIGFPE, ErreurFlottant ) ;
	signal( SIGABRT, ErreurAbort ) ;
	signal( SIGILL, ErreurIll ) ;
	signal( SIGINT, ErreurInt ) ;
	signal( SIGSEGV, ErreurSegV ) ;
	signal( SIGTERM, ErreurSigTerm ) ;

    SetErrorMode( SEM_FAILCRITICALERRORS /*| SEM_NOGPFAULTERRORBOX*/ ) ;

	NoircirEcran = TRUE ;
	CEconomiseur::InitSave( hWnd ) ;


	DefaultParameters() ;
	LitPreferences() ;

	_pSkin	=	new CSkin ;

	if ( COptions::Depart() == 5 )
		LoadFile( COptions::FichierInit() ) ;

	if ( COptions::UseSkinFile())
		_pSkin->SetFile( COptions::SkinFile()) ;
	else
		_pSkin->ValeursDefaut() ;

	// Calcul du delai entre deux images en millisecondes
	_DelaiImages	=	1000 / COptions::NbImagesSeconde() ;
	_DerniereImage	=	0 ;

	_ZoomInitial	=	COptions::DistMult() ;
	_NbExplosions	=	0 ;

	Steps	=	_pSkin->NbImages() + _pSkin->NbElementsDecors() + 4;
	
	ChargeBitmaps() ;

	JaugeStep() ;
	GenereCorps() ;

	JaugeStep() ;
	_pSkin->CreatePalette( &Palette ) ;

	SetPalette( (HPALETTE)Palette.m_hObject ) ;
	
	///////////////////////////////////////////////////////////////////////////
	// DC Intermediaire pour affichage sans clignotement
	/////////////////////////////////////////////////////////////////////////
	pDCIntermediaire	=	new CDIBSurface ;
	if ( ! pDCIntermediaire->Create( Largeur, Hauteur, &Palette ))
		Error( "Not enough memory to create double buffer. Please free memory by closing running applications" );
	
	EffaceRectangle( CRect( 0, 0, Largeur, Hauteur )) ;
	
	_DerniersRectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;
	_NouveauxRectangles.Espace( CRect( 0, 0, Largeur, Hauteur-1 )) ;
	
	DernierTemps		=	GetCurrentTime() ;
	
	RegisterDocTypes() ;
	JaugeStep() ;
	}


// ============================================================================
// Collision
// Determine si deux corps sont entres en collision
// ENTREES :	@ des deux corps
// RETOUR :		VRAI s'il y a collision
// ============================================================================
inline BOOL CEcoGravitation::Collision( const T_CORPS & Corps1, const T_CORPS & Corps2 )
{
	register const FLOTTANT SommeRayon		=	(_Bitmap[Corps1.Image].Rayon + _Bitmap[Corps2.Image].Rayon)	* COptions::CoeffRayon() ;
	
	return SommeRayon*COptions::DistMult()> CalculeDistance( Corps1, Corps2 ) ;
}


///////////////////////////////////////////////////////////////////////////
// Decalage des elements de decors ( donne une illusion de profondeur
//	quand la camera se deplace )
//	ENTREES :	Decalage X et Y de la camera
///////////////////////////////////////////////////////////////////////////
void CEcoGravitation::DecaleElementsDecors(FLOTTANT dx, FLOTTANT dy)
{
	if ( COptions::DecaleElementsDecors() == 0 )
		return ;

	const FLOTTANT RATIO	=	COptions::TimeMult()*COptions::DistMult() * COptions::DecaleElementsDecors() ;
	const FLOTTANT DX		=	-dx / RATIO ;
	const FLOTTANT DY		=	-dy / RATIO ;

	for ( register int i = 0; i < _pSkin->NbElementsDecors(); i++)
		{
		_ElementsDecors[i].x += DX ;
		_ElementsDecors[i].y += DY ;

		const int	L	=_ElementsDecors[i].Dib.GetWidth() ;
		const int	H	=_ElementsDecors[i].Dib.GetHeight() ;

		if ( _ElementsDecors[i].x > Largeur && DX > 0 )
			_ElementsDecors[i].x -= Largeur + _MaxLargeurDecor ;
		else
			if ( _ElementsDecors[i].x + L < 0 && DX < 0 )
				_ElementsDecors[i].x += Largeur + _MaxLargeurDecor ;

		if ( _ElementsDecors[i].y > Hauteur && DY > 0)
			_ElementsDecors[i].y -= Hauteur + _MaxHauteurDecor ;
		else
			if ( _ElementsDecors[i].y + H < 0 && DY < 0 )
				_ElementsDecors[i].y += Hauteur + _MaxHauteurDecor ;
		}
}


// ============================================================================
// Agglomeration
// Deux corps se rencontrent et se fondent pour en creer un plus gros
// ENTREES :	Indice des deux corps
// SORTIES :	rien
// ============================================================================
void	CEcoGravitation::Agglomeration( int	Indice1, int Indice2 )
{
	if ( _Corps[Indice1].Attraction < _Corps[Indice2].Attraction )
		{
		// Indice1 doit etre le plus gros des deux corps
		const int	i =	Indice1 ;
		Indice1 =	Indice2 ;
		Indice2 =	i ;
	    }
	    
	// Combiner les deux corps
	_Corps[Indice1].vx		=	( (_Corps[Indice1].vx*_Corps[Indice1].Attraction)
								 +(_Corps[Indice2].vx*_Corps[Indice2].Attraction)
								)
								/
								( _Corps[Indice1].Attraction+_Corps[Indice2].Attraction) ;
	_Corps[Indice1].vy		=	( (_Corps[Indice1].vy*_Corps[Indice1].Attraction)
								 +(_Corps[Indice2].vy*_Corps[Indice2].Attraction)
								)
								/
								( _Corps[Indice1].Attraction+_Corps[Indice2].Attraction) ;
	
	_Corps[Indice1].vz		=	( (_Corps[Indice1].vz*_Corps[Indice1].Attraction)
									 +(_Corps[Indice2].vz*_Corps[Indice2].Attraction)
									)
									/
									( _Corps[Indice1].Attraction+_Corps[Indice2].Attraction) ;

	_Corps[Indice1].Attraction	+=	_Corps[Indice2].Attraction ;
	_Corps[Indice1].Image	=	(int)ImagePourMasse(_Corps[Indice1].Attraction ) ;
	_Corps[Indice1].Phase	=	0 ;
	_Corps[Indice1].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
	if ( UnSur( 2 ))
		_Corps[Indice1].Rotation	=	- _Corps[Indice1].Rotation ;

	AjouteExplosion( (int)_Corps[Indice1].x, (int)_Corps[Indice1].y ) ;
	
	// Ce nouveau corps est peut etre le plus gros de tous
	if ( _Corps[Indice1].Attraction > _Corps[_IndicePlusGros].Attraction )
		RecherchePlusGros() ;

	// Supprimer le deuxieme corps
	SupprimeCorps( Indice2 ) ;

	_DernierEvenement	=	"Two planets collided and merged" ;
}

// ============================================================================
// Eclatement
// Deux corps se rencontrent et s'eparpillent en petits bouts
// ENTREES :	Indice des deux corps
// SORTIES :	rien
// ============================================================================
void	CEcoGravitation::Eclatement( int	Indice1, int Indice2 )
{
	// Nombre de fragments
	const int NbFragments	=	Alea( 6, 20 ) ;
	
	// La masse des fragments est une fraction de la somme totale des deux corps
	const FLOTTANT	Attraction	=	_Corps[Indice2].Attraction / NbFragments  ;
	const int		Image	=	ImagePourMasse( Attraction ) ;
	const FLOTTANT	Rayon	=	_Bitmap[Image].Rayon ;

	///////////////////////////////////////////////////////////////////////////
	// Position et vitesse moyenne des fragments
	///////////////////////////////////////////////////////////////////////////
	const FLOTTANT vx	=	((_Corps[Indice1].vx*_Corps[Indice1].Attraction) + (_Corps[Indice2].vy*_Corps[Indice2].Attraction))
						/ (_Corps[Indice1].Attraction + _Corps[Indice2].Attraction) ;
	const FLOTTANT vy	=	((_Corps[Indice1].vy*_Corps[Indice1].Attraction) + (_Corps[Indice2].vy*_Corps[Indice2].Attraction))
						/ (_Corps[Indice1].Attraction + _Corps[Indice2].Attraction) ;
	const FLOTTANT vz	=	((_Corps[Indice1].vz*_Corps[Indice1].Attraction) + (_Corps[Indice2].vz*_Corps[Indice2].Attraction))
						/ (_Corps[Indice1].Attraction + _Corps[Indice2].Attraction) ;
	const FLOTTANT x	=	(_Corps[Indice1].x+_Corps[Indice2].x)/2 ;
	const FLOTTANT y	=	(_Corps[Indice1].y+_Corps[Indice2].y)/2 ;
	const FLOTTANT z	=	(_Corps[Indice1].z+_Corps[Indice2].z)/2 ;
	
	///////////////////////////////////////////////////////////////////////////
	// On doit commencer par enlever celui dont l'indice est le plus haut, ca
	// evite des calculs pour enlever l'autre
	///////////////////////////////////////////////////////////////////////////
	if ( Indice2 < Indice1 )
		{
		const int ind = Indice2 ;
		Indice2 =Indice1 ;
		Indice1 = ind ;
		}
	
	AjouteExplosion( (int)_Corps[Indice1].x, (int)_Corps[Indice1].y ) ;

	// Suppression des deux corps eclates
	SupprimeCorps( Indice2 ) ;
	SupprimeCorps( Indice1 ) ;	

	// creation des Fragments
	// Choix d'une vitesse
	const FLOTTANT Vitesse		=	COptions::Modele3D() ?
									sqrt( vx*vx + vy*vy + vz*vz ) :
									sqrt( vx*vx + vy*vy ) ;

	const FLOTTANT Distance		=	_Bitmap[Image].Rayon * 4 * COptions::DistMult() ;
				
	for ( register int i = 0; (i < NbFragments) && (NbCorps < COptions::NbMaxCorps()); i++ )
		{
		// Choix d'un angle
		const FLOTTANT AngleFragment	=	AngleAleatoire() ;
		const FLOTTANT	Vit				=	Vitesse * 100.0 / Alea( 90, 110 ) ;
		
		// Ajoute le corps a la liste
		const FLOTTANT	Cos	=	cos( AngleFragment ) ;
		const FLOTTANT	Sin	=	sin( AngleFragment ) ;
		_Corps[NbCorps].vx	=	vx + Vit * Sin ;
		_Corps[NbCorps].vy	=	vy + Vit * Cos ;

		_Corps[NbCorps].x	=	x	+	Distance * Sin ;
		_Corps[NbCorps].y	=	y	+	Distance * Cos ;

		_Corps[NbCorps].vz	=	vz + Vit * Cos ;
		_Corps[NbCorps].z	=	z	+	Distance * Cos ;

		_Corps[NbCorps].Attraction=	Attraction ;
		_Corps[NbCorps].Image=	(int)Image ;
		_Corps[NbCorps].Phase=	0 ;
		_Corps[NbCorps].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
		if ( UnSur( 2 ))
			_Corps[NbCorps].Rotation	=	- _Corps[NbCorps].Rotation ;

		NbCorps++ ;
		}

	RecherchePlusGros() ;

	///////////////////////////////////////////////////////////////////////////
	// En prime, creation de quelques poussieres
	///////////////////////////////////////////////////////////////////////////
	if ( _NbPoussieres >= COptions::NbMaxPoussieres() -1 )
		return ;

	int Px, Py ;
	UniversToPixel( x, y, z, &Px, &Py ) ;
	if (  (Px < 0 && vx < 0 ) || ( Px > Largeur && vx > 0 ) ||
		  (Py < 0 && vy < 0 ) || ( Py > Hauteur && vy > 0 ) )
		  return ;

	const int NbPouss	=	Alea( 5, 50 ) ;

	for ( i = 0; (i < NbPouss) && ( _NbPoussieres < COptions::NbMaxPoussieres()); i++)
		{
		// Ajoute le corps a la liste
		const FLOTTANT	Vit =	Vitesse * 100.0 / Alea( 100-COptions::BruitPoussieres(), 
														100+COptions::BruitPoussieres() ) ;
		// Choix d'un angle
		const FLOTTANT AngleFragment	=	AngleAleatoire() ;
		const FLOTTANT	Cos	=	cos( AngleFragment ) ;
		const FLOTTANT	Sin	=	sin( AngleFragment ) ;
	
		_Poussieres[_NbPoussieres].x	=	x ;
		_Poussieres[_NbPoussieres].y	=	y ;

		_Poussieres[_NbPoussieres].vx	=	vx + Vit * Sin ;
		_Poussieres[_NbPoussieres].vy	=	vy + Vit * Cos ;

		_Poussieres[_NbPoussieres].Couleur	=	PALETTEINDEX( Alea(1, 255)) ; // PALETTEINDEX( CouleursComete[ Alea( 0, NB_COULEURS_COMETE-1)]);
		_Poussieres[_NbPoussieres].Vie		=	Alea( (int)(COptions::ViePoussieres()* 500.0), 
													  (int)(COptions::ViePoussieres()*1000.0) ) * 1000  ;
		_Poussieres[_NbPoussieres].Taille	=	Alea( 1, COptions::TaillePoussieres() ) ;

		_NbPoussieres ++ ;
		}

	_DernierEvenement	= "Two planets collided and exploded" ;
}

// ============================================================================
// Rencontre
// Gere la rencontre de deux corps
// Si les deux masses sont tres differentes, le plus gros absorbe le plus petit
// sinon si les vitesses sont tres differentes, les deux eclatent
// ENTREES :	indice des deux corps
// ============================================================================
void	CEcoGravitation::Rencontre( int	Indice1, int Indice2 )
{
	if ( Indice1 < 0 || Indice1 >= NbCorps )
		Error( "Mauvais indice1 %d dans Rencontre", Indice1 ) ;

	if ( Indice2 < 0 || Indice2 >= NbCorps )
		Error( "Mauvais indice2 %d dans Rencontre", Indice2 ) ;

	int		ImageMin ;
	int		ImageMax ;
	
	// De toutes facons, si on a deja trop de corps a gerer, on les agglomere
	if ( NbCorps > COptions::NbMaxCorps()-5)
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}

	// Si les deux corps sont deja petits, on les agglomere
	if ( _Corps[Indice1].Image <= IMAGE_PETITE_PLANETE &&
		 _Corps[Indice2].Image <= IMAGE_PETITE_PLANETE )
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}
		 	
	if ( _Corps[Indice1].Attraction > _Corps[Indice2].Attraction )
		{
		ImageMax	=	_Corps[Indice1].Image ;
		ImageMin	=	_Corps[Indice2].Image ;
		}
	else
		{
		ImageMax	=	_Corps[Indice2].Image ;
		ImageMin	=	_Corps[Indice1].Image ;
		}

	// Si les masses sont tres differentes, le plus gros absorbe le plus petit			
	if ( ImageMax > (ImageMin + 1) )
		{
		Agglomeration( Indice1, Indice2 ) ;
		return ;
		}
		
	// Les corps sont a peu pres semblables, ce qui se passe depend de la
	// vitesse a laquelle ils se rentrent dedans
		
	// Calculer la difference des vitesses
	const FLOTTANT 
	DeltaV	=	COptions::Modele3D() ?
				sqrt( (_Corps[Indice1].vx-_Corps[Indice2].vx)*(_Corps[Indice1].vx-_Corps[Indice2].vx)
					  +(_Corps[Indice1].vy-_Corps[Indice2].vy)*(_Corps[Indice1].vy-_Corps[Indice2].vy)
					  +(_Corps[Indice1].vz-_Corps[Indice2].vz)*(_Corps[Indice1].vz-_Corps[Indice2].vz))
					  :
				sqrt( (_Corps[Indice1].vx-_Corps[Indice2].vx)*(_Corps[Indice1].vx-_Corps[Indice2].vx)
					  +(_Corps[Indice1].vy-_Corps[Indice2].vy)*(_Corps[Indice1].vy-_Corps[Indice2].vy) );

		
	if ( (DeltaV/**COptions::TimeMult()*/) > COptions::DeltaVMax() )
		Eclatement( Indice1, Indice2 ) ;
	else
		Agglomeration( Indice1, Indice2 ) ;
}

// ============================================================================
// CalculeAcceleration
// Calcule les forces d'attraction entre tous les corps
// ============================================================================
void	CEcoGravitation::CalculAccelerations( void )
	{
	for ( register int i = 0; i < NbCorps; i++)
		{
		for ( register int j = i + 1; j < NbCorps; j++ )
			{
			// Les deux corps entrent-ils en collision ?
			if ( Collision( _Corps[i], _Corps[j]) )
				Rencontre( i, j ) ;
			else
				Accelere( &_Corps[i], &_Corps[j] ) ;
			}
		}
	}

// ============================================================================
// Recale l'origine sur le corps le plus massif
// Pour que ce soit plus joli, on decale pas tout en une fois
// ============================================================================
void	CEcoGravitation::Recentre( void )
{
	const FLOTTANT	Dist	=	CalculeDistance( _Corps[_IndicePlusGros] ) / COptions::DistMult() ;
	_DecalageX	=	_Corps[_IndicePlusGros].x * COptions::CoeffTraveling() ;
	_DecalageY	=	_Corps[_IndicePlusGros].y * COptions::CoeffTraveling() ;
	_DecalageVx	=	_Corps[_IndicePlusGros].vx * COptions::CoeffTraveling() ;
	_DecalageVy	=	_Corps[_IndicePlusGros].vy * COptions::CoeffTraveling() ;
}

// ============================================================================
// C'est d'ici que part l'animation
// ============================================================================
void CEcoGravitation::Animation( CDC&	Dc ) 
	{
	// Pour garder une vitesse constante quelle que soit le temps mis pour les calculs
	const DWORD TempsCourant	=	GetCurrentTime ();
	DeltaT			=	(TempsCourant-DernierTemps) * COptions::TimeMult() ;
	DernierTemps	=	TempsCourant ;
	
		
	// Calcul des interactions qu'exercent les corps les uns sur les autres
	CalculAccelerations() ;

	// Deplace les corps	
	if ( COptions::Modele3D() ) // On sort  le test de la boucle !
		{
		_MinZ	=	_Corps[_IndicePlusGros].z ;
		_MaxZ	=	_MinZ ;

		for ( register i = 0; i < NbCorps; i++)
			{
			_Corps[i].x	+=	(_Corps[i].vx * DeltaT) ;
			_Corps[i].y	+=	(_Corps[i].vy * DeltaT)  ;
			_Corps[i].z +=	(_Corps[i].vz * DeltaT)  ;
			}
		}
	else
		{
		// Deplacements en 2D
		for ( register i = 0; i < NbCorps; i++)
			{
			_Corps[i].x	+=	(_Corps[i].vx * DeltaT) ;
			_Corps[i].y	+=	(_Corps[i].vy * DeltaT)  ;
			}
		}


	AvancerPoussieres( DeltaT ) ;

	_NbBoucles ++ ;

	// Est-il temps de s'occuper de l'affichage ?
	if ( TempsCourant >= _DerniereImage + _DelaiImages )
		{
		//Recentre() ;
		CalculZoom() ;
		CalculeMinEtMaxZ() ;

		// Generation aleatoire de comete
		if ( _pSkin->ImageComete() != -1 )
			if ( UnSur( COptions::CreationComete() ))
					GenereUneComete() ;

		EffacerTousLesCorps() ;

		if ( ! Apercu())
			AfficherDecors() ;

		AfficherTousLesCorps() ;
		AfficherPoussieres() ;
		AfficheExplosions() ;

		if ( COptions::AfficherInfos() && ! Apercu())
			AfficheInfos() ;	

		_NbExplosions	=	0 ;

		// Transferer a l'ecran les nouvelles images et les effacements
		_DerniersRectangles +=	_NouveauxRectangles ;
		_DerniersRectangles.BitBlt( Dc.m_hDC, pDCIntermediaire->GetHDC()) ;

		_DerniersRectangles	=	_NouveauxRectangles ;
		_NouveauxRectangles.Vide() ;

		_DerniereImage	=	TempsCourant ;
		_NbBoucles		=	0 ;

		// Regenerer tous les corps si leur nombre est devenu trop petit
		if ( NbCorps < COptions::NbMinCorps())
			{
			InvalidateRect( _hWnd, NULL, TRUE ) ;
			GenereCorps() ;
			_DernierEvenement = "Universe recreated because minimum planet number was reached" ;
			}
		else
		if ( COptions::ReInitSiPlusDEtoile() && _Corps[_IndicePlusGros].Image < (_pSkin->NbImages()-1 ))
			{
			InvalidateRect( _hWnd, NULL, TRUE ) ;
			GenereCorps() ;
			_DernierEvenement = "Universe recreated because no more star existed" ;
			}
		}
}

///////////////////////////////////////////////////////////////////////////////	
// PeintFenetre
//	Peint la fenetre dans son etat initial
///////////////////////////////////////////////////////////////////////////////	
void	CEcoGravitation::PeintFenetre( CDC & , const CRect& R)
{
	EffaceRectangle(R) ;
	_DerniersRectangles += R ;
}

///////////////////////////////////////////////////////////////////////////////	
// Preferences
// Initialisation des preferences en mode Shareware
///////////////////////////////////////////////////////////////////////////////	
void CEcoGravitation::PreferencesShareWare()
	{
	GetOptions()->ValeursShareware() ;
	}


///////////////////////////////////////////////////////////////////////////////
// ParametresApercu
//	Parametres speciaux pour le mode Apercu
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::ParametresApercu()
	{
	GetOptions()->ValeursApercu() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Ecriture ou lecture des preferences
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::Preferences()
	{
	CEconomiseur::Preferences() ;
	CRegistrationKey*	pKey = CRegistrationKey::GetKey() ;

	CString RegistryKey = "Software\\Lucien PILLONI\\Economiseurs d'écrans\\" 
						+ NomEconomiseur() ;

	if ( _EcriturePreferences )
		// Ecriture des preferences
		GetOptions()->EcritRegistry( RegistryKey, pKey->IsLocked() ) ;
	else
		{
		DefaultParameters() ;
		if ( Apercu())
			ParametresApercu() ;
		
		GetOptions()->LitRegistry( RegistryKey, Apercu(), pKey->IsLocked() ) ;
//		if ( pKey->IsLocked())
//			PreferencesShareWare() ;
//
//		if ( COptions::Depart() == 5 )
//				LoadFile( COptions::FichierInit() ) ;
		}

	Preference( "Rapport tailles bitmaps", _RapportTailleBitmaps ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Fait bouger les grains de poussieres
// ENTREE : delai depuis le dernier calcul
///////////////////////////////////////////////////////////////////////////////
inline void	CEcoGravitation::AvancerPoussieres( FLOTTANT Delai )
{
	int x, y ;
	const FLOTTANT	DureeSecondes	=	Delai / 1000.0 / COptions::TimeMult() ;

	for ( register int i = 0; i < _NbPoussieres; i++)
		{
		UniversToPixel( _Poussieres[i].x, _Poussieres[i].y, 0, &x, &y ) ;

		_Poussieres[i].Vie -=DureeSecondes ;

		if ( _Poussieres[i].Vie <= 0 || x < 0 || y < 0 || x > Largeur || y > Hauteur )
			{
			// Suppression de la poussiere
			memcpy( &_Poussieres[i], &_Poussieres[i+1], sizeof( _Poussieres[i] ) * (_NbPoussieres-i-1)) ;
			_NbPoussieres -- ;
			i-- ;
			}
		else
			{
			_Poussieres[i].x	+= (_Poussieres[i].vx * Delai) ;
			_Poussieres[i].y	+= (_Poussieres[i].vy * Delai) ;
			}
		}
}



///////////////////////////////////////////////////////////////////////////////
// Validation des preferences
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::ValidePreferences()
{
	CEconomiseur::ValidePreferences() ;

	// Trier les masses par ordre croissant
	for ( register int i = 0; i < _pSkin->NbImages()-1; i++)
		for ( register int j = i; j < _pSkin->NbImages()-1; j++ )
			{
			if ( COptions::MasseMax(j) > COptions::MasseMax(j+1))
				{
				FLOTTANT s = COptions::MasseMax(j) ;
				COptions::MasseMax(j).Set( COptions::MasseMax(j+1)) ;
				COptions::MasseMax(j+1).Set( s ) ;
				}
			}
}



///////////////////////////////////////////////////////////////////////////////
// Generation aleatoire d'une comete
///////////////////////////////////////////////////////////////////////////////
inline void CEcoGravitation::GenereUneComete( void )
{
	if ( NbCorps >= COptions::NbMaxCorps()-1 )
		return ;

	const FLOTTANT	Distance	=	Alea( max(Largeur, Hauteur)/2, max( Largeur, Hauteur)) * COptions::DistMult() ;
	const FLOTTANT	Angle		=	AngleAleatoire() ;
	const FLOTTANT	Vitesse		=	VitesseOrbiteCirculaire( Distance, _Corps[_IndicePlusGros].Attraction ) ;

	// Pour ne pas obtenir un orbite circulaire, on diminue un peu la vitesse
	const FLOTTANT	VitesseReelle	=	Vitesse * (FLOTTANT)Alea( 10, 60 ) / 100.0 ;
	
	_Corps[NbCorps].vx	=	VitesseReelle * sin( Angle + PI/2 ) + _Corps[_IndicePlusGros].vx ;
	_Corps[NbCorps].vy	=	VitesseReelle * cos( Angle + PI/2 ) + _Corps[_IndicePlusGros].vy ;
	_Corps[NbCorps].vz	=	_Corps[_IndicePlusGros].vz ;

	_Corps[NbCorps].x	=	_Corps[_IndicePlusGros].x	+	Distance * sin( Angle ) ;
	_Corps[NbCorps].y	=	_Corps[_IndicePlusGros].y	+	Distance * cos( Angle ) ;
	_Corps[NbCorps].z	=	_Corps[_IndicePlusGros].z ;

	_Corps[NbCorps].Attraction	=	COptions::MasseMax( _pSkin->ImageComete())  * COptions::G() ;
	_Corps[NbCorps].Image		=	_pSkin->ImageComete() ;
	_Corps[NbCorps].Phase		=	0 ;

	// Coefficient de dispersion des poussieres propre a chaque comete
	_Corps[NbCorps].BruitPoussiere	=	(int)((FLOTTANT)(COptions::BruitPoussieres() *  Alea( 70, 130 )) / 100.0 ) ;
	if ( _Corps[NbCorps].BruitPoussiere < 0 )
		_Corps[NbCorps].BruitPoussiere = 0 ;
	else
		if ( _Corps[NbCorps].BruitPoussiere > 100 )
			_Corps[NbCorps].BruitPoussiere	=	100 ;

	NbCorps++ ;

	_DernierEvenement	=	"A comet was randomly generated" ;
}

///////////////////////////////////////////////////////////////////////////////
// Choix d'un angle aleatoire ( exprime en radian 0..2*PI)
///////////////////////////////////////////////////////////////////////////////
FLOTTANT CEcoGravitation::AngleAleatoire( void )
{
	return (FLOTTANT)Alea( 0, (int)(PI*20000.0) ) / 10000.0 ;
}


///////////////////////////////////////////////////////////////////////////////
// Construction de la fenetre de configuration
///////////////////////////////////////////////////////////////////////////////
void	CEcoGravitation::Configuration( CPropertySheet * pPropSheet )
	{
	pPropSheet->AddPage( new CPage1 ) ;
	pPropSheet->AddPage( new CPagesParametres ) ;
	
	CString Titre ;
	Titre.LoadString( IDS_TITRE_SETTINGS ) ;
	pPropSheet->SetTitle( Titre ) ;

	CEconomiseur::Configuration( pPropSheet ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Calcule la vitesse d'orbite circulaire autour d'un corps dont on donne la
// masse en fonction de la distance
// formule :
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
//			v	=	sqrt( GM/d )
///////////////////////////////////////////////////////////////////////////////
FLOTTANT CEcoGravitation::VitesseOrbiteCirculaire( const FLOTTANT & Distance, const FLOTTANT & Attraction )
{
	return sqrt( Attraction / Distance ) ;
}

///////////////////////////////////////////////////////////////////////////////
// LostInSpace !
// Retourne VRAI si on peut considerer le corps comme perdu dans l'espace :
//	S'il est toujours a l'ecran, on le garde
//	Sinon on calcule sa vitesse de liberation du corps le plus gros
///////////////////////////////////////////////////////////////////////////////
inline BOOL CEcoGravitation::LostInSpace( const T_CORPS & Corps )
{
	int x, y ;
	
	UniversToPixel( Corps.x, Corps.y, Corps.z, &x, &y ) ;
	
	///////////////////////////////////////////////////////////////////////////
	// Si le corps est visible a l'ecran, on le garde de toutes facons
	///////////////////////////////////////////////////////////////////////////
	if ( x > 0 && x < Largeur )
		return FALSE ;

	if ( y > 0 && y < Hauteur )
		return FALSE ;

	if ( x > Largeur && Corps.vx < 0 )
		// Le corps revient vers l'ecran
		return FALSE ;

	if ( x < 0 && Corps.vx > 0)
		return FALSE ;

	if ( y > Hauteur && Corps.vy < 0 )
		// Le corps revient vers l'ecran
		return FALSE ;

	if ( y < 0 && Corps.vy > 0)
		return FALSE ;

	// Calcule la distance au corps le + gros
	const FLOTTANT		Distance	=	CalculeDistance( Corps ) / COptions::DistMult() ;
	const int	DistanceMax			=	2 * (Largeur + Hauteur ) ;

	if ( Distance > DistanceMax )
		{
		_DernierEvenement	=	"A planet was lost because it was too far" ;
		return TRUE ;
		}

	// Controle la vitesse de liberation
	const FLOTTANT	Vx		=	Corps.vx - _Corps[_IndicePlusGros].vx ;
	const FLOTTANT	Vy		=	Corps.vy - _Corps[_IndicePlusGros].vy ;
	const FLOTTANT	Vz		=	Corps.vz - _Corps[_IndicePlusGros].vz ;

	// Vitesse relative du corps par rapport au corps central
	const FLOTTANT	V		=	COptions::Modele3D() ?
								sqrt( (Vx*Vx) + (Vy*Vy) + (Vz*Vz) ) :
								sqrt( (Vx*Vx) + (Vy*Vy) ) ;

	if ( V > ( CalculeVitesseLiberation( Corps ) * COptions::CoeffLiberation() / 100.0 ))
		{
		_DernierEvenement	=	"A planet escaped from the gravity field" ;
		return TRUE ;
		}
	else
		return FALSE ;

}

// ============================================================================
// Accelere
// Calcule l'acceleration gravitationnelle reciproque qui s'exerce entre deux
// corps suivant la formule : F	=	GMm/d2  =>	acceleration = F/m = GM/d2
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
// ENTREES	:	Les deux corps
// SORTIES	:	Les deux corps avec leurs vitesse modifiees
// ============================================================================
inline void	CEcoGravitation::Accelere( T_CORPS	*	pCorps1, T_CORPS * pCorps2 )
{
	// ================================================== Calcul de la distance
	const FLOTTANT DistanceX		=   (FLOTTANT)(pCorps2->x - pCorps1->x)  ;
	const FLOTTANT DistanceY		=   (FLOTTANT)(pCorps2->y - pCorps1->y)  ;
	const FLOTTANT DistanceZ		=   (FLOTTANT)(pCorps2->z - pCorps1->z)  ;

	const FLOTTANT Distance			=	COptions::Modele3D() ?
		sqrt( (DistanceX * DistanceX ) + ( DistanceY * DistanceY ) + (DistanceZ * DistanceZ) ) :
		sqrt( (DistanceX * DistanceX ) + ( DistanceY * DistanceY )  )	;

	const FLOTTANT DistanceCube		=	Distance * Distance * Distance ;

	if ( DistanceCube	!= 0 )
		{
		pCorps1->vx	+=	pCorps2->Attraction * (DistanceX / DistanceCube * DeltaT) ;
		pCorps2->vx	-=	pCorps1->Attraction * (DistanceX / DistanceCube * DeltaT) ;
		
		pCorps1->vy	+=	pCorps2->Attraction * (DistanceY / DistanceCube * DeltaT) ;
		pCorps2->vy	-=	pCorps1->Attraction * (DistanceY / DistanceCube * DeltaT) ;
	
		if ( COptions::Modele3D() )
			{
			pCorps1->vz	+=	pCorps2->Attraction * (DistanceZ / DistanceCube * DeltaT) ;
			pCorps2->vz	-=	pCorps1->Attraction * (DistanceZ / DistanceCube * DeltaT) ;
			}
		}
}

// ============================================================================
// CalculeVitesseLiberation
// Calcule la vitesse de liberation necessaire pour que le corps donne puisse
//	s'echapper du corps central
// Comme toutes les fonctions utilisant une equation de gravite, elle n'utilise
// pas CoeffDistance qui sert uniquement a l'affichage
// la formule :
//			ve	=	sqrt( 2GM/d )
// ============================================================================
inline FLOTTANT CEcoGravitation::CalculeVitesseLiberation( const T_CORPS & Corps )
{
	const FLOTTANT	Distance	=	CalculeDistance( Corps ) ;
	return sqrt( 2.0 * _Corps[_IndicePlusGros].Attraction / Distance ) ;	
}



// ============================================================================
// Genere tous les corps en orbite autour d'un soleil central
// ============================================================================
void CEcoGravitation::GenereCorpsOrbites()
{
	// Un gros corps au centre, les autres en orbite autour
	_Corps[0].x			=	0 ;
	_Corps[0].y			=	0 ;
	_Corps[0].z			=	0 ;
	_Corps[0].vx		=	0 ;
	_Corps[0].vy		=	0 ;
	_Corps[0].vz		=	0 ;
	_Corps[0].Attraction=	COptions::MasseMax( _pSkin->NbImages()-1) * COptions::G() ;
	_Corps[0].Image		=	_pSkin->NbImages() - 1 ;
	_Corps[0].Phase		=0 ;
	_Corps[0].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
	if ( UnSur( 2 ))
		_Corps[0].Rotation	=	- _Corps[0].Rotation ;

	GenereSatellites(	0, NbCorps-1, _pSkin->NbImages()-2,
						COptions::DistMult()*0.01*Largeur,
						COptions::DistMult()*Largeur/2.0 ) ;
}

// ============================================================================
// GenereSatellites
//	Genere des satellites autour du corps donne. Appelle recursivement
// ============================================================================
void CEcoGravitation::GenereSatellites( int Indice, int NbSatellites, int ImageMax, FLOTTANT DistanceMin, FLOTTANT DistanceMax )
	{
	for ( int i = Indice+1; i <= Indice+NbSatellites; i++ )
		{
		const FLOTTANT Distance	=	(FLOTTANT)Alea( 0, 10000) * (DistanceMax-DistanceMin) / 10000.0 + DistanceMin ;
		const FLOTTANT Angle	=	AngleAleatoire() ;
		
		const FLOTTANT Vitesse	=	VitesseOrbiteCirculaire( Distance, _Corps[Indice].Attraction ) ;

		// Tourne a droite ou a gauche aleatoirement
		FLOTTANT EcartAngle	;

		if ( COptions::Depart() == 3  )
			EcartAngle	=	-PI/2 ;
		else
			EcartAngle	=	UnSur(2) ? PI/2 : -PI/2 ;

		_Corps[i].vx		=	Vitesse* sin( Angle + EcartAngle ) + _Corps[Indice].vx ;
		_Corps[i].vy		=	Vitesse* cos( Angle + EcartAngle ) + _Corps[Indice].vy ;
		_Corps[i].vz		=	0 ;

		_Corps[i].x			=	_Corps[Indice].x + Distance*sin( Angle ) ;
		_Corps[i].y			=	_Corps[Indice].y + Distance*cos( Angle ) ;
		_Corps[i].z			=	Alea( -1, 1 ) ;

		_Corps[i].Image		=	(int)Alea( 0, ImageMax ) ;
		_Corps[i].Attraction=	COptions::MasseMax(_Corps[i].Image) * COptions::G() ;
		_Corps[i].Phase		=	0 ;
		_Corps[i].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
		if ( UnSur( 2 ))
			_Corps[i].Rotation	=	- _Corps[i].Rotation ;

		if ( _Corps[i].Image > 3 && (i < NbSatellites-4) && UnSur( 10 ))
			{
			// Creer des satellites autour de ce corps
			const int	NbSatellites	=	Alea( 1, 4 ) ;

			GenereSatellites( i, NbSatellites, ImageMax-3, DistanceMin/10, DistanceMax/10 ) ;

			i += NbSatellites ;
			}
		}
	}


///////////////////////////////////////////////////////////////////////////////
// AjouteExplosion
// Ajoute une explosion a la liste.
// ENTREES :	Coordonnees x et y ( univers )
// SORTIES :	rien
// REMARQUE :
//	On stocke les coordonnees ECRAN pour etre certain que l'explosion va
//	s'afficher a l'endroit ou on a vu les corps se rencontrer, meme si le
//	repere change d'ici au prochain affichage
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AjouteExplosion( int x , int y )
{
	if ( _NbExplosions >= sizeof(_Explosions)/sizeof(_Explosions[0]))
		return ;

	int Px, Py ;
	UniversToPixel( x, y, 0, &Px, &Py ) ;

	_Explosions[_NbExplosions].x	=	(short)Px ;
	_Explosions[_NbExplosions].y	=	(short)Py ;

	_NbExplosions ++ ;
}

void CEcoGravitation::FinDC( CDC & )
	{
	}


///////////////////////////////////////////////////////////////////////////////
// Placer les elements de decors
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::PlaceDecors( void )
{
	if ( Apercu())
		return ;

	for ( int i = 0; i < NB_MAX_DECORS; i++)
		{
		const int	TailleX	=	_ElementsDecors[i].Dib.GetWidth() ;
		const int	TailleY	=	_ElementsDecors[i].Dib.GetHeight() ;

		BOOL Chevauche ;

		/*if ( i == 0 )
			{
			// Le premier element du decor est toujours mon copyright
			_ElementsDecors[i].x	=	Largeur - TailleX ;
			_ElementsDecors[i].y	=	Hauteur - TailleY  ;
			}
		else*/
			{
			int NbEssais = 0 ;
			do
				{
				_ElementsDecors[i].x	=	Alea( 0, Largeur - TailleX ) ;
				_ElementsDecors[i].y		=	Alea( 0, Hauteur - TailleY ) ;
				
				Chevauche	=	FALSE ;
				for ( int j = 0; j < i; j++)
					{
					RECT R, R1, R2 ;
					SetRect( &R1, (int)_ElementsDecors[i].x, (int)_ElementsDecors[i].y,
								  (int)_ElementsDecors[i].x+TailleX, 
								  (int)_ElementsDecors[i].y+TailleY ) ;
					SetRect( &R2, (int)_ElementsDecors[j].x, (int)_ElementsDecors[j].y,
								  (int)_ElementsDecors[j].x+_ElementsDecors[j].Dib.GetWidth(), 
								  (int)_ElementsDecors[j].y+_ElementsDecors[j].Dib.GetHeight() ) ;

					if ( IntersectRect( &R, &R1, &R2 ))
						{
						Chevauche	=	TRUE ;
						break ;
						}
					}
				NbEssais ++ ;
				}
			while ( Chevauche && (NbEssais < 1000)) ;
			}
		}
}

void CEcoGravitation::CalculZoom()
{
	FLOTTANT	NouveauCoeff ;

	if ( COptions::ZoomMax() == 0 )
		NouveauCoeff = COptions::DistMult() ;
	else
		{
		const int	BORD	= 10 ;
		
			{
			FLOTTANT	X = 0 ;
			FLOTTANT	Y = 0 ;
			//FLOTTANT	MasseTotale = 0 ;
			FLOTTANT	MaxX	=	0 ;
			FLOTTANT	MaxY	=	0 ;
			FLOTTANT	MinX	=	0 ;
			FLOTTANT	MinY	=	0 ;
			
			if ( _IndicePlusGros < 0 ||
				_IndicePlusGros >= NbCorps )
				RecherchePlusGros() ;
			
			for ( int i = 0; i < NbCorps; i++)
				{
				///////////////////////////////////////////////////////////////////////
				// Calcul du centre de gravite
				///////////////////////////////////////////////////////////////////////
				//X	+=	_Corps[i].x * _Corps[i].Attraction ;
				//Y	+=	_Corps[i].y * _Corps[i].Attraction ;
				
				//MasseTotale	+=	_Corps[i].Attraction ;
				
				///////////////////////////////////////////////////////////////////////
				// Calcul de l'espace occupe
				///////////////////////////////////////////////////////////////////////
				if ( _Corps[i].x > MaxX )
					MaxX	=	_Corps[i].x ;
				
				if ( _Corps[i].y > MaxY )
					MaxY	=	_Corps[i].y ;
				
				if ( _Corps[i].x	< MinX )
					MinX	=	_Corps[i].x ;
				
				if ( _Corps[i].y < MinY )
					MinY	=	_Corps[i].y ;
				}
			
			// Camera centree sur le corp le plus gros
			//X	/= MasseTotale ;
			//Y	/= MasseTotale ;
			X	=	_Corps[_IndicePlusGros].x ;
			Y	=	_Corps[_IndicePlusGros].y ;
			
			int	iMaxX, iMaxY ;
			UniversToPixel( MaxX, MaxY, 0, &iMaxX, &iMaxY ) ;
			int	iMinX, iMinY ;
			UniversToPixel( MinX, MinY, 0, &iMinX, &iMinY ) ;
			
			if ( (iMinX < BORD ) || (iMinY < BORD ) 
				|| (iMaxX > (Largeur-BORD)) || (iMaxY > (Hauteur-BORD) ))
				{
				NouveauCoeff	=	((MaxX-MinX) + (MaxY-MinY)) * 2.0  / Largeur ;
				
				if ( NouveauCoeff > _ZoomInitial * COptions::ZoomMax() )
					NouveauCoeff	=	_ZoomInitial * COptions::ZoomMax() ;
				
				if ( NouveauCoeff < _ZoomInitial )
					NouveauCoeff	=	_ZoomInitial ;
				
				// Moyenne ponderee pour eviter les trops grands ecarts de zoom
				const FLOTTANT	PONDERATION_ZOOM	=	100.0 ;
				NouveauCoeff	=	((COptions::DistMult()*PONDERATION_ZOOM)+NouveauCoeff)/(PONDERATION_ZOOM + 1.0)  ;
				}
			else
				NouveauCoeff	=	COptions::DistMult() * 0.999999999 ;
			
			// Pour garder des queues de cometes avec une allure constante
			COptions::VentSolaire().Set( COptions::VentSolaire() * COptions::DistMult() / NouveauCoeff ) ;
			
			COptions::DistMult().Set( NouveauCoeff ) ;
			}
		}

	Recentre() ;

	for ( register int i = 0; i < NbCorps; i++)
		if ( LostInSpace( _Corps[i] ))
			SupprimeCorps( i ) ;
		else
			{
			_Corps[i].vx	-= _DecalageVx ;
			_Corps[i].vy	-= _DecalageVy ;

			_Corps[i].x	-=	_DecalageX ;
			_Corps[i].y	-=	_DecalageY ;
			}

	DecaleElementsDecors( _DecalageX, _DecalageY ) ;

	for ( i = 0; i < _NbPoussieres; i++ )
		{
		_Poussieres[i].x -= _DecalageX ;
		_Poussieres[i].y -= _DecalageY ;

		_Poussieres[i].vx-= _DecalageVx ;
		_Poussieres[i].vy-= _DecalageVy ;
		}
/*
	FLOTTANT DecalagePixelX =	(_DecalageX / (CoeffDistance*5.0)) ;
	FLOTTANT DecalagePixelY =	(_DecalageY / (CoeffDistance*5.0)) ;

	for ( i = 1; i < NB_ELEMENTS_DECOR; i++)
		{
		_ElementsDecors[i].x += DecalagePixelX ;
		_ElementsDecors[i].y += DecalagePixelY ;

		const int	RLargeur	=	_ElementsDecors[i].pDib->GetWidth() ;
		const int	RHauteur	=	_ElementsDecors[i].pDib->GetHeight() ;

		if ( _ElementsDecors[i].x > Largeur && DecalagePixelX > 0  )
			_ElementsDecors[i].x	=	0 ;
		else
			if ( (int)(_ElementsDecors[i].x + RLargeur) < 0 && DecalagePixelX < 0 )
				{
				_ElementsDecors[i].x	=	Largeur ;
				}

		if ( _ElementsDecors[i].x > Hauteur && DecalagePixelY > 0 )
			{
			_ElementsDecors[i].y		=	- RHauteur ;
			}
		else
			if ( (int)(_ElementsDecors[i].x + RHauteur) < 0 && DecalagePixelY < 0 )
				{
				_ElementsDecors[i].y	=	Hauteur ;
				}
		}
*/
}

// ============================================================================
// Efface un corps
//
// ============================================================================
void	CEcoGravitation::EffacerTousLesCorps()
{
	const	int	NbRects	=	_DerniersRectangles.NbRectangles() ;

	for ( register int i = 0; i < NbRects; i++)
		EffaceRectangle( _DerniersRectangles.Rectangle( i ) ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Efface un rectangle
// Apres avoir remis du noir, on couvre la surface avec des etoiles aleatoires
// de densite constante
///////////////////////////////////////////////////////////////////////////////
inline void	CEcoGravitation::EffaceRectangle( const CRect & R )
	{
	// Noir
	pDCIntermediaire->FillBits( R.left, R.top, R.Width(), R.Height(), PALETTEINDEX( _pSkin->Transparence() ) ) ;

	// Champs d'etoile dans le fond
	AfficheEtoiles( pDCIntermediaire, R ) ;
	}


///////////////////////////////////////////////////////////////////////////////
// met tous les parametres a leurs valeurs par defaut
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::DefaultParameters()
	{
	GetOptions()->ValeursDefaut() ;
	}

///////////////////////////////////////////////////////////////////////////////
//	GenerePositionsAleatoires
//	Genere une position aleatoire pour chaque corps
//	On en profite pour calculer le centre de gravite, l'"attraction totale"
//	et l'angle vectoriel de chaque corp
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::GenerePositionsAleatoires(FLOTTANT & CentreX, FLOTTANT & CentreY, FLOTTANT & CentreZ, FLOTTANT & AttractionTotale, FLOTTANT Angles[] )
{
	AttractionTotale	=	0 ;

	for ( register int i = 0; i  < NbCorps; i++ )
		{
		if ( Apercu())
			_Corps[i].Image	=	(int)((int)i%(_pSkin->NbImages()-1)+1) ;
		else
			_Corps[i].Image	=	(int)Alea( 0, _pSkin->NbImages() - 1 ) ;

		_Corps[i].Attraction	=	COptions::MasseMax( _Corps[i].Image ) * COptions::G() ;
		_Corps[i].Phase	=	0 ;

		// Angles et distances
		const FLOTTANT Distances	=	Alea( 0, Largeur ) *COptions::DistMult() ;
		Angles[i]		=	AngleAleatoire() ;

		_Corps[i].x		=	Distances * sin( Angles[i] ) ;
		_Corps[i].y		=	Distances * cos( Angles[i] ) ;

		if ( COptions::Modele3D() )
			_Corps[i].z		=	Distances * cos( Angles[i] )  ;
		else
			_Corps[i].z		=	0 ;

		_Corps[i].vx	=	0 ;
		_Corps[i].vy	=	0 ;
		_Corps[i].vz	=	0 ;
		
		CentreX += (_Corps[i].x * _Corps[i].Attraction) ;
		CentreY += (_Corps[i].y * _Corps[i].Attraction) ;
		CentreZ += (_Corps[i].z * _Corps[i].Attraction) ;
		AttractionTotale	+=	_Corps[i].Attraction ;

		_Corps[i].Rotation	=	(FLOTTANT)Alea( 7, 14 ) / 10 ;
		if ( UnSur( 2 ))
			_Corps[i].Rotation	=	- _Corps[i].Rotation ;
		}

	CentreX /= AttractionTotale ;
	CentreY /= AttractionTotale ;
	CentreZ /= AttractionTotale ;
}

///////////////////////////////////////////////////////////////////////////////
// GenereVitessesOrbites
// Calcule les vecteurs vitesses de chaque corps pour le mettre en orbite
// autour du centre de gravite
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::GenereVitessesOrbites(FLOTTANT CentreX, FLOTTANT CentreY, FLOTTANT CentreZ, FLOTTANT AttractionTotale, FLOTTANT Angles [ ])
{
	for ( int i = 0; i < NbCorps; i++ )
		{
		const FLOTTANT Distance	=	sqrt( (_Corps[i].x-CentreX)*(_Corps[i].x-CentreX)
										+ (_Corps[i].y-CentreY)*(_Corps[i].y-CentreY)
										+ (_Corps[i].z-CentreZ)*(_Corps[i].z-CentreZ)) ;

		const FLOTTANT Vitesse	=	VitesseOrbiteCirculaire( Distance, AttractionTotale ) ;
		const FLOTTANT VitesseReelle=	COptions::Depart() == 1 ? 
													   Vitesse/2 
													 : Vitesse * (FLOTTANT)Alea( 10, 120 ) / 100.0 ;

		// Tourne a droite ou a gauche aleatoirement
		const FLOTTANT EcartAngle	=	UnSur(2) ? PI/2 : -PI/2 ;

		_Corps[i].vx		=	VitesseReelle * sin( Angles[i] + EcartAngle ) ;
		_Corps[i].vy		=	VitesseReelle * cos( Angles[i] + EcartAngle ) ;
		_Corps[i].vz		=	VitesseReelle * cos( Angles[i] + EcartAngle ) ;
		}
}



void CEcoGravitation::RegisterDocTypes()
{
	// Icone
	char	Path[MAX_PATH] ;
	GetModuleFileName( hMainInstance, Path, sizeof( Path )) ;
	
	{
	const char *	GRAV_PARAM	=	"Grav.Params" ;
	const char *	GRAV_DESCRIPTION = "Gravitation SCR parameters" ;

	// HKEY_CLASSES_ROOT\.Gravitation=Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, ".Gravitation", REG_SZ, GRAV_PARAM, strlen( GRAV_PARAM ) + 1 ) ;

	// HKEY_CLASSES_ROOT\Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, GRAV_PARAM, REG_SZ, GRAV_DESCRIPTION, strlen( GRAV_DESCRIPTION ) + 1 ) ;


	
	CString Chaine ;
	Chaine.Format( "%s,0", Path ) ;
	RegSetValue( HKEY_CLASSES_ROOT, "Grav.Params\\DefaultIcon", REG_SZ, Chaine.GetBuffer( 1 ), Chaine.GetLength()+1 ) ;
	}

	{
	const char *	UNIV_PARAM	=	"Univ.Params" ;
	const char *	UNIV_DESCRIPTION = "Gravitation SCR universe" ;

	// HKEY_CLASSES_ROOT\.Gravitation=Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, ".Universe", REG_SZ, UNIV_PARAM, strlen( UNIV_PARAM ) + 1 ) ;

	// HKEY_CLASSES_ROOT\Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, UNIV_PARAM, REG_SZ, UNIV_DESCRIPTION, strlen( UNIV_DESCRIPTION ) + 1 ) ;


	// Icone
	char	Path[MAX_PATH] ;
	GetModuleFileName( hMainInstance, Path, sizeof( Path )) ;

	CString Chaine ;
	Chaine.Format( "%s,0", Path ) ;
	RegSetValue( HKEY_CLASSES_ROOT, "Univ.Params\\DefaultIcon", REG_SZ, Chaine.GetBuffer( 1 ), Chaine.GetLength()+1 ) ;
	}

	{
	const char *	UNIV_PARAM	=	"Grav.Skin" ;
	const char *	UNIV_DESCRIPTION = "Gravitation SCR skin file" ;

	// HKEY_CLASSES_ROOT\.Gravitation=Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, ".GravSkin", REG_SZ, UNIV_PARAM, strlen( UNIV_PARAM ) + 1 ) ;

	// HKEY_CLASSES_ROOT\Grav.Params
	RegSetValue( HKEY_CLASSES_ROOT, UNIV_PARAM, REG_SZ, UNIV_DESCRIPTION, strlen( UNIV_DESCRIPTION ) + 1 ) ;


	// Icone
	char	Path[MAX_PATH] ;
	GetModuleFileName( hMainInstance, Path, sizeof( Path )) ;

	CString Chaine ;
	Chaine.Format( "%s,0", Path ) ;
	RegSetValue( HKEY_CLASSES_ROOT, "Grav.Skin\\DefaultIcon", REG_SZ, Chaine.GetBuffer( 1 ), Chaine.GetLength()+1 ) ;
	}


}

void CEcoGravitation::CalculeMinEtMaxZ()
{
	FLOTTANT	MinZ	=	_Corps[_IndicePlusGros].z ;
	FLOTTANT	MaxZ	=	_Corps[_IndicePlusGros].z ;

	_NbAffiches	=	0 ;

	int x, y; 
	for ( register int i = 0; i < NbCorps; i++)
		{
		// Ne prendre le corps en compte que s'il est affiche
		UniversToPixel( _Corps[i].x, _Corps[i].y, _Corps[i].z, &x, &y ) ;		
				
		if ( x >= 0 && x <= Largeur && y >=0 && y <= Hauteur)
			{
			_NbAffiches	++ ;

			if ( _Corps[i].z > MaxZ )
				MaxZ	=	_Corps[i].z ;

			if ( _Corps[i].z < MinZ)
				MinZ	=	_Corps[i].z ;
			}
		}

	const FLOTTANT	Ecart	=	(MaxZ - MinZ) / 2.0 ;
	
	///////////////////////////////////////////////////////////////////////////
	// Calcul des nouveaux min et max avec ponderation pour eviter que les
	// tailles bougent trop
	///////////////////////////////////////////////////////////////////////////
	_MaxZ	=	(COptions::CoeffMinMax()*_MaxZ + _Corps[_IndicePlusGros].z + Ecart) / (COptions::CoeffMinMax()+1.0) ;
	_MinZ	=	(COptions::CoeffMinMax()*_MinZ + _Corps[_IndicePlusGros].z - Ecart) / (COptions::CoeffMinMax()+1.0) ;

	///////////////////////////////////////////////////////////////////////////
	// Evitons les problemes qui pourraient nous arriver avec un intervalle
	// trop petit
	///////////////////////////////////////////////////////////////////////////
	if ( _MaxZ - _MinZ < 500 )
		{
		_MaxZ += 250 ;
		_MinZ -= 250 ;
		}
}

void CEcoGravitation::AfficherDecors()
{
	for ( register int i = 0; i < _pSkin->NbElementsDecors(); i++)
		{
		CRect R ;
		R.SetRect( (int)_ElementsDecors[i].x, (int)_ElementsDecors[i].y,
				   (int)(_ElementsDecors[i].x + _ElementsDecors[i].Dib.GetWidth()),
				   (int)(_ElementsDecors[i].y + _ElementsDecors[i].Dib.GetHeight())) ;

		int DecalageX, DecalageY ;
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

		// Affichage si la planete est a l'ecran
		if (! R.IsRectEmpty())
			{
			_NouveauxRectangles += R ;
			_ElementsDecors[i].Dib.CopyBits( pDCIntermediaire, &R,
											  (int)(R.left - _ElementsDecors[i].x), 
											  (int)(R.top - _ElementsDecors[i].y) ) ;
			}
		}

	static	CRect R ;
	static	char *	pCopyright	=	"Gravitation (c) Lucien PILLONI 1999" ;
	static	const int Longueur	=	strlen( pCopyright ) ;

	CDC	* pDc	=	pDCIntermediaire->GetDC() ;
	pDc->SetBkMode( TRANSPARENT ) ;
	pDc->SetTextColor( RGB( 255,255, 255)) ;
	pDc->SelectStockObject( ANSI_VAR_FONT ) ;

	if ( R.IsRectEmpty())
		pDc->DrawText( pCopyright, Longueur, R, DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_TOP ) ;

	R.OffsetRect( Largeur - R.right, Hauteur - R.bottom ) ;
	pDc->DrawText( pCopyright, Longueur, R, DT_SINGLELINE | DT_LEFT | DT_TOP ) ;
	_NouveauxRectangles += R ;
	}

void CEcoGravitation::GenereCorpsShareware()
{
	GetOptions()->ValeursShareware() ;

	// Corps 0 : etoile centrale
	_Corps[0].Attraction	=	COptions::MasseMax( 7 ) * COptions::G() ;
	_Corps[0].Image			=	(int)ImagePourMasse(_Corps[0].Attraction ) ;
	_Corps[0].x				=	0 ;
	_Corps[0].y				=	0 ;
	_Corps[0].z				=	0 ;
	_Corps[0].vx			=	0 ;
	_Corps[0].vy			=	0 ;
	_Corps[0].vz			=	0 ;
	_Corps[0].Rotation		=	0.5 ;

	//	Corps 1 : terre en orbite autour de l'etoile centrale
	_Corps[1].Attraction	=	COptions::MasseMax( 5 )  * COptions::G() ;
	_Corps[1].Image			=	(int)ImagePourMasse(_Corps[1].Attraction ) ;
	_Corps[1].Phase			=	0 ;
	_Corps[1].Rotation		=	1 ;
	MetEnOrbiteAutour( _Corps[1], _Corps[0], 18000 ) ;


	//	Corps 2 : jupiter en orbite autour de l'etoile centrale
	_Corps[2].Attraction	=	(COptions::MasseMax( 6 )-1) * COptions::G() ;
	_Corps[2].Image			=	ImagePourMasse(_Corps[2].Attraction ) ;
	_Corps[2].Phase			=	0 ;
	_Corps[2].Rotation		=	-0.5 ;
	MetEnOrbiteAutour( _Corps[2], _Corps[0], 30000 ) ;

	// Corps 3 : 
	_Corps[3].Attraction	=	COptions::MasseMax( 2 ) * COptions::G() ;
	_Corps[3].Image	=	ImagePourMasse(_Corps[3].Attraction ) ;
	_Corps[3].Phase			=	0 ;
	_Corps[3].Rotation		=	2;
	MetEnOrbiteAutour( _Corps[3], _Corps[0], 5000 ) ;

	// Corps 4 
	_Corps[4].Attraction	=	COptions::MasseMax( 3 ) * COptions::G() ;
	_Corps[4].Image	=	ImagePourMasse(_Corps[4].Attraction ) ;
	_Corps[4].Phase			=	0 ;
	_Corps[4].Rotation		=	2;
	MetEnOrbiteAutour( _Corps[4], _Corps[0], 25000 ) ;


	// Corps 5
	_Corps[5].Attraction	=	COptions::MasseMax( 0 ) * COptions::G() ;
	_Corps[5].Image	=	ImagePourMasse(_Corps[5].Attraction ) ;
	_Corps[5].Phase			=	0 ;
	_Corps[5].Rotation		=	0.5 ;
	MetEnOrbiteAutour( _Corps[5], _Corps[2], 4000 ) ;


	//	Corps 6
	_Corps[6].Attraction	=	COptions::MasseMax( 0 ) * COptions::G() ;
	_Corps[6].Image	=	ImagePourMasse(_Corps[6].Attraction ) ;
	_Corps[6].Phase			=	0 ;
	_Corps[6].Rotation		=	1.5 ;
	MetEnOrbiteAutour( _Corps[6], _Corps[2], 2000 ) ;

	
	for( int i = 7; i < 50; i++)
		{
		_Corps[i].Attraction	=	COptions::MasseMax( 0 ) * COptions::G() ;
		_Corps[i].Image	=	ImagePourMasse(_Corps[i].Attraction ) ;
		_Corps[i].Phase			=	0 ;
		_Corps[i].Rotation		=	0.5 ;
		MetEnOrbiteAutour( _Corps[i], _Corps[0], 35000 + Alea( 0, 800 )) ;
		}
	NbCorps	=	50 ;
	RecherchePlusGros() ;
}

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::MetEnOrbiteAutour(T_CORPS & Corps,  const T_CORPS & Mere, FLOTTANT Distance )
{
	FLOTTANT	Vitesse	=	VitesseOrbiteCirculaire( Distance, Mere.Attraction ) ;
	// Calcul de la position et de la vitesse du satellite
	FLOTTANT	Angle = AngleAleatoire() ;
	Corps.vx		=	Vitesse* sin( Angle + PI/2) + Mere.vx ;
	Corps.vy		=	Vitesse* cos( Angle + PI/2) + Mere.vy ;
	Corps.vz		=	Mere.vz ;

	Corps.x			=	Mere.x + Distance*sin( Angle ) ;
	Corps.y			=	Mere.y + Distance*cos( Angle ) ;
	Corps.z			=	Mere.z ;
}




int ChangeEchelle( int Valeur, int VSMin, int VSMax, int VDMin, int VDMax )
	{
	FLOTTANT Val = Valeur - VSMin ;
	Val	*= (VDMax - VDMin ) ;
	Val	/= (VSMax - VSMin) ;

	return (int)(Val + VDMin ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// RemplirTableauDImages
//	Rempli le tableau des images. Chaque element correspond a une phase de la
// rotation de la planete
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::RemplirTableauDImages( T_IMAGE * pImage, CDIB & ToutesLesPhases )
{
	const int Hauteur	=	ToutesLesPhases.GetHeight() ;
	const int Largeur	=	ToutesLesPhases.GetWidth() ;

	pImage->NbPhases	=	Largeur / Hauteur ;
	
	if ( COptions::Modele3D() )
		{
		const int TailleMin	=	(int)(Hauteur / 2.0) ;
		const int TailleMax	=	(int)(Hauteur) ; 
		pImage->NbTailles	=	TailleMax - TailleMin + 1 ;

		pImage->Images		=	new CDIB*[pImage->NbTailles] ;

		for ( int t = 0; t < pImage->NbTailles; t ++)
			{
			int Taille = ChangeEchelle( t, 0, pImage->NbTailles, TailleMin, TailleMax ) ;

			pImage->Images[t]	=	new CDIB[pImage->NbPhases] ;
			
			for ( UINT i = 0; i < pImage->NbPhases; i++ )
				{	
				// Taille normale
				if ( ! pImage->Images[t][i].Create(Taille, Taille, hPalette ))
					{
					MessageBox( 0, "Cannot create phase bitmap", 0, MB_OK | MB_ICONSTOP ) ;
					ExitProcess(0) ;
					}

				ToutesLesPhases.StretchBits( &pImage->Images[t][i], 0, 0, Taille,Taille, Hauteur*i, 0, Hauteur, Hauteur, 0xFFFFFFFF ) ;
				}
			}
		}
	else
		{
		//Seule la premiere taille ( indice 0 ) est utilisee
		pImage->NbTailles	=	1 ;
		pImage->Images		=	new CDIB *[1] ;
		pImage->Images[0]	=	new CDIB[pImage->NbPhases] ;

		for ( UINT i = 0; i < pImage->NbPhases; i++ )
			{	
			// Taille normale
			if ( ! pImage->Images[0][i].Create(Hauteur, Hauteur, hPalette ))
				{
				MessageBox( 0, "Cannot create phase bitmap", 0, MB_OK | MB_ICONSTOP ) ;
				ExitProcess(0) ;
				}

			ToutesLesPhases.CopyBits( &pImage->Images[0][i], 0, 0, Hauteur,Hauteur, Hauteur*i, 0, 0xFFFFFFFF ) ;
			}
		}
}

// ==================================================================================================
// ImagePourMasse
// Calcule l'indice de l'image en fonction de la masse du corps
// ENTREES :	Masse du corps celeste
// SORTIES :	Indice de la bitmap
// ==================================================================================================
int	CEcoGravitation::ImagePourMasse( FLOTTANT	Attraction )
{
	int i ;

	const FLOTTANT Masse	=	Attraction / COptions::G() ;

	for ( i = 0; i < _pSkin->NbImages(); i++)
		if ( Masse <= COptions::MasseMax(i) )
			return i ;
			
	return _pSkin->NbImages() - 1 ;
}

// ==================================================================================================
// Charge les bitmaps necessaires a l'affichage
// On calcule le nombre de phase de chaque bitmap en divisant la largeur par la hauteur (chaque
// phase est a cote es autres )
// ENTREES :	Nombre de bitmaps
//				Tableau des noms de fichiers de bitmaps
//				Nombre de decors
//				Tableau des noms de fichiers de decors
// ==================================================================================================
void	CEcoGravitation::ChargeBitmaps()
	{
	
	for ( int i = 0; i < _pSkin->NbImages(); i++)
		{
		CDIB ToutesLesPhases ;
		JaugeStep() ;
		_pSkin->CreatePhasesPlanete( i, &ToutesLesPhases ) ;

		_Bitmap[i].Rayon	=	ToutesLesPhases.GetHeight() / 2 ;
		_Bitmap[i].NbPhases	=	max( 1, ToutesLesPhases.GetWidth() / ToutesLesPhases.GetHeight() ) ;
		
		RemplirTableauDImages( & _Bitmap[i], ToutesLesPhases ) ; 
		}
	
	_pSkin->CreateExplosion( &_Explosion ) ;

	_ElementsDecors[0].Dib.Load( IDR_COPYRIGHT ) ;

	// Message de copyright non pris en compte, il ne bouge pas
	_MaxLargeurDecor	=	0 ;
	_MaxHauteurDecor	=	0 ;

	for ( i = 0; i < _pSkin->NbElementsDecors(); i++)
		{
		JaugeStep() ;
		//_pSkin->CreateDecors( i, &_ElementsDecors[i+1].Dib ) ;
		_pSkin->CreateDecors( i, &_ElementsDecors[i].Dib ) ;
		
		// Mettre quelques etoiles sur le decors pour qu'il se fonde mieux dans
		// l'arriere plan

		CRect R ;
		R.left	=	0 ;
		R.top	=	0 ;
		R.right	=	_ElementsDecors[i].Dib.GetWidth() ;
		R.bottom=	_ElementsDecors[i].Dib.GetHeight() ;

		if ( _ElementsDecors[i].Dib.GetWidth() > _MaxLargeurDecor )
			_MaxLargeurDecor	=	_ElementsDecors[i].Dib.GetWidth() ;

		if ( _ElementsDecors[i].Dib.GetHeight() > _MaxHauteurDecor )
			_MaxHauteurDecor	=	_ElementsDecors[i].Dib.GetHeight() ;
		
		AfficheEtoiles( &_ElementsDecors[i].Dib, R ) ;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Affichage du repere autour du corps le plus gros
///////////////////////////////////////////////////////////////////////////////
inline void	CEcoGravitation::AfficheRepere()
{
	int	x, y ;
	UniversToPixel( _Corps[_IndicePlusGros].x, _Corps[_IndicePlusGros].y,
					_Corps[_IndicePlusGros].z,
					&x, &y ) ;

	{
	// Affiche la barre verticale
	pDCIntermediaire->FillBits( x, 0,1, Hauteur, PALETTEINDEX( _pSkin->CouleurRepere())) ;
	_NouveauxRectangles += CRect( x, 0, x+1, Hauteur ) ;
	}

	{
	//	Affiche la barre horizontale
	pDCIntermediaire->FillBits( 0, y, Largeur, 1, PALETTEINDEX( _pSkin->CouleurRepere())) ;
	_NouveauxRectangles += CRect( 0, y, Largeur, y+1 ) ;	
	}
}

int _cdecl CompareEloignementCorps( const void *arg1, const void *arg2 )
	{
	if ( ((CEcoGravitation::T_CORPS*)arg1)->z >= ((CEcoGravitation::T_CORPS*)arg2)->z )
		return -1 ;
	else
		return 1 ;
	}

// ============================================================================
// AfficheTousLesCorps
// ============================================================================
void	CEcoGravitation::AfficherTousLesCorps()
{
	// Changement d'image tous les 1/15 secondes
	double DeltaImages	=	(::GetCurrentTime()-_DerniereImage) / (1000.0 / 15.0) ;

	if ( COptions::Modele3D() )
		{
		// Tri des corps selon la distance
		qsort( _Corps, NbCorps, sizeof( T_CORPS ), CompareEloignementCorps ) ;
		RecherchePlusGros() ;
		}

	CRect	R ;

	if ( COptions::AfficherRepere() && ! Apercu() ) 
		AfficheRepere () ;
	
	for ( register int i = 0; i < NbCorps; i++)
		{
		int x, y ;

		int		IndiceTaille =		CalculeIndiceTaille( _Corps[i].z, _Bitmap[_Corps[i].Image].NbTailles ) ;
		CDIB * pDib	=	&_Bitmap[_Corps[i].Image].Images[IndiceTaille][(int)_Corps[i].Phase] ;
		const int	Rayon	=	pDib->GetWidth()/2 ;

		UniversToPixel( _Corps[i].x, _Corps[i].y, _Corps[i].z, &x, &y ) ;		
		SetRect( &R, x - Rayon, y - Rayon, x + Rayon, y + Rayon ) ;
				
		int DecalageX, DecalageY ;
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;


		// Affichage si la planete est a l'ecran
		if (! R.IsRectEmpty())
			{
			_NouveauxRectangles += R ;

			pDib->CopyBits(	pDCIntermediaire,
							R.left, R.top,	R.right-R.left, R.bottom-R.top,
							DecalageX,DecalageY,
							PALETTEINDEX( _pSkin->Transparence() )) ;

			///////////////////////////////////////////////////////////////////
			// Changer de phase, rotation des planetes
			///////////////////////////////////////////////////////////////////
			_Corps[i].Phase += DeltaImages * _Corps[i].Rotation ;
			
			if ( _Corps[i].Phase >= _Bitmap[_Corps[i].Image].NbPhases)
				_Corps[i].Phase = 0 ;
			else
				if ( _Corps[i].Phase < 0 )
					_Corps[i].Phase	= _Bitmap[_Corps[i].Image].NbPhases - 1 ;

			if ( _Corps[i].Image	==	_pSkin->ImageComete() )
				GenerePoussiere( _Corps[i] ) ;
			}
		}
}



// ============================================================================
// Generer un grain de poussiere de la queue de la comete
// ============================================================================
void	CEcoGravitation::GenerePoussiere( const T_CORPS & Cps )
{
	if ( _NbPoussieres >= COptions::NbMaxPoussieres() -1 )
		return ;

	if ( _pSkin->NbCouleursCometes() == 0 )
		return ;

	int x, y ;
	UniversToPixel( Cps.x, Cps.y, Cps.z, &x, &y ) ;

	if (  (x < 0 && Cps.vx < 0 ) || ( x > Largeur && Cps.vx > 0 ) ||
		  (y < 0 && Cps.vy < 0 ) || ( y > Hauteur && Cps.vy > 0 ) )
		  return ;

	FLOTTANT	dx, dy ;
	CalculVentSolaire( Cps, &dx, &dy ) ;

	const FLOTTANT PourcentX			=	Alea( 100-Cps.BruitPoussiere, 100+Cps.BruitPoussiere ) ;
	const FLOTTANT PourcentY			=	Alea( 100-Cps.BruitPoussiere, 100+Cps.BruitPoussiere ) ;
	const	int	IndiceTaille			=	CalculeIndiceTaille( Cps.z, _Bitmap[_pSkin->ImageComete()].NbTailles ) ;
	const	int HauteurComete			=	_Bitmap[_pSkin->ImageComete()].Images[IndiceTaille][0].GetHeight() / 2 ;

	_Poussieres[_NbPoussieres].x		=	Cps.x + Alea( -HauteurComete, HauteurComete )*COptions::DistMult() ;
	_Poussieres[_NbPoussieres].y		=	Cps.y + Alea( -HauteurComete, HauteurComete )*COptions::DistMult() ;

	_Poussieres[_NbPoussieres].vx		=	(Cps.vx + dx) * (PourcentX / 100.0) ;
	_Poussieres[_NbPoussieres].vy		=	(Cps.vy + dy) * (PourcentY / 100.0) ;

	_Poussieres[_NbPoussieres].Couleur	=	PALETTEINDEX( _pSkin->CouleursCometes( Alea( 0, _pSkin->NbCouleursCometes()-1)));
	_Poussieres[_NbPoussieres].Vie		=	COptions::ViePoussieres() * Alea( 500, 1500 ) / 1000.0 ;

	_Poussieres[_NbPoussieres].Taille	=	Alea( 1, COptions::TaillePoussieres() ) ;

	_NbPoussieres ++ ;
}

void CEcoGravitation::AfficheEtoiles( CDIB * pDib, const CRect & R )
	{
	if ( COptions::DensiteEtoiles() && _pSkin->NbCouleursEtoiles())
		{
		int	Surface	=	(R.Width() * R.Height()) ;
		if ( Surface < COptions::DensiteEtoiles() )
			{
			// Sert a garder un densite moyenne constante
			static int Restant = 0 ;

			Restant += Surface ;

			if ( Restant >= COptions::DensiteEtoiles() )
				{
				Surface = COptions::DensiteEtoiles() ;
				Restant -= Surface ;
				}
			}

		Surface /=	COptions::DensiteEtoiles() ;

		for ( register int i = 0; i < Surface ; i++)
			pDib->FillBits(	Alea( R.left, R.right-1 ),
							Alea( R.top, R.bottom-1 ),
							1,1, 
							PALETTEINDEX( _pSkin->CouleursEtoiles( Alea( 0, _pSkin->NbCouleursEtoiles()-1)))) ;
		}
	}


///////////////////////////////////////////////////////////////////////////////
// Affichage des grains de poussieres generes par les cometes
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AfficherPoussieres()
{
	int dx, dy ;
	int x, y ;
	for ( register int i = 0; i < _NbPoussieres; i++)
		{
		UniversToPixel( _Poussieres[i].x, _Poussieres[i].y, 0, &x, &y ) ;
		
		if ( (x >=0) && (y >= 0) && (x < Largeur) && (y < Hauteur) )
			{
			CRect	R( x, y, x + _Poussieres[i].Taille, y + _Poussieres[i].Taille ) ;

			_NouveauxRectangles.LimiteRect( R, &dx, &dy ) ;
			_NouveauxRectangles += R ;

			pDCIntermediaire->FillBits( x, y, _Poussieres[i].Taille, _Poussieres[i].Taille, _Poussieres[i].Couleur ) ;
			}
		}
}


void CEcoGravitation::AfficheExplosions()
{
	for ( register int i = 0; i < _NbExplosions; i++)
		{
		CRect R ;
		R.left	=	_Explosions[i].x - _Explosion.GetWidth() / 2 ;
		R.top	=	_Explosions[i].y - _Explosion.GetHeight() / 2 ;

		R.right	=	R.left + _Explosion.GetWidth() ;
		R.bottom=	R.top + _Explosion.GetHeight() ;
				
		int DecalageX, DecalageY ;
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;

		if (! R.IsRectEmpty())
			{
			_NouveauxRectangles += R ;

			_Explosion.CopyBits( pDCIntermediaire,
								R.left, R.top,	R.right-R.left, R.bottom-R.top,
								DecalageX,DecalageY,
								PALETTEINDEX( _pSkin->Transparence() )) ;
			}
	}
}

// ============================================================================
// Calcule  la vitesse donnee par le vent solaire pour une comete
// NB: comme les queues des cometes sont purement un attribut d'affichage,
//	   on ne doit tenir compte ni de TimeMult ni de DistMult
// ============================================================================
inline void	CEcoGravitation::CalculVentSolaire( const T_CORPS & Cps, FLOTTANT * pdx, FLOTTANT *pdy )
{
	const int PlusProche	=	RechercheEtoilePlusProche(Cps) ;

	const FLOTTANT	Distance	=	CalculeDistance2D( Cps, _Corps[PlusProche] ) / COptions::DistMult() ;
	if ( Distance == 0.0 )
		{
		*pdx	=	0 ;
		*pdy	=	0 ;
		}
	else
		{
		*pdx	=	(Cps.x - _Corps[PlusProche].x )  * (COptions::VentSolaire() / Distance ) ;
		*pdy	=	(Cps.y - _Corps[PlusProche].y )  * (COptions::VentSolaire() / Distance ) ;
		}
}




// ============================================================================
// Recherche l'etoile la plus proche d'un corps
// ============================================================================
int	CEcoGravitation::RechercheEtoilePlusProche( const T_CORPS & Cps )
{
	int	Indice	=	0 ;
	int Image	=	-1 ;
	FLOTTANT	Distance = 0 ;

	for ( register int i = 0; i < NbCorps; i++)
		{
		// Si l'image est celle d'une planete plus grosse, on prend celle la
		if ( _Corps[i].Image > Image )
			{
			Image	=	_Corps[i].Image ;
			Indice	=	i ;
			Distance=	CalculeDistance( _Corps[i], Cps ) ;
			}
		else
			// On ne prend en compte que les corps au moins aussi grand que
			// celui qu'on a deja
			if ( _Corps[i].Image == Image )
				{
				const FLOTTANT Dist	=	CalculeDistance( _Corps[i], Cps ) ;
				if ( Dist < Distance )
					{
					Indice		=	i ;
					Distance	=	Dist ;
					}
				}	
		}
	return Indice ;
}

///////////////////////////////////////////////////////////////////////////////
// CalculeIndiceTaille
//	Determiner la taille de bitmap a utiliser en fonction de l'eloignement du
//	corps. Le nombre de tailles precalculees disponible est fonction de la
//	taille initiale de l'image
//	NB: en mode 2D, il y a une seule taille
//	ENTREES :	coordonnee z
//				Nombre de tailles disponibles pour cette image
//	RETOUR :	Indice dans le tableau de tailles
///////////////////////////////////////////////////////////////////////////////
int CEcoGravitation::CalculeIndiceTaille(FLOTTANT z, int NbTailles )
{
	if ( ! COptions::Modele3D() )
		return 0 ;

	if ( _NbAffiches == 1 )
		return NbTailles / 2 ;

	if ( z >= _MaxZ )
		return 0 ;

	if ( z <= _MinZ )
		return NbTailles - 1 ;

	return ChangeEchelle( (int)z, (int)_MaxZ, (int)_MinZ, 0, NbTailles-1 ) ;
}

///////////////////////////////////////////////////////////////////////////////
// AfficheInfos
// Affiche quelques infos texte
///////////////////////////////////////////////////////////////////////////////
void CEcoGravitation::AfficheInfos()
	{
	CDC	* pDc	=	pDCIntermediaire->GetDC() ;
	pDc->SetBkMode( TRANSPARENT ) ;
	pDc->SetTextColor( RGB( 255,255, 255)) ;
	pDc->SelectStockObject( ANSI_VAR_FONT ) ;
	
	CRect R ;
	int x, y ;
			
	for ( register int i = 0; i < NbCorps; i++)
		{
		int		IndiceTaille =		CalculeIndiceTaille( _Corps[i].z, _Bitmap[_Corps[i].Image].NbTailles ) ;
		CDIB * pDib	=	&_Bitmap[_Corps[i].Image].Images[IndiceTaille][(int)_Corps[i].Phase] ;
		const int	Rayon	=	pDib->GetWidth()/2 ;
		
		UniversToPixel( _Corps[i].x, _Corps[i].y, _Corps[i].z, &x, &y ) ;		
		SetRect( &R, x - Rayon, y + Rayon, x + Rayon, y + Rayon + Rayon ) ;
		
		int DecalageX, DecalageY ;
		_NouveauxRectangles.LimiteRect( R, &DecalageX, &DecalageY ) ;
		
		if ( ! R.IsRectEmpty())
			{
			const FLOTTANT Vitesse = COptions::Modele3D() ?
					sqrt( (_Corps[i].vx * _Corps[i].vx ) + ( _Corps[i].vy * _Corps[i].vy ) + (_Corps[i].vz * _Corps[i].vz) ) :
					sqrt( (_Corps[i].vx * _Corps[i].vx ) + ( _Corps[i].vy * _Corps[i].vy )  )	;
		
			CString	Masse	;
			Masse.Format( "m=%g\nv=%g", _Corps[i].Attraction / COptions::G(),
										Vitesse ) ;

			pDc->DrawText( Masse, R, DT_LEFT | DT_CALCRECT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX ) ;		
			pDc->DrawText( Masse, R, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_NOPREFIX ) ;	
			_NouveauxRectangles += R ;
			}
		}
	
	CString Texte ;
	CString	Masses ;
	
	for ( i = 0; i < _pSkin->NbImages(); i++)
		{
		CString Masse ;
		Masse.Format( "Mass %d = %5g\n", i, (FLOTTANT)COptions::MasseMax(i)) ;
		Masses += Masse ;
		}
	
	const DWORD	Maintenant	=	GetCurrentTime() ;
	DWORD	Duree			=	(DWORD)((Maintenant - _DebutSysteme) / 1000L * COptions::TimeMult()) ;
	const DWORD	Jours		=	Duree / ( 60L * 60L * 24L ) ;
	Duree					-=	Jours * ( 60L * 60L * 24L ) ;
	const DWORD	Heures	   =	Duree / ( 60L * 60L ) ;
	Duree					-=	Heures * ( 60L * 60L ) ;

	const DWORD Minutes	   =	Duree  / 60L ;
	const DWORD	Secondes   =	Duree % 60L ;
	
	CString Line ;
	Line.Format( 
		"%s\n"
		"G         = %-5g\n"
		"Nb planets=%-5d\n"
		"%s"
		"Dist Mult = %-5g\n"
		"Time mult = %-5g\n"
		"Star sys.life=%dd%2dh%2dm%2ds\n"
		"Frame/sec=%-5d\n"
		"Comp. pos/frm=%-d\n"
		"Last event:\n%s",
		COptions::Modele3D() ? "3D model" : "2D model",
		(FLOTTANT)COptions::G(), 
		NbCorps,
		(const TCHAR *)Masses,
		(FLOTTANT)COptions::DistMult(), 
		(FLOTTANT)COptions::TimeMult(),
		(int)Jours, (int)Heures, (int)Minutes, (int)Secondes, 
		(int)COptions::NbImagesSeconde(), 
		_NbBoucles,
		(const TCHAR*)_DernierEvenement ) ;

	Texte += Line ;

	R.SetRectEmpty() ;
	R.right	=	R.left + 150 ;
	pDc->DrawText( Texte, R, DT_LEFT | DT_TOP | DT_CALCRECT | DT_WORDBREAK) ;

	static int Bord = -1 ;
	if ( Bord == -1 || CEcoGravitation::GetEconomiseur()->UnSur(1000) )
		Bord = CEcoGravitation::GetEconomiseur()->Alea( 1, 4 ) ;

	switch( Bord )
		{
		case 1 :
			break ;

		case 2 :
			R.OffsetRect( Largeur - R.Width(), 0 ) ;
			break ;

		case 3 :
			R.OffsetRect( 0, Hauteur - R.Height()) ;
			break ;

		case 4 :
			R.OffsetRect( Largeur - R.Width(), Hauteur - R.Height()) ;
			break ;

		}

	FillRect( *pDc, R, (HBRUSH)GetStockObject( DKGRAY_BRUSH )) ;
	pDc->DrawText( Texte, R, DT_LEFT | DT_TOP | DT_WORDBREAK ) ;
	
	_NouveauxRectangles += R ;
	}


FLOTTANT CEcoGravitation::CalculeDistance( const T_CORPS & T1, const T_CORPS & T2 )
		{
		if ( COptions::Modele3D() )
				{
				const FLOTTANT DX	=	T1.x - T2.x ;
				const FLOTTANT DY	=	T1.y - T2.y ;
				const FLOTTANT DZ	=	T1.z - T2.z ;
				
				return sqrt( (DX*DX) + (DY*DY) + (DZ*DZ)) ;
				}
			else
				return CalculeDistance2D( T1, T2 ) ;
		}


FLOTTANT	CEcoGravitation::CalculeDistance( const CEcoGravitation::T_CORPS & T2 )
	{
	if ( COptions::Modele3D() )
		return CalculeDistance3D(T2) ;
	else
		return CalculeDistance2D(T2);		
	}


void CEcoGravitation::UniversToPixel( FLOTTANT x, FLOTTANT y, FLOTTANT, int * px, int * py )
		{
		const FLOTTANT X = (x / COptions::DistMult()) 
						+ (double)(CEconomiseur::GetEconomiseur()->Largeur/2) ;

			if ( X > (double)INT_MAX )
				*px	=	INT_MAX-1 ;
			else
				if ( X < (double)INT_MIN )
					*px	=	INT_MIN+1 ;
				else
					*px	=	(int)X ;

		const FLOTTANT Y = (y / COptions::DistMult()) + (double)(CEconomiseur::GetEconomiseur()->Hauteur/2) ;

			if ( Y > (double)INT_MAX )
				*py	=	INT_MAX-1 ;
			else
				if ( Y < (double)INT_MIN )
					*py	=	INT_MIN+1 ;
				else
					*py =	(int)Y ;
		}

COptions* CEcoGravitation::GetOptions()
{
	if ( ! _pOptions )
		_pOptions	=	new COptions() ;

	return _pOptions ;
}
