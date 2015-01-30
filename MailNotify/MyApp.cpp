// MyApp.cpp: implementation of the CMyApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxsock.h>

#include "MyApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyApp::CMyApp()
{

}

CMyApp::~CMyApp()
{

}

BOOL CMyApp::InitInstance()
{
	if (! AfxSocketInit())
	{
		AfxMessageBox("Could not initialize Winsock");
		return 0 ;
	}


	return TRUE ;
}
