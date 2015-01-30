// AutoSummarizeDoc.cpp : implementation of the CAutoSummarizeDoc class
//

#include "stdafx.h"
#include "AutoSummarize.h"

#include "AutoSummarizeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char Lettres[]		= " ,;.(){}\"'~&=+-:?abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZçéèàùìòâêûîôäëüïöÿ" ;
static const char SansAccents[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
static const char Voyelles[]	= "aeiouyAEIOUYéèàùìòâêûîôäëüïö" ;
static const char Accentuees[]	= "éèàùìòâêûîôäëüïö" ;

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeDoc

IMPLEMENT_DYNCREATE(CAutoSummarizeDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoSummarizeDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoSummarizeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeDoc construction/destruction

CAutoSummarizeDoc::CAutoSummarizeDoc()
{
	// TODO: add one-time construction code here

}

CAutoSummarizeDoc::~CAutoSummarizeDoc()
{
}

BOOL CAutoSummarizeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeDoc serialization

void CAutoSummarizeDoc::Serialize(CArchive& ar)
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
// CAutoSummarizeDoc diagnostics

#ifdef _DEBUG
void CAutoSummarizeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoSummarizeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoSummarizeDoc commands

BOOL CAutoSummarizeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{

	HANDLE	hFile		=	CreateFile( lpszPathName,
										GENERIC_READ,
										FILE_SHARE_READ,
										NULL, 
										OPEN_EXISTING, 
										FILE_FLAG_SEQUENTIAL_SCAN,
										NULL ) ;


	if ( hFile == INVALID_HANDLE_VALUE )
		return FALSE ;

	DWORD TailleHigh ;
	// Les premiers megas nous suffiront largement
	DWORD Taille =	GetFileSize( hFile, &TailleHigh ) ;
	
	HANDLE	hMapping	=	CreateFileMapping(hFile, NULL, PAGE_READONLY, (DWORD)(Taille >> (_int64)32), (DWORD)Taille,
											  NULL ) ;
	if ( ! hMapping )
		{
		CloseHandle( hFile ) ;
		return FALSE ;
		}

	LPVOID pFile = MapViewOfFile( hMapping, FILE_MAP_READ, 0, 0, 0 ) ;
	if ( ! pFile )
		{
		CloseHandle( hMapping ) ;
		CloseHandle( hFile ) ;
		return FALSE ;
		}

	ExtraitMots( (LPSTR)pFile, Taille ) ;

	UnmapViewOfFile( pFile ) ;
	CloseHandle( hMapping ) ;
	CloseHandle( hFile ) ;

	return TRUE;
}

void CAutoSummarizeDoc::ExtraitMots(LPSTR pMots, DWORD Taille)
{
	DWORD Indice =	0 ;


	while ( Indice < Taille )
		{
		// Cherche la premiere lettre
		while ( (Indice < Taille) && (!strchr( Lettres, *pMots ) || (!(*pMots))))
			{
			pMots ++ ;
			Indice ++ ;
			}

		if ( Indice < Taille )
			{
			CString Mot ;

			// Accumule les lettres jusqu'a trouver une 'non lettre'
			while ((Indice < Taille ) && (*pMots) && strchr( Lettres, *pMots ))
				{
				Mot += *pMots ;
				pMots ++ ;
				Indice ++ ;
				}

			// Ajoute le mot dans la liste
			if ( Mot.GetLength() > 1 )
				// Elimine les mots vraisemblablement pas valides
				if ( AuMoinsUnSansAccent( Mot ))
					if ( ! LonguesSequences( Mot ))
						if ( UneVoyelle( Mot ))
							{
							_Mots.Add( Mot ) ;
							if ( _Mots.GetSize() > 200 )
								return ;
							}
			}
		}

}

BOOL CAutoSummarizeDoc::AuMoinsUnSansAccent(const CString &Mot)
{
	for ( int i = 0; i < Mot.GetLength(); i++)
		{
		if ( strchr( SansAccents, Mot[i] ))
			return TRUE ;
		}
	return FALSE ;
}

BOOL CAutoSummarizeDoc::LonguesSequences(const CString &Mot)
{
	const int Longueur	=	Mot.GetLength() ;
	for ( int iDepart	=	0; iDepart < Longueur-1; iDepart ++ )
		{
		if ( Mot[iDepart] == Mot[iDepart+1])
			{
			// Debut d'une sequence, quelle est sa longueur ?
			for ( int iFin = iDepart + 1; iFin < Longueur; iFin++)
				{
				if ( Mot[iDepart] != Mot[iFin] )
					// On n'est plus dans la sequence
					break ;

				if ( iDepart + 1 < iFin )
					// Sequence trop longue ! 3 lettres identiques a la suite, c'est louche
					return TRUE ;
				}
			}
		}
	return FALSE ;
}

BOOL CAutoSummarizeDoc::UneVoyelle(const CString &Mot)
{
	return Mot.FindOneOf( Voyelles ) != -1 ;
}

