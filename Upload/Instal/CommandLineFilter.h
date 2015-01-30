///////////////////////////////////////////////////////////////////////////////
// CCommandLineFilter
//	Object used to parse a command line
///////////////////////////////////////////////////////////////////////////////
#ifndef _COMMANDLINEFILTER_H_
#define _COMMANDLINEFILTER_H_

#define SHELL_FOLDERS	"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell folders"
#define PROGRAM_FILES_FOLDERS_KEY	"Software\\Microsoft\\Windows\\CurrentVersion"
#define PROGRAM_FILES_FOLDERS_ENTRY	"ProgramFilesDir"
#define SETUP			"Software\\Microsoft\\Windows\\CurrentVersion\\Setup"

#define WINDOWS_DIR		"$WinDir"			//	repertoire de windows
#define SYSTEM_DIR		"$SysDir"			//	Repertoire systeme
#define STARTMENU_DIR	"$StartMenuDir"		//	repertoire du bouton de demarrage
#define PROGRAMFILES_DIR "$ProgramFilesDir"	//	repertoire sous lequel on installe les programmes
#define PROGRAMS_DIR	"$ProgramsDir"		//	repertoire des shortcuts programmes
#define STARTUP_DIR		"$StartupDir"		//	repertoire des shortcuts de depart automatique
#define DESKTOP_DIR		"$DesktopDir"		//	repertoire du bureau
#define INSTALL_DIR		"$InstallDir"		//	repertoire du bureau
#define PROGRAM_DIR		"$ProgramDir"		//	repertoire du programme
#define TEMP_DIR		"$TempDir"			//	repertoire pour fichiers temporaires

class	CCommandLineFilter
	{
	public :
		void Change( const CString & KeyWord, const CString & Remplace );
		CCommandLineFilter() ;
		CCommandLineFilter( const CStringArray & KeyWords, const CStringArray & Conversion ) ;

		CString	Decode( const char * ) ;
		void	Add( const CString & KeyWord, const CString & Conversion ) ;

	private :
		CStringArray	m_strKeyword ;
		CStringArray	m_strConversion ;

		static int GetInstallDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetDesktopDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetProgramsDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetProgramsFileDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetStartMenuDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetStartupDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetProgramDirectory(LPSTR buf,UINT sizebuf) ;
		static int GetTempDirectory(LPSTR buf,UINT sizebuf) ;
		static void ReplaceString( CString & Path, const char * pKeyWord, const CString & Substitute ) ;
	} ;

#endif
