# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Gravitation - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Gravitation - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Gravitation - Win32 Release" && "$(CFG)" !=\
 "Gravitation - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gravitation.mak" CFG="Gravitation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gravitation - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gravitation - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Gravitation - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Gravitation - Win32 Release"

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

ALL : "$(OUTDIR)\Gravitation.scr" ".\toto" ".\tot"

CLEAN : 
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\DibSurface.obj"
	-@erase "$(INTDIR)\DlgParametres.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Econo.res"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Gravitation.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\PageAffichage.obj"
	-@erase "$(INTDIR)\PageComete.obj"
	-@erase "$(INTDIR)\PageGenese.obj"
	-@erase "$(INTDIR)\PageMasses.obj"
	-@erase "$(INTDIR)\PagePhysique.obj"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(OUTDIR)\Gravitation.scr"
	-@erase ".\tot"
	-@erase ".\toto"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /G5 /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Econo.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Gravitation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib scrnsave.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Gravitation.scr"
LINK32_FLAGS=winmm.lib scrnsave.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Gravitation.pdb" /machine:I386 /out:"$(OUTDIR)/Gravitation.scr"\
 
LINK32_OBJS= \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\DibSurface.obj" \
	"$(INTDIR)\DlgParametres.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Econo.res" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Gravitation.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\PageAffichage.obj" \
	"$(INTDIR)\PageComete.obj" \
	"$(INTDIR)\PageGenese.obj" \
	"$(INTDIR)\PageMasses.obj" \
	"$(INTDIR)\PagePhysique.obj" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Gravitation.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

# Begin Custom Build
TargetPath=.\Release\Gravitation.scr
InputPath=.\Release\Gravitation.scr
SOURCE=$(InputPath)

BuildCmds= \
	copy $(TargetPath) c:\windows\system \
	copy $(TargetPath) "d:\public\livraison" \
	

"toto" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"tot" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

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

ALL : "$(OUTDIR)\Gravitation.exe"

CLEAN : 
	-@erase "$(INTDIR)\Dib.obj"
	-@erase "$(INTDIR)\Dibpal.obj"
	-@erase "$(INTDIR)\DibSurface.obj"
	-@erase "$(INTDIR)\DlgParametres.obj"
	-@erase "$(INTDIR)\Econo.obj"
	-@erase "$(INTDIR)\Econo.res"
	-@erase "$(INTDIR)\Economiseur.obj"
	-@erase "$(INTDIR)\Gravitation.obj"
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\PageAffichage.obj"
	-@erase "$(INTDIR)\PageComete.obj"
	-@erase "$(INTDIR)\PageGenese.obj"
	-@erase "$(INTDIR)\PageMasses.obj"
	-@erase "$(INTDIR)\PagePhysique.obj"
	-@erase "$(INTDIR)\RectAffichage.obj"
	-@erase "$(INTDIR)\RegisterDialogClasses.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Gravitation.exe"
	-@erase "$(OUTDIR)\Gravitation.ilk"
	-@erase "$(OUTDIR)\Gravitation.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /Ob2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /c
# SUBTRACT CPP /YX /Yc /Yu
CPP_PROJ=/nologo /G5 /MTd /W3 /Gm /GX /Zi /Od /Ob2 /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_MBCS" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Econo.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Gravitation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 winmm.lib scrnsave.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=winmm.lib scrnsave.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Gravitation.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Gravitation.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Dib.obj" \
	"$(INTDIR)\Dibpal.obj" \
	"$(INTDIR)\DibSurface.obj" \
	"$(INTDIR)\DlgParametres.obj" \
	"$(INTDIR)\Econo.obj" \
	"$(INTDIR)\Econo.res" \
	"$(INTDIR)\Economiseur.obj" \
	"$(INTDIR)\Gravitation.obj" \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\PageAffichage.obj" \
	"$(INTDIR)\PageComete.obj" \
	"$(INTDIR)\PageGenese.obj" \
	"$(INTDIR)\PageMasses.obj" \
	"$(INTDIR)\PagePhysique.obj" \
	"$(INTDIR)\RectAffichage.obj" \
	"$(INTDIR)\RegisterDialogClasses.obj"

