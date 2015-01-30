// DecoupeDlg.h : header file
//

#if !defined(AFX_DECOUPEDLG_H__8B7D2461_99B4_4FD6_A161_6FC566EC2860__INCLUDED_)
#define AFX_DECOUPEDLG_H__8B7D2461_99B4_4FD6_A161_6FC566EC2860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDecoupeDlg dialog
#include "DlgDecoupeEnCours.h"

class CDecoupeDlg : public CDialog
{
// Construction
public:
	CDecoupeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDecoupeDlg)
	enum { IDD = IDD_DECOUPE_DIALOG };
	CComboBox	m_Tailles;
	CComboBox	m_FormatsNomsCibles;
	CString	m_FichierADecouper;
	CString	m_TailleFichier;
	CString	m_RepertoireCible;
	DWORD	m_TailleMorceau;
	CString	m_NbMorceaux;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoupeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDecoupeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnParcoursFichiers();
	afx_msg void OnParcoursRepertoire();
	afx_msg void OnChangeFichierADecouper();
	afx_msg void OnSelchangeTailles();
	afx_msg void OnChangeTailleMorceau();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DecoupeFichier( CDlgDecoupeEnCours& dlg, const char * pNomFichier, const char * pRepertoireCible, DWORD TailleMorceaux, const char * pFormatNom );
	static CString FormatteTailleFichier( DWORD Taille );
	void CalculeTailleFichier();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECOUPEDLG_H__8B7D2461_99B4_4FD6_A161_6FC566EC2860__INCLUDED_)
