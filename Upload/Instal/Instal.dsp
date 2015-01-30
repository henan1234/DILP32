# Microsoft Developer Studio Project File - Name="Instal" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** NE PAS MODIFIER **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Instal - Win32 Debug
!MESSAGE Ce fichier Make est incorrect. Pour générer ce projet à l'aide de\
 NMAKE,
!MESSAGE utilisez la commande Exporter des fichiers Make et exécutez
!MESSAGE 
!MESSAGE NMAKE /f "Instal.mak".
!MESSAGE 
!MESSAGE Vous pouvez indiquer une configuration lors de l'exécution de NMAKE
!MESSAGE en définissant la macro CFG sur la ligne de commande. Par exemple:
!MESSAGE 
!MESSAGE NMAKE /f "Instal.mak" CFG="Instal - Win32 Debug"
!MESSAGE 
!MESSAGE Les configurations possibles sont les suivantes:
!MESSAGE 
!MESSAGE "Instal - Win32 Release" (basé sur "Win32 (x86) Application")
!MESSAGE "Instal - Win32 Debug" (basé sur "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Instal - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "c:\dilp32\upload\instal" /I "c:\dilp32\classes" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ole32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Instal - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ole32.Lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Instal - Win32 Release"
# Name "Instal - Win32 Debug"
# Begin Group "Fichiers source"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChoixRepertoire.cpp
# End Source File
# Begin Source File

SOURCE=.\Choosfol.cpp
# End Source File
# Begin Source File

SOURCE=.\CommandLineFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\Confirmation.cpp
# End Source File
# Begin Source File

SOURCE=.\information.cpp
# End Source File
# Begin Source File

SOURCE=.\Instal.cpp
# End Source File
# Begin Source File

SOURCE=.\Instal.rc

!IF  "$(CFG)" == "Instal - Win32 Release"

!ELSEIF  "$(CFG)" == "Instal - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\InstalDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\LogFile.cpp
# End Source File
# Begin Source File

SOURCE=.\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\Sclib.cpp
# End Source File
# Begin Source File

SOURCE=.\Script.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Fichiers d'en-tête"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChoixRepertoire.h
# End Source File
# Begin Source File

SOURCE=.\CommandLineFilter.h
# End Source File
# Begin Source File

SOURCE=.\Confirmation.h
# End Source File
# Begin Source File

SOURCE=.\information.h
# End Source File
# Begin Source File

SOURCE=.\Instal.h
# End Source File
# Begin Source File

SOURCE=.\InstalDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\Classes\LogFile.h
# End Source File
# Begin Source File

SOURCE=.\Message.h
# End Source File
# Begin Source File

SOURCE=.\RegistrationKey.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Script.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Fichiers de ressources"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Instal.ico
# End Source File
# Begin Source File

SOURCE=.\res\Instal.rc2
# End Source File
# Begin Source File

SOURCE=.\res\Installation.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Install.script
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section Instal : {F7393982-2DDD-11D1-AEF5-444553540000}
# 	2:19:RegistrationKey.cpp:RegistrationKey.cpp
# 	2:23:CLASS: CRegistrationKey:CRegistrationKey
# 	2:17:RegistrationKey.h:RegistrationKey.h
# 	2:19:Application Include:Instal.h
# End Section
