@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by ACTIVEDESKTOP.HPJ. >"hlp\ActiveDesktop.hm"
echo. >>"hlp\ActiveDesktop.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ActiveDesktop.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ActiveDesktop.hm"
echo. >>"hlp\ActiveDesktop.hm"
echo // Prompts (IDP_*) >>"hlp\ActiveDesktop.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ActiveDesktop.hm"
echo. >>"hlp\ActiveDesktop.hm"
echo // Resources (IDR_*) >>"hlp\ActiveDesktop.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ActiveDesktop.hm"
echo. >>"hlp\ActiveDesktop.hm"
echo // Dialogs (IDD_*) >>"hlp\ActiveDesktop.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ActiveDesktop.hm"
echo. >>"hlp\ActiveDesktop.hm"
echo // Frame Controls (IDW_*) >>"hlp\ActiveDesktop.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ActiveDesktop.hm"
REM -- Make help for Project ACTIVEDESKTOP


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\ActiveDesktop.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\ActiveDesktop.hlp" goto :Error
if not exist "hlp\ActiveDesktop.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\ActiveDesktop.hlp" Debug
if exist Debug\nul copy "hlp\ActiveDesktop.cnt" Debug
if exist Release\nul copy "hlp\ActiveDesktop.hlp" Release
if exist Release\nul copy "hlp\ActiveDesktop.cnt" Release
echo.
goto :done

:Error
echo hlp\ActiveDesktop.hpj(1) : error: Problem encountered creating help file

:done
echo.
