# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=AuFeu - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to AuFeu - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "AuFeu - Win32 Release" && "$(CFG)" != "AuFeu - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Aufeu.mak" CFG="AuFeu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AuFeu - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "AuFeu - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "AuFeu - Win32 Release"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "AuFeu - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "$(OUTDIR)\AuFeu.scr"

CLEAN : 
	-@erase ".\WinRel\AuFeu.scr"
	-@erase ".\WinRel\AuFeu.obj"
	-@erase ".\WinRel\AuFeu.res"
	-@erase ".\WinRel\Econo.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Aufeu.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/AuFeu.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Aufeu.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 comctl32.lib kernel32.lib user32.lib gdi32.lib shell32.lib advapi32.lib comdlg32.lib scrnsave.lib \wing\lib\wing32.lib /nologo /subsystem:windows /machine:I386 /out:"WinRel/AuFeu.scr"
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=comctl32.lib kernel32.lib user32.lib gdi32.lib shell32.lib\
 advapi32.lib comdlg32.lib scrnsave.lib \wing\lib\wing32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/AuFeu.pdb" /machine:I386\
 /out:"$(OUTDIR)/AuFeu.scr" 
LINK32_OBJS= \
	".\WinRel\AuFeu.obj" \
	".\WinRel\Econo.obj" \
	".\WinRel\AuFeu.res"

"$(OUTDIR)\AuFeu.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "AuFeu - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\Aufeu.exe"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\Aufeu.exe"
	-@erase ".\WinDebug\AuFeu.obj"
	-@erase ".\WinDebug\AuFeu.res"
	-@erase ".\WinDebug\Econo.obj"
	-@erase ".\WinDebug\Aufeu.ilk"
	-@erase ".\WinDebug\Aufeu.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Aufeu.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/AuFeu.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Aufeu.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ole32.lib oleaut32.lib uuid.lib kernel32.lib user32.lib gdi32.lib shell32.lib advapi32.lib comdlg32.lib scrnsave.lib \wing\lib\wing32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=ole32.lib oleaut32.lib uuid.lib kernel32.lib user32.lib gdi32.lib\
 shell32.lib advapi32.lib comdlg32.lib scrnsave.lib \wing\lib\wing32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Aufeu.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/Aufeu.exe" 
LINK32_OBJS= \
	".\WinDebug\AuFeu.obj" \
	".\WinDebug\Econo.obj" \
	".\WinDebug\AuFeu.res"

"$(OUTDIR)\Aufeu.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "AuFeu - Win32 Release"
# Name "AuFeu - Win32 Debug"

!IF  "$(CFG)" == "AuFeu - Win32 Release"

!ELSEIF  "$(CFG)" == "AuFeu - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\AuFeu.c
DEP_CPP_AUFEU=\
	".\..\specif.h"\
	

"$(INTDIR)\AuFeu.obj" : $(SOURCE) $(DEP_CPP_AUFEU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuFeu.rc
DEP_RSC_AUFEU_=\
	".\Reference.bmp"\
	".\GAZ.bmp"\
	".\FLAMME16.bmp"\
	".\GAZ16.bmp"\
	".\CENDRE1.bmp"\
	".\CENDRE2.bmp"\
	".\PNEUS.bmp"\
	".\PNEUS16.bmp"\
	".\econo.ico"\
	".\lpi.ico"\
	

"$(INTDIR)\AuFeu.res" : $(SOURCE) $(DEP_RSC_AUFEU_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\lpi\Dilp32\Economiseurs\Econo.c
DEP_CPP_ECONO=\
	".\..\specif.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
