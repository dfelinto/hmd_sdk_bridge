HMD SDK Bridge
==============

This library is intended to allow for testing different HMD SDKs for C, C++ and Python applications.
The so called bridge is a high-level wrapper, that abstract the implementation of each of the supported SDKs.

Building Requirements
---------------------
* CMake
* Oculus
 * Oculus SDK 0.7
 * Oculus Run-Time
 * Windows

Code Structure
--------------
```
//build [-]
//cmake
//examples
  |--> c
  |--> cpp
  |--> python
  |--> ...
//extern
  |--> glew
  |--> ...
//python
  |-->bridge
  |-->__init__.py
//source
  |--> HMD_Bridge_API.h
  |--> *.cpp
  |--> *.h
//tests (automatic tests)
CMakeLists.txt
INSTALL
LICENSE
README
```

`[-]` (hmd_sdk_bridge_build.git)

Build Structure
---------------
hmd_sdk_bridge_build.git

```
//include
  |--> HMD_Bridge_API.h [+]
//lib/x64
  |--> BridgeLib.dll
  |--> BridgeLib.lib
  |--> BridgeLib.so
  |--> BridgeLib.dylib
//lib/x86
  |--> BridgeLib.dll
  |--> BridgeLib.lib
  |--> Bridge.so
//bridge [+]
__init__.py [+]
README
```

``[+]`` (files copied/duplicated from hmd_sdk_bridge.git)

How to Build
------------
1. Run CMake
2. Set OCULUS_SDK_DIR
   [C:\OculusSDK\LibOVR]
3. Build (make)
4. Install (make install)

Repeat with BUILD_SHARED_LIBS off, and build for different platforms (x86, x64). 

Install
-------
The installation routine populates the //build folder with the API,
include, the Python wrapper code and the built library.

```
//build/lib/x86
  |--> BridgeLib.dll (from: Win32/Release/BridgeLib.dll)
  |--> BridgeLib.lib (from: Win32/Release/BridgeLib.dll)
//build/lib/x64
  |--> BridgeLib.dll (from: x64/Release/BridgeLib.dll)
  |--> BridgeLib.lib (from: x64/Release/BridgeLib.dll)
```

Besides that, for legacy reasons, the Oculus SDK 0.5 library is to be found there already:
```
//build/lib/x84
  |--> libOculusVR.dylib
  |--> libOculusVR.so
  |--> OculusVR.dll
//build/lib/x64
  |--> libOculusVR.dylib
  |--> libOculusVR.so
  |--> OculusVR.dll
```

After building for the different platforms, the `build` folder can be pushed upstream, and its
submodule hash should be updated in the main repository.

Testing
-------
No automated tests are setup at this moment. But they will live in `tests`.

Source Installation
-------------------
```
$ git clone https://github.com/dfelinto/hmd_sdk_bridge.git
$ cd hmd_sdk_bridge
$ git submodule update --init --recursive --remote
```

Source Update
-------------
```
$ git pull origin
$ git submodule update --recursive --remote
```
