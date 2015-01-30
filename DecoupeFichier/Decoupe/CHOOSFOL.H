//****************************************************************************
// Hewlett-Packard (c)
// 
// choosfol.h :	declaration of the CChooseFolder class
//				this class is Win95 version of the CChooseDirectory class
//				WORKS ONLY UNDER WIN95 ! (Or WinNT with the new shell)
//
// 
// $Author:: Flaven    $   $Date:: 12/14/95 $
// $Archive: /Common/postit/skeleton/choosfol.h $
// $Header: /Common/postit/skeleton/choosfol.h 1     12/14/95 12:20p Flaven $
// $Logfile: /Common/postit/skeleton/choosfol.h $
// $Modtime: 12/14/95 12:20p $
// $Revision: 1 $
// $Workfile: choosfol.h $
//----------------------------------------------------------------------------
// $Log: /Common/postit/skeleton/choosfol.h $
// 
// 1     12/14/95 12:20p Flaven
// A Win95 improved version of CChooseDirectory.
//----------------------------------------------------------------------------
class CChooseFolder: public CObject
{
	DECLARE_DYNAMIC(CChooseFolder)

public:
// Attributes

// Constructors
	CChooseFolder(LPCTSTR lpstrInitialDir, UINT uiTitleString, CWnd* pParentWnd = NULL);
	CChooseFolder(LPCTSTR lpstrInitialDir=NULL, CWnd* pParentWnd = NULL);


// Implementation
	virtual int 	DoModal();
	const CString & GetDirName()	{ return m_selectedDir; }

private:
	void AjouteMedia( CString & MediaName );
	CString m_initialDir;
	CString m_selectedDir;
	CString	m_title;
	CWnd *m_pParent;
};
