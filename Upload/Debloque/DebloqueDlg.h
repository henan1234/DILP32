// DebloqueDlg.h : header file
//

#if !defined(AFX_DEBLOQUEDLG_H__4859C685_30D7_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_DEBLOQUEDLG_H__4859C685_30D7_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDebloqueDlg dialog

class CDebloqueDlg : public CDialog
{
// Construction
public:
	CDebloqueDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDebloqueDlg)
	enum { IDD = IDD_DEBLOQUE_DIALOG };
	CListBox	m_Liste;
	CString	m_Entree;
	CString	m_Sortie;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDebloqueDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDebloqueDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeListe();
	afx_msg void OnChangeEntree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL VerifieLogiciel( void );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_DEBLOQUEDLG_H__4859C685_30D7_11D1_AEF5_444553540000__INCLUDED_)
