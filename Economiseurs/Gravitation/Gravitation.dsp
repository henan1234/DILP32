# Microsoft Developer Studio Project File - Name="Gravitation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Gravitation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gravitation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gravitation.mak" CFG="Gravitation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gravitation - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Gravitation - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
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
# ADD CPP /nologo /Gr /MT /W4 /O2 /Op /Ob2 /I "c:\dilp32\economiseurs\gravitation" /I "c:\dilp32\economiseurs\economiseur generique" /I "c:\dilp32\classes" /D "NDEBUG" /D ANNEE_VERSION=99 /D MOIS_VERSION=10 /D JOUR_VERSION=5 /D "WIN32" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 scrnsave.lib winmm.lib /nologo /subsystem:windows /machine:I386 /out:"Release/Gravitation.scr"

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
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "c:\dilp32\economiseurs\gravitation" /I "c:\dilp32\economiseurs\economiseur generique" /I "c:\dilp32\classes" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D ANNEE_VERSION=1999 /D MOIS_VERSION=5 /D JOUR_VERSION=23 /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib scrnsave.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Gravitation - Win32 Release"
# Name "Gravitation - Win32 Debug"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\cinema1.ico
# End Source File
# Begin Source File

SOURCE=.\Comete1.ico
# End Source File
# Begin Source File

SOURCE=.\Copyright.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Copyright.dib"
# End Source File
# Begin Source File

SOURCE=.\creation.ico
# End Source File
# Begin Source File

SOURCE=..\..\Classes\DeblocageDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\DeblocageDlg.h
# End Source File
# Begin Source File

SOURCE=.\decor1.dib
# End Source File
# Begin Source File

SOURCE=.\Decor2.dib
# End Source File
# Begin Source File

SOURCE=.\Decor3.dib
# End Source File
# Begin Source File

SOURCE=.\decor4.dib
# End Source File
# Begin Source File

SOURCE=.\decor5.dib
# End Source File
# Begin Source File

SOURCE=.\decor6.dib
# End Source File
# Begin Source File

SOURCE=.\decor7.dib
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

SOURCE=.\distance.ico
# End Source File
# Begin Source File

SOURCE=..\..\Classes\dlgpriorite.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\dlgpriorite.h
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

SOURCE=.\NouvellesImages\espace_fond.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\espacefond.dib"
# End Source File
# Begin Source File

SOURCE=.\etoiles.ico
# End Source File
# Begin Source File

SOURCE=.\etoiles1.ico
# End Source File
# Begin Source File

SOURCE=.\NouvellesImages\explosion256.dib
# End Source File
# Begin Source File

SOURCE=.\fichier.ico
# End Source File
# Begin Source File

SOURCE=.\g1.ico
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

SOURCE=.\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\id_app.ico
# End Source File
# Begin Source File

SOURCE=.\image1.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image10.dib"
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image11.dib"
# End Source File
# Begin Source File

SOURCE=.\Image2.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image2.dib"
# End Source File
# Begin Source File

SOURCE=.\Image3.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image3.dib"
# End Source File
# Begin Source File

SOURCE=.\Image4.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image4.dib"
# End Source File
# Begin Source File

SOURCE=.\Image5.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image5.dib"
# End Source File
# Begin Source File

SOURCE=.\Image6.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image6.dib"
# End Source File
# Begin Source File

SOURCE=.\Image7.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image7.dib"
# End Source File
# Begin Source File

SOURCE=.\Image8.dib
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image8.dib"
# End Source File
# Begin Source File

SOURCE=".\Images de Fond\Image9.dib"
# End Source File
# Begin Source File

SOURCE=.\jauge.bmp
# End Source File
# Begin Source File

SOURCE=.\Lulu.ico
# End Source File
# Begin Source File

SOURCE=.\masse_1.ico
# End Source File
# Begin Source File

SOURCE=.\masse_2.ico
# End Source File
# Begin Source File

SOURCE=.\masse_3.ico
# End Source File
# Begin Source File

SOURCE=.\masse_4.ico
# End Source File
# Begin Source File

SOURCE=.\masse_5.ico
# End Source File
# Begin Source File

SOURCE=.\masse_6.ico
# End Source File
# Begin Source File

SOURCE=.\masse_7.ico
# End Source File
# Begin Source File

SOURCE=.\masses1.ico
# End Source File
# Begin Source File

SOURCE=.\max1.ico
# End Source File
# Begin Source File

SOURCE=.\min.ico
# End Source File
# Begin Source File

SOURCE=.\min1.ico
# End Source File
# Begin Source File

SOURCE=.\nombres1.ico
# End Source File
# Begin Source File

SOURCE=.\Option.cpp
# End Source File
# Begin Source File

SOURCE=.\Option.h
# End Source File
# Begin Source File

SOURCE=.\OptionChaine.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionChaine.h
# End Source File
# Begin Source File

SOURCE=.\OptionEntier.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionEntier.h
# End Source File
# Begin Source File

SOURCE=.\OptionFlottant.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionFlottant.h
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\Page1.cpp
# End Source File
# Begin Source File

SOURCE=.\Page1.h
# End Source File
# Begin Source File

SOURCE=.\PagesParametres.cpp
# End Source File
# Begin Source File

SOURCE=.\PagesParametres.h
# End Source File
# Begin Source File

SOURCE=.\Palette.dib
# End Source File
# Begin Source File

SOURCE=.\physique.ico
# End Source File
# Begin Source File

SOURCE=..\..\Classes\PropPageRegistering.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\PropPageRegistering.h
# End Source File
# Begin Source File

SOURCE=.\rayon1.ico
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Rectaffichage.cpp"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Rectaffichage.h"
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\RegisterDialogClasses.c"
# ADD CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\Classes\RegistrationKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Classes\RegistrationKey.h
# End Source File
# Begin Source File

SOURCE=.\repere1.ico
# End Source File
# Begin Source File

SOURCE=.\repere2.ico
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SharewareMessageWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SharewareMessageWnd.h
# End Source File
# Begin Source File

SOURCE=.\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\Skin.h
# End Source File
# Begin Source File

SOURCE="..\Economiseur generique\Specif.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\travelin.ico
# End Source File
# Begin Source File

SOURCE=.\UniverseFile.cpp
# End Source File
# End Target
# End Project
# Section Gravitation : {00000000-0000-0000-0000-000000000000}
# 	2:14:CDlgParametres:Palette support added
# End Section
