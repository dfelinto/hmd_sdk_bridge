Oculus SDK Bridge
=================

This library works on Windows only, and with the Oculus SDK 0.7.

Requirements
------------
* Oculus SDK 0.7
* Oculus Run-Time
* Windows
* MSVC 2013

How to Build
------------
1. Open Project file
2. Right-Click in BridgeLib and select `Properties`
3. `Linker` > `Input` > `Additional Dependencies`
4. Add in the file and path for the Oculus .lib files:
   C:\OculusSDK\LibOVR\Lib\Windows\Win32\Debug\VS2013\LibOVR.lib
   C:\OculusSDK\LibOVR\Lib\Windows\Win32\Release\VS2013\LibOVR.lib
   (change it accordingly to your Oculus SDK location).

5. Under the project's properties, `Configuration Properties` > `C/C++` > `Additional Include Directories`:
   C:\OculusSDK\LibOVR\Include
   C:\OculusSDK\LibOVRKernel\Src
   (change it accordingly to your Oculus SDK location).

6. Build the solution

Once built, the final package should be assembled with the wrapper python files such that:
```
//bridge (new folder)
//bridge/__init__.py (wrapper/__init__.py)
//bridge/hmd.py (wrapper/hmd.py)
//bridge/oculus.py (wrapper/oculus.py)
//bridge/win32-x86/BridgeLib.dll (Release/BridgeLib.dll)
```

Testing
-------
Simply `tests/run-tests.bat` and check the output.
