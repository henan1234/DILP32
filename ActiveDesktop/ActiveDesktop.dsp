# Microsoft Developer Studio Project File - Name="ActiveDesktop" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ActiveDesktop - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ActiveDesktop.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ActiveDesktop.mak" CFG="ActiveDesktop - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ActiveDesktop - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ActiveDesktop - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ActiveDesktop - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ActiveD0"
# PROP BASE Intermediate_Dir "ActiveD0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ActiveD0"
# PROP Intermediate_Dir "ActiveD0"
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
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ActiveDesktop - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ActiveD1"
# PROP BASE Intermediate_Dir "ActiveD1"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "ActiveD1"
# PROP Intermediate_Dir "ActiveD1"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ActiveDesktop - Win32 Release"
# Name "ActiveDesktop - Win32 Debug"
# Begin Source File

SOURCE=.\ActiveDesktop.cpp
# End Source File
# Begin Source File

SOURCE=.\ActiveDesktop.h
# End Source File
# Begin Source File

SOURCE=.\ActiveDesktop.rc

!IF  "$(CFG)" == "ActiveDesktop - Win32 Release"

!ELSEIF  "$(CFG)" == "ActiveDesktop - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ActiveDesktopDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ActiveDesktopDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChangeMotDePasse.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangeMotDePasse.h
# End Source File
# Begin Source File

SOURCE=.\DeblocageDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeblocageDlg.h
# End Source File
# Begin Source File

SOURCE=.\FenetreTransparente.cpp
# End Source File
# Begin Source File

SOURCE=.\FenetreTransparente.h
# End Source File
# Begin Source File

SOURCE=.\GraphicPropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphicPropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\PageInformation.cpp
# End Source File
# Begin Source File

SOURCE=.\PageInformation.h
# End Source File
# Begin Source File

SOURCE=.\Preferences.cpp
# End Source File
# Begin Source File

SOURCE=.\Preferences.h
# End Source File
# Begin Source File

SOURCE=.\PropPageRegistering.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPageRegistering.h
# End Source File
# Begin Source File

SOURCE=.\PropPages.cpp
# End Source File
# Begin Source File

SOURCE=.\PropPages.h
# End Source File
# Begin Source File

SOURCE=.\RegistrationKey.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistrationKey.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SaisieMotDePasse.cpp
# End Source File
# Begin Source File

SOURCE=.\SaisieMotDePasse.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WorkingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\WorkingDlg.h
# End Source File
# End Target
# End Project
