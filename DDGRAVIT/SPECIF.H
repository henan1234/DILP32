#ifdef __cplusplus
extern "C"
{
#endif

///////////////////////////////////////////////////////////////////////////////
// Mettre a VRAI si on doit noircir la fenetre
///////////////////////////////////////////////////////////////////////////////
extern BOOL	NoircirEcran ;

///////////////////////////////////////////////////////////////////////////////
// Mettre a VRAI si on s'execute plus vite qu'avec un WM_TIMER
///////////////////////////////////////////////////////////////////////////////
extern BOOL	HautePriorite ;

///////////////////////////////////////////////////////////////////////////////
// Nom de l'economiseur a fournir
///////////////////////////////////////////////////////////////////////////////
extern	const char	*	SPECIF_NomEconomiseur ;

///////////////////////////////////////////////////////////////////////////////
// Valeur arbitraire pour verifier l'enregistrement des versions shareware
///////////////////////////////////////////////////////////////////////////////
extern	const char	*	SPECIF_ValeurEnregistre ;

///////////////////////////////////////////////////////////////////////////////
// Taille de l'affichage, fourni
///////////////////////////////////////////////////////////////////////////////
extern int	Largeur ;
extern int	Hauteur ;
extern HPALETTE	hPalette ;

extern	HANDLE	hMainInstance ;

// Les fonctions SPECIF_xxx sont a fournir
void 	SPECIF_InitEconomiseur( HWND hWnd ) ;
void 	SPECIF_Animation( HDC, UINT NoTimer, LPRECT lpR ) ;
void 	SPECIF_Fin( HWND hWnd ) ;
 
void	SPECIF_PeintFenetre( HDC, LPRECT ) ;

void	SPECIF_LirePreferences(void) ;
void	SPECIF_EcrirePreferences(void) ;

BOOL	SPECIF_PreprocessMessageConfig( HWND, unsigned, WPARAM, LPARAM ) ;

// Ces fonctions sont dans ECONO.C
// ==================================================================================================
// Retoune un entier aleatoire
// ==================================================================================================
int arand( int x ) ;
// ==================================================================================================
// Alea
// Retourne une valeur aleatoire entre deux bornes incluses
// ==================================================================================================
int Alea( int Min, int Max ) ;

// ==================================================================================================
// UnSur
// Retourne une VRAI un coup sur...
// ==================================================================================================
BOOL UnSur( int x ) ;

// ==================================================================================================
// Lecture des valeurs a partir du fichier de configuration
// Pour toutes les fonctions :
//	App = nom de l'economiseur
//	Nom	= nom de la valeur
// ==================================================================================================
int		LitEntier( char * Nom, DWORD Defaut ) ;
double	LitDouble( char * Nom, double	Defaut ) ;
void	LitChaine( char * Nom, char * Buffer, int TailleBuffer ) ;

// ==================================================================================================
// Ecriture des valeurs a partir du fichier de configuration
// Pour toutes les fonctions :
//	App = nom de l'economiseur
//	Nom	= nom de la valeur
// ==================================================================================================
void EcritEntier( char * Nom, DWORD Valeur ) ;
void EcritDouble( char * Nom, double	Valeur ) ;
void EcritChaine( char * Nom, char * Buffer ) ;

// ==================================================================================================
// Obtient une bitmap copie de l'ecran AVANT l'affichage de l'economiseur
// ENTREES :	Taille desiree de l'image
// ==================================================================================================
HBITMAP	MemoEcran( int Largeur, int Hauteur ) ;

// ==================================================================================================
// Retourne VRAI si c'est une version enregistree
// ==================================================================================================
BOOL	VerifVersion() ;

// ==================================================================================================
// AfficheRectangme
// Affiche les rectangles de la liste
// ENTREES :	Tableau de rectangles
//				Nombre de rectangles
//				Dc source et dest
// SORTIES :	rien
// RETOUR :		rien
// ==================================================================================================
void	AfficheRectangles( RECT *	TabRect, const int NbRects, HDC hDCDest, HDC hDCSrc ) ;

// ==================================================================================================
// AjouteRect
// Ajoute un rectangle a la liste de rectangles a afficher, ne la prend pas en compte si elle sort de
// l'ecran ou si le rectangle est inclu dans un rectangle deja affiche
// ENTREES :	Tableau de rectangles
//				Taille du tableau
//				Nombre actuel de rectangles
//				Rectangle a ajouter
// SORTIES :	Nb de rectangles eventuellement incremente
// RETOUR :		rien
// ==================================================================================================
void AjouteRect( RECT*	TabRects, int NbMaxRects, int * pNbRects, const RECT * pR ) ;

// ==================================================================================================
// IncluRect
//	Determine si le deuxieme rectangle est entierement inclu dans le premier
// ENTREES :	Deux rectangles
// RETOUR :		Vrai si le deuxieme est inclu dans le premier
// ==================================================================================================
BOOL IncluRect( const RECT *	pR1, const RECT * pR2 ) ;

// ==================================================================================================
// NbCouleurs
// Retourne le nombre de couleurs du mode graphique
// ENTREES :	rien
// SORTIES :	rien
// RETOUR :		vraisemblablement 16, 256 ou 65536
// ==================================================================================================
int	NbCouleurs(void) ;

// ==================================================================================================
// FastBitBlt
// Pointeur sur une fonction de transfert de pixels la plus rapide possible (WinG si on
// trouve, GDI sinon)
// ENTREES :	DC	Dest
//				x, y, l, h
//				DC Source
//				x source, y source
// SORTIES :	rien
// RETOUR :		rien
// ==================================================================================================
#define WINGAPI WINAPI
typedef HDC (WINGAPI WinGCreateDCProc)(void);
typedef BOOL (WINGAPI WinGBitBltProc)(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc,int nYOriginSrc );
typedef BOOL (WINGAPI WinGStretchBltProc)(HDC hdcDest,int nXOriginDest,int nYOriginDest,int nWidthDest,int nHeightDest,HDC hdcSrc,int nXOriginSrc, int nYOriginSrc,int nWidthSrc,int nHeightSrc );

WinGCreateDCProc*	FastCreateDC ;
WinGBitBltProc*		FastBitBlt ;
WinGStretchBltProc*	FastStretchBlt ;

// ==================================================================================================
// FastCreateBitmap
// Creer une bitmap le mieux adaptee possible a l'affichage actuel (eventuellement WinG)
// ENTREES :	Largeur, Hauteur
// SORTIES :	rien
// RETOUR :		HBITMAP
// ==================================================================================================
HBITMAP	FastCreateBitmap( HDC, int, int ) ;

#ifdef __cplusplus
} ;
#endif

