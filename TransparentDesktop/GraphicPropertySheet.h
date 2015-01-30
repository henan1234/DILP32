#if !defined(AFX_GRAPHICPROPERTYSHEET_H__04039F01_2507_11D1_AEF5_444553540000__INCLUDED_)
#define AFX_GRAPHICPROPERTYSHEET_H__04039F01_2507_11D1_AEF5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GraphicPropertySheet.h : header file
//
#define PREFERENCES		"Software\\Lucien PILLONI\\Transparent Desktop"

class CFenetreTransparente ;

/////////////////////////////////////////////////////////////////////////////
// CGraphicPropertySheet

class CGraphicPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CGraphicPropertySheet)

// Construction
public:
	CGraphicPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CGraphicPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicPropertySheet();

	// Generated message map functions
protected:
	UINT OnFinEdition( UINT wParam, LONG lParam );
	//{{AFX_MSG(CGraphicPropertySheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent) ;
	afx_msg BOOL OnCommand(WPARAM wParam, LPARAM lParam) ;
	afx_msg void ChangeImageDeFond() ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public :
	static void ChangeTrayIcone( UINT NoIcone, const char * Tip = NULL );
	static void AfficheMenu( void );
	static void PermetMenu( BOOL bPermission = TRUE );
	static const UINT				_wTaskBarNotify ;
	static const UINT				_wFinEdition;
	HANDLE					_hProcessEdition;
	CFenetreTransparente *	_pFenetreTransparente ;

	LONG	OnTaskBarNotify(UINT wParam, LONG lParam) ;
	static void	EditBackGroundImage() ;
	
	void	FinEdition() ;
private:
	void AfficheAide( const char * pRubrique = 0 );
	UINT _NoIcone;
	CTime	_DateAvantEdition ;
	BOOL _bPermissionMenu;
	static void CompleteSousMenu( CMenu * pMenu );
	BOOL ImageModifiee( void );
	static CGraphicPropertySheet	* _pZeOnlyOuane ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICPROPERTYSHEET_H__04039F01_2507_11D1_AEF5_444553540000__INCLUDED_)
