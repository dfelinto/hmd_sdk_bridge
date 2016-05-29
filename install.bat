REM copy addon

SET BRIDGE="C:\src\hmd_sdk_bridge"
SET RELEASE="C:\src\hmd_sdk_bridge_release"

SET RELEASE_32=%RELEASE%\Release
SET RELEASE_64=%RELEASE%\x64\Release

SET BUILD=%BRIDGE%\build
cd %BUILD%

REM copy python wrapper
xcopy /Y /E ..\python

REM copy include file
xcopy /Q /Y /E ..\source\HMD_Bridge_API.h include\

REM copy compiled libraries
xcopy /Q /Y /E %RELEASE_32%\BridgeLib.dll lib\x86\
xcopy /Q /Y /E %RELEASE_32%\BridgeLib.lib lib\x86\
xcopy /Q /Y /E %RELEASE_64%\BridgeLib.dll lib\x64\
xcopy /Q /Y /E %RELEASE_64%\BridgeLib.lib lib\x64\
