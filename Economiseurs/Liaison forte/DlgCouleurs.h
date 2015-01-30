#if !defined(AFX_DLGCOULEURS_H__653C3F23_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
#define AFX_DLGCOULEURS_H__653C3F23_4C8A_11D1_AB40_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgCouleurs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCouleurs dialog
#include "resource.h"

class CDlgCouleurs : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgCouleurs)

// Construction
public:
	CDlgCouleurs();
	~CDlgCouleurs();

// Dialog Data
	//{{AFX_DATA(CDlgCouleurs)
	enum { IDD = IDD_COULEURS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgCouleurs)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgCouleurs)
	afx_msg void OnPaint();
	afx_msg void OnFond();
	afx_msg void OnLibre();
	afx_msg void OnLiens();
	afx_msg void OnSature();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void PeintRectangle( CDC &, UINT IdControl, COLORREF Couleur );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOULEURS_H__653C3F23_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
