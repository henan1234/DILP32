///////////////////////////////////////////////////////////////////////////////
// CIconeGroupe : Icone qui gère un groupe de documents
///////////////////////////////////////////////////////////////////////////////

#ifndef __ICONEGROUPE_H__
#define __ICONEGROUPE_H__

#include "WndIcone.h"
class	CRaccourci ;

class	CIconeGroupe	:	public	CIcone
	{
	DECLARE_SERIAL( CIconeGroupe ) ;

	public :
		CIconeGroupe() ;
		virtual	~CIconeGroupe() ;

		// Affichage
		virtual	void		Affiche( CDC&	Dc, CPoint Pt, BOOL	Selectionnee ) ;

		virtual	HRGN		Region( CPoint Decalage ) const  ;

		virtual	UINT		GetMenuID( void ) const ;
		virtual	BOOL		ExecuteCommand( UINT NoCommande ) ;
		virtual	BOOL		ExecuteCommand( void ) ;

		// Archivage
		void	Serialize( CArchive& ar ) ;
		COLORREF			GetCouleur(void)const { return _Couleur ; } ;
		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

public:
	void AjouteProgrammes( void );
	virtual BOOL ConfirmeSuppression( void ) const;
	static int _NbGroupes;
	BOOL Proprietes( int IndiceRacc );
	void SupprimeRaccourci( int );
	virtual void AccepteFichiers( HDROP );
	CRaccourci* GetRaccourcis( int Indice );
	int NbRaccourcis( void ) const;
	virtual CWnd* OuvreFenetre( CRect & RectFenetre, CWnd* pParent );
	virtual CString GetTip( void );
private:
	void AjouteRep( const char * );
	CObArray _Raccourcis;
	CString _Nom;
	COLORREF _Couleur;
	void GetPolygon( POINT * ) const;
	} ;
#endif
/////////////////////////////////////////////////////////////////////////////
// CWndGroupe window

class CWndGroupe : public CWndIcone
{
// Construction
public:
	CImageList _ListeIcones;
	CWndGroupe( CIcone * );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndGroupe)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndGroupe();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWndGroupe)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg	void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg	void OnRclick(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg	void OnProprietes( void ) ;
	afx_msg	void OnSupprimer( void ) ;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SupprimeRaccourci( int );
	CListCtrl _Liste;
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPropsGroupe dialog

class CPropsGroupe : public CDialog
{
// Construction
public:
	CPropsGroupe(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPropsGroupe)
	enum { IDD = IDD_GROUPE };
	CString	m_Nom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropsGroupe)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropsGroupe)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
