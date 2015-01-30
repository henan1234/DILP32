// SurveilleDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSurveilleDlg dialog
#include "WndIcone.h"
class	CIcone ;

class CSurveilleDlg : public CWndIcone
{
// Construction
public:
	CSurveilleDlg(CIcone *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSurveilleDlg)
	enum { IDD = IDD_SURVEILLE };
	CListBox	m_Evenements;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSurveilleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSurveilleDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
