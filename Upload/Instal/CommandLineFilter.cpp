///////////////////////////////////////////////////////////////////////////////
// CCommandLineFilter
//	Object used to parse a command line
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "winreg.h"
#include "CommandLineFilter.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////
CCommandLineFilter::CCommandLineFilter()
{
    char str[_MAX_PATH];

    // Trouver repertoire Windows pour remplacer $WinDir
	GetWindowsDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( WINDOWS_DIR );
    m_strConversion.Add( str );

	// Repertoire systeme pour remplacer $SysDir
	GetSystemDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( SYSTEM_DIR );
    m_strConversion.Add( str );

	// Repertoire Start Menu
	GetStartMenuDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( STARTMENU_DIR );
    m_strConversion.Add( str );

    // Repertoire des fichiers programmes
	GetProgramsDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( PROGRAMS_DIR );
    m_strConversion.Add( str );

    // Program file directory
    GetProgramsFileDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( PROGRAMFILES_DIR );
    m_strConversion.Add( str );

    // Start menu directory
    GetStartupDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( STARTUP_DIR );
    m_strConversion.Add( str );

    // Desktop directory
    GetDesktopDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( DESKTOP_DIR );
    m_strConversion.Add( str );

    // Installation directory
    GetInstallDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( INSTALL_DIR );
    m_strConversion.Add( str );

	// Program directory
	GetProgramDirectory( str, sizeof( str )) ;
	m_strKeyword.Add( PROGRAM_DIR ) ;
	m_strConversion.Add( str ) ;

	// Temp directory
	    // Installation directory
    GetTempDirectory( str, sizeof(str) ) ;
    m_strKeyword.Add( TEMP_DIR );
    m_strConversion.Add( str );

}

///////////////////////////////////////////////////////////////////////////////
// Decode
// Replace the keyword by the directories
///////////////////////////////////////////////////////////////////////////////
CString CCommandLineFilter::Decode( const char * pCodedPath )
{
	CString	Path( pCodedPath ) ;

    for ( int i = 0; i < m_strKeyword.GetSize(); i++ )
	    {
	    ReplaceString( Path, m_strKeyword[i], m_strConversion[i] ) ;
		}
	return Path ;
}

void CCommandLineFilter::ReplaceString( CString & Path, const char * pKeyWord, const CString & Substitute )
{
	ASSERT( pKeyWord ) ;
	ASSERT( pKeyWord[0] ) ;

	const	int	LongueurMotCle	=	lstrlen( pKeyWord ) ;
	int		Index	=	Path.Find( pKeyWord ) ;

	while ( Index != -1 )
		{
		// Index est l'indice du debut du mot cle, remplacer celui ci par
		// drive letter
		Path	=	Path.Left( Index )  + Substitute + Path.Mid( Index + LongueurMotCle ) ;
		Index	=	Path.Find( pKeyWord ) ;
		}

}


///////////////////////////////////////////////////////////////////////////////
// GetDesktop directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetDesktopDirectory(LPSTR buf,UINT sizebuf)
{
 HKEY hkey;
 LONG ret;
 DWORD cbData=sizebuf;
 DWORD dwType;

 ret=RegOpenKeyEx(HKEY_CURRENT_USER,SHELL_FOLDERS,0,KEY_READ,&hkey);
 if(ret==ERROR_SUCCESS)
  {
   ret=RegQueryValueEx(hkey,"Desktop", NULL,&dwType,(unsigned char*)buf,&cbData);
   if(ret!=ERROR_SUCCESS)
           return 0;
  }
 else return 0;
 return cbData;
}

///////////////////////////////////////////////////////////////////////////////
// Get programs directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetProgramsDirectory(LPSTR buf,UINT sizebuf)
{
 HKEY hkey;
 LONG ret;
 DWORD cbData=sizebuf;
 DWORD dwType;

 ret=RegOpenKeyEx(HKEY_CURRENT_USER,SHELL_FOLDERS,0,KEY_READ,&hkey);
 if(ret==ERROR_SUCCESS)
  {
   ret=RegQueryValueEx(hkey,"Programs", NULL,&dwType,(unsigned char*)buf,&cbData);
   if(ret!=ERROR_SUCCESS)
           return 0;
  }
 else return 0;
 return cbData;
}

///////////////////////////////////////////////////////////////////////////////
// Get "Program files" directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetProgramsFileDirectory(LPSTR buf,UINT sizebuf)
{
        HKEY hkey;
        LONG ret;
        DWORD cbData=sizebuf;
        DWORD dwType;

        ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,PROGRAM_FILES_FOLDERS_KEY,0,KEY_READ,&hkey);
        if(ret==ERROR_SUCCESS)
        {
            ret=RegQueryValueEx(hkey,PROGRAM_FILES_FOLDERS_ENTRY, NULL,&dwType,(unsigned char*)buf,&cbData);
            if (ret!=ERROR_SUCCESS)
                return 0;
        }
        else return 0;
        return cbData;
}


