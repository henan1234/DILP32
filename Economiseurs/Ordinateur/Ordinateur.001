# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Ordinateur - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ordinateur - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ordinateur - Win32 Release" && "$(CFG)" !=\
 "Ordinateur - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ordinateur.mak" CFG="Ordinateur - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ordinateur - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ordinateur - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

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

ALL : "$(OUTDIR)\Ordinateur.exe"

CLEAN : 
	-@erase "$(INTDIR)\Case.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Ordinateur.obj"
	-@erase "$(INTDIR)\Ordinateur.res"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(OUTDIR)\Ordinateur.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Ordinateur.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ordinateur.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ordinateur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=scrnsave.lib winmm.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Ordinateur.pdb" /machine:I386 /out:"$(OUTDIR)/Ordinateur.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Case.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Ordinateur.obj" \
	"$(INTDIR)\Ordinateur.res" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Ordinateur.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

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

ALL : "$(OUTDIR)\Ordinateur.exe"

CLEAN : 
	-@erase "$(INTDIR)\Case.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Ordinateur.obj"
	-@erase "$(INTDIR)\Ordinateur.res"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Ordinateur.exe"
	-@erase "$(OUTDIR)\Ordinateur.ilk"
	-@erase "$(OUTDIR)\Ordinateur.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Ordinateur.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Ordinateur.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ordinateur.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Ordinateur.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Ordinateur.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Case.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Ordinateur.obj" \
	"$(INTDIR)\Ordinateur.res" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Ordinateur.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Ordinateur - Win32 Release"
# Name "Ordinateur - Win32 Debug"

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Stdafx.h

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Case.h

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ordinateur.cpp
DEP_CPP_ORDIN=\
	"..\Economiseur Generique\economiseur.h"\
	".\Case.h"\
	".\Ordinateur.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Ordinateur.obj" : $(SOURCE) $(DEP_CPP_ORDIN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ordinateur.h

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ordinateur.rc
DEP_RSC_ORDINA=\
	".\bip.wav"\
	".\icon1.ico"\
	

"$(INTDIR)\Ordinateur.res" : $(SOURCE) $(DEP_RSC_ORDINA) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "Ordinateur - Win32 Release"

!ELSEIF  "$(CFG)" == "Ordinateur - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Case.cpp
DEP_CPP_CASE_=\
	".\Case.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Case.obj" : $(SOURCE) $(DEP_CPP_CASE_) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\RegisterDialogClasses.c"

"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\Economiseur.cpp"
DEP_CPP_ECONO=\
	"..\Economiseur Generique\economiseur.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	"..\Economiseur generique\RectAffichage.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\Econo.cpp"
DEP_CPP_ECONO_=\
	"..\Economiseur Generique\economiseur.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
