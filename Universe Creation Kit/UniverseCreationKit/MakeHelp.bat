@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by UNIVERSECREATIONKIT.HPJ. >"hlp\UniverseCreationKit.hm"
echo. >>"hlp\UniverseCreationKit.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\UniverseCreationKit.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\UniverseCreationKit.hm"
echo. >>"hlp\UniverseCreationKit.hm"
echo // Prompts (IDP_*) >>"hlp\UniverseCreationKit.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\UniverseCreationKit.hm"
echo. >>"hlp\UniverseCreationKit.hm"
echo // Resources (IDR_*) >>"hlp\UniverseCreationKit.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\UniverseCreationKit.hm"
echo. >>"hlp\UniverseCreationKit.hm"
echo // Dialogs (IDD_*) >>"hlp\UniverseCreationKit.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\UniverseCreationKit.hm"
echo. >>"hlp\UniverseCreationKit.hm"
echo // Frame Controls (IDW_*) >>"hlp\UniverseCreationKit.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\UniverseCreationKit.hm"
REM -- Make help for Project UNIVERSECREATIONKIT


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\UniverseCreationKit.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\UniverseCreationKit.hlp" goto :Error
if not exist "hlp\UniverseCreationKit.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\UniverseCreationKit.hlp" Debug
if exist Debug\nul copy "hlp\UniverseCreationKit.cnt" Debug
if exist Release\nul copy "hlp\UniverseCreationKit.hlp" Release
if exist Release\nul copy "hlp\UniverseCreationKit.cnt" Release
echo.
goto :done

:Error
echo hlp\UniverseCreationKit.hpj(1) : error: Problem encountered creating help file

:done
echo.
