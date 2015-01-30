///////////////////////////////////////////////////////////////////////////////
// CLPIBitmap
//	Construction directement a partir des ressources
//	Taille sans s'emmerder avec GetObject
//	Serialization
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "windowsx.h"
#include "math.h"
#include "LpiBitmap.h"

#define __huge

///////////////////////////////////////////////////////////////////////////////
// ReadHuge
//	Lire un tres gros morceau dans une archive
///////////////////////////////////////////////////////////////////////////////
DWORD	ReadHuge( CArchive & Ar, void __huge * pBuffer, DWORD Longueur )
{
	DWORD	NbLus	=	0 ;
	char __huge *	pLecture	=	(char __huge *)pBuffer ;

	while ( Longueur > NbLus )
		{
		const	UINT	Morceau	=	min( 32000, Longueur - NbLus ) ;
		const UINT	Lecture	=	Ar.Read( pLecture, Morceau ) ;
		pLecture	+=	Lecture ;
		NbLus		+=	Lecture ;
		}

	return NbLus ;
}

DWORD	WriteHuge( CArchive & Ar, const void __huge * pBuffer, DWORD Longueur )
{
	DWORD	NbEcrits	=	0 ;
	char __huge *	pEcriture =	(char __huge *)pBuffer ;

	while ( Longueur > NbEcrits )
		{
		const	UINT	Morceau	=	min( 32000, Longueur - NbEcrits ) ;
		Ar.Write( pEcriture, Morceau ) ;
		pEcriture	+=	Morceau ;
		NbEcrits	+=	Morceau ;
		}
	return NbEcrits ;
}


IMPLEMENT_SERIAL( CLPIBitmap, CBitmap, 1 ) ;

CLPIBitmap::CLPIBitmap()
{
	memset( &_sBitmap, 0, sizeof( _sBitmap )) ;
}

CLPIBitmap::CLPIBitmap( WORD	IdRessource )
{
	VERIFY( LoadBitmap( IdRessource )) ;
	CGdiObject::GetObject( sizeof( _sBitmap ), &_sBitmap ) ;
}

CLPIBitmap::CLPIBitmap( LPCSTR	ResourceName )
{
	VERIFY( LoadBitmap( ResourceName )) ;
	CGdiObject::GetObject( sizeof( _sBitmap ), &_sBitmap ) ;
}

CLPIBitmap::~CLPIBitmap()
{
	DeleteObject() ;
}
		
CSize	CLPIBitmap::Taille(void) const
{
	return CSize( _sBitmap.bmWidth, _sBitmap.bmHeight ) ;
}
		
int		CLPIBitmap::Largeur( void ) const
{
	return	_sBitmap.bmWidth ;
}

int		CLPIBitmap::Hauteur( void ) const
{
	return	_sBitmap.bmHeight ;
}

const BITMAP *	CLPIBitmap::GetObject() const
{
	return &_sBitmap ;
}
		
void	CLPIBitmap::Serialize( CArchive & ar )
{
	CObject::Serialize( ar ) ;
	
	if ( ar.IsLoading() )
		{
		ar.Read( &_sBitmap, sizeof( _sBitmap )) ;
		DWORD	Longueur ;
		ar >> Longueur ;
		if ( Longueur )
			{
			BYTE FAR *	lpBits	=	new __huge BYTE[ Longueur ] ;
			ar.Read ( lpBits, Longueur) ;
			GetBitmapBits( lpBits ) ;
			delete [] lpBits ;
			}		
		}
	else
		{
		ar.Write( &_sBitmap, sizeof( _sBitmap )) ;
		const	DWORD	Longueur	=	NbOctets() ;
		ar << Longueur ;
		if ( Longueur )
			{
			BYTE FAR *	lpBits	=	new __huge BYTE[ Longueur ] ;
			GetBitmapBits( lpBits ) ;
			
			WriteHuge ( ar, lpBits, Longueur) ;
			delete [] lpBits ;
			}
		}
}

DWORD CLPIBitmap::NbCouleurs( void ) const
{
	return (DWORD)pow( 2, _sBitmap.bmBitsPixel * _sBitmap.bmPlanes ) ;
}
                 
DWORD	CLPIBitmap::NbOctets( void ) const
{
	return (DWORD)_sBitmap.bmWidthBytes * (DWORD)_sBitmap.bmHeight ;
}


void CLPIBitmap::SetBitmapBits( const BYTE __huge * lpBits )
{
	const	DWORD	Longueur	=	NbOctets() ;
	// Desole, AfxIsValidAddress ne verifie que 64K en version 16 bits
	ASSERT( AfxIsValidAddress( lpBits, (int)Longueur, FALSE )) ;
	CBitmap::SetBitmapBits( Longueur, lpBits ) ;
}

void CLPIBitmap::GetBitmapBits( BYTE __huge * lpBits ) const
{
	const	DWORD	Longueur	=	NbOctets() ;
	// Desole, AfxIsValidAddress ne verifie que 64K en version 16 bits
	ASSERT( AfxIsValidAddress( lpBits, (int)Longueur, TRUE )) ;
	CBitmap::GetBitmapBits( Longueur, lpBits ) ;
}


