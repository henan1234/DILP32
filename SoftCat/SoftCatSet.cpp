// SoftCatSet.cpp : implementation of the CSoftCatSet class
//

#include "stdafx.h"
#include "SoftCat.h"
#include "SoftCatSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftCatSet implementation

IMPLEMENT_DYNAMIC(CSoftCatSet, CRecordset)

CSoftCatSet::CSoftCatSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSoftCatSet)
	m_Numero = 0;
	m_Nom = _T("");
	m_Description = _T("");
	m_NumeroDeMedia = 0;
	m_FichierIcone = _T("");
	m_IndexIcone = 0;
	m_Numero2 = 0;
	m_Nom2 = _T("");
	m_Description2 = _T("");
	m_N_ = 0;
	m_Nom3 = _T("");
	m_Date = 0;
	m_Support = _T("");
	m_Commentaire = _T("");
	m_Icone = 0;
	m_MotCle = _T("");
	m_NoFichier = 0;
	m_nFields = 18;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CSoftCatSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=SOFTS");
}

CString CSoftCatSet::GetDefaultSQL()
{
	return _T("[Fichiers],[Fichiers Requête],[Medias],[MotsCles]");
}

void CSoftCatSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSoftCatSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Fichiers].[Numero]"), m_Numero);
	RFX_Text(pFX, _T("[Fichiers].[Nom]"), m_Nom);
	RFX_Text(pFX, _T("[Fichiers].[Description]"), m_Description);
	RFX_Long(pFX, _T("[NumeroDeMedia]"), m_NumeroDeMedia);
	RFX_Text(pFX, _T("[FichierIcone]"), m_FichierIcone);
	RFX_Int(pFX, _T("[IndexIcone]"), m_IndexIcone);
	RFX_Long(pFX, _T("[Fichiers Requête].[Numero]"), m_Numero2);
	RFX_Text(pFX, _T("[Fichiers Requête].[Nom]"), m_Nom2);
	RFX_Text(pFX, _T("[Fichiers Requête].[Description]"), m_Description2);
	RFX_Binary(pFX, _T("[MotCles]"), m_MotCles);
	RFX_Long(pFX, _T("[N°]"), m_N_);
	RFX_Text(pFX, _T("[Medias].[Nom]"), m_Nom3);
	RFX_Date(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[Support]"), m_Support);
	RFX_Text(pFX, _T("[Commentaire]"), m_Commentaire);
	RFX_Int(pFX, _T("[Icone]"), m_Icone);
	RFX_Text(pFX, _T("[MotCle]"), m_MotCle);
	RFX_Long(pFX, _T("[NoFichier]"), m_NoFichier);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSoftCatSet diagnostics

#ifdef _DEBUG
void CSoftCatSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSoftCatSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
