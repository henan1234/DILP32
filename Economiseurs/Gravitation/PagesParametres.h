#if !defined(AFX_PAGESPARAMETRES_H__B10F3EC0_3140_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_PAGESPARAMETRES_H__B10F3EC0_3140_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PagesParametres.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CPagesParametres dialog
#include "SharewareMessageWnd.h"
#include "options.h"

class CPagesParametres : public CPropertyPage
{
	DECLARE_DYNCREATE(CPagesParametres)

// Construction
public:
	CPagesParametres();
	~CPagesParametres();
	typedef void	(*CALL_BACK_FLOTTANT)(CPagesParametres*) ;

// Dialog Data
	//{{AFX_DATA(CPagesParametres)
	enum { IDD = IDD_PARAMETRES };
	CButton	m_FichierBrowse;
	CEdit	m_FichierEdit;
	CComboBox	m_Choix;
	CEdit	m_FlottantEdit;
	CStatic	m_FlottantUnite;
	CButton	m_BoolCheck;
	CStatic	m_IntCurrentValue;
	CSliderCtrl	m_IntNumber;
	CEdit	m_Tip;
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPagesParametres)
	public:
	virtual BOOL OnSetActive();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPagesParametres)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBoolcheck();
	afx_msg void OnKillfocusFlottantEdit();
	afx_msg void OnChangeFlottantEdit();
	afx_msg void OnSelchangeChoix();
	afx_msg void OnFichierBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg long	OnUserParameters( UINT, LONG ) ;

private:
	static void SetDirectory( COptionChaine * pOption, char * pDir );
	static void GetDirectory( COptionChaine * pOption, char * pDir );
	void RemplitCamera( HTREEITEM hRoot );
	void RemplitArbre();
	void RemplitMasses( HTREEITEM hRoot );

	void CacheControles();
	void SaisieIntIntervalle( HTREEITEM, UINT, COptionEntier *, int, int );
	void SaisieBool			( HTREEITEM, UINT, UINT, COptionEntier * );
	void SaisieFlottant		( HTREEITEM, UINT, COptionFlottant *, CALL_BACK_FLOTTANT ) ;
	void SaisieChoix		( HTREEITEM, UINT, UINT, COptionEntier * ) ;
	void SaisieFichier		( HTREEITEM, UINT, COptionChaine * ) ;

	CImageList	_ImageListe ;
	void	RemplitNombres() ;
	void	RemplitPhysique() ;
	void	RemplitAffichage() ;
	void	RemplitCometes(HTREEITEM hRoot) ;

	void	AddItem( HTREEITEM, UINT, UINT, int, UINT ) ;
	void	AddBoolItem( HTREEITEM, UINT, UINT, BOOL, UINT ) ;
	void	AddFlottantItem( HTREEITEM, UINT, UINT, FLOTTANT, UINT ) ;
	void	AddItemFichier( HTREEITEM, UINT, UINT, const CString &, UINT ) ;
	void	AddItemChoix( HTREEITEM, UINT, UINT, UINT, int, UINT ) ;

	CSharewareMessageWnd	_Shareware ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESPARAMETRES_H__B10F3EC0_3140_11D2_B79A_0000E8D9BF74__INCLUDED_)
