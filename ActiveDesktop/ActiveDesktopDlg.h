// ActiveDesktopDlg.h : header file
//

#if !defined(AFX_ACTIVEDESKTOPDLG_H__D3655845_2446_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_ACTIVEDESKTOPDLG_H__D3655845_2446_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CFenetreTransparente ;
/////////////////////////////////////////////////////////////////////////////
// CActiveDesktopDlg dialog

class CActiveDesktopDlg : public CPropertyPage
{
// Construction
public:
	CActiveDesktopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveDesktopDlg)
	enum { IDD = IDD_ACTIVEDESKTOP_DIALOG };
	CButton	m_DefaultEditor;
	CButton	m_ChangeEditor;
	CString	m_EditorPath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveDesktopDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnSetActive( void );
	// Generated message map functions
	//{{AFX_MSG(CActiveDesktopDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnAvoid();
	afx_msg void OnChangeEditor();
	afx_msg void OnDefaultEditor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFenetreTransparente * _pFenetreTransparente;
	DWORD _BackupActuel;
	void ChangeImageDeFond( );
	CString GetNomUnique( const char * Directory );
	void EditBackGroundImage( void );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio insère des déclarations supplémentaires juste au-dessus de la ligne précédente.

#endif // !defined(AFX_ACTIVEDESKTOPDLG_H__D3655845_2446_11D1_AEF5_444553540000__INCLUDED_)
