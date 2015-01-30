# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Orbites - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Orbites - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Orbites - Win32 Release" && "$(CFG)" !=\
 "Orbites - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Orbites.mak" CFG="Orbites - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Orbites - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Orbites - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Orbites - Win32 Debug"
MTL=mktyplib.exe
RSC=rc.exe
CPP=cl.exe

!IF  "$(CFG)" == "Orbites - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Orbites.exe"

CLEAN : 
	-@erase ".\Release\Orbites.exe"
	-@erase ".\Release\RectAffichage.obj"
	-@erase ".\Release\Orbites.obj"
	-@erase ".\Release\dibpal.obj"
	-@erase ".\Release\RegisterDialogClasses.obj"
	-@erase ".\Release\dib.obj"
	-@erase ".\Release\Econo.obj"
	-@erase ".\Release\Economiseur.obj"
	-@erase ".\Release\dibsurf.obj"
	-@erase ".\Release\Orbites.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Orbites.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Orbites.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Orbites.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib winmm.lib comctl32.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=scrnsave.lib winmm.lib comctl32.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Orbites.pdb" /machine:I386\
 /out:"$(OUTDIR)/Orbites.exe" 
LINK32_OBJS= \
	"$(INTDIR)/RectAffichage.obj" \
	"$(INTDIR)/Orbites.obj" \
	"$(INTDIR)/dibpal.obj" \
	"$(INTDIR)/RegisterDialogClasses.obj" \
	"$(INTDIR)/dib.obj" \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/Economiseur.obj" \
	"$(INTDIR)/dibsurf.obj" \
	"$(INTDIR)/Orbites.res"

"$(OUTDIR)\Orbites.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Orbites - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Orbites.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Orbites.exe"
	-@erase ".\Debug\RectAffichage.obj"
	-@erase ".\Debug\Economiseur.obj"
	-@erase ".\Debug\Econo.obj"
	-@erase ".\Debug\dib.obj"
	-@erase ".\Debug\dibsurf.obj"
	-@erase ".\Debug\dibpal.obj"
	-@erase ".\Debug\RegisterDialogClasses.obj"
	-@erase ".\Debug\Orbites.obj"
	-@erase ".\Debug\Orbites.res"
	-@erase ".\Debug\Orbites.ilk"
	-@erase ".\Debug\Orbites.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /O2 /Ob2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Orbites.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Orbites.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Orbites.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 scrnsave.lib winmm.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=scrnsave.lib winmm.lib comctl32.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Orbites.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Orbites.exe" 
LINK32_OBJS= \
	"$(INTDIR)/RectAffichage.obj" \
	"$(INTDIR)/Economiseur.obj" \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/dib.obj" \
	"$(INTDIR)/dibsurf.obj" \
	"$(INTDIR)/dibpal.obj" \
	"$(INTDIR)/RegisterDialogClasses.obj" \
	"$(INTDIR)/Orbites.obj" \
	"$(INTDIR)/Orbites.res"

"$(OUTDIR)\Orbites.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Orbites - Win32 Release"
# Name "Orbites - Win32 Debug"

!IF  "$(CFG)" == "Orbites - Win32 Release"

!ELSEIF  "$(CFG)" == "Orbites - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\RegisterDialogClasses.c"

"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\dibpal.cpp"
DEP_CPP_DIBPA=\
	".\..\Economiseur Generique\animate.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\dibsurf.cpp"
DEP_CPP_DIBSU=\
	".\..\Economiseur Generique\animate.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\dibsurf.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\Econo.cpp"
DEP_CPP_ECONO=\
	".\..\Economiseur Generique\Economiseur.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\Economiseur.cpp"
DEP_CPP_ECONOM=\
	".\..\Economiseur Generique\Economiseur.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	".\..\Economiseur Generique\RectAffichage.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur Generique\dib.cpp"
DEP_CPP_DIB_C=\
	".\..\Economiseur Generique\animate.h"\
	".\..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Orbites.rc
DEP_RSC_ORBIT=\
	".\dib2.bin"\
	

"$(INTDIR)\Orbites.res" : $(SOURCE) $(DEP_RSC_ORBIT) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Orbites.cpp
DEP_CPP_ORBITE=\
	".\..\Economiseur Generique\stdafx.h"\
	".\..\Economiseur Generique\animate.h"\
	".\..\Economiseur Generique\RectAffichage.h"\
	".\Orbites.h"\
	".\..\Economiseur Generique\Economiseur.h"\
	

"$(INTDIR)\Orbites.obj" : $(SOURCE) $(DEP_CPP_ORBITE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
