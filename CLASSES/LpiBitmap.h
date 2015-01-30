///////////////////////////////////////////////////////////////////////////////
// CLPIBitmap
//	Construction directement a partir des ressources
//	Taille sans s'emmerder avec GetObject
//	Serialization
///////////////////////////////////////////////////////////////////////////////

#ifndef __LPIBITMAP_H__
#define __LPIBITMAP_H__

class	CLPIBitmap : public	CBitmap
{
	public	:
		CLPIBitmap( WORD	IdRessource ) ;			// LoadBitmap( IdRessource )
		CLPIBitmap( LPCSTR	ResourceName ) ;		// LoadBitmap( ResourceName )
		~CLPIBitmap() ;								// DeleteObject
		
		CSize			Taille(void) const ;
		int				Largeur( void ) const ;
		int				Hauteur( void ) const ;
		const BITMAP *	GetObject() const ;
		DWORD			NbCouleurs( void ) const ;
		DWORD			NbOctets( void ) const ;

		void			SetBitmapBits( const BYTE * ) ;
		void			GetBitmapBits( BYTE * ) const ;
		
		DECLARE_SERIAL( CLPIBitmap ) ;			// Stocke
		virtual	void	Serialize( CArchive & ) ; 
		
		// Afficher la bitmap dans un DC
		void Affiche( CDC *, int xDC, int yDC, int xBitmap=0, int yBitmap=0,
					  DWORD RasterOp	=	SRCCOPY ) ;
		
		// Calculer la region occupee par la bitmap, sauf une couleur
		HRGN	CreateRegion( COLORREF	Masque ) const ;

		friend	class	CLPIIcone ;
	private :
		CLPIBitmap() ;		// Juste pour la serialization
		
		BITMAP	_sBitmap ;
} ;

#endif
