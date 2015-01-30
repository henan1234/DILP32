// Script.h: interface for the CScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPT_H__437D6361_368B_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_SCRIPT_H__437D6361_368B_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "CommandLineFilter.h"

class	CProgressWnd ;

class CScript  
{
	public:
		CString MessageTermine( void );
		BOOL ScriptOk( void ) const;
		DWORD DiskSpace( void );

		CScript( const char * pFileName = 0 );
		virtual ~CScript();


		CString	GetApplicationName( void ) ;
		const CString	& GetInstallDir( void ) const ;
		void	SetInstallDir( const char * ) ;

		BOOL	ExecuteScript( CProgressWnd * pProgress ) ;

private:
	CString GetFullPath(const char * FilePath) ;
	void LogLastError( void );
	BOOL _Ok;
	static DWORD TailleRepertoire( const char * Repertoire );
	static DWORD TailleFichier( const char * NomFichier );
	BOOL Open( const CString & Line );
	BOOL EffaceRepertoire( const char * Rep );
	BOOL CopieRepertoire( const char * RepertoireSource, const char * RepertoireDestination );
	BOOL ExecuteLine( const CString & Line );
	void GetDefaultInstallDir( void );
	static CString ProchainMorceau(  const CString& Chaine, int & Debut, int & Fin );
	CString GetPart( const CString & String, int NoPart );
	static BOOL CorrectLine( CString &  Line );
	void ReadScript( CStdioFile & File );

	CStringList			_ScriptLines ;
	CCommandLineFilter	_Filter ;
	CString				_InstallDir ;

	BOOL	CreateDir( const CString & ) ;
	BOOL	CopyFile( const CString & ) ;
	BOOL	CopyDir( const CString & ) ;
	BOOL	CreateShortcut( const CString & ) ;
	BOOL	DeleteFile( const CString & ) ;
	BOOL	DeleteDir( const CString & ) ;
};

#endif // !defined(AFX_SCRIPT_H__437D6361_368B_11D1_AEF5_444553540000__INCLUDED_)
