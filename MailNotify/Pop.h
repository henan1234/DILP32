// Pop.h : main header file for the POP application
//

#if !defined(AFX_POP_H__A44B38B6_697C_11D1_881E_00001C302581__INCLUDED_)
#define AFX_POP_H__A44B38B6_697C_11D1_881E_00001C302581__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxsock.h>

#define CONNECTION_CHECK 0
#define USER_CHECK		1
#define PASSWORD_CHECK	2
#define QUIT_CHECK		3
#define DELETE_CHECK	4
#define RSET_CHECK		5 
#define STAT_CHECK		6 
#define NOOP_CHECK		7
#define LIST_CHECK		8
#define RETR_CHECK		9
#define RETR_HEADER		10

/////////////////////////////////////////////////////////////////////////////
// CPopApp:
// See Pop.cpp for the implementation of this class
//

class CPopApp : public CWinApp
{
public:
	CPopApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPopApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////


class CPop  
{
public:
	BOOL List();
	CWordArray m_SizeOfMsg;
	CString GetErrorMessage();
	CString GetPassword();
	void SetPassword(CString& Password);
	CString GetUser();
	void SetUser(CString& User);
	CString GetHost();
	void SetHost(CString& Host);
	BOOL Connect();
	int GetTotalMailSize();
	int GetNumberOfMails();
	CString GetMsgContents();
	BOOL Statistics();
	BOOL Retrieve(int MsgNumber);
	CString RetrieveHeader( int MsgNumber ) ;

	BOOL Reset();
	int  GetMessageSize(int MsgNumber);
	BOOL Noop();
	BOOL Disconnect();
	BOOL Delete(int& MsgNumber);
	BOOL Connect( const CString& Host, int Port, const CString& User, const CString& Password);
	CPop();
	virtual ~CPop();

	void SetPort( int p ) { m_Port = p ; }
	int GetPort()  { return m_Port ; }
private:
	CString m_ErrorMessage;
	BOOL CheckResponse(int ResponseType);
	CString m_Password;
	CString m_User;
	CString m_Host;
	CString m_MsgContents;
	CString m_HeaderContent ;
	int		m_Port ;
	int m_TotalSize;	
	int m_NumberMail;
	CSocket m_PopServer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POP_H__A44B38B6_697C_11D1_881E_00001C302581__INCLUDED_)
