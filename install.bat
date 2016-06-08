REM copy addon

SET BRIDGE="C:\src\hmd_sdk_bridge"
SET RELEASE="C:\src\hmd_sdk_bridge_cmake"

SET SHARED_32=%RELEASE%\shared_32\Release
SET STATIC_32=%RELEASE%\static_32\Release
SET SHARED_64=%RELEASE%\shared_64\Release
SET STATIC_64=%RELEASE%\static_64\Release

SET BUILD=%BRIDGE%\build
cd %BUILD%

REM copy python wrapper
xcopy /Y /E ..\python

REM copy include file
xcopy /Q /Y /E ..\source\HMD_Bridge_API.h include\

REM copy compiled libraries
xcopy /Q /Y /E %SHARED_32%\BridgeLib.dll lib\x86\
xcopy /Q /Y /E %SHARED_64%\BridgeLib.dll lib\x64\
xcopy /Q /Y /E %STATIC_32%\BridgeLib.lib lib\x86\
xcopy /Q /Y /E %STATIC_64%\BridgeLib.lib lib\x64\
