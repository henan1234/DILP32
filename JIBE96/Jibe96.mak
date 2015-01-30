# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Jibe96 - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Jibe96 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Jibe96 - Win32 Release" && "$(CFG)" != "Jibe96 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Jibe96.mak" CFG="Jibe96 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jibe96 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Jibe96 - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Jibe96 - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

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

ALL : "$(OUTDIR)\Jibe96.exe"

CLEAN : 
	-@erase ".\Release\Jibe96.exe"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Jibe96.pch"
	-@erase ".\Release\IconeSwap.obj"
	-@erase ".\Release\TipDlg.obj"
	-@erase ".\Release\IconePeriodique.obj"
	-@erase ".\Release\WndIcone.obj"
	-@erase ".\Release\IconeBouton.obj"
	-@erase ".\Release\IconeSurveille.obj"
	-@erase ".\Release\iconeSeparateur.obj"
	-@erase ".\Release\Jibe96View.obj"
	-@erase ".\Release\icone.obj"
	-@erase ".\Release\IconeJauge.obj"
	-@erase ".\Release\sclib.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\DlgIcone.obj"
	-@erase ".\Release\SurveilleDlg.obj"
	-@erase ".\Release\PreferencesDlg.obj"
	-@erase ".\Release\iconeNote.obj"
	-@erase ".\Release\Jibe96.obj"
	-@erase ".\Release\PropsDisque.obj"
	-@erase ".\Release\iconeGroupe.obj"
	-@erase ".\Release\Jibe96Doc.obj"
	-@erase ".\Release\DlgOptionsSurveillance.obj"
	-@erase ".\Release\iconeRAM.obj"
	-@erase ".\Release\LpiBitmap.obj"
	-@erase ".\Release\Splash.obj"
	-@erase ".\Release\IconeMem.obj"
	-@erase ".\Release\iconeDisque.obj"
	-@erase ".\Release\Lpiicone.obj"
	-@erase ".\Release\Preferences.obj"
	-@erase ".\Release\IconeHorloge.obj"
	-@erase ".\Release\choosfol.obj"
	-@erase ".\Release\DlgSeuilAlarme.obj"
	-@erase ".\Release\Raccourci.obj"
	-@erase ".\Release\IconeCommande.obj"
	-@erase ".\Release\Jibe96.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/Jibe96.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Jibe96.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jibe96.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Jibe96.pdb" /machine:I386 /out:"$(OUTDIR)/Jibe96.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/IconeSwap.obj" \
	"$(INTDIR)/TipDlg.obj" \
	"$(INTDIR)/IconePeriodique.obj" \
	"$(INTDIR)/WndIcone.obj" \
	"$(INTDIR)/IconeBouton.obj" \
	"$(INTDIR)/IconeSurveille.obj" \
	"$(INTDIR)/iconeSeparateur.obj" \
	"$(INTDIR)/Jibe96View.obj" \
	"$(INTDIR)/icone.obj" \
	"$(INTDIR)/IconeJauge.obj" \
	"$(INTDIR)/sclib.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/DlgIcone.obj" \
	"$(INTDIR)/SurveilleDlg.obj" \
	"$(INTDIR)/PreferencesDlg.obj" \
	"$(INTDIR)/iconeNote.obj" \
	"$(INTDIR)/Jibe96.obj" \
	"$(INTDIR)/PropsDisque.obj" \
	"$(INTDIR)/iconeGroupe.obj" \
	"$(INTDIR)/Jibe96Doc.obj" \
	"$(INTDIR)/DlgOptionsSurveillance.obj" \
	"$(INTDIR)/iconeRAM.obj" \
	"$(INTDIR)/LpiBitmap.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/IconeMem.obj" \
	"$(INTDIR)/iconeDisque.obj" \
	"$(INTDIR)/Lpiicone.obj" \
	"$(INTDIR)/Preferences.obj" \
	"$(INTDIR)/IconeHorloge.obj" \
	"$(INTDIR)/choosfol.obj" \
	"$(INTDIR)/DlgSeuilAlarme.obj" \
	"$(INTDIR)/Raccourci.obj" \
	"$(INTDIR)/IconeCommande.obj" \
	"$(INTDIR)/Jibe96.res"

