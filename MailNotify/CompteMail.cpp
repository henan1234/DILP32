// CompteMail.cpp: implementation of the CCompteMail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CompteMail.h"
#include "restriction.h"
#include "mail.h"
#include "pop.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern HWND		hwndMain ;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CCompteMail::~CCompteMail()
{

}


int CCompteMail::Check()
	{
	/*for (int i = 0; i < _Mails.GetSize(); i++)
		delete _Mails[i] ;

	_Mails.RemoveAll() ;
	*/

	CPop PopServer;
	if( ! PopServer.Connect( Serveur(), Port() ,UserName(), Password()))
		return 0 ;

	if ( ! PopServer.Statistics())
		return 0 ;

	const int NbMails = PopServer.GetNumberOfMails();
	
	for ( int i = 0; i < NbMails; i++)
		{
		PopServer.Retrieve( i+1 ) ;
		CString Content	=	PopServer.GetMsgContents() ;

		CMail *	pMail	=	new CMail( Content ) ;

		if ( Convient( pMail ) && !ExisteDeja( pMail ))
			_Mails.Add( pMail ) ;
		else
			delete pMail ;
		}
	
	PopServer.Disconnect() ;

	return NbNotAcknowledged() ;
	}

///////////////////////////////////////////////////////////////////////////////
// Convient
// Verifie qu'un mail ne transgresse aucune des restrictions du compte
//	ENTREES:	@ d'un mail
//	RETOUR :	TRUE si le mail convient
///////////////////////////////////////////////////////////////////////////////
BOOL CCompteMail::Convient(CMail * pMail )
{
	for ( int i = 0; i < _Restrictions.GetSize(); i++)
		if ( ! _Restrictions[i]->Convient( pMail ))
			return FALSE ;

	return TRUE ;
}

int CCompteMail::NbNotAcknowledged()
{
	int Nb = 0 ;

	for ( int i = 0; i < _Mails.GetSize(); i++)
		if ( ! _Mails[i]->Acknowledged())
			Nb ++ ;

	return Nb ;
}

BOOL CCompteMail::ExisteDeja(CMail * pMail )
{
	const CString Id	=	pMail->Id() ;

	for ( int i = 0; i < _Mails.GetSize(); i++)
		{
		CMail* pMailCourant	=	_Mails[i] ;
		if ( Id == pMailCourant->Id() )
			return TRUE ;

		if ( pMail->From() == pMailCourant->From() &&
			 pMail->Content() == pMailCourant->Content() &&
			 pMail->Subject() == pMailCourant->Subject())
			 return TRUE ;
		}
	return FALSE ;
}


void CCompteMail::SupprimeMail(CMail *pZeMail)
{
	for ( int i = 0; i < _Mails.GetSize(); i++)
		{
		CMail * pMail	=	_Mails[i] ;
		if ( pMail == pZeMail )
			{
			_Mails.RemoveAt( i ) ;
			return ;
			}
		}
}

void CCompteMail::SupprimeMails()
{
	for ( int i = 0; i < _Mails.GetSize(); i++)
		{
		CMail * pMail	=	_Mails[i] ;
		delete _Mails[i] ;
		}

	_Mails.RemoveAll() ;
	_NbMails	=	0 ;
}
