// Instal.h : main header file for the INSTAL application
//

#if !defined(AFX_INSTAL_H__57D6A0C3_2DB1_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_INSTAL_H__57D6A0C3_2DB1_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInstalApp:
// See Instal.cpp for the implementation of this class
//
class CScript ;

class CInstalApp : public CWinApp
{
public:
	CString ProgramName( void );
	static DWORD DiskSpace( void );
	static CString MessageTermine( void );
	static BOOL Install();
	static void ChangeInstallationDirectory( const char * );
	static CString GetInstallationDirectory( void );
	CInstalApp();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstalApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInstalApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CScript * _pScript;
	static DWORD Code( const char *  pChar );
	static void EcritClefShareware();
	static CString InstallationDirectory;
	static CString GetProgramsFileDirectory( void );
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_INSTAL_H__57D6A0C3_2DB1_11D1_AEF5_444553540000__INCLUDED_)
