#if !defined(AFX_DLGPROPRIETESGENERIQUE_H__89502698_81F4_4C9D_8E29_5B271AA39A23__INCLUDED_)
#define AFX_DLGPROPRIETESGENERIQUE_H__89502698_81F4_4C9D_8E29_5B271AA39A23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProprietesGenerique.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProprietesGenerique dialog

class CDlgProprietesGenerique : public CDialog
{
// Construction
public:
	CDlgProprietesGenerique(UINT IDDlg, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgProprietesGenerique)
	enum { IDD = IDD_PROPRIETES_GENERIQUE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProprietesGenerique)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProprietesGenerique)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROPRIETESGENERIQUE_H__89502698_81F4_4C9D_8E29_5B271AA39A23__INCLUDED_)
