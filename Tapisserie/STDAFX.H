/// Precomp.h fichier d'entete precompile
#include <afxwin.h>
#include <afxdlgs.h>
#include <afxext.h>

#ifndef TCM_GETBKCOLOR
#pragma message ( "attention ! incoherence des .h pour TCM_GETBKCOLOR" )
#define TCM_FIRST               0x1300
#define TCM_GETBKCOLOR          (TCM_FIRST + 0)
#define TCM_SETBKCOLOR          (TCM_FIRST + 1)
#endif

#include <afxcmn.h>