"$(OUTDIR)\Jibe96.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

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

ALL : "$(OUTDIR)\Jibe96.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Jibe96.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Jibe96.exe"
	-@erase ".\Debug\iconeGroupe.obj"
	-@erase ".\Debug\LpiBitmap.obj"
	-@erase ".\Debug\WndIcone.obj"
	-@erase ".\Debug\IconeJauge.obj"
	-@erase ".\Debug\iconeNote.obj"
	-@erase ".\Debug\IconeSurveille.obj"
	-@erase ".\Debug\DlgOptionsSurveillance.obj"
	-@erase ".\Debug\iconeDisque.obj"
	-@erase ".\Debug\Raccourci.obj"
	-@erase ".\Debug\TipDlg.obj"
	-@erase ".\Debug\Preferences.obj"
	-@erase ".\Debug\sclib.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\DlgSeuilAlarme.obj"
	-@erase ".\Debug\PreferencesDlg.obj"
	-@erase ".\Debug\IconePeriodique.obj"
	-@erase ".\Debug\IconeCommande.obj"
	-@erase ".\Debug\Jibe96View.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\iconeRAM.obj"
	-@erase ".\Debug\IconeBouton.obj"
	-@erase ".\Debug\Jibe96.obj"
	-@erase ".\Debug\IconeMem.obj"
	-@erase ".\Debug\SurveilleDlg.obj"
	-@erase ".\Debug\Lpiicone.obj"
	-@erase ".\Debug\IconeHorloge.obj"
	-@erase ".\Debug\IconeSwap.obj"
	-@erase ".\Debug\DlgIcone.obj"
	-@erase ".\Debug\icone.obj"
	-@erase ".\Debug\choosfol.obj"
	-@erase ".\Debug\Jibe96Doc.obj"
	-@erase ".\Debug\PropsDisque.obj"
	-@erase ".\Debug\iconeSeparateur.obj"
	-@erase ".\Debug\Splash.obj"
	-@erase ".\Debug\Jibe96.res"
	-@erase ".\Debug\Jibe96.ilk"
	-@erase ".\Debug\Jibe96.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jibe96.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x40c /fo"$(INTDIR)/Jibe96.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Jibe96.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Jibe96.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Jibe96.exe" 
LINK32_OBJS= \
	"$(INTDIR)/iconeGroupe.obj" \
	"$(INTDIR)/LpiBitmap.obj" \
	"$(INTDIR)/WndIcone.obj" \
	"$(INTDIR)/IconeJauge.obj" \
	"$(INTDIR)/iconeNote.obj" \
	"$(INTDIR)/IconeSurveille.obj" \
	"$(INTDIR)/DlgOptionsSurveillance.obj" \
	"$(INTDIR)/iconeDisque.obj" \
	"$(INTDIR)/Raccourci.obj" \
	"$(INTDIR)/TipDlg.obj" \
	"$(INTDIR)/Preferences.obj" \
	"$(INTDIR)/sclib.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/DlgSeuilAlarme.obj" \
	"$(INTDIR)/PreferencesDlg.obj" \
	"$(INTDIR)/IconePeriodique.obj" \
	"$(INTDIR)/IconeCommande.obj" \
	"$(INTDIR)/Jibe96View.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/iconeRAM.obj" \
	"$(INTDIR)/IconeBouton.obj" \
	"$(INTDIR)/Jibe96.obj" \
	"$(INTDIR)/IconeMem.obj" \
	"$(INTDIR)/SurveilleDlg.obj" \
	"$(INTDIR)/Lpiicone.obj" \
	"$(INTDIR)/IconeHorloge.obj" \
	"$(INTDIR)/IconeSwap.obj" \
	"$(INTDIR)/DlgIcone.obj" \
	"$(INTDIR)/icone.obj" \
	"$(INTDIR)/choosfol.obj" \
	"$(INTDIR)/Jibe96Doc.obj" \
	"$(INTDIR)/PropsDisque.obj" \
	"$(INTDIR)/iconeSeparateur.obj" \
	"$(INTDIR)/Splash.obj" \
	"$(INTDIR)/Jibe96.res"

