// MyTree.h: interface for the CMyTree class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYTREE_H__A9B42074_1C11_4828_9ABD_89DD8D0BAB96__INCLUDED_)
#define AFX_MYTREE_H__A9B42074_1C11_4828_9ABD_89DD8D0BAB96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyTree : public CTreeCtrl  
{
	DECLARE_MESSAGE_MAP(  ) ;
public:

	virtual void OnPaint();
	CMyTree();
	virtual ~CMyTree();

	void	SetHeaderCtrl( CHeaderCtrl* pH ) { _pHeader = pH ; }

private:
	void AfficheElement( CDC & DC, HTREEITEM hItem );
	CHeaderCtrl *	_pHeader ;
};

#endif // !defined(AFX_MYTREE_H__A9B42074_1C11_4828_9ABD_89DD8D0BAB96__INCLUDED_)
