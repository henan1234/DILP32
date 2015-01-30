@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by JIBE3.HPJ. >"hlp\Jibe3.hm"
echo. >>"hlp\Jibe3.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Jibe3.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Jibe3.hm"
echo. >>"hlp\Jibe3.hm"
echo // Prompts (IDP_*) >>"hlp\Jibe3.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Jibe3.hm"
echo. >>"hlp\Jibe3.hm"
echo // Resources (IDR_*) >>"hlp\Jibe3.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Jibe3.hm"
echo. >>"hlp\Jibe3.hm"
echo // Dialogs (IDD_*) >>"hlp\Jibe3.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Jibe3.hm"
echo. >>"hlp\Jibe3.hm"
echo // Frame Controls (IDW_*) >>"hlp\Jibe3.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Jibe3.hm"
REM -- Make help for Project JIBE3


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Jibe3.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Jibe3.hlp" goto :Error
if not exist "hlp\Jibe3.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Jibe3.hlp" Debug
if exist Debug\nul copy "hlp\Jibe3.cnt" Debug
if exist Release\nul copy "hlp\Jibe3.hlp" Release
if exist Release\nul copy "hlp\Jibe3.cnt" Release
echo.
goto :done

:Error
echo hlp\Jibe3.hpj(1) : error: Problem encountered creating help file

:done
echo.
