///////////////////////////////////////////////////////////////////////////////
// Classe pour mettre une fonction critique non interruptible dans un thread
///////////////////////////////////////////////////////////////////////////////
#ifndef _CRITICALBLOCK_H_
#define _CRITICALBLOCK_H_

#ifndef __AFXMT_H__
#include <afxmt.h>
#endif

class	CCriticalBlock : private	CCriticalSection
	{
	public	:
		CCriticalBlock( ) { Lock() ; } ;
		~CCriticalBlock() { Unlock() ; } ;
	} ;
#endif
