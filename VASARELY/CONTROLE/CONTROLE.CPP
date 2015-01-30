// ControleCouleurPpg.cpp : Implementation of the CControleCouleurPropPage property page class.

#include "stdafx.h"
#include "ControleCouleur.h"
#include "ControleCouleurPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CControleCouleurPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CControleCouleurPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CControleCouleurPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CControleCouleurPropPage, "CONTROLECOULEUR.ControleCouleurPropPage.1",
	0xeace7d87, 0x59b8, 0x11d0, 0x97, 0x62, 0x8, 0, 0x9, 0xbd, 0x28, 0x1c)


/////////////////////////////////////////////////////////////////////////////
// CControleCouleurPropPage::CControleCouleurPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CControleCouleurPropPage

BOOL CControleCouleurPropPage::CControleCouleurPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CONTROLECOULEUR_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CControleCouleurPropPage::CControleCouleurPropPage - Constructor

CControleCouleurPropPage::CControleCouleurPropPage() :
	COlePropertyPage(IDD, IDS_CONTROLECOULEUR_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CControleCouleurPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CControleCouleurPropPage::DoDataExchange - Moves data between page and properties

void CControleCouleurPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CControleCouleurPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CControleCouleurPropPage message handlers
