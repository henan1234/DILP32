// MediaFile.h: interface for the CMediaFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIAFILE_H__0381E538_2441_4CC9_82FB_78B126481C14__INCLUDED_)
#define AFX_MEDIAFILE_H__0381E538_2441_4CC9_82FB_78B126481C14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMediaFile : public CStdioFile  
{
public:
	BOOL VerifieFormat( const CString & formatname );
	void WriteFormat( const CString & formatname );
	CMediaFile();
	virtual ~CMediaFile();

	CString	ReadString() ;
	void	WriteString( const CString & ) ;

};

#endif // !defined(AFX_MEDIAFILE_H__0381E538_2441_4CC9_82FB_78B126481C14__INCLUDED_)
