#if !defined(AFX_DLGDECOUPEENCOURS_H__09EAF216_D53C_4569_AA5A_3BADF9873326__INCLUDED_)
#define AFX_DLGDECOUPEENCOURS_H__09EAF216_D53C_4569_AA5A_3BADF9873326__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDecoupeEnCours.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDecoupeEnCours dialog

class CDlgDecoupeEnCours : public CDialog
{
// Construction
public:
	CDlgDecoupeEnCours(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDecoupeEnCours)
	enum { IDD = IDD_DECOUPE_EN_COURS };
	CProgressCtrl	m_Progress;
	CString	m_NoMorceau;
	CString	m_NomFichier;
	CString	m_NomFichierMorceau;
	CString	m_TailleMorceau;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDecoupeEnCours)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDecoupeEnCours)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDECOUPEENCOURS_H__09EAF216_D53C_4569_AA5A_3BADF9873326__INCLUDED_)
