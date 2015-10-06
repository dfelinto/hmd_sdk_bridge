
REM cleanup deployment folder

rd /Q /S bridge

REM copy wrapper
mkdir bridge
copy ..\wrapper\*.py bridge\
mkdir bridge\win32-x86
copy ..\Release\*.dll bridge\win32-x86\
mkdir bridge\win32-x86-64
copy ..\x64\Release\*.dll bridge\win32-x86-64\

REM run test
C:\python34\python.exe run-test.py