void	CLPIBitmap::Affiche( CDC * pDC, int xDC, int yDC, int xBitmap, int yBitmap, DWORD RasterOp )
{
	ASSERT_VALID( pDC ) ;
	CDC	MemDc ;
	VERIFY( MemDc.CreateCompatibleDC( pDC )) ;
	ASSERT_VALID( &MemDc ) ;
	
	CBitmap*	pOld	=	MemDc.SelectObject( this ) ;
	
	pDC->BitBlt(	xDC, yDC,
					Largeur(), Hauteur(),
					&MemDc, xBitmap, yBitmap, RasterOp ) ;
					
	MemDc.SelectObject( pOld ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Creation d'une region a partir d'une bitmap
// On enleve toutes les parties qui sont d'une certaine couleur
///////////////////////////////////////////////////////////////////////////////
HRGN	CLPIBitmap::CreateRegion( COLORREF	CouleurHors ) const
{
	HDC		hMemDC ;
	BITMAP	sBitmap ;
	HGDIOBJ	hOld ;
	RGNDATA	*	lpData ;
	LPRECT	lpR	;
	int		Ligne ;
	int		IndiceFin	;
	int		IndiceDepart;


	ASSERT( m_hObject ) ;
						
	::GetObject( m_hObject, sizeof( sBitmap ), &sBitmap ) ;

	hMemDC	=	CreateCompatibleDC( NULL ) ;
	hOld	=	SelectObject( hMemDC, m_hObject ) ;

	///////////////////////////////////////////////////////////////////////////
	// Initialisation de l'entete de la structure
	///////////////////////////////////////////////////////////////////////////
	lpData				=	(RGNDATA*)GlobalAllocPtr(GMEM_ZEROINIT,	sizeof( RGNDATA ) + sizeof( RECT ) * sBitmap.bmHeight ) ;
	ASSERT( lpData ) ;

	lpData->rdh.dwSize	=	sizeof( lpData->rdh.dwSize ) ;
	lpData->rdh.iType	=	RDH_RECTANGLES ;
	lpData->rdh.nCount	=	0 ;
	lpData->rdh.nRgnSize=	0 ;

	// Bounding rectangle : le rectangle de la bitmap
	SetRect( &lpData->rdh.rcBound,0,0,sBitmap.bmWidth,sBitmap.bmHeight ) ;

	lpR	=	(LPRECT)&lpData->Buffer ;			// Pour se faciliter la vie, on pointe directement sur les rectangles

	///////////////////////////////////////////////////////////////////////////
	// Parcourir les lignes pour en deduire les rectangles
	///////////////////////////////////////////////////////////////////////////
	for ( Ligne	=	0; Ligne < sBitmap.bmHeight; Ligne ++ )
		{
		IndiceDepart	=	0 ;

		while ( IndiceDepart < sBitmap.bmWidth-1)
			{
			///////////////////////////////////////////////////////////////////////////
			// Parcourir la ligne et en deduire les bouts de la couleur qui nous interessent
			///////////////////////////////////////////////////////////////////////////
	
			// Trouver le premier pixel d'une autre couleur que celle specifiee
			while ( (IndiceDepart < sBitmap.bmWidth) &&	GetPixel( hMemDC, IndiceDepart, Ligne ) == CouleurHors )
				IndiceDepart ++ ;

			// Parcourir jusqu'a retrouver la couleur specifiee
			IndiceFin =	IndiceDepart ;
			while ( (IndiceFin < sBitmap.bmWidth ) && GetPixel( hMemDC, IndiceFin, Ligne ) != CouleurHors )
				IndiceFin ++ ;
			
			// Ajouter le rectangle trouve
			if ( IndiceFin > IndiceDepart )
				{
				// Ajouter le rectangle
				lpData	=	(RGNDATA*)GlobalReAllocPtr( lpData, sizeof( lpData->rdh ) + ((lpData->rdh.nCount+1)*sizeof( RECT )),
									   					GMEM_MOVEABLE) ;
				SetRect( &lpR[lpData->rdh.nCount], IndiceDepart, Ligne, IndiceFin, Ligne+1 ) ;

				lpData->rdh.nRgnSize	+=	sizeof( RECT ) ;
				lpData->rdh.nCount++ ;
				}

			IndiceDepart = IndiceFin ;
			}

		// Ligne suivante
		}

	SelectObject( hMemDC, hOld ) ;
	DeleteDC( hMemDC ) ;

	HRGN hRegion	=	ExtCreateRegion( NULL, sizeof( lpData->rdh ) + (lpData->rdh.nCount*sizeof( RECT )),	lpData ) ;

	GlobalFreePtr( lpData ) ;

	return hRegion ;
}

void CLPIBitmap::Mosaique( CDC * pDC, const CRect  & R, DWORD RasterOp )
{
	ASSERT_VALID( pDC ) ;
	CDC	MemDc ;
	VERIFY( MemDc.CreateCompatibleDC( pDC )) ;
	ASSERT_VALID( &MemDc ) ;
	
	CBitmap*	pOld	=	MemDc.SelectObject( this ) ;

	for ( int x = R.left; x < R.right; x += Largeur())
		for ( int y = R.top; y < R.bottom; y += Hauteur())
				pDC->BitBlt(	x, y,
								Largeur(), Hauteur(),
								&MemDc,
								0, 0, RasterOp ) ;
					
	MemDc.SelectObject( pOld ) ;
}
