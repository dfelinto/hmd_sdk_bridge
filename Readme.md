# Head Mounted Display SDK Bridge for Blender Viewport Add-on
===============================

A Native (C++) to Python bridge for multiple Virtual Reality Head Mounted
Displays (HMDs) for use with the Blender Virtual Reality Viewport Add-on
(https://github.com/dfelinto/virtual_reality_viewport)

By Dalai Felinto (Oculus, and multi HMD Architecture).
OpenVR Implemented by @cedeon (William Culver)

This library works on Windows only, with the Oculus SDK 0.7. & OpenVR based HMD's

---------------------------

## Requirements

* For HTC Vive & OpenVR Compatible HMDs - Steam & OpenVR
* For Oculus: Oculus SDK 0.7 & Oculus Run-Time
* For Legacy Oculus Support: Oculus SDK 0.5 & 0.5 Runtime (OculusVR.dll)
* Windows
* MSVC 2013

## Dependencies

- Glew (Headers & Compiled Library) - Version 1.13.0 as of writing.
- OpenVR (Headers & Compiled Library) - Version OpenVR SDK 0.9.20 as of writing
- Oculus (Headers & Compiled Library) - Version 0.7 as of writing.

### Where to get Dependencies

- OpenVR SDK - https://github.com/ValveSoftware/openvr/
- Oculus SDK - https://developer.oculus.com/downloads/
- Glew - http://glew.sourceforge.net/

### Current Testing status.

- HTC Vive on Windows x64 - WORKS.
- HTC Vive on Windows x86 - compiled but not tested.
- Oculus DK2 on 0.7 Runtime on Windows - WORKS.

------------------------

How to Build
------------
1. Open Project file
2. Right-Click in BridgeLib and select `Properties`
3. `Linker` > `Input` > `Additional Dependencies`
4. Add the following - LibOVR.lib , opengl32.lib, glew32.lib, openvr_api.lib
5. Add the following aswell - LibOVR.lib , opengl32.lib, glew32.lib, openvr_api.lib
6. `Linker` > `General` > `Additional Library Directories`
7. Add the directories containing the files in step #4.
5. Under the project's properties, `Configuration Properties` > `C/C++` > `Additional Include Directories`:
D:\git\openvr\samples\thirdparty\sdl2-2.0.3\include;
D:\git\openvr\headers;C:\Oculus\OculusSDK\LibOVR\Include;
C:\Oculus\OculusSDK\LibOVRKernel\Src;
D:\git\hmd_sdk_bridge\Project\thirdparty\glew-1.13.0\include
   (change it accordingly to your file locations).

6. Build the solution

Once built, the final package should be copied to the bridge dylibs folder:
```
//bridge/dylibs/win32-x86/BridgeLib.dll (From Win32/Release/BridgeLib.dll)
//bridge/dylibs/win32-x86-64/BridgeLib.dll (From x64/Release/BridgeLib.dll)
```

Besides that, the SDK 0.5 dlls (OculusVR.dll), glew32.dll & openvr_api.dll should be copied to:
```
//bridge/dylibs/win32-x86-64/
//bridge/dylibs/win32-x86/
```

TODO - The following are to be implemented at a later date.
//bridge/dylibs/darwin-x86-64/
//bridge/dylibs/linux-x86-64/


The bridge folder should then be copied to the `hmd_sdk_bridge_build` repository and committed.

Testing
-------
Simply `tests/run-tests.bat` and check the output.
