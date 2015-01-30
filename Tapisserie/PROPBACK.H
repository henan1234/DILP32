// propback.h : header file
//
#ifndef __PropBack_h__
#define __PropBack_h__
/////////////////////////////////////////////////////////////////////////////
// CPropBackground dialog

class CPropBackground : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropBackground)

public :
	static	void	OnTimer() ;
	static	void	ChangeMaintenant() ;
	virtual	void	OnOK() ;

private :
	void	ChangeTray( UINT, HICON ) ;
	static	void ChangeTapisserie( const char * ) ;


	static	int				_NbMinutes ;			// Nombre de minutes entre les changements
	static	int				_Courant   ;			// Image courante
	static	int				_DepuisChangement ;		// Nombre de minutes depuis le dernier changement

	static const	UINT	_wDragListNotify ;
	void					InstalleIcone( void ) ;

	void LitConfiguration() ;
	void EcritConfiguration() ;
	void LanceTimer() ;
	CString	_FichierAChanger ;
	BOOL _DebutThread ;
	void	ChangeTexteMinutes(int) ;

// Construction
public:
	CPropBackground();
	~CPropBackground();

// Dialog Data
	//{{AFX_DATA(CPropBackground)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_Minutes;
	CListBox	m_Liste;
	CEdit	m_MinutesTexte;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropBackground)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void			OnDropFiles( HDROP ) ;
	afx_msg	LRESULT 		OnDragListNotify( WPARAM, LPARAM ) ;

	// Generated message map functions
	//{{AFX_MSG(CPropBackground)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAjouter();
	afx_msg void OnSupprimer();
	afx_msg void OnTester();
	afx_msg void OnDblclkImages();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif
