// DumpDoc.cpp : implementation of the CDumpDoc class
//

#include "stdafx.h"
#include "Dump.h"

#include "DumpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDumpDoc

IMPLEMENT_DYNCREATE(CDumpDoc, CDocument)

BEGIN_MESSAGE_MAP(CDumpDoc, CDocument)
	//{{AFX_MSG_MAP(CDumpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDumpDoc construction/destruction

CDumpDoc::CDumpDoc()
{
	_NbOctetsParLigne	=	16 ;
	_NbOctets	=	0 ;
	_pOctets	=	0 ;
}

CDumpDoc::~CDumpDoc()
{
}

BOOL CDumpDoc::OnNewDocument()
{
	return FALSE;

}



/////////////////////////////////////////////////////////////////////////////
// CDumpDoc serialization

void CDumpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDumpDoc diagnostics

#ifdef _DEBUG
void CDumpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDumpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDumpDoc commands

int CDumpDoc::NbLignes() const
{
	return (int)((_NbOctets+_NbOctetsParLigne-1) / _NbOctetsParLigne) ;
}

// retourne la longueur d'une ligne en caracteres
int CDumpDoc::LongueurLigne()
{
	return _NbOctetsParLigne * ( 2 //		representationb hexa
								+ 1 //		espace entre hexa
								+ 1 )	//		affichage du caractere ANSI
								+ 8	//		Adresse dans le fichier
								+ 2; // Espace
}

BOOL CDumpDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	// Creation d'un "memory mapped file"
	_hFile	=	CreateFile( lpszPathName,
							GENERIC_READ,
							FILE_SHARE_READ,
							NULL,
							OPEN_EXISTING,
							0,
							NULL ) ;

	if ( _hFile == INVALID_HANDLE_VALUE )
		return FALSE ;

	DWORD	HighWord ;
	_NbOctets	=	GetFileSize( _hFile, &HighWord ) ;

	if ( HighWord )
		{
		CloseHandle( _hFile ) ;
		AfxMessageBox( "Fichier trop gros", MB_ICONSTOP | MB_OK ) ;
		return FALSE ;
		}

	_hMapping	=	CreateFileMapping( _hFile, NULL,  PAGE_READONLY, 0, _NbOctets, NULL ) ;

	if ( _hMapping == NULL )
		{
		CloseHandle( _hFile ) ;
		return FALSE ;
		}

	_pOctets	= (LPBYTE)MapViewOfFileEx( _hMapping, FILE_MAP_READ, 0, 0, 0, 0 ) ;
	ASSERT( _pOctets ) ;

	
	return TRUE;
}

void CDumpDoc::OnCloseDocument() 
{
	if ( _pOctets )
		{
		UnmapViewOfFile( _pOctets ) ;

		if ( _hMapping )
			CloseHandle( _hMapping ) ;

		CloseHandle( _hFile ) ;
		}

	CDocument::OnCloseDocument();
}

CString CDumpDoc::GetLigne(int NoLigne)
{
	CString	Ligne ;
	CString	Hexa ;
	CString	Ansi ;

	LPBYTE	pOctet	=	_pOctets	+ ( NoLigne * _NbOctetsParLigne ) ;
	if ( pOctet >= _pOctets + _NbOctets )
		return "" ;

	DWORD	NoOctet=	0 ;

	while ( (NoOctet < _NbOctetsParLigne) &&
			(pOctet < (_pOctets + _NbOctets)) )
		{
		Hexa	+= ' ' ;
		Hexa	+= OctetHexa( *pOctet ) ;

		Ansi	+= RepresentationAnsi( *pOctet ) ;

		NoOctet ++ ;
		pOctet ++ ;
		}

	Ligne.Format( "%06lX %s %s", (long)(NoLigne*_NbOctetsParLigne),
								(const char *)Hexa, (const char *)Ansi ) ;

	return Ligne ;
}


CString CDumpDoc::OctetHexa(BYTE Octet)
{
	CString Chaine ;

	Chaine.Format( "%02X", (int)Octet ) ;

	return Chaine ;
}

CString CDumpDoc::RepresentationAnsi(BYTE Octet)
{
	if ( Octet )
		return CString( Octet ) ;
	else
		return CString( '0' )  ;
}

