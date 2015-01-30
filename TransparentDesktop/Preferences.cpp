// Preferences.cpp: implementation of the CPreferences class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <io.h>
#include "Transparentdesktop.h"
#include "Preferences.h"
#include "olectl.h"
#include "SaisieMotDePasse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PREFERENCES	"Software\\Lucien PILLONI\\Transparent Desktop"

// Rubriques dans la registry
#define IMAGE_EDITOR	"Favorite Image Editor"
#define NB_FichiersImages		"Images number"
#define AVOID_16_BITS	"Avoid 16 bits images"
#define IMAGE_COURANTE	"Current image"
#define PROTEGEE		"Password%d"
#define MOT_DE_PASSE	"Pwd%d"
#define DEJA_EDITE		"Note edited"

#define MAXWRITE	1024

CString	CPreferences::m_ImageEditor	=	CPreferences::GetPreference( IMAGE_EDITOR ) ;

CStringArray	CPreferences::_FichiersImages ;		// Nom des fichiers
CStringArray	CPreferences::_PageNames ;	// Nom affichable des pages
COLORREF		CPreferences::_CouleurTransparente	=	RGB(0,0,0) ;
CUIntArray		CPreferences::_Protege ;
int				CPreferences::_NoImageCourante ;
CStringArray	CPreferences::_MotsDePasses ;
CUIntArray		CPreferences::_MotDePasseSaisi ;

PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp)
	{ 
    BITMAP bmp; 
    PBITMAPINFO pbmi; 
    WORD    cClrBits; 
 
	ASSERT( hBmp ) ;

    /* Retrieve the bitmap's color format, width, and height. */ 
     if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
        return 0 ;
 
     /* Convert the color format to a count of bits. */ 
     cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
 
    if (cClrBits == 1) 
        cClrBits = 1; 
    else if (cClrBits <= 4) 
        cClrBits = 4; 
    else if (cClrBits <= 8) 
        cClrBits = 8; 
    else if (cClrBits <= 16) 
        cClrBits = 16; 
    else if (cClrBits <= 24) 
        cClrBits = 24; 
    else 
        cClrBits = 32; 
 
    /* 
     * Allocate memory for the BITMAPINFO structure. (This structure 
     * contains a BITMAPINFOHEADER structure and an array of RGBQUAD data 
     * structures.) 
     */ 
 
    if (cClrBits != 24) 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER) + 
                    sizeof(RGBQUAD) * (2^cClrBits)); 
 
    /* 
     * There is no RGBQUAD array for the 24-bit-per-pixel format. 
     */ 
 
    else 
         pbmi = (PBITMAPINFO) LocalAlloc(LPTR, 
                    sizeof(BITMAPINFOHEADER)); 
 
 
 
    /* Initialize the fields in the BITMAPINFO structure. */ 
 
    pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
    pbmi->bmiHeader.biWidth = bmp.bmWidth; 
    pbmi->bmiHeader.biHeight = bmp.bmHeight; 
    pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
    pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
    if (cClrBits < 24) 
        pbmi->bmiHeader.biClrUsed = 2^cClrBits; 
 
 
    /* If the bitmap is not compressed, set the BI_RGB flag. */ 
 
    pbmi->bmiHeader.biCompression = BI_RGB; 
 
    /* 
     * Compute the number of bytes in the array of color 
     * indices and store the result in biSizeImage. 
     */ 
 
    pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) /8 
                                  * pbmi->bmiHeader.biHeight 
                                  * cClrBits; 
 
    /* 
     * Set biClrImportant to 0, indicating that all of the 
     * device colors are important. 
     */ 
 
    pbmi->bmiHeader.biClrImportant = 0; 
 
    return pbmi; 
	}

