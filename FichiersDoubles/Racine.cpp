// Racine.cpp: implementation of the CRacine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FichiersDoubles.h"
#include "Racine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRacine::CRacine()
{

}

CRacine::~CRacine()
{

}

//////////////////////////////////////////////////////////////////////
// Remplit une branche de l'arbre
//////////////////////////////////////////////////////////////////////
void CRacine::RemplitArbre(CTreeCtrl &Tree, HTREEITEM hParent, CImageListHandler &Imh, BOOL NonDuppliques)
{
	if ( ! NonDuppliques && ! ADesDuppliques())
		return ;

	if ( _Elements.GetSize() == 0 )
		return ;

	const int IndiceIcone	=	Imh.GetIconIndex( Path()) ;
	HTREEITEM	hRep =	Tree.InsertItem( Nom(), IndiceIcone, IndiceIcone, hParent, TVI_LAST ) ;
	Tree.SetItemData( hRep, (DWORD)this ) ;
	
	for ( int i = 0; i < _Elements.GetSize(); i++)
		{
		_Elements[i]->RemplitArbre( Tree, hRep, Imh, NonDuppliques ) ;
		}

	Tree.Expand( hRep, TVE_EXPAND ) ;
		
}
