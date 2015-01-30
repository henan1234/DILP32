#include <windows.h>
#include "resource.h"

#define NB_MAX_BULLES	50
#define NB_MAX_GOUTTES	50
#define NB_MAX_BULLES	50
#define NB_MAX_ONDES	50

#define NB_MAX_IMAGES_BULLES	3

#define NB_PHASES_CREATION	9
#define NB_MAX_PHASES_GOUTTES 11

COLORREF	CouleurLiquide ;
int			Niveau ;

extern		int				NbMaxGouttes	;
extern		int				NbGouttes		;
extern		HINSTANCE		hMainInstance ;
extern		int				NbMaxBulles ;
extern		int				NbBulles ;
extern		HDC				hDCEcran ;

extern void MonteeDesBulles( HDC hDC ) ;
extern void	GestionGouttes( HDC hDC, COLORREF	CouleurLiquide, int NiveauLiquide ) ;
extern void	AfficheBitmapTransparent( HDC	hDC, int xD, int yD, int l, int h, HBITMAP hBitmap, int xS, int yS ) ;
