# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Brownien - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Brownien - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Brownien - Win32 Release" && "$(CFG)" !=\
 "Brownien - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Brownien.mak" CFG="Brownien - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Brownien - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Brownien - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Brownien - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Brownien - Win32 Release"

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

ALL : "$(OUTDIR)\Brownien.scr"

CLEAN : 
	-@erase "$(INTDIR)\Brownien.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\DibSurface.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Econo.res"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(OUTDIR)\Brownien.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Brownien.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Econo.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Brownien.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Brownien.scr"
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Brownien.pdb" /machine:I386\
 /out:"$(OUTDIR)/Brownien.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Brownien.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\DibSurface.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Econo.res" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Brownien.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Brownien - Win32 Debug"

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

ALL : "$(OUTDIR)\Brownien.scr"

CLEAN : 
	-@erase "$(INTDIR)\Brownien.obj"
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\DibSurface.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Econo.res"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Brownien.ilk"
	-@erase "$(OUTDIR)\Brownien.pdb"
	-@erase "$(OUTDIR)\Brownien.scr"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Brownien.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Econo.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Brownien.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/Brownien.scr"
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Brownien.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Brownien.scr" 
LINK32_OBJS= \
	"$(INTDIR)\Brownien.obj" \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\DibSurface.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Econo.res" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Brownien.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Brownien - Win32 Release"
# Name "Brownien - Win32 Debug"

!IF  "$(CFG)" == "Brownien - Win32 Release"

!ELSEIF  "$(CFG)" == "Brownien - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Brownien.h

!IF  "$(CFG)" == "Brownien - Win32 Release"

!ELSEIF  "$(CFG)" == "Brownien - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Econo.rc
DEP_RSC_ECONO=\
	".\Econo.ico"\
	".\lpi.ico"\
	".\Particules.dib"\
	

"$(INTDIR)\Econo.res" : $(SOURCE) $(DEP_RSC_ECONO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "Brownien - Win32 Release"

!ELSEIF  "$(CFG)" == "Brownien - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Brownien.cpp
DEP_CPP_BROWN=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\Dibpal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\Economiseur Generique\stdafx.h"\
	".\Brownien.h"\
	".\Page1.h"\
	".\page2.h"\
	

"$(INTDIR)\Brownien.obj" : $(SOURCE) $(DEP_CPP_BROWN) "$(INTDIR)"


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
DEP_CPP_ECONOM=\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\DibSurface.cpp
DEP_CPP_DIBSU=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\Dibpal.h"\
	"..\..\Classes\DibSurface.h"\
	

"$(INTDIR)\DibSurface.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\Dibpal.cpp
DEP_CPP_DIBPA=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\Dibpal.h"\
	

"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\Dib.cpp
DEP_CPP_DIB_C=\
	"..\..\Classes\Dib.h"\
	

"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.cpp
DEP_CPP_PAGE2=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\Dibpal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\Brownien.h"\
	".\page2.h"\
	

"$(INTDIR)\Page2.obj" : $(SOURCE) $(DEP_CPP_PAGE2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.cpp
DEP_CPP_PAGE1=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\Dibpal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\Brownien.h"\
	".\Page1.h"\
	

"$(INTDIR)\Page1.obj" : $(SOURCE) $(DEP_CPP_PAGE1) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\Econo.cpp"
DEP_CPP_ECONO_=\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\stdafx.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
