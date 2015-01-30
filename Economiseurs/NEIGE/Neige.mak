# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Neige - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Neige - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Neige - Win32 Release" && "$(CFG)" != "Neige - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Neige.mak" CFG="Neige - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Neige - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Neige - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Neige - Win32 Release"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Neige - Win32 Release"

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

ALL : "$(OUTDIR)\Neige.scr"

CLEAN : 
	-@erase ".\Release\Neige.scr"
	-@erase ".\Release\neige.obj"
	-@erase ".\Release\flocon.obj"
	-@erase ".\Release\Neige.res"
	-@erase ".\Release\RegisterDialogClasses.obj"
	-@erase ".\Release\Economiseur.obj"
	-@erase ".\Release\RectAffichage.obj"
	-@erase ".\Release\Econo.obj"
	-@erase ".\Release\DibSurface.obj"
	-@erase ".\Release\Dibpal.obj"
	-@erase ".\Release\Dib.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Neige.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Neige.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Neige.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Neige.scr"
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Neige.pdb" /machine:I386\
 /out:"$(OUTDIR)/Neige.scr" 
LINK32_OBJS= \
	"$(INTDIR)/neige.obj" \
	"$(INTDIR)/flocon.obj" \
	"$(INTDIR)/RegisterDialogClasses.obj" \
	"$(INTDIR)/Economiseur.obj" \
	"$(INTDIR)/RectAffichage.obj" \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/DibSurface.obj" \
	"$(INTDIR)/Dibpal.obj" \
	"$(INTDIR)/Dib.obj" \
	"$(INTDIR)/Neige.res"

"$(OUTDIR)\Neige.scr" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"

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

ALL : "$(OUTDIR)\Neige.exe" "$(OUTDIR)\Neige.bsc"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Neige.bsc"
	-@erase ".\Debug\flocon.sbr"
	-@erase ".\Debug\neige.sbr"
	-@erase ".\Debug\RegisterDialogClasses.sbr"
	-@erase ".\Debug\Economiseur.sbr"
	-@erase ".\Debug\RectAffichage.sbr"
	-@erase ".\Debug\Econo.sbr"
	-@erase ".\Debug\DibSurface.sbr"
	-@erase ".\Debug\Dibpal.sbr"
	-@erase ".\Debug\Dib.sbr"
	-@erase ".\Debug\Neige.exe"
	-@erase ".\Debug\flocon.obj"
	-@erase ".\Debug\neige.obj"
	-@erase ".\Debug\Neige.res"
	-@erase ".\Debug\RegisterDialogClasses.obj"
	-@erase ".\Debug\Economiseur.obj"
	-@erase ".\Debug\RectAffichage.obj"
	-@erase ".\Debug\Econo.obj"
	-@erase ".\Debug\DibSurface.obj"
	-@erase ".\Debug\Dibpal.obj"
	-@erase ".\Debug\Dib.obj"
	-@erase ".\Debug\Neige.ilk"
	-@erase ".\Debug\Neige.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Neige.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Neige.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Neige.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/flocon.sbr" \
	"$(INTDIR)/neige.sbr" \
	"$(INTDIR)/RegisterDialogClasses.sbr" \
	"$(INTDIR)/Economiseur.sbr" \
	"$(INTDIR)/RectAffichage.sbr" \
	"$(INTDIR)/Econo.sbr" \
	"$(INTDIR)/DibSurface.sbr" \
	"$(INTDIR)/Dibpal.sbr" \
	"$(INTDIR)/Dib.sbr"

"$(OUTDIR)\Neige.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Neige.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Neige.exe" 
LINK32_OBJS= \
	"$(INTDIR)/flocon.obj" \
	"$(INTDIR)/neige.obj" \
	"$(INTDIR)/RegisterDialogClasses.obj" \
	"$(INTDIR)/Economiseur.obj" \
	"$(INTDIR)/RectAffichage.obj" \
	"$(INTDIR)/Econo.obj" \
	"$(INTDIR)/DibSurface.obj" \
	"$(INTDIR)/Dibpal.obj" \
	"$(INTDIR)/Dib.obj" \
	"$(INTDIR)/Neige.res"

"$(OUTDIR)\Neige.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Neige - Win32 Release"
# Name "Neige - Win32 Debug"

!IF  "$(CFG)" == "Neige - Win32 Release"

!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\neige.cpp
DEP_CPP_NEIGE=\
	".\..\Economiseur Generique\stdafx.h"\
	".\..\Economiseur Generique\RectAffichage.h"\
	".\Flocon.h"\
	".\Neige.h"\
	".\..\..\classes\dibpal.h"\
	".\..\..\classes\dibsurface.h"\
	".\..\Economiseur Generique\Economiseur.h"\
	".\..\..\Classes\Dib.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\neige.obj" : $(SOURCE) $(DEP_CPP_NEIGE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


"$(INTDIR)\neige.obj" : $(SOURCE) $(DEP_CPP_NEIGE) "$(INTDIR)"

"$(INTDIR)\neige.sbr" : $(SOURCE) $(DEP_CPP_NEIGE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Neige.rc
DEP_RSC_NEIGE_=\
	".\icon1.ico"\
	

"$(INTDIR)\Neige.res" : $(SOURCE) $(DEP_RSC_NEIGE_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\flocon.cpp
DEP_CPP_FLOCO=\
	".\..\Economiseur Generique\RectAffichage.h"\
	".\..\Economiseur Generique\stdafx.h"\
	".\Flocon.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\flocon.obj" : $(SOURCE) $(DEP_CPP_FLOCO) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


"$(INTDIR)\flocon.obj" : $(SOURCE) $(DEP_CPP_FLOCO) "$(INTDIR)"

"$(INTDIR)\flocon.sbr" : $(SOURCE) $(DEP_CPP_FLOCO) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\RegisterDialogClasses.c"

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RegisterDialogClasses.sbr" : $(SOURCE) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\Economiseur.cpp"
DEP_CPP_ECONO=\
	".\..\Economiseur Generique\stdafx.h"\
	".\..\Economiseur Generique\Economiseur.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Economiseur.sbr" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	".\..\Economiseur Generique\stdafx.h"\
	".\..\Economiseur Generique\RectAffichage.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\RectAffichage.sbr" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\Econo.cpp"
DEP_CPP_ECONO_=\
	".\..\Economiseur Generique\stdafx.h"\
	".\..\Economiseur Generique\Economiseur.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Econo.sbr" : $(SOURCE) $(DEP_CPP_ECONO_) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\lpi\Dilp32\Classes\DibSurface.cpp
DEP_CPP_DIBSU=\
	".\..\..\classes\dibsurface.h"\
	".\..\..\classes\dibpal.h"\
	".\..\..\Classes\Dib.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\DibSurface.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\DibSurface.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\DibSurface.sbr" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\lpi\Dilp32\Classes\Dibpal.cpp
DEP_CPP_DIBPA=\
	".\..\..\classes\dibpal.h"\
	".\..\..\Classes\Dib.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dibpal.sbr" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\lpi\Dilp32\Classes\Dib.cpp
DEP_CPP_DIB_C=\
	".\..\..\Classes\Dib.h"\
	

!IF  "$(CFG)" == "Neige - Win32 Release"


"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Neige - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Dib.sbr" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
