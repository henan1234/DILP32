#if !defined(AFX_DLGAJOUTEMEDIA_H__8472365A_20A7_4347_AB1A_C417716FC05E__INCLUDED_)
#define AFX_DLGAJOUTEMEDIA_H__8472365A_20A7_4347_AB1A_C417716FC05E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAjouteMedia.h : header file
//
#include "DlgProprietesGenerique.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAjouteMedia dialog

class CDlgAjouteMedia : public CDlgProprietesGenerique
{
// Construction
public:
	CDlgAjouteMedia(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAjouteMedia)
	enum { IDD = IDD_AJOUTE_MEDIA };
	CListCtrl	m_ListeMedias;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAjouteMedia)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAjouteMedia)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AjouteDrives( void );
	CImageList		_ImageListeMedias ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAJOUTEMEDIA_H__8472365A_20A7_4347_AB1A_C417716FC05E__INCLUDED_)
