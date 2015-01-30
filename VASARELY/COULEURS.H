// CouleursWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCouleursWnd window

class CCouleursWnd : public CWnd
{
// Construction
public:
	CCouleursWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCouleursWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCouleursWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCouleursWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
