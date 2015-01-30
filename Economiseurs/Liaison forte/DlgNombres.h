#if !defined(AFX_DLGNOMBRES_H__FDF45841_4C87_11D1_AB40_0020AF71E433__INCLUDED_)
#define AFX_DLGNOMBRES_H__FDF45841_4C87_11D1_AB40_0020AF71E433__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgNombres.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNombres dialog
#include "resource.h"

class CDlgNombres : public CPropertyPage
{
	DECLARE_DYNCREATE(CDlgNombres)

// Construction
public:
	CDlgNombres();
	~CDlgNombres();

// Dialog Data
	//{{AFX_DATA(CDlgNombres)
	enum { IDD = IDD_NOMBRES };
	CSliderCtrl	m_NbAtomes;
	CSliderCtrl	m_Min;
	CSliderCtrl	m_Max;
	CSliderCtrl	m_Liens;
	CSliderCtrl	m_Equilibre;
	CSliderCtrl	m_Affichage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDlgNombres)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgNombres)
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)  ;

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void PositionsSliders( void );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNOMBRES_H__FDF45841_4C87_11D1_AB40_0020AF71E433__INCLUDED_)
