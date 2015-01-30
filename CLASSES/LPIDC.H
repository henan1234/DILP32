///////////////////////////////////////////////////////////////////////////////
// CLPIMemDC
//	DC en memoire avec une bitmap de taille donnee
///////////////////////////////////////////////////////////////////////////////

#ifndef __LPIDC_H__
#define __LPIDC_H__

class	CLPIMemDC : public CDC
{
	public :
		CLPIMemDC( CDC & DCCompatible, int	Largeur, int Hauteur ) ; 	
		CLPIMemDC( CDC &, int Largeur, int Hauteur, int BitsPixels, int Plans, LPBYTE = NULL ) ;
		CLPIMemDC( CDC &, CBitmap & ) ;
		CLPIMemDC( CBitmap & ) ;		// CreateCompatibleDC( NULL )
		
		~CLPIMemDC() ;
		
#ifdef _DEBUG		
	virtual	void	AssertValid() const ;
#endif
		
	private :
		CBitmap*	_pOldBitmap ;
		CBitmap*	_pBitmapCreee ;
} ;

#endif
