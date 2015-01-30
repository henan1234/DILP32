// SoftCollectionDlg.h : header file
//

#if !defined(AFX_SOFTCOLLECTIONDLG_H__513D9732_6640_44F1_8C82_1D889F4B37CF__INCLUDED_)
#define AFX_SOFTCOLLECTIONDLG_H__513D9732_6640_44F1_8C82_1D889F4B37CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxext.h>
#include "matoolbar.h"
#include <afxtempl.h>

class	CMedia ;

class CSoftCollectionDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CSoftCollectionDlg dialog

class CSoftCollectionDlg : public CDialog
{
	DECLARE_DYNAMIC(CSoftCollectionDlg);
	friend class CSoftCollectionDlgAutoProxy;

// Construction
public:
	void ChargeCatalogues();
	CSoftCollectionDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CSoftCollectionDlg();

// Dialog Data
	//{{AFX_DATA(CSoftCollectionDlg)
	enum { IDD = IDD_SOFTCOLLECTION_DIALOG };
	CButton	m_BoutonSupprimerMedia;
	CListCtrl	m_Attributs;
	CTreeCtrl	m_ContenuMedia;
	CListCtrl	m_ListeMedias;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftCollectionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CSoftCollectionDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CSoftCollectionDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMediasAjouter();
	afx_msg void OnItemchangedListemedias(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedContenumedia(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListemedias(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRechercheChercher();
	afx_msg void OnMediasSupprimer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int _iSelected;
	void DeselectionneMedia( int Indice );
	CString NomFichierUnique();
	void SelectionneMedia( int Indice );
	CMedia*	TrouveMedia( const CString & MediaName ) ;
	int GetIndiceMedia( const CString & MediaName );
	void SelectionneMedia( const CString & MediaName );
	BOOL AjouteMedia( CMedia * pMedia );
	void AjouteMedia( const CString & Media );

	CArray<CMedia*, CMedia*>	_TableauMedias ;
	CStringArray				_NomsFichiers ;
	CImageList	_ImageListMedias ;
	CImageList	_ImageListContenus ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTCOLLECTIONDLG_H__513D9732_6640_44F1_8C82_1D889F4B37CF__INCLUDED_)
