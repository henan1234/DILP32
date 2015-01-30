// Jibe96Doc.h : interface of the CJibe96Doc class
//
/////////////////////////////////////////////////////////////////////////////
#include "icone.h"

class CJibe96Doc : public CDocument
{
protected: // create from serialization only
	CJibe96Doc();
	DECLARE_DYNCREATE(CJibe96Doc)

// Attributes
public:
	void Insere( int, int );
	void Echange( int, int );
	int IndiceIcone( CIcone * );
	void SupprimeIcone( CIcone * pIcone );
	void AjouteIcone( CIcone * );
	int NbIcones( void ) const;
	CIcone * GetIcone( int Indice );
	void SetSide( UINT Side );
	UINT GetSide( void ) const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJibe96Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual void OnCloseDocument();
	protected:
	virtual BOOL SaveModified();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJibe96Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJibe96Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CJibe96Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
//	DECLARE_DISPATCH_MAP()
//	DECLARE_INTERFACE_MAP()
private:
	UINT		_Side;
	CObArray	_Icones ;

};

/////////////////////////////////////////////////////////////////////////////