"$(OUTDIR)\Jibe96.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Jibe96 - Win32 Release"
# Name "Jibe96 - Win32 Debug"

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\DlgIcone.cpp
DEP_CPP_DLGIC=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Dlgicone.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\DlgIcone.obj" : $(SOURCE) $(DEP_CPP_DLGIC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgSeuilAlarme.cpp
DEP_CPP_DLGSE=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\IconeJauge.h"\
	".\DlgSeuilAlarme.h"\
	".\TipDlg.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\DlgSeuilAlarme.obj" : $(SOURCE) $(DEP_CPP_DLGSE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\icone.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONE=\
	".\Icone.h"\
	".\Jibe96View.h"\
	".\Mainfrm.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\icone.obj" : $(SOURCE) $(DEP_CPP_ICONE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONE=\
	".\Stdafx.h"\
	".\Mainfrm.h"\
	".\Icone.h"\
	".\Jibe96View.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\icone.obj" : $(SOURCE) $(DEP_CPP_ICONE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\iconeDisque.cpp
DEP_CPP_ICONED=\
	".\Stdafx.h"\
	".\IconeDisque.h"\
	".\PropsDisque.h"\
	".\Jibe96View.h"\
	".\TipDlg.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\iconeDisque.obj" : $(SOURCE) $(DEP_CPP_ICONED) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\iconeGroupe.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONEG=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\IconeGroupe.h"\
	".\Raccourci.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\iconeGroupe.obj" : $(SOURCE) $(DEP_CPP_ICONEG) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONEG=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\IconeGroupe.h"\
	".\Raccourci.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\iconeGroupe.obj" : $(SOURCE) $(DEP_CPP_ICONEG) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeHorloge.cpp
DEP_CPP_ICONEH=\
	".\Stdafx.h"\
	".\IconeHorloge.h"\
	".\Jibe96View.h"\
	".\LpiBitmap.h"\
	".\TipDlg.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	

"$(INTDIR)\IconeHorloge.obj" : $(SOURCE) $(DEP_CPP_ICONEH) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeJauge.cpp
DEP_CPP_ICONEJ=\
	".\Stdafx.h"\
	".\IconeJauge.h"\
	".\DlgSeuilAlarme.h"\
	".\Jibe96View.h"\
	".\LpiBitmap.h"\
	".\TipDlg.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\IconeJauge.obj" : $(SOURCE) $(DEP_CPP_ICONEJ) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeMem.Cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONEM=\
	".\Icone.h"\
	".\IconeJauge.h"\
	".\Iconemem.h"\
	".\IconePeriodique.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\IconeMem.obj" : $(SOURCE) $(DEP_CPP_ICONEM) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONEM=\
	".\Stdafx.h"\
	".\Iconemem.h"\
	".\TipDlg.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	

"$(INTDIR)\IconeMem.obj" : $(SOURCE) $(DEP_CPP_ICONEM) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\iconeNote.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONEN=\
	".\Icone.h"\
	".\IconeNote.h"\
	".\Jibe96View.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\iconeNote.obj" : $(SOURCE) $(DEP_CPP_ICONEN) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONEN=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\IconeNote.h"\
	".\Jibe96View.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\iconeNote.obj" : $(SOURCE) $(DEP_CPP_ICONEN) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconePeriodique.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONEP=\
	".\Icone.h"\
	".\IconePeriodique.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\IconePeriodique.obj" : $(SOURCE) $(DEP_CPP_ICONEP) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONEP=\
	".\Stdafx.h"\
	".\IconePeriodique.h"\
	".\TipDlg.h"\
	".\Icone.h"\
	

"$(INTDIR)\IconePeriodique.obj" : $(SOURCE) $(DEP_CPP_ICONEP) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\iconeRAM.cpp
DEP_CPP_ICONER=\
	".\Stdafx.h"\
	".\Iconeram.h"\
	".\TipDlg.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	

"$(INTDIR)\iconeRAM.obj" : $(SOURCE) $(DEP_CPP_ICONER) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\iconeSeparateur.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONES=\
	".\Icone.h"\
	".\IconeSeparateur.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\iconeSeparateur.obj" : $(SOURCE) $(DEP_CPP_ICONES) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONES=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\IconeSeparateur.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\iconeSeparateur.obj" : $(SOURCE) $(DEP_CPP_ICONES) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeSurveille.cpp
