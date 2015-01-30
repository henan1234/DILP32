# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Graffiti - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Graffiti - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Graffiti - Win32 Release" && "$(CFG)" !=\
 "Graffiti - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Graffiti.mak" CFG="Graffiti - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Graffiti - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Graffiti - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Graffiti - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Graffiti - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Graffiti"
# PROP BASE Intermediate_Dir "Graffiti"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Graffiti"
# PROP Intermediate_Dir "Graffiti"
# PROP Target_Dir ""
OUTDIR=.\Graffiti
INTDIR=.\Graffiti

ALL : "$(OUTDIR)\Graffiti.exe"

CLEAN : 
	-@erase ".\Graffiti\Graffiti.exe"
	-@erase ".\Graffiti\Trajectoire.obj"
	-@erase ".\Graffiti\Outil.obj"
	-@erase ".\Graffiti\Graffiti.obj"
	-@erase ".\Graffiti\Grafitti.res"
	-@erase ".\Graffiti\Econo.obj"
	-@erase ".\Graffiti\Economiseur.obj"
	-@erase ".\Graffiti\RectAffichage.obj"
	-@erase ".\Graffiti\RegisterDialogClasses.obj"
	-@erase ".\Graffiti\DibSurface.obj"
	-@erase ".\Graffiti\Dibpal.obj"
	-@erase ".\Graffiti\Dib.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX"afxwin.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Graffiti.pch" /YX"afxwin.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Graffiti/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Grafitti.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Graffiti.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Graffiti.pdb" /machine:I386\
 /out:"$(OUTDIR)/Graffiti.exe" 
LINK32_OBJS= \
	".\Graffiti\Trajectoire.obj" \
	".\Graffiti\Outil.obj" \
	".\Graffiti\Graffiti.obj" \
	".\Graffiti\Econo.obj" \
	".\Graffiti\Economiseur.obj" \
	".\Graffiti\RectAffichage.obj" \
	".\Graffiti\RegisterDialogClasses.obj" \
	".\Graffiti\DibSurface.obj" \
	".\Graffiti\Dibpal.obj" \
	".\Graffiti\Dib.obj" \
	".\Graffiti\Grafitti.res"

"$(OUTDIR)\Graffiti.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Graffit0"
# PROP BASE Intermediate_Dir "Graffit0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Graffit0"
# PROP Intermediate_Dir "Graffit0"
# PROP Target_Dir ""
OUTDIR=.\Graffit0
INTDIR=.\Graffit0

ALL : "$(OUTDIR)\Graffiti.exe" "$(OUTDIR)\Graffiti.bsc"

CLEAN : 
	-@erase ".\Graffit0\vc40.pdb"
	-@erase ".\Graffit0\vc40.idb"
	-@erase ".\Graffit0\Graffiti.bsc"
	-@erase ".\Graffit0\Outil.sbr"
	-@erase ".\Graffit0\Graffiti.sbr"
	-@erase ".\Graffit0\Trajectoire.sbr"
	-@erase ".\Graffit0\Econo.sbr"
	-@erase ".\Graffit0\Economiseur.sbr"
	-@erase ".\Graffit0\RectAffichage.sbr"
	-@erase ".\Graffit0\RegisterDialogClasses.sbr"
	-@erase ".\Graffit0\DibSurface.sbr"
	-@erase ".\Graffit0\Dibpal.sbr"
	-@erase ".\Graffit0\Dib.sbr"
	-@erase ".\Graffit0\Graffiti.exe"
	-@erase ".\Graffit0\Outil.obj"
	-@erase ".\Graffit0\Graffiti.obj"
	-@erase ".\Graffit0\Trajectoire.obj"
	-@erase ".\Graffit0\Grafitti.res"
	-@erase ".\Graffit0\Econo.obj"
	-@erase ".\Graffit0\Economiseur.obj"
	-@erase ".\Graffit0\RectAffichage.obj"
	-@erase ".\Graffit0\RegisterDialogClasses.obj"
	-@erase ".\Graffit0\DibSurface.obj"
	-@erase ".\Graffit0\Dibpal.obj"
	-@erase ".\Graffit0\Dib.obj"
	-@erase ".\Graffit0\Graffiti.ilk"
	-@erase ".\Graffit0\Graffiti.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Graffiti.pch" /YX\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Graffit0/
CPP_SBRS=.\Graffit0/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Grafitti.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Graffiti.bsc" 
BSC32_SBRS= \
	".\Graffit0\Outil.sbr" \
	".\Graffit0\Graffiti.sbr" \
	".\Graffit0\Trajectoire.sbr" \
	".\Graffit0\Econo.sbr" \
	".\Graffit0\Economiseur.sbr" \
	".\Graffit0\RectAffichage.sbr" \
	".\Graffit0\RegisterDialogClasses.sbr" \
	".\Graffit0\DibSurface.sbr" \
	".\Graffit0\Dibpal.sbr" \
	".\Graffit0\Dib.sbr"

