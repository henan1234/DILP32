// Option.cpp: implementation of the COption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ecogravitation.h"
#include "Option.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COption::COption( const TCHAR * pNom, BOOL bModifiableShareware )
{
	_Nom	=	pNom ;
	_ModifiableShareware = bModifiableShareware ;
}

COption::~COption()
{

}