DEP_CPP_ICONESU=\
	".\Stdafx.h"\
	".\IconeSurveille.h"\
	".\SurveilleDlg.h"\
	".\Choosfol.h"\
	".\DlgOptionsSurveillance.h"\
	".\TipDlg.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\IconeSurveille.obj" : $(SOURCE) $(DEP_CPP_ICONESU) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeSwap.Cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_ICONESW=\
	".\Icone.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\IconeSwap.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\IconeSwap.obj" : $(SOURCE) $(DEP_CPP_ICONESW) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_ICONESW=\
	".\Stdafx.h"\
	".\IconeSwap.h"\
	".\TipDlg.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	

"$(INTDIR)\IconeSwap.obj" : $(SOURCE) $(DEP_CPP_ICONESW) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jibe96.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_JIBE9=\
	".\Icone.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\Jibe96View.h"\
	".\Mainfrm.h"\
	".\Preferences.h"\
	".\Splash.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Jibe96.obj" : $(SOURCE) $(DEP_CPP_JIBE9) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_JIBE9=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Mainfrm.h"\
	".\Jibe96Doc.h"\
	".\Jibe96View.h"\
	".\Splash.h"\
	".\Preferences.h"\
	".\TipDlg.h"\
	".\Icone.h"\
	

"$(INTDIR)\Jibe96.obj" : $(SOURCE) $(DEP_CPP_JIBE9) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jibe96Doc.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_JIBE96=\
	".\Icone.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Jibe96Doc.obj" : $(SOURCE) $(DEP_CPP_JIBE96) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_JIBE96=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\TipDlg.h"\
	".\Icone.h"\
	

"$(INTDIR)\Jibe96Doc.obj" : $(SOURCE) $(DEP_CPP_JIBE96) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jibe96View.cpp
DEP_CPP_JIBE96V=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\Jibe96View.h"\
	".\Mainfrm.h"\
	".\LpiBitmap.h"\
	".\IconeNote.h"\
	".\IconeHorloge.h"\
	".\IconeDisque.h"\
	".\Iconeram.h"\
	".\Iconemem.h"\
	".\IconeSwap.h"\
	".\IconeGroupe.h"\
	".\IconeSeparateur.h"\
	".\Preferences.h"\
	".\PreferencesDlg.h"\
	".\IconeSurveille.h"\
	".\IconeCommande.h"\
	".\IconeBouton.h"\
	".\TipDlg.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	".\IconePeriodique.h"\
	".\IconeJauge.h"\
	".\Raccourci.h"\
	

"$(INTDIR)\Jibe96View.obj" : $(SOURCE) $(DEP_CPP_JIBE96V) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_MAINF=\
	".\Icone.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\Jibe96View.h"\
	".\Mainfrm.h"\
	".\Splash.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_MAINF=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Jibe96Doc.h"\
	".\Jibe96View.h"\
	".\Mainfrm.h"\
	".\Splash.h"\
	".\TipDlg.h"\
	".\Icone.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Preferences.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_PREFE=\
	".\Preferences.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_PREFE=\
	".\Stdafx.h"\
	".\Preferences.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PreferencesDlg.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_PREFER=\
	".\Jibe96.h"\
	".\Preferences.h"\
	".\PreferencesDlg.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\PreferencesDlg.obj" : $(SOURCE) $(DEP_CPP_PREFER) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_PREFER=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\PreferencesDlg.h"\
	".\Preferences.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\PreferencesDlg.obj" : $(SOURCE) $(DEP_CPP_PREFER) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PropsDisque.cpp
