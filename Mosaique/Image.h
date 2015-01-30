// Image.h: interface for the CImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__2F183336_3FE9_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_IMAGE_H__2F183336_3FE9_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define CENTREV	1
#define CENTREH	2
class CImage : public CObject  
{
public:
	void Dessine( CDC &, int x, int y, int l, int h, int Centre = CENTREV | CENTREH  );
	void DeleteObject();
	HBITMAP Handle();
	int Hauteur();
	int Largeur();
	CSize Taille();
	const CString & Nom();
	CImage( LPCSTR BitmapName );
	virtual ~CImage();

	void	Dessine( CDC &, int x, int y, double FacteurZoom = 1.0 ) ;

private :
	CString	_Nom ;
	HBITMAP	_hBitmap ;
	CSize	_Taille ;
};

#endif // !defined(AFX_IMAGE_H__2F183336_3FE9_11D1_AEF5_444553540000__INCLUDED_)
