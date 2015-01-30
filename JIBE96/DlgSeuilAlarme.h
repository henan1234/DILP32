// DlgSeuilAlarme.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSeuilAlarme dialog
#include "resource.h"
#include "wndicone.h"

class CDlgSeuilAlarme : public CWndIcone
{
// Construction
public:
	CDlgSeuilAlarme(CIcone *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSeuilAlarme)
	enum { IDD = IDD_SEUIL_ALARME };
	CStatic	m_Pct;
	CSliderCtrl	m_Slider;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSeuilAlarme)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSeuilAlarme)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ChangePct( void );
};
