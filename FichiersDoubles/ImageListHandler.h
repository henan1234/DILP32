// ImageListHandler.h: interface for the CImageListHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGELISTHANDLER_H__1F9F96B6_3254_497F_9A44_2A04D93EB259__INCLUDED_)
#define AFX_IMAGELISTHANDLER_H__1F9F96B6_3254_497F_9A44_2A04D93EB259__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageListHandler  
{
public:
	CImageListHandler();
	virtual ~CImageListHandler();

	CImageList & GetImageList() { return _ImageList ; }
	int			GetIconIndex( const char * Path ) ;

private:
	CImageList	_ImageList ;

	CMapStringToPtr _Extensions ;
};

#endif // !defined(AFX_IMAGELISTHANDLER_H__1F9F96B6_3254_497F_9A44_2A04D93EB259__INCLUDED_)
