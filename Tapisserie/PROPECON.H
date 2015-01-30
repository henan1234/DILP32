// propecon.h : header file
//
#include "ListeEconomiseurs.h"

/////////////////////////////////////////////////////////////////////////////
// CPropEconomiseurs dialog

class CPropEconomiseurs : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropEconomiseurs)
private :
	static		CListeEconomiseurs		_Liste ;
	static		UINT	_NbMinutes ;
	static		HWND		_hOldWnd ;

// Construction
public:
	CPropEconomiseurs();
	~CPropEconomiseurs();

	static	void	OnTimer( void ) ;
	virtual	void	OnOK() ;

// Dialog Data
	//{{AFX_DATA(CPropEconomiseurs)
	enum { IDD = IDD_DIALOG2 };
	CListBox	m_LB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropEconomiseurs)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropEconomiseurs)
	virtual BOOL OnInitDialog();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnSelchangeListeEco();
	afx_msg void OnConfigurer();
	afx_msg void OnTest();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnRadio7();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
