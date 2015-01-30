# Microsoft Developer Studio Project File - Name="Jibe96" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Jibe96 - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Jibe96.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Jibe96.mak" CFG="Jibe96 - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Jibe96 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Jibe96 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Jibe96 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Jibe96 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Jibe96 - Win32 Release"
# Name "Jibe96 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\choosfol.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIcone.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSurveillance.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSeuilAlarme.cpp
# End Source File
# Begin Source File

SOURCE=.\icone.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeBouton.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeCommande.cpp
# End Source File
# Begin Source File

SOURCE=.\iconeDisque.cpp
# End Source File
# Begin Source File

SOURCE=.\iconeGroupe.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeHorloge.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeJauge.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeMem.Cpp
# End Source File
# Begin Source File

SOURCE=.\iconeNote.cpp
# End Source File
# Begin Source File

SOURCE=.\IconePeriodique.cpp
# End Source File
# Begin Source File

SOURCE=.\iconeRAM.cpp
# End Source File
# Begin Source File

SOURCE=.\iconeSeparateur.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeSurveille.cpp
# End Source File
# Begin Source File

SOURCE=.\IconeSwap.Cpp
# End Source File
# Begin Source File

SOURCE=.\Jibe96.cpp
# End Source File
# Begin Source File

SOURCE=.\Jibe96.rc
# End Source File
# Begin Source File

SOURCE=.\Jibe96Doc.cpp
# End Source File
# Begin Source File

SOURCE=.\Jibe96View.cpp
# End Source File
# Begin Source File

SOURCE=.\LpiBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\Lpiicone.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Preferences.cpp
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PropsDisque.cpp
# End Source File
# Begin Source File

SOURCE=.\Raccourci.cpp
# End Source File
# Begin Source File

SOURCE=.\sclib.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SurveilleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WndIcone.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\Choosfol.h
# End Source File
# Begin Source File

SOURCE=.\Dlgicone.h
# End Source File
# Begin Source File

SOURCE=.\DlgOptionsSurveillance.h
# End Source File
# Begin Source File

SOURCE=.\DlgSeuilAlarme.h
# End Source File
# Begin Source File

SOURCE=.\Icone.h
# End Source File
# Begin Source File

SOURCE=.\IconeBouton.h
# End Source File
# Begin Source File

SOURCE=.\IconeCommande.h
# End Source File
# Begin Source File

SOURCE=.\IconeDisque.h
# End Source File
# Begin Source File

SOURCE=.\IconeGroupe.h
# End Source File
# Begin Source File

SOURCE=.\IconeHorloge.h
# End Source File
# Begin Source File

SOURCE=.\IconeJauge.h
# End Source File
# Begin Source File

SOURCE=.\Iconemem.h
# End Source File
# Begin Source File

SOURCE=.\IconeNote.h
# End Source File
# Begin Source File

SOURCE=.\IconePeriodique.h
# End Source File
# Begin Source File

SOURCE=.\Iconeram.h
# End Source File
# Begin Source File

SOURCE=.\IconeSeparateur.h
# End Source File
# Begin Source File

SOURCE=.\IconeSurveille.h
# End Source File
# Begin Source File

SOURCE=.\IconeSwap.h
# End Source File
# Begin Source File

SOURCE=.\Jibe96.h
# End Source File
# Begin Source File

SOURCE=.\Jibe96Doc.h
# End Source File
# Begin Source File

SOURCE=.\Jibe96View.h
# End Source File
# Begin Source File

SOURCE=.\LpiBitmap.h
# End Source File
# Begin Source File

SOURCE=.\LpiIcone.h
# End Source File
# Begin Source File

SOURCE=.\Mainfrm.h
# End Source File
# Begin Source File

SOURCE=.\Preferences.h
# End Source File
# Begin Source File

SOURCE=.\PreferencesDlg.h
# End Source File
# Begin Source File

SOURCE=.\PropsDisque.h
# End Source File
# Begin Source File

SOURCE=.\Raccourci.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Sclib.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\SurveilleDlg.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# Begin Source File

SOURCE=.\Wndicone.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\assombri.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BITMAP16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bouton.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Cdrom.ico
# End Source File
# Begin Source File

SOURCE=.\res\DATE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DATE16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Disque_d.ico
# End Source File
# Begin Source File

SOURCE=.\res\Disque_r.ico
# End Source File
# Begin Source File

SOURCE=.\res\Floppy.ico
# End Source File
# Begin Source File

SOURCE=.\res\FOND.bmp
# End Source File
# Begin Source File

SOURCE=.\res\FOND16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Horlmin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HORLMN16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\jibe.cur
# End Source File
# Begin Source File

SOURCE=.\res\Jibe96.ico
# End Source File
# Begin Source File

SOURCE=.\res\Jibe96.rc2
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MEM.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MEM16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Note1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note10.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note11.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note12.ico
# End Source File
# Begin Source File

SOURCE=.\res\note15.ico
# End Source File
# Begin Source File

SOURCE=.\res\note16.ico
# End Source File
# Begin Source File

SOURCE=.\res\note17.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note4.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note6.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note8.ico
# End Source File
# Begin Source File

SOURCE=.\res\Note9.ico
# End Source File
# Begin Source File

SOURCE=.\res\RAM.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RAM16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ramdisk.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\surveill.ico
# End Source File
# Begin Source File

SOURCE=.\res\swap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SWAP16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TITRE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TITRE16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# End Target
# End Project
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
