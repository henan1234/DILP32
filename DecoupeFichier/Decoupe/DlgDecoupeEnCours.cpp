// DlgDecoupeEnCours.cpp : implementation file
//

#include "stdafx.h"
#include "Decoupe.h"
#include "DlgDecoupeEnCours.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoupeEnCours dialog


CDlgDecoupeEnCours::CDlgDecoupeEnCours(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDecoupeEnCours::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDecoupeEnCours)
	m_NoMorceau = _T("");
	m_NomFichier = _T("");
	m_NomFichierMorceau = _T("");
	m_TailleMorceau = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDecoupeEnCours::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDecoupeEnCours)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Text(pDX, IDC_NO_MORCEAU, m_NoMorceau);
	DDX_Text(pDX, IDC_NOM_FICHIER, m_NomFichier);
	DDX_Text(pDX, IDC_NOM_FICHIER_MORCEAU, m_NomFichierMorceau);
	DDX_Text(pDX, IDC_TAILLE_MORCEAU, m_TailleMorceau);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDecoupeEnCours, CDialog)
	//{{AFX_MSG_MAP(CDlgDecoupeEnCours)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoupeEnCours message handlers
