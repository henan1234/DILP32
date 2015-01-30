# Microsoft Developer Studio Project File - Name="Secoue" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** NE PAS MODIFIER **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Secoue - Win32 Debug
!MESSAGE Ce fichier Make est incorrect. Pour générer ce projet à l'aide de\
 NMAKE,
!MESSAGE utilisez la commande Exporter des fichiers Make et exécutez
!MESSAGE 
!MESSAGE NMAKE /f "Secoue.mak".
!MESSAGE 
!MESSAGE Vous pouvez indiquer une configuration lors de l'exécution de NMAKE
!MESSAGE en définissant la macro CFG sur la ligne de commande. Par exemple:
!MESSAGE 
!MESSAGE NMAKE /f "Secoue.mak" CFG="Secoue - Win32 Debug"
!MESSAGE 
!MESSAGE Les configurations possibles sont les suivantes:
!MESSAGE 
!MESSAGE "Secoue - Win32 Release" (basé sur "Win32 (x86) Application")
!MESSAGE "Secoue - Win32 Debug" (basé sur "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Secoue - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Secoue.scr"

!ELSEIF  "$(CFG)" == "Secoue - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Secoue - Win32 Release"
# Name "Secoue - Win32 Debug"
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

SOURCE="..\Economiseur generique\RegisterDialogClasses.c"
# End Source File
# Begin Source File

SOURCE=.\Secoue.cpp
# End Source File
# Begin Source File

SOURCE=.\Secoue.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Specif.h"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Stdafx.h"
# End Source File
# End Target
# End Project