"$(OUTDIR)\Gravitation.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Gravitation - Win32 Release"
# Name "Gravitation - Win32 Debug"

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgParametres.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EcoGravitation.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Econo.rc
DEP_RSC_ECONO=\
	".\bitmap1.bmp"\
	".\bitmap2.bmp"\
	".\bmp00001.bmp"\
	".\bmp00002.bmp"\
	".\bmp00003.bmp"\
	".\dib1.dib"\
	".\dib10.dib"\
	".\dib2.dib"\
	".\dib3.dib"\
	".\dib4.dib"\
	".\dib5.dib"\
	".\dib6.dib"\
	".\dib7.dib"\
	".\dib8.dib"\
	".\dib9.dib"\
	".\ECONO.ICO"\
	".\explosion.dib"\
	".\lulu.ico"\
	".\masse2.bmp"\
	".\masse3.bmp"\
	".\masse4.bmp"\
	".\masse8.bmp"\
	

"$(INTDIR)\Econo.res" : $(SOURCE) $(DEP_RSC_ECONO) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gravitation.cpp
DEP_CPP_GRAVI=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\Page1.h"\
	".\Page2.h"\
	".\PageAffichage.h"\
	".\PageComete.h"\
	".\PageGenese.h"\
	".\PageMasses.h"\
	".\PagePhysique.h"\
	

"$(INTDIR)\Gravitation.obj" : $(SOURCE) $(DEP_CPP_GRAVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.cpp
DEP_CPP_PAGE1=\
	"..\stdafx.h"\
	".\Page1.h"\
	

"$(INTDIR)\Page1.obj" : $(SOURCE) $(DEP_CPP_PAGE1) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.cpp
DEP_CPP_PAGE2=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\Page2.h"\
	

"$(INTDIR)\Page2.obj" : $(SOURCE) $(DEP_CPP_PAGE2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page3.h

!IF  "$(CFG)" == "Gravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgParametres.cpp
DEP_CPP_DLGPA=\
	"..\stdafx.h"\
	".\DlgParametres.h"\
	

"$(INTDIR)\DlgParametres.obj" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\Economiseur.cpp"
DEP_CPP_ECONOM=\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE="\Dilp32\Economiseurs\Economiseur generique\Econo.cpp"
DEP_CPP_ECONO_=\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur generique\stdafx.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\DibSurface.cpp
DEP_CPP_DIBSU=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	

"$(INTDIR)\DibSurface.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\Dibpal.cpp
DEP_CPP_DIBPA=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	

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

SOURCE="\Dilp32\Economiseurs\Economiseur generique\RegisterDialogClasses.c"

"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageGenese.cpp
DEP_CPP_PAGEG=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\PageGenese.h"\
	

"$(INTDIR)\PageGenese.obj" : $(SOURCE) $(DEP_CPP_PAGEG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageComete.cpp
DEP_CPP_PAGEC=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\PageComete.h"\
	

"$(INTDIR)\PageComete.obj" : $(SOURCE) $(DEP_CPP_PAGEC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PagePhysique.cpp
DEP_CPP_PAGEP=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\PagePhysique.h"\
	

"$(INTDIR)\PagePhysique.obj" : $(SOURCE) $(DEP_CPP_PAGEP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageAffichage.cpp
DEP_CPP_PAGEA=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\PageAffichage.h"\
	

"$(INTDIR)\PageAffichage.obj" : $(SOURCE) $(DEP_CPP_PAGEA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageMasses.cpp
DEP_CPP_PAGEM=\
	"..\..\Classes\Dib.h"\
	"..\..\Classes\DibPal.h"\
	"..\..\Classes\DibSurface.h"\
	"..\Economiseur Generique\Economiseur.h"\
	"..\Economiseur Generique\RectAffichage.h"\
	"..\stdafx.h"\
	".\EcoGravitation.h"\
	".\PageMasses.h"\
	

"$(INTDIR)\PageMasses.obj" : $(SOURCE) $(DEP_CPP_PAGEM) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
