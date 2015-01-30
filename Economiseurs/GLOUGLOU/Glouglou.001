# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=glouglou - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to glouglou - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "glouglou - Win32 Release" && "$(CFG)" !=\
 "glouglou - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Glouglou.mak" CFG="glouglou - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "glouglou - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "glouglou - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "glouglou - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "glouglou - Win32 Release"

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

ALL : "$(OUTDIR)\glouglou.scr"

CLEAN : 
	-@erase "$(INTDIR)\bulles.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Glouglou.obj"
	-@erase "$(INTDIR)\glougou.res"
	-@erase "$(INTDIR)\gouttes.obj"
	-@erase "$(OUTDIR)\glouglou.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /ML /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Glouglou.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/glougou.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Glouglou.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/glouglou.scr"
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/glouglou.pdb" /machine:I386\
 /out:"$(OUTDIR)/glouglou.scr" 
LINK32_OBJS= \
	"$(INTDIR)\bulles.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Glouglou.obj" \
	"$(INTDIR)\glougou.res" \
	"$(INTDIR)\gouttes.obj"

"$(OUTDIR)\glouglou.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "glouglou - Win32 Debug"

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

ALL : "$(OUTDIR)\Glouglou.exe"

CLEAN : 
	-@erase "$(INTDIR)\bulles.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Glouglou.obj"
	-@erase "$(INTDIR)\glougou.res"
	-@erase "$(INTDIR)\gouttes.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Glouglou.exe"
	-@erase "$(OUTDIR)\Glouglou.ilk"
	-@erase "$(OUTDIR)\Glouglou.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /Gm /Zi /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MLd /W3 /Gm /Zi /O1 /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Glouglou.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/glougou.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Glouglou.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib scrnsave.lib comctl32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Glouglou.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Glouglou.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bulles.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Glouglou.obj" \
	"$(INTDIR)\glougou.res" \
	"$(INTDIR)\gouttes.obj"

"$(OUTDIR)\Glouglou.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "glouglou - Win32 Release"
# Name "glouglou - Win32 Debug"

!IF  "$(CFG)" == "glouglou - Win32 Release"

!ELSEIF  "$(CFG)" == "glouglou - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Glouglou.c
DEP_CPP_GLOUG=\
	"..\specif.h"\
	".\Glouglou.h"\
	

"$(INTDIR)\Glouglou.obj" : $(SOURCE) $(DEP_CPP_GLOUG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\bulles.c
DEP_CPP_BULLE=\
	"..\specif.h"\
	".\Glouglou.h"\
	

"$(INTDIR)\bulles.obj" : $(SOURCE) $(DEP_CPP_BULLE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\gouttes.c
DEP_CPP_GOUTT=\
	"..\specif.h"\
	".\Glouglou.h"\
	

"$(INTDIR)\gouttes.obj" : $(SOURCE) $(DEP_CPP_GOUTT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\glougou.rc
DEP_RSC_GLOUGO=\
	".\bmp00001.bmp"\
	".\Bulle1.bmp"\
	".\Bulle2.bmp"\
	".\Bulle3.bmp"\
	".\Eclate1.bmp"\
	".\Eclate2.bmp"\
	".\Eclate3.bmp"\
	".\goutte1.bmp"\
	".\goutte_1.bmp"\
	".\goutte_2.bmp"\
	".\goutte_3.bmp"\
	".\goutte_4.bmp"\
	".\goutte_5.bmp"\
	".\goutte_6.bmp"\
	".\goutte_7.bmp"\
	".\goutte_8.bmp"\
	".\goutte_9.bmp"\
	".\icon1.ico"\
	".\lpi.ico"\
	".\Vague.bmp"\
	".\Vague2.bmp"\
	".\Vague3.bmp"\
	".\Vague4.bmp"\
	

"$(INTDIR)\glougou.res" : $(SOURCE) $(DEP_RSC_GLOUGO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Economiseurs\Econo.c
DEP_CPP_ECONO=\
	"..\specif.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
