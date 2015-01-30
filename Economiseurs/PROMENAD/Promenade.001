# Microsoft Visual C++ Generated NMAKE File, Format Version 40000
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Promenade - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Promenade - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Promenade - Win32 Release" && "$(CFG)" !=\
 "Promenade - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Promenade.mak" CFG="Promenade - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Promenade - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Promenade - Win32 Debug" (based on "Win32 (x86) Application")
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
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Promenade - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir Release
# PROP BASE Intermediate_Dir Release
# PROP BASE Target_Dir
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir Release
# PROP Intermediate_Dir Release
# PROP Target_Dir
OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Release\Promenade.exe"

CLEAN : 
	-@erase ".\Release\Promenade.exe"
	-@erase ".\Release\Specif.obj"
	-@erase ".\Release\Econo.res"
	-@erase ".\Release\Econo.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Promenade.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Econo.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Promenade.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib comctl32.lib scrnsave.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib comctl32.lib scrnsave.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Promenade.pdb" /machine:I386\
 /out:"$(OUTDIR)/Promenade.exe" 
LINK32_OBJS= \
	".\Release\Specif.obj" \
	".\Release\Econo.obj" \
	".\Release\Econo.res"

".\Release\Promenade.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Promenade - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir Debug
# PROP BASE Intermediate_Dir Debug
# PROP BASE Target_Dir
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir Debug
# PROP Intermediate_Dir Debug
# PROP Target_Dir
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\Debug\Promenade.exe"

CLEAN : 
	-@erase ".\Debug\Promenade.exe"
	-@erase ".\Debug\Specif.obj"
	-@erase ".\Debug\Econo.res"
	-@erase ".\Debug\Econo.obj"
	-@erase ".\Debug\Promenade.ilk"
	-@erase ".\Debug\Promenade.pdb"
	-@erase ".\Debug\vc40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Promenade.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Econo.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Promenade.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib comctl32.lib scrnsave.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib comctl32.lib scrnsave.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Promenade.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Promenade.exe" 
LINK32_OBJS= \
	".\Debug\Specif.obj" \
	".\Debug\Econo.obj" \
	".\Debug\Econo.res"

".\Debug\Promenade.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Promenade - Win32 Release"
# Name "Promenade - Win32 Debug"

!IF  "$(CFG)" == "Promenade - Win32 Release"

!ELSEIF  "$(CFG)" == "Promenade - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Specif.c
DEP_CPP_SPECI=\
	".\..\specif.h"\
	

!IF  "$(CFG)" == "Promenade - Win32 Release"


".\Release\Specif.obj" : $(SOURCE) $(DEP_CPP_SPECI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Promenade - Win32 Debug"


".\Debug\Specif.obj" : $(SOURCE) $(DEP_CPP_SPECI) "$(INTDIR)"

".\Debug\vc40.pdb" : $(SOURCE) $(DEP_CPP_SPECI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Econo.rc
DEP_RSC_ECONO=\
	".\ECONO.ICO"\
	".\OMBRE.BMP"\
	

!IF  "$(CFG)" == "Promenade - Win32 Release"


".\Release\Econo.res" : $(SOURCE) $(DEP_RSC_ECONO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Promenade - Win32 Debug"


".\Debug\Econo.res" : $(SOURCE) $(DEP_RSC_ECONO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Economiseurs\Econo.c
DEP_CPP_ECONO_=\
	".\..\specif.h"\
	

!IF  "$(CFG)" == "Promenade - Win32 Release"


".\Release\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Promenade - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

".\Debug\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(BuildCmds)

".\Debug\vc40.pdb" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
