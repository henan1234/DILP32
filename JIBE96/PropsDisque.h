// PropsDisque.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropsDisque dialog
#include "wndicone.h"

class CPropsDisque : public CWndIcone
{
// Construction
public:
	int m_PourcentageAlarme;
	CPropsDisque(CIcone *, CWnd* pParent = NULL);   // standard constructor
	static CString GetDriveName( const CString & Drive );

// Dialog Data
	//{{AFX_DATA(CPropsDisque)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	m_Disques;
	CSliderCtrl	m_Alarme;
	CString	m_Disque;
	CString	m_Props;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropsDisque)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL ConfirmeFermetureAuto( void );

	// Generated message map functions
	//{{AFX_MSG(CPropsDisque)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnItemchangedDisques(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkAlarme(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickAlarme(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetPropsDisque( void );
	CImageList _ListeIcones;
};
