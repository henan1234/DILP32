// Restriction.h: interface for the CRestriction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESTRICTION_H__B2F7B551_A241_11D3_A621_00A04B04180E__INCLUDED_)
#define AFX_RESTRICTION_H__B2F7B551_A241_11D3_A621_00A04B04180E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMail ;

class CRestriction  
{
public:
	typedef enum	{ FROM_CONTIENT, FROM_NE_CONTIENT_PAS,
					  TO_CONTIENT, TO_NE_CONTIENT_PAS,
					  SUBJECT_CONTIENT, SUBJECT_NE_CONTIENT_PAS }
			T_RULE ;
			CRestriction( T_RULE r, const CString & s) { _Rule = r; _Chaine = s ; }
	virtual ~CRestriction();

	BOOL	Convient( CMail * )  ;

	T_RULE	GetRule() { return _Rule ; }
	const CString	& GetText() { return _Chaine ; }
	
private:
	CString	_Chaine ;
	T_RULE	_Rule ;
};

#endif // !defined(AFX_RESTRICTION_H__B2F7B551_A241_11D3_A621_00A04B04180E__INCLUDED_)
