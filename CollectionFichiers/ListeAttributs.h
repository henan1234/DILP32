#if !defined(AFX_LISTEATTRIBUTS_H__0E5E5C4F_3E2E_41B4_9C68_1D2AF7519D25__INCLUDED_)
#define AFX_LISTEATTRIBUTS_H__0E5E5C4F_3E2E_41B4_9C68_1D2AF7519D25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListeAttributs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListeAttributs dialog

class CListeAttributs : public CDialog
{
// Construction
public:
	CListeAttributs(CWnd* pParent , CMapStringToString& ListeAttributs );   // standard constructor

// Dialog Data
	//{{AFX_DATA(CListeAttributs)
	enum { IDD = IDD_LISTE_ATTRIBUTS };
	CListCtrl	m_Liste;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListeAttributs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


	
// Implementation
protected:
	CMapStringToString	& _ListeAttributs ;

	// Generated message map functions
	//{{AFX_MSG(CListeAttributs)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedListeAttributs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnddragListeAttributs(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTEATTRIBUTS_H__0E5E5C4F_3E2E_41B4_9C68_1D2AF7519D25__INCLUDED_)
