#if !defined(AFX_RECHERCHE_H__D9598656_93E0_4939_9EC9_FD645D2B652B__INCLUDED_)
#define AFX_RECHERCHE_H__D9598656_93E0_4939_9EC9_FD645D2B652B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Recherche.h : header file
//
#include <afxtempl.h>
#include "media.h"

/////////////////////////////////////////////////////////////////////////////
// CRecherche dialog

class CRecherche : public CDialog
{
// Construction
public:
	CRecherche(CWnd* pParent, CArray<CMedia*, CMedia*> & );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecherche)
	enum { IDD = IDD_RECHERCHE };
	CEdit	m_TexteCtrl;
	CButton	m_Chercher;
	CListCtrl	m_ResultatRecherche;
	CComboBox	m_ListeAttributs;
	CString	m_Texte;
	int		m_TousAttributs;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecherche)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecherche)
	virtual BOOL OnInitDialog();
	afx_msg void OnTousAttributs();
	afx_msg void OnUnAttribut();
	afx_msg void OnChangeTexte();
	afx_msg void OnChercher();
	virtual void OnOK();
	afx_msg void OnItemclickResultat(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickResultat(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int m_iSubItemSort;
	static int CALLBACK fctCompare( LPARAM Param1, LPARAM Param2, LPARAM ParamSort );
	CArray<CMedia*, CMedia*> & _TableauMedias ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHERCHE_H__D9598656_93E0_4939_9EC9_FD645D2B652B__INCLUDED_)
