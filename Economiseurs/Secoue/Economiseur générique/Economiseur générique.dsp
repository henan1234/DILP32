# Microsoft Developer Studio Project File - Name="Economiseur g�n�rique" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** NE PAS MODIFIER **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Economiseur g�n�rique - Win32 Debug
!MESSAGE Ce fichier Make est incorrect. Pour g�n�rer ce projet � l'aide de\
 NMAKE,
!MESSAGE utilisez la commande Exporter des fichiers Make et ex�cutez
!MESSAGE 
!MESSAGE NMAKE /f "Economiseur g�n�rique.mak".
!MESSAGE 
!MESSAGE Vous pouvez indiquer une configuration lors de l'ex�cution de NMAKE
!MESSAGE en d�finissant la macro CFG sur la ligne de commande. Par exemple:
!MESSAGE 
!MESSAGE NMAKE /f "Economiseur g�n�rique.mak"\
 CFG="Economiseur g�n�rique - Win32 Debug"
!MESSAGE 
!MESSAGE Les configurations possibles sont les suivantes:
!MESSAGE 
!MESSAGE "Economiseur g�n�rique - Win32 Release" (bas� sur\
 "Win32 (x86) Static Library")
!MESSAGE "Economiseur g�n�rique - Win32 Debug" (bas� sur\
 "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "Economiseur g�n�rique - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Economiseur g�n�rique - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Economiseur g�n�rique - Win32 Release"
# Name "Economiseur g�n�rique - Win32 Debug"
# End Target
# End Project
