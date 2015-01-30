#include "stdafx.h"
#include <winnetwk.h>
#include <shlobj.h>
#include "choosfol.h"

#ifndef BFFM_SETSELECTION	// some versions of shlobj.h miss this symbol
#define BFFM_SETSELECTION	(WM_USER + 102)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CChooseFolder,CObject)

static int CALLBACK BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData);

CChooseFolder::CChooseFolder(LPCTSTR lpstrInitialDir, UINT uiTitleString, CWnd* pParentWnd)
{
	m_initialDir = lpstrInitialDir;
	m_title.LoadString(uiTitleString);
	m_pParent = pParentWnd;
}

CChooseFolder::CChooseFolder(LPCTSTR lpstrInitialDir, CWnd* pParentWnd)
{
	if (lpstrInitialDir)
		m_initialDir = lpstrInitialDir;
	m_pParent = pParentWnd;
}

int CChooseFolder::DoModal()
{
   	BROWSEINFO bi; 
    LPSTR lpBuffer; 
    LPITEMIDLIST pidlBrowse;    // PIDL selected by user
    int nRet = IDCANCEL;
	LPMALLOC pMalloc = NULL;
 
    // if the initial directory ends with \, remove the trailing \ (except for C:\, of course) 
	if (m_initialDir.GetLength() > 3)
	{
		if (m_initialDir.Right(1) == _T("\\"))
			m_initialDir = m_initialDir.Left(m_initialDir.GetLength() - 1);
	}

    VERIFY(S_OK == SHGetMalloc(&pMalloc) );
    
    // Allocate a buffer to receive browse information. 
    if ((lpBuffer = (LPSTR) pMalloc->Alloc(MAX_PATH)) == NULL) 
        return IDCANCEL; 
  
    // Fill in the BROWSEINFO structure. 
    bi.hwndOwner = m_pParent ? m_pParent->m_hWnd : NULL; 
    bi.pidlRoot = NULL;	// allow selection starting from the Desktop 
    bi.pszDisplayName = lpBuffer; 
    bi.lpszTitle = (LPCTSTR) m_title; 
    bi.ulFlags = 0; 
    bi.lpfn = (BFFCALLBACK)BrowseCallbackProc;
    if (m_initialDir.IsEmpty())
    	bi.lParam = NULL;
    else 
    	bi.lParam = (long)(LPCTSTR) m_initialDir; 
 
    // Browse for a folder and return its PIDL. 
    pidlBrowse = SHBrowseForFolder(&bi); 
    if (pidlBrowse != NULL)
    { 
		// Retrieve the path to the selected folder. 
        VERIFY(SHGetPathFromIDList(pidlBrowse, lpBuffer)); 
       	m_selectedDir = lpBuffer; 
 
        // Free the PIDL returned by SHBrowseForFolder. 
		pMalloc->Free(pidlBrowse);
		nRet = IDOK; 
    }
 
    // Clean up. 
    pMalloc->Free(lpBuffer);
    
    return nRet; 
}

int CALLBACK BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
{
	if (uMsg == BFFM_SELCHANGED)
	{
		// lParam points to the PIDL of the selected object
		SHFILEINFO shfi;
		DWORD dwAttrib = 0;

		if (SHGetFileInfo((LPCTSTR)lParam, dwAttrib, &shfi, sizeof(shfi), SHGFI_PIDL|SHGFI_ATTRIBUTES))
		{
			if (shfi.dwAttributes & SFGAO_FILESYSTEM)	// folder or root folder
				::SendMessage( hwnd, BFFM_ENABLEOK, 1,1);	// enable the OK button
			else	
				::SendMessage( hwnd, BFFM_ENABLEOK, 0,0);	// disable the OK button
		}
		else
			::SendMessage( hwnd, BFFM_ENABLEOK, 0,0);	// disable the OK button
			
	}
	else if ( uMsg == BFFM_INITIALIZED)
	{
		// if an initial dir is specified, select it now
		if (lpData)
			::SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);	// TRUE means lpData is a Path and not a Pidl
	}
	return 0;
}
