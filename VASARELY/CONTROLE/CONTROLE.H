// ControleCouleurPpg.h : Declaration of the CControleCouleurPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CControleCouleurPropPage : See ControleCouleurPpg.cpp.cpp for implementation.

class CControleCouleurPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CControleCouleurPropPage)
	DECLARE_OLECREATE_EX(CControleCouleurPropPage)

// Constructor
public:
	CControleCouleurPropPage();

// Dialog Data
	//{{AFX_DATA(CControleCouleurPropPage)
	enum { IDD = IDD_PROPPAGE_CONTROLECOULEUR };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CControleCouleurPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
