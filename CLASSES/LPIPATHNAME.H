///////////////////////////////////////////////////////////////////////////////
// CLPIPathName
//	Facilite beaucoup le maniement des noms de fichiers et chemins
///////////////////////////////////////////////////////////////////////////////
#ifndef __LPIPATHNAME_H__
#define __LPIPATHNAME_H__

class CLPIPathName : public CObject
{
	DECLARE_SERIAL( CLPIPathName ) ;
	
   ///////////////////////////////////////////////////////////////////////////	
	public:
	///////////////////////////////////////////////////////////////////////////	
		// ======================================================= Constructors
		// Empty file name
		CLPIPathName() ;                          			
		// From a string ( ex : "C:\ONE\TWO\THREE.XXX"
		CLPIPathName( const CString & ) ;
		CLPIPathName( LPCSTR	) ;
		// Copy constructor
		CLPIPathName( const CLPIPathName & ) ;
		// From path components
		CLPIPathName( const CString & PathName, const CString & FileName, const CString & Extension ) ;
					
							
		// ==================================== Access to parts of the pathname
		// Path Name, read & write
		CString		Path( void ) const ;					// "C:\ONE\TWO"
		BOOL			Path( const CString & ) ;
		// Search file in PATH directories
		BOOL		SearchPath( const CString & = "PATH" ) ;			//could be INCLUDE, LIB...
		      
		// File name, read & write
		const CString 	FileName( void ) const ;			// "THREE"
		BOOL			FileName( const CString & ) ;
		
		// Extension, read & write
		const CString 	Extension( void ) const ;			// "XXX"
		BOOL			Extension( const CString & ) ;
		
		// Filename with Extension, read. Use FileName to write
		CString		GetFileWithExtension() const ;				// "THREE.XXX"
		
		void		GetPathComponents( CStringList & ) const ;// "C:", "ONE", "TWO"
					
		BOOL		SetEmptyExtension( void ) ;					// Set empty extension
			        
		// Move down one level
		BOOL		Down( const CString & ) ;		// + "FOUR" -> C:\ONE\TWO\FOUR\THREE.XXX
		// Move up the the parent directory
		BOOL		Up() ;								// -> C:\ONE\THREE.XXX
					
		// ============================================== Check file existance
		BOOL		FileExist( void ) const ;
		
		// ========================================= Check directory existance
		BOOL		DirectoryExist( void ) const ;
					
		// ======================================================= Affectation
		const	CLPIPathName &	operator =( const CLPIPathName & ) ;
		const	CLPIPathName &	operator =( const CString & ) ;
		const	CLPIPathName &	operator =( LPCSTR ) ;
					
		// ======================================================= Comparison
		int				operator ==( const CLPIPathName & ) const ;
		int				operator !=( const CLPIPathName & ) const ;
					
		// Convertion en chaines de caracteres
		operator CString () const ;
		operator	LPCTSTR() const ;

		// Set of valid characters for file names
		static const CString	VALID_CHARACTERS ;			// Set of valid characters for a file name
		static const char		PATH_SEPARATOR ;			// separator for path components "\"
		static const char		EXTENSION_SEPARATOR ;		// separtor for extension "."
		
		// Sizes
		static const int		MAX_FILE_LENGTH ;			// 8
		static const int		MAX_EXTENSION_LENGTH ;		// 3
		
#ifdef _DEBUG
		virtual void Dump( CDumpContext & dc ) const ;
		virtual void AssertValid() const ;
#endif
   
   virtual void Serialize( CArchive & ar ) ;
   
	///////////////////////////////////////////////////////////////////////////	
	protected :
	///////////////////////////////////////////////////////////////////////////	
		// String parts extractions :
		void	SepareChemin( CString &, CString &, CString & ) const ;
		void	ColleMorceaux( const CString &, const CString &, const CString &,
							   BOOL	ForceExtension = TRUE ); 
	   
	///////////////////////////////////////////////////////////////////////////	
	private :
	///////////////////////////////////////////////////////////////////////////	
		CString			_PathFileName ;
};
                  
#endif
