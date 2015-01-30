// GravitationSkinMakerDlg.h : header file
//

#if !defined(AFX_GRAVITATIONSKINMAKERDLG_H__9D213528_817B_11D3_A60F_00A04B04180E__INCLUDED_)
#define AFX_GRAVITATIONSKINMAKERDLG_H__9D213528_817B_11D3_A60F_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGravitationSkinMakerDlg dialog

class CGravitationSkinMakerDlg : public CDialog
{
// Construction
public:
	CGravitationSkinMakerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGravitationSkinMakerDlg)
	enum { IDD = IDD_GRAVITATIONSKINMAKER_DIALOG };
	CListCtrl	m_Liste;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGravitationSkinMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CImageList	_ListeImages ;
	int			_IndiceImageCourante ;
	CStringArray	_NomsDeFichiers;
	CObArray		_Bitmaps ;

	// Generated message map functions
	//{{AFX_MSG(CGravitationSkinMakerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMoveup();
	afx_msg void OnMovedown();
	afx_msg void OnCopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAVITATIONSKINMAKERDLG_H__9D213528_817B_11D3_A60F_00A04B04180E__INCLUDED_)
