#ifndef _RsCgDlg_H_
#define _RsCgDlg_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"
// CG : In order to use this code against a different version of ADO, the appropriate
// ADO library needs to be used in the #import statement
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename_namespace("ADOCG") rename("EOF", "EndOfFile")
using namespace ADOCG;
#include "icrsint.h"

// RsCgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomRs class

class CCustomRs : 
	public CADORecordBinding
{
BEGIN_ADO_BINDING(CCustomRs)
	ADO_FIXED_LENGTH_ENTRY(1, adInteger, m_lCol1, lCol1Status, FALSE)
	ADO_VARIABLE_LENGTH_ENTRY2(2, adVarWChar, m_wszCol2, sizeof(m_wszCol2), lCol2Status, FALSE)
	ADO_FIXED_LENGTH_ENTRY(3, adDate, m_dtCol3, lCol3Status, FALSE)
	ADO_VARIABLE_LENGTH_ENTRY2(4, adVarWChar, m_wszCol4, sizeof(m_wszCol4), lCol4Status, FALSE)
	ADO_VARIABLE_LENGTH_ENTRY2(5, adVarWChar, m_wszCol5, sizeof(m_wszCol5), lCol5Status, FALSE)
	ADO_FIXED_LENGTH_ENTRY(6, adSmallInt, m_sCol6, lCol6Status, FALSE)
END_ADO_BINDING()

protected:
	LONG m_lCol1;
	ULONG lCol1Status;
	WCHAR m_wszCol2[201];
	ULONG lCol2Status;
	DATE m_dtCol3;
	ULONG lCol3Status;
	WCHAR m_wszCol4[101];
	ULONG lCol4Status;
	WCHAR m_wszCol5[256];
	ULONG lCol5Status;
	SHORT m_sCol6;
	ULONG lCol6Status;
};

//
// TODO : These definitions should be moved to the resource header.
//
#define ID_BTN_MOVEPREVIOUS			201
#define ID_BTN_MOVENEXT				202
#define ID_BTN_MOVELAST				203
#define ID_BTN_MOVEFIRST				204
#define IDC_STATIC_COL1		1001
#define IDC_EDIT_COL1		2001
#define IDC_STATIC_COL2		1002
#define IDC_EDIT_COL2		2002
#define IDC_STATIC_COL3		1003
#define IDC_EDIT_COL3		2003
#define IDC_STATIC_COL4		1004
#define IDC_EDIT_COL4		2004
#define IDC_STATIC_COL5		1005
#define IDC_EDIT_COL5		2005
#define IDC_STATIC_COL6		1006
#define IDC_EDIT_COL6		2006


/////////////////////////////////////////////////////////////////////////////
// CRsCgDlg dialog

class CRsCgDlg : 
	public CDialog, 
	public CCustomRs
{
// Construction
public:
	CRsCgDlg(CWnd* pParent = NULL);
	~CRsCgDlg();

	BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CRsCgDlg)
	enum { IDD = CG_IDD_RECORDSET };
	LONG m_lDlgCol1;
	CString m_strDlgCol2;
	COleDateTime m_oledtDlgCol3;
	CString m_strDlgCol4;
	CString m_strDlgCol5;
	SHORT m_sDlgCol6;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsCgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void RefreshBoundData();
	void GenerateError(HRESULT hr, PWSTR pwszDescription);

	_RecordsetPtr m_pRs;

	CString m_strConnection;
	CString m_strCmdText;

	// Generated message map functions
	//{{AFX_MSG(CRsCgDlg)
	afx_msg void OnBtnMoveFirst();
	afx_msg void OnBtnMoveLast();
	afx_msg void OnBtnMoveNext();
	afx_msg void OnBtnMovePrevious();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !_RsCgDlg_H_
