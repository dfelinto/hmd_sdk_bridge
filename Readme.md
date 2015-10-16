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

Once built, the final package should be copied to the bridge dylibs folder:
```
//bridge/dylibs/win32-x86/BridgeLib.dll (Win32/Release/BridgeLib.dll)
//bridge/dylibs/win32-x86-64/BridgeLib.dll (x64/Release/BridgeLib.dll)
```

Besides that, the SDK 0.5 dlls should be copied to:
```
//bridge/dylibs/darwin-x86-64/
//bridge/dylibs/linux-x86-64/
//bridge/dylibs/win32-x86-64/
//bridge/dylibs/win32-x86/
```

The bridge folder should then be copied to the `hmd_sdk_bridge_build` repository and committed.

Testing
-------
Simply `tests/run-tests.bat` and check the output.
