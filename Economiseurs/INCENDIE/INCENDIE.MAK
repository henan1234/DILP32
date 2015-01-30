# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Incendie - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Incendie - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Incendie - Win32 Release" && "$(CFG)" !=\
 "Incendie - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Incendie.mak" CFG="Incendie - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Incendie - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Incendie - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Incendie - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Incendie - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Incendie.scr" "$(OUTDIR)\Incendie.bsc"

CLEAN : 
	-@erase ".\Release\Incendie.bsc"
	-@erase ".\Release\Econo.sbr"
	-@erase ".\Release\Incendie.sbr"
	-@erase ".\Release\Incendie.scr"
	-@erase ".\Release\Incendie.obj"
	-@erase ".\Release\Econo.obj"
	-@erase ".\Release\Incendie.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Incendie.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Incendie.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Incendie.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/Econo.sbr" \
	"$(INTDIR)/Incendie.sbr"

"$(OUTDIR)\Incendie.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib wing32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Incendie.scr"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib wing32.lib scrnsave.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Incendie.pdb" /machine:I386\
 /out:"$(OUTDIR)/Incendie.scr" 
LINK32_OBJS= \
	"$(INTDIR)/Incendie.obj" \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/Incendie.res"

"$(OUTDIR)\Incendie.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Incendie - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Incendie.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Incendie.exe"
	-@erase ".\Debug\Econo.obj"
	-@erase ".\Debug\Incendie.obj"
	-@erase ".\Debug\Incendie.res"
	-@erase ".\Debug\Incendie.ilk"
	-@erase ".\Debug\Incendie.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Incendie.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Incendie.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Incendie.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib wing32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib wing32.lib scrnsave.lib comctl32.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Incendie.pdb" /debug\
 /machine:I386 /out:"$(OUTDIR)/Incendie.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/Incendie.obj" \
	"$(INTDIR)/Incendie.res"

"$(OUTDIR)\Incendie.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Incendie - Win32 Release"
# Name "Incendie - Win32 Debug"

!IF  "$(CFG)" == "Incendie - Win32 Release"

!ELSEIF  "$(CFG)" == "Incendie - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Incendie.c
DEP_CPP_INCEN=\
	".\..\specif.h"\
	{$(INCLUDE)}"\Wing.h"\
	

!IF  "$(CFG)" == "Incendie - Win32 Release"


"$(INTDIR)\Incendie.obj" : $(SOURCE) $(DEP_CPP_INCEN) "$(INTDIR)"

"$(INTDIR)\Incendie.sbr" : $(SOURCE) $(DEP_CPP_INCEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Incendie - Win32 Debug"


"$(INTDIR)\Incendie.obj" : $(SOURCE) $(DEP_CPP_INCEN) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Incendie.rc
DEP_RSC_INCEND=\
	".\Reference.bmp"\
	".\GAZ.bmp"\
	".\FLAMME16.bmp"\
	".\GAZ16.bmp"\
	".\CENDRE1.bmp"\
	".\PNEUS.bmp"\
	".\PNEUS16.bmp"\
	".\econo.ico"\
	".\lpi.ico"\
	

"$(INTDIR)\Incendie.res" : $(SOURCE) $(DEP_RSC_INCEND) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Economiseurs\Econo.c
DEP_CPP_ECONO=\
	".\..\specif.h"\
	

!IF  "$(CFG)" == "Incendie - Win32 Release"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Econo.sbr" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Incendie - Win32 Debug"


"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
