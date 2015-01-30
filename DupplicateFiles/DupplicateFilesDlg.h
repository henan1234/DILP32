// DupplicateFilesDlg.h : header file
//

#if !defined(AFX_DUPPLICATEFILESDLG_H__91606A87_40E1_11D2_B79A_0000E8D9BF74__INCLUDED_)
#define AFX_DUPPLICATEFILESDLG_H__91606A87_40E1_11D2_B79A_0000E8D9BF74__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDupplicateFilesDlg dialog
typedef struct
	{
	TCHAR		Name[_MAX_PATH] ;
	_int64		Size ;
	HTREEITEM	hItem ;
	}
	T_FILES_ATTRIBUTE ;

class CScanningDlg ;

class CDupplicateFilesDlg : public CDialog
{
// Construction
public:
	CDupplicateFilesDlg(CWnd* pParent = NULL);	// standard constructor
	CString		_CommandLine ;

// Dialog Data
	//{{AFX_DATA(CDupplicateFilesDlg)
	enum { IDD = IDD_DUPPLICATEFILES_DIALOG };
	CButton	m_DeleteFile;
	CButton	m_ShowDups;
	CButton	m_Prev;
	CButton	m_Open;
	CButton	m_Next;
	CButton	m_DeleteAll;
	CButton	m_Delete;
	CTreeCtrl	m_FileTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDupplicateFilesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDupplicateFilesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnDelete();
	afx_msg void OnOpen();
	afx_msg void OnShowDupp();
	afx_msg void OnDeleteAll();
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeletefile();
	afx_msg void OnDeleteMultiple();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CMapStringToPtr m_Extensions;
	int GetIconIndex( const TCHAR * pFileName );
	void DeleteListOfFiles( CStringArray & FilesToDelete, CDWordArray & );
	void DeleteFilesFromTree( CStringArray & ListOfFiles, CDWordArray & );
	static BOOL FileUnderPath( const TCHAR * Dir, const TCHAR * File );
	void AddFilesFromItemDirectory( HTREEITEM, const TCHAR *, CStringArray &, CDWordArray & );
	void BrowseDuplicatedFilesUnderDir( CStringArray & ListOfFiles, CDWordArray &, const TCHAR * pDir );
	void DeleteDuplicatedContaining( const TCHAR * );
	void DeleteDuplicatedUnderDir( const TCHAR * );
	void DeleteAllDuplicated();
	int _DuplicatedFound;
	int _ProcessedFiles;
	BOOL DeleteFiles( const CString & );
	int _DecalageBouton;
	void ParcoursRepertoire( const TCHAR *, T_FILES_ATTRIBUTE * &, int*, int*, CScanningDlg * );
	BOOL TraiteCommandLine();
	static _int64 GetFileLength( const TCHAR * pChar );
	CImageList _IconList ;
	static BOOL MemeContenu( const TCHAR * pFile1, CStdioFile & );
	void AddFile( const TCHAR *, T_FILES_ATTRIBUTE*, int *, _int64 );
	void AddDupplicate( HTREEITEM, const TCHAR *, CScanningDlg * );
	HTREEITEM GetDupplicate( const TCHAR *, T_FILES_ATTRIBUTE*, int, _int64 *, CScanningDlg * );
	void FillFiles();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUPPLICATEFILESDLG_H__91606A87_40E1_11D2_B79A_0000E8D9BF74__INCLUDED_)
