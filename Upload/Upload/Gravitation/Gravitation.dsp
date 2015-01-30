# Microsoft Developer Studio Project File - Name="Gravitation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** NE PAS MODIFIER **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gravitation - Win32 Debug
!MESSAGE Ce fichier Make est incorrect. Pour générer ce projet à l'aide de\
 NMAKE,
!MESSAGE utilisez la commande Exporter des fichiers Make et exécutez
!MESSAGE 
!MESSAGE NMAKE /f "Gravitation.mak".
!MESSAGE 
!MESSAGE Vous pouvez indiquer une configuration lors de l'exécution de NMAKE
!MESSAGE en définissant la macro CFG sur la ligne de commande. Par exemple:
!MESSAGE 
!MESSAGE NMAKE /f "Gravitation.mak" CFG="Gravitation - Win32 Debug"
!MESSAGE 
!MESSAGE Les configurations possibles sont les suivantes:
!MESSAGE 
!MESSAGE "Gravitation - Win32 Release" (basé sur "Win32 (x86) Application")
!MESSAGE "Gravitation - Win32 Debug" (basé sur "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gravitation - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Gravitation - Win32 Debug"

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

# Name "Gravitation - Win32 Release"
# Name "Gravitation - Win32 Debug"
# Begin Source File

SOURCE=.\Bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\Bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\Bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\Bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\Bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\Comete1.ico
# End Source File
# Begin Source File

SOURCE=.\creation.ico
# End Source File
# Begin Source File

SOURCE=.\Decor2.dib
# End Source File
# Begin Source File

SOURCE=.\Decor3.dib
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dib.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dib.h
# End Source File
# Begin Source File

SOURCE=.\Dib1.dib
# End Source File
# Begin Source File

SOURCE=.\Dib10.dib
# End Source File
# Begin Source File

SOURCE=.\Dib2.dib
# End Source File
# Begin Source File

SOURCE=.\Dib3.dib
# End Source File
# Begin Source File

SOURCE=.\Dib4.dib
# End Source File
# Begin Source File

SOURCE=.\Dib5.dib
# End Source File
# Begin Source File

SOURCE=.\Dib6.dib
# End Source File
# Begin Source File

SOURCE=.\Dib7.dib
# End Source File
# Begin Source File

SOURCE=.\Dib8.dib
# End Source File
# Begin Source File

SOURCE=.\Dib9.dib
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dibpal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dibpal.h
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dibsurface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\Dibsurface.h
# End Source File
# Begin Source File

SOURCE=.\Dlgparametres.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgparametres.h
# End Source File
# Begin Source File

SOURCE=.\Ecogravitation.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Econo.cpp"
# End Source File
# Begin Source File

SOURCE=.\Econo.ico
# End Source File
# Begin Source File

SOURCE=.\Econo.rc
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Economiseur.cpp"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Economiseur.h"
# End Source File
# Begin Source File

SOURCE=.\Etoilebrillante.dib
# End Source File
# Begin Source File

SOURCE=.\Etoilebrillante2.dib
# End Source File
# Begin Source File

SOURCE=.\Etoilerouge.dib
# End Source File
# Begin Source File

SOURCE=.\Explosion.dib
# End Source File
# Begin Source File

SOURCE=.\Galaxie.dib
# End Source File
# Begin Source File

SOURCE=.\Gravitation.cpp
# End Source File
# Begin Source File

SOURCE=.\Ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\Ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\Ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\Icon2.ico
# End Source File
# Begin Source File

SOURCE=.\Lulu.ico
# End Source File
# Begin Source File

SOURCE=.\Masse2.bmp
# End Source File
# Begin Source File

SOURCE=.\Masse3.bmp
# End Source File
# Begin Source File

SOURCE=.\Masse4.bmp
# End Source File
# Begin Source File

SOURCE=.\Masse8.bmp
# End Source File
# Begin Source File

SOURCE=.\masses1.ico
# End Source File
# Begin Source File

SOURCE=.\Nebuleuse.dib
# End Source File
# Begin Source File

SOURCE=.\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page1.h
# End Source File
# Begin Source File

SOURCE=.\Page2.cpp
# End Source File
# Begin Source File

SOURCE=.\Page2.h
# End Source File
# Begin Source File

SOURCE=.\Page3.h
# End Source File
# Begin Source File

SOURCE=.\Page4.h
# End Source File
# Begin Source File

SOURCE=.\Page5.h
# End Source File
# Begin Source File

SOURCE=.\Pageaffichage.cpp
# End Source File
# Begin Source File

SOURCE=.\Pageaffichage.h
# End Source File
# Begin Source File

SOURCE=.\Pagecomete.cpp
# End Source File
# Begin Source File

SOURCE=.\Pagecomete.h
# End Source File
# Begin Source File

SOURCE=.\Pagefond.h
# End Source File
# Begin Source File

SOURCE=.\Pagegenese.cpp
# End Source File
# Begin Source File

SOURCE=.\Pagegenese.h
# End Source File
# Begin Source File

SOURCE=.\Pagemasses.cpp
# End Source File
# Begin Source File

SOURCE=.\Pagemasses.h
# End Source File
# Begin Source File

SOURCE=.\Pagephysique.cpp
# End Source File
# Begin Source File

SOURCE=.\Pagephysique.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
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

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Specif.h"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Stdafx.h"
# End Source File
# End Target
# End Project
