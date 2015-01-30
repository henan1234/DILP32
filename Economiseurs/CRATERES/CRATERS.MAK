# Microsoft Visual C++ generated build script - Do not modify

PROJ = CRATERS
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = /s
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\CRATERS\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = SCRNSAVE.C  
FIRSTCPP =             
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AS /Od /D "_DEBUG" /D "STRICT" /GA /Fd"CRATERS.PDB"
CFLAGS_R_WEXE = /nologo /f- /Gs /G2 /W3 /AS /O2 /Oa /Ow /Oe /Og /Oi /Ol /Or /Ot /Ox /Ob2 /D "NDEBUG" /D "STRICT" /D "STRICT" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = oldnames libw slibcew commdlg.lib olecli.lib olesvr.lib scrnsave.lib shell.lib 
LIBS_R_WEXE = oldnames libw slibcew commdlg.lib olecli.lib olesvr.lib scrnsave.lib shell.lib 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = CRATERS.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = SCRNSAVE.SBR \
		CRATERS.SBR \
		RANDOM.SBR


SCRNSAVE_DEP = c:\craters\craters.h


CRATERS_RCDEP = c:\craters\craters.h


CRATERS_DEP = c:\craters\craters.h


RANDOM_DEP = 

all:	$(PROJ).EXE

SCRNSAVE.OBJ:	SCRNSAVE.C $(SCRNSAVE_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c SCRNSAVE.C

CRATERS.RES:	CRATERS.RC $(CRATERS_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r CRATERS.RC

CRATERS.OBJ:	CRATERS.C $(CRATERS_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c CRATERS.C

RANDOM.OBJ:	RANDOM.C $(RANDOM_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c RANDOM.C


$(PROJ).EXE::	CRATERS.RES

$(PROJ).EXE::	SCRNSAVE.OBJ CRATERS.OBJ RANDOM.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
SCRNSAVE.OBJ +
CRATERS.OBJ +
RANDOM.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\l\msvc\lib\+
d:\l\msvc\mfc\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) CRATERS.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	CRATERS.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) CRATERS.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
