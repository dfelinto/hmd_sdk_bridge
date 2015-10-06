Oculus SDK Bridge
*****************

This library works on Windows only, and with the Oculus SDK 0.7.

How to build:
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


6. Build
