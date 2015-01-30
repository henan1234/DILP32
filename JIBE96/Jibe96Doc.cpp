// Jibe96Doc.cpp : implementation of the CJibe96Doc class
//

#include "stdafx.h"
#include "resource.h"
#include "Jibe96.h"

#include "Jibe96Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJibe96Doc

IMPLEMENT_DYNCREATE(CJibe96Doc, CDocument)

BEGIN_MESSAGE_MAP(CJibe96Doc, CDocument)
	//{{AFX_MSG_MAP(CJibe96Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
//	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, CDocument::OnUpdatePasteMenu)
//	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, CDocument::OnUpdatePasteLinkMenu)
//	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, CDocument::OnUpdateObjectVerbMenu)
//	ON_COMMAND(ID_OLE_EDIT_CONVERT, CDocument::OnEditConvert)
//	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, CDocument::OnUpdateEditLinksMenu)
//	ON_COMMAND(ID_OLE_EDIT_LINKS, CDocument::OnEditLinks)
//	ON_UPDATE_COMMAND_UI(ID_OLE_VERB_FIRST, CDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/*BEGIN_DISPATCH_MAP(CJibe96Doc, CDocument)
	//{{AFX_DISPATCH_MAP(CJibe96Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()
*/
// Note: we add support for IID_IJibe96 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {F567F822-12A1-11CF-B124-0800096E0E20}
/*static const IID IID_IJibe96 =
{ 0xf567f822, 0x12a1, 0x11cf, { 0xb1, 0x24, 0x8, 0x0, 0x9, 0x6e, 0xe, 0x20 } };

BEGIN_INTERFACE_MAP(CJibe96Doc, CDocument)
	INTERFACE_PART(CJibe96Doc, IID_IJibe96, Dispatch)
END_INTERFACE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CJibe96Doc construction/destruction

CJibe96Doc::CJibe96Doc()
{
	// Use OLE compound files
//	EnableCompoundFile();

	// TODO: add one-time construction code here

//	EnableAutomation();

//	AfxOleLockApp();
}

CJibe96Doc::~CJibe96Doc()
{
//	AfxOleUnlockApp();
	const int Nb	=	NbIcones() ;

	for ( int i = 0; i < Nb; i++)
		delete _Icones[i] ;
}

BOOL CJibe96Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	SetPathName( "JIBE", FALSE );
			 
	_Side	=	ABE_RIGHT ;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CJibe96Doc serialization

void CJibe96Doc::Serialize(CArchive& ar)
{
	// Calling the base class CDocument enables serialization
	//  of the container document's COleClientItem objects.
	CDocument::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << _Side ;
	}
	else
	{
		ar >> _Side ;
	}

	_Icones.Serialize( ar ) ;
	
}

/////////////////////////////////////////////////////////////////////////////
// CJibe96Doc diagnostics

#ifdef _DEBUG
void CJibe96Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJibe96Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJibe96Doc commands

UINT CJibe96Doc::GetSide( void ) const
{
	return _Side ;
}

void CJibe96Doc::SetSide( UINT Side )
{
	ASSERT( Side	== ABE_RIGHT || Side == ABE_LEFT ||
		    Side	== ABE_TOP || Side == ABE_BOTTOM ) ;

	if ( _Side != Side )
		{
		_Side	=	Side ;
		SetModifiedFlag() ;
		}
}

CIcone * CJibe96Doc::GetIcone( int Indice )
{
	ASSERT( Indice >= 0 ) ;
	ASSERT( Indice < _Icones.GetSize()) ;
	CIcone	* pIcone	=	(CIcone*)_Icones[Indice] ;
	
	return pIcone ;
}

int CJibe96Doc::NbIcones( void ) const
{
	return _Icones.GetSize() ;
}

void CJibe96Doc::AjouteIcone( CIcone * pIcone )
{
	_Icones.SetAtGrow( _Icones.GetSize(), pIcone ) ;
	SetModifiedFlag() ;
}

void CJibe96Doc::SupprimeIcone( CIcone * pIcone )
{
	// Trouver l'indice de cette icone
	ASSERT_VALID( pIcone ) ;
	const int Nb	=	NbIcones() ;

	for ( int i = 0; i < Nb; i++)
		if ( _Icones.GetAt( i ) == pIcone )
			{
			_Icones.RemoveAt( i ) ;
			delete	pIcone ;
			SetModifiedFlag() ;
			UpdateAllViews( 0 ) ;
			return ;
			}
}

int CJibe96Doc::IndiceIcone( CIcone * pIcone )
{
	ASSERT_VALID( this ) ;
	ASSERT( pIcone ) ;
	const int Nb	=	NbIcones() ;

	for ( int i = 0; i < Nb; i++)
		if ( pIcone == _Icones[i] )
			return i ;

	return -1 ;
}

void CJibe96Doc::Echange( int I1, int I2 )
{
	ASSERT( I1 >= 0 && I1 < _Icones.GetSize()) ;
	ASSERT( I2 >= 0 && I2 < _Icones.GetSize()) ;
	CObject	*	pObject	=	_Icones[I1] ;
	_Icones[I1]		=	_Icones[I2] ;
	_Icones[I2]		=	pObject ;

	SetModifiedFlag() ;
	UpdateAllViews( 0 ) ;
}

BOOL CJibe96Doc::CanCloseFrame(CFrameWnd* pFrame) 
{
	CDocument::CanCloseFrame( pFrame ) ;
	return TRUE ;
}


void CJibe96Doc::OnCloseDocument() 
{
	const int Nb	=	NbIcones() ;

	for ( int i = 0; i < Nb; i++)
		{
		CIcone	* pIcone	=	(CIcone*)_Icones[i] ;
		if ( pIcone->Modifiee() )
			{
			SetModifiedFlag() ;
			OnSaveDocument("JIBE.Jib" ) ;
			break ;
			}
		}
			
	CDocument::OnCloseDocument();
}

BOOL CJibe96Doc::SaveModified() 
{
	if ( ! IsModified())
		{
		const int Nb	=	NbIcones() ;

		for ( int i = 0; i < Nb; i++)
			{
			CIcone	* pIcone	=	(CIcone*)_Icones[i] ;
			if ( pIcone->Modifiee() )
				{
				SetModifiedFlag() ;
				break ;
				}
			}
		}

	if ( IsModified())
		{
		if ( AfxMessageBox( IDS_SAVE_JIBE, MB_YESNO | MB_ICONQUESTION ) == IDYES )
			{
			DoFileSave() ;
			}
		}

	return TRUE ;
}

///////////////////////////////////////////////////////////////////////////////
// Insere l'icone I1 avant l'icone I2
///////////////////////////////////////////////////////////////////////////////
void CJibe96Doc::Insere( int I1, int I2 )
{
	if ( I1 == I2 )
		return ;

	
	CObject*	pO	=	_Icones[I1] ;
	_Icones.InsertAt( I2, pO ) ;

	if ( I2 < I1 )
		I1 ++ ;
	_Icones.RemoveAt( I1 ) ;

	SetModifiedFlag() ;
	UpdateAllViews( 0 ) ;
}