"$(OUTDIR)\Graffiti.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=scrnsave.lib comctl32.lib winmm.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Graffiti.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Graffiti.exe" 
LINK32_OBJS= \
	".\Graffit0\Outil.obj" \
	".\Graffit0\Graffiti.obj" \
	".\Graffit0\Trajectoire.obj" \
	".\Graffit0\Econo.obj" \
	".\Graffit0\Economiseur.obj" \
	".\Graffit0\RectAffichage.obj" \
	".\Graffit0\RegisterDialogClasses.obj" \
	".\Graffit0\DibSurface.obj" \
	".\Graffit0\Dibpal.obj" \
	".\Graffit0\Dib.obj" \
	".\Graffit0\Grafitti.res"

"$(OUTDIR)\Graffiti.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Graffiti - Win32 Release"
# Name "Graffiti - Win32 Debug"

!IF  "$(CFG)" == "Graffiti - Win32 Release"

!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Grafitti.rc
DEP_RSC_GRAFI=\
	".\bitmap1.bmp"\
	".\ico00001.ico"\
	".\icon1.ico"\
	".\icon2.ico"\
	".\icon3.ico"\
	".\icon4.ico"\
	

"$(INTDIR)\Grafitti.res" : $(SOURCE) $(DEP_RSC_GRAFI) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Outil.cpp
DEP_CPP_OUTIL=\
	".\..\..\Classes\CriticalBloc.h"\
	".\Outil.h"\
	".\Stdafx.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Outil.obj" : $(SOURCE) $(DEP_CPP_OUTIL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


"$(INTDIR)\Outil.obj" : $(SOURCE) $(DEP_CPP_OUTIL) "$(INTDIR)"

"$(INTDIR)\Outil.sbr" : $(SOURCE) $(DEP_CPP_OUTIL) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Trajectoire.cpp
DEP_CPP_TRAJE=\
	".\Outil.h"\
	".\Stdafx.h"\
	".\Trajectoire.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Trajectoire.obj" : $(SOURCE) $(DEP_CPP_TRAJE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


"$(INTDIR)\Trajectoire.obj" : $(SOURCE) $(DEP_CPP_TRAJE) "$(INTDIR)"

"$(INTDIR)\Trajectoire.sbr" : $(SOURCE) $(DEP_CPP_TRAJE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Graffiti.cpp
DEP_CPP_GRAFF=\
	".\..\..\classes\dib.h"\
	".\..\economiseur generique\economiseur.h"\
	".\..\Economiseur Generique\RectAffichage.h"\
	".\..\stdafx.h"\
	".\graffiti.h"\
	".\Outil.h"\
	".\Trajectoire.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Graffiti.obj" : $(SOURCE) $(DEP_CPP_GRAFF) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


"$(INTDIR)\Graffiti.obj" : $(SOURCE) $(DEP_CPP_GRAFF) "$(INTDIR)"

"$(INTDIR)\Graffiti.sbr" : $(SOURCE) $(DEP_CPP_GRAFF) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\Econo.cpp"
DEP_CPP_ECONO=\
	".\..\Economiseur generique\stdafx.h"\
	".\..\economiseur generique\economiseur.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Econo.obj" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Econo.sbr" : $(SOURCE) $(DEP_CPP_ECONO) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\Economiseur.cpp"
DEP_CPP_ECONOM=\
	".\..\Economiseur generique\stdafx.h"\
	".\..\economiseur generique\economiseur.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Economiseur.obj" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Economiseur.sbr" : $(SOURCE) $(DEP_CPP_ECONOM) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\RectAffichage.cpp"
DEP_CPP_RECTA=\
	".\..\Economiseur generique\stdafx.h"\
	".\..\Economiseur Generique\RectAffichage.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\RectAffichage.obj" : $(SOURCE) $(DEP_CPP_RECTA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


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

SOURCE="\lpi\Dilp32\Economiseurs\Economiseur generique\RegisterDialogClasses.c"

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\RegisterDialogClasses.obj" : $(SOURCE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


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

SOURCE=\lpi\Dilp32\Classes\DibSurface.cpp
DEP_CPP_DIBSU=\
	".\..\..\Classes\DibSurface.h"\
	".\..\..\Classes\DibPal.h"\
	".\..\..\classes\dib.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\DibSurface.obj" : $(SOURCE) $(DEP_CPP_DIBSU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


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
	".\..\..\Classes\DibPal.h"\
	".\..\..\classes\dib.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Dibpal.obj" : $(SOURCE) $(DEP_CPP_DIBPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


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
	".\..\..\classes\dib.h"\
	

!IF  "$(CFG)" == "Graffiti - Win32 Release"


"$(INTDIR)\Dib.obj" : $(SOURCE) $(DEP_CPP_DIB_C) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Graffiti - Win32 Debug"


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
