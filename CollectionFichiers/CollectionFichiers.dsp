# Microsoft Developer Studio Project File - Name="CollectionFichiers" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CollectionFichiers - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CollectionFichiers.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CollectionFichiers.mak" CFG="CollectionFichiers - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CollectionFichiers - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CollectionFichiers - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CollectionFichiers - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 version.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "CollectionFichiers - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CollectionFichiers - Win32 Release"
# Name "CollectionFichiers - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CFrameHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\Choosfol.cpp
# End Source File
# Begin Source File

SOURCE=.\CId3Tag.cpp
# End Source File
# Begin Source File

SOURCE=.\CMP3Info.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiers.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiers.idl
# ADD MTL /h "CollectionFichiers_i.h" /iid "CollectionFichiers_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiers.rc
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiersDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiersView.cpp
# End Source File
# Begin Source File

SOURCE=.\CVBitRate.cpp
# End Source File
# Begin Source File

SOURCE=.\Element.cpp
# End Source File
# Begin Source File

SOURCE="C:\Program Files\Microsoft Office\Office\EXCEL8.IDL"
# End Source File
# Begin Source File

SOURCE=.\FileServices.cpp
# End Source File
# Begin Source File

SOURCE=.\FiltreToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\ListeAttributs.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTree.cpp
# End Source File
# Begin Source File

SOURCE=.\RegroupeToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\ScanningDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CFrameHeader.h
# End Source File
# Begin Source File

SOURCE=.\CHOOSFOL.H
# End Source File
# Begin Source File

SOURCE=.\CId3Tag.h
# End Source File
# Begin Source File

SOURCE=.\CMP3Info.h
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiers.h
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiersDoc.h
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiersView.h
# End Source File
# Begin Source File

SOURCE=.\CVBitRate.h
# End Source File
# Begin Source File

SOURCE=.\Element.h
# End Source File
# Begin Source File

SOURCE=.\FileServices.h
# End Source File
# Begin Source File

SOURCE=.\FiltreToolbar.h
# End Source File
# Begin Source File

SOURCE=.\ListeAttributs.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyTree.h
# End Source File
# Begin Source File

SOURCE=.\RegroupeToolbar.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScanningDlg.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TipDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CollectionFichiers.ico
# End Source File
# Begin Source File

SOURCE=.\res\CollectionFichiers.rc2
# End Source File
# Begin Source File

SOURCE=.\CollectionFichiers.rgs
# End Source File
# Begin Source File

SOURCE=.\res\CollectionFichiersDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\dossier1.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\CollectionFichiers.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\Scanne.avi
# End Source File
# End Target
# End Project
# Section CollectionFichiers : {72ADFD54-2C39-11D0-9903-00A0C91BC942}
# 	1:17:CG_IDS_DIDYOUKNOW:116
# 	1:22:CG_IDS_TIPOFTHEDAYMENU:115
# 	1:18:CG_IDS_TIPOFTHEDAY:114
# 	1:22:CG_IDS_TIPOFTHEDAYHELP:119
# 	1:19:CG_IDP_FILE_CORRUPT:118
# 	1:7:IDD_TIP:113
# 	1:13:IDB_LIGHTBULB:112
# 	1:18:CG_IDS_FILE_ABSENT:117
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
# Section CollectionFichiers : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:103
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section CollectionFichiers : {0050004F-0045-0052-5400-59005F005200}
# 	1:22:IDR_COLLECTIONFICHIERS:102
# End Section