void CreateBMPFile(LPCTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC) 
 { 
 
    HANDLE hf;                  /* file handle */ 
    BITMAPFILEHEADER hdr;       /* bitmap file-header */ 
    PBITMAPINFOHEADER pbih;     /* bitmap info-header */ 
    LPBYTE lpBits;              /* memory pointer */ 
    DWORD dwTotal;              /* total count of bytes */ 
    DWORD cb;                   /* incremental count of bytes */ 
    BYTE *hp;                   /* byte pointer */ 
    DWORD dwTmp; 
 
 
	ASSERT( pszFile ) ;
	ASSERT( pbi ) ;
	ASSERT( hBMP ) ;
	ASSERT( hDC ) ;

    pbih = (PBITMAPINFOHEADER) pbi; 
    lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);
    if (!lpBits) 
         return ; 
 
    /* 
     * Retrieve the color table (RGBQUAD array) and the bits 
     * (array of palette indices) from the DIB. 
     */ 
 
    if (!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, 
                   lpBits, pbi, DIB_RGB_COLORS)) 
        return ;
 
    /* Create the .BMP file. */ 
 
    hf = CreateFile(pszFile, 
                   GENERIC_READ | GENERIC_WRITE, 
                   (DWORD) 0, 
                   (LPSECURITY_ATTRIBUTES) NULL, 
                   CREATE_ALWAYS, 
                   FILE_ATTRIBUTE_NORMAL, 
                   (HANDLE) NULL); 
 
    if (hf == INVALID_HANDLE_VALUE) 
        return ;
 
    hdr.bfType = 0x4d42;        /* 0x42 = "B" 0x4d = "M" */ 
 
    /* Compute the size of the entire file. */ 
 
    hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                 pbih->biSize + pbih->biClrUsed 
                 * sizeof(RGBQUAD) + pbih->biSizeImage); 
 
    hdr.bfReserved1 = 0; 
    hdr.bfReserved2 = 0; 
 
    /* Compute the offset to the array of color indices. */ 
 
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + 
                    pbih->biSize + pbih->biClrUsed 
                    * sizeof (RGBQUAD); 
 
    /* Copy the BITMAPFILEHEADER into the .BMP file. */ 
 
    if (!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), 
       (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
       return ;
 
    /* Copy the BITMAPINFOHEADER and RGBQUAD array into the file. */ 
 
    if (!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                  + pbih->biClrUsed * sizeof (RGBQUAD), 
                  (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
       return ;
 
    /* Copy the array of color indices into the .BMP file. */ 
 
    dwTotal = cb = pbih->biSizeImage; 
    hp = lpBits;
    while (cb > MAXWRITE) 
		{ 
        if (!WriteFile(hf, (LPSTR) hp, (int) MAXWRITE, (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
                return ;
         cb-= MAXWRITE; 
         hp += MAXWRITE; 
		} 
    if (!WriteFile(hf, (LPSTR) hp, (int) cb, 
         (LPDWORD) &dwTmp, (LPOVERLAPPED) NULL)) 
           return ;
 
    /* Close the .BMP file. */ 
 
    if (!CloseHandle(hf)) 
           return ;
 
    /* Free memory. */

    GlobalFree((HGLOBAL)lpBits);
} 
 
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPreferences::CPreferences()
{

}

CPreferences::~CPreferences()
{

}


///////////////////////////////////////////////////////////////////////////////
// Lit une preference chaine
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::GetPreference(const char * PreferenceName )
{
	ASSERT( AfxIsValidString( PreferenceName )) ;
	return GetRegistryValue( HKEY_CURRENT_USER, PREFERENCES, PreferenceName );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int CPreferences::GetPreference(const char * PreferenceName, int Default )
{
	ASSERT( AfxIsValidString( PreferenceName )) ;

	int Preference	=	Default ;

	HKEY	hKey ;
	if ( RegOpenKeyEx(HKEY_CURRENT_USER, PREFERENCES, 0, KEY_READ, &hKey )
		 != ERROR_SUCCESS )
		 return Preference ;

	DWORD	Buffer ;
	DWORD	Taille	=	sizeof( Buffer ) ;
	DWORD Type	=	REG_DWORD ;
	if ( RegQueryValueEx( hKey, PreferenceName, 0, &Type, (LPBYTE)&Buffer, &Taille )
		 == ERROR_SUCCESS )
		{
		Preference	=	(int)Buffer ;
		}

	RegCloseKey( hKey ) ;

	return Preference ;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::GetRegistryValue(HKEY hRoot, const char * Path, const char * ValueName )
{
	ASSERT( AfxIsValidString( Path )) ;
	ASSERT( !ValueName || AfxIsValidString( ValueName )) ;

	CString Value ;

	HKEY	hKey ;
	if ( RegOpenKeyEx(hRoot, Path, 0, KEY_READ, &hKey )
		 != ERROR_SUCCESS )
		 return Value ;

	char Buffer[1024] ;
	DWORD	Taille	=	sizeof( Buffer ) ;
	DWORD Type	=	REG_SZ ;

	if ( RegQueryValueEx( hKey, ValueName, 0, &Type, (LPBYTE)&Buffer, &Taille )
		 == ERROR_SUCCESS )
		{
		Value	=	Buffer ;
		}

	RegCloseKey( hKey ) ;

	return Value ;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::GetSystemImageEditor()
{
	CString Path	=	GetRegistryValue( HKEY_LOCAL_MACHINE,
										  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\MSPAINT.EXE",
										  NULL ) ;

	if ( ! Path.IsEmpty())
		return Path ;

	char	Dir[_MAX_DIR ] ;
	GetCurrentDirectory( sizeof( Dir ), Dir ) ;

	char	Buffer[_MAX_PATH] ;
	CString	Image	=	FichierImageCourante() ;

	FindExecutable( Image, Dir, Buffer ) ;
	
	return Buffer ;
}

///////////////////////////////////////////////////////////////////////////////
// Retourne le chemin vers l'editeur d'images
///////////////////////////////////////////////////////////////////////////////
const CString & CPreferences::GetImageEditor()
	{
	if ( m_ImageEditor.IsEmpty())
		m_ImageEditor	=	GetSystemImageEditor() ;

	return m_ImageEditor ;
	}

///////////////////////////////////////////////////////////////////////////////
// Retrouve l'image courante.
// Cree une image s'il n'en existe encore aucune
// Demande le mot de passe si besoin
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::FichierImageCourante()
{
	if ( _FichiersImages.GetSize() == 0 )
		LitImages() ;

	if ( _FichiersImages.GetSize() == 0 )
		CreerUneImage() ;

	ASSERT( _FichiersImages.GetSize() > 0 ) ;

	if ( _NoImageCourante >= _FichiersImages.GetSize())
		_NoImageCourante	=	_FichiersImages.GetSize()-1 ;

	if ( SaisieMotDePasse( _NoImageCourante ))
		return	_FichiersImages[_NoImageCourante] ;
	else
		return "" ;
}


///////////////////////////////////////////////////////////////////////////////
// Lit les images dans la registry
///////////////////////////////////////////////////////////////////////////////
void CPreferences::LitImages()
{
	const int NbImages	=	GetPreference( NB_FichiersImages, 0 ) ;

	for ( int i = 0; i < NbImages; i++ )
		{
		CString	PreferenceName ;
		PreferenceName.Format( "Page%d", i ) ;

		CString PageName	=	GetPreference( PreferenceName ) ;

		PreferenceName.Format( "Image%d", i ) ;
		CString ImageName	=	GetPreference( PreferenceName ) ;

		PreferenceName.Format( PROTEGEE, i ) ;
		BOOL	Protege	=	GetPreference( PreferenceName, FALSE ) ;


		PreferenceName.Format( MOT_DE_PASSE, i ) ;
		CString	Password	=	DecodePwd( GetPreference( PreferenceName ) ) ;

		if ( ! ImageName.IsEmpty())
			{
			_FichiersImages.Add( ImageName ) ;
			_PageNames.Add( PageName ) ;
			_Protege.Add( Protege ) ;
			_MotsDePasses.Add( Password ) ;
			_MotDePasseSaisi.Add( FALSE ) ;
			}
		}

	_NoImageCourante	=	GetPreference( IMAGE_COURANTE, 0 ) ;
}

///////////////////////////////////////////////////////////////////////////////
// Creer une image a partir de rien
///////////////////////////////////////////////////////////////////////////////
void CPreferences::CreerUneImage()
	{
	const int Largeur	=	GetSystemMetrics( SM_CXSCREEN ) ;
	const int Hauteur	=	GetSystemMetrics( SM_CYSCREEN ) ;

	CDC	Dc ;
	Dc.CreateDC( "display", 0, 0, 0 ) ;

	const int	BitPixels	=	Dc.GetDeviceCaps( BITSPIXEL ) ;
	const int	Planes		=	Dc.GetDeviceCaps( PLANES ) ;


	CBitmap	Bitmap ;
	Bitmap.CreateCompatibleBitmap( &Dc, Largeur, Hauteur ) ;

	CDC MemDC ;
	MemDC.CreateCompatibleDC( &Dc ) ;
	Dc.DeleteDC() ;

	CBitmap*	pOld	=	MemDC.SelectObject( &Bitmap ) ;
	CBrush	Brosse( _CouleurTransparente ) ;
	CRect R( 0, 0, Largeur, Hauteur) ;
	MemDC.FillRect( R, &Brosse ) ;
	Brosse.DeleteObject() ;

	///////////////////////////////////////////////////////////////////////////
	// S'il s'agit de la toute premiere image, on ajoute la bitmap d'aide
	///////////////////////////////////////////////////////////////////////////
	if ( _FichiersImages.GetSize() == 0 )
		{
		CBitmap	BitmapAide ;
		BitmapAide.LoadBitmap( IDB_BITMAP2 ) ;

		BITMAP	sBitmap ;
		BitmapAide.GetBitmap( &sBitmap ) ;

		
		MemDC.DrawState( CPoint( Largeur-sBitmap.bmWidth, 0  ), 
						 CSize( sBitmap.bmWidth, sBitmap.bmHeight),
						 &BitmapAide, DSS_NORMAL ) ;

		BitmapAide.DeleteObject() ;
		}

	MemDC.SelectObject( pOld ) ;

	CString	NomPage	=	NouveauNomPage() ;
	CString NomImage=	NouveauNomImage() ;

	_FichiersImages.Add( NomImage ) ;
	_PageNames.Add( NomPage ) ;
	_Protege.Add( FALSE ) ;
	_MotDePasseSaisi.Add( FALSE ) ;
	_MotsDePasses.Add( "" ) ;

	SauveImage( NomImage, Bitmap ) ;
	Bitmap.DeleteObject() ;

	SauvegardeNomsImages() ;
	}



CString CPreferences::NouveauNomPage()
{
	CString Format ;
	Format.LoadString( IDS_FORMAT_NOM_PAGE ) ;

	CString Result ;
	Result.Format( Format, _PageNames.GetSize() + 1 ) ;

	return Result ;
}

///////////////////////////////////////////////////////////////////////////////
// NouveauNomImage
// Trouver un nom de fichier unique pour la nouvelle page
// Se fichier se trouvera dans le repertoire Pages en dessous du repertoire
// de l'executable
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::NouveauNomImage()
{
	// Tout d'abord, se mettre dans le repertoire de l'executable
	char Buffer[_MAX_PATH] ;
	GetModuleFileName( GetModuleHandle(NULL), Buffer, sizeof( Buffer ) ) ;

	char Drive[_MAX_DRIVE] ;
	char Path[_MAX_PATH] ;

	_splitpath( Buffer, Drive, Path, NULL, NULL ) ;

	_makepath( Buffer, Drive, Path, "", "" ) ;
	SetCurrentDirectory(Buffer) ;

	int Indice	=	_FichiersImages.GetSize() ;

	CreateDirectory( "Pages", NULL ) ;

	///////////////////////////////////////////////////////////////////////////
	// Essayer des noms de fichiers jusqu'a ce qu'on en trouve un qui
	// n'existe pas
	///////////////////////////////////////////////////////////////////////////
	CString Format ;
	Format.LoadString( IDS_FORMAT_NOM_IMAGES ) ;

	do
		{
		// Construction du nom de fichier
		CString Result ;
		Result.Format( Format, Indice ) ;

		// Verifier s'il existe
		if ( _access( Result, 0 ) == -1 )
			{
			char Buffer[ _MAX_PATH ] ;
			LPTSTR	FilePart ;

			GetFullPathName( Result, sizeof( Buffer ), Buffer, &FilePart ) ;
	
			return Buffer ;
			}

		// Passer au nom suivant
		Indice ++ ;
		}
	while ( true ) ;

	return "" ; // Ca n'arrive jamais
}


///////////////////////////////////////////////////////////////////////////////
// Sauve un fichier image
///////////////////////////////////////////////////////////////////////////////
void CPreferences::SauveImage(const char * FileName, CBitmap & Bitmap)
{
	ASSERT( AfxIsValidString( FileName )) ;
	ASSERT_VALID( &Bitmap ) ;

	BITMAPINFO	* pBitmapInfo	=	CreateBitmapInfoStruct( Bitmap ) ;

	if (pBitmapInfo )
		{
		CDC		Dc	;
		Dc.CreateDC( "display", 0, 0, 0 ) ;
		CreateBMPFile( FileName, pBitmapInfo, Bitmap, Dc ) ;
		LocalFree( pBitmapInfo ) ;
		}
}

void CPreferences::SetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName, const char * Value )
	{
	ASSERT( AfxIsValidString( Path )) ;
	ASSERT( AfxIsValidString( ValueName )) ;
	ASSERT( AfxIsValidString( Value )) ;
		
	HKEY	hKey ;
	DWORD	Disp ;

	if ( ERROR_SUCCESS == RegCreateKeyEx(hRoot, Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
										 NULL, &hKey, &Disp ))
		{
		RegSetValueEx( hKey, ValueName, 0, REG_SZ, (CONST BYTE *)Value, lstrlen( Value ) + 1 ) ;
		RegCloseKey( hKey ) ;
		}
	}


void CPreferences::SetRegistryValue( HKEY hRoot, const char * Path, const char * ValueName, int Value )
	{
	ASSERT( AfxIsValidString( Path )) ;
	ASSERT( AfxIsValidString( ValueName )) ;
	
	HKEY	hKey ;
	DWORD	Disp ;

	if ( ERROR_SUCCESS == RegCreateKeyEx(hRoot, Path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
										 NULL, &hKey, &Disp ))
		{
		DWORD Val	=	Value ;
		RegSetValueEx( hKey, ValueName, 0, REG_DWORD, (CONST BYTE *)&Val, sizeof( Val ) ) ;
		RegCloseKey( hKey ) ;
		}
	}

void CPreferences::SauvegardeNomsImages()
{
	const int NbImages	=	_FichiersImages.GetSize() ;
	SetPreference( NB_FichiersImages, NbImages ) ;

	for ( int i = 0; i < NbImages; i++ )
		{
		CString	PreferenceName ;

		PreferenceName.Format( "Page%d", i ) ;
		SetPreference( PreferenceName, _PageNames[i] )  ;
		
		PreferenceName.Format( "Image%d", i ) ;
		SetPreference( PreferenceName, _FichiersImages[i] ) ;
		
		PreferenceName.Format( PROTEGEE, i ) ;
		SetPreference( PreferenceName, _Protege[i]) ;

		PreferenceName.Format( MOT_DE_PASSE, i ) ;
		CString	Password	=	DecodePwd( GetPreference( PreferenceName ) ) ;
		}
}

void CPreferences::SetPreference(const char * PreferenceName, const char * Value )
{
	ASSERT( AfxIsValidString( PreferenceName )) ;
	ASSERT( AfxIsValidString( Value )) ;
	
	SetRegistryValue( HKEY_CURRENT_USER, PREFERENCES, PreferenceName, Value );
}

void CPreferences::SetPreference(const char * PreferenceName, int Value )
{
	ASSERT( AfxIsValidString( PreferenceName )) ;
	
	SetRegistryValue( HKEY_CURRENT_USER, PREFERENCES, PreferenceName, Value );
}

void CPreferences::SetImageEditor( const char * Path )
	{
	ASSERT( AfxIsValidString( Path )) ;
	m_ImageEditor	=	Path ;
	SetPreference( IMAGE_EDITOR, m_ImageEditor ) ;
	}


const char * CPreferences::NomImage(int i)
{
	if ( CActiveDesktopApp::IsShareWare())
		return _PageNames[0] ;

	return _PageNames[i] ;
}



int CPreferences::NbPages()
{
	ASSERT( _FichiersImages.GetSize() == _Protege.GetSize() ) ;
	ASSERT( _FichiersImages.GetSize() == _PageNames.GetSize()) ;
	return _FichiersImages.GetSize() ;
}

BOOL CPreferences::AjoutePage()
{
	CreerUneImage() ;
	return TRUE ;
}

BOOL CPreferences::RenommeImage(int i, const char * pNom)
{
	ASSERT( AfxIsValidString( pNom )) ;
	_PageNames[i]	=	pNom ;
	SauvegardeNomsImages() ;
	return TRUE ;
}

int CPreferences::GetNoImageCourante()
{
	if ( CActiveDesktopApp::IsShareWare())
		return 0 ;

	return _NoImageCourante ;
}

///////////////////////////////////////////////////////////////////////////////
// SetImageCourante
// Changement de l'image courante avec protection eventuelle par mot de passe
// ENTREES	:	Numero de la page desiree
// RETOUR :		VRAI si la page a ete changee
///////////////////////////////////////////////////////////////////////////////
BOOL CPreferences::SetImageCourante(int No)
{
	if ( CActiveDesktopApp::IsShareWare())
		No = 0 ;

	if ( No >= 0 && No < _FichiersImages.GetSize())
		{
		if ( ! SaisieMotDePasse( No ))
				return FALSE ;

		_NoImageCourante	=	No ;
		SetPreference( IMAGE_COURANTE, _NoImageCourante ) ;

		return TRUE ;
		}

	return FALSE ;
}

void CPreferences::SetDefaultImageEditor()
	{
	m_ImageEditor = GetSystemImageEditor() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Codage du mot de passe avant de l'ecrire dans la registry
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::CodePwd(const char * pPwd )
{
	ASSERT( AfxIsValidString( pPwd )) ;
	CString Result ;

	while ( * pPwd )
		{
		char Nouveau	=	~ (*pPwd) ;
		Result += Nouveau ;
		pPwd ++ ;
		}

	return Result ;
}

///////////////////////////////////////////////////////////////////////////////
// Deodage du mot de passe apres l'avoir lu dans la registry
///////////////////////////////////////////////////////////////////////////////
CString CPreferences::DecodePwd(const char * pPwd )
{
	ASSERT( AfxIsValidString( pPwd )) ;

	CString	Result ;

	while ( * pPwd )
		{
		char Nouveau	=	~ (*pPwd) ;
		Result += Nouveau ;
		pPwd ++ ;
		}

	return Result ;
}

BOOL CPreferences::SaisieMotDePasse( int NoImage )
{
	if ( ! _Protege[NoImage] )
		return TRUE ;

	if ( _MotDePasseSaisi[ NoImage ] )
		return TRUE ;

	CSaisieMotDePasse	Dlg( AfxGetMainWnd()) ;

	if ( Dlg.DoModal() == IDOK )
		{
		if ( Dlg.m_Password == _MotsDePasses[NoImage] )
			{
			_MotDePasseSaisi[NoImage] = TRUE ;
			return TRUE ;
			}
		else
			{
			CString Message, Titre ;
			Titre.LoadString( IDS_TITRE ) ;
			Message.LoadString( IDS_PASSWORD_INCORRECT ) ;

			MessageBeep( MB_ICONINFORMATION ) ;
			AfxGetMainWnd()->MessageBox( Message, Titre, MB_ICONINFORMATION | MB_OK | MB_SETFOREGROUND ) ;
			}
		}

	return FALSE ;
}

void CPreferences::SupprimeImage(int NoImage)
{
	ASSERT( NoImage >= 0 && NoImage < _FichiersImages.GetSize()) ;

	// Suppression du fichier
	CFile::Remove( _FichiersImages[NoImage] ) ;

	// Suppression des donnees
	_FichiersImages.RemoveAt( NoImage ) ;
	_MotDePasseSaisi.RemoveAt( NoImage ) ;
	_MotsDePasses.RemoveAt( NoImage ) ;
	_PageNames.RemoveAt( NoImage ) ;
	_Protege.RemoveAt( NoImage ) ;

	ASSERT( _FichiersImages.GetSize() == _MotDePasseSaisi.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _MotsDePasses.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _PageNames.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _Protege.GetSize()) ;

	if ( _NoImageCourante > NoImage )
		_NoImageCourante -- ;

	SauvegardeNomsImages() ;
}

///////////////////////////////////////////////////////////////////////////////
// Protege
//	Retourne VRAI si la page est protegee
// ENTREES :	Numero de la page
///////////////////////////////////////////////////////////////////////////////
BOOL CPreferences::Protege(int NoPage )
{
	return _Protege[NoPage] ;
}



///////////////////////////////////////////////////////////////////////////////
// Memorisation du nouveau mot de passe d'une page
// ENTREES :	No de la page
//				Nouveau mdp de la page
///////////////////////////////////////////////////////////////////////////////
void CPreferences::ChangeMotDePasse(int NoPage, const char * pPwd)
{
	ASSERT( pPwd ) ;
	_MotsDePasses[NoPage]	=	pPwd ;

	CString PreferenceName ;
	PreferenceName.Format( MOT_DE_PASSE, NoPage ) ;
	SetPreference( PreferenceName, CodePwd( _MotsDePasses[NoPage] )) ;
}

///////////////////////////////////////////////////////////////////////////////
// Changement de l'etat de protection d'une page
// Si la page etait anterieurement protegee, saisie du mot de passe
// ENTREES :	Numero de la page
//				Nouvel etat de protection
///////////////////////////////////////////////////////////////////////////////
void CPreferences::Protege(int NoPage, BOOL bProtect)
{
	if ( bProtect == (BOOL)_Protege[NoPage] )
		// Pas de changement
		return ;

	if ( ! SaisieMotDePasse( NoPage ))
		return ;

	_Protege[NoPage]	=	bProtect ;

	CString PreferenceName ;
	PreferenceName.Format( PROTEGEE, NoPage ) ;
	SetPreference( PreferenceName, _Protege[NoPage]) ;
}

///////////////////////////////////////////////////////////////////////////////
// Imporation d'une page
// ENTREES :	Nom du fichier
///////////////////////////////////////////////////////////////////////////////
BOOL CPreferences::ImportPage(const char * PageFileName )
{
	CWaitCursor	Wait ;

	ASSERT( AfxIsValidString( PageFileName )) ;

	///////////////////////////////////////////////////////////////////////////
	// Verifier qu'on peut bien charger la page et que c'est bien une
	// bitmap
	///////////////////////////////////////////////////////////////////////////
	HBITMAP hBitmap	=	(HBITMAP)
						LoadImage(AfxGetInstanceHandle(), PageFileName, IMAGE_BITMAP,
						  0, 0, LR_LOADFROMFILE
						 ) ;

	if (! hBitmap )
		return FALSE ;
	DeleteObject( hBitmap ) ;

	
	///////////////////////////////////////////////////////////////////////////
	// Nouveaux noms de page et d'image
	///////////////////////////////////////////////////////////////////////////
	const	CString NomFichier	=	NouveauNomImage() ;
	char	PageName[_MAX_FNAME] ;
	_splitpath( PageFileName, NULL, NULL, PageName, NULL ) ;

	///////////////////////////////////////////////////////////////////////////
	// En faire une copie locale
	///////////////////////////////////////////////////////////////////////////
	if ( ! CopyFile( PageFileName, NomFichier, TRUE) )
		return FALSE ;

	///////////////////////////////////////////////////////////////////////////
	// Ajouter dans les tables
	///////////////////////////////////////////////////////////////////////////
	_FichiersImages.Add( NomFichier ) ;
	_PageNames.Add( PageName ) ;
	_Protege.Add( FALSE ) ;
	_MotsDePasses.Add( "" ) ;
	_MotDePasseSaisi.Add( FALSE ) ;

	ASSERT( _FichiersImages.GetSize() == _MotDePasseSaisi.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _MotsDePasses.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _PageNames.GetSize()) ;
	ASSERT( _FichiersImages.GetSize() == _Protege.GetSize()) ;

	///////////////////////////////////////////////////////////////////////////
	// MAJ de la registry
	///////////////////////////////////////////////////////////////////////////
	SauvegardeNomsImages() ;

	return TRUE ;
}

BOOL CPreferences::DejaEdite()
{
	return GetPreference( DEJA_EDITE, FALSE ) ;
}

void CPreferences::DejaEdite(BOOL Deja)
{
	SetPreference( DEJA_EDITE, Deja ) ;
}
