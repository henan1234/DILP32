// Element.h: interface for the CElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENT_H__76F42DE6_175E_4A33_8FD4_AA4F6B527177__INCLUDED_)
#define AFX_ELEMENT_H__76F42DE6_175E_4A33_8FD4_AA4F6B527177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "scanningdlg.h"

// Noms d'attributs standards
const char CHEMIN[]					=	"Chemin" ;
const char REPERTOIRE[]				=	"Répertoire" ;
const char NOM_FICHIER[]			=	"Nom de fichier" ;
const char NOM[]					=	"Nom" ;
const char FICHIER[]				=	"Fichier";
const char TAILLE[]					=	"Taille" ;
const char ELEMENT[]				=	"Element" ;
const char EXTENSION[]				=	"Extension" ;
const char RACINE[]					=	"Racine" ;

class CElement : public CObject  
{
	DECLARE_SERIAL( CElement ) ;
public:
	BOOL ConvientPourFiltre( const CString & AttributFiltre, const CString & TexteFiltre );
	void	SetAttribut( const CString & Nom, const CString & Valeur ) ;
	void	SetAttribut( const CString & Nom, int Valeur ) ;

	CString GetAttribut( const CString & Nom );
	CElement();
	virtual ~CElement();

	BOOL	Scanne( const CString & Path, WIN32_FIND_DATA, CScanningDlg &, CMapStringToString & AttributsCommuns ) ;


	static CStringArray & GetTousAttributs() { return _TousLesAttributs ; }

	virtual void Serialize( CArchive & ar ) ;

private:
	BOOL ValeurConvient( const CString & Texte, const CString & Valeur );
	static void	CElement::ReferenceAttribut( const CString & NomAttribut ) ;
	static CStringArray	_TousLesAttributs ;

	CString CalculeTexteTaille(__int64 TailleFichier) ;
	void ExtraitInfosFichier(const CString &File, const CString &Ext) ;
	void ExtraitInfosMP3(const CString &File) ;
	void GetFileCheckSum(const CString &NomFichier, __int64 Taille, CScanningDlg & dlg ) ;
	void GetSystemInfo(const CString &Ext) ;

	CMapStringToString	_Attributs ;
	WIN32_FIND_DATA		_Data ;
};

#endif // !defined(AFX_ELEMENT_H__76F42DE6_175E_4A33_8FD4_AA4F6B527177__INCLUDED_)
