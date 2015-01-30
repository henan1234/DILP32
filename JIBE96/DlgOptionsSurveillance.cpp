// DlgOptionsSurveillance.cpp : implementation file
//

#include "stdafx.h"
#include "Jibe96.h"
#include "DlgOptionsSurveillance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsSurveillance dialog


CDlgOptionsSurveillance::CDlgOptionsSurveillance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptionsSurveillance::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptionsSurveillance)
	m_Attributs = FALSE;
	m_DateModif = FALSE;
	m_Fichiers = FALSE;
	m_Repertoires = FALSE;
	m_SousRep = FALSE;
	m_Taille = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgOptionsSurveillance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptionsSurveillance)
	DDX_Check(pDX, IDC_ATTRIBUTS, m_Attributs);
	DDX_Check(pDX, IDC_DATE_MODIF, m_DateModif);
	DDX_Check(pDX, IDC_FICHIERS, m_Fichiers);
	DDX_Check(pDX, IDC_REPERTOIRES, m_Repertoires);
	DDX_Check(pDX, IDC_SOUSREP, m_SousRep);
	DDX_Check(pDX, IDC_TAILLE, m_Taille);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptionsSurveillance, CDialog)
	//{{AFX_MSG_MAP(CDlgOptionsSurveillance)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptionsSurveillance message handlers
