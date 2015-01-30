// DlgRestriction.cpp : implementation file
//

#include "stdafx.h"
#include "DlgRestriction.h"
#include "restriction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char*	TextesRestrictions[]=
	{
	"'From' contains'",
	"'From' does not contain",
	"'To' contains",
	"'To' does not contain",
	"'Subject' contains",
	"'Subject' does not contain"
	} ;

static const CRestriction::T_RULE Codes[] =
	{
	 CRestriction::FROM_CONTIENT,  CRestriction::FROM_NE_CONTIENT_PAS,
	 CRestriction::TO_CONTIENT,  CRestriction::TO_NE_CONTIENT_PAS,
	 CRestriction::SUBJECT_CONTIENT,  CRestriction::SUBJECT_NE_CONTIENT_PAS
	} ;


/////////////////////////////////////////////////////////////////////////////
// CDlgRestriction dialog


CDlgRestriction::CDlgRestriction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRestriction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRestriction)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRestriction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRestriction)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRestriction, CDialog)
	//{{AFX_MSG_MAP(CDlgRestriction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRestriction message handlers

BOOL CDlgRestriction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	RemplitRules() ;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CDlgRestriction::RemplitRules()
{
	//for ( int i =
}
