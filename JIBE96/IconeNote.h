///////////////////////////////////////////////////////////////////////////////
// CIconeNote
//	Classe d'icones contenant une note
///////////////////////////////////////////////////////////////////////////////

#ifndef _ICONENOTE_H_
#define _ICONENOTE_H_

#define ETAT_MIN		0
#define ETAT_MOY		1
#define ETAT_MAX		2

#include "wndicone.h"

class	CIconeNote : public	CIcone
	{
	DECLARE_SERIAL( CIconeNote ) ;

	public :
		CIconeNote() ;
		virtual	~CIconeNote() ;

		// Affichage
		virtual		void	Affiche( CDC	&	Dc, CPoint Pt, BOOL	Selectionnee ) ;
		virtual		HRGN	Region( CPoint Decalage ) const ;

		// Archivage
		void		Serialize( CArchive& ar ) ;

		virtual		BOOL ConfirmeSuppression( void ) const;
		void		SetTexte( const CString & );
		const		CString&	GetText( void ) const { return _Texte ; } ;
		COLORREF	GetCouleur( void ) const { return _CouleurFond ; } ;
		virtual		CWnd* OuvreFenetre( CRect &, CWnd * );
		virtual		CString GetTip( void );
		virtual		CString TipText( void ) const;
		virtual		UINT GetMenuID( void ) const;
		virtual		BOOL ExecuteCommand( void );
		virtual		BOOL ExecuteCommand( UINT NoCommande ) ;
		virtual		void AccepteFichiers( HDROP ) ;
		// DEBUG
#ifdef _DEBUG
		virtual void AssertValid( void ) const ;
		virtual void Dump( CDumpContext & ) const ;
#endif

	private :
		// Retourne la taille de la note en fonction de son etat present
		CSize		TailleEtat( ) const ;

		// Texte de la note
		CString		_Texte ;

		// Etat d'affichage
		UINT		_Etat ;

		//
		UINT		_NoIcone ;
		COLORREF	_CouleurFond ;
	} ;

/////////////////////////////////////////////////////////////////////////////
// CNoteDlg dialog

class CNoteDlg : public CDialog
{
// Construction
public:
	COLORREF m_Couleur;
	UINT m_NoIcone;
	CNoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNoteDlg)
	enum { IDD = IDD_DIALOG_NOTE };
	CListCtrl	m_Icones;
	int		m_Affichage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNoteDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCouleur();
	afx_msg void OnItemchangedIcones(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList _Images;
};
/////////////////////////////////////////////////////////////////////////////
// CWndNote window

class CWndNote : public CWndIcone
{
// Construction
public:
	CWndNote( CIcone * );

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndNote)
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWndNote();

	// Generated message map functions
protected:
	virtual BOOL ConfirmeFermetureAuto( void );
	//{{AFX_MSG(CWndNote)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CToolBar _ToolBar;
	CEdit _Edit;
};

/////////////////////////////////////////////////////////////////////////////
#endif
