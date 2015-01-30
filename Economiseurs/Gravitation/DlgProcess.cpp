// DlgProcess.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DlgProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProcess dialog


CDlgProcess::CDlgProcess(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProcess::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProcess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgProcess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProcess)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_MESSAGE, m_Message);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProcess, CDialog)
	//{{AFX_MSG_MAP(CDlgProcess)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProcess message handlers
