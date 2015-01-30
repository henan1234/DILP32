# Microsoft Developer Studio Generated NMAKE File, Format Version 4.20
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Tapisserie V2 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Tapisserie V2 - Win32\
 Debug.
!ENDIF 

!IF "$(CFG)" != "Tapisserie V2 - Win32 Release" && "$(CFG)" !=\
 "Tapisserie V2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Tapisserie V2.mak" CFG="Tapisserie V2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Tapisserie V2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Tapisserie V2 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Tapisserie V2 - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Tapisserie V2 - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Tapisserie V2.exe"

CLEAN : 
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\RegistryKey.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tapisserie V2.obj"
	-@erase "$(INTDIR)\Tapisserie V2.pch"
	-@erase "$(INTDIR)\Tapisserie V2.res"
	-@erase "$(INTDIR)\Tapisserie V2Dlg.obj"
	-@erase "$(INTDIR)\Tapisserie.obj"
	-@erase "$(INTDIR)\TapisserieSheet.obj"
	-@erase "$(OUTDIR)\Tapisserie V2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Tapisserie V2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Tapisserie V2.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tapisserie V2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Tapisserie V2.pdb" /machine:I386\
 /out:"$(OUTDIR)/Tapisserie V2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\RegistryKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tapisserie V2.obj" \
	"$(INTDIR)\Tapisserie V2.res" \
	"$(INTDIR)\Tapisserie V2Dlg.obj" \
	"$(INTDIR)\Tapisserie.obj" \
	"$(INTDIR)\TapisserieSheet.obj"

"$(OUTDIR)\Tapisserie V2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Tapisserie V2 - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Tapisserie V2.exe"

CLEAN : 
	-@erase "$(INTDIR)\Page1.obj"
	-@erase "$(INTDIR)\Page2.obj"
	-@erase "$(INTDIR)\RegistryKey.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Tapisserie V2.obj"
	-@erase "$(INTDIR)\Tapisserie V2.pch"
	-@erase "$(INTDIR)\Tapisserie V2.res"
	-@erase "$(INTDIR)\Tapisserie V2Dlg.obj"
	-@erase "$(INTDIR)\Tapisserie.obj"
	-@erase "$(INTDIR)\TapisserieSheet.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Tapisserie V2.exe"
	-@erase "$(OUTDIR)\Tapisserie V2.ilk"
	-@erase "$(OUTDIR)\Tapisserie V2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Tapisserie V2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Tapisserie V2.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Tapisserie V2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Tapisserie V2.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/Tapisserie V2.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Page1.obj" \
	"$(INTDIR)\Page2.obj" \
	"$(INTDIR)\RegistryKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Tapisserie V2.obj" \
	"$(INTDIR)\Tapisserie V2.res" \
	"$(INTDIR)\Tapisserie V2Dlg.obj" \
	"$(INTDIR)\Tapisserie.obj" \
	"$(INTDIR)\TapisserieSheet.obj"

"$(OUTDIR)\Tapisserie V2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Tapisserie V2 - Win32 Release"
# Name "Tapisserie V2 - Win32 Debug"

!IF  "$(CFG)" == "Tapisserie V2 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tapisserie V2 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Tapisserie V2 - Win32 Release"

!ELSEIF  "$(CFG)" == "Tapisserie V2 - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\Tapisserie V2.cpp"
DEP_CPP_TAPIS=\
	".\Page1.h"\
	".\Page2.h"\
	".\StdAfx.h"\
	".\Tapisserie V2.h"\
	".\Tapisserie V2Dlg.h"\
	".\TapisserieSheet.h"\
	

"$(INTDIR)\Tapisserie V2.obj" : $(SOURCE) $(DEP_CPP_TAPIS) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=".\Tapisserie V2Dlg.cpp"
DEP_CPP_TAPISS=\
	".\StdAfx.h"\
	".\Tapisserie V2.h"\
	".\Tapisserie V2Dlg.h"\
	

"$(INTDIR)\Tapisserie V2Dlg.obj" : $(SOURCE) $(DEP_CPP_TAPISS) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Tapisserie V2 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/Tapisserie V2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tapisserie V2.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Tapisserie V2 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/Tapisserie V2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Tapisserie V2.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=".\Tapisserie V2.rc"
DEP_RSC_TAPISSE=\
	".\res\Cursor1.cur"\
	".\res\icon3.ico"\
	".\res\icon4.ico"\
	".\res\icon5.ico"\
	".\res\Mainfram.ico"\
	".\res\Tapisserie V2.rc2"\
	".\res\Taskbar1.ico"\
	".\res\Taskbar_.ico"\
	

"$(INTDIR)\Tapisserie V2.res" : $(SOURCE) $(DEP_RSC_TAPISSE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page2.cpp
DEP_CPP_PAGE2=\
	"..\classes\registrykey.h"\
	".\Page2.h"\
	".\StdAfx.h"\
	".\Tapisserie V2.h"\
	".\Tapisserie.h"\
	

"$(INTDIR)\Page2.obj" : $(SOURCE) $(DEP_CPP_PAGE2) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Page1.cpp
DEP_CPP_PAGE1=\
	".\Page1.h"\
	".\StdAfx.h"\
	".\Tapisserie V2.h"\
	

"$(INTDIR)\Page1.obj" : $(SOURCE) $(DEP_CPP_PAGE1) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\TapisserieSheet.cpp
DEP_CPP_TAPISSER=\
	".\Page2.h"\
	".\StdAfx.h"\
	".\Tapisserie V2.h"\
	".\TapisserieSheet.h"\
	

"$(INTDIR)\TapisserieSheet.obj" : $(SOURCE) $(DEP_CPP_TAPISSER) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Tapisserie.cpp
DEP_CPP_TAPISSERI=\
	".\StdAfx.h"\
	".\Tapisserie.h"\
	".\TapisserieSheet.h"\
	

"$(INTDIR)\Tapisserie.obj" : $(SOURCE) $(DEP_CPP_TAPISSERI) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=\Dilp32\Classes\RegistryKey.cpp
DEP_CPP_REGIS=\
	"..\classes\registrykey.h"\
	
NODEP_CPP_REGIS=\
	"..\Classes\stdafx.h"\
	

"$(INTDIR)\RegistryKey.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\Tapisserie V2.pch"
   $(CPP) $(CPP_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
