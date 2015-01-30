// Preferences.h: interface for the CPreferences class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREFERENCES_H__04039F04_2507_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_PREFERENCES_H__04039F04_2507_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPreferences  
{
public:
	static void ChangeMotDePasse( int NoPage ,const char * pPwd );
	static BOOL Protege( int NoPage );
	static void SupprimeImage( int NoImage );
	static void SetImageCourante( int No );
	static int GetNoImageCourante( void );
	static BOOL RenommeImage( int i , const char * pNom );
	static BOOL AjoutePage( void );
	static int NbPages( void );
	static CUIntArray _Protege;
	static BOOL PassWordProtected( int i );
	static const char * NomImage( int i );
	static CString NouveauNomPage( void );
	static COLORREF _CouleurTransparente;
	static CString ImageCourante( void );
	CPreferences();
	virtual ~CPreferences();

	static	const CString&	GetImageEditor() ;
	static	void	SetImageEditor( const char * ) ;
	static	void	SetDefaultImageEditor() ;

private:
	static BOOL SaisieMotDePasse( int i );
	static CString DecodePwd( const char * );
	static CString CodePwd( const char * );
	static CStringArray _MotsDePasses;
	static CUIntArray	_MotDePasseSaisi ;

	static int _NoImageCourante;
	static void SetPreference( const char *, int );
	static void SetPreference( const char *, const char * );
	static void SauvegardeNomsImages( void );
	static void SauveImage( const char * FileName, CBitmap & pBitmap );
	static CString NouveauNomImage( void );
	static CStringArray _PageNames;
	static void LitImages( void );
	static CStringArray _Images;
	static	CString	m_ImageEditor ;

	static	CString	GetSystemImageEditor() ;
	static	CString GetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName );
	static	void SetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName, const char * Value );
	static	void SetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName, int Value );

	static	int		GetPreference( const char * PreferenceName, int Default );
	static  CString GetPreference( const char * PreferenceName );
	static	void	CreerUneImage( void ) ;
};

#endif // !defined(AFX_PREFERENCES_H__04039F04_2507_11D1_AEF5_444553540000__INCLUDED_)
