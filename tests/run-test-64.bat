
REM cleanup deployment folder

rd /Q /S bridge

REM copy wrapper

rd /Q /S build
mkdir build
cd "build"

xcopy /Q /Y /E ..\..\bridge bridge\

mkdir bridge\dylibs\win32-x86
mkdir bridge\dylibs\win32-x86-64

copy ..\..\Release\*.dll bridge\dylibs\win32-x86\
copy ..\..\x64\Release\*.dll bridge\dylibs\win32-x86-64\

copy ..\run-test.py run-test.py

REM run test
C:\python35\python.exe run-test.py

cd "..\"

pause