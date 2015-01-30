// MosaiqueDoc.cpp : implementation of the CMosaiqueDoc class
//

#include "stdafx.h"
#include "Mosaique.h"
#include "image.h"
#include "MosaiqueDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueDoc

IMPLEMENT_DYNCREATE(CMosaiqueDoc, CDocument)

BEGIN_MESSAGE_MAP(CMosaiqueDoc, CDocument)
	//{{AFX_MSG_MAP(CMosaiqueDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueDoc construction/destruction

CMosaiqueDoc::CMosaiqueDoc()
{
	_NbLignes	=	3 ;
	_NbColonnes	=	3 ;
}

CMosaiqueDoc::~CMosaiqueDoc()
{
}

BOOL CMosaiqueDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMosaiqueDoc serialization

void CMosaiqueDoc::Serialize(CArchive& ar)
{
	CDocument::Serialize( ar ) ;


	if ( ar.IsStoring())
		{
		ar << (DWORD)_NbLignes ;
		ar << (DWORD)_NbColonnes ;

		const int NbImages	=	_Images.GetSize() ;

		CStringArray Chaines ;

		for ( int i = 0; i < NbImages; i++)
			Chaines.Add( GetImage(i)->Nom()) ;

		Chaines.Serialize( ar ) ;
		}
	else
		{
		DWORD d ;
		ar >> d ;
		_NbLignes = (int)d ;

		ar >> d ;
		_NbColonnes = (int)d ;

		CStringArray Chaines ;

		Chaines.Serialize( ar ) ;
		
		const int NbChaines	=	Chaines.GetSize() ;
		for ( int i = 0; i < NbChaines; i++)
			AjouteImage( Chaines[i] ) ;
		
		}
}

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueDoc diagnostics

#ifdef _DEBUG
void CMosaiqueDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMosaiqueDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMosaiqueDoc commands



void CMosaiqueDoc::OnCloseDocument() 
{
	const int Nb = _Images.GetSize() ;

	for ( int i = 0; i < Nb; i ++ )
		delete _Images[i] ;

	_Images.RemoveAll() ;

	CDocument::OnCloseDocument();
}

int CMosaiqueDoc::NbImages()
{
	return _Images.GetSize() ;
}

CImage * CMosaiqueDoc::GetImage(int i)
{
	return (CImage*)_Images[i] ;
}

BOOL CMosaiqueDoc::AjouteImage(const char * pNomImage)
{
		TRY
			{

			CImage*	pImage	=	new CImage( pNomImage ) ;
			_Images.Add( pImage ) ;
			SetModifiedFlag() ;
		
			return TRUE ;
			}
		CATCH ( CNotSupportedException, e )
			{
			return FALSE ;
			}
		END_CATCH
}

BOOL CMosaiqueDoc::AjouteImage( int i, const char * pNomImage)
{
		TRY
			{

			CImage*	pImage	=	new CImage( pNomImage ) ;
			_Images.InsertAt( i, pImage ) ;
			SetModifiedFlag() ;
		
			return TRUE ;
			}
		CATCH ( CNotSupportedException, e )
			{
			return FALSE ;
			}
		END_CATCH
}

int CMosaiqueDoc::NbLignes()
{
	return _NbLignes ;
}

int CMosaiqueDoc::NbColonnes()
{
	return _NbColonnes ;
}

void CMosaiqueDoc::NbColonnes(int NbColonnes)
{
	if ( NbColonnes > 0 )
		{
		_NbColonnes	=	NbColonnes ;
		SetModifiedFlag() ;
		}
}

void CMosaiqueDoc::NbLignes(int NbLignes)
{
	if ( NbLignes > 0 )
		{
		_NbLignes	=	NbLignes ;
		SetModifiedFlag() ;
		}
}

BOOL CMosaiqueDoc::PlusHaut(int Indice)
{
	if ( Indice <= 0 )
		return FALSE ;

	if ( Indice >= _Images.GetSize())
		return FALSE ;

	CImage	*	pImage1	= GetImage( Indice ) ;
	CImage  *	pImage2	= GetImage( Indice -1 ) ;

	_Images.SetAt( Indice, pImage2 ) ;
	_Images.SetAt( Indice - 1, pImage1 ) ;

	SetModifiedFlag() ;
	return TRUE ;
}

BOOL CMosaiqueDoc::PlusBas(int Indice)
{
	if ( Indice < 0 )
		return FALSE ;

	if ( Indice >= _Images.GetSize() - 1 )
		return FALSE ;

	CImage	*	pImage1	= GetImage( Indice ) ;
	CImage  *	pImage2	= GetImage( Indice + 1 ) ;

	_Images.SetAt( Indice, pImage2 ) ;
	_Images.SetAt( Indice +  1, pImage1 ) ;
	SetModifiedFlag() ;
	return TRUE ;
}

BOOL CMosaiqueDoc::Deplace(int IndiceDepart, int IndiceArrivee)
{
	CImage	*	pImage	= GetImage( IndiceDepart ) ;

	_Images.RemoveAt( IndiceDepart ) ;

	if ( IndiceDepart < IndiceArrivee )
		IndiceArrivee -- ;


	_Images.InsertAt( IndiceArrivee, pImage ) ;

	SetModifiedFlag() ;

	return TRUE ;	
}

void CMosaiqueDoc::SupprimeImage(int i)
{
	CImage * pImage	=	GetImage( i ) ;
	delete pImage ;

	_Images.RemoveAt(i) ;

	SetModifiedFlag() ;
}
