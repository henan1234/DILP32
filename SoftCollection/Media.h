// Media.h: interface for the CMedia class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIA_H__6DA14354_8030_4EDB_A0E3_BF935B77645D__INCLUDED_)
#define AFX_MEDIA_H__6DA14354_8030_4EDB_A0E3_BF935B77645D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "scanningdlg1.h"
class	CElement ;

class CMedia  
{
public:
	void Recherche( const CString & Texte, const CString & Attribut, CArray<CElement*, CElement*> & );
	BOOL ChargeInfos( const CString & NomFichier );
	BOOL Charge( const CString & NomFichier );
	void Vide();
	void Sauve( const CString & NomFichier );
	CElement * TrouveElement( HTREEITEM hItem );
	void Remplit( CTreeCtrl & Tree );
	BOOL Scan( const CString & Media );
	CMedia();
	virtual ~CMedia();
	const CString & MediaPath() const { return _MediaPath ; }
	void MediaPath( const CString & Path ) { _MediaPath = Path ; }

	const CString & MediaName() const { return _MediaName ; }
	void MediaName( const CString & Name ) { _MediaName	=	Name ; }

private:
	BOOL ScanneFirstDirectory( const CString & Path );
	BOOL AjouteElement( CElement * pElement );

	CString	_MediaPath ;
	CString _MediaName ;

	CArray<CElement*, CElement *> _TableauElements ;
	CString		_NomFichier ;

	BOOL _Vide ;
};

#endif // !defined(AFX_MEDIA_H__6DA14354_8030_4EDB_A0E3_BF935B77645D__INCLUDED_)
