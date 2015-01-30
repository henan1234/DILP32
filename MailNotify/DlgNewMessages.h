#if !defined(AFX_DLGNEWMESSAGES_H__014EE7F6_B16D_11D3_A626_00A04B04180E__INCLUDED_)
#define AFX_DLGNEWMESSAGES_H__014EE7F6_B16D_11D3_A626_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNewMessages.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgNewMessages dialog
class CMail ;

class CDlgNewMessages : public CDialog
{
// Construction
public:
	void Refresh();
	CDlgNewMessages(CWnd* pParent = NULL);   // standard constructor
	~CDlgNewMessages() ;

// Dialog Data
	//{{AFX_DATA(CDlgNewMessages)
	enum { IDD = IDD_MESSAGES };
	CListCtrl	m_Messages;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewMessages)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewMessages)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedMessages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMailclient();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnColumnclickMessages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SupprimeMailsMarques();
	void Transparence();
	CString GetState( const CMail * );
	HBRUSH m_hBrush;

	int		_EcartGauche ;
	int		_EcartDroite ;
	int		_EcartHaut ;
	int		_EcartBas ;
	CImageList	_ImageList ;

	void BougeFenetre();
	void RemplitMails();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWMESSAGES_H__014EE7F6_B16D_11D3_A626_00A04B04180E__INCLUDED_)
