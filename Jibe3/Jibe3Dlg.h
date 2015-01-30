// Jibe3Dlg.h : header file
//

#if !defined(AFX_JIBE3DLG_H__56718AA8_22BD_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_JIBE3DLG_H__56718AA8_22BD_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CJibe3DlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CJibe3Dlg dialog

class CJibe3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CJibe3Dlg);
	friend class CJibe3DlgAutoProxy;

// Construction
public:
	CJibe3Dlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CJibe3Dlg();

// Dialog Data
	//{{AFX_DATA(CJibe3Dlg)
	enum { IDD = IDD_JIBE3_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJibe3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CJibe3DlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CJibe3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_JIBE3DLG_H__56718AA8_22BD_11D1_AEF5_444553540000__INCLUDED_)
