#if !defined(AFX_REGLAGES_H__653C3F21_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
#define AFX_REGLAGES_H__653C3F21_4C8A_11D1_AB40_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Reglages.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CReglages dialog

class CReglages : public CPropertyPage
{
	DECLARE_DYNCREATE(CReglages)

// Construction
public:
	CReglages();
	~CReglages();

// Dialog Data
	//{{AFX_DATA(CReglages)
	enum { IDD = IDD_REGLAGES };
	CSliderCtrl	m_NbAtomes;
	CSliderCtrl	m_Min;
	CSliderCtrl	m_Max;
	CSliderCtrl	m_Liens;
	CSliderCtrl	m_Equilibre;
	CSliderCtrl	m_Affichage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReglages)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReglages)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGLAGES_H__653C3F21_4C8A_11D1_AB40_0020AF71E433__INCLUDED_)
