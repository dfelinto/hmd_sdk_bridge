REM ~~~ Put this in the solution as a post build script ~~~
cd %1
copy .\build\Win32\Release\BridgeLib.dll bridge\dylibs\win32-x86
copy .\build\x64\Release\BridgeLib.dll bridge\dylibs\win32-x86-64
exit 0
