// Restriction.cpp: implementation of the CRestriction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Restriction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CRestriction::~CRestriction()
{

}


BOOL CRestriction::Convient( CMail * pMail )
	{
	return TRUE ;
	}