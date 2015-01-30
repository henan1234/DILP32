# Microsoft Developer Studio Project File - Name="Liaison Forte" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Liaison Forte - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Liaison Forte.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Liaison Forte.mak" CFG="Liaison Forte - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Liaison Forte - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Liaison Forte - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Liaison Forte - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /Ob2 /I "d:\archives\dilp32\economiseurs\liaison forte" /I "d:\archives\dilp32\economiseurs\economiseur generique" /I "d:\archives\dilp32\classes" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D ANNEE_VERSION=1999 /D MOIS_VERSION=6 /D JOUR_VERSION=10 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Molecules.scr"

!ELSEIF  "$(CFG)" == "Liaison Forte - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "c:\dilp32\economiseur\liaison forte" /I "c:\dilp32\classes" /I "c:\dilp32\economiseurs\liaison forte" /I "c:\dilp32\economiseurs\economiseur generique" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 scrnsave.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Liaison Forte - Win32 Release"
# Name "Liaison Forte - Win32 Debug"
# Begin Source File

SOURCE=.\Configuration.CPP
# End Source File
# Begin Source File

SOURCE=.\Configuration.H
# End Source File
# Begin Source File

SOURCE=..\..\Classes\DeblocageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCouleurs.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCouleurs.h
# End Source File
# Begin Source File

SOURCE=.\DlgNombres.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNombres.h
# End Source File
# Begin Source File

SOURCE=..\..\Classes\dlgpriorite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\dlgpriorite.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Econo.cpp"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Economiseur.cpp"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Economiseur.h"
# End Source File
# Begin Source File

SOURCE=.\Fonction.cpp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Information.CPP
# End Source File
# Begin Source File

SOURCE=.\Information.H
# End Source File
# Begin Source File

SOURCE=".\Liaison forte.bmp"
# End Source File
# Begin Source File

SOURCE=".\Liaison Forte.rc"

!IF  "$(CFG)" == "Liaison Forte - Win32 Release"

!ELSEIF  "$(CFG)" == "Liaison Forte - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LiaisonForte.cpp
# End Source File
# Begin Source File

SOURCE=.\LiaisonForte.H
# End Source File
# Begin Source File

SOURCE=.\Lulu.ico
# End Source File
# Begin Source File

SOURCE=.\nombres1.ico
# End Source File
# Begin Source File

SOURCE=.\PhysiqueDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PhysiqueDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\Classes\PropPageRegistering.cpp
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Rectaffichage.cpp"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Rectaffichage.h"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\RegisterDialogClasses.c"
# End Source File
# Begin Source File

SOURCE=..\..\Classes\RegistrationKey.cpp
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Specif.h"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Utilitaires.cpp
# End Source File
# Begin Source File

SOURCE=.\Utilitaires.h
# End Source File
# End Target
# End Project
