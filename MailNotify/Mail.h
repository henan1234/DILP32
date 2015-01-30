// Mail.h: interface for the CMail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAIL_H__69F0E291_9791_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_MAIL_H__69F0E291_9791_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMail  
{
public:
	CMail( const CString &	MsgContent );
	virtual ~CMail();

	const CString& From() const { return _From ; }
	const CString& Subject() const { return _Subject ; } 
	const CString& Content() const { return _Content ; }

	void	Acknowledge( BOOL b )	{ _Acknowledged	=	b ; }
	BOOL	Acknowledged() const { return _Acknowledged ; }

	const CString & Id() const { return _MessageId ; }
private:
	CString DecodeBody( const CString & Body );
	CString ChercheLigneNonVide( const CString & Chaine );
	CString ExtractContent( const CString & MsgContent );
	static void Iso( CString & );
	static CString ExtraitFrom( const CString & From );
	static CString Extract( const CString & Content, const CString & Keyword ) ;

	CString	_From ;
	CString	_Subject ;	
	CString	_Content ;
	BOOL	_Acknowledged ;
	CString	_MessageId ;
};

#endif // !defined(AFX_MAIL_H__69F0E291_9791_11D3_A61A_00A04B04180E__INCLUDED_)
