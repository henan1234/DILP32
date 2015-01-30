///////////////////////////////////////////////////////////////////////////////
// CIconeSeparateur
//	Classe d'icones contenant un separateur
///////////////////////////////////////////////////////////////////////////////

#ifndef _ICONESEPARATEUR_H_
#define _ICONESEPARATEUR_H_

#define ETAT_MIN		0
#define ETAT_MOY		1
#define ETAT_MAX		2

class	CIconeSeparateur : public	CIcone
	{
	DECLARE_SERIAL( CIconeSeparateur ) ;

	public :
		CIconeSeparateur() ;
		virtual	~CIconeSeparateur() ;

		// Affichage
		virtual	void	Affiche( CDC	&	Dc, CPoint Pt, BOOL	Selectionnee ) ;

		virtual	HRGN	Region( CPoint Decalage ) const ;

		// Archivage
		void	Serialize( CArchive& ar ) ;
		
		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

	private :
		int		_Hauteur ;

public:
	virtual CRect Rect( void ) const;

	virtual CString GetTip( void );
	virtual UINT GetMenuID( void ) const;
	virtual BOOL ExecuteCommand( void );
	virtual BOOL ExecuteCommand( UINT NoCommande ) ;
} ;

#endif

/////////////////////////////////////////////////////////////////////////////
// CSeparateurDlg dialog

class CSeparateurDlg : public CDialog
{
// Construction
public:
	CSeparateurDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSeparateurDlg)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_WndHauteur;
	CStatic	m_Dessin;
	CSpinButtonCtrl	m_Spinner;
	int		m_Hauteur;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparateurDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeparateurDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
