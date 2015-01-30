// IconeCommande.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCommande dialog
#include "wndicone.h"

class	CIconeCommande	:	public	CIcone
{
	DECLARE_SERIAL( CIconeCommande ) ;

	public :
		CIconeCommande() ;
		virtual	~CIconeCommande() ;

		// Affichage
		virtual	void		Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;

		virtual	HRGN		Region( CPoint Decalage ) const  ;

		virtual	UINT		GetMenuID( void ) const ;
		virtual	BOOL		ExecuteCommand( UINT NoCommande ) ;
		virtual	BOOL		ExecuteCommand( void ) ;

		// Archivage
		void	Serialize( CArchive& ar ) ;
		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

public:
	virtual BOOL ConfirmeSuppression( void ) const;
	BOOL Proprietes( int IndiceRacc );
	virtual void AccepteFichiers( HDROP );
	virtual CWnd* OuvreFenetre( CRect & RectFenetre, CWnd* pParent );
	virtual CString GetTip( void );

private:
	CStringList		_CommandesTapees ;
	} ;


class CDlgCommande : public CWndIcone
{
// Construction
public:
	CDlgCommande(CIcone *, CStringList & Commandes, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCommande)
	enum { IDD = IDD_COMMANDE };
	CListBox	m_Liste;
	CComboBox	m_Combo;
	CString	m_Ligne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCommande)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCommande)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private :
		CStringList &		_Commandes ;
};