DEP_CPP_PROPS=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\IconeDisque.h"\
	".\PropsDisque.h"\
	".\TipDlg.h"\
	".\IconeJauge.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\PropsDisque.obj" : $(SOURCE) $(DEP_CPP_PROPS) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Raccourci.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_RACCO=\
	".\Dlgicone.h"\
	".\Raccourci.h"\
	".\Sclib.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Raccourci.obj" : $(SOURCE) $(DEP_CPP_RACCO) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_RACCO=\
	".\Stdafx.h"\
	".\Raccourci.h"\
	".\Dlgicone.h"\
	".\Sclib.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Raccourci.obj" : $(SOURCE) $(DEP_CPP_RACCO) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\sclib.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_SCLIB=\
	".\Sclib.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\sclib.obj" : $(SOURCE) $(DEP_CPP_SCLIB) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_SCLIB=\
	".\Stdafx.h"\
	".\Sclib.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\sclib.obj" : $(SOURCE) $(DEP_CPP_SCLIB) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Splash.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_SPLAS=\
	".\Icone.h"\
	".\Splash.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_SPLAS=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\Splash.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/Jibe96.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jibe96.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Jibe96.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Jibe96.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WndIcone.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_WNDIC=\
	".\Icone.h"\
	".\IconeGroupe.h"\
	".\Jibe96.h"\
	".\Jibe96View.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\WndIcone.obj" : $(SOURCE) $(DEP_CPP_WNDIC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_WNDIC=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Icone.h"\
	".\Wndicone.h"\
	".\IconeGroupe.h"\
	".\Jibe96View.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\WndIcone.obj" : $(SOURCE) $(DEP_CPP_WNDIC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Jibe96.rc
DEP_RSC_JIBE96_=\
	".\res\ico00007.ico"\
	".\res\ico00008.ico"\
	".\RES\bouton.bmp"\
	".\res\Jibe96.ico"\
	".\res\Cdrom.ico"\
	".\res\Floppy.ico"\
	".\res\Disque_d.ico"\
	".\res\Disque_r.ico"\
	".\res\ico00003.ico"\
	".\res\Ramdisk.ico"\
	".\res\Jibe96Doc.ico"\
	".\res\Icon1.ico"\
	".\res\Note2.ico"\
	".\res\Note12.ico"\
	".\res\Note11.ico"\
	".\res\Note10.ico"\
	".\res\note13.ico"\
	".\res\ico00004.ico"\
	".\res\note15.ico"\
	".\res\Note1.ico"\
	".\res\Ico00001.ico"\
	".\res\Note8.ico"\
	".\res\Note4.ico"\
	".\res\Icon2.ico"\
	".\res\Note6.ico"\
	".\res\Note9.ico"\
	".\res\Ico00002.ico"\
	".\res\idr_main.ico"\
	".\res\note16.ico"\
	".\res\ico00005.ico"\
	".\res\ico00006.ico"\
	".\res\icon3.ico"\
	".\res\surveill.ico"\
	".\res\note17.ico"\
	".\res\Horlmin.bmp"\
	".\res\FOND.bmp"\
	".\res\DATE.bmp"\
	".\res\bitmap1.bmp"\
	".\res\RAM.bmp"\
	".\Splsh.bmp"\
	".\res\MEM.bmp"\
	".\res\swap.bmp"\
	".\res\SWAP16.bmp"\
	".\res\DATE16.bmp"\
	".\res\FOND16.bmp"\
	".\res\HORLMN16.bmp"\
	".\res\MEM16.bmp"\
	".\res\RAM16.bmp"\
	".\res\BITMAP16.bmp"\
	".\res\splash16.bmp"\
	".\res\Toolbar.bmp"\
	".\res\bmp00001.bmp"\
	".\res\TITRE16.bmp"\
	".\res\TITRE.bmp"\
	".\res\assombri.bmp"\
	".\res\litebulb.bmp"\
	".\res\jibe.cur"\
	".\res\Jibe96.rc2"\
	

"$(INTDIR)\Jibe96.res" : $(SOURCE) $(DEP_RSC_JIBE96_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\choosfol.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_CHOOS=\
	".\Choosfol.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\choosfol.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_CHOOS=\
	".\Stdafx.h"\
	".\Choosfol.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\choosfol.obj" : $(SOURCE) $(DEP_CPP_CHOOS) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SurveilleDlg.cpp
DEP_CPP_SURVE=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\SurveilleDlg.h"\
	".\IconeSurveille.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	".\IconePeriodique.h"\
	".\Icone.h"\
	

"$(INTDIR)\SurveilleDlg.obj" : $(SOURCE) $(DEP_CPP_SURVE) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DlgOptionsSurveillance.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_DLGOP=\
	".\DlgOptionsSurveillance.h"\
	".\Jibe96.h"\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\DlgOptionsSurveillance.obj" : $(SOURCE) $(DEP_CPP_DLGOP) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_DLGOP=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\DlgOptionsSurveillance.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\DlgOptionsSurveillance.obj" : $(SOURCE) $(DEP_CPP_DLGOP) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TipDlg.cpp
DEP_CPP_TIPDL=\
	".\Stdafx.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\TipDlg.obj" : $(SOURCE) $(DEP_CPP_TIPDL) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeCommande.cpp
DEP_CPP_ICONEC=\
	".\Stdafx.h"\
	".\Jibe96.h"\
	".\Icone.h"\
	".\IconeCommande.h"\
	".\TipDlg.h"\
	".\Wndicone.h"\
	

"$(INTDIR)\IconeCommande.obj" : $(SOURCE) $(DEP_CPP_ICONEC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LpiBitmap.cpp
DEP_CPP_LPIBI=\
	".\Stdafx.h"\
	".\LpiBitmap.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\LpiBitmap.obj" : $(SOURCE) $(DEP_CPP_LPIBI) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\IconeBouton.cpp
DEP_CPP_ICONEB=\
	".\Stdafx.h"\
	".\Icone.h"\
	".\IconeBouton.h"\
	".\LpiIcone.h"\
	".\LpiBitmap.h"\
	".\Raccourci.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\IconeBouton.obj" : $(SOURCE) $(DEP_CPP_ICONEB) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lpiicone.cpp

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

DEP_CPP_LPIIC=\
	".\Stdafx.h"\
	".\LpiIcone.h"\
	".\LpiBitmap.h"\
	".\TipDlg.h"\
	
NODEP_CPP_LPIIC=\
	".\}"\
	

"$(INTDIR)\Lpiicone.obj" : $(SOURCE) $(DEP_CPP_LPIIC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

DEP_CPP_LPIIC=\
	".\Stdafx.h"\
	".\LpiIcone.h"\
	".\LpiBitmap.h"\
	".\TipDlg.h"\
	

"$(INTDIR)\Lpiicone.obj" : $(SOURCE) $(DEP_CPP_LPIIC) "$(INTDIR)"\
 "$(INTDIR)\Jibe96.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section Jibe96 : {C7CBC2A5-0D53-11CF-B124-0800096E0E20}
# 	0:8:TipDlg.h:C:\Dilp32\Jibe96\TipDlg.h
# 	0:10:TipDlg.cpp:C:\Dilp32\Jibe96\TipDlg.cpp
# 	1:17:CG_IDS_DIDYOUKNOW:114
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:113
# 	1:18:CG_IDS_TIPOFTHEDAY:112
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:117
# 	1:19:CG_IDP_FILE_CORRUPT:116
# 	1:7:IDD_TIP:111
# 	1:13:IDB_LIGHTBULB:110
# 	1:18:CG_IDS_FILE_ABSENT:115
# 	2:17:CG_IDS_DIDYOUKNOW:CG_IDS_DIDYOUKNOW
# 	2:7:CTipDlg:CTipDlg
# 	2:22:CG_IDS_TIPOFTHEDAYMENU:CG_IDS_TIPOFTHEDAYMENU
# 	2:18:CG_IDS_TIPOFTHEDAY:CG_IDS_TIPOFTHEDAY
# 	2:12:CTIP_Written:OK
# 	2:22:CG_IDS_TIPOFTHEDAYHELP:CG_IDS_TIPOFTHEDAYHELP
# 	2:2:BH:
# 	2:19:CG_IDP_FILE_CORRUPT:CG_IDP_FILE_CORRUPT
# 	2:7:IDD_TIP:IDD_TIP
# 	2:8:TipDlg.h:TipDlg.h
# 	2:13:IDB_LIGHTBULB:IDB_LIGHTBULB
# 	2:18:CG_IDS_FILE_ABSENT:CG_IDS_FILE_ABSENT
# 	2:10:TipDlg.cpp:TipDlg.cpp
# End Section
################################################################################
