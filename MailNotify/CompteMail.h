// CompteMail.h: interface for the CCompteMail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPTEMAIL_H__8A90C0C8_9696_11D3_A61A_00A04B04180E__INCLUDED_)
#define AFX_COMPTEMAIL_H__8A90C0C8_9696_11D3_A61A_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>

class CMail ;
class CRestriction ;

class CCompteMail  
{
public:
	void SupprimeMails();
	void SupprimeMail( CMail * pMail );
	void AcknowledgeMail( CMail * pMail, BOOL bState );
	int NbNotAcknowledged();
	CCompteMail( LPCTSTR Nom, LPCTSTR Serveur, int Port, LPCTSTR UserName, LPCTSTR Password )
		{
		_Nom		=	Nom ;
		_Serveur	=	Serveur ;
		_Port		=	Port ;
		_UserName	=	UserName ;
		_Password	=	Password ;
		}

	virtual ~CCompteMail();

	const CString & Nom() { return _Nom ; } ;
	void	Nom( const CString & N ) { _Nom = N ; }

	const CString & Serveur() { return _Serveur ; }
	void	Serveur( const CString & S ) { _Serveur	=	S ; }
	
	int		Port() { return _Port ; }
	void	Port( int p ) { _Port = p ; }

	const CString & UserName() { return _UserName ; }
	void	UserName( const CString & N ) { _UserName	=	N ; }

	const CString & Password() { return _Password ; }
	void Password( const CString & p ) { _Password = p ; }

	int	Check() ;
	int	GetNbMails() const { return _Mails.GetSize() ; }
	const CMail*	GetMail( int i ) { return _Mails[i] ; }

	int	GetNbRestrictions() const { return _Restrictions.GetSize() ; }
	void AddRestriction( CRestriction * p ) { _Restrictions.Add( p ) ; }
	CRestriction*	GetRestriction( int i ) { return _Restrictions[i] ; }
		


private:
	BOOL ExisteDeja( CMail * );
	BOOL Convient( CMail * );
	CString	_Nom ;
	CString	_Serveur ;
	int		_Port ;
	CString	_UserName ;
	CString _Password ;

	int		_NbMails ;

	CArray<CMail*, CMail*> _Mails ;
	CArray<CRestriction	*, CRestriction*> _Restrictions ;
};

#endif // !defined(AFX_COMPTEMAIL_H__8A90C0C8_9696_11D3_A61A_00A04B04180E__INCLUDED_)
