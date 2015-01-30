// RsCgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RsCgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsCgDlg dialog


CRsCgDlg::CRsCgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRsCgDlg::IDD, pParent)
{
	m_strConnection = _T("Provider=MSDASQL.1;Persist Security Info=False;Data Source=SOFTS");
	m_strCmdText = _T("Medias");

	m_pRs = NULL;
	
	//{{AFX_DATA_INIT(CRsCgDlg)
	m_lDlgCol1 = 0;
	m_strDlgCol2 = _T("");
	m_oledtDlgCol3 = 0L;
	m_strDlgCol4 = _T("");
	m_strDlgCol5 = _T("");
	m_sDlgCol6 = 0;
	//}}AFX_DATA_INIT
}

CRsCgDlg::~CRsCgDlg()
{
	m_pRs = NULL;
}

BOOL CRsCgDlg::OnInitDialog()
{
	HRESULT hr = NOERROR;
	IADORecordBinding *piAdoRecordBinding = NULL;

	CDialog::OnInitDialog();

	try
	{
		m_pRs.CreateInstance(__uuidof(Recordset));

		m_pRs->CursorLocation = adUseClient;
		m_pRs->Open((LPCTSTR)m_strCmdText, (LPCTSTR)m_strConnection, adOpenStatic, 
			adLockReadOnly, adCmdTableDirect);

		if (FAILED(hr = m_pRs->QueryInterface(__uuidof(IADORecordBinding), (LPVOID *)&piAdoRecordBinding)))
			_com_issue_error(hr);
		if (FAILED(hr = piAdoRecordBinding->BindToRecordset(this)))
			_com_issue_error(hr);

		RefreshBoundData();
	}
	catch (_com_error &e)
	{
		GenerateError(e.Error(), e.Description());
	}

	if (piAdoRecordBinding)
		piAdoRecordBinding->Release();

	return TRUE;
}

void CRsCgDlg::RefreshBoundData()
{
	if (adFldOK == lCol1Status)
		m_lDlgCol1 = m_lCol1;
	else
		m_lDlgCol1 = 0;
	if (adFldOK == lCol2Status)
		m_strDlgCol2 = m_wszCol2;
	else
		m_strDlgCol2 = _T("");
	if (adFldOK == lCol3Status)
		m_oledtDlgCol3 = m_dtCol3;
	else
		m_oledtDlgCol3 = 0L;
	if (adFldOK == lCol4Status)
		m_strDlgCol4 = m_wszCol4;
	else
		m_strDlgCol4 = _T("");
	if (adFldOK == lCol5Status)
		m_strDlgCol5 = m_wszCol5;
	else
		m_strDlgCol5 = _T("");
	if (adFldOK == lCol6Status)
		m_sDlgCol6 = m_sCol6;
	else
		m_sDlgCol6 = 0;

	UpdateData(FALSE);
}

void CRsCgDlg::GenerateError(HRESULT hr, PWSTR pwszDescription)
{
	CString strError;

	strError.Format("Run-time error '%d (%x)'", hr, hr);
	strError += "\n\n";
	strError += pwszDescription;

	AfxMessageBox(strError);
}

void CRsCgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRsCgDlg)
	DDX_Text(pDX, IDC_EDIT_COL1, m_lDlgCol1);
	DDX_Text(pDX, IDC_EDIT_COL2, m_strDlgCol2);
	DDX_Text(pDX, IDC_EDIT_COL3, m_oledtDlgCol3);
	DDX_Text(pDX, IDC_EDIT_COL4, m_strDlgCol4);
	DDX_Text(pDX, IDC_EDIT_COL5, m_strDlgCol5);
	DDX_Text(pDX, IDC_EDIT_COL6, m_sDlgCol6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRsCgDlg, CDialog)
	//{{AFX_MSG_MAP(CRsCgDlg)
	ON_BN_CLICKED(ID_BTN_MOVEFIRST, OnBtnMoveFirst)
	ON_BN_CLICKED(ID_BTN_MOVELAST, OnBtnMoveLast)
	ON_BN_CLICKED(ID_BTN_MOVENEXT, OnBtnMoveNext)
	ON_BN_CLICKED(ID_BTN_MOVEPREVIOUS, OnBtnMovePrevious)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRsCgDlg message handlers

void CRsCgDlg::OnBtnMoveFirst() 
{
	try
	{
		m_pRs->MoveFirst();
		RefreshBoundData();
	}
	catch (_com_error &e)
	{
		GenerateError(e.Error(), e.Description());
	}
}

void CRsCgDlg::OnBtnMoveLast() 
{
	try
	{
		m_pRs->MoveLast();
		RefreshBoundData();
	}
	catch (_com_error &e)
	{
		GenerateError(e.Error(), e.Description());
	}
}

void CRsCgDlg::OnBtnMoveNext() 
{
	try
	{
		m_pRs->MoveNext();
		RefreshBoundData();
	}
	catch (_com_error &e)
	{
		GenerateError(e.Error(), e.Description());
	}
}

void CRsCgDlg::OnBtnMovePrevious() 
{
	try
	{
		m_pRs->MovePrevious();
		RefreshBoundData();
	}
	catch (_com_error &e)
	{
		GenerateError(e.Error(), e.Description());
	}
}