///////////////////////////////////////////////////////////////////////////////
// Get start menu directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetStartMenuDirectory(LPSTR buf,UINT sizebuf)
{				 
 HKEY hkey;
 LONG ret;
 DWORD cbData=sizebuf;
 DWORD dwType;

 ret=RegOpenKeyEx(HKEY_CURRENT_USER,SHELL_FOLDERS,0,KEY_READ,&hkey);
 if(ret==ERROR_SUCCESS)
  {
   ret=RegQueryValueEx(hkey,"Start Menu", NULL,&dwType,(unsigned char*)buf,&cbData);
   if(ret!=ERROR_SUCCESS)
           return 0;
  }
 else return 0;
 return cbData;
}

int CCommandLineFilter::GetProgramDirectory( LPSTR buf, UINT sizebuf )
{
	char	Buffer[ _MAX_PATH ] ;
	GetModuleFileName( AfxGetInstanceHandle(), Buffer, sizeof( Buffer )) ;

	char Drive[ _MAX_DRIVE ] ;
	char Path[ _MAX_PATH ] ;
	_splitpath(Buffer, Drive, Path, 0, 0 ) ;

	_makepath(  buf, Drive, Path, NULL, NULL ) ;

	if ( buf[ lstrlen( buf )-1] == '\\' )
		buf[ lstrlen( buf ) - 1 ] = 0 ;

	return lstrlen( buf ) ;
}
 

///////////////////////////////////////////////////////////////////////////////
// Get automatic startup directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetStartupDirectory(LPSTR buf,UINT sizebuf)
{				 
 HKEY hkey;
 LONG ret;
 DWORD cbData=sizebuf;
 DWORD dwType;

 ret=RegOpenKeyEx(HKEY_CURRENT_USER,SHELL_FOLDERS,0,KEY_READ,&hkey);
 if(ret==ERROR_SUCCESS)
  {
   ret=RegQueryValueEx(hkey,"Startup", NULL,&dwType,(unsigned char*)buf,&cbData);
   if(ret!=ERROR_SUCCESS)
           return 0;
  }
 else return 0;
 return cbData;
}

///////////////////////////////////////////////////////////////////////////////
// Get automatic startup directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetTempDirectory(LPSTR buf,UINT sizebuf)
	{				 
	const char * pTemp = getenv( "TEMP" ) ;

	if ( ! pTemp )
		{
		buf[0] = 0 ;
		return 0 ;
		}
 
	strncpy( buf, pTemp,  sizebuf ) ;
	buf[ sizebuf-1 ] = 0 ;

	return strlen( buf ) ;
	}

///////////////////////////////////////////////////////////////////////////////
// Get automatic startup directory
///////////////////////////////////////////////////////////////////////////////
int CCommandLineFilter::GetInstallDirectory(LPSTR buf,UINT sizebuf)
{				 
 HKEY hkey;
 LONG ret;
 DWORD cbData=sizebuf;
 DWORD dwType;

 ret=RegOpenKeyEx(HKEY_LOCAL_MACHINE,SETUP,0,KEY_READ,&hkey);
	if(ret==ERROR_SUCCESS)
		{
		ret=RegQueryValueEx(hkey,"SourcePath", NULL,&dwType,(unsigned char*)buf,&cbData);
		if(ret!=ERROR_SUCCESS)
		   return 0;
		}
 else
		return 0;

 return cbData;
}

void	CCommandLineFilter::Add( const CString & KeyWord, const CString & Conversion )
	{
	ASSERT( m_strKeyword.GetSize() == m_strConversion.GetSize() ) ;
	m_strKeyword.Add( KeyWord ) ;
	m_strConversion.Add( Conversion ) ;
	ASSERT( m_strKeyword.GetSize() == m_strConversion.GetSize() ) ;
	}

void CCommandLineFilter::Change(const CString & KeyWord, const CString & Remplace)
{
	ASSERT( m_strConversion.GetSize() == m_strKeyword.GetSize()) ;

	// Recherche du mot cle
	for ( int i = 0; i < m_strKeyword.GetSize(); i++)
		if ( KeyWord == m_strKeyword[i] )
			{
			// Remplacer la chaine de conversion
			m_strConversion[i]	=	Remplace ;
			return ;
			}

	// Mot cle pas trouve, on le remplace
	m_strConversion.Add( Remplace ) ;
	m_strKeyword.Add( KeyWord ) ;

	ASSERT( m_strConversion.GetSize() == m_strKeyword.GetSize()) ;
}
