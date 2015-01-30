// Page2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPage2 dialog
class	CTapisserie ;
#include "myimagelist.h"

class CPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPage2)

// Construction
public:
	CPage2();
	~CPage2();

// Dialog Data
	//{{AFX_DATA(CPage2)
	enum { IDD = IDD_PAGE2 };
	CListCtrl	m_Liste;
	CSpinButtonCtrl	m_SpinnerMinutes;
	CEdit	m_EditMinutes;
	CButton	m_Supprimer;
	int		m_Minutes;
	int		m_Mosaique;
	BOOL	m_Economiseur;
	BOOL	m_Change;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPage2)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnAjouter();
	afx_msg void OnCentre();
	afx_msg void OnMosaique();
	afx_msg void OnChangeMinutes();
	afx_msg void OnTester();
	afx_msg void OnItemchangedListe(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSupprimer();
	afx_msg void OnDblclkListe(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChange();
	afx_msg void OnChangeCouleur();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class	CTapisserieSheet ;

private:
	void ChargeImages( void );
	void ChangeTapisserie( void );
	CRect _RCouleur;
	HBRUSH m_hBrush;
	void AjouteImage( CTapisserie * );
	void Sauvegarde( void );
	void SetImageActuelle();
	static int NoIcone( const CTapisserie * );
	CImageList _ImageListe;
	void		AjouteImage( const char * Image, BOOL Mosaique, int NbMinutes );
	CObArray	_ListeTapisseries;
	void ChangeMaintenant( void );
	int _DepuisChangement;
	int _Courant;
};
