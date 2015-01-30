// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxtempl.h>		// Collection templates

#ifndef TCM_GETBKCOLOR
#pragma message ( "attention ! incoherence des .h pour TCM_GETBKCOLOR" )
#define TCM_FIRST               0x1300
#define TCM_GETBKCOLOR          (TCM_FIRST + 0)
#define TCM_SETBKCOLOR          (TCM_FIRST + 1)
#endif

#include <afxcmn.h>
#include <scrnsave.h>