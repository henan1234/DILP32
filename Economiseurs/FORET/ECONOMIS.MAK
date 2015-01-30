# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "FORET.SCR" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ECONOMIS.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FORET.SCR" (based on "Win32 (x86) Application")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "FORET.SCR"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FORET.SCR"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : .\WinRel\Foret.scr .\WinRel\ECONOMIS.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /vmg /GX /YX"windows.h" /Ox /Ot /Oi /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Fp"STARSAVE.PCH" /c
# ADD CPP /nologo /MT /W3 /vmg /GX /YX"windows.h" /O1 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Fp"STARSAVE.PCH" /c
CPP_PROJ=/nologo /MT /W3 /vmg /GX /YX"windows.h" /O1 /Ob2 /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR$(INTDIR)/ /Fp"STARSAVE.PCH" /Fo$(INTDIR)/\
 /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"ECONO.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"ECONOMIS.bsc" 
BSC32_SBRS= \
	.\WinRel\SPECIF.SBR \
	.\WinRel\PAYSAG.SBR \
	.\WinRel\ECONO.SBR

.\WinRel\ECONOMIS.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib scrnsave.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib oldnames.lib scrnsave.lib comctl32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /MACHINE:IX86 /OUT:"WinRel/Foret.scr"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib oldnames.lib\
 scrnsave.lib comctl32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows\
 /INCREMENTAL:no /PDB:$(OUTDIR)/"ECONOMIS.pdb" /MACHINE:IX86\
 /OUT:"WinRel/Foret.scr" 
DEF_FILE=
LINK32_OBJS= \
	.\WinRel\SPECIF.OBJ \
	.\WinRel\ECONO.res \
	.\WinRel\PAYSAG.OBJ \
	.\WinRel\ECONO.OBJ

.\WinRel\Foret.scr : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : .\WinDebug\ECONOMIS.exe .\WinDebug\ECONOMIS.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX"windows.h" /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Fp"STARSAVE.PCH" /c
# ADD CPP /nologo /MT /W3 /GX /Zi /YX"windows.h" /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Fp"STARSAVE.PCH" /c
CPP_PROJ=/nologo /MT /W3 /GX /Zi /YX"windows.h" /O2 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /FR$(INTDIR)/ /Fp"STARSAVE.PCH" /Fo$(INTDIR)/\
 /Fd$(OUTDIR)/"ECONOMIS.pdb" /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo$(INTDIR)/"ECONO.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o$(OUTDIR)/"ECONOMIS.bsc" 
BSC32_SBRS= \
	.\WinDebug\SPECIF.SBR \
	.\WinDebug\PAYSAG.SBR \
	.\WinDebug\ECONO.SBR

.\WinDebug\ECONOMIS.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 oldnames.lib scrnsave.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
# ADD LINK32 oldnames.lib scrnsave.lib comctl32.lib /NOLOGO /STACK:0x10240 /SUBSYSTEM:windows /DEBUG /MACHINE:IX86
LINK32_FLAGS=oldnames.lib scrnsave.lib comctl32.lib /NOLOGO /STACK:0x10240\
 /SUBSYSTEM:windows /INCREMENTAL:yes /PDB:$(OUTDIR)/"ECONOMIS.pdb" /DEBUG\
 /MACHINE:IX86 /OUT:$(OUTDIR)/"ECONOMIS.exe" 
DEF_FILE=
LINK32_OBJS= \
	.\WinDebug\SPECIF.OBJ \
	.\WinDebug\ECONO.res \
	.\WinDebug\PAYSAG.OBJ \
	.\WinDebug\ECONO.OBJ

.\WinDebug\ECONOMIS.exe : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
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

################################################################################
# Begin Group "Source Files"

################################################################################
# Begin Source File

SOURCE=.\SPECIF.C
DEP_SPECI=\
	..\SPECIF.H

!IF  "$(CFG)" == "FORET.SCR"

.\WinRel\SPECIF.OBJ :  $(SOURCE)  $(DEP_SPECI) $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\SPECIF.OBJ :  $(SOURCE)  $(DEP_SPECI) $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ECONO.RC
DEP_ECONO=\
	.\ECONO.ICO\
	.\ISL.ICO\
	.\LPI.ICO\
	..\ECONO.H

!IF  "$(CFG)" == "FORET.SCR"

.\WinRel\ECONO.res :  $(SOURCE)  $(DEP_ECONO) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\ECONO.res :  $(SOURCE)  $(DEP_ECONO) $(INTDIR)
   $(RSC) $(RSC_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PAYSAG.C

!IF  "$(CFG)" == "FORET.SCR"

.\WinRel\PAYSAG.OBJ :  $(SOURCE)  $(INTDIR)

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\PAYSAG.OBJ :  $(SOURCE)  $(INTDIR)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Economiseurs\ECONO.C
DEP_ECONO_=\
	..\ECONO.H\
	..\SPECIF.H

!IF  "$(CFG)" == "FORET.SCR"

.\WinRel\ECONO.OBJ :  $(SOURCE)  $(DEP_ECONO_) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ELSEIF  "$(CFG)" == "Win32 Debug"

.\WinDebug\ECONO.OBJ :  $(SOURCE)  $(DEP_ECONO_) $(INTDIR)
   $(CPP) $(CPP_PROJ)  $(SOURCE) 

!ENDIF 

# End Source File
# End Group
# End Project
################################################################################
