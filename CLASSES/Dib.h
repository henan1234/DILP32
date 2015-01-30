///////////////////////////////////////////////////////////////////////////////
// DIB.H
//	Interface de la classe CDIB
///////////////////////////////////////////////////////////////////////////////
#ifndef _DIB_H_
#define _DIB_H_

class CDIB : public CObject
{
    DECLARE_SERIAL(CDIB)
public:
	COLORREF GetPixel( int x, int y );
    CDIB();
    ~CDIB();

    inline	BITMAPINFO *	GetBitmapInfoAddress()	{return m_pBMI;}                        // ptr to bitmap info
    inline	void *			GetBitsAddress()		{return m_pBits;}                       // ptr to the bits
    inline	RGBQUAD *		GetClrTabAddress()		{return (LPRGBQUAD)(((BYTE *)(m_pBMI))+ sizeof(BITMAPINFOHEADER));}       // ptr to color table
    inline	int GetBitsPerPixel() {return m_pBMI->bmiHeader.biBitCount;}

    int GetNumClrEntries();                     // number of color table entries
    virtual int GetWidth() {return DibWidth();}   // image width
    virtual int GetStorageWidth() {return StorageWidth();}   // memory width
    virtual int GetHeight() {return DibHeight();} // image height
    
	// Creation
	BOOL Create(int width, int height, CPalette* pPal = NULL);         // create a new DIB
    BOOL Create(int width, int height, HPALETTE hPal);         // create a new DIB
    BOOL Create(BITMAPINFO* pBMI, BYTE* pBits, BOOL bOwnBits = FALSE); // create from existing mem,
    BOOL Create(BITMAPINFO* pPackedDIB); // create from packed DIB
    void *GetPixelAddress(int x, int y);

	// Chargement
    virtual BOOL Load(const char* pszFileName = NULL);// load DIB from disk file
    virtual BOOL Load(CFile* fp);               // load from file
    virtual BOOL Load(WORD wResid);             // load DIB from resource

	// Sauvegarde
    virtual BOOL Save(const char* pszFileName = NULL);// save DIB to disk file
    virtual BOOL Save(CFile *fp);               // save to file
    virtual void Serialize(CArchive& ar);

	// Dessiner la DIB dans un DC
    virtual void Draw(CDC *pDC, int x, int y);
    virtual void Draw(HDC hDC, int x, int y);
    virtual BOOL MapColorsToPalette(CPalette *pPal);
    virtual BOOL MapColorsToPalette(HPALETTE hPal);
    virtual void GetRect(RECT* pRect);
    virtual void CopyBits(CDIB* pDIB, int xd, int yd, int w, int h, int xs, int ys, COLORREF clrTrans = 0xFFFFFFFF);
	inline void CopyBits(CDIB* pDIB, LPRECT lpR, int xs, int ys, COLORREF clrTrans = 0xFFFFFFFF)
	{ CopyBits( pDIB, lpR->left, lpR->top, lpR->right - lpR->left, lpR->bottom-lpR->top, xs, ys, clrTrans ) ; }


	// Ajouts LPI
	void	FillBits( int x, int y, int w, int h, COLORREF Couleur ) ;
	void	SetPixelV( int x, int y, COLORREF Clr ) ;

    virtual void StretchBits(CDIB* pDIB, 
                             int xd, int yd,
                             int wd, int hd,
                             int xs, int ys,
                             int ws, int hs,
                             COLORREF clrTrans = 0xFFFFFFFF);
    virtual void DoubleBits(CDIB* pDIB, 
                            int xd, int yd,
                            int xs, int ys,
                            int ws, int hs,
                            COLORREF clrTrans = 0xFFFFFFFF);
    BOOL SetColorTable(CPalette* pPal);

    static BOOL IsWinDIB(BITMAPINFOHEADER* pBIH);
    static int NumDIBColorEntries(BITMAPINFO* pBmpInfo);

// Ajouts LPI
	///////////////////////////////////////////////////////////////////////////
	// Retourne une REGION excluant une couleur donnee
	///////////////////////////////////////////////////////////////////////////
	HRGN		CreateRegion( COLORREF	clrTrans	=	0xFFFFFFFF ) ;
	///////////////////////////////////////////////////////////////////////////
	// Cree un HBITMAP a partir d'une DIB
	///////////////////////////////////////////////////////////////////////////
	HBITMAP		CreateBitmap( void ) ;
	inline		operator HBITMAP() { return CreateBitmap() ; } ;

protected:
    BITMAPINFO *m_pBMI;         // pointer to BITMAPINFO struct
    BYTE *m_pBits;              // pointer to the bits
    BOOL m_bMyBits;             // TRUE if DIB owns Bits memory

private:
    int DibHeight()  {return m_pBMI->bmiHeader.biHeight;}
    int DibWidth() {return m_pBMI->bmiHeader.biWidth;}
    int StorageWidth() {return (((m_pBMI->bmiHeader.biWidth * m_pBMI->bmiHeader.biBitCount)
                     + 31) & ~31) >> 3;}

	HRGN	CreateRegion8Bits( COLORREF ) ;		// Pour bitmaps 256 couleurs
	HRGN	CreateRegion16Bits( COLORREF ) ;	// Pour bitmaps 64K couleurs
	HRGN	CreateRegion24Bits( COLORREF ) ;	// Pour bitmaps 24M couleurs
};

#endif

