# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=DDGravitation - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to DDGravitation - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "DDGravitation - Win32 Release" && "$(CFG)" !=\
 "DDGravitation - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "DDGravitation.mak" CFG="DDGravitation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DDGravitation - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DDGravitation - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "DDGravitation - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\DDGravitation.exe"

CLEAN : 
	-@erase "$(INTDIR)\Ddutil.obj"
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
	-@erase "$(OUTDIR)\DDGravitation.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDGravitation.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Econo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DDGravitation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib ddraw.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=scrnsave.lib ddraw.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/DDGravitation.pdb" /machine:I386\
 /out:"$(OUTDIR)/DDGravitation.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Ddutil.obj" \
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

"$(OUTDIR)\DDGravitation.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\DDGravitation.exe"

CLEAN : 
	-@erase "$(INTDIR)\Ddutil.obj"
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
	-@erase "$(OUTDIR)\DDGravitation.exe"
	-@erase "$(OUTDIR)\DDGravitation.ilk"
	-@erase "$(OUTDIR)\DDGravitation.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/DDGravitation.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Econo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/DDGravitation.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 scrnsave.lib ddraw.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=scrnsave.lib ddraw.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/DDGravitation.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/DDGravitation.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Ddutil.obj" \
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

"$(OUTDIR)\DDGravitation.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "DDGravitation - Win32 Release"
# Name "DDGravitation - Win32 Debug"

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Stdafx.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DirectDrawSurface.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgParametres.cpp
DEP_CPP_DLGPA=\
	".\DlgParametres.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\DlgParametres.obj" : $(SOURCE) $(DEP_CPP_DLGPA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgParametres.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EcoGravitation.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Econo.cpp
DEP_CPP_ECONO=\
	".\Economiseur.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Econo.rc
DEP_RSC_ECONO_=\
	".\AxeHorizontal.bmp"\
	".\AxeHorizontal64.bmp"\
	".\AxeVertical.bmp"\
	".\AxeVertical64.bmp"\
	".\bitmap1.bmp"\
	".\bitmap2.bmp"\
	".\bmp00001.bmp"\
	".\bmp00002.bmp"\
	".\bmp00003.bmp"\
	".\dib1.bmp"\
	".\dib10.bmp"\
	".\dib2.bmp"\
	".\dib3.bmp"\
	".\dib4.bmp"\
	".\dib5.bmp"\
	".\dib6.bmp"\
	".\dib64_1.bmp"\
	".\dib64_10.bmp"\
	".\dib64_2.bmp"\
	".\dib64_4.bmp"\
	".\dib64_5.bmp"\
	".\dib64_6.bmp"\
	".\dib64_8.bmp"\
	".\dib64_9.bmp"\
	".\dib7.bmp"\
	".\dib8.bmp"\
	".\dib9.bmp"\
	".\ECONO.ICO"\
	".\explosion.bmp"\
	".\explosion64.bmp"\
	".\lulu.ico"\
	".\masse2.bmp"\
	".\masse3.bmp"\
	".\masse4.bmp"\
	".\masse8.bmp"\
	".\RepereHorizontal.bmp"\
	".\RepereHorizontal64.bmp"\
	".\RepereVertical.bmp"\
	".\RepereVertical64.bmp"\
	

"$(INTDIR)\Econo.res" : $(SOURCE) $(DEP_RSC_ECONO_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Economiseur.cpp
DEP_CPP_ECONOM=\
	".\ddutil.h"\
	".\Economiseur.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Economiseur.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gravitation.cpp
DEP_CPP_GRAVI=\
	".\ddutil.h"\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\Page1.h"\
	".\Page2.h"\
	".\PageAffichage.h"\
	".\PageComete.h"\
	".\PageGenese.h"\
	".\PageMasses.h"\
	".\PagePhysique.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Gravitation.obj" : $(SOURCE) $(DEP_CPP_GRAVI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.cpp
DEP_CPP_PAGE1=\
	".\Page1.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Page1.obj" : $(SOURCE) $(DEP_CPP_PAGE1) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.cpp
DEP_CPP_PAGE2=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\Page2.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\Page2.obj" : $(SOURCE) $(DEP_CPP_PAGE2) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page3.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page4.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page5.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageAffichage.cpp
DEP_CPP_PAGEA=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\PageAffichage.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\PageAffichage.obj" : $(SOURCE) $(DEP_CPP_PAGEA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageAffichage.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageComete.cpp
DEP_CPP_PAGEC=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\PageComete.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\PageComete.obj" : $(SOURCE) $(DEP_CPP_PAGEC) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageComete.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageGenese.cpp
DEP_CPP_PAGEG=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\PageGenese.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\PageGenese.obj" : $(SOURCE) $(DEP_CPP_PAGEG) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageGenese.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageMasses.cpp
DEP_CPP_PAGEM=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\PageMasses.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\PageMasses.obj" : $(SOURCE) $(DEP_CPP_PAGEM) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PageMasses.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PagePhysique.cpp
DEP_CPP_PAGEP=\
	".\EcoGravitation.h"\
	".\Economiseur.h"\
	".\PagePhysique.h"\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\PagePhysique.obj" : $(SOURCE) $(DEP_CPP_PAGEP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\PagePhysique.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RectAffichage.cpp
DEP_CPP_RECTA=\
	".\RectAffichage.h"\
	".\Stdafx.h"\
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\RectAffichage.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegisterDialogClasses.c

"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Specif.h

!IF  "$(CFG)" == "DDGravitation - Win32 Release"

!ELSEIF  "$(CFG)" == "DDGravitation - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ddutil.cpp
DEP_CPP_DDUTI=\
	".\ddutil.h"\
	

"$(INTDIR)\Ddutil.obj" : $(SOURCE) $(DEP_CPP_DDUTI) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
