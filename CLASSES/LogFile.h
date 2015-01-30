///////////////////////////////////////////////////////////////////////////////
// CLogFile
//	LogFile management class
///////////////////////////////////////////////////////////////////////////////
#ifndef _LOGFILE_H_
#define _LOGFILE_H_

class	CLogFile
	{
	public :
		// Constructor
		CLogFile(	const char * PathName	= "LOGFILE.TXT", LONG MaxSize =	10000 ) ;

		// Conditionnal log file : not written if the specified key is found
		CLogFile(	HKEY hRoot,
					const char * pRegistryKeyPath,
					const char * pRegistryKey,
					const char * pRegistryKeyValue,
					const char * PathName = "LOGFILE.TXT", LONG MaxSize = 10000 ) ,
		~CLogFile() ;
		
		// Use any of these value to insert an end of line
		typedef enum T_NEWLINE { newline, endline, endl, newl } ;

		CLogFile & operator	<< ( const char * ) ;
		CLogFile & operator << ( int ) ;
		CLogFile & operator << ( T_NEWLINE ) ;

		void	Write( const char * ) ;
		void	Write( const char *, const char * ) ;
		void	Write( const char *, int ) ;
		const	CString &	FileName( void ) const { return _FileName ; } ;

	private :
		BOOL		_WriteToFile ;
		static		CString GetFullPath( const char * Path );
		CStdioFile	_File ;
		CString		_FileName ;

		int			_Indentation ;
		BOOL		_NewLine ;

		friend class	CLogIndent ;
		BOOL		TryToOpen( const char * FileName, LONG MaxSize );

		// To indent the log file, used by CLogIndent
		void		FunctionEnter( )  ;
		void		FunctionExit() ;

		BOOL	RegistryKeyFound( HKEY hRoot, const char * pPath, const char * pValueName, const char * pValue ) ;
		void	OpenFile( const char * PathName, LONG MaxSize ) ;
	} ;

///////////////////////////////////////////////////////////////////////////////
// Use CLogIndent to indent the text in a log file.
// Symply instanciate a CLogIndent object in a function to indent
// The destructor will automatically deindent when exiting from the function
///////////////////////////////////////////////////////////////////////////////
class	CLogIndent
	{
	public :
		CLogIndent( CLogFile & ) ;
		~CLogIndent() ;

	private :
		CLogFile * _pLogFile ;
	} ;

// Use this macro if you don't want to choose a Logfile indentor name
#define INDENTLOG(L)		CLogIndent __Reserved_Log_Indent_Name__(L)
#endif

