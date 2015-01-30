// Element.cpp: implementation of the CElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "Element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC( CElement, CObject ) ;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "fileservices.h"
CElement::CElement()
{

}

CElement::~CElement()
{

}

void CElement::Scanne(const char *pChemin)
{
	_Path	=	pChemin ;
	_Nom	=	CFileServices::ExtractFileName( pChemin ) ;	
}


void CElement::RemplitListe(CListCtrl &Liste)
{

}

void CElement::SetAttributs(CDC &dc)
{
	dc.SetTextColor( GetSysColor( COLOR_WINDOWTEXT )) ;
}	


void CElement::AfficheProprietes( CWnd * pParent )
	{
	SHELLEXECUTEINFO Sei ;

	Sei.cbSize	=	sizeof( Sei ) ;
	Sei.fMask	=	SEE_MASK_NOCLOSEPROCESS | SEE_MASK_INVOKEIDLIST | SEE_MASK_FLAG_NO_UI ; 
	Sei.hwnd	=	*pParent ; 
	Sei.lpVerb	=	"properties" ; 
    Sei.lpFile	=	Path() ; 
	Sei.lpParameters	=	NULL ; 
    Sei.lpDirectory		=	NULL ; 
    Sei.nShow	=	SW_SHOW ; 
	Sei.hInstApp=	NULL ; 
 	Sei.lpIDList=	NULL ; 
    Sei.lpClass	=	NULL ; 
    Sei.hkeyClass=	NULL ; 
    Sei.dwHotKey= NULL; 
	Sei.hIcon	=	NULL ;

	ShellExecuteEx( &Sei ) ;
	}

void CElement::Ouvre(CWnd *pParent)
{
	SHELLEXECUTEINFO Sei ;

	Sei.cbSize	=	sizeof( Sei ) ;
	Sei.fMask	=	SEE_MASK_NOCLOSEPROCESS | SEE_MASK_INVOKEIDLIST | SEE_MASK_FLAG_NO_UI ; 
	Sei.hwnd	=	*pParent ; 
	Sei.lpVerb	=	"open" ; 
    Sei.lpFile	=	Path() ; 
	Sei.lpParameters	=	NULL ; 
    Sei.lpDirectory		=	NULL ; 
    Sei.nShow	=	SW_SHOW ; 
	Sei.hInstApp=	NULL ; 
 	Sei.lpIDList=	NULL ; 
    Sei.lpClass	=	NULL ; 
    Sei.hkeyClass=	NULL ; 
    Sei.dwHotKey= NULL; 
	Sei.hIcon	=	NULL ;

	ShellExecuteEx( &Sei ) ;

}

void CElement::FiniScan()
{

}

void CElement::Vide()
{

}
